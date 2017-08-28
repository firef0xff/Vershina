#include "path_programm.h"
#include "../support_functions/serialize.h"
#include "../log/log.h"

PathProgramm::PathProgramm()
{
}


void PathProgramm::Load() // прочитать программу по пути из файла
{
   FILE *fparam = fopen( SProgFName.c_str(), "rb" );
   if ( fparam == nullptr )
   {
      logger::LogPrint("Can't open file \"" + SProgFName + "\" for reading!", logger::lcRED);
      return;
   }
   serialize::Read( fparam, SProgName );
   serialize::Read( fparam, STyrePressure );
   serialize::Read( fparam, total_step_S );
   serialize::Read( fparam, total_S );
   serialize::Read( fparam, num_S_poll );
   serialize::Read( fparam, reinterpret_cast<uint8_t*>( &Ssettings[0][0] ), sizeof(Ssettings) );
   serialize::Read( fparam, reinterpret_cast<uint8_t*>( &prog_step_S[0] ), sizeof(prog_step_S) );
   serialize::Read( fparam, reinterpret_cast<uint8_t*>( &poll_step_S[0] ), sizeof(poll_step_S) );
   fclose(fparam);
}

void PathProgramm::Save() // записать программу по пути в файл
{
   FILE *fparam = fopen(SProgFName.c_str(), "wb");
   if ( fparam == nullptr )
   {
      logger::LogPrint("Can't open file \"" + SProgFName + "\" for writing!", logger::lcRED);
      return;
   }
   serialize::Write( fparam, SProgName );
   serialize::Write( fparam, STyrePressure );
   serialize::Write( fparam, total_step_S );
   serialize::Write( fparam, total_S );
   serialize::Write( fparam, num_S_poll );
   serialize::Write( fparam, reinterpret_cast<uint8_t const*>( &Ssettings[0][0] ), sizeof(Ssettings) );
   serialize::Write( fparam, reinterpret_cast<uint8_t const*>( &prog_step_S[0] ), sizeof(prog_step_S) );
   serialize::Write( fparam, reinterpret_cast<uint8_t const*>( &poll_step_S[0] ), sizeof(poll_step_S) );
   fclose(fparam);
}

void PathProgramm::Clear()
{
   for (size_t i = 0; i < POLLS_COUNT; i++) // массив опросов по пути
   {
      poll_step_S[i] = 0;
   }
   for (size_t i = 0; i < STEPS_COUNT; i++)
   {
      prog_step_S[i] = 0;
      for ( size_t j = 0; j < ARRAYS_COUNT; ++j )
         Ssettings[j][i] = 0;
   }
   SProgFName = ""; // имя файла для сохранения программы по пути
   SProgName = ""; // имя программы испытаний по пути
   STyrePressure = 0.0; // давление в шине
   total_step_S = 0; // суммарное кол-во шагов программы по пути
   total_S = 0.0; // суммарная продолжительность программы по пути, км
   num_S_poll = 0; // количество опросов по пути
}

void PathProgramm::ToCpu( cpu::data::GR4& gr4, cpu::data::GR6& gr6 )
{
   for (int i = 0; i < STEPS_COUNT; i++)
   {
      gr4.step_S[i] = prog_step_S[i];
      for ( size_t j = 0; j < ARRAYS_COUNT; ++j )
         gr6.setting[j][i] = Ssettings[j][i];
   }
   for (int i = 0; i < POLLS_COUNT; i++)
   {
      gr4.poll_step_S[i] = poll_step_S[i];
   }
}
