// ---------------------------------------------------------------------------
#include "TyreProt.h"
//#include "src/Common.h"
#include "src/def.h"
#include <stdio.h>
#include "../log/log.h"
#include "../support_functions/date_time.h"
#include "../support_functions/serialize.h"

Tyre::Tyre(const std::string &side):
   mSide(side)
{
   ProtNo = 0; // номер протокола
   Size = String(10, ' '); // размер шины
   Model = String(10, ' '); // модель шины
   TestProcedure = String(10, ' '); // методика испытаний
   StandName = STAND_NO; // наименование стенда
   Manufacturer = String(10, ' '); // изготовитель шины
   DrumDiameter = 1700; // диаметр барабана, мм
   TestCustomer = String(10, ' '); // заказчик
   ManufactDate = dt::Clock::now(); // дата изготовления
   FormNo = 0; // номер формы протокола
   OrderNo = 0; // номер заказа
   PerfSpecNo = 0; // номер ТЗ
   SerialNo = 0; // порядковый номер шины
   LoadIndex = String(10, ' '); // Индекс нагрузки шины
   MaxLoad = 0.0; // максимальная нагрузка
   SpeedInd = String(10, ' '); // Индекс скорости
   MaxSpeed = 0.0; // Максимальная скорость
   StaticR = 0.0; // статический радиус
   OuterD = 0.0; // наружный диаметр
   WheelRim = String(10, ' '); // обозначение обода
   MaxLoadPress = 0.0; // давление при максимально нагрузке
   ProfileWide = 0; // ширина профиля
   Type = 1; // тип покрышки, 0-радиальная, 1-диагональная
   CurrentLoad = 0.0; // нагрузка
   InitPressure = 0.0; // начальное давление
   CurrentSpeed = 0.0; // скорость
   TestMode = -1; // режим испытаний, 0-по времени, 1-по пути
   TotalTime = 0; // общее время испытаний, мсек
   TotalS = 0.0; // сумарный путь испытаний
   StepsNo = 0; // количество шагов программы
   PollsNo = 0; // количество опросов
   Clear();
}
void Tyre::Init()
{
   ProtNo = 0; // номер протокола
   Size = String(10, ' '); // размер шины
   Model = String(10, ' '); // модель шины
   TestProcedure = String(10, ' '); // методика испытаний
   StandName = STAND_NO; // наименование стенда
   Manufacturer = String(10, ' '); // изготовитель шины
   DrumDiameter = 1700; // диаметр барабана, мм
   TestCustomer = String(10, ' '); // заказчик
   ManufactDate = dt::Clock::now(); // дата изготовления
   FormNo = 0; // номер формы протокола
   OrderNo = 0; // номер заказа
   PerfSpecNo = 0; // номер ТЗ
   SerialNo = 0; // порядковый номер шины
   LoadIndex = String(10, ' '); // Индекс нагрузки шины
   MaxLoad = 0.0; // максимальная нагрузка
   SpeedInd = String(10, ' '); // Индекс скорости
   MaxSpeed = 0.0; // Максимальная скорость
   StaticR = 0.0; // статический радиус
   OuterD = 0.0; // наружный диаметр
   WheelRim = String(10, ' '); // обозначение обода
   MaxLoadPress = 0.0; // давление при максимально нагрузке
   ProfileWide = 0; // ширина профиля
   Type = 1; // тип покрышки, 0-радиальная, 1-диагональная
   CurrentLoad = 0.0; // нагрузка
   InitPressure = 0.0; // начальное давление
   CurrentSpeed = 0.0; // скорость
   TestMode = -1; // режим испытаний, 0-по времени, 1-по пути
   TotalTime = 0; // общее время испытаний, мсек
   TotalS = 0.0; // сумарный путь испытаний
   StepsNo = 0; // количество шагов программы
   PollsNo = 0; // количество опросов
   Clear();
}

