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
   GR1(const wchar_t* group_name, const wchar_t *addresses[] );
   void Write() override;
   bool Read() override;
   void Clear();

   //поз1
   bool &Blowout          = mBoolData[0]; // M02.1 Разрыв шины 1
   bool &GuardRail        = mBoolData[1]; // I125.3 Ограждение 1
   bool &PumpOn           = mBoolData[2]; // M50.1 Насос 1
   bool &CarriageTo       = mBoolData[3]; // M50.3 Подвод каретки поз 1
   bool &CarriageFrom     = mBoolData[4]; // M50.4 Отвод каретки поз 1
   bool &CarriageOff      = mBoolData[5]; // M02.2 каретка позиция 1 в исходном
   bool &ControlLateral   = mBoolData[6]; // M02.3 вкл/выкл контроля бокового разрыва поз А
   bool &DestroyLateral   = mBoolData[7]; // M34.0 рарушение бововой 1
   bool &DestroyRunning   = mBoolData[8]; // M34.1 разрушение беговой 1
   bool &AutoMode         = mBoolData[9]; // DB10,X2.0 Режим Автомат 1
   bool &ManualMode       = mBoolData[10]; // DB10,X2.1 Режим Ручной 1
   bool &Start            = mBoolData[11]; // DB10,X2.2 Старт поз 1
   bool &Stop             = mBoolData[12]; // DB10,X2.3 Стоп поз 1
   bool &Reset            = mBoolData[13]; // DB10,X2.4 Сброс поз 1                    НА !!!!!!!!!!!!!!!!!!!!!!
   bool &KeepLoad         = mBoolData[14]; // DB10,X3.0 Удержание нагрузки 1
   bool &ResetData        = mBoolData[15]; // M0.7 сброс результатов испытаний 1
   bool &OverLoad         = mBoolData[16]; // DB10,X38.5 A Превышение нагрузки на шаге на стороне 1

   int &fakt_time        = mIntData[0]; // DB20,DINT26 факт. время 1
   int &step_write       = mIntData[1]; // DB20,DINT38 номер текущего шага опроса 1
   int &step_change      = mIntData[2]; // DB20,DINT42 номер текущего рабочего шага 1
   int &next_step_time    = mIntData[3]; // DB20,DINT148 номер следующего шага опроса по времени 1
   int &next_step_change  = mIntData[4]; // DB20,DINT180 номер следующего рабочего шага 1

   float &ReadLoading    = mFloatData[0]; // DB10,REAL26 Нагрузка 1  считывание
   float &min_load       = mFloatData[1]; // DB10,REAL142 мин. нагрузка 1 в цикле
   float &max_load       = mFloatData[2]; // DB10,REAL146 макс нагрузка 1 в цикле
   float &min_temp       = mFloatData[3]; // DB10,REAL158 Минимальная температура в Поз А
   float &max_temp       = mFloatData[4]; // DB10,REAL162 Максимальная температура в Поз А

   enum
   {
      BOOL_COUNT  = 17,    // количество булевых переменных в группе 1
      INT_COUNT   = 5,    // количество целых переменных в группе 1
      FLOAT_COUNT = 5,    // количество вещественных переменных в группе 1
   };

private:
   friend class cpu::CpuMemory;

   GR1(const GR1&) = delete;
   void operator = (const GR1&) = delete;


   bool  mBoolData[BOOL_COUNT];
   int   mIntData[INT_COUNT];
   float mFloatData[FLOAT_COUNT];

   unsigned long long mGroupID = 0;
};

extern wchar_t const* Gr1Pos1Adresses[ GR1::BOOL_COUNT + GR1::INT_COUNT + GR1::FLOAT_COUNT];
extern wchar_t const* Gr1Pos1Name;

extern wchar_t const* Gr1Pos2Adresses[ GR1::BOOL_COUNT + GR1::INT_COUNT + GR1::FLOAT_COUNT];
extern wchar_t const* Gr1Pos2Name;
} // namespace data

} // namespace cpu

#endif
