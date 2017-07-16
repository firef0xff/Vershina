// ---------------------------------------------------------------------------

#pragma hdrstop
//// Used by GetErrorString; Language code ////
#define LOCALE_ID    0x409	// Code 0x409 = ENGLISH
#include "def.h"
// #define GR1ITEMSNUM  6     // количество переменных в группе 1
#include "Common.h"
#include "opcrw.h"
#include <vector>
#include "cpu_memory.h"

#pragma package(smart_init)

__fastcall OPCRW::OPCRW(void) // конструктор
{
   pServerName = L"OPC.SimaticNET";
   pGr7Name = L"Gr7DB1_6";
   pGr11Name = L"Gr11DB11_16";
   TimeBias = 0;
   PercentDeadband = 0.0;
   String wsStr = "";

   OPCConnectOK = false;
   r1 = CoInitialize(NULL);
   LogPrint("Подключение к OPC-серверу", clLime);
   // получение идентификатора класса по имени сервера
   if (CLSIDFromProgID(pServerName, &clsid) != S_OK)
   {
      LogPrint("OPC-сервер не найден!", clRed);
      return;
   }
   LogPrint("Найден OPC-сервер: \"" + String(pServerName) + "\"", clWhite);
   // получение адреса сервера
   if (CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IOPCServer,
      (void**)&pIOPCServer) != S_OK)
   {
      LogPrint("Ошибка при подключении к OPC-серверу!", clRed);
      return;
   }
   LogPrint("Подключено к OPC-серверу \"" + String(pServerName) + "\"",
      clWhite);
   // создание OPC-группы 7
   r1 = pIOPCServer->AddGroup(pGr7Name, true, 500, 7, &TimeBias,
      &PercentDeadband, LOCALE_ID, &GrpSrvHandle, &RevisedUpdateRate,
      IID_IOPCItemMgt, (LPUNKNOWN*)&pIOPCItemMgt7);
   if (r1 == S_OK)
   {
      // LogPrint("Добавлена группа \""+String(pGr7Name)+"\"",clWhite);
   }
   else
   {
      LogPrint("Ошибка при добавлении группы к серверу", clRed);
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // define an item table with items as in-paramter for AddItem
   for (int i = 0; i < GR7ARRAYSNUM; i++)
   {
      ItemsGr7[i].szAccessPath = L"";
      ItemsGr7[i].szItemID = Gr7ItemsNme[i];
      ItemsGr7[i].bActive = TRUE;
      ItemsGr7[i].hClient = 1;
      ItemsGr7[i].dwBlobSize = 0;
      ItemsGr7[i].pBlob = NULL;
      ItemsGr7[i].vtRequestedDataType = 0;
   }
   r1 = pIOPCItemMgt7->AddItems(GR7ARRAYSNUM, ItemsGr7, &pItemResult7,
      &pErrors);
   if (r1 == S_OK || r1 == S_FALSE)
   {
      // LogPrint("Добавлены переменные группы 7 - массивы в блоках DB1-6",clWhite);
   }
   else
   {
      pIOPCServer->GetErrorString(pErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Ошибка при добавлении переменных группы 7: " +
         String(ErrorStr), clRed);
      CoTaskMemFree(ErrorStr);
      pIOPCItemMgt7->Release();
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // query interface for sync calls on group object
   r1 = pIOPCItemMgt7->QueryInterface(IID_IOPCSyncIO, (void**)&pIOPCSyncIO7);
   if (r1 >= 0)
   {
      LogPrint("Получен указатель на IOPCSyncIO7 для переменных группы \"" +
         String(pGr7Name) + "\"", clWhite);
   }
   else
   {
      LogPrint("Ошибка при получении указателя на IOPCSyncIO7", clRed);
      CoTaskMemFree(pItemResult7);
      pIOPCItemMgt7->Release();
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // создание OPC-группы 11
   r1 = pIOPCServer->AddGroup(pGr11Name, true, 500, 11, &TimeBias,
      &PercentDeadband, LOCALE_ID, &GrpSrvHandle, &RevisedUpdateRate,
      IID_IOPCItemMgt, (LPUNKNOWN*)&pIOPCItemMgt11);
   if (r1 == S_OK)
   {
      // LogPrint("Добавлена группа \""+String(pGr11Name)+"\"",clWhite);
      // LogPrint("RevisedUpdateRate="+String((unsigned int)RevisedUpdateRate),clFuchsia);//------
   }
   else
   {
      LogPrint("Ошибка при добавлении группы к серверу", clRed);
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // define an item table with items as in-paramter for AddItem
   for (int i = 0; i < GR11ARRAYSNUM; i++)
   {
      ItemsGr11[i].szAccessPath = L"";
      ItemsGr11[i].szItemID = Gr11ItemsNme[i];
      ItemsGr11[i].bActive = TRUE;
      ItemsGr11[i].hClient = 1;
      ItemsGr11[i].dwBlobSize = 0;
      ItemsGr11[i].pBlob = NULL;
      ItemsGr11[i].vtRequestedDataType = 0;
   }
   r1 = pIOPCItemMgt11->AddItems(GR11ARRAYSNUM, ItemsGr11, &pItemResult11,
      &pErrors);
   if (r1 == S_OK || r1 == S_FALSE)
   {
      // LogPrint("Добавлены переменные группы 11 - массивы в блоках DB11-16",clWhite);
   }
   else
   {
      pIOPCServer->GetErrorString(pErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Ошибка при добавлении переменных группы 11: " +
         String(ErrorStr), clRed);
      CoTaskMemFree(ErrorStr);
      pIOPCItemMgt11->Release();
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // query interface for sync calls on group object
   r1 = pIOPCItemMgt11->QueryInterface(IID_IOPCSyncIO, (void**)&pIOPCSyncIO11);
   if (r1 >= 0)
   {
      LogPrint("Получен указатель на IOPCSyncIO11 для переменных группы \"" +
         String(pGr11Name) + "\"", clWhite);
   }
   else
   {
      LogPrint("Ошибка при получении указателя на IOPCSyncIO11", clRed);
      CoTaskMemFree(pItemResult11);
      pIOPCItemMgt11->Release();
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }

   LogPrint("Соединение со стендом установлено", clAqua);
   OPCConnectOK = true;
}
// ---- End of Constructor ---------------------------------------------------

int __fastcall OPCRW::ReadGr7(void) // чтение переменных группы 7
{
#ifdef _mDEBUG
   return 1;
#endif

   OPCITEMSTATE *pItemValue;
   LPWSTR ErrorStr;
   UINT qnr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR7ARRAYSNUM);

   for (int i = 0; i < GR7ARRAYSNUM; i++)
   {
      phServer[i] = pItemResult7[i].hServer;
   }

   r1 = pIOPCSyncIO7->Read(OPC_DS_CACHE, GR7ARRAYSNUM, &(*phServer.begin()),
      &pItemValue, &pRErrors);

   if (r1 == S_OK)
   {
      if (pItemValue[0].vDataValue.vt == (VT_ARRAY | VT_I4))
      { // целый массив из блока DB1
         int *pValues = NULL;
         SafeArrayAccessData(pItemValue[0].vDataValue.parray,
            (void **)&pValues);
         for (int i = 0; i < MAXNUMOFPOLLS; i++)
         {
            read_TA[i] = pValues[i];
         }
         LogPrint("Read7,DB1: read_TA[1] is: " + String(read_TA[0]), clTeal);
         SafeArrayUnaccessData(pItemValue[0].vDataValue.parray);
      }
      if (pItemValue[1].vDataValue.vt == (VT_ARRAY | VT_R4))
      { // вещественный массив из блока DB2
         float *pValues = NULL;
         SafeArrayAccessData(pItemValue[1].vDataValue.parray,
            (void **)&pValues);
         for (int i = 0; i < MAXNUMOFPOLLS; i++)
         {
            read_VA[i] = pValues[i];
         }
         LogPrint("Read7,DB2: read_VA[1] is: " + FloatToStr(read_VA[0]),
            clTeal);
         SafeArrayUnaccessData(pItemValue[1].vDataValue.parray);
      }
      if (pItemValue[2].vDataValue.vt == (VT_ARRAY | VT_R4))
      { // вещественный массив из блока DB3
         float *pValues = NULL;
         SafeArrayAccessData(pItemValue[2].vDataValue.parray,
            (void **)&pValues);
         for (int i = 0; i < MAXNUMOFPOLLS; i++)
         {
            read_SA[i] = pValues[i];
         }
         LogPrint("Read7,DB3: read_SA[1] is: " + FloatToStr(read_SA[0]),
            clTeal);
         SafeArrayUnaccessData(pItemValue[2].vDataValue.parray);
      }
      if (pItemValue[3].vDataValue.vt == (VT_ARRAY | VT_R4))
      { // вещественный массив из блока DB4
         float *pValues = NULL;
         SafeArrayAccessData(pItemValue[3].vDataValue.parray,
            (void **)&pValues);
         for (int i = 0; i < MAXNUMOFPOLLS; i++)
         {
            read_LA[i] = pValues[i];
         }
         LogPrint("Read7,DB4: read_LA[1] is: " + FloatToStr(read_LA[0]),
            clTeal);
         SafeArrayUnaccessData(pItemValue[3].vDataValue.parray);
      }
      if (pItemValue[4].vDataValue.vt == (VT_ARRAY | VT_R4))
      { // вещественный массив из блока DB5
         float *pValues = NULL;
         SafeArrayAccessData(pItemValue[4].vDataValue.parray,
            (void **)&pValues);
         for (int i = 0; i < MAXNUMOFPOLLS; i++)
         {
            read_RA[i] = pValues[i];
         }
         LogPrint("Read7,DB5: read_RA[1] is: " + FloatToStr(read_RA[0]),
            clTeal);
         SafeArrayUnaccessData(pItemValue[4].vDataValue.parray);
      }
      if (pItemValue[5].vDataValue.vt == (VT_ARRAY | VT_R4))
      { // вещественный массив из блока DB6
         float *pValues = NULL;
         SafeArrayAccessData(pItemValue[5].vDataValue.parray,
            (void **)&pValues);
         for (int i = 0; i < MAXNUMOFPOLLS; i++)
         {
            read_TempA[i] = pValues[i];
         }
         LogPrint("Read7,DB5: read_TempA[1] is: " + FloatToStr(read_TempA[0]),
            clTeal);
         SafeArrayUnaccessData(pItemValue[5].vDataValue.parray);
      }
      // release out-parameters in case of not failed
      for (int i = 0; i < GR7ARRAYSNUM; i++)
         VariantClear(&pItemValue[i].vDataValue);
      CoTaskMemFree(pItemValue);

      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pRErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Read: Group 7 item reading error: " + String(ErrorStr), clRed);

      CoTaskMemFree(ErrorStr);
      return 0;
   }
}
// ---- End of ReadGr7 -------------------------------------------------------

int __fastcall OPCRW::ReadGr11(void) // чтение переменных группы 11
{
#ifdef _mDEBUG
   return 1;
#endif

   OPCITEMSTATE *pItemValue;
   LPWSTR ErrorStr;
   UINT qnr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR11ARRAYSNUM);

   for (int i = 0; i < GR11ARRAYSNUM; i++)
   {
      phServer[i] = pItemResult11[i].hServer;
   }
   r1 = pIOPCSyncIO11->Read(OPC_DS_CACHE, GR11ARRAYSNUM, &(*phServer.begin()),
      &pItemValue, &pRErrors);

   if (r1 == S_OK)
   {
      if (pItemValue[0].vDataValue.vt == (VT_ARRAY | VT_I4))
      { // целый массив из блока DB11
         int *pValues = NULL;
         SafeArrayAccessData(pItemValue[0].vDataValue.parray,
            (void **)&pValues);
         for (int i = 0; i < MAXNUMOFPOLLS; i++)
         {
            read_TB[i] = pValues[i];
         }
         LogPrint("Read11,DB11: read_TB[1] is: " + String(read_TB[0]),
            clTeal); // debug print
         SafeArrayUnaccessData(pItemValue[0].vDataValue.parray);
      }
      if (pItemValue[1].vDataValue.vt == (VT_ARRAY | VT_R4))
      { // вещественный массив из блока DB12
         float *pValues = NULL;
         SafeArrayAccessData(pItemValue[1].vDataValue.parray,
            (void **)&pValues);
         for (int i = 0; i < MAXNUMOFPOLLS; i++)
         {
            read_VB[i] = pValues[i];
         }
         LogPrint("Read11,DB12: read_VB[1] is: " + FloatToStr(read_VB[0]),
            clTeal); // debug print
         SafeArrayUnaccessData(pItemValue[1].vDataValue.parray);
      }
      if (pItemValue[2].vDataValue.vt == (VT_ARRAY | VT_R4))
      { // вещественный массив из блока DB13
         float *pValues = NULL;
         SafeArrayAccessData(pItemValue[2].vDataValue.parray,
            (void **)&pValues);
         for (int i = 0; i < MAXNUMOFPOLLS; i++)
         {
            read_SB[i] = pValues[i];
         }
         LogPrint("Read11,DB13: read_SB[1] is: " + FloatToStr(read_SB[0]),
            clTeal); // debug print
         SafeArrayUnaccessData(pItemValue[2].vDataValue.parray);
      }
      if (pItemValue[3].vDataValue.vt == (VT_ARRAY | VT_R4))
      { // вещественный массив из блока DB14
         float *pValues = NULL;
         SafeArrayAccessData(pItemValue[3].vDataValue.parray,
            (void **)&pValues);
         for (int i = 0; i < MAXNUMOFPOLLS; i++)
         {
            read_LB[i] = pValues[i];
         }
         LogPrint("Read11,DB14: read_LB[1] is: " + FloatToStr(read_LB[0]),
            clTeal); // debug print
         SafeArrayUnaccessData(pItemValue[3].vDataValue.parray);
      }
      if (pItemValue[4].vDataValue.vt == (VT_ARRAY | VT_R4))
      { // вещественный массив из блока DB15
         float *pValues = NULL;
         SafeArrayAccessData(pItemValue[4].vDataValue.parray,
            (void **)&pValues);
         for (int i = 0; i < MAXNUMOFPOLLS; i++)
         {
            read_RB[i] = pValues[i];
         }
         LogPrint("Read11,DB15: read_RB[1] is: " + FloatToStr(read_RB[0]),
            clTeal); // debug print
         SafeArrayUnaccessData(pItemValue[4].vDataValue.parray);
      }
      if (pItemValue[5].vDataValue.vt == (VT_ARRAY | VT_R4))
      { // вещественный массив из блока DB16
         float *pValues = NULL;
         SafeArrayAccessData(pItemValue[5].vDataValue.parray,
            (void **)&pValues);
         for (int i = 0; i < MAXNUMOFPOLLS; i++)
         {
            read_TempB[i] = pValues[i];
         }
         LogPrint("Read11,DB15: read_TempB[1] is: " + FloatToStr(read_TempB[0]),
            clTeal); // debug print
         SafeArrayUnaccessData(pItemValue[5].vDataValue.parray);
      }
      // release out-parameters in case of not failed
      for (int i = 0; i < GR11ARRAYSNUM; i++)
         VariantClear(&pItemValue[i].vDataValue);
      CoTaskMemFree(pItemValue);

      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pRErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Read: Group 11 item reading error: " + String(ErrorStr), clRed);

      CoTaskMemFree(ErrorStr);
      return 0;
   }
}
// ---- End of ReadGr11 ------------------------------------------------------

int __fastcall OPCRW::ResetGr7(void)
{
#ifdef _NO_Write
   return 1;
#endif

   VARIANT values[GR7ARRAYSNUM];
   HRESULT *pWErrors;
   LPWSTR ErrorStr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR7ARRAYSNUM);

   for (int i = 0; i < GR7ARRAYSNUM; ++i)
   {
      phServer[i] = pItemResult7[i].hServer;
   }

   values[0].vt = VT_ARRAY | VT_I4;
   values[0].parray = SafeArrayCreateVector(VT_I4, -1, GR7ARRAYSIZE);

   int *pValues0 = NULL;
   SafeArrayAccessData(values[0].parray, (void **)&pValues0);
   for (int i = 0; i < GR7ARRAYSIZE; i++)
   {
      pValues0[i] = i;
   }
   SafeArrayUnaccessData(values[0].parray);

   values[1].vt = VT_ARRAY | VT_R4;
   values[1].parray = SafeArrayCreateVector(VT_R4, -1, GR7ARRAYSIZE);

   float *pValues1 = NULL;
   SafeArrayAccessData(values[1].parray, (void **)&pValues1);
   for (int i = 0; i < GR7ARRAYSIZE; i++)
   {
      pValues1[i] = i;
   }
   SafeArrayUnaccessData(values[1].parray);

   values[2].vt = VT_ARRAY | VT_R4;
   values[2].parray = SafeArrayCreateVector(VT_R4, -1, GR7ARRAYSIZE);

   float *pValues2 = NULL;
   SafeArrayAccessData(values[2].parray, (void **)&pValues2);
   for (int i = 0; i < GR7ARRAYSIZE; i++)
   {
      pValues2[i] = i;
   }
   SafeArrayUnaccessData(values[2].parray);

   values[3].vt = VT_ARRAY | VT_R4;
   values[3].parray = SafeArrayCreateVector(VT_R4, -1, GR7ARRAYSIZE);

   float *pValues3 = NULL;
   SafeArrayAccessData(values[3].parray, (void **)&pValues3);
   for (int i = 0; i < GR7ARRAYSIZE; i++)
   {
      pValues3[i] = i;
   }
   SafeArrayUnaccessData(values[3].parray);

   values[4].vt = VT_ARRAY | VT_R4;
   values[4].parray = SafeArrayCreateVector(VT_R4, -1, GR7ARRAYSIZE);

   float *pValues4 = NULL;
   SafeArrayAccessData(values[4].parray, (void **)&pValues4);
   for (int i = 0; i < GR7ARRAYSIZE; i++)
   {
      pValues4[i] = i;
   }
   SafeArrayUnaccessData(values[4].parray);

   values[5].vt = VT_ARRAY | VT_R4;
   values[5].parray = SafeArrayCreateVector(VT_R4, -1, GR7ARRAYSIZE);

   float *pValues5 = NULL;
   SafeArrayAccessData(values[5].parray, (void **)&pValues5);
   for (int i = 0; i < GR7ARRAYSIZE; i++)
   {
      pValues5[i] = i;
   }
   SafeArrayUnaccessData(values[5].parray);

   r1 = pIOPCSyncIO11->Write(GR7ARRAYSNUM, &(*phServer.begin()), values,
      &pWErrors);

   if (r1 == S_OK)
   {
      LogPrint("Reset Gr7: OK!", clAqua);
      CoTaskMemFree(pWErrors);
      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pWErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Reset Gr7: item writing error: " + String(ErrorStr), clRed);

      CoTaskMemFree(pWErrors);
      CoTaskMemFree(ErrorStr);
      return 0;
   }
}

int __fastcall OPCRW::ResetGr11(void)
{
#ifdef _NO_Write
   return 1;
#endif

   VARIANT values[GR11ARRAYSNUM];
   HRESULT *pWErrors;
   LPWSTR ErrorStr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR11ARRAYSNUM);

   for (int i = 0; i < GR11ARRAYSNUM; ++i)
   {
      phServer[i] = pItemResult11[i].hServer;
   }

   values[0].vt = VT_ARRAY | VT_I4;
   values[0].parray = SafeArrayCreateVector(VT_I4, -1, GR11ARRAYSIZE);

   int *pValues0 = NULL;
   SafeArrayAccessData(values[0].parray, (void **)&pValues0);
   for (int i = 0; i < GR11ARRAYSIZE; i++)
   {
      pValues0[i] = 0;
   }
   SafeArrayUnaccessData(values[0].parray);

   values[1].vt = VT_ARRAY | VT_R4;
   values[1].parray = SafeArrayCreateVector(VT_R4, -1, GR11ARRAYSIZE);

   float *pValues1 = NULL;
   SafeArrayAccessData(values[1].parray, (void **)&pValues1);
   for (int i = 0; i < GR11ARRAYSIZE; i++)
   {
      pValues1[i] = 0;
   }
   SafeArrayUnaccessData(values[1].parray);

   values[2].vt = VT_ARRAY | VT_R4;
   values[2].parray = SafeArrayCreateVector(VT_R4, -1, GR11ARRAYSIZE);

   float *pValues2 = NULL;
   SafeArrayAccessData(values[2].parray, (void **)&pValues2);
   for (int i = 0; i < GR11ARRAYSIZE; i++)
   {
      pValues2[i] = 0;
   }
   SafeArrayUnaccessData(values[2].parray);

   values[3].vt = VT_ARRAY | VT_R4;
   values[3].parray = SafeArrayCreateVector(VT_R4, -1, GR11ARRAYSIZE);

   float *pValues3 = NULL;
   SafeArrayAccessData(values[3].parray, (void **)&pValues3);
   for (int i = 0; i < GR11ARRAYSIZE; i++)
   {
      pValues3[i] = 0;
   }
   SafeArrayUnaccessData(values[3].parray);

   values[4].vt = VT_ARRAY | VT_R4;
   values[4].parray = SafeArrayCreateVector(VT_R4, -1, GR11ARRAYSIZE);

   float *pValues4 = NULL;
   SafeArrayAccessData(values[4].parray, (void **)&pValues4);
   for (int i = 0; i < GR11ARRAYSIZE; i++)
   {
      pValues4[i] = 0;
   }
   SafeArrayUnaccessData(values[4].parray);

   values[5].vt = VT_ARRAY | VT_R4;
   values[5].parray = SafeArrayCreateVector(VT_R4, -1, GR11ARRAYSIZE);

   float *pValues5 = NULL;
   SafeArrayAccessData(values[5].parray, (void **)&pValues5);
   for (int i = 0; i < GR11ARRAYSIZE; i++)
   {
      pValues5[i] = 0;
   }
   SafeArrayUnaccessData(values[5].parray);

   r1 = pIOPCSyncIO11->Write(GR11ARRAYSNUM, &(*phServer.begin()), values,
      &pWErrors);

   if (r1 == S_OK)
   {
      LogPrint("Reset Gr11: OK!", clAqua);
      CoTaskMemFree(pWErrors);
      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pWErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Reset Gr11: item writing error: " + String(ErrorStr), clRed);

      CoTaskMemFree(pWErrors);
      CoTaskMemFree(ErrorStr);
      return 0;
   }
}


int __fastcall OPCRW::ReadCycleParameters(void) // чтение циклических параметров
{
   auto &inst = cpu::CpuMemory::Instance();
   if ( inst.mGr1.Read() && inst.mGr2.Read() )
   {
      return 1;
   }
   return 0;
}
// ---- End of ReadCycleParameters -------------------------------------------
