#include "gr4.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{
GR4::GR4()
{
    memset( poll_step_SA, 0, sizeof(poll_step_SA) );
    memset( step_SA, 0, sizeof(step_SA) );
    mGroupID = opc::miniOPC::Instance().AddGroup( L"GR4", mAdresses, ARRAYS_COUNT );
}

bool GR4::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez)//ошибка подключения..
      return false;

   opc::ReadToArray( rez[0].vDataValue, poll_step_SA, POLLS_COUNT );
   opc::ReadToArray( rez[1].vDataValue, step_SA, STEPS_COUNT );
   opc::miniOPC::Instance().OpcMassFree( mGroupID, rez );

   return true;
}

void GR4::Write()
{
   VARIANT data[ARRAYS_COUNT];

   opc::LoadToVariant( data[0], poll_step_SA, POLLS_COUNT );
   opc::LoadToVariant( data[1], step_SA, STEPS_COUNT );

   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, ARRAYS_COUNT, static_cast<void*>( &data ), opc::tVARIANT );
}

}
}
