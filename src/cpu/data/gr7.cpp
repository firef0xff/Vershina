#include "gr7.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{
wchar_t const* Gr7Pos1Adresses[ GR7::ARRAYS_COUNT ]=
{
   L"S7:[S7 connection_4]DB1,DINT2,250", L"S7:[S7 connection_4]DB2,REAL2,250",
   L"S7:[S7 connection_4]DB3,REAL2,250", L"S7:[S7 connection_4]DB4,REAL2,250",
   L"S7:[S7 connection_4]DB5,REAL2,250", L"S7:[S7 connection_4]DB6,REAL2,250",
};
wchar_t const* Gr7Pos1Name = L"Gr7Pos1";

GR7::GR7(const wchar_t *group_name, const wchar_t *addresses[])
{
    memset( read_T, 0, sizeof(read_T) );
    memset( read_V, 0, sizeof(read_V) );
    memset( read_S, 0, sizeof(read_S) );
    memset( read_L, 0, sizeof(read_L) );
    memset( read_R, 0, sizeof(read_R) );
    memset( read_Temp, 0, sizeof(read_Temp) );
    mGroupID = opc::miniOPC::Instance().AddGroup( group_name, addresses, ARRAYS_COUNT );
}

bool GR7::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez)//ошибка подключения..
      return false;

   opc::ReadToArray( rez[0].vDataValue, read_T, ITEMS_COUNT );
   opc::ReadToArray( rez[1].vDataValue, read_V, ITEMS_COUNT );
   opc::ReadToArray( rez[2].vDataValue, read_S, ITEMS_COUNT );
   opc::ReadToArray( rez[3].vDataValue, read_L, ITEMS_COUNT );
   opc::ReadToArray( rez[4].vDataValue, read_R, ITEMS_COUNT );
   opc::ReadToArray( rez[5].vDataValue, read_Temp, ITEMS_COUNT );
   opc::miniOPC::Instance().OpcMassFree( mGroupID, rez );

   return true;
}

void GR7::Reset()
{
	memset( read_T, 0, sizeof(read_T) );
    memset( read_V, 0, sizeof(read_V) );
    memset( read_S, 0, sizeof(read_S) );
    memset( read_L, 0, sizeof(read_L) );
    memset( read_R, 0, sizeof(read_R) );
	memset( read_Temp, 0, sizeof(read_Temp) );

   Write();
}

void GR7::Write()
{
   VARIANT data[ARRAYS_COUNT];

   opc::LoadToVariant( data[0], read_T, ITEMS_COUNT );
   opc::LoadToVariant( data[1], read_V, ITEMS_COUNT );
   opc::LoadToVariant( data[2], read_S, ITEMS_COUNT );
   opc::LoadToVariant( data[3], read_L, ITEMS_COUNT );
   opc::LoadToVariant( data[4], read_R, ITEMS_COUNT );
   opc::LoadToVariant( data[5], read_Temp, ITEMS_COUNT );

   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, ARRAYS_COUNT, static_cast<void*>( &data ), opc::tVARIANT );
}

}
}
