#pragma once
#ifndef gr5H
#define gr5H
#include "../data_block_base.h"
#include <stdint.h>

namespace cpu
{
class CpuMemory;
namespace data
{

class GR5 :public InOut
{
public:
   enum
   {
      POLLS_COUNT = 250,
      STEPS_COUNT = 100,
   };

   bool Read();
   void Write();

   int32_t poll_step_TA[POLLS_COUNT];
   int32_t step_TA[STEPS_COUNT];

private:
   friend class cpu::CpuMemory;
   GR5();
   GR5( const GR5& ) = delete;
   void operator = ( const GR5& ) = delete;

   enum
   {
       ARRAYS_COUNT = 2
   };

   unsigned long long mGroupID = 0;
   wchar_t const* mAdresses[ ARRAYS_COUNT ] =
   {
      L"S7:[S7 connection_4]DB7,DINT0,250",
      L"S7:[S7 connection_4]DB21,DINT0,100"
   };
};

}

}
#endif
