#include "cpu_memory.h"
#include <memory>
#include <mutex>

namespace cpu
{

namespace
{
static std::unique_ptr< CpuMemory > CPU_MEMORY;
static std::mutex CPU_MEMORY_MUTEX;
}//namespace

CpuMemory::CpuMemory():
   mGr4Pos1( cpu::data::Gr4Pos1Name, cpu::data::Gr4Pos1Adresses ),
   mGr5Pos1( cpu::data::Gr5Pos1Name, cpu::data::Gr5Pos1Adresses ),
   mGr6Pos1( cpu::data::Gr6Pos1Name, cpu::data::Gr6Pos1Adresses ),
   mGr7Pos1( cpu::data::Gr7Pos1Name, cpu::data::Gr7Pos1Adresses ),
   mGr12Pos1( cpu::data::Gr12Pos1NameA, cpu::data::Gr12Pos1AdressesA,
              cpu::data::Gr12Pos1NameQ, cpu::data::Gr12Pos1AdressesQ),

   mGr4Pos2( cpu::data::Gr4Pos2Name, cpu::data::Gr4Pos2Adresses ),
   mGr5Pos2( cpu::data::Gr5Pos2Name, cpu::data::Gr5Pos2Adresses ),
   mGr6Pos2( cpu::data::Gr6Pos2Name, cpu::data::Gr6Pos2Adresses ),
   mGr7Pos2( cpu::data::Gr7Pos2Name, cpu::data::Gr7Pos2Adresses ),
   mGr12Pos2( cpu::data::Gr12Pos2NameA, cpu::data::Gr12Pos2AdressesA,
              cpu::data::Gr12Pos2NameQ, cpu::data::Gr12Pos2AdressesQ)
{}
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

int CpuMemory::ReadCycleParameters(void) // чтение циклических параметров
{
   if ( mGr1.Read() && mGr2.Read() )
   {
      return 1;
   }
   return 0;
}

}//namespace cpu
