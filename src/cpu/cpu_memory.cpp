﻿#include "cpu_memory.h"
#include <memory>
#include <mutex>
#include "miniOPC.h"
#include "thread"

namespace cpu
{

namespace
{
static std::unique_ptr< CpuMemory > CPU_MEMORY;
static std::mutex CPU_MEMORY_MUTEX;

std::vector< CpuMemory::CallBack > CALLBACKS;
}//namespace

Position::Position(std::unique_ptr<data::GR1> gr1,
                    std::unique_ptr<data::GR2> gr2,
                    std::unique_ptr<data::GR3> gr3,
                    std::unique_ptr<data::GR4> gr4,
                    std::unique_ptr<data::GR5> gr5,
                    std::unique_ptr<data::GR6> gr6,
                    std::unique_ptr<data::GR7> gr7,
                    std::unique_ptr<data::GR12> gr12 ,
                   std::unique_ptr<data::SI8> si8):
                  mGr1( std::move( gr1 ) ),
                  mGr2( std::move( gr2 ) ),
                  mGr3( std::move( gr3 ) ),
                  mGr4( std::move( gr4 ) ),
                  mGr5( std::move( gr5 ) ),
                  mGr6( std::move( gr6 ) ),
                  mGr7( std::move( gr7 ) ),
                  mGr12( std::move( gr12 ) ),
                  mTimeSensor( std::move( si8 ) )
{}

CpuMemory::CpuMemory():
   mSpeedSensor(0)
{
   if ( IsConnected() )
   {
      mPos1.reset( new Position(
                      std::unique_ptr<data::GR1>( new data::GR1( cpu::data::Gr1Pos1Name, cpu::data::Gr1Pos1Adresses ) ),
                      std::unique_ptr<data::GR2>( new data::GR2( cpu::data::Gr2Pos1Name, cpu::data::Gr2Pos1Adresses ) ),
                      std::unique_ptr<data::GR3>( new data::GR3( cpu::data::Gr3Pos1Name, cpu::data::Gr3Pos1Adresses ) ),
                      std::unique_ptr<data::GR4>( new data::GR4( cpu::data::Gr4Pos1Name, cpu::data::Gr4Pos1Adresses ) ),
                      std::unique_ptr<data::GR5>( new data::GR5( cpu::data::Gr5Pos1Name, cpu::data::Gr5Pos1Adresses ) ),
                      std::unique_ptr<data::GR6>( new data::GR6( cpu::data::Gr6Pos1Name, cpu::data::Gr6Pos1Adresses ) ),
                      std::unique_ptr<data::GR7>( new data::GR7( cpu::data::Gr7Pos1Name, cpu::data::Gr7Pos1Adresses ) ),
                      std::unique_ptr<data::GR12>( new data::GR12( cpu::data::Gr12Pos1NameA, cpu::data::Gr12Pos1AdressesA,
                                                                   cpu::data::Gr12Pos1NameQ, cpu::data::Gr12Pos1AdressesQ ) ),
                      std::unique_ptr<data::SI8>( new data::SI8( 1 ) )
                     ) );

      mPos2.reset( new Position(
                      std::unique_ptr<data::GR1>( new data::GR1( cpu::data::Gr1Pos2Name, cpu::data::Gr1Pos2Adresses ) ),
                      std::unique_ptr<data::GR2>( new data::GR2( cpu::data::Gr2Pos2Name, cpu::data::Gr2Pos2Adresses ) ),
                      std::unique_ptr<data::GR3>( new data::GR3( cpu::data::Gr3Pos2Name, cpu::data::Gr3Pos2Adresses ) ),
                      std::unique_ptr<data::GR4>( new data::GR4( cpu::data::Gr4Pos2Name, cpu::data::Gr4Pos2Adresses ) ),
                      std::unique_ptr<data::GR5>( new data::GR5( cpu::data::Gr5Pos2Name, cpu::data::Gr5Pos2Adresses ) ),
                      std::unique_ptr<data::GR6>( new data::GR6( cpu::data::Gr6Pos2Name, cpu::data::Gr6Pos2Adresses ) ),
                      std::unique_ptr<data::GR7>( new data::GR7( cpu::data::Gr7Pos2Name, cpu::data::Gr7Pos2Adresses ) ),
                      std::unique_ptr<data::GR12>( new data::GR12( cpu::data::Gr12Pos2NameA, cpu::data::Gr12Pos2AdressesA,
                                                                   cpu::data::Gr12Pos2NameQ, cpu::data::Gr12Pos2AdressesQ ) ),
                      std::unique_ptr<data::SI8>( new data::SI8( 2 ) )
                     ) );

      mPos.push_back( mPos1.get() );
      mPos.push_back( mPos2.get() );

      std::thread([]()
      {
         for( auto f: CALLBACKS )
            f();
      }).detach();
   }
}
CpuMemory::~CpuMemory()
{}

CpuMemory& CpuMemory::Instance()
{
   std::lock_guard< std::mutex > lock( CPU_MEMORY_MUTEX );
   if ( !CPU_MEMORY || !CPU_MEMORY->IsConnected() )
   {
      CPU_MEMORY.reset( new CpuMemory() );
   }
   return *CPU_MEMORY;
}

int CpuMemory::ReadCycleParameters() // чтение циклических параметров
{
   if ( !IsConnected() || !mSpeedSensor.IsConnected() )
      return 0;

   //обновляем данные в контроллере

   //читаем данные с контроллера
   bool res = mCommonParams.Read();
   mCommonParams.SensorDrumSpeed = mSpeedSensor.DSPD();
   for ( Position* p: mPos )
   {
      res &=p->mGr1->Read();
      res &=p->mGr2->Read();
      res &=p->mGr3->Read();
      p->mGr2->fakt_distance = p->mTimeSensor->F_DCNT();
      p->mGr2->fakt_time = p->mTimeSensor->DTMR();
      p->mGr2->Write();
   }
   return res ? 1 : 0;
}

bool CpuMemory::IsConnected()
{
   return opc::miniOPC::Instance().Connected();
}

void CpuMemory::OnConnected( CallBack f )
{
   std::lock_guard< std::mutex > lock( CPU_MEMORY_MUTEX );
   CALLBACKS.push_back( f );
   if ( CPU_MEMORY && CPU_MEMORY->IsConnected() )
      f();
}
}//namespace cpu
