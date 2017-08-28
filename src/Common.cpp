// ---------------------------------------------------------------------------
#include <stdio.h>
#include <process.h>
#include <DateUtils.hpp>
#include <StrUtils.hpp>
#pragma hdrstop
#include "def.h"
#include "TyreProt.h"
#include "Common.h"

// ---------------------------------------------------------------------------

#pragma package(smart_init)
#ifdef _DEBUG
int ThreadCounter = 0;
#endif
bool needSaveA = false, needSaveB = false;
// индикаторы автосохранения протоколов за испытание
bool StendConnection = false; // индикатор связи со стендом

bool switch_Carriage1 = false;
// триггеры для обработки сообщений остановки каретки
bool switch_Carriage2 = false;

String strDistProg = "", strTimeProg = "", strProtA = "", strProtB = "",
   strTitleProt = "", strLoadCalibrA = "", strLoadCalibrB = "", strTCalibrA =
   "", strTCalibrB = "", strRCalibrA = "", strRCalibrB = "", strSpdCalibr = "",
   strSertPrintProtA = "", strSertPrintProtB = "";
bool AutoSave = false;
TRichEdit *pPrt; // указатель на компонент для вывода протокола
HWND MainFormHandle; // дескриптор окна основной формы
String LogMess = ""; // Строка для печати сообщений в журнале
HANDLE hOPCCtrlThrd; // Handler для потока CPU
unsigned OPCCtrlThrdID; // идентификатор потока CPU
bool OPCControlOn = false; // Управление OPC-сервером запущено
bool OPCConnectOK = false; // соединение с OPC-сервером установлено
int OldMode1, CurrMode1; // предидущий и текущий режим ручной/авто поз. 1
int OldMode2, CurrMode2; // предидущий и текущий режим ручной/авто поз. 2
int OldSMode1, CurrSMode1; // предидущий и текущий режим старт/стоп поз. 1
int OldSMode2, CurrSMode2; // предидущий и текущий режим старт/стоп поз. 2
int old_step_1 = 1; // предидущий номер шага по поз. 1
int cur_step_1 = 1; // текущий номер шага по поз. 1
int old_step_2 = 1; // предидущий номер шага по поз. 2
int cur_step_2 = 1; // текущий номер шага по поз. 2
float old_speed_1 = 0.0; // предидущая скорость по поз. 1
float cur_speed_1 = 0.0; // текущая скорость по поз. 1
int old_time_1 = 0; // продолжительность предидущего шага поз. 1
int cur_time_1 = 0; // продолжительность текущего шага поз. 1
float old_dist_1 = 0.0; // путь на предидущем шаге поз. 1
float cur_dist_1 = 0.0; // путь на текущем шаге поз. 1
float old_load_1 = 0.0; // нагрузка на предидущем шаге поз. 1
float cur_load_1 = 0.0; // нагрузка на текущем шаге поз. 1
float old_temp_1 = 0.0; // температура на предидущем шаге поз. 1
float cur_temp_1 = 0.0; // температура на текущем шаге поз. 1
float old_radius_1 = 0.0; // радиус на предидущем шаге поз. 1
float cur_radius_1 = 0.0; // радиус на текущем шаге поз. 1
float old_speed_2 = 0.0; // предидущая скорость по поз. 2
float cur_speed_2 = 0.0; // текущая скорость по поз. 2
int old_time_2 = 0; // продолжительность предидущего шага поз. 2
int cur_time_2 = 0; // продолжительность текущего шага поз. 2
float old_dist_2 = 0.0; // путь на предидущем шаге поз. 2
float cur_dist_2 = 0.0; // путь на текущем шаге поз. 2
float old_load_2 = 0.0; // нагрузка на предидущем шаге поз. 2
float cur_load_2 = 0.0; // нагрузка на текущем шаге поз. 2
float old_temp_2 = 0.0; // температура на предидущем шаге поз. 2
float cur_temp_2 = 0.0; // температура на текущем шаге поз. 2
float old_radius_2 = 0.0; // радиус на предидущем шаге поз. 2
float cur_radius_2 = 0.0; // радиус на текущем шаге поз. 2
bool CurrentStart1 = false; // Текущее состояние поз. 1
bool CurrentStart2 = false; // Текущее состояние поз. 2
// bool      Handle1On=true;       // Обработка событий по поз. 1 включена
// bool      Handle2On=true;       // Обработка событий по поз. 2 включена
short OPCCtrlStat = 0; // управляющая переменная цикла управления стендом
long TimerCycleCnt = 0; // Счетчик циклов таймера
// переменные протокола
// Tyre      *InpTyre,             // покрышка для ввода и редактирования протокола
// *TyreA,               // покрышка в поз. А
// *TyreB;               // покрышка в поз. Б
String TyreTypeA = "А", TyreTypeB = "Б"; // тип покрышки
String RunProgNameA = "Прог 1", RunProgNameB = "Прог 2";
// наименвание программы обкатки

