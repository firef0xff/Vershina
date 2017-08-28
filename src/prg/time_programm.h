#ifndef time_programmH
#define time_programmH
#pragma once
#include <string>
#include "src/cpu/cpu_memory.h"

class TimeProgramm
{
public:
   enum
   {
      POLLS_COUNT = cpu::data::GR5::POLLS_COUNT,
      STEPS_COUNT = cpu::data::GR6::ITEMS_COUNT,
      ARRAYS_COUNT = cpu::data::GR6::ARRAYS_COUNT
   };
   TimeProgramm();

   void Load();
   void Save() const;

   void Clear();

   void ToCpu( cpu::data::GR5& gr5, cpu::data::GR6& gr6 );
//private:
   // программа по времени
   std::string TProgFName = ""; // имя файла для сохранения программы по времени
   std::string TProgName = ""; // имя программы испытаний по времени
   float TTyrePressure = 0; // давление в шине
   int total_step_T = 0; // суммарное кол-во шагов программы по времени
   int total_T = 0; // суммарная продолжительность программы по времени, мсек
   int num_T_poll = 0; // количество опросов по времени
   int poll_step_T[POLLS_COUNT] = {0}; // массив опросов по времени
   int prog_step_T[STEPS_COUNT] = {0}; // массив шагов по времени
   float Tsettings[ARRAYS_COUNT][STEPS_COUNT] = {{0.0}}; // массив нагрузок (1-й столбец) и скоростей (2-й столбец)
};

#endif // TIMEPROGRAMM_H
