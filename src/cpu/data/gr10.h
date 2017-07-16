#pragma once
#ifndef gr10H
#define gr10H
#include "../data_block_base.h"
#include <stdint.h>

namespace cpu
{
class CpuMemory;
namespace data
{

class GR10 :public InOut
{
public:
   enum
   {
      ITEMS_COUNT = 100,
   };

   bool Read();
   void Write();

   float setting_B0[ITEMS_COUNT];
   float setting_B1[ITEMS_COUNT];

private:
   friend class cpu::CpuMemory;
   GR10();
   GR10( const GR10& ) = delete;
   void operator = ( const GR10& ) = delete;

   enum
   {
       ARRAYS_COUNT = 2
   };

   unsigned long long mGroupID = 0;
   wchar_t const* mAdresses[ ARRAYS_COUNT ] =
   {
      L"S7:[S7 connection_4]DB33,REAL0,100",
      L"S7:[S7 connection_4]DB33,REAL100,100"
   };
};

}

}
#endif
