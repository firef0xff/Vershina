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
   int __fastcall ResetGr7(void); // сброс значений для переменных группый 7
   int __fastcall ResetGr11(void); // сброс значений для переменных группый 11
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
      *pIOPCItemMgt7, *pIOPCItemMgt11;
   IOPCSyncIO // указатели на интерфейсы ввода/вывода
      *pIOPCSyncIO7, *pIOPCSyncIO11;
   OPCITEMDEF// эелементы в группах
      ItemsGr7[GR7ARRAYSNUM], ItemsGr11[GR11ARRAYSNUM];
   OPCITEMRESULT // указатели на элементы
      *pItemResult7, *pItemResult11;
   OPCHANDLE GrpSrvHandle;
   HRESULT *pErrors, *pRErrors, r1;
   UINT qnr;

   wchar_t *pServerName;
   wchar_t *pGr7Name, *pGr11Name;
   _GUID clsid;
   long TimeBias;
   float PercentDeadband;
   DWORD RevisedUpdateRate;
   LPWSTR ErrorStr;
};
#endif
