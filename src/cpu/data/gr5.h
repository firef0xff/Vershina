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
      ARRAYS_COUNT = 2
   };
   GR5(const wchar_t* group_name, const wchar_t *addresses[] );

   bool Read();
   void Write();

   int32_t poll_step_T[POLLS_COUNT];
   int32_t step_T[STEPS_COUNT];

private:
   friend class cpu::CpuMemory;
   GR5( const GR5& ) = delete;
   void operator = ( const GR5& ) = delete;

   unsigned long long mGroupID = 0;
};

extern wchar_t const* Gr5Pos1Adresses[ GR5::ARRAYS_COUNT ];
extern wchar_t const* Gr5Pos1Name;

}

}
#endif
