#include "gr5.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{
wchar_t const* Gr5Pos1Adresses[ GR5::ARRAYS_COUNT ]=
{
   L"S7:[S7 connection_4]DB7,DINT0,250",
   L"S7:[S7 connection_4]DB21,DINT0,100"
};
wchar_t const* Gr5Pos1Name = L"Gr5Pos1";

GR5::GR5(const wchar_t *group_name, const wchar_t *addresses[])
{
    memset( poll_step_T, 0, sizeof(poll_step_T) );
    memset( step_T, 0, sizeof(step_T) );
    mGroupID = opc::miniOPC::Instance().AddGroup( group_name, addresses, ARRAYS_COUNT );
}

bool GR5::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez)//ошибка подключения..
      return false;

   opc::ReadToArray( rez[0].vDataValue, poll_step_T, POLLS_COUNT );
   opc::ReadToArray( rez[1].vDataValue, step_T, STEPS_COUNT );
   opc::miniOPC::Instance().OpcMassFree( mGroupID, rez );

   return true;
}

void GR5::Write()
{
   VARIANT data[ARRAYS_COUNT];

   opc::LoadToVariant( data[0], poll_step_T, POLLS_COUNT );
   opc::LoadToVariant( data[1], step_T, STEPS_COUNT );

   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, ARRAYS_COUNT, static_cast<void*>( &data ), opc::tVARIANT );
}

}
}
