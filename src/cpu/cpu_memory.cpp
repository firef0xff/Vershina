#include "cpu_memory.h"
#include <memory>
#include <mutex>

namespace cpu
{

namespace
{
static std::unique_ptr< CpuMemory > CPU_MEMORY;
static std::mutex CPU_MEMORY_MUTEX;

//A
data::GR1 Gr1Pos1( cpu::data::Gr1Pos1Name, cpu::data::Gr1Pos1Adresses );
data::GR2 Gr2Pos1( cpu::data::Gr2Pos1Name, cpu::data::Gr2Pos1Adresses );
data::GR3 Gr3Pos1( cpu::data::Gr3Pos1Name, cpu::data::Gr3Pos1Adresses );
data::GR4 Gr4Pos1( cpu::data::Gr4Pos1Name, cpu::data::Gr4Pos1Adresses );
data::GR5 Gr5Pos1( cpu::data::Gr5Pos1Name, cpu::data::Gr5Pos1Adresses );
data::GR6 Gr6Pos1( cpu::data::Gr6Pos1Name, cpu::data::Gr6Pos1Adresses );
data::GR7 Gr7Pos1( cpu::data::Gr7Pos1Name, cpu::data::Gr7Pos1Adresses );
data::GR12 Gr12Pos1( cpu::data::Gr12Pos1NameA, cpu::data::Gr12Pos1AdressesA,
                     cpu::data::Gr12Pos1NameQ, cpu::data::Gr12Pos1AdressesQ );

//B
data::GR1 Gr1Pos2( cpu::data::Gr1Pos2Name, cpu::data::Gr1Pos2Adresses );
data::GR2 Gr2Pos2( cpu::data::Gr2Pos2Name, cpu::data::Gr2Pos2Adresses );
data::GR3 Gr3Pos2( cpu::data::Gr3Pos2Name, cpu::data::Gr3Pos2Adresses );
data::GR4 Gr4Pos2( cpu::data::Gr4Pos2Name, cpu::data::Gr4Pos2Adresses );
data::GR5 Gr5Pos2( cpu::data::Gr5Pos2Name, cpu::data::Gr5Pos2Adresses );
data::GR6 Gr6Pos2( cpu::data::Gr6Pos2Name, cpu::data::Gr6Pos2Adresses );
data::GR7 Gr7Pos2( cpu::data::Gr7Pos2Name, cpu::data::Gr7Pos2Adresses );
data::GR12 Gr12Pos2( cpu::data::Gr12Pos2NameA, cpu::data::Gr12Pos2AdressesA,
                     cpu::data::Gr12Pos2NameQ, cpu::data::Gr12Pos2AdressesQ );

}//namespace

Position::Position(data::GR1 &gr1,
                      data::GR2 &gr2,
                      data::GR3 &gr3,
                      data::GR4& gr4,
                      data::GR5& gr5,
                      data::GR6& gr6,
                      data::GR7& gr7,
                      data::GR12& gr12 ):
                  mGr1( gr1 ),
                  mGr2( gr2 ),
                  mGr3( gr3 ),
                  mGr4( gr4 ),
                  mGr5( gr5 ),
                  mGr6( gr6 ),
                  mGr7( gr7 ),
                  mGr12( gr12 )
{}

CpuMemory::CpuMemory():
   mPos1( Gr1Pos1, Gr2Pos1, Gr3Pos1, Gr4Pos1, Gr5Pos1, Gr6Pos1, Gr7Pos1, Gr12Pos1 ),
   mPos2( Gr1Pos2, Gr2Pos2, Gr3Pos2, Gr4Pos2, Gr5Pos2, Gr6Pos2, Gr7Pos2, Gr12Pos2 )
{
   mPos.push_back( &mPos1 );
   mPos.push_back( &mPos2 );
}
CpuMemory::~CpuMemory()
{}

CpuMemory& CpuMemory::Instance()
{
    if ( !CPU_MEMORY )
    {
        std::lock_guard< std::mutex > lock( CPU_MEMORY_MUTEX );
        if ( !CPU_MEMORY )
        {
            CPU_MEMORY.reset( new CpuMemory() );
        }
    }
    return *CPU_MEMORY;
}

int CpuMemory::ReadCycleParameters() // чтение циклических параметров
{
   bool res = mCommonParams.Read();

   for ( Position* p: mPos )
   {
      res &=p->mGr1.Read();
      res &=p->mGr2.Read();
   }

   return res ? 1 : 0;
}

}//namespace cpu
