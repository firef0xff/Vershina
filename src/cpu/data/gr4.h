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
      ARRAYS_COUNT = 2
   };
   GR4(const wchar_t* group_name, const wchar_t *addresses[] );

   bool Read();
   void Write();

   float poll_step_S[POLLS_COUNT];
   float step_S[STEPS_COUNT];

private:
   friend class cpu::CpuMemory;
   GR4( const GR4& ) = delete;
   void operator = ( const GR4& ) = delete;

   unsigned long long mGroupID = 0;

};

extern wchar_t const* Gr4Pos1Adresses[ GR4::ARRAYS_COUNT ];
extern wchar_t const* Gr4Pos1Name;
}

}
#endif
