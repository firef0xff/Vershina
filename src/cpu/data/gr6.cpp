#include "gr6.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{
wchar_t const* Gr6Pos1Adresses[ GR6::ARRAYS_COUNT ] =
{
   L"S7:[S7 connection_4]DB23,REAL0,100",
   L"S7:[S7 connection_4]DB23,REAL100,100"
};
wchar_t const* Gr6Pos1Name = L"Gr6Pos1";

GR6::GR6(const wchar_t *group_name, const wchar_t *addresses[])
{
    memset( setting_0, 0, sizeof(setting_0) );
    memset( setting_1, 0, sizeof(setting_1) );
    mGroupID = opc::miniOPC::Instance().AddGroup( group_name, addresses, ARRAYS_COUNT );
}

bool GR6::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez)//ошибка подключения..
      return false;

   opc::ReadToArray( rez[0].vDataValue, setting_0, ITEMS_COUNT );
   opc::ReadToArray( rez[1].vDataValue, setting_1, ITEMS_COUNT );
   opc::miniOPC::Instance().OpcMassFree( mGroupID, rez );

   return true;
}

void GR6::Write()
{
   VARIANT data[ARRAYS_COUNT];

   opc::LoadToVariant( data[0], setting_0, ITEMS_COUNT );
   opc::LoadToVariant( data[1], setting_1, ITEMS_COUNT );

   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, ARRAYS_COUNT, static_cast<void*>( &data ), opc::tVARIANT );
}

}
}
