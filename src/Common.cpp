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
extern int ThreadCounter = 0;
#endif
extern bool needSaveA = false, needSaveB = false;
// индикаторы автосохранения протоколов за испытание
extern bool StendConnection = false; // индикатор связи со стендом

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

// рабочие переменные для программ испытаний
// программа по пути
String SProgFName = ""; // имя файла для сохранения программы по пути
String SProgName = ""; // имя программы испытаний по пути
float STyrePressure = 0; // давление в шине
int total_step_S = 0; // суммарное кол-во шагов программы по пути
float total_S = 0; // суммарная продолжительность программы по пути, км
int num_S_poll = 0; // количество опросов по пути
float poll_step_S[MAXNUMOFPOLLS] =
{0}; // массив опросов по пути
float prog_step_S[MAXNUMOFSTEPS] =
{0}; // массив шагов по пути
float Ssettings[2][MAXNUMOFSTEPS] =
{0}; // массив нагрузок (1-й столбец) и скоростей (2-й столбец)
// программа по времени
String TProgFName = ""; // имя файла для сохранения программы по времени
String TProgName = ""; // имя программы испытаний по времени
float TTyrePressure = 0; // давление в шине
int total_step_T = 0; // суммарное кол-во шагов программы по времени
int total_T = 0; // суммарная продолжительность программы по времени, мсек
int num_T_poll = 0; // количество опросов по времени
int poll_step_T[MAXNUMOFPOLLS] =
{0}; // массив опросов по времени
int prog_step_T[MAXNUMOFSTEPS] =
{0}; // массив шагов по времени
float Tsettings[2][MAXNUMOFSTEPS] =
{0}; // массив нагрузок (1-й столбец) и скоростей (2-й столбец)

// сброс программы по времени
void ClearTProg(void)
{
   for (size_t i = 0; i < MAXNUMOFPOLLS; i++) // массив опросов по времени
   {
      poll_step_T[i] = 0;
   }
   for (size_t i = 0; i < MAXNUMOFSTEPS; i++)
   {
      prog_step_T[i] = 0; // массив шагов по времени
      Tsettings[0][i] = 0; // массив нагрузок (1-й столбец)
      Tsettings[1][i] = 0; // массив скоростей (2-й столбец)
   }
   TProgFName = ""; // имя файла для сохранения программы по времени
   TProgName = ""; // имя программы испытаний по времени
   TTyrePressure = 0.0; // давление в шине
   total_step_T = 0; // суммарное кол-во шагов программы по времени
   total_T = 0; // суммарная продолжительность программы по времени, мсек
   num_T_poll = 0; // количество опросов по времени
}

// сброс программы по пути
void ClearSProg(void)
{
   for (size_t i = 0; i < MAXNUMOFPOLLS; i++) // массив опросов по пути
   {
      poll_step_S[i] = 0;
   }
   for (size_t i = 0; i < MAXNUMOFSTEPS; i++)
   {
      prog_step_S[i] = 0; // массив шагов по времени
      Ssettings[0][i] = 0; // массив нагрузок (1-й столбец)
      Ssettings[1][i] = 0; // массив скоростей (2-й столбец)
   }
   SProgFName = ""; // имя файла для сохранения программы по пути
   SProgName = ""; // имя программы испытаний по пути
   STyrePressure = 0.0; // давление в шине
   total_step_S = 0; // суммарное кол-во шагов программы по пути
   total_S = 0.0; // суммарная продолжительность программы по пути, км
   num_S_poll = 0; // количество опросов по пути
}

// общие функции ------------------------------------------------------------

void __fastcall ResetKA(float *A) // сброс массива А в единичку
{
   for (int i = 0; i < GR13ARRAYSIZE; i++)
   {
      A[i] = 1.0;
   }
}
// ---- End of ResetKA -------------------------------------------------------

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

String __fastcall mSecToHMSStr(int tm)
   // перевод целого кол-ва мсек в строку чч:мм:сс
{
   int s = tm / 1000, h, m;
   h = s / 3600;
   s -= h * 3600;
   m = s / 60;
   s -= m * 60;
   String ws = "";
   // часы
   if (h == 0)
      ws = "00:";
   else if (h < 10)
      ws = "0" + String(h) + ":";
   else
      ws = String(h) + ":";
#ifdef _NOS_SHOW_SEK
   // минуты
   if (m == 0)
      ws += "00";
   else if (m < 10)
      ws += "0" + String(m);
   else
      ws += String(m);
#endif
#ifndef _NOS_SHOW_SEK
   // минуты
   if (m == 0)
      ws += "00:";
   else if (m < 10)
      ws += "0" + String(m) + ":";
   else
      ws += String(m) + ":";
   // секукны
   if (s == 0)
      ws += "00";
   else if (s < 10)
      ws += "0" + String(s);
   else
      ws += String(s);
#endif
   return ws;
}
// ---- End of mSecToHMSStr --------------------------------------------------