// общие функции ------------------------------------------------------------

// Печати сроки Str в окне протокола цветом CClr ----------------------------
void __fastcall LogPrint(String Str, TColor CClr)
{
   pPrt->SelAttributes->Color = CClr;
   pPrt->Lines->Add(Str);
}
// ---- End of LogPrint ------------------------------------------------------

// Вывод сообщений в окно протокола при помощи SendMessage
void __fastcall SLogPrint(String Str, TColor CClr)
{
   LogMess = Str;
   SendMessage(MainFormHandle, WM_LogPrint, 0, (long)CClr);
}
// ---- End of SLogPrint -----------------------------------------------------

// Вывод сообщений в окно протокола при помощи PostMessage
void __fastcall PLogPrint(String Str, TColor CClr)
{
   LogMess = Str;
   PostMessage(MainFormHandle, WM_LogPrint, 0, (long)CClr);
}
// ---- End of PLogPrint -----------------------------------------------------

void __fastcall OPCControlStart(TTimer* t) // Запуск управления стендом
{
   OPCControlOn = true;
   t->Enabled = true;
}
// ---- End of OPCControlStart -----------------------------------------------

void __fastcall OPCControlPause(TTimer* t) // Приостановка управления стендом
{
   LogPrint("Приостановка контроля управлением!", clLime);
   t->Enabled = false;
}
// ---- End of OPCControlPause -----------------------------------------------

void __fastcall OPCControlResume(TTimer* t) // Возобновление управления стендом
{
   LogPrint("Возобновление контроля управлением!", clLime);
   t->Enabled = true;
}
// ---- End of OPCControlResume ----------------------------------------------

void __fastcall OPCControlStop(TTimer* t) // Останов управления стендом
{
   LogPrint("Останов контроля управлением!", clLime);
   t->Enabled = false;
   OPCControlOn = false;
}
// ---- End of OPCControlStop ------------------------------------------------

float __fastcall StrToFlt(String ws)
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

int __fastcall StrToI(String ws) // ПРеобразование строки в значение типа int
{
   String s;
   s = Trim(ws);
   if (s == "")
      return 0;
   else
      return StrToInt(s);
}
// ---- End of StrToI --------------------------------------------------------

String __fastcall FileNameParse
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

int __fastcall NextCycleCount(void) // увеличение цикла счетчика на 1
{
   if ((++TimerCycleCnt) >= MAXINT)
      TimerCycleCnt = 0;
   return TimerCycleCnt;
}
// ---- End of NextCycleCount ------------------------------------------------

void __fastcall LeastSquares
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

void __fastcall LogPrintF( // Вывод сообщений в файл журнала
   String FNme, // имя файла журнала
   String Mess, // сообщение
   TColor wcl) // цвет сообщения в окне
{
   FILE *fparam;
   if ((fparam = fopen(AnsiString(FNme).c_str(), "at+")) == NULL)
   {
      LogPrint("Can't open logfile \"" + FNme + "\" for writing!", clRed);
      return;
   }
   // LogPrint("Write to file \""+FNme+"\" mess: \""+Mess+"\"",wcl);
   LogPrint("Logfile mess: " + Now().TimeString() + " \"" + Mess + "\"", wcl);
   fprintf(fparam, "%8s: %s\n", AnsiString(Now().TimeString()).c_str(),
      AnsiString(Mess).c_str());
   fclose(fparam);
}
// ---- End of LogPrintF -----------------------------------------------------

String __fastcall LogFName(void) // Генерация имени файла журнала
{
   String wfname;
   wfname = "RBLogFile";
   wfname += IntToStr(YearOf(Now()));
   int month = MonthOf(Now());
   if (month < 10)
      wfname += "0";
   wfname += IntToStr(month);
   int day = DayOf(Now());
   if (day < 10)
      wfname += "0";
   wfname += IntToStr(day) + ".log";
   return wfname;
}
// ---- End of LogFName ------------------------------------------------------

int __fastcall BUnion(bool b1, bool b2)
   // объединение занчений аргументов в целое значение
{
   return (int(b1) << 1)+int(b2);
}
// ---- End of BUnion --------------------------------------------------------

String __fastcall FltToStr( // Преобразование числа в строку длиной l
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
