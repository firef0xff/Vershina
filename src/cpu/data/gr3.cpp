#include "gr3.h"
#include "miniOPC.h"
#include <memory.h>
namespace cpu
{

namespace data
{
wchar_t const* Gr3Pos1Adresses[ GR3::INT_COUNT + GR3::FLOAT_COUNT] =
{
   //int
   L"S7:[S7 connection_4]DB10,DINT10",
   L"S7:[S7 connection_4]DB10,INT4",
   L"S7:[S7 connection_4]DB10,INT34",
   L"S7:[S7 connection_4]DB10,INT36",

   //float
   L"S7:[S7 connection_4]DB10,REAL18",
   L"S7:[S7 connection_4]DB10,REAL26",
   L"S7:[S7 connection_4]DB10,REAL30",
   L"S7:[S7 connection_4]DB10,REAL74",
   L"S7:[S7 connection_4]DB10,REAL82",
   L"S7:[S7 connection_4]DB10,REAL90",
   L"S7:[S7 connection_4]DB10,REAL94",
   L"S7:[S7 connection_4]DB10,REAL98",
   L"S7:[S7 connection_4]DB10,REAL102",
   L"S7:[S7 connection_4]DB10,REAL122",
   L"S7:[S7 connection_4]DB10,REAL126",
   L"S7:[S7 connection_4]DB10,REAL142",
   L"S7:[S7 connection_4]DB10,REAL146",
   L"S7:[S7 connection_4]DB10,REAL158",
   L"S7:[S7 connection_4]DB10,REAL162",

};
wchar_t const* Gr3Pos2Adresses[ GR3::INT_COUNT + GR3::FLOAT_COUNT] =
{
   //int
   L"S7:[S7 connection_4]DB10,DINT46",
   L"S7:[S7 connection_4]DB10,INT40",
   L"S7:[S7 connection_4]DB10,INT70",
   L"S7:[S7 connection_4]DB10,INT72",

   //float
   L"S7:[S7 connection_4]DB10,REAL54",
   L"S7:[S7 connection_4]DB10,REAL62",
   L"S7:[S7 connection_4]DB10,REAL66",
   L"S7:[S7 connection_4]DB10,REAL78",
   L"S7:[S7 connection_4]DB10,REAL86",
   L"S7:[S7 connection_4]DB10,REAL106",
   L"S7:[S7 connection_4]DB10,REAL110",
   L"S7:[S7 connection_4]DB10,REAL114",
   L"S7:[S7 connection_4]DB10,REAL118",
   L"S7:[S7 connection_4]DB10,REAL130",
   L"S7:[S7 connection_4]DB10,REAL134",
   L"S7:[S7 connection_4]DB10,REAL150",
   L"S7:[S7 connection_4]DB10,REAL154",
   L"S7:[S7 connection_4]DB10,REAL166",
   L"S7:[S7 connection_4]DB10,REAL170"
};

wchar_t const* Gr3Pos1Name = L"Gr3Pos1";
wchar_t const* Gr3Pos2Name = L"Gr3Pos2";

GR3::GR3(const wchar_t* group_name, const wchar_t *addresses[] )
{
   memset( mIntData, 0, sizeof(mIntData) );
   memset( mFloatData, 0, sizeof(mFloatData) );
   mGroupID = opc::miniOPC::Instance().AddGroup( group_name, addresses, INT_COUNT + FLOAT_COUNT );
}

void GR3::Write()
{
   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, INT_COUNT, static_cast<void*>( mIntData ), opc::tINT );

   res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, INT_COUNT, FLOAT_COUNT, static_cast<void*>( mFloatData ), opc::tFLOAT );
}

bool GR3::Read()
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

void GR3::Clear()
{
   for ( int i = 0; i < INT_COUNT; ++i )
      mIntData[i] = 0;
   for ( int i = 0; i < FLOAT_COUNT; ++i )
      mFloatData[i] = 0.0;
}

}//namespace data

}//namespace cpu
