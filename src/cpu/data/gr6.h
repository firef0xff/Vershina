#pragma once
#ifndef gr6H
#define gr6H
#include "../data_block_base.h"
#include "gr5.h"
#include <stdint.h>

namespace cpu
{
class CpuMemory;
namespace data
{

class GR6 :public InOut
{
public:
   enum
   {
      ITEMS_COUNT = GR5::STEPS_COUNT,
      ARRAYS_COUNT = 2
   };
   GR6(const wchar_t* group_name, const wchar_t *addresses[] );

   bool Read();
   void Write();

   float setting[ARRAYS_COUNT][ITEMS_COUNT];

private:
   friend class cpu::CpuMemory;
   GR6( const GR6& ) = delete;
   void operator = ( const GR6& ) = delete;

   unsigned long long mGroupID = 0;
};
extern wchar_t const* Gr6Pos1Adresses[ GR6::ARRAYS_COUNT ];
extern wchar_t const* Gr6Pos1Name;

}

}
#endif
