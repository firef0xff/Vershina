#include "gr2.h"
#include "miniOPC.h"
#include <memory.h>
namespace cpu
{

namespace data
{
wchar_t const* Gr2Pos1Adresses[ GR2::INT_COUNT + GR2::FLOAT_COUNT ] =
{
   //int
   L"S7:[S7 connection_4]DB20,DINT188",

   //float
   L"S7:[S7 connection_4]DB20,REAL18",
   L"S7:[S7 connection_4]DB20,REAL22",
   L"S7:[S7 connection_4]DB20,REAL30",
   L"S7:[S7 connection_4]DB20,REAL34",
   L"S7:[S7 connection_4]DB20,REAL46",
   L"S7:[S7 connection_4]DB20,REAL50",
   L"S7:[S7 connection_4]DB20,REAL156",
   L"S7:[S7 connection_4]DB20,REAL164",
   L"S7:[S7 connection_4]DB20,REAL172",
   L"S7:[S7 connection_4]DB20,REAL196",
};
wchar_t const* Gr2Pos2Adresses[ GR2::INT_COUNT + GR2::FLOAT_COUNT ] =
{
   //int
   L"S7:[S7 connection_4]DB20,DINT192",

   //float
   L"S7:[S7 connection_4]DB20,REAL58",
   L"S7:[S7 connection_4]DB20,REAL62",
   L"S7:[S7 connection_4]DB20,REAL70",
   L"S7:[S7 connection_4]DB20,REAL74",
   L"S7:[S7 connection_4]DB20,REAL86",
   L"S7:[S7 connection_4]DB20,REAL90",
   L"S7:[S7 connection_4]DB20,REAL160",
   L"S7:[S7 connection_4]DB20,REAL168",
   L"S7:[S7 connection_4]DB20,REAL176",
   L"S7:[S7 connection_4]DB20,REAL200"
};

wchar_t const* Gr2Pos1Name = L"Gr2Pos1";
wchar_t const* Gr2Pos2Name = L"Gr2Pos2";

GR2::GR2(const wchar_t* group_name, const wchar_t *addresses[] )
{
   memset( mIntData, 0, sizeof(mIntData) );
   memset( mFloatData, 0, sizeof(mFloatData) );
   mGroupID = opc::miniOPC::Instance().AddGroup( group_name, addresses, INT_COUNT + FLOAT_COUNT );
}

void GR2::Write()
{
   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, INT_COUNT, static_cast<void*>( mIntData ), opc::tINT );

   res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, INT_COUNT, FLOAT_COUNT, static_cast<void*>( mFloatData ), opc::tFLOAT );
}

bool GR2::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez) //ошибка подключения..
      return false;
   for (size_t i = 0; i < INT_COUNT + FLOAT_COUNT; i++)
   {
      if ( i < INT_COUNT )
         mIntData[ i ] = rez[i].vDataValue.lVal;
      else
         mFloatData[ i - INT_COUNT ] = rez[i].vDataValue.fltVal;
   }
   opc::miniOPC::Instance().OpcMassFree( mGroupID, rez );
   return true;
}

void GR2::Clear()
{
   for ( int i = 0; i < INT_COUNT; ++i )
      mIntData[i] = 0;
   for ( int i = 0; i < FLOAT_COUNT; ++i )
      mFloatData[i] = 0.0;
}

}//namespace data

}//namespace cpu
