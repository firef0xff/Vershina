#pragma once
#ifndef gr9H
#define gr9H
#include "../data_block_base.h"
#include <stdint.h>

namespace cpu
{
class CpuMemory;
namespace data
{

class GR9 :public InOut
{
public:
   enum
   {
      POLLS_COUNT = 250,
      STEPS_COUNT = 100,
   };

   bool Read();
   void Write();

   int32_t poll_step_TB[POLLS_COUNT];
   int32_t step_TB[STEPS_COUNT];

private:
   friend class cpu::CpuMemory;
   GR9();
   GR9( const GR9& ) = delete;
   void operator = ( const GR9& ) = delete;

   enum
   {
       ARRAYS_COUNT = 2
   };

   unsigned long long mGroupID = 0;
   wchar_t const* mAdresses[ ARRAYS_COUNT ] =
   {
      L"S7:[S7 connection_4]DB17,DINT0,250",
      L"S7:[S7 connection_4]DB31,DINT0,100"
   };
};

}

}
#endif
