#include "gr1.h"
#include "miniOPC.h"
#include <memory.h>
namespace cpu
{

namespace data
{

wchar_t const* Gr1Pos1Adresses[ GR1::BOOL_COUNT] =
{
   //bool
   L"S7:[S7 connection_4]MX2.1",
   L"S7:[S7 connection_4]IX125.3",
   L"S7:[S7 connection_4]MX50.1",
   L"S7:[S7 connection_4]MX50.3",
   L"S7:[S7 connection_4]MX50.4",
   L"S7:[S7 connection_4]MX2.2",
   L"S7:[S7 connection_4]MX2.3",
   L"S7:[S7 connection_4]MX34.0",
   L"S7:[S7 connection_4]MX34.1",
   L"S7:[S7 connection_4]DB10,X2.0",
   L"S7:[S7 connection_4]DB10,X2.1",
   L"S7:[S7 connection_4]DB10,X2.2",
   L"S7:[S7 connection_4]DB10,X2.3",
   L"S7:[S7 connection_4]DB10,X2.4",
   L"S7:[S7 connection_4]DB10,X3.0",
   L"S7:[S7 connection_4]M0.7",
   L"S7:[S7 connection_4]DB10,X38.5",
};
wchar_t const* Gr1Pos2Adresses[ GR1::BOOL_COUNT] =
{
   //bool
   L"S7:[S7 connection_4]MX3.1",
   L"S7:[S7 connection_4]IX125.7",
   L"S7:[S7 connection_4]MX50.2",
   L"S7:[S7 connection_4]MX50.5",
   L"S7:[S7 connection_4]MX50.6",
   L"S7:[S7 connection_4]MX3.2",
   L"S7:[S7 connection_4]MX3.3",
   L"S7:[S7 connection_4]MX34.2",
   L"S7:[S7 connection_4]MX34.3",
   L"S7:[S7 connection_4]DB10,X38.0",
   L"S7:[S7 connection_4]DB10,X38.1",
   L"S7:[S7 connection_4]DB10,X38.2",
   L"S7:[S7 connection_4]DB10,X38.3",
   L"S7:[S7 connection_4]DB10,X38.4",
   L"S7:[S7 connection_4]DB10,X39.0",
   L"S7:[S7 connection_4]M1.7",
   L"S7:[S7 connection_4]DB10,X38.6",
};

wchar_t const* Gr1Pos1Name = L"Gr1Pos1";
wchar_t const* Gr1Pos2Name = L"Gr1Pos2";

GR1::GR1(const wchar_t* group_name, const wchar_t *addresses[] )
{
   memset( mBoolData, 0, sizeof(mBoolData) );
   mGroupID = opc::miniOPC::Instance().AddGroup( group_name, addresses, BOOL_COUNT);
}

void GR1::Write()
{
   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, BOOL_COUNT, static_cast<void*>( mBoolData ), opc::tBOOL );
}

bool GR1::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez) //ошибка подключения..
      return false;
   for (size_t i = 0; i < BOOL_COUNT ; i++)
   {
      mBoolData[ i ] = rez[i].vDataValue.boolVal;
   }
   opc::miniOPC::Instance().OpcMassFree( mGroupID, rez );
   return true;
}

void GR1::Clear()
{
   for ( int i = 0; i < BOOL_COUNT; ++i )
      mBoolData[i] = false;
}

}//namespace data

}//namespace cpu
