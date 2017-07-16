#include "gr6.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{
GR6::GR6()
{
    memset( setting_A0, 0, sizeof(setting_A0) );
    memset( setting_A1, 0, sizeof(setting_A1) );
    mGroupID = opc::miniOPC::Instance().AddGroup( L"GR6", mAdresses, ARRAYS_COUNT );
}

bool GR6::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez)//ошибка подключения..
      return false;

   opc::ReadToArray( rez[0].vDataValue, setting_A0, ITEMS_COUNT );
   opc::ReadToArray( rez[1].vDataValue, setting_A1, ITEMS_COUNT );
   opc::miniOPC::Instance().OpcMassFree( mGroupID, rez );

   return true;
}

void GR6::Write()
{
   VARIANT data[ARRAYS_COUNT];

   opc::LoadToVariant( data[0], setting_A0, ITEMS_COUNT );
   opc::LoadToVariant( data[1], setting_A1, ITEMS_COUNT );

   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, ARRAYS_COUNT, static_cast<void*>( &data ), opc::tVARIANT );
}

}
}