void __fastcall ReadSProgFmFile(void) // прочитать программу по пути из файла
{
   FILE *fparam;
   float w;
   if ((fparam = fopen(AnsiString(SProgFName).c_str(), "rb")) == NULL)
   {
      LogPrint("Can't open file \"" + SProgFName + "\" for reading!", clRed);
      return;
   }
   SProgName = ReadString(fparam);
   fread(&STyrePressure, sizeof(float), 1, fparam);
   fread(&total_step_S, sizeof(int), 1, fparam);
   fread(&total_S, sizeof(float), 1, fparam);
   fread(&num_S_poll, sizeof(int), 1, fparam);
   fread(&Ssettings[0][0], sizeof(Ssettings), 1, fparam);
   fread(&prog_step_S[0], sizeof(prog_step_S), 1, fparam);
   fread(&poll_step_S[0], sizeof(poll_step_S), 1, fparam);
   fclose(fparam);
   // LogPrint("Total_S="+FloatToStrF(total_S,ffFixed,7,2),clAqua);
   // LogPrint("Num_S_poll="+String(num_S_poll),clAqua);
   // LogPrint("poll_step__S[0]="+FloatToStrF(poll_step_S[0],ffFixed,7,2),clAqua);
   // LogPrint("Total_S="+FloatToStrF(total_S,ffFixed,7,2),clAqua);
}
// ---- End of ReadSProgFmFile -----------------------------------------------

void __fastcall WriteSProgToFile(void) // записать программу по пути в файл
{
   FILE *fparam;
   if ((fparam = fopen(AnsiString(SProgFName).c_str(), "wb")) == NULL)
   {
      LogPrint("Can't open file \"" + SProgFName + "\" for writing!", clRed);
      return;
   }
   WriteString(SProgName, fparam);
   fwrite(&STyrePressure, sizeof(float), 1, fparam);
   fwrite(&total_step_S, sizeof(int), 1, fparam);
   fwrite(&total_S, sizeof(float), 1, fparam);
   fwrite(&num_S_poll, sizeof(int), 1, fparam);
   fwrite(&Ssettings[0][0], sizeof(Ssettings), 1, fparam);
   fwrite(&prog_step_S[0], sizeof(prog_step_S), 1, fparam);
   fwrite(&poll_step_S[0], sizeof(poll_step_S), 1, fparam);
   fclose(fparam);
   // LogPrint("Total_S="+FloatToStrF(total_S,ffFixed,7,2),clAqua);
   // LogPrint("Num_S_poll="+String(num_S_poll),clAqua);
   // LogPrint("poll_step__S[0]="+FloatToStrF(poll_step_S[0],ffFixed,7,2),clAqua);
   // LogPrint("Total_S="+FloatToStrF(total_S,ffFixed,7,2),clAqua);
}
// ---- End of WriteSProgFmFile ----------------------------------------------

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

String __fastcall ReadString(FILE *fp) // чтение строки типа String из файла
{
   char is[1024];
   short it;
   fread(&it, sizeof(short), 1, fp);
   fread(is, sizeof(char), it, fp);
   is[it] = 0;
   return String(is);
}
// ---- End of ReadString ----------------------------------------------------

void __fastcall WriteString( // запись строки типа String в файл
   String ws, FILE *fp)
{
   short it = strlen(AnsiString(ws).c_str());
   fwrite(&it, sizeof(short), 1, fp);
   fwrite(AnsiString(ws).c_str(), sizeof(char), it, fp);
}
// ---- End of WriteString ---------------------------------------------------

void __fastcall ReadTProgFmFile(void) // прочитать программу по времени из файла
{
   FILE *fparam;
   if ((fparam = fopen(AnsiString(TProgFName).c_str(), "rb")) == NULL)
   {
      LogPrint("Can't open file \"" + TProgFName + "\" for reading!", clRed);
      return;
   }
   TProgName = ReadString(fparam);
   fread(&TTyrePressure, sizeof(float), 1, fparam);
   fread(&total_step_T, sizeof(int), 1, fparam);
   fread(&total_T, sizeof(int), 1, fparam);
   fread(&num_T_poll, sizeof(int), 1, fparam);
   fread(&Tsettings[0][0], sizeof(Tsettings), 1, fparam);
   fread(&prog_step_T[0], sizeof(prog_step_T), 1, fparam);
   fread(&poll_step_T[0], sizeof(poll_step_T), 1, fparam);
   fclose(fparam);
   LogPrint("Loading TProg fm file: Total T=" + mSecToHMSStr(total_T), clLime);
}
// ---- End of ReadTProgFmFile -----------------------------------------------

void __fastcall WriteTProgToFile(void) // записать программу по времени в файл
{
   FILE *fparam;
   if ((fparam = fopen(AnsiString(TProgFName).c_str(), "wb")) == NULL)
   {
      LogPrint("Can't open file \"" + TProgFName + "\" for writing!", clRed);
      return;
   }
   WriteString(TProgName, fparam);
   fwrite(&TTyrePressure, sizeof(float), 1, fparam);
   fwrite(&total_step_T, sizeof(int), 1, fparam);
   fwrite(&total_T, sizeof(int), 1, fparam);
   fwrite(&num_T_poll, sizeof(int), 1, fparam);
   fwrite(&Tsettings[0][0], sizeof(Tsettings), 1, fparam);
   fwrite(&prog_step_T[0], sizeof(prog_step_T), 1, fparam);
   fwrite(&poll_step_T[0], sizeof(poll_step_T), 1, fparam);
   fclose(fparam);
}
// ---- End of WriteTProgFmFile ----------------------------------------------

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

String __fastcall IntToS( // Преобразование целого в строку длиной l
   int i, // преобразуемое число
   int l) // длина строки
{
   String ws;
   ws = String(i);
   int wl = ws.Length();
   if (wl < l)
   {
      ws = String(DupeString(' ', l - wl)) + ws;
   }
   return ws;
}
// ---- End of IntToS ------------------------------------------------------
