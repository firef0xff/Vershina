// ---------------------------------------------------------------------------
#pragma hdrstop

#include "OPCControl.h"
#include "Common.h"
#include "opcrw.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

unsigned __stdcall OPCControl(void*)
   // Функция управления стендом при помощи OPC-сервера
{
   LogMess = "OPCControl thread start!";
   PostMessage(MainFormHandle, WM_LogPrint, 0, (long)clAqua);
   OPCCtrlStat = 0;
   do
   {
      switch (OPCCtrlStat)
      {
      case IDDLESTAT:
         break;
      case READGR1:
         LogMess = "OPCControl: Read Group1!";
         SendMessage(MainFormHandle, WM_LogPrint, 0, (long)clLime);
         SendMessage(MainFormHandle, WM_OPCCmd, READGR1, 0);
         OPCCtrlStat = IDDLESTAT;
         break;
      case WRITEGR1ITEM:
         LogMess = "OPCControl: Write Group1 Item!";
         SendMessage(MainFormHandle, WM_LogPrint, 0, (long)clLime);
         SendMessage(MainFormHandle, WM_OPCCmd, WRITEGR1ITEM, 0);
         OPCCtrlStat = IDDLESTAT;
         break;
      default:
         OPCCtrlStat = IDDLESTAT;
      }

      Sleep(500);
   }
   while (OPCControlOn);
   return 0;
}
// ---- End of OPCControl ----------------------------------------------------
