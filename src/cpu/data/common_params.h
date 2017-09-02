#pragma once
#ifndef common_paramsH
#define common_paramsH
#include "src/cpu/data_block_base.h"

namespace cpu
{
   class CpuMemory;

namespace data
{

class CommonParams : public InOut
{
public:
   void Write() override;
   bool Read() override;
   void Clear();

   //common gr1
   bool &OilLvl         = mBoolData[0]; // M34.4 уровень масла
   bool &OilFilter      = mBoolData[1]; // M34.5 засор фильтра
   bool &ElDriveDrum    = mBoolData[2]; // M34.6 нет готовности электропривода
   bool &DrumOn         = mBoolData[3]; // DB10,X2.5 Включить барабан
   bool &DrumOff        = mBoolData[4]; // DB10,X2.6 Выключить барабан

   int &fakt_time       = mIntData[0]; // DB20,DINT14 общее время             НА !!!!!!!!!!!!!!!!!!!

   float &OilTemp       = mFloatData[0]; // DB20,x100 температура масла
   float &max_speed     = mFloatData[1]; // DB10,REAL138 максимальная скорость в цикле
   float &min_speed     = mFloatData[2]; // DB10,REAL174 минимальная скорость в цикле

   //common gr2
   float &fakt_speed    = mFloatData[3]; // DB20,REAL2 фактическая скорость
   float &set_speed     = mFloatData[4]; // DB20,REAL6 заданная скорость
   float &fakt_distance = mFloatData[5]; // DB20,REAL10 общий пробег          НА !!!!!!!!!!!!!!!!!!!

   //common gr3
   float &DrumSpeed     = mFloatData[6]; // DB10,REAL22 Скорость барабана

private:
   friend class cpu::CpuMemory;

   CommonParams();
   CommonParams(const CommonParams&) = delete;
   void operator = (const CommonParams&) = delete;

   enum
   {
      BOOL_COUNT  = 5,    // количество булевых переменных
      INT_COUNT   = 1,    // количество целых переменных
      FLOAT_COUNT = 7,    // количество вещественных переменных в группе 1
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
      //int
      L"S7:[S7 connection_4]DB20,DINT14",
      //float
      L"S7:[S7 connection_4]DB20,REAL100",
      L"S7:[S7 connection_4]DB10,REAL138",
      L"S7:[S7 connection_4]DB10,REAL174",
      L"S7:[S7 connection_4]DB20,REAL2",
      L"S7:[S7 connection_4]DB20,REAL6",
      L"S7:[S7 connection_4]DB20,REAL10",
      L"S7:[S7 connection_4]DB10,REAL22",
   };
};

}//namespace data
}//namespace cpu

#endif // COMMONPARAMS_H
