#pragma once
#ifndef gr6H
#define gr6H
#include "../data_block_base.h"
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
      ITEMS_COUNT = 100,
   };

   bool Read();
   void Write();

   float setting_A0[ITEMS_COUNT];
   float setting_A1[ITEMS_COUNT];

private:
   friend class cpu::CpuMemory;
   GR6();
   GR6( const GR6& ) = delete;
   void operator = ( const GR6& ) = delete;

   enum
   {
       ARRAYS_COUNT = 2
   };

   unsigned long long mGroupID = 0;
   wchar_t const* mAdresses[ ARRAYS_COUNT ] =
   {
      L"S7:[S7 connection_4]DB23,REAL0,100",
      L"S7:[S7 connection_4]DB23,REAL100,100"
   };
};

}

}
#endif
