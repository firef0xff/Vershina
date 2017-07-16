#include "gr13.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{
GR13::GR13()
{
    memset( A2, 0, sizeof(A2) );
    memset( Q2, 0, sizeof(Q2) );
    mAGroupID = opc::miniOPC::Instance().AddGroup( L"GR13A", mAdressesA, ITEMS_COUNT );
    mQGroupID = opc::miniOPC::Instance().AddGroup( L"GR13Q", mAdressesQ, ITEMS_COUNT );
}

bool GR13::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mAGroupID );
   if (!rez)//ошибка подключения..
      return false;
   for (size_t i = 0; i < ITEMS_COUNT; i++)
      A2[ i ] = rez[i].vDataValue.fltVal;
   opc::miniOPC::Instance().OpcMassFree( mAGroupID, rez );


   rez = opc::miniOPC::Instance().Read( mQGroupID );
   if (!rez)//ошибка подключения..
      return false;
   for (size_t i = 0; i < ITEMS_COUNT; i++)
      Q2[ i ] = rez[i].vDataValue.fltVal;
   opc::miniOPC::Instance().OpcMassFree( mQGroupID, rez );

   return true;
}

void GR13::Write()
{
   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mAGroupID, 0, ITEMS_COUNT, static_cast<void*>( A2 ), opc::tFLOAT );

   res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mQGroupID, 0, ITEMS_COUNT, static_cast<void*>( Q2 ), opc::tFLOAT );
}

}
}
