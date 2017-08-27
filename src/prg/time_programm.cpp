#include "time_programm.h"
#include "../support_functions/serialize.h"
#include "../support_functions/date_time.h"
#include "../log/log.h"

TimeProgramm::TimeProgramm()
{
   Clear();
}
void TimeProgramm::Clear()
{
   for (size_t i = 0; i < POLLS_COUNT; ++i) // массив опросов по времени
   {
      poll_step_T[i] = 0;
   }
   for (size_t i = 0; i < STEPS_COUNT; ++i)
   {
      prog_step_T[i] = 0; // массив шагов по времени
      for ( size_t j = 0; j < ARRAYS_COUNT; ++j )
         Tsettings[j][i] = 0; // массив нагрузок (1-й столбец)
   }
   TProgFName = ""; // имя файла для сохранения программы по времени
   TProgName = ""; // имя программы испытаний по времени
   TTyrePressure = 0.0; // давление в шине
   total_step_T = 0; // суммарное кол-во шагов программы по времени
   total_T = 0; // суммарная продолжительность программы по времени, мсек
   num_T_poll = 0; // количество опросов по времени
}

void TimeProgramm::Load()
{
   FILE *fparam = fopen(TProgFName.c_str(), "rb");
   if ( fparam == nullptr )
   {
      logger::LogPrint("Can't open file \"" + TProgFName + "\" for reading!", logger::lcRED );
      return;
   }
   serialize::Read( fparam, TProgName );
   serialize::Read( fparam, TTyrePressure );
   serialize::Read( fparam, total_step_T );
   serialize::Read( fparam, total_T );
   serialize::Read( fparam, num_T_poll );
   serialize::Read( fparam, reinterpret_cast<uint8_t*>( &Tsettings[0][0] ), sizeof(Tsettings) );
   serialize::Read( fparam, reinterpret_cast<uint8_t*>( &prog_step_T[0] ), sizeof(prog_step_T) );
   serialize::Read( fparam, reinterpret_cast<uint8_t*>( &poll_step_T[0] ), sizeof(poll_step_T) );

   fclose(fparam);
   logger::LogPrint("Loading TProg fm file: Total T=" + dt::mSecToHMSStr(total_T), logger::lcLIME);
}
void TimeProgramm::Save() const
{
   FILE *fparam = fopen( TProgFName.c_str(), "wb");
   if ( fparam == nullptr )
   {
      logger::LogPrint("Can't open file \"" + TProgFName + "\" for reading!", logger::lcRED );
      return;
   }

   serialize::Write( fparam, TProgName );
   serialize::Write( fparam, TTyrePressure );
   serialize::Write( fparam, total_step_T );
   serialize::Write( fparam, total_T );
   serialize::Write( fparam, num_T_poll );
   serialize::Write( fparam, reinterpret_cast<uint8_t const*>( &Tsettings[0][0] ), sizeof(Tsettings) );
   serialize::Write( fparam, reinterpret_cast<uint8_t const*>( &prog_step_T[0] ), sizeof(prog_step_T) );
   serialize::Write( fparam, reinterpret_cast<uint8_t const*>( &poll_step_T[0] ), sizeof(poll_step_T) );

   fclose(fparam);
}

void TimeProgramm::ToCpu( cpu::data::GR5& gr5, cpu::data::GR6& gr6 )
{
   // читаем программу из ячеек и загружаем в контроллер поз. А
   for (int i = 0; i < STEPS_COUNT; i++)
   {
      gr5.step_T[i] = prog_step_T[i];
      for ( size_t j = 0; j < ARRAYS_COUNT; ++j )
         gr6.setting[j][i] = Tsettings[j][i];
   }
   for (int i = 0; i < POLLS_COUNT; i++)
   {
      gr5.poll_step_T[i] = poll_step_T[i];
   }
}
