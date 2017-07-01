// ---------------------------------------------------------------------------

#ifndef opcrwH
#define opcrwH
#include "def.h"
#include "opc.h"

// ---------------------------------------------------------------------------
class OPCRW
{
public:
   __fastcall OPCRW(void); // конструктор
   int __fastcall ReadGr3(void); // чтение переменных группы 3
   int __fastcall ReadGr4(void); // чтение переменных группы 4
   int __fastcall ReadGr5(void); // чтение переменных группы 5
   int __fastcall ReadGr6(void); // чтение переменных группы 6
   int __fastcall ReadGr7(void); // чтение переменных группы 7
   int __fastcall ReadGr8(void); // чтение переменных группы 8
   int __fastcall ReadGr9(void); // чтение переменных группы 9
   int __fastcall ReadGr10(void); // чтение переменных группы 10
   int __fastcall ReadGr11(void); // чтение переменных группы 11
   int __fastcall ReadGr12(void); // чтение переменных группы 12
   int __fastcall ReadGr13(void); // чтение переменных группы 13
   int __fastcall WriteGr3(int *); // запись целой переменной группы 3
   int __fastcall WriteGr3(float *); // запись вещественной переменной группы 3
   int __fastcall WriteGr4(void); // запись вещественных массивов группы 4
   int __fastcall WriteGr5(void); // запись целых массивов группы 5
   int __fastcall WriteGr6(void); // запись вещественного массива группы 6
   int __fastcall ResetGr7(void); // сброс значений для переменных группый 7
   int __fastcall WriteGr8(void); // запись вещественных массивов группы 8
   int __fastcall WriteGr9(void); // запись целых массивов группы 9
   int __fastcall WriteGr10(void); // запись вещественного массива группы 10
   int __fastcall ResetGr11(void); // сброс значений для переменных группый 11
   int __fastcall WriteGr12(void); // запись вещественного массива группы 12
   int __fastcall WriteGr13(void); // запись вещественного массива группы 13
   int __fastcall TestParamWrite( // запись параметров цикла испытаний
      float *pS, // переменная типа float из группы 3
      int *piw1, // переменная типа int из группы 3
      int *piw2, // переменная типа int из группы 3
      int *piw3, // переменная типа int из группы 3
      int *piw4); // переменная типа int из группы 3

   int __fastcall ReadCycleParameters(void); // чтение циклических параметров

private:
   IOPCServer *pIOPCServer; // указатель на OPC-сервер
   IOPCItemMgt // указатели на группы
      *pIOPCItemMgt3, *pIOPCItemMgt4, *pIOPCItemMgt5,
      *pIOPCItemMgt6, *pIOPCItemMgt7, *pIOPCItemMgt8, *pIOPCItemMgt9,
      *pIOPCItemMgt10, *pIOPCItemMgt11, *pIOPCItemMgt12, *pIOPCItemMgt13;
   IOPCSyncIO // указатели на интерфейсы ввода/вывода
      *pIOPCSyncIO3, *pIOPCSyncIO4, *pIOPCSyncIO5, *pIOPCSyncIO6,
      *pIOPCSyncIO7, *pIOPCSyncIO8, *pIOPCSyncIO9, *pIOPCSyncIO10,
      *pIOPCSyncIO11, *pIOPCSyncIO12, *pIOPCSyncIO13;
   OPCITEMDEF// эелементы в группах
      ItemsGr3[GR3ITEMSNUM], ItemsGr4[GR4ITEMSNUM],
      ItemsGr5[GR5ITEMSNUM], ItemsGr6[GR6ITEMSNUM], ItemsGr7[GR7ARRAYSNUM],
      ItemsGr8[GR8ITEMSNUM], ItemsGr9[GR9ITEMSNUM], ItemsGr10[GR10ITEMSNUM],
      ItemsGr11[GR11ARRAYSNUM], ItemsGr12[GR12ITEMSNUM],
      ItemsGr13[GR13ITEMSNUM];
   OPCITEMRESULT // указатели на элементы
      *pItemResult3, *pItemResult4, *pItemResult5, *pItemResult6,
      *pItemResult7, *pItemResult8, *pItemResult9, *pItemResult10,
      *pItemResult11, *pItemResult12, *pItemResult13;
   OPCHANDLE GrpSrvHandle;
   HRESULT *pErrors, *pRErrors, r1;
   UINT qnr;

   wchar_t *pServerName;
   wchar_t *pGr3Name, *pGr4Name, *pGr5Name, *pGr6Name,
      *pGr7Name, *pGr8Name, *pGr9Name, *pGr10Name, *pGr11Name, *pGr12Name,
      *pGr13Name;
   _GUID clsid;
   long TimeBias;
   float PercentDeadband;
   DWORD RevisedUpdateRate;
   LPWSTR ErrorStr;
};
#endif
