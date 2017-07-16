#include "gr5.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{
GR5::GR5()
{
    memset( poll_step_TA, 0, sizeof(poll_step_TA) );
    memset( step_TA, 0, sizeof(step_TA) );
    mGroupID = opc::miniOPC::Instance().AddGroup( L"GR5", mAdresses, ARRAYS_COUNT );
}

bool GR5::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez)//ошибка подключения..
      return false;

   opc::ReadToArray( rez[0].vDataValue, poll_step_TA, POLLS_COUNT );
   opc::ReadToArray( rez[1].vDataValue, step_TA, STEPS_COUNT );
   opc::miniOPC::Instance().OpcMassFree( mGroupID, rez );

   return true;
}

void GR5::Write()
{
   VARIANT data[ARRAYS_COUNT];

   opc::LoadToVariant( data[0], poll_step_TA, POLLS_COUNT );
   opc::LoadToVariant( data[1], step_TA, STEPS_COUNT );

   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, ARRAYS_COUNT, static_cast<void*>( &data ), opc::tVARIANT );
}

}
}
