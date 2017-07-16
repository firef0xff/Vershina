#pragma once
#ifndef gr8H
#define gr8H
#include "../data_block_base.h"


namespace cpu
{
class CpuMemory;
namespace data
{

class GR8 :public InOut
{
public:
   enum
   {
      POLLS_COUNT = 250,
      STEPS_COUNT = 100,
   };

   bool Read();
   void Write();

   float poll_step_SB[POLLS_COUNT];
   float step_SB[STEPS_COUNT];

private:
   friend class cpu::CpuMemory;
   GR8();
   GR8( const GR8& ) = delete;
   void operator = ( const GR8& ) = delete;

   enum
   {
       ARRAYS_COUNT = 2
   };

   unsigned long long mGroupID = 0;
   wchar_t const* mAdresses[ ARRAYS_COUNT ] =
   {
      L"S7:[S7 connection_4]DB18,REAL0,250",
      L"S7:[S7 connection_4]DB32,REAL0,100"
   };
};

}

}
#endif
