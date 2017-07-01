#pragma once
#ifndef gr4H
#define gr4H
#include "../data_block_base.h"


namespace cpu
{
class CpuMemory;
namespace data
{

class GR4 :public InOut
{
public:
   enum
   {
      POLLS_COUNT = 250,
      STEPS_COUNT = 100,
   };

   bool Read();
   void Write();

   float poll_step_SA[POLLS_COUNT];
   float step_SA[STEPS_COUNT];

private:
   friend class cpu::CpuMemory;
   GR4();
   GR4( const GR4& ) = delete;
   void operator = ( const GR4& ) = delete;

   enum
   {
       ARRAYS_COUNT = 2
   };

   unsigned long long mGroupID = 0;
   wchar_t const* mAdresses[ ARRAYS_COUNT ] =
   {
      L"S7:[S7 connection_4]DB8,REAL0,250",
      L"S7:[S7 connection_4]DB22,REAL0,100"
   };
};

}

}
#endif
