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
   pGr8Name = L"Gr8DB18DB32";
   pGr9Name = L"Gr9DB17DB31";
   pGr10Name = L"Gr10DB33";
   pGr11Name = L"Gr11DB11_16";
   pGr12Name = L"Gr12DB71";
   pGr13Name = L"Gr13DB70";
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
   // создание OPC-группы 8
   r1 = pIOPCServer->AddGroup(pGr8Name, true, 500, 8, &TimeBias,
      &PercentDeadband, LOCALE_ID, &GrpSrvHandle, &RevisedUpdateRate,
      IID_IOPCItemMgt, (LPUNKNOWN*)&pIOPCItemMgt8);

   if (r1 == S_OK)
   {
      // LogPrint("Добавлена группа \""+String(pGr8Name)+"\"",clWhite);
   }
   else
   {
      LogPrint("Ошибка при добавлении группы к серверу", clRed);
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // define an item table with items as in-paramter for AddItem
   for (int i = 0; i < GR8ITEMSNUM; i++)
   {
      if (i < GR81ITEMSNUM)
         wsStr = AddrDB18 + String(i * 4 + 2);
      else
         wsStr = AddrDB32 + String((i - GR81ITEMSNUM) * 4 + 2);
      Gr8ItemsNme[i] = &Gr8ItemsAddr[i][0];
      StringToWideChar(wsStr, Gr8ItemsNme[i], wsStr.Length() + 1);
      // if(i==0)LogPrint("Gr8ItemsNme[0]="+String(Gr8ItemsNme[i]),clAqua);
      // if(i==250)LogPrint("Gr8ItemsNme[250]="+String(Gr8ItemsNme[i]),clAqua);
      ItemsGr8[i].szAccessPath = L"";
      ItemsGr8[i].szItemID = Gr8ItemsNme[i];
      ItemsGr8[i].bActive = TRUE;
      ItemsGr8[i].hClient = 1;
      ItemsGr8[i].dwBlobSize = 0;
      ItemsGr8[i].pBlob = NULL;
      ItemsGr8[i].vtRequestedDataType = 0;
   }
   r1 = pIOPCItemMgt8->AddItems(GR8ITEMSNUM, ItemsGr8, &pItemResult8, &pErrors);
   if (r1 == S_OK || r1 == S_FALSE)
   {
      // LogPrint("Добавлены переменные группы 8 - массивы в блоках DB18 и DB32",clWhite);
   }
   else
   {
      pIOPCServer->GetErrorString(pErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Ошибка при добавлении переменных группы 8: " +
         String(ErrorStr), clRed);
      CoTaskMemFree(ErrorStr);
      pIOPCItemMgt8->Release();
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   r1 = pIOPCItemMgt8->QueryInterface(IID_IOPCSyncIO, (void**)&pIOPCSyncIO8);
   if (r1 >= 0)
   {
      LogPrint("Получен указатель на IOPCSyncIO8 для переменных группы \"" +
         String(pGr8Name) + "\"", clWhite);
   }
   else
   {
      LogPrint("Ошибка при получении указателя на IOPCSyncIO8", clRed);
      CoTaskMemFree(pItemResult8);
      pIOPCItemMgt8->Release();
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // создание OPC-группы 9
   r1 = pIOPCServer->AddGroup(pGr9Name, true, 500, 9, &TimeBias,
      &PercentDeadband, LOCALE_ID, &GrpSrvHandle, &RevisedUpdateRate,
      IID_IOPCItemMgt, (LPUNKNOWN*)&pIOPCItemMgt9);
   if (r1 == S_OK)
   {
      // LogPrint("Добавлена группа \""+String(pGr9Name)+"\"",clWhite);
   }
   else
   {
      LogPrint("Ошибка при добавлении группы к серверу", clRed);
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // define an item table with items as in-paramter for AddItem
   for (int i = 0; i < GR9ITEMSNUM; i++)
   {
      if (i < GR91ITEMSNUM)
         wsStr = AddrDB17 + String(i * 4 + 2);
      else
         wsStr = AddrDB31 + String((i - GR91ITEMSNUM) * 4 + 2);
      Gr9ItemsNme[i] = &Gr9ItemsAddr[i][0];
      StringToWideChar(wsStr, Gr9ItemsNme[i], wsStr.Length() + 1);
      // if(i==0)LogPrint("Gr9ItemsNme[0]="+String(Gr9ItemsNme[i]),clAqua);
      // if(i==250)LogPrint("Gr9ItemsNme[250]="+String(Gr9ItemsNme[i]),clAqua);
      ItemsGr9[i].szAccessPath = L"";
      ItemsGr9[i].szItemID = Gr9ItemsNme[i];
      ItemsGr9[i].bActive = TRUE;
      ItemsGr9[i].hClient = 1;
      ItemsGr9[i].dwBlobSize = 0;
      ItemsGr9[i].pBlob = NULL;
      ItemsGr9[i].vtRequestedDataType = 0;
   }
   r1 = pIOPCItemMgt9->AddItems(GR9ITEMSNUM, ItemsGr9, &pItemResult9, &pErrors);
   if (r1 == S_OK || r1 == S_FALSE)
   {
      // LogPrint("Добавлены переменные группы 9 - массивы в блоках DB17 и DB31",clWhite);
   }
   else
   {
      pIOPCServer->GetErrorString(pErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Ошибка при добавлении переменных группы 9: " +
         String(ErrorStr), clRed);
      CoTaskMemFree(ErrorStr);
      pIOPCItemMgt9->Release();
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // query interface for sync calls on group object
   r1 = pIOPCItemMgt9->QueryInterface(IID_IOPCSyncIO, (void**)&pIOPCSyncIO9);
   if (r1 >= 0)
   {
      LogPrint("Получен указатель на IOPCSyncIO9 для переменных группы \"" +
         String(pGr9Name) + "\"", clWhite);
   }
   else
   {
      LogPrint("Ошибка при получении указателя на IOPCSyncIO9", clRed);
      CoTaskMemFree(pItemResult9);
      pIOPCItemMgt9->Release();
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // создание OPC-группы 10
   r1 = pIOPCServer->AddGroup(pGr10Name, true, 500, 10, &TimeBias,
      &PercentDeadband, LOCALE_ID, &GrpSrvHandle, &RevisedUpdateRate,
      IID_IOPCItemMgt, (LPUNKNOWN*)&pIOPCItemMgt10);
   if (r1 == S_OK)
   {
      // LogPrint("Добавлена группа \""+String(pGr10Name)+"\"",clWhite);
   }
   else
   {
      LogPrint("Ошибка при добавлении группы к серверу", clRed);
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // define an item table with items as in-paramter for AddItem
   for (int i = 0; i < GR10ITEMSNUM; i++)
   {
      wsStr = AddrDB33 + String(i * 4 + 2);
      Gr10ItemsNme[i] = &Gr10ItemsAddr[i][0];
      StringToWideChar(wsStr, Gr10ItemsNme[i], wsStr.Length() + 1);
      // if(i==  0)LogPrint("Gr10ItemsNme[  0]="+String(Gr10ItemsNme[i]),clAqua);
      // if(i==100)LogPrint("Gr10ItemsNme[100]="+String(Gr10ItemsNme[i]),clAqua);
      ItemsGr10[i].szAccessPath = L"";
      ItemsGr10[i].szItemID = Gr10ItemsNme[i];
      ItemsGr10[i].bActive = TRUE;
      ItemsGr10[i].hClient = 1;
      ItemsGr10[i].dwBlobSize = 0;
      ItemsGr10[i].pBlob = NULL;
      ItemsGr10[i].vtRequestedDataType = 0;
   }
   r1 = pIOPCItemMgt10->AddItems(GR10ITEMSNUM, ItemsGr10, &pItemResult10,
      &pErrors);
   if (r1 == S_OK || r1 == S_FALSE)
   {
      // LogPrint("Добавлены переменные группы 10 - массив в блоке DB33",clWhite);
   }
   else
   {
      pIOPCServer->GetErrorString(pErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Ошибка при добавлении переменных группы 10: " +
         String(ErrorStr), clRed);
      CoTaskMemFree(ErrorStr);
      pIOPCItemMgt10->Release();
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // query interface for sync calls on group object
   r1 = pIOPCItemMgt10->QueryInterface(IID_IOPCSyncIO, (void**)&pIOPCSyncIO10);
   if (r1 >= 0)
   {
      LogPrint("Получен указатель на IOPCSyncIO10 для переменных группы \"" +
         String(pGr10Name) + "\"", clWhite);
   }
   else
   {
      LogPrint("Ошибка при получении указателя на IOPCSyncIO10", clRed);
      CoTaskMemFree(pItemResult10);
      pIOPCItemMgt10->Release();
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

   // создание OPC-группы 12
   r1 = pIOPCServer->AddGroup(pGr12Name, true, 500, 1, &TimeBias,
      &PercentDeadband, LOCALE_ID, &GrpSrvHandle, &RevisedUpdateRate,
      IID_IOPCItemMgt, (LPUNKNOWN*)&pIOPCItemMgt12);
   if (r1 == S_OK)
   {
      // LogPrint("Добавлена группа \""+String(pGr12Name)+"\"",clWhite);
   }
   else
   {
      LogPrint("Ошибка при добавлении группы к серверу", clRed);
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   for (int i = 0; i < GR12ITEMSNUM; i++)
   {
      ItemsGr12[i].szAccessPath = L"";
      ItemsGr12[i].szItemID = Gr12ItemsNme[i];
      ItemsGr12[i].bActive = TRUE;
      ItemsGr12[i].hClient = 1;
      ItemsGr12[i].dwBlobSize = 0;
      ItemsGr12[i].pBlob = NULL;
      ItemsGr12[i].vtRequestedDataType = 0;
   }
   r1 = pIOPCItemMgt12->AddItems(GR12ITEMSNUM, ItemsGr12, &pItemResult12,
      &pErrors);
   if (r1 == S_OK || r1 == S_FALSE)
   {
      // LogPrint("Добавлены переменные группы 12 - переменные в блоке DB71",clWhite);
   }
   else
   {
      pIOPCServer->GetErrorString(pErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Ошибка при добавлении переменных группы 12: " +
         String(ErrorStr), clRed);
      CoTaskMemFree(ErrorStr);
      pIOPCItemMgt12->Release();
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // query interface for sync calls on group object
   r1 = pIOPCItemMgt12->QueryInterface(IID_IOPCSyncIO, (void**)&pIOPCSyncIO12);
   if (r1 >= 0)
   {
      LogPrint("Получен указатель на IOPCSyncIO12 для переменных группы \"" +
         String(pGr12Name) + "\"", clWhite);
   }
   else
   {
      LogPrint("Ошибка при получении указателя на IOPCSyncIO12", clRed);
      CoTaskMemFree(pItemResult12);
      pIOPCItemMgt12->Release();
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // создание OPC-группы 13
   r1 = pIOPCServer->AddGroup(pGr13Name, true, 500, 1, &TimeBias,
      &PercentDeadband, LOCALE_ID, &GrpSrvHandle, &RevisedUpdateRate,
      IID_IOPCItemMgt, (LPUNKNOWN*)&pIOPCItemMgt13);
   if (r1 == S_OK)
   {
      // LogPrint("Добавлена группа \""+String(pGr13Name)+"\"",clWhite);
   }
   else
   {
      LogPrint("Ошибка при добавлении группы к серверу", clRed);
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   for (int i = 0; i < GR13ITEMSNUM; i++)
   {
      ItemsGr13[i].szAccessPath = L"";
      ItemsGr13[i].szItemID = Gr13ItemsNme[i];
      ItemsGr13[i].bActive = TRUE;
      ItemsGr13[i].hClient = 1;
      ItemsGr13[i].dwBlobSize = 0;
      ItemsGr13[i].pBlob = NULL;
      ItemsGr13[i].vtRequestedDataType = 0;
   }
   r1 = pIOPCItemMgt13->AddItems(GR13ITEMSNUM, ItemsGr13, &pItemResult13,
      &pErrors);
   if (r1 == S_OK || r1 == S_FALSE)
   {
      // LogPrint("Добавлены переменные группы 13 - переменные в блоке DB70",clWhite);
   }
   else
   {
      pIOPCServer->GetErrorString(pErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Ошибка при добавлении переменных группы 13: " +
         String(ErrorStr), clRed);
      CoTaskMemFree(ErrorStr);
      pIOPCItemMgt12->Release();
      pIOPCServer->Release();
      CoUninitialize();
      return;
   }
   // query interface for sync calls on group object
   r1 = pIOPCItemMgt13->QueryInterface(IID_IOPCSyncIO, (void**)&pIOPCSyncIO13);
   if (r1 >= 0)
   {
      LogPrint("Получен указатель на IOPCSyncIO13 для переменных группы \"" +
         String(pGr13Name) + "\"", clWhite);
   }
   else
   {
      LogPrint("Ошибка при получении указателя на IOPCSyncIO13", clRed);
      CoTaskMemFree(pItemResult13);
      pIOPCItemMgt13->Release();
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

int __fastcall OPCRW::ReadGr8(void) // чтение переменных группы 8
{
#ifdef _mDEBUG
   return 1;
#endif

   OPCITEMSTATE *pItemValue;
   LPWSTR ErrorStr;
   UINT qnr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR8ITEMSNUM);

   for (int i = 0; i < GR8ITEMSNUM; i++)
   {
      phServer[i] = pItemResult8[i].hServer;
   }
   r1 = pIOPCSyncIO8->Read(OPC_DS_CACHE, GR8ITEMSNUM, &(*phServer.begin()),
      &pItemValue, &pRErrors);

   if (r1 == S_OK)
   {
      for (int i = 0; i < GR8ITEMSNUM; i++)
      {
         if (i < GR81ITEMSNUM)
            poll_step_SB[i] = pItemValue[i].vDataValue.fltVal;
         else
            step_SB[i - GR81ITEMSNUM] = pItemValue[i].vDataValue.fltVal;
      }
      for (int i = 0; i < GR8ITEMSNUM; i++)
      {
         VariantClear(&pItemValue[i].vDataValue);
      }
      CoTaskMemFree(pItemValue);

      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pRErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Read: Group 8 item reading error: " + String(ErrorStr), clRed);

      CoTaskMemFree(ErrorStr);
      return 0;
   }
}
// ---- End of ReadGr8 -------------------------------------------------------

int __fastcall OPCRW::ReadGr9(void) // чтение переменных группы 9
{
#ifdef _mDEBUG
   return 1;
#endif

   OPCITEMSTATE *pItemValue;
   LPWSTR ErrorStr;
   UINT qnr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR9ITEMSNUM);

   for (int i = 0; i < GR9ITEMSNUM; i++)
   {
      phServer[i] = pItemResult9[i].hServer;
   }
   r1 = pIOPCSyncIO9->Read(OPC_DS_CACHE, GR9ITEMSNUM, &(*phServer.begin()),
      &pItemValue, &pRErrors);

   if (r1 == S_OK)
   {
      for (int i = 0; i < GR9ITEMSNUM; i++)
      {
         if (i < GR91ITEMSNUM)
            poll_step_TB[i] = pItemValue[i].vDataValue.lVal;
         else
            step_TB[i - GR91ITEMSNUM] = pItemValue[i].vDataValue.lVal;
      }
      for (int i = 0; i < GR9ITEMSNUM; i++)
      {
         VariantClear(&pItemValue[i].vDataValue);
      }
      CoTaskMemFree(pItemValue);
      LogPrint("poll_step_TB[0]=" + String(poll_step_TB[0]), clLime);
      // debug print
      LogPrint("step_TB[0]=" + String(step_TB[0]), clLime); // debug print

      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pRErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Read: Group 9 item reading error: " + String(ErrorStr), clRed);

      CoTaskMemFree(ErrorStr);
      return 0;
   }
}
// ---- End of ReadGr9 -------------------------------------------------------

int __fastcall OPCRW::ReadGr10(void) // чтение переменных группы 10
{
#ifdef _mDEBUG
   return 1;
#endif

   OPCITEMSTATE *pItemValue;
   LPWSTR ErrorStr;
   UINT qnr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR10ITEMSNUM);

   for (int i = 0; i < GR10ITEMSNUM; i++)
   {
      phServer[i] = pItemResult10[i].hServer;
   }
   r1 = pIOPCSyncIO10->Read(OPC_DS_CACHE, GR10ITEMSNUM, &(*phServer.begin()),
      &pItemValue, &pRErrors);

   if (r1 == S_OK)
   {
      for (int i = 0; i < GR10ITEMSNUM; i++)
      {
         if (i < MAXNUMOFSTEPS)
            setting_B[0][i] = pItemValue[i].vDataValue.fltVal;
         else
            setting_B[1][i - MAXNUMOFSTEPS] = pItemValue[i].vDataValue.fltVal;
      }
      for (int i = 0; i < GR10ITEMSNUM; i++)
      {
         VariantClear(&pItemValue[i].vDataValue);
      }
      CoTaskMemFree(pItemValue);
      LogPrint("setting_B[0][0]=" + FloatToStrF(setting_B[0][0], ffFixed, 6, 2),
         clLime); // debug print
      LogPrint("setting_B[1][0]=" + FloatToStrF(setting_B[1][0], ffFixed, 6, 2),
         clLime); // debug print

      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pRErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Read: Group 10 item reading error: " + String(ErrorStr), clRed);

      CoTaskMemFree(ErrorStr);
      return 0;
   }
}
// ---- End of ReadGr10 ------------------------------------------------------

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

int __fastcall OPCRW::ReadGr12(void) // чтение переменных группы 12
{
#ifdef _mDEBUG
   return 1;
#endif

   OPCITEMSTATE *pItemValue;
   LPWSTR ErrorStr;
   UINT qnr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR12ITEMSNUM);

   for (int i = 0; i < GR12ITEMSNUM; i++)
   {
      phServer[i] = pItemResult12[i].hServer;
   }
   r1 = pIOPCSyncIO12->Read(OPC_DS_CACHE, GR12ITEMSNUM, &(*phServer.begin()),
      &pItemValue, &pRErrors);

   if (r1 == S_OK)
   {
      for (int i = 0; i < GR12ARRAYSIZE; i++)
      {
         *A1[i] = pItemValue[i].vDataValue.fltVal;
         *Q1[i] = pItemValue[i + GR12ARRAYSIZE].vDataValue.fltVal;
      }
      for (int i = 0; i < GR12ITEMSNUM; i++)
      {
         VariantClear(&pItemValue[i].vDataValue);
      }
      CoTaskMemFree(pItemValue);

      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pRErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Read: Group 12 item reading error: " + String(ErrorStr), clRed);

      CoTaskMemFree(ErrorStr);
      return 0;
   }
}
// ---- End of ReadGr12 ------------------------------------------------------

int __fastcall OPCRW::ReadGr13(void) // чтение переменных группы 13
{
#ifdef _mDEBUG
   return 1;
#endif

   OPCITEMSTATE *pItemValue;
   LPWSTR ErrorStr;
   UINT qnr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR13ITEMSNUM);

   for (int i = 0; i < GR13ITEMSNUM; i++)
   {
      phServer[i] = pItemResult13[i].hServer;
   }
   r1 = pIOPCSyncIO13->Read(OPC_DS_CACHE, GR13ITEMSNUM, &(*phServer.begin()),
      &pItemValue, &pRErrors);

   if (r1 == S_OK)
   {
      for (int i = 0; i < GR13ARRAYSIZE; i++)
      {
         *A2[i] = pItemValue[i].vDataValue.fltVal;
         *Q2[i] = pItemValue[i + GR13ARRAYSIZE].vDataValue.fltVal;
      }
      for (int i = 0; i < GR13ITEMSNUM; i++)
      {
         VariantClear(&pItemValue[i].vDataValue);
      }
      CoTaskMemFree(pItemValue);

      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pRErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Read: Group 13 item reading error: " + String(ErrorStr), clRed);

      CoTaskMemFree(ErrorStr);
      return 0;
   }
}
// ---- End of ReadGr13 ------------------------------------------------------

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

int __fastcall OPCRW::WriteGr8(void) // запись вещественных массивов группы 8
{
#ifdef _NO_Write
   return 1;
#endif

   VARIANT values[GR8ITEMSNUM];
   HRESULT *pWErrors;
   LPWSTR ErrorStr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR8ITEMSNUM);

   for (int i = 0; i < GR8ITEMSNUM; i++)
   {
      phServer[i] = pItemResult8[i].hServer;
      values[i].vt = VT_R4;
      if (i < GR81ITEMSNUM)
         values[i].fltVal = poll_step_SB[i];
      else
         values[i].fltVal = step_SB[i - GR81ITEMSNUM];
   }
   r1 = pIOPCSyncIO8->Write(GR8ITEMSNUM, &(*phServer.begin()), values,
      &pWErrors);

   if (r1 == S_OK)
   {
      LogPrint("Write Gr8: OK!", clAqua);
      CoTaskMemFree(pWErrors);
      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pWErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Write Gr8: item writing error: " + String(ErrorStr), clRed);

      CoTaskMemFree(pWErrors);
      CoTaskMemFree(ErrorStr);
      return 0;
   }
}
// ---- End of WriteGr8 ------------------------------------------------------

int __fastcall OPCRW::WriteGr9(void) // запись целых массивов группы 9
{
#ifdef _NO_Write
   return 1;
#endif

   VARIANT values[GR9ITEMSNUM];
   HRESULT *pWErrors;
   LPWSTR ErrorStr;
   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR9ITEMSNUM);

   for (int i = 0; i < GR9ITEMSNUM; i++)
   {
      phServer[i] = pItemResult9[i].hServer;
      values[i].vt = VT_I4;
      if (i < GR91ITEMSNUM)
         values[i].lVal = poll_step_TB[i];
      else
         values[i].lVal = step_TB[i - GR91ITEMSNUM];
   }
   r1 = pIOPCSyncIO9->Write(GR9ITEMSNUM, &(*phServer.begin()), values,
      &pWErrors);

   if (r1 == S_OK)
   {
      LogPrint("Write Gr9: OK!", clAqua);
      CoTaskMemFree(pWErrors);
      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pWErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Write Gr9: item writing error: " + String(ErrorStr), clRed);

      CoTaskMemFree(pWErrors);
      CoTaskMemFree(ErrorStr);
      return 0;
   }
}
// ---- End of WriteGr9 ------------------------------------------------------

int __fastcall OPCRW::WriteGr10(void) // запись вещественного массива группы 10
{
#ifdef _NO_Write
   return 1;
#endif

   VARIANT values[GR10ITEMSNUM];
   HRESULT *pWErrors;
   LPWSTR ErrorStr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR10ITEMSNUM);

   for (int i = 0; i < GR10ITEMSNUM; i++)
   {
      phServer[i] = pItemResult10[i].hServer;
      values[i].vt = VT_R4;
      if (i < MAXNUMOFSTEPS)
         values[i].fltVal = setting_B[1][i];
      else
         values[i].fltVal = setting_B[0][i - MAXNUMOFSTEPS];
   }
   r1 = pIOPCSyncIO10->Write(GR10ITEMSNUM, &(*phServer.begin()), values,
      &pWErrors);

   if (r1 == S_OK)
   {
      LogPrint("Write Gr10: OK!", clAqua);
      CoTaskMemFree(pWErrors);
      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pWErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Write Gr10: item writing error: " + String(ErrorStr), clRed);

      CoTaskMemFree(pWErrors);
      CoTaskMemFree(ErrorStr);
      return 0;
   }
}
// ---- End of WriteGr10 -----------------------------------------------------

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

int __fastcall OPCRW::WriteGr12(void) // запись вещественного массива группы 12
{
#ifdef _NO_Write
   return 1;
#endif
   VARIANT values[GR12ITEMSNUM];
   HRESULT *pWErrors;
   LPWSTR ErrorStr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR12ITEMSNUM);

   for (int i = 0; i < GR12ARRAYSIZE; i++)
   {
      phServer[i] = pItemResult12[i].hServer;
      values[i].vt = VT_R4;
      values[i].fltVal = *A1[i];
      phServer[i + GR12ARRAYSIZE] = pItemResult12[i + GR12ARRAYSIZE].hServer;
      values[i + GR12ARRAYSIZE].vt = VT_R4;
      values[i + GR12ARRAYSIZE].fltVal = *Q1[i];
   }

   r1 = pIOPCSyncIO12->Write(GR12ITEMSNUM, &(*phServer.begin()), values,
      &pWErrors);

   if (r1 == S_OK)
   {
      LogPrint("Write Gr12: OK!", clAqua);
      CoTaskMemFree(pWErrors);
      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pWErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Write Gr12: item writing error: " + String(ErrorStr), clRed);

      CoTaskMemFree(pWErrors);
      CoTaskMemFree(ErrorStr);
      return 0;
   }
}
// ---- End of WriteGr12 -----------------------------------------------------

int __fastcall OPCRW::WriteGr13(void) // запись вещественного массива группы 12
{
#ifdef _NO_Write
   return 1;
#endif

   VARIANT values[GR13ITEMSNUM];
   HRESULT *pWErrors;
   LPWSTR ErrorStr;

   std::vector<OPCHANDLE>phServer;
   phServer.resize(GR13ITEMSNUM);

   for (int i = 0; i < GR13ARRAYSIZE; i++)
   {
      phServer[i] = pItemResult13[i].hServer;
      values[i].vt = VT_R4;
      values[i].fltVal = *A2[i];
      phServer[i + GR13ARRAYSIZE] = pItemResult13[i + GR13ARRAYSIZE].hServer;
      values[i + GR13ARRAYSIZE].vt = VT_R4;
      values[i + GR13ARRAYSIZE].fltVal = *Q2[i];
   }
   r1 = pIOPCSyncIO13->Write(GR13ITEMSNUM, &(*phServer.begin()), values,
      &pWErrors);

   if (r1 == S_OK)
   {
      LogPrint("Write Gr13: OK!", clAqua);
      CoTaskMemFree(pWErrors);
      return 1;
   }
   else
   {
      pIOPCServer->GetErrorString(pWErrors[0], LOCALE_ID, &ErrorStr);
      LogPrint("Write Gr13: item writing error: " + String(ErrorStr), clRed);

      CoTaskMemFree(pWErrors);
      CoTaskMemFree(ErrorStr);
      return 0;
   }
}
// ---- End of WriteGr13 -----------------------------------------------------

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
