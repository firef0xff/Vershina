#include "gr8.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{
GR8::GR8()
{
    memset( poll_step_SB, 0, sizeof(poll_step_SB) );
    memset( step_SB, 0, sizeof(step_SB) );
    mGroupID = opc::miniOPC::Instance().AddGroup( L"GR8", mAdresses, ARRAYS_COUNT );
}

bool GR8::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez)//ошибка подключения..
      return false;

   opc::ReadToArray( rez[0].vDataValue, poll_step_SB, POLLS_COUNT );
   opc::ReadToArray( rez[1].vDataValue, step_SB, STEPS_COUNT );
   opc::miniOPC::Instance().OpcMassFree( mGroupID, rez );

   return true;
}

void GR8::Write()
{
   VARIANT data[ARRAYS_COUNT];

   opc::LoadToVariant( data[0], poll_step_SB, POLLS_COUNT );
   opc::LoadToVariant( data[1], step_SB, STEPS_COUNT );

   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, ARRAYS_COUNT, static_cast<void*>( &data ), opc::tVARIANT );
}

}
}
