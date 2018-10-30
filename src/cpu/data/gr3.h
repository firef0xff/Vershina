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
   GR3(const wchar_t* group_name, const wchar_t *addresses[] );
   void Write() override;
   bool Read() override;
   void Clear();

   //поз1
   int &T_end_cycle      = mIntData[0]; // DB10,DINT10 Конечное время цикла 1
   int &type_cycle       = mIntData[1];// DB10,INT4 Тип цикла 1
   int &StepsQty          = mIntData[2]; // DB10,INT34 Количество шагов программы 1
   int &PollsQty          = mIntData[3]; // DB10,INT36 Количество опросов 1

   float &S_end_cycle    = mFloatData[0]; // DB10,REAL18 Конечный пробег цикла 1
   float &Loading        = mFloatData[1]; // DB10,REAL26 Нагрузка 1
   float &Radius         = mFloatData[2]; // DB10,REAL30 Радиус 1
   float &CorrSetSpeed    = mFloatData[3]; // DB10,REAL74 Корекция А по заданию скорости
   float &CorrMeasSpeed   = mFloatData[4];// DB10,REAL82 Корекция А по измерению скорости
   float &TempLowLimit    = mFloatData[5];// DB10,REAL90 Нижний предел датчика температуры 1
   float &TempUpLimit     = mFloatData[6];// DB10,REAL94 Верхний предел датчика температуры 1
   float &CommonOfset     = mFloatData[7];// DB10,REAL98 калибровка тензодатчика общее смещение
   float &CorrBMeasLoad   = mFloatData[8];// DB10,REAL102 Корекция Б по измерению нагрузки 1   НА!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   float &RadLowLimit     = mFloatData[9];// DB10,REAL122 Нижний предел измерений датчика радиуса 1
   float &RadUpLimit      = mFloatData[10];// DB10,REAL126 Верхний предел измерений датчика радиуса 1
   float &min_load       = mFloatData[11]; // DB10,REAL142 мин. нагрузка 1 в цикле
   float &max_load       = mFloatData[12]; // DB10,REAL146 макс нагрузка 1 в цикле
   float &min_temp       = mFloatData[13]; // DB10,REAL158 Минимальная температура в Поз А
   float &max_temp       = mFloatData[14]; // DB10,REAL162 Максимальная температура в Поз А

   enum
   {
      INT_COUNT   = 4,
      FLOAT_COUNT = 15
   };
private:
   friend class cpu::CpuMemory;

   GR3(const GR3&) = delete;
   void operator = (const GR3&) = delete;


   int   mIntData[INT_COUNT];
   float mFloatData[FLOAT_COUNT];

   unsigned long long mGroupID = 0;
};
extern wchar_t const* Gr3Pos1Adresses[ GR3::INT_COUNT + GR3::FLOAT_COUNT];
extern wchar_t const* Gr3Pos1Name;

extern wchar_t const* Gr3Pos2Adresses[ GR3::INT_COUNT + GR3::FLOAT_COUNT];
extern wchar_t const* Gr3Pos2Name;
} // namespace data

} // namespace cpu

#endif