void Tyre::ImportTemplate ( Tyre const& r)
{
   //Init();
   ProtNo = r.ProtNo;
   Size = r.Size;
   Model = r.Model;
   TestProcedure = r.TestProcedure;
   StandName = r.StandName;
   Manufacturer = r.Manufacturer;
   DrumDiameter = r.DrumDiameter;
   TestCustomer = r.TestCustomer;
   ManufactDate = r.ManufactDate;
   SerialNo = r.SerialNo;
   PerfSpecNo = r.PerfSpecNo;
   OrderNo = r.OrderNo;
   FormNo = r.FormNo;
   LoadIndex = r.LoadIndex;
   MaxLoad = r.MaxLoad;
   SpeedInd = r.SpeedInd;
   MaxSpeed = r.MaxSpeed;
   StaticR = r.StaticR;
   OuterD = r.OuterD;
   WheelRim = r.WheelRim;
   MaxLoadPress = r.MaxLoadPress;
   ProfileWide = r.ProfileWide;
   Type = r.Type;
   // CurrentLoad = r.CurrentLoad;
   // InitPressure = r.InitPressure;
   // CurrentSpeed = r.CurrentSpeed;
   TestMode = r.TestMode;
}

void Tyre::Clear(void)
{
   for (int i = 0; i < 250; i++)
   {
      rT[i] = 0; // массивы с результатами испытаний
      rV[i] = 0;
      rS[i] = 0;
      rL[i] = 0;
      rR[i] = 0;
      rTemp[i] = 0;
   }
}

void Tyre::WriteToFile(String fname) // запись полей Tyre в файл с именем fname
{
   FILE *fparam = fopen(fname.c_str(), "wb");
   if ( fparam == nullptr )
   {
      logger::LogPrint( "Can't open file \"" + fname + "\" for writing!", logger::lcRED );
      return;
   }
   serialize::Write(fparam, Size);
   serialize::Write(fparam, Model);
   serialize::Write(fparam, TestProcedure);
   serialize::Write(fparam, StandName);
   serialize::Write(fparam, Manufacturer);
   serialize::Write(fparam, TestCustomer);
   serialize::Write(fparam, LoadIndex);
   serialize::Write(fparam, SpeedInd);
   serialize::Write(fparam, WheelRim);
   serialize::Write(fparam, ProtNo);
   serialize::Write(fparam, FormNo);
   serialize::Write(fparam, OrderNo);
   serialize::Write(fparam, PerfSpecNo);
   serialize::Write(fparam, SerialNo);
   serialize::Write(fparam, ProfileWide);
   serialize::Write(fparam, Type);
   serialize::Write(fparam, TestMode);
   serialize::Write(fparam, TotalTime);
   serialize::Write(fparam, StepsNo);
   serialize::Write(fparam, PollsNo);
   serialize::Write(fparam, DrumDiameter);
   serialize::Write(fparam, MaxLoad);
   serialize::Write(fparam, MaxSpeed);
   serialize::Write(fparam, StaticR);
   serialize::Write(fparam, OuterD);
   serialize::Write(fparam, MaxLoadPress);
   serialize::Write(fparam, CurrentLoad);
   serialize::Write(fparam, InitPressure);
   serialize::Write(fparam, CurrentSpeed);
   serialize::Write(fparam, TotalS);
   fclose(fparam);
}

void Tyre::ReadFromFile(String fname) // чтение полей Tyre из файла с именем fname
{
   FILE *fparam = fopen(fname.c_str(), "rb");
   if ( fparam == nullptr)
   {
      logger::LogPrint( "Can't open file \"" + fname + "\" for writing!", logger::lcRED );
      return;
   }
   serialize::Read( fparam, Size );
   serialize::Read( fparam, Model );
   serialize::Read( fparam, TestProcedure );
   serialize::Read( fparam, StandName );
   serialize::Read( fparam, Manufacturer );
   serialize::Read( fparam, TestCustomer );
   serialize::Read( fparam, LoadIndex );
   serialize::Read( fparam, SpeedInd );
   serialize::Read( fparam, WheelRim );


   serialize::Read( fparam, ProtNo );
   serialize::Read( fparam, FormNo );
   serialize::Read( fparam, OrderNo );
   serialize::Read( fparam, PerfSpecNo );
   serialize::Read( fparam, SerialNo );
   serialize::Read( fparam, ProfileWide );
   serialize::Read( fparam, Type );
   serialize::Read( fparam, TestMode );
   serialize::Read( fparam, TotalTime );
   serialize::Read( fparam, StepsNo );
   serialize::Read( fparam, PollsNo );
   serialize::Read( fparam, DrumDiameter );
   serialize::Read( fparam, MaxLoad );
   serialize::Read( fparam, MaxSpeed );
   serialize::Read( fparam, StaticR );
   serialize::Read( fparam, OuterD );
   serialize::Read( fparam, MaxLoadPress );
   serialize::Read( fparam, CurrentLoad );
   serialize::Read( fparam, InitPressure );
   serialize::Read( fparam, CurrentSpeed );
   serialize::Read( fparam, TotalS );
   fclose(fparam);
}

