//---------------------------------------------------------------------------

#ifndef CD_9904H
#define CD_9904H
//---------------------------------------------------------------------------

#include <Classes.hpp>

#include "ComPort.h"
#include <boost/thread.hpp>
namespace CD_9904
{
//параметры пакета
	//заголовок  позиции в массиве
	#define     SYNC 		0  //позиция символа синхронизации
	#define     LEN			1  //позиция длинны информационной части пакета
	#define     ADDR 		2  //позиция адреса устройства
	#define     NUM 		3  //позиция NUM в этом протоколе сегда равна 0x00
	#define     CRC_TITLE 	4  //позиция начала контрольной суммы заголовка

	//содержимое пакета
	#define     TYPE 		6  //позиция типа информации в пакете
	#define		INF_I		7  //позиция первого байта информации
//константы
	#define   	TILE_LEN 		6  	//длинна загловка пакета пакета
	#define 	CRC_TITLE_LEN 	2 	//длина CRC кода заголовка
	#define 	CRC_TITLE_INF 	2 	//длина CRC кода Информации

	enum ErrCode 	{
					Sucsess			=0x0,
					Addr_Err		=0x1,
					CRC_Info		=0x2,
					Unknown_command	=0x3,
					Too_long_message=0x5,
					Time_out_err	=0x7,
					Ident_err		=0x8,
					CRC_Title		=0x9,
					Unknown_err		=0x10
					};
	enum Info 		{
					Sensor_first_carriage	=0x0,
					Sensor_second_carriage	=0x1,
					Speed_over_350			=0x2,
					Speed_less_10			=0x3,
					Drum_stopped			=0x4
					};
	class CD_Time
	{

	public:
		explicit CD_Time(unsigned short _hours=0,BYTE _minits=0);
		explicit CD_Time(String TimeStr);
				~CD_Time();
		unsigned int  Get_hours			(void)const{return (unsigned int)hours;};
		unsigned int  Get_minits		(void)const{return (unsigned int)minits;};
		String        Get_time_string	(void)const{return time_string;};
		int 		  Get_msek			(void)const{return msek;};
	private:
		unsigned short hours;
		BYTE           minits;
		String         time_string;
		int 		   msek;
	};
	class Data
	{
		public:

			 Data (BYTE *ans,size_t size);
			 ~Data();
			 double 		Speed	(void)const{return speed;}; //измеряемая скорость
			 unsigned int 	Road_1	(void)const{return road_1;}; //измеряемый путь канал 1
			 CD_Time        Time_1	(void)const{return *time_1;}; //время испытания
			 unsigned int 	Road_2	(void)const{return road_2;}; //измеряемый путь канал 2
			 CD_Time        Time_2	(void)const{return *time_2;}; //время испытания
			 Info			St_Info	(String & str);  //информация о состоянии
		private:
			 double speed;  //измеряемая скорость разрешение 0,1 км/ч
			 unsigned int road_1; //измеряемый путь канал 1 разрешение 1 км
			 unsigned int road_2; //измеряемый путь канал 2 разрешение 1 км
             boost::shared_ptr<CD_Time> time_1; //время испытания 1 байт -часы ст байт 2 байт часы мл байт 3 байт минуты
             boost::shared_ptr<CD_Time> time_2; //время испытания 1 байт -часы ст байт 2 байт часы мл байт 3 байт минуты
			 BYTE inform; 	/*служебное инфо флаги 	0- датчик каретки 1
													1- датчик каретки 2
													2- скорость больше 350 км/ч
													3- скорость меньше 10 км/ч
													4- барабан остановлен
													enum info
													*/
	};
	class Sensor
	{
		public:
					Sensor(wchar_t *_COM,BYTE _addr,bool init=true); //конструктор с создание собственного порта
					Sensor(COMPort * _port,BYTE _addr);  //конструктор с импортирование чужого порта
					~Sensor();
			ErrCode	Init			(BYTE _addr);             //инициализация устройства
			ErrCode Write_ADDR		(BYTE _addr);             //запись нового адреса устройству
			ErrCode Read_Diametr	(unsigned short &Diametr);//считывание диаметра в переменную параметра
			ErrCode	Write_Diametr	(unsigned short Diametr);//разрешение 1 мм
			ErrCode	Tansl_Speed  	(boost::shared_ptr<Data> &speed);
			ErrCode	Write_Road_1    (unsigned int road);
			ErrCode	Write_Road_2    (unsigned int road);
			ErrCode	Write_Time_1    (CD_Time *time);
			ErrCode	Write_Time_2    (CD_Time *time);
			COMPort * GetPort		(void)
			{
				return port;
			}
			BYTE 	GetAddr			(void)
			{
				return addr;
			}

static		String  Get_Err			(ErrCode err);  //возвращает текстовое описание ошибки
		private:
			ErrCode Compile_command	(       //компиляция команды отправляемой датчику
									BYTE _type,   //тип пакета команды
									BYTE data_len,//длинна секции передаваемых данных в команде
									BYTE *s_data,      //передаваемые данные
									size_t s_data_len, //длинна передаваемых данных
									BYTE r_type,       //тип пакета ответа
									BYTE *r_data,      //массиив для получения ответа
									size_t &r_data_len //размер ответа
									);
			void  	Get_Com_Title	(size_t len, BYTE *com); //генерация заголовка пакета
			bool 	Check_CRC       (const BYTE *);  //проверка целостности пакета по crc
			void	Get_Title_CRC 	(const BYTE *com, BYTE *title_crc, size_t crc_len); //расчет crc заголовка пакета
			void	Get_CRC_IFO   	(const BYTE *com, BYTE *info_crc, size_t crc_len);  //расчет crc содержимого пакета

			ErrCode SendMessage		(const BYTE*);  //отправка задания датчику, проверка выполнения по отклику

			COMPort *port;      //объект порта для управления
	const 	wchar_t *COM;       //название порта
			BYTE 	addr;       //адресс устройства
			bool 	port_owner; //метка хозяина компорта (учитывается при деструкции)
	};
};

#endif
