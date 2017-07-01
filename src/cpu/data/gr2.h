#pragma once
#ifndef gr2H
#define gr2H
#include "src/cpu/data_block_base.h"

namespace cpu
{
   class CpuMemory;

namespace data
{

/// таблица входных параметров тестирования кейса гидро распределителей
class GR2 : public InOut
{
public:
   void Write() override;
   bool Read() override;
   void Clear();


   //common
   float &fakt_speed    = mFloatData[0]; // DB20,REAL2 фактическая скорость
   float &set_speed     = mFloatData[1]; // DB20,REAL6 заданная скорость
   float &fakt_distance = mFloatData[2]; // DB20,REAL10 общий пробег

   //поз1
   int &next_set_time1        = mIntData[0]; // DB20,DINT188

   float &fakt_distance_1     = mFloatData[3]; // DB20,REAL18 факт. пробег 1
   float &fakt_loading_1      = mFloatData[4]; // DB20,REAL22 факт. нагрузка 1
   float &fakt_radius_1       = mFloatData[5]; // DB20,REAL30 факт. радиус 1
   float &fakt_temper_1       = mFloatData[6]; // DB20,REAL34 факт. температура 1
   float &set_speed_1         = mFloatData[7]; // DB20,REAL46 заданная скорость 1 на текущем шаге
   float &set_loading_1       = mFloatData[8]; // DB20,REAL50 заданная нагрузка 1 на текущем шаге
   float &next_step_distance1 = mFloatData[9]; // DB20,REAL156 номер следующего шага опроса по пробегу 1
   float &next_speed1         = mFloatData[10]; // DB20,REAL164 скорость на следующем шаге1
   float &next_loading1       = mFloatData[11]; // DB20,REAL172 нагрузка на следующем шаге1
   float &next_set_distance1  = mFloatData[12]; // DB20,REAL196

   //поз2
   int &next_set_time2        = mIntData[1]; // DB20,DINT192

   float &fakt_distance_2     = mFloatData[13]; // DB20,REAL58 факт. пробег 2
   float &fakt_loading_2      = mFloatData[14]; // DB20,REAL62 факт. нагрузка 2
   float &fakt_radius_2       = mFloatData[15]; // DB20,REAL70 факт. радиус 2
   float &fakt_temper_2       = mFloatData[16]; // DB20,REAL74 факт. температура 2
   float &set_speed_2         = mFloatData[17];  // DB20,REAL86 заданная скорость 2 на текущем шаге
   float &set_loading_2       = mFloatData[18]; // DB20,REAL90 заданная нагрузка 2 на текущем шаге
   float &next_step_distance2 = mFloatData[19]; // DB20,REAL160 номер следующего шага опроса по пробегу 2
   float &next_speed2         = mFloatData[20]; // DB20,REAL168 скорость на следующем шаге2
   float &next_loading2       = mFloatData[21]; // DB20,REAL176 нагрузка на следующем шаге2
   float &next_set_distance2  = mFloatData[22]; // DB20,REAL200

private:
   friend class cpu::CpuMemory;

   GR2();
   GR2(const GR2&) = delete;
   void operator = (const GR2&) = delete;

   enum
   {
      INT_COUNT   = 2,
      FLOAT_COUNT = 23
   };

   int   mIntData[INT_COUNT];
   float mFloatData[FLOAT_COUNT];

   unsigned long long mGroupID = 0;

   wchar_t const* mAdresses[INT_COUNT + FLOAT_COUNT] =
   {
      //int
      L"S7:[S7 connection_4]DB20,DINT188",
      L"S7:[S7 connection_4]DB20,DINT192",
      //float
      L"S7:[S7 connection_4]DB20,REAL2",
      L"S7:[S7 connection_4]DB20,REAL6",
      L"S7:[S7 connection_4]DB20,REAL10",
      L"S7:[S7 connection_4]DB20,REAL18",
      L"S7:[S7 connection_4]DB20,REAL22",
      L"S7:[S7 connection_4]DB20,REAL30",
      L"S7:[S7 connection_4]DB20,REAL34",
      L"S7:[S7 connection_4]DB20,REAL46",
      L"S7:[S7 connection_4]DB20,REAL50",
      L"S7:[S7 connection_4]DB20,REAL156",
      L"S7:[S7 connection_4]DB20,REAL164",
      L"S7:[S7 connection_4]DB20,REAL172",
      L"S7:[S7 connection_4]DB20,REAL196",
      L"S7:[S7 connection_4]DB20,REAL58",
      L"S7:[S7 connection_4]DB20,REAL62",
      L"S7:[S7 connection_4]DB20,REAL70",
      L"S7:[S7 connection_4]DB20,REAL74",
      L"S7:[S7 connection_4]DB20,REAL86",
      L"S7:[S7 connection_4]DB20,REAL90",
      L"S7:[S7 connection_4]DB20,REAL160",
      L"S7:[S7 connection_4]DB20,REAL168",
      L"S7:[S7 connection_4]DB20,REAL176",
      L"S7:[S7 connection_4]DB20,REAL200"
   };
};

} // namespace data

} // namespace cpu

#endif
