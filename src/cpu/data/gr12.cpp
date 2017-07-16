#include "gr12.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{
GR12::GR12()
{
    memset( A1, 0, sizeof(A1) );
    memset( Q1, 0, sizeof(Q1) );
    mAGroupID = opc::miniOPC::Instance().AddGroup( L"GR12A", mAdressesA, ITEMS_COUNT );
    mQGroupID = opc::miniOPC::Instance().AddGroup( L"GR12Q", mAdressesQ, ITEMS_COUNT );
}

bool GR12::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mAGroupID );
   if (!rez)//ошибка подключения..
      return false;
   for (size_t i = 0; i < ITEMS_COUNT; i++)
      A1[ i ] = rez[i].vDataValue.fltVal;
   opc::miniOPC::Instance().OpcMassFree( mAGroupID, rez );


   rez = opc::miniOPC::Instance().Read( mQGroupID );
   if (!rez)//ошибка подключения..
      return false;
   for (size_t i = 0; i < ITEMS_COUNT; i++)
      Q1[ i ] = rez[i].vDataValue.fltVal;
   opc::miniOPC::Instance().OpcMassFree( mQGroupID, rez );

   return true;
}

void GR12::Write()
{
   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mAGroupID, 0, ITEMS_COUNT, static_cast<void*>( A1 ), opc::tFLOAT );

   res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mQGroupID, 0, ITEMS_COUNT, static_cast<void*>( Q1 ), opc::tFLOAT );
}

}
}
