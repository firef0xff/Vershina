#pragma once
#ifndef TyreProtH
#define TyreProtH
#include <string>
#include "src/cpu/data/gr7.h"
#include "../support_functions/date_time.h"

class Tyre
{
public:
   typedef std::string String;
   // переменные протокола
   int ProtNo; // номер протокола
   String Size; // размер шины
   String Model; // модель шины
   String TestProcedure; // методика испытаний
   String StandName; // наименование стенда
   String Manufacturer; // изготовитель шины
   float DrumDiameter; // диаметр барабана
   String TestCustomer; // заказчик
   dt::DateTime ManufactDate; // дата изготовления
   dt::DateTime Start; // дата начала испытания
   dt::DateTime Stop; // дата окончания испытания
   int FormNo; // номер формы протокола
   int OrderNo; // номер заказа
   int PerfSpecNo; // номер ТЗ
   int SerialNo; // порядковый номер шины
   String LoadIndex; // Индекс нагрузки шины
   float MaxLoad; // максимальная нагрузка
   String SpeedInd; // Индекс скорости
   float MaxSpeed; // Максимальная скорость
   float StaticR; // статический радиус
   float OuterD; // наружный диаметр
   String WheelRim; // обозначение обода
   float MaxLoadPress; // давление при максимально нагрузке
   int ProfileWide; // ширина профиля
   int Type; // тип покрышки, 0-радиальная, 1-диагональная
   float CurrentLoad; // нагрузка
   float InitPressure; // начальное давление
   float CurrentSpeed; // скорость
   int TestMode; // режим испытаний, 0-по времени, 1-по пути
   int TotalTime; // общее время испытаний, мсек
   float TotalS; // сумарный путь испытаний
   int StepsNo; // количество шагов программы
   int PollsNo; // количество опросов

   int rT[cpu::data::GR7::ITEMS_COUNT]; // массивы с результатами испытаний
   float rV[cpu::data::GR7::ITEMS_COUNT];
   float rS[cpu::data::GR7::ITEMS_COUNT];
   float rL[cpu::data::GR7::ITEMS_COUNT];
   float rR[cpu::data::GR7::ITEMS_COUNT];
   float rTemp[cpu::data::GR7::ITEMS_COUNT];

   Tyre();

   void ImportTemplate ( Tyre const& );

   void WriteToFile(String fname);
   // запись полей Tyre в файл с именем fname
   void ReadFromFile(String fname);
   // чтение полей Tyre из файла с именем fname
   void PrintProtToFile(String fname, String side);
   // печать протокола испытаний в файл fname
   void Clear(void);
   // очистка массивов (они варварским способом не чистятся, просто копируют значения из дргого массива)

   std::string CustomDate(void) const;
   void CustomDate( std::string const& dt);

private:
   void Init();
   Tyre(Tyre const& op2) = delete;
   Tyre& operator = (Tyre const& op2) = delete;

};
#endif
