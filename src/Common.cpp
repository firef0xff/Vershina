// ---------------------------------------------------------------------------
#include <stdio.h>
#include <process.h>
#include <DateUtils.hpp>
#include <StrUtils.hpp>
#pragma hdrstop
#include "def.h"
#include "Common.h"
#include "log/log_impl.h"

// ---------------------------------------------------------------------------

#pragma package(smart_init)
// индикаторы автосохранения протоколов за испытание
bool StendConnection = false; // индикатор связи со стендом
bool OPCControlOn = false; // Управление OPC-сервером запущено
bool OPCConnectOK = false; // соединение с OPC-сервером установлено
short OPCCtrlStat = 0; // управляющая переменная цикла управления стендом
long TimerCycleCnt = 0; // Счетчик циклов таймера
void  OPCControlStart(TTimer* t) // Запуск управления стендом
{
   OPCControlOn = true;
   t->Enabled = true;
}
void  OPCControlPause(TTimer* t) // Приостановка управления стендом
{
   LogPrint("Приостановка контроля управлением!", clLime);
   t->Enabled = false;
}
void  OPCControlResume(TTimer* t) // Возобновление управления стендом
{
   LogPrint("Возобновление контроля управлением!", clLime);
   t->Enabled = true;
}
void  OPCControlStop(TTimer* t) // Останов управления стендом
{
   LogPrint("Останов контроля управлением!", clLime);
   t->Enabled = false;
   OPCControlOn = false;
}


float  StrToFlt(String ws)
   // Преобразование строки в значение типа float
{
   String s;
   s = Trim(ws);
   if (s == "")
      return 0.0;
   int PointPos = s.Pos(".");
   if (PointPos)
      s = TrimRight(s.SubString(1, PointPos - 1)) + "." +
         Trim(s.SubString(PointPos + 1, 100));
   int CommaPos = s.Pos(",");
   if (CommaPos)
      s = TrimRight(s.SubString(1, PointPos - 1)) + "." +
         Trim(s.SubString(PointPos + 1, 100));
   return StrToFloat(s);
}
// ---- End of StrToFlt ------------------------------------------------------

int  StrToI(String ws) // ПРеобразование строки в значение типа int
{
   String s;
   s = Trim(ws);
   if (s == "")
      return 0;
   else
      return StrToInt(s);
}
// ---- End of StrToI --------------------------------------------------------

String  FileNameParse
   ( // Функция выделения имени файла из полного пути
   String SFN) // Полное имя файла
{
   String wfname = SFN;
   if (wfname.Length() > 0)
   {
      int slPos = wfname.Pos("\\");
      while (slPos)
      {
         wfname = wfname.SubString(slPos + 1, 1000);
         slPos = wfname.Pos("\\");
      }
   }
   return wfname;
}
// ---- End of FileNameParse -------------------------------------------------

int  NextCycleCount(void) // увеличение цикла счетчика на 1
{
   if ((++TimerCycleCnt) >= MAXINT)
      TimerCycleCnt = 0;
   return TimerCycleCnt;
}
// ---- End of NextCycleCount ------------------------------------------------

void  LeastSquares
   ( // расчет коэффициентов A и B методом наименьших квадратов
   float X[], // массив X
   float Y[], // массив Y
   int N, // количество элементов в массивах
   float &A, // коэффициент A
   float &B) // коэффициент B
{
   int i;
   double SXi, SYi, SXiYi, SXi2, Ndbl;
   SXi = 0;
   SYi = 0;
   SXiYi = 0;
   SXi2 = 0;
   Ndbl = N;
   for (i = 0; i < N; i++)
   {
      SXi += X[i];
      SYi += Y[i];
      SXiYi += X[i] * Y[i];
      SXi2 += X[i] * X[i];
   }
   A = (Ndbl * SXiYi - SXi * SYi) / (Ndbl * SXi2 - SXi * SXi);
   B = (SYi - A * SXi) / Ndbl;
}
// ---- End of LeastSquares --------------------------------------------------


int  BUnion(bool b1, bool b2)
   // объединение занчений аргументов в целое значение
{
   return (int(b1) << 1)+int(b2);
}
// ---- End of BUnion --------------------------------------------------------

String  FltToStr( // Преобразование числа в строку длиной l
   float f, // преобразуемое число
   TFloatFormat ff, // формат
   int l, // длина строки
   int r) // длина дробной части
{
   String ws;
   ws = FloatToStrF(f, ff, l, r);
   int wl = ws.Length();
   if (wl < l)
   {
      ws = String(DupeString(' ', l - wl)) + ws;
   }
   return ws;
}
// ---- End of FltToStr -----------------------------------------------------
