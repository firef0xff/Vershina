#pragma once
#ifndef gr1H
#define gr1H
#include "src/cpu/data_block_base.h"

namespace cpu
{
   class CpuMemory;

namespace data
{

/// таблица входных параметров тестирования кейса гидро распределителей
class GR1 : public InOut
{
public:
   void Write() override;
   bool Read() override;
   void Clear();

   //common
   bool &OilLvl         = mBoolData[0]; // M34.4 уровень масла
   bool &OilFilter      = mBoolData[1]; // M34.5 засор фильтра
   bool &ElDriveDrum    = mBoolData[2]; // M34.6 нет готовности электропривода
   bool &DrumOn         = mBoolData[3]; // DB10,X2.5 Включить барабан
   bool &DrumOff        = mBoolData[4]; // DB10,X2.6 Выключить барабан

   int &fakt_time       = mIntData[0]; // DB20,DINT14 общее время

   float &OilTemp       = mFloatData[0]; // DB20,x100 температура масла
   float &max_speed     = mFloatData[1]; // DB10,REAL138 максимальная скорость в цикле
   float &min_speed     = mFloatData[2]; // DB10,REAL174 минимальная скорость в цикле

   //поз1
   bool &Blowout1          = mBoolData[5]; // M02.1 Разрыв шины 1
   bool &GuardRail1        = mBoolData[6]; // I125.3 Ограждение 1
   bool &Pump1On           = mBoolData[7]; // M50.1 Насос 1
   bool &Carriage1To       = mBoolData[8]; // M50.3 Подвод каретки поз 1
   bool &Carriage1From     = mBoolData[9]; // M50.4 Отвод каретки поз 1
   bool &Carriage1Off      = mBoolData[10]; // M02.2 каретка позиция 1 в исходном
   bool &ControlLateralA   = mBoolData[11]; // M02.3 вкл/выкл контроля бокового разрыва поз А
   bool &DestroyLateral1   = mBoolData[12]; // M34.0 рарушение бововой 1
   bool &DestroyRunning1   = mBoolData[13]; // M34.1 разрушение беговой 1
   bool &AutoMode1         = mBoolData[14]; // DB10,X2.0 Режим Автомат 1
   bool &ManualMode1       = mBoolData[15]; // DB10,X2.1 Режим Ручной 1
   bool &Start1            = mBoolData[16]; // DB10,X2.2 Старт поз 1
   bool &Stop1             = mBoolData[17]; // DB10,X2.3 Стоп поз 1
   bool &Reset1            = mBoolData[18]; // DB10,X2.4 Сброс поз 1
   bool &KeepLoad1         = mBoolData[19]; // DB10,X3.0 Удержание нагрузки 1
   bool &ResetData1        = mBoolData[20]; // M0.7 сброс результатов испытаний 1
   bool &OverLoad1         = mBoolData[21]; // DB10,X38.5 A Превышение нагрузки на шаге на стороне 1

   int &fakt_time_1        = mIntData[1]; // DB20,DINT26 факт. время 1
   int &step_write_1       = mIntData[2]; // DB20,DINT38 номер текущего шага опроса 1
   int &step_change_1      = mIntData[3]; // DB20,DINT42 номер текущего рабочего шага 1
   int &next_step_time1    = mIntData[4]; // DB20,DINT148 номер следующего шага опроса по времени 1
   int &next_step_change1  = mIntData[5]; // DB20,DINT180 номер следующего рабочего шага 1

   float &ReadLoading_1    = mFloatData[3]; // DB10,REAL26 Нагрузка 1  считывание
   float &min_load_1       = mFloatData[4]; // DB10,REAL142 мин. нагрузка 1 в цикле
   float &max_load_1       = mFloatData[5]; // DB10,REAL146 макс нагрузка 1 в цикле
   float &min_temp_1       = mFloatData[6]; // DB10,REAL158 Минимальная температура в Поз А
   float &max_temp_1       = mFloatData[7]; // DB10,REAL162 Максимальная температура в Поз А

   //поз2
   bool &Blowout2          = mBoolData[22]; // M03.1 Разрыв шины 2
   bool &GuardRail2        = mBoolData[23]; // I125.7 Ограждение 2
   bool &Pump2On           = mBoolData[24]; // M50.2 Насос 2
   bool &Carriage2To       = mBoolData[25]; // M50.5 Подвод каретки поз 2
   bool &Carriage2From     = mBoolData[26]; // M50.6 Отвод каретки поз 2
   bool &Carriage2Off      = mBoolData[27]; // M03.2 каретка позиция 2 в исходном
   bool &ControlLateralB   = mBoolData[28]; // M03.3 вкл/выкл контроля бокового разрыва поз Б
   bool &DestroyLateral2   = mBoolData[29]; // M34.2 разрушение боковой 2
   bool &DestroyRunning2   = mBoolData[30]; // M34.3 разрушение беговой 2
   bool &AutoMode2         = mBoolData[31]; // DB10,X38.0 Режим атомат 2
   bool &ManualMode2       = mBoolData[32]; // DB10,X38.1 Режим ручной 2
   bool &Start2            = mBoolData[33]; // DB10,X38.2 Старт поз 2
   bool &Stop2             = mBoolData[34]; // DB10,X38.3 Стоп поз 2
   bool &Reset2            = mBoolData[35]; // DB10,X38.4 Сброс поз 2
   bool &KeepLoad2         = mBoolData[36]; // DB10,X39.0 Удержание нагрузки 2
   bool &ResetData2        = mBoolData[37]; // M1.7 сброс результатов испытаний 2
   bool &OverLoad2         = mBoolData[38]; // DB10,X38.6 B Превышение нагрузки на шаге на стороне 2

