#include "gr1.h"
#include "miniOPC.h"
#include <memory.h>
namespace cpu
{

namespace data
{

wchar_t const* Gr1Pos1Adresses[ GR1::BOOL_COUNT + GR1::INT_COUNT + GR1::FLOAT_COUNT] =
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

   //int
   L"S7:[S7 connection_4]DB20,DINT26",
   L"S7:[S7 connection_4]DB20,DINT38",
   L"S7:[S7 connection_4]DB20,DINT42",
   L"S7:[S7 connection_4]DB20,DINT148",
   L"S7:[S7 connection_4]DB20,DINT180",

   //float
   L"S7:[S7 connection_4]DB10,REAL26",
   L"S7:[S7 connection_4]DB10,REAL142",
   L"S7:[S7 connection_4]DB10,REAL146",
   L"S7:[S7 connection_4]DB10,REAL158",
   L"S7:[S7 connection_4]DB10,REAL162",
};
wchar_t const* Gr1Pos2Adresses[ GR1::BOOL_COUNT + GR1::INT_COUNT + GR1::FLOAT_COUNT] =
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

   //int
   L"S7:[S7 connection_4]DB20,DINT66",
   L"S7:[S7 connection_4]DB20,DINT78",
   L"S7:[S7 connection_4]DB20,DINT82",
   L"S7:[S7 connection_4]DB20,DINT152",
   L"S7:[S7 connection_4]DB20,DINT184",

   //float
   L"S7:[S7 connection_4]DB10,REAL62",
   L"S7:[S7 connection_4]DB10,REAL150",
   L"S7:[S7 connection_4]DB10,REAL154",
   L"S7:[S7 connection_4]DB10,REAL166",
   L"S7:[S7 connection_4]DB10,REAL170"
};

wchar_t const* Gr1Pos1Name = L"Gr1Pos1";
wchar_t const* Gr1Pos2Name = L"Gr1Pos2";

GR1::GR1(const wchar_t* group_name, const wchar_t *addresses[] )
{
   memset( mBoolData, 0, sizeof(mBoolData) );
   memset( mIntData, 0, sizeof(mIntData) );
   memset( mFloatData, 0, sizeof(mFloatData) );
   mGroupID = opc::miniOPC::Instance().AddGroup( group_name, addresses, BOOL_COUNT + INT_COUNT + FLOAT_COUNT );
}

void GR1::Write()
{
   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, BOOL_COUNT, static_cast<void*>( mBoolData ), opc::tBOOL );

   res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, BOOL_COUNT, INT_COUNT, static_cast<void*>( mIntData ), opc::tINT );

   res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, BOOL_COUNT + INT_COUNT, FLOAT_COUNT, static_cast<void*>( mFloatData ), opc::tFLOAT );
}

bool GR1::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez) //ошибка подключения..
      return false;
   for (size_t i = 0; i < BOOL_COUNT + INT_COUNT + FLOAT_COUNT; i++)
   {
      if ( i < BOOL_COUNT )
         mBoolData[ i ] = rez[i].vDataValue.boolVal;
      else if ( i < BOOL_COUNT + INT_COUNT )
         mIntData[ i - BOOL_COUNT ] = rez[i].vDataValue.lVal;
      else
         mFloatData[ i - BOOL_COUNT - INT_COUNT ] = rez[i].vDataValue.fltVal;
   }
   opc::miniOPC::Instance().OpcMassFree( mGroupID, rez );
   return true;
}

void GR1::Clear()
{
   for ( int i = 0; i < BOOL_COUNT; ++i )
      mBoolData[i] = false;
   for ( int i = 0; i < INT_COUNT; ++i )
      mIntData[i] = 0;
   for ( int i = 0; i < FLOAT_COUNT; ++i )
      mFloatData[i] = 0.0;
}

}//namespace data

}//namespace cpu
