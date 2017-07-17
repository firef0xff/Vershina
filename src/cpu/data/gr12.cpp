#include "gr12.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{

wchar_t const* Gr12Pos1AdressesA[ GR12::ITEMS_COUNT ]=
{
   // Коэффициент коррекции прямой ход
   L"S7:[S7 connection_4]DB71,REAL180", L"S7:[S7 connection_4]DB71,REAL188",
   L"S7:[S7 connection_4]DB71,REAL196", L"S7:[S7 connection_4]DB71,REAL204",
   L"S7:[S7 connection_4]DB71,REAL212", L"S7:[S7 connection_4]DB71,REAL2",
   L"S7:[S7 connection_4]DB71,REAL10", L"S7:[S7 connection_4]DB71,REAL18",
   L"S7:[S7 connection_4]DB71,REAL26", L"S7:[S7 connection_4]DB71,REAL34",
   L"S7:[S7 connection_4]DB71,REAL42", L"S7:[S7 connection_4]DB71,REAL50",
   L"S7:[S7 connection_4]DB71,REAL58", L"S7:[S7 connection_4]DB71,REAL66",
   L"S7:[S7 connection_4]DB71,REAL74", L"S7:[S7 connection_4]DB71,REAL260",
   L"S7:[S7 connection_4]DB71,REAL268", L"S7:[S7 connection_4]DB71,REAL276",
   L"S7:[S7 connection_4]DB71,REAL284", L"S7:[S7 connection_4]DB71,REAL292",

   // Коэффициент коррекции обратный ход
   L"S7:[S7 connection_4]DB71,REAL300", L"S7:[S7 connection_4]DB71,REAL308",
   L"S7:[S7 connection_4]DB71,REAL316", L"S7:[S7 connection_4]DB71,REAL324",
   L"S7:[S7 connection_4]DB71,REAL332", L"S7:[S7 connection_4]DB71,REAL100",
   L"S7:[S7 connection_4]DB71,REAL108", L"S7:[S7 connection_4]DB71,REAL116",
   L"S7:[S7 connection_4]DB71,REAL124", L"S7:[S7 connection_4]DB71,REAL132",
   L"S7:[S7 connection_4]DB71,REAL140", L"S7:[S7 connection_4]DB71,REAL148",
   L"S7:[S7 connection_4]DB71,REAL156", L"S7:[S7 connection_4]DB71,REAL164",
   L"S7:[S7 connection_4]DB71,REAL172", L"S7:[S7 connection_4]DB71,REAL220",
   L"S7:[S7 connection_4]DB71,REAL228", L"S7:[S7 connection_4]DB71,REAL236",
   L"S7:[S7 connection_4]DB71,REAL244", L"S7:[S7 connection_4]DB71,REAL252"
};
wchar_t const* Gr12Pos1NameA = L"Gr12Pos1A";

wchar_t const* Gr12Pos1AdressesQ[ GR12::ITEMS_COUNT ] =
{
   // Граница действия прямой ход
   L"S7:[S7 connection_4]DB71,REAL184", L"S7:[S7 connection_4]DB71,REAL192",
   L"S7:[S7 connection_4]DB71,REAL200", L"S7:[S7 connection_4]DB71,REAL208",
   L"S7:[S7 connection_4]DB71,REAL216", L"S7:[S7 connection_4]DB71,REAL6",
   L"S7:[S7 connection_4]DB71,REAL14", L"S7:[S7 connection_4]DB71,REAL22",
   L"S7:[S7 connection_4]DB71,REAL30", L"S7:[S7 connection_4]DB71,REAL38",
   L"S7:[S7 connection_4]DB71,REAL46", L"S7:[S7 connection_4]DB71,REAL54",
   L"S7:[S7 connection_4]DB71,REAL62", L"S7:[S7 connection_4]DB71,REAL70",
   L"S7:[S7 connection_4]DB71,REAL78", L"S7:[S7 connection_4]DB71,REAL264",
   L"S7:[S7 connection_4]DB71,REAL272", L"S7:[S7 connection_4]DB71,REAL280",
   L"S7:[S7 connection_4]DB71,REAL288", L"S7:[S7 connection_4]DB71,REAL296",

   // Граница действия обратный ход
   L"S7:[S7 connection_4]DB71,REAL304", L"S7:[S7 connection_4]DB71,REAL312",
   L"S7:[S7 connection_4]DB71,REAL320", L"S7:[S7 connection_4]DB71,REAL328",
   L"S7:[S7 connection_4]DB71,REAL336", L"S7:[S7 connection_4]DB71,REAL104",
   L"S7:[S7 connection_4]DB71,REAL112", L"S7:[S7 connection_4]DB71,REAL120",
   L"S7:[S7 connection_4]DB71,REAL128", L"S7:[S7 connection_4]DB71,REAL136",
   L"S7:[S7 connection_4]DB71,REAL144", L"S7:[S7 connection_4]DB71,REAL152",
   L"S7:[S7 connection_4]DB71,REAL160", L"S7:[S7 connection_4]DB71,REAL168",
   L"S7:[S7 connection_4]DB71,REAL176", L"S7:[S7 connection_4]DB71,REAL224",
   L"S7:[S7 connection_4]DB71,REAL232", L"S7:[S7 connection_4]DB71,REAL240",
   L"S7:[S7 connection_4]DB71,REAL248", L"S7:[S7 connection_4]DB71,REAL256"
};
wchar_t const* Gr12Pos1NameQ = L"Gr12Pos1Q";




GR12::GR12(const wchar_t *group_a_name, const wchar_t *a_addresses[],
           const wchar_t *group_q_name, const wchar_t *q_addresses[])
{
    memset( A, 0, sizeof(A) );
    memset( Q, 0, sizeof(Q) );
    mAGroupID = opc::miniOPC::Instance().AddGroup( group_a_name, a_addresses, ITEMS_COUNT );
    mQGroupID = opc::miniOPC::Instance().AddGroup( group_q_name, q_addresses, ITEMS_COUNT );
}

bool GR12::Read()
{
   OPCITEMSTATE* rez = opc::miniOPC::Instance().Read( mAGroupID );
   if (!rez)//ошибка подключения..
      return false;
   for (size_t i = 0; i < ITEMS_COUNT; i++)
      A[ i ] = rez[i].vDataValue.fltVal;
   opc::miniOPC::Instance().OpcMassFree( mAGroupID, rez );


   rez = opc::miniOPC::Instance().Read( mQGroupID );
   if (!rez)//ошибка подключения..
      return false;
   for (size_t i = 0; i < ITEMS_COUNT; i++)
      Q[ i ] = rez[i].vDataValue.fltVal;
   opc::miniOPC::Instance().OpcMassFree( mQGroupID, rez );

   return true;
}

void GR12::Write()
{
   HRESULT res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mAGroupID, 0, ITEMS_COUNT, static_cast<void*>( A ), opc::tFLOAT );

   res = E_FAIL;
   while ( res == E_FAIL )
      res = opc::miniOPC::Instance().WriteMass( mQGroupID, 0, ITEMS_COUNT, static_cast<void*>( Q ), opc::tFLOAT );
}

}
}
