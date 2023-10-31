//---------------------------------------------------------------------------

#ifndef TyreProtH
#define TyreProtH
#include <SysUtils.hpp>
#include <Printers.hpp>
#include "def.h"
//---------------------------------------------------------------------------
class Tyre
{ public:

// переменные протокола
    int       ProtNo;            // номер протокола
    String    Size;              // размер шины
    String    Model;             // модель шины
    String    TestProcedure;     // методика испытаний
    String    StandName;         // наименование стенда
    String    Manufacturer;      // изготовитель шины
    float     DrumDiameter;      // диаметр барабана
    String    TestCustomer;      // заказчик
    TDateTime ManufactDate;      // дата изготовления
    TDateTime Start;             // дата начала испытания
    TDateTime Stop;              // дата окончания испытания
    int       FormNo;            // номер формы протокола
    int       OrderNo;           // номер заказа
    int       PerfSpecNo;        // номер ТЗ
    int       SerialNo;          // порядковый номер шины
    String    LoadIndex;         // Индекс нагрузки шины
    float     MaxLoad;           // максимальная нагрузка
    String    SpeedInd;          // Индекс скорости
    float     MaxSpeed;          // Максимальная скорость
    float     StaticR;           // статический радиус
    float     OuterD;            // наружный диаметр
    String    WheelRim;          // обозначение обода
    float     MaxLoadPress;      // давление при максимально нагрузке
    int       ProfileWide;       // ширина профиля
    int       Type;              // тип покрышки, 0-радиальная, 1-диагональная
    float     CurrentLoad;       // нагрузка
    float     InitPressure;      // начальное давление
    float     CurrentSpeed;      // скорость
    int       TestMode;          // режим испытаний, 0-по времени, 1-по пути
    int       TotalTime;         // общее время испытаний, мсек
    float     TotalS;            // сумарный путь испытаний
    int       StepsNo;           // количество шагов программы
	int       PollsNo;           // количество опросов
    int       rT[250]; // массивы с результатами испытаний
    float     rV[250];
    float     rS[250];
    float     rL[250];
    float     rR[250];
	float     rTemp[250];
    float     Mass;               //Масса

              __fastcall Tyre(void);                       // конструктор
              __fastcall ~Tyre(void);                      // деструктор
    Tyre      __fastcall operator=(Tyre op2);              // переопределение присваивания
    void      __fastcall WriteTyreToFile(String fname);    // запись полей Tyre в файл с именем fname
    void      __fastcall ReadTyreFmFile(String fname);     // чтение полей Tyre из файла с именем fname
	void      __fastcall PrintProtToFile(String fname,String side);    // печать протокола испытаний в файл fname
	void      __fastcall PrintProtocol(TPrinter *pprt,String side);    // печать протокола на принтер pprt
	void	Clear	(void);//очистка массивов (они варварским способом не чистятся, просто копируют значения из дргого массива)

	AnsiString CustomDate (void)
	{
		int week_num;
		Word year, month, day;
		ManufactDate.DecodeDate(&year,&month,&day);	// раскладываем нашу дату на составляющие
		TDateTime _1_jan(year,1,1);		// 1-е января того года, которому соответствует дата
		int _1_jan_day_of_week = (_1_jan.DayOfWeek()+5)%7; // день недели 1-го января
		week_num = (int)(ManufactDate-TDateTime(year,1,1)+_1_jan_day_of_week)/7; // искомый номер недели(с 0)
		return AnsiString(week_num)+":"+AnsiString(year).SubString(3,2);
	}
	void  	CustomDate  (AnsiString dt)
	{
		int delim = dt.Pos(".");
		int week=dt.SubString(1,delim-1).ToIntDef(0);
		short year=dt.SubString(delim+1,dt.Length()-delim).ToIntDef(0);
	   	ManufactDate=TDateTime(year,1,1)+7*(week);
		return;
	}
  private:
};
#endif
