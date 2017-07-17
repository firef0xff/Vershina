#include "gr4.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{
wchar_t const* Gr4Pos1Adresses[ GR4::ARRAYS_COUNT ] =
{
   L"S7:[S7 connection_4]DB8,REAL0,250",
   L"S7:[S7 connection_4]DB22,REAL0,100"
};
wchar_t const* Gr4Pos1Name = L"Gr4Pos1";

GR4::GR4(const wchar_t *group_name, wchar_t const* addresses[] )
{
    memset( poll_step_S, 0, sizeof(poll_step_S) );
    memset( step_S, 0, sizeof(step_S) );
    mGroupID = opc::miniOPC::Instance().AddGroup( group_name, addresses, ARRAYS_COUNT );
}

bool GR4::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez)//ошибка подключения..
      return false;

   opc::ReadToArray( rez[0].vDataValue, poll_step_S, POLLS_COUNT );
   opc::ReadToArray( rez[1].vDataValue, step_S, STEPS_COUNT );
   opc::miniOPC::Instance().OpcMassFree( mGroupID, rez );

   return true;
}

void GR4::Write()
{
   VARIANT data[ARRAYS_COUNT];

   opc::LoadToVariant( data[0], poll_step_S, POLLS_COUNT );
   opc::LoadToVariant( data[1], step_S, STEPS_COUNT );

   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, ARRAYS_COUNT, static_cast<void*>( &data ), opc::tVARIANT );
}

}
}
