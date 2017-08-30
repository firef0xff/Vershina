#pragma once
#ifndef gr12H
#define gr12H
#include "../data_block_base.h"
#include <stdint.h>

namespace cpu
{
class CpuMemory;
namespace data
{

class GR12 :public InOut
{
public:
   enum
   {
      ITEMS_COUNT = 40,
   };
   GR12( const wchar_t *group_a_name, const wchar_t *a_addresses[],
         const wchar_t *group_q_name, const wchar_t *q_addresses[]);

   bool Read();
   void Write();

   float A[ITEMS_COUNT];
   float Q[ITEMS_COUNT];

   void ResetKA();

private:
   friend class cpu::CpuMemory;
   GR12( const GR12& ) = delete;
   void operator = ( const GR12& ) = delete;

   void WriteA();
   void WriteQ();

   uint64_t mAGroupID = 0;
   uint64_t mQGroupID = 0;
};

extern wchar_t const* Gr12Pos1AdressesA[ GR12::ITEMS_COUNT ];
extern wchar_t const* Gr12Pos1NameA;

extern wchar_t const* Gr12Pos1AdressesQ[ GR12::ITEMS_COUNT ];
extern wchar_t const* Gr12Pos1NameQ;

}

}
#endif