void Tyre::PrintProtToFile(String fname) // печать протокола испытаний в файл fname
{
   FILE *fprint = fopen(fname.c_str(), "wt");
   if (fprint == nullptr)
   {
      logger::LogPrint( "Can't open file \"" + fname + "\" for printing!", logger::lcRED );
      return;
   }
   fprintf(fprint, "          ПРОТОКОЛ ИСПЫТАНИЙ № ______" /* %d */ " НА СТЕНДЕ %s\n"/* ,ProtNo */ , (StandName + mSide).c_str());
   fprintf(fprint, "       Изготовитель: %10s     Заказчик: %s  Заказ №: %5d\n",Manufacturer.c_str(), TestCustomer.c_str(),OrderNo);
   fprintf(fprint, "             Размер: %10s            Модель: %10s     Маркировка: %s\n", Size.c_str(), Model.c_str(), "_____");
   fprintf(fprint, "  Дата изготовления: %10s      Порядковый №: %10d        Форма №: %d\n",CustomDate().c_str(), SerialNo,FormNo);
   fprintf(fprint, "Диаметр барабана,мм: %10.0f          Методика: %10s\n\n", DrumDiameter, TestProcedure.c_str());
   if (Type == 0)
      fprintf(fprint,"               ХАРАКТЕРИСТИКИ ИСПЫТЫВАЕМОЙ ШИНЫ\n" /* РАДИАЛЬНОЙ ШИНЫ\n" */);
   else
      fprintf(fprint,"               ХАРАКТЕРИСТИКИ ИСПЫТЫВАЕМОЙ ШИНЫ\n" /* ДИАГОНАЛЬНОЙ ШИНЫ\n" */);
   fprintf(fprint,"   Индекс нагрузки: %10s    Наружный диаметр, мм: %10.2f \n", LoadIndex.c_str(), OuterD);
   fprintf(fprint,"Категория скорости: %10s      Ширина профиля, мм: %10d \n", SpeedInd.c_str(), ProfileWide);
   fprintf(fprint,"     Давление, кПа: %10.2f                    Обод: %10s\n\n",InitPressure, WheelRim.c_str() );
   fprintf(fprint, "                            РЕЗУЛЬТАТЫ ИСПЫТАНИЙ:\n");
   if (TestMode == 0)
      fprintf(fprint, "      Режим обкатки: по времени\n");
   else
      fprintf(fprint, "      Режим обкатки: по пути\n");
   fprintf(fprint, "            Общее время испытаний: %10s\n",dt::mSecToHMSStr(TotalTime).c_str());
   fprintf(fprint, "            Общий путь: %8f км\n", TotalS);
   fprintf(fprint, "            Дата начала испытания: %s\n",dt::ToString( Start ).c_str() );
   fprintf(fprint, "            Дата окончания испытания: %s\n",dt::ToString( Stop ).c_str() );

   fprintf(fprint,"+-----+---------+--------+--------+--------+--------+-----------+\n");
   fprintf(fprint,"|Опрос|  время  |скорость|путь, км|нагрузка| радиус |Температура|\n");
   fprintf(fprint,"|     |  чч:мм  | км/час |        |  кН    |   мм   |    С      |\n");
   fprintf(fprint,"+-----+---------+--------+--------+--------+--------+-----------+\n");
   for (int i = 0; i < PollsNo; i++)
   {
      if (rT[i] != 0 && rV[i] != 0 && rS[i] != 0 && rL[i] != 0 && rR[i]
         != 0 && rTemp[i] != 0)
      { // это не даст печататься пустым строкам данных (пожелание заказчика)
         fprintf(fprint,"| %03d |%7s  | %6.2f | %6.0f | %6.2f | %5.2f |    %5.1f  |\n",
            i + 1, dt::mSecToHMSStr( rT[i] ).c_str(), rV[i], rS[i], rL[i],
            rR[i], rTemp[i]);
      }
   }
   fprintf(fprint, "+-----+---------+--------+--------+--------+--------+-----------+\n");
   fclose(fprint);
}

std::string Tyre::CustomDate(void) const
{
   return dt::ToWeekYYYY(ManufactDate);
}

void Tyre::CustomDate( std::string const& dt)
{
   ManufactDate = dt::FromWeekYYYY( dt );
   return;
}
