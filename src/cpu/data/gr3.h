#pragma once
#ifndef gr3H
#define gr3H
#include "src/cpu/data_block_base.h"

namespace cpu
{
   class CpuMemory;

namespace data
{

/// таблица входных параметров тестирования кейса гидро распределителей
class GR3 : public InOut
{
public:
   void Write() override;
   bool Read() override;
   void Clear();

   //common
   float &DrumSpeed        = mFloatData[0]; // DB10,REAL22 Скорость барабана

   //поз1
   int &T_end_cycle_1      = mIntData[0]; // DB10,DINT10 Конечное время цикла 1
   int &type_cycle_1       = mIntData[1];// DB10,INT4 Тип цикла 1
   int &StepsQty1          = mIntData[2]; // DB10,INT34 Количество шагов программы 1
   int &PollsQty1          = mIntData[3]; // DB10,INT36 Количество опросов 1

   float &S_end_cycle_1    = mFloatData[1]; // DB10,REAL18 Конечный пробег цикла 1
   float &Loading_1        = mFloatData[2]; // DB10,REAL26 Нагрузка 1
   float &Radius_1         = mFloatData[3]; // DB10,REAL30 Радиус 1
   float &CorrASetSpeed    = mFloatData[4]; // DB10,REAL74 Корекция А по заданию скорости
   float &CorrAMeasSpeed   = mFloatData[5];// DB10,REAL82 Корекция А по измерению скорости
   float &Temp1LowLimit    = mFloatData[6];// DB10,REAL90 Нижний предел датчика температуры 1
   float &Temp1UpLimit     = mFloatData[7];// DB10,REAL94 Верхний предел датчика температуры 1
   float &CorrAMeasLoad1   = mFloatData[8];// DB10,REAL98 Корекция А по измерению  нагрузки 1
   float &CorrBMeasLoad1   = mFloatData[9];// DB10,REAL102 Корекция Б по измерению нагрузки 1
   float &Rad1LowLimit     = mFloatData[10];// DB10,REAL122 Нижний предел измерений датчика радиуса 1
   float &Rad1UpLimit      = mFloatData[11];// DB10,REAL126 Верхний предел измерений датчика радиуса 1

   //поз2
   int &T_end_cycle_2      = mIntData[4]; // DB10,DINT46 Конечное время цикла 2
   int &type_cycle_2       = mIntData[5];// DB10,INT40 Тип цикла 2
   int &StepsQty2          = mIntData[6]; // DB10,INT70 Количество шагов программы 2
   int &PollsQty2          = mIntData[7]; // DB10,INT72 Количество опросов 2

   float &S_end_cycle_2    = mFloatData[12];// DB10,REAL54 Конечный пробег цикла 2
   float &Loading_2        = mFloatData[13]; // DB10,REAL62 Нагрузка 2
   float &Radius_2         = mFloatData[14]; // DB10,REAL66 Радиус 2
   float &CorrBSetSpeed    = mFloatData[15]; // DB10,REAL78 Корекция Б по заданию скорости
   float &CorrBMeasSpeed   = mFloatData[16];// DB10,REAL86 Корекция Б по измерению скорости
   float &Temp2LowLimit    = mFloatData[17];// DB10,REAL106 Нижний предел датчика температуры 2
   float &Temp2UpLimit     = mFloatData[18];// DB10,REAL110 Верхний предел датчика температуры 2
   float &CorrAMeasLoad2   = mFloatData[19];// DB10,REAL114 Корекция А по измерению  нагрузки 2
   float &CorrBMeasLoad2   = mFloatData[20];// DB10,REAL118 Корекция Б по измерению нагрузки 2
   float &Rad2LowLimit     = mFloatData[21];// DB10,REAL130 Нижний предел измерений датчика радиуса 2
   float &Rad2UpLimit      = mFloatData[22];// DB10,REAL134 Верхний предел измерений датчика радиуса 2

private:
   friend class cpu::CpuMemory;

   GR3();
   GR3(const GR3&) = delete;
   void operator = (const GR3&) = delete;

   enum
   {
      INT_COUNT   = 8,
      FLOAT_COUNT = 23
   };

   int   mIntData[INT_COUNT];
   float mFloatData[FLOAT_COUNT];

   unsigned long long mGroupID = 0;

   wchar_t const* mAdresses[INT_COUNT + FLOAT_COUNT] =
   {
      //int
      L"S7:[S7 connection_4]DB10,DINT10",
      L"S7:[S7 connection_4]DB10,INT4",
      L"S7:[S7 connection_4]DB10,INT34",
      L"S7:[S7 connection_4]DB10,INT36",
      L"S7:[S7 connection_4]DB10,DINT46",
      L"S7:[S7 connection_4]DB10,INT40",
      L"S7:[S7 connection_4]DB10,INT70",
      L"S7:[S7 connection_4]DB10,INT72",
      //float
      L"S7:[S7 connection_4]DB10,REAL22",
      L"S7:[S7 connection_4]DB10,REAL18",
      L"S7:[S7 connection_4]DB10,REAL26",
      L"S7:[S7 connection_4]DB10,REAL30",
      L"S7:[S7 connection_4]DB10,REAL74",
      L"S7:[S7 connection_4]DB10,REAL82",
      L"S7:[S7 connection_4]DB10,REAL90",
      L"S7:[S7 connection_4]DB10,REAL94",
      L"S7:[S7 connection_4]DB10,REAL98",
      L"S7:[S7 connection_4]DB10,REAL102",
      L"S7:[S7 connection_4]DB10,REAL122",
      L"S7:[S7 connection_4]DB10,REAL126",
      L"S7:[S7 connection_4]DB10,REAL54",
      L"S7:[S7 connection_4]DB10,REAL62",
      L"S7:[S7 connection_4]DB10,REAL66",
      L"S7:[S7 connection_4]DB10,REAL78",
      L"S7:[S7 connection_4]DB10,REAL86",
      L"S7:[S7 connection_4]DB10,REAL106",
      L"S7:[S7 connection_4]DB10,REAL110",
      L"S7:[S7 connection_4]DB10,REAL114",
      L"S7:[S7 connection_4]DB10,REAL118",
      L"S7:[S7 connection_4]DB10,REAL130",
      L"S7:[S7 connection_4]DB10,REAL134"
   };
};

} // namespace data

} // namespace cpu

#endif
