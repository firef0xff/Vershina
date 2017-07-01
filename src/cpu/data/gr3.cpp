#include "gr3.h"
#include "miniOPC.h"
#include <memory.h>
namespace cpu
{

namespace data
{

GR3::GR3()
{
   memset( mIntData, 0, sizeof(mIntData) );
   memset( mFloatData, 0, sizeof(mFloatData) );
   mGroupID = opc::miniOPC::Instance().AddGroup( L"GR2", mAdresses, INT_COUNT + FLOAT_COUNT );
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
