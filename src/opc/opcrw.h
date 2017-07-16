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
   int __fastcall ReadGr7(void); // чтение переменных группы 7
   int __fastcall ReadGr11(void); // чтение переменных группы 11
   int __fastcall ReadGr12(void); // чтение переменных группы 12
   int __fastcall ReadGr13(void); // чтение переменных группы 13
   int __fastcall ResetGr7(void); // сброс значений для переменных группый 7
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
      *pIOPCItemMgt7, *pIOPCItemMgt11, *pIOPCItemMgt12, *pIOPCItemMgt13;
   IOPCSyncIO // указатели на интерфейсы ввода/вывода
      *pIOPCSyncIO7, *pIOPCSyncIO11, *pIOPCSyncIO12, *pIOPCSyncIO13;
   OPCITEMDEF// эелементы в группах
      ItemsGr7[GR7ARRAYSNUM], ItemsGr11[GR11ARRAYSNUM], ItemsGr12[GR12ITEMSNUM],
      ItemsGr13[GR13ITEMSNUM];
   OPCITEMRESULT // указатели на элементы
      *pItemResult7, *pItemResult11, *pItemResult12, *pItemResult13;
   OPCHANDLE GrpSrvHandle;
   HRESULT *pErrors, *pRErrors, r1;
   UINT qnr;

   wchar_t *pServerName;
   wchar_t *pGr7Name, *pGr11Name, *pGr12Name,
      *pGr13Name;
   _GUID clsid;
   long TimeBias;
   float PercentDeadband;
   DWORD RevisedUpdateRate;
   LPWSTR ErrorStr;
};
#endif
