#include "gr9.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{
GR9::GR9()
{
    memset( poll_step_TB, 0, sizeof(poll_step_TB) );
    memset( step_TB, 0, sizeof(step_TB) );
    mGroupID = opc::miniOPC::Instance().AddGroup( L"GR9", mAdresses, ARRAYS_COUNT );
}

bool GR9::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez)//ошибка подключения..
      return false;

   opc::ReadToArray( rez[0].vDataValue, poll_step_TB, POLLS_COUNT );
   opc::ReadToArray( rez[1].vDataValue, step_TB, STEPS_COUNT );
   opc::miniOPC::Instance().OpcMassFree( mGroupID, rez );

   return true;
}

void GR9::Write()
{
   VARIANT data[ARRAYS_COUNT];

   opc::LoadToVariant( data[0], poll_step_TB, POLLS_COUNT );
   opc::LoadToVariant( data[1], step_TB, STEPS_COUNT );

   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, ARRAYS_COUNT, static_cast<void*>( &data ), opc::tVARIANT );
}

}
}
