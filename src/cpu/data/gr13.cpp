#include "gr13.h"

#include "miniOPC.h"
#include "memory.h"

namespace cpu
{
namespace data
{
extern wchar_t const* Gr12Pos2AdressesA[ GR12::ITEMS_COUNT ] =
{
   // Коэффициент коррекции прямой ход
   L"S7:[S7 connection_4]DB70,REAL180", L"S7:[S7 connection_4]DB70,REAL188",
   L"S7:[S7 connection_4]DB70,REAL196", L"S7:[S7 connection_4]DB70,REAL204",
   L"S7:[S7 connection_4]DB70,REAL212", L"S7:[S7 connection_4]DB70,REAL2",
   L"S7:[S7 connection_4]DB70,REAL10", L"S7:[S7 connection_4]DB70,REAL18",
   L"S7:[S7 connection_4]DB70,REAL26", L"S7:[S7 connection_4]DB70,REAL34",
   L"S7:[S7 connection_4]DB70,REAL42", L"S7:[S7 connection_4]DB70,REAL50",
   L"S7:[S7 connection_4]DB70,REAL58", L"S7:[S7 connection_4]DB70,REAL66",
   L"S7:[S7 connection_4]DB70,REAL74", L"S7:[S7 connection_4]DB70,REAL260",
   L"S7:[S7 connection_4]DB70,REAL268", L"S7:[S7 connection_4]DB70,REAL276",
   L"S7:[S7 connection_4]DB70,REAL284", L"S7:[S7 connection_4]DB70,REAL292",

   // Коэффициент коррекции обратный ход

   L"S7:[S7 connection_4]DB70,REAL300", L"S7:[S7 connection_4]DB70,REAL308",
   L"S7:[S7 connection_4]DB70,REAL316", L"S7:[S7 connection_4]DB70,REAL324",
   L"S7:[S7 connection_4]DB70,REAL332", L"S7:[S7 connection_4]DB70,REAL100",
   L"S7:[S7 connection_4]DB70,REAL108", L"S7:[S7 connection_4]DB70,REAL116",
   L"S7:[S7 connection_4]DB70,REAL124", L"S7:[S7 connection_4]DB70,REAL132",
   L"S7:[S7 connection_4]DB70,REAL140", L"S7:[S7 connection_4]DB70,REAL148",
   L"S7:[S7 connection_4]DB70,REAL156", L"S7:[S7 connection_4]DB70,REAL164",
   L"S7:[S7 connection_4]DB70,REAL172", L"S7:[S7 connection_4]DB70,REAL220",
   L"S7:[S7 connection_4]DB70,REAL228", L"S7:[S7 connection_4]DB70,REAL236",
   L"S7:[S7 connection_4]DB70,REAL244", L"S7:[S7 connection_4]DB70,REAL252"
};
extern wchar_t const* Gr12Pos2NameA = L"Gr12Pos2A";

extern wchar_t const* Gr12Pos2AdressesQ[ GR12::ITEMS_COUNT ]=
{
   // Граница действия прямой ход
   L"S7:[S7 connection_4]DB70,REAL184", L"S7:[S7 connection_4]DB70,REAL192",
   L"S7:[S7 connection_4]DB70,REAL200", L"S7:[S7 connection_4]DB70,REAL208",
   L"S7:[S7 connection_4]DB70,REAL216", L"S7:[S7 connection_4]DB70,REAL6",
   L"S7:[S7 connection_4]DB70,REAL14", L"S7:[S7 connection_4]DB70,REAL22",
   L"S7:[S7 connection_4]DB70,REAL30", L"S7:[S7 connection_4]DB70,REAL38",
   L"S7:[S7 connection_4]DB70,REAL46", L"S7:[S7 connection_4]DB70,REAL54",
   L"S7:[S7 connection_4]DB70,REAL62", L"S7:[S7 connection_4]DB70,REAL70",
   L"S7:[S7 connection_4]DB70,REAL78", L"S7:[S7 connection_4]DB70,REAL264",
   L"S7:[S7 connection_4]DB70,REAL272", L"S7:[S7 connection_4]DB70,REAL280",
   L"S7:[S7 connection_4]DB70,REAL288", L"S7:[S7 connection_4]DB70,REAL296",

   // Граница действия обратный ход

   L"S7:[S7 connection_4]DB70,REAL304", L"S7:[S7 connection_4]DB70,REAL312",
   L"S7:[S7 connection_4]DB70,REAL320", L"S7:[S7 connection_4]DB70,REAL328",
   L"S7:[S7 connection_4]DB70,REAL336", L"S7:[S7 connection_4]DB70,REAL104",
   L"S7:[S7 connection_4]DB70,REAL112", L"S7:[S7 connection_4]DB70,REAL120",
   L"S7:[S7 connection_4]DB70,REAL128", L"S7:[S7 connection_4]DB70,REAL136",
   L"S7:[S7 connection_4]DB70,REAL144", L"S7:[S7 connection_4]DB70,REAL152",
   L"S7:[S7 connection_4]DB70,REAL160", L"S7:[S7 connection_4]DB70,REAL168",
   L"S7:[S7 connection_4]DB70,REAL176", L"S7:[S7 connection_4]DB70,REAL224",
   L"S7:[S7 connection_4]DB70,REAL232", L"S7:[S7 connection_4]DB70,REAL240",
   L"S7:[S7 connection_4]DB70,REAL248", L"S7:[S7 connection_4]DB70,REAL256"
};
extern wchar_t const* Gr12Pos2NameQ = L"Gr12Pos2Q";


}
}