   int &fakt_time_2        = mIntData[6]; // DB20,DINT66 факт. время 2
   int &step_write_2       = mIntData[7]; // DB20,DINT78 номер текущего шага опроса 2
   int &step_change_2      = mIntData[8]; // DB20,DINT82 номер текущего рабочего шага 2
   int &next_step_time2    = mIntData[9]; // DB20,DINT152 номер следующего шага опроса по времени 1
   int &next_step_change2  = mIntData[10]; // DB20,DINT184 номер следующего рабочего шага

   float &ReadLoading_2    = mFloatData[8]; // DB10,REAL62 Нагрузка 2  считывание
   float &min_load_2       = mFloatData[9]; // DB10,REAL150 мин нагрузка 2 в цикле
   float &max_load_2       = mFloatData[10]; // DB10,REAL154 Корекция диапазона 10-20 по заданию нагрузки 1
   float &min_temp_2       = mFloatData[11]; // DB10,REAL166 Минимальная температура в Поз Б
   float &max_temp_2       = mFloatData[12]; // DB10,REAL170 Максимальная температура в Поз Б

private:
   friend class cpu::CpuMemory;

   GR1();
   GR1(const GR1&) = delete;
   void operator = (const GR1&) = delete;

   enum
   {
      BOOL_COUNT  = 39,    // количество булевых переменных в группе 1
      INT_COUNT   = 11,    // количество целых переменных в группе 1
      FLOAT_COUNT = 13,    // количество вещественных переменных в группе 1
   };

   bool  mBoolData[BOOL_COUNT];
   int   mIntData[INT_COUNT];
   float mFloatData[FLOAT_COUNT];

   unsigned long long mGroupID = 0;

   wchar_t const * mAdresses[BOOL_COUNT + INT_COUNT + FLOAT_COUNT] =
   {
      //bool
      L"S7:[S7 connection_4]MX34.4",
      L"S7:[S7 connection_4]MX34.5",
      L"S7:[S7 connection_4]MX34.6",
      L"S7:[S7 connection_4]DB10,X2.5",
      L"S7:[S7 connection_4]DB10,X2.6",
      L"S7:[S7 connection_4]MX2.1",
      L"S7:[S7 connection_4]IX125.3",
      L"S7:[S7 connection_4]MX50.1",
      L"S7:[S7 connection_4]MX50.3",
      L"S7:[S7 connection_4]MX50.4",
      L"S7:[S7 connection_4]MX2.2",
      L"S7:[S7 connection_4]MX2.3",
      L"S7:[S7 connection_4]MX34.0",
      L"S7:[S7 connection_4]MX34.1",
      L"S7:[S7 connection_4]DB10,X2.0",
      L"S7:[S7 connection_4]DB10,X2.1",
      L"S7:[S7 connection_4]DB10,X2.2",
      L"S7:[S7 connection_4]DB10,X2.3",
      L"S7:[S7 connection_4]DB10,X2.4",
      L"S7:[S7 connection_4]DB10,X3.0",
      L"S7:[S7 connection_4]M0.7",
      L"S7:[S7 connection_4]DB10,X38.5",
      L"S7:[S7 connection_4]MX3.1",
      L"S7:[S7 connection_4]IX125.7",
      L"S7:[S7 connection_4]MX50.2",
      L"S7:[S7 connection_4]MX50.5",
      L"S7:[S7 connection_4]MX50.6",
      L"S7:[S7 connection_4]MX3.2",
      L"S7:[S7 connection_4]MX3.3",
      L"S7:[S7 connection_4]MX34.2",
      L"S7:[S7 connection_4]MX34.3",
      L"S7:[S7 connection_4]DB10,X38.0",
      L"S7:[S7 connection_4]DB10,X38.1",
      L"S7:[S7 connection_4]DB10,X38.2",
      L"S7:[S7 connection_4]DB10,X38.3",
      L"S7:[S7 connection_4]DB10,X38.4",
      L"S7:[S7 connection_4]DB10,X39.0",
      L"S7:[S7 connection_4]M1.7",
      L"S7:[S7 connection_4]DB10,X38.6",
      //int
      L"S7:[S7 connection_4]DB20,DINT14",
      L"S7:[S7 connection_4]DB20,DINT26",
      L"S7:[S7 connection_4]DB20,DINT38",
      L"S7:[S7 connection_4]DB20,DINT42",
      L"S7:[S7 connection_4]DB20,DINT148",
      L"S7:[S7 connection_4]DB20,DINT180",
      L"S7:[S7 connection_4]DB20,DINT66",
      L"S7:[S7 connection_4]DB20,DINT78",
      L"S7:[S7 connection_4]DB20,DINT82",
      L"S7:[S7 connection_4]DB20,DINT152",
      L"S7:[S7 connection_4]DB20,DINT184",
      //float
      L"S7:[S7 connection_4]DB20,REAL100",
      L"S7:[S7 connection_4]DB10,REAL138",
      L"S7:[S7 connection_4]DB10,REAL174",
      L"S7:[S7 connection_4]DB10,REAL26",
      L"S7:[S7 connection_4]DB10,REAL142",
      L"S7:[S7 connection_4]DB10,REAL146",
      L"S7:[S7 connection_4]DB10,REAL158",
      L"S7:[S7 connection_4]DB10,REAL162",
      L"S7:[S7 connection_4]DB10,REAL62",
      L"S7:[S7 connection_4]DB10,REAL150",
      L"S7:[S7 connection_4]DB10,REAL154",
      L"S7:[S7 connection_4]DB10,REAL166",
      L"S7:[S7 connection_4]DB10,REAL170"
   };
};

} // namespace data

} // namespace cpu

#endif
