#include "gr1.h"
#include "miniOPC.h"
#include <memory.h>
namespace cpu
{

namespace data
{

GR1::GR1()
{
   memset( mBoolData, 0, sizeof(mBoolData) );
   memset( mIntData, 0, sizeof(mIntData) );
   memset( mFloatData, 0, sizeof(mFloatData) );
   mGroupID = opc::miniOPC::Instance().AddGroup( L"GR1", mAdresses, BOOL_COUNT + INT_COUNT + FLOAT_COUNT );
}

void GR1::Write()
{
   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, 0, BOOL_COUNT, static_cast<void*>( mBoolData ), opc::tBOOL );

   res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, BOOL_COUNT, INT_COUNT, static_cast<void*>( mIntData ), opc::tFLOAT );

   res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mGroupID, BOOL_COUNT + INT_COUNT, FLOAT_COUNT, static_cast<void*>( mFloatData ), opc::tFLOAT );
}

void GR1::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mGroupID );
   if (!rez) //ошибка подключения..
      return;
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
