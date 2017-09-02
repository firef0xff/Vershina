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
   GR2(const wchar_t* group_name, const wchar_t *addresses[] );

   void Write() override;
   bool Read() override;
   void Clear();

   //поз1
   int &next_set_time        = mIntData[0]; // DB20,DINT188

   float &fakt_distance     = mFloatData[0]; // DB20,REAL18 факт. пробег 1
   float &fakt_loading      = mFloatData[1]; // DB20,REAL22 факт. нагрузка 1
   float &fakt_radius       = mFloatData[2]; // DB20,REAL30 факт. радиус 1
   float &fakt_temper       = mFloatData[3]; // DB20,REAL34 факт. температура 1
   float &set_speed         = mFloatData[4]; // DB20,REAL46 заданная скорость 1 на текущем шаге
   float &set_loading       = mFloatData[5]; // DB20,REAL50 заданная нагрузка 1 на текущем шаге
   float &next_step_distance = mFloatData[6]; // DB20,REAL156 номер следующего шага опроса по пробегу 1
   float &next_speed         = mFloatData[7]; // DB20,REAL164 скорость на следующем шаге1
   float &next_loading       = mFloatData[8]; // DB20,REAL172 нагрузка на следующем шаге1
   float &next_set_distance  = mFloatData[9]; // DB20,REAL196

   enum
   {
      INT_COUNT   = 1,
      FLOAT_COUNT = 10
   };

private:
   friend class cpu::CpuMemory;

   GR2(const GR2&) = delete;
   void operator = (const GR2&) = delete;


   int   mIntData[INT_COUNT];
   float mFloatData[FLOAT_COUNT];

   unsigned long long mGroupID = 0;

};

extern wchar_t const* Gr2Pos1Adresses[ GR2::INT_COUNT + GR2::FLOAT_COUNT];
extern wchar_t const* Gr2Pos1Name;

extern wchar_t const* Gr2Pos2Adresses[ GR2::INT_COUNT + GR2::FLOAT_COUNT];
extern wchar_t const* Gr2Pos2Name;
} // namespace data

} // namespace cpu

#endif
