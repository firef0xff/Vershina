#ifndef path_programmH
#define path_programmH
#pragma once
#include <string>
#include "src/cpu/cpu_memory.h"

class PathProgramm
{
public:
   enum
   {
      POLLS_COUNT = cpu::data::GR4::POLLS_COUNT,
      STEPS_COUNT = cpu::data::GR4::STEPS_COUNT,
      ARRAYS_COUNT = cpu::data::GR4::ARRAYS_COUNT
   };
   PathProgramm();

   void Load();
   void Save();

   void Clear();
   void ToCpu(cpu::data::GR4& gr4, cpu::data::GR6& gr6 );
//private:
   // программа по пути
   std::string SProgFName = ""; // имя файла для сохранения программы по пути
   std::string SProgName = ""; // имя программы испытаний по пути
   float STyrePressure = 0.0; // давление в шине
   int total_step_S = 0; // суммарное кол-во шагов программы по пути
   float total_S = 0.0; // суммарная продолжительность программы по пути, км
   int num_S_poll = 0; // количество опросов по пути
   float poll_step_S[POLLS_COUNT] = {0}; // массив опросов по пути
   float prog_step_S[STEPS_COUNT] = {0}; // массив шагов по пути
   float Ssettings[ARRAYS_COUNT][STEPS_COUNT] = {{0.0}};// массив нагрузок (1-й столбец) и скоростей (2-й столбец)
};

#endif // PATH_PROGRAMM_H
