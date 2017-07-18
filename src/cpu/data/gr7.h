#pragma once
#ifndef gr7H
#define gr7H
#include "../data_block_base.h"
#include <stdint.h>

namespace cpu
{
class CpuMemory;
namespace data
{

class GR7 :public InOut
{
public:
   enum
   {
      ITEMS_COUNT = 250,
      ARRAYS_COUNT = 6
   };

   bool Read();
   void Reset();
   int32_t read_T[ITEMS_COUNT];
   float read_V[ITEMS_COUNT];
   float read_S[ITEMS_COUNT];
   float read_L[ITEMS_COUNT];
   float read_R[ITEMS_COUNT];
   float read_Temp[ITEMS_COUNT];

private:
   void Write();
   friend class cpu::CpuMemory;
   GR7(const wchar_t* group_name, const wchar_t *addresses[] );
   GR7( const GR7& ) = delete;
   void operator = ( const GR7& ) = delete;

   unsigned long long mGroupID = 0;
};

extern wchar_t const* Gr7Pos1Adresses[ GR7::ARRAYS_COUNT ];
extern wchar_t const* Gr7Pos1Name;

}

}
#endif
