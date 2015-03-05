//---------------------------------------------------------------------------

#ifndef CD_9904H
#define CD_9904H
//---------------------------------------------------------------------------

#include <Classes.hpp>

#include "ComPort.h"
#include <boost/thread.hpp>
namespace CD_9904
{
//��������� ������
	//���������  ������� � �������
	#define     SYNC 		0  //������� ������� �������������
	#define     LEN			1  //������� ������ �������������� ����� ������
	#define     ADDR 		2  //������� ������ ����������
	#define     NUM 		3  //������� NUM � ���� ��������� ����� ����� 0x00
	#define     CRC_TITLE 	4  //������� ������ ����������� ����� ���������

	//���������� ������
	#define     TYPE 		6  //������� ���� ���������� � ������
	#define		INF_I		7  //������� ������� ����� ����������
//���������
	#define   	TILE_LEN 		6  	//������ �������� ������ ������
	#define 	CRC_TITLE_LEN 	2 	//����� CRC ���� ���������
	#define 	CRC_TITLE_INF 	2 	//����� CRC ���� ����������

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
			 double 		Speed	(void)const{return speed;}; //���������� ��������
			 unsigned int 	Road_1	(void)const{return road_1;}; //���������� ���� ����� 1
			 CD_Time        Time_1	(void)const{return *time_1;}; //����� ���������
			 unsigned int 	Road_2	(void)const{return road_2;}; //���������� ���� ����� 2
			 CD_Time        Time_2	(void)const{return *time_2;}; //����� ���������
			 Info			St_Info	(String & str);  //���������� � ���������
		private:
			 double speed;  //���������� �������� ���������� 0,1 ��/�
			 unsigned int road_1; //���������� ���� ����� 1 ���������� 1 ��
			 unsigned int road_2; //���������� ���� ����� 2 ���������� 1 ��
             boost::shared_ptr<CD_Time> time_1; //����� ��������� 1 ���� -���� �� ���� 2 ���� ���� �� ���� 3 ���� ������
             boost::shared_ptr<CD_Time> time_2; //����� ��������� 1 ���� -���� �� ���� 2 ���� ���� �� ���� 3 ���� ������
			 BYTE inform; 	/*��������� ���� ����� 	0- ������ ������� 1
													1- ������ ������� 2
													2- �������� ������ 350 ��/�
													3- �������� ������ 10 ��/�
													4- ������� ����������
													enum info
													*/
	};
	class Sensor
	{
		public:
					Sensor(wchar_t *_COM,BYTE _addr,bool init=true); //����������� � �������� ������������ �����
					Sensor(COMPort * _port,BYTE _addr);  //����������� � �������������� ������ �����
					~Sensor();
			ErrCode	Init			(BYTE _addr);             //������������� ����������
			ErrCode Write_ADDR		(BYTE _addr);             //������ ������ ������ ����������
			ErrCode Read_Diametr	(unsigned short &Diametr);//���������� �������� � ���������� ���������
			ErrCode	Write_Diametr	(unsigned short Diametr);//���������� 1 ��
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

static		String  Get_Err			(ErrCode err);  //���������� ��������� �������� ������
		private:
			ErrCode Compile_command	(       //���������� ������� ������������ �������
									BYTE _type,   //��� ������ �������
									BYTE data_len,//������ ������ ������������ ������ � �������
									BYTE *s_data,      //������������ ������
									size_t s_data_len, //������ ������������ ������
									BYTE r_type,       //��� ������ ������
									BYTE *r_data,      //������� ��� ��������� ������
									size_t &r_data_len //������ ������
									);
			void  	Get_Com_Title	(size_t len, BYTE *com); //��������� ��������� ������
			bool 	Check_CRC       (const BYTE *);  //�������� ����������� ������ �� crc
			void	Get_Title_CRC 	(const BYTE *com, BYTE *title_crc, size_t crc_len); //������ crc ��������� ������
			void	Get_CRC_IFO   	(const BYTE *com, BYTE *info_crc, size_t crc_len);  //������ crc ����������� ������

			ErrCode SendMessage		(const BYTE*);  //�������� ������� �������, �������� ���������� �� �������

			COMPort *port;      //������ ����� ��� ����������
	const 	wchar_t *COM;       //�������� �����
			BYTE 	addr;       //������ ����������
			bool 	port_owner; //����� ������� �������� (����������� ��� ����������)
	};
};

#endif
