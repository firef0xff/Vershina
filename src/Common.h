#ifndef CommonH
#define CommonH
// ---------------------------------------------------------------------------
#include "TyreProt.h"
#include <stdio.h>
#include <Comctrls.hpp>
#include "def.h"
#include "opcrw.h"
#include <memory>
// объявление общих переменных ----------------------------------------------
extern TRichEdit *pPrt; // указатель на компонент для вывода протокола
extern HWND MainFormHandle; // дескриптор окна основной формы
extern String LogMess; // Строка для печати сообщений в журнале
extern HANDLE hOPCCtrlThrd; // Handler для потока CPU
extern unsigned OPCCtrlThrdID; // идентификатор потока CPU
extern bool OPCControlOn; // Управление OPC-сервером запущено
extern bool OPCConnectOK; // соединение с OPC-сервером установлено
extern int OldMode1, CurrMode1; // предидущий и текущий режим ручной/авто поз. 1
extern int OldMode2, CurrMode2; // предидущий и текущий режим ручной/авто поз. 2
extern int OldSMode1, CurrSMode1;
// предидущий и текущий режим старт/стоп поз. 1
extern int OldSMode2, CurrSMode2;
// предидущий и текущий режим старт/стоп поз. 2
extern int old_step_1; // предидущий номер шага по поз. 1
extern int cur_step_1; // текущий номер шага по поз. 1
extern int old_step_2; // предидущий номер шага по поз. 2
extern int cur_step_2; // текущий номер шага по поз. 2
extern float old_speed_1; // предидущая скорость по поз. 1
extern float cur_speed_1; // текущая скорость по поз. 1
extern int old_time_1; // продолжительность предидущего шага поз. 1
extern int cur_time_1; // продолжительность текущего шага поз. 1
extern float old_dist_1; // путь на предидущем шаге поз. 1
extern float cur_dist_1; // путь на текущем шаге поз. 1
extern float old_load_1; // нагрузка на предидущем шаге поз. 1
extern float cur_load_1; // нагрузка на текущем шаге поз. 1
extern float old_temp_1; // температура на предидущем шаге поз. 1
extern float cur_temp_1; // температура на текущем шаге поз. 1
extern float old_radius_1; // радиус на предидущем шаге поз. 1
extern float cur_radius_1; // радиус на текущем шаге поз. 1
extern float old_speed_2; // предидущая скорость по поз. 2
extern float cur_speed_2; // текущая скорость по поз. 2
extern int old_time_2; // продолжительность предидущего шага поз. 2
extern int cur_time_2; // продолжительность текущего шага поз. 2
extern float old_dist_2; // путь на предидущем шаге поз. 2
extern float cur_dist_2; // путь на текущем шаге поз. 2
extern float old_load_2; // нагрузка на предидущем шаге поз. 2
extern float cur_load_2; // нагрузка на текущем шаге поз. 2
extern float old_temp_2; // температура на предидущем шаге поз. 2
extern float cur_temp_2; // температура на текущем шаге поз. 2
extern float old_radius_2; // радиус на предидущем шаге поз. 2
extern float cur_radius_2; // радиус на текущем шаге поз. 2
extern bool CurrentStart1; // Текущее состояние поз. 1
extern bool CurrentStart2; // Текущее состояние поз. 2
// extern bool      Handle1On;                // Обработка событий по поз. 1 включена
// extern bool      Handle2On;                // Обработка событий по поз. 2 включена
extern short OPCCtrlStat; // управляющая переменная цикла управления стендом
extern long TimerCycleCnt; // Счетчик циклов таймера
// переменные протокола
extern std::unique_ptr<Tyre>InpTyre,
   // покрышка для ввода и редактирования протокола
   TyreA, // покрышка в поз. А
   TyreB; // покрышка в поз. Б
extern String TyreTypeA, TyreTypeB; // тип покрышки
extern String RunProgNameA, RunProgNameB; // наименвание программы обкатки
// рабочие переменные для программ испытаний
// программа по пути
extern String SProgFName; // имя файла для сохранения программы по пути
extern String SProgName; // имя программы испытаний по пути
extern float STyrePressure; // давление в шине
extern int total_step_S; // суммарное кол-во шагов программы по пути
extern float total_S; // суммарная продолжительность программы по пути, км
extern int num_S_poll; // количество опросов по пути
extern float poll_step_S[MAXNUMOFPOLLS]; // массив опросов по пути
extern float prog_step_S[MAXNUMOFSTEPS]; // массив шагов по пути
extern float Ssettings[2][MAXNUMOFSTEPS];
// массив нагрузок (1-й столбец) и скоростей (2-й столбец)
// программа по времени
extern String TProgFName; // имя файла для сохранения программы по времени
extern String TProgName; // имя программы испытаний по времени
extern float TTyrePressure; // давление в шине
extern int total_step_T; // суммарное кол-во шагов программы по времени
extern int total_T; // суммарная продолжительность программы по времени, мсек
extern int num_T_poll; // количество опросов по времени
extern int poll_step_T[MAXNUMOFPOLLS]; // массив опросов по времени
extern int prog_step_T[MAXNUMOFSTEPS]; // массив шагов по времени
extern float Tsettings[2][MAXNUMOFSTEPS];
extern bool switch_Carriage1;
extern bool switch_Carriage2;
// массив нагрузок (1-й столбец) и скоростей (2-й столбец)

// переменные группы CtrlGr7 ------------------------------------------------
// блок DB1
extern int read_TA[MAXNUMOFPOLLS];
// блок DB2
extern float read_VA[MAXNUMOFPOLLS];
// блок DB3
extern float read_SA[MAXNUMOFPOLLS];
// блок DB4
extern float read_LA[MAXNUMOFPOLLS];
// блок DB5
extern float read_RA[MAXNUMOFPOLLS];
// блок DB6
extern float read_TempA[MAXNUMOFPOLLS];
// адреса переменных в группе 7
extern wchar_t *Gr7ItemsNme[GR7ARRAYSNUM];
// End of CtrlGr7 -----------------------------------------------------------

// переменные группы CtrlGr11 -----------------------------------------------
// блок DB11
extern int read_TB[MAXNUMOFPOLLS];
// блок DB12
extern float read_VB[MAXNUMOFPOLLS];
// блок DB13
extern float read_SB[MAXNUMOFPOLLS];
// блок DB14
extern float read_LB[MAXNUMOFPOLLS];
// блок DB15
extern float read_RB[MAXNUMOFPOLLS];
// блок DB16
extern float read_TempB[MAXNUMOFPOLLS];
// адреса переменных в группе 11
extern wchar_t *Gr11ItemsNme[GR11ARRAYSNUM];
// End of CtrlGr11 ----------------------------------------------------------


// объявление общих функций -------------------------------------------------
void ClearTProg(void); // сброс программы по времени
void ClearSProg(void); // сброс программы по пути
void __fastcall ResetKA(float *A); // сброс массива А в единичку
void __fastcall LogPrint( // Вывод сообщений в окно протокола
   String, TColor = clWhite);
void __fastcall SLogPrint
   ( // Вывод сообщений в окно протокола при помощи SendMessage
   String, TColor = clWhite);
void __fastcall PLogPrint
   ( // Вывод сообщений в окно протокола при помощи PostMessage
   String, TColor = clWhite);
void __fastcall LogPrintF( // Вывод сообщений в файл журнала
   String FNme, // имя файла журнала
   String Mess, // сообщение
   TColor = clLime); // цвет сообщения в окне
String __fastcall LogFName(void); // Генерация имени файла журнала
String __fastcall FileNameParse
   ( // Функция выделения имени файла из полного пути
   String SFN);
int __fastcall NextCycleCount(void); // увеличение цикла счетчика на 1
void __fastcall OPCControlStart(TTimer*); // Запуск управления стендом
void __fastcall OPCControlStop(TTimer*); // Останов управления стендом
void __fastcall OPCControlPause(TTimer*); // Приостановка управления стендом
void __fastcall OPCControlResume(TTimer*); // Возобновление управления стендом
String __fastcall mSecToHMSStr(int tm);
// перевод целого кол-ва мсек в строку чч:мм:сс
String __fastcall ReadString(FILE *fp); // чтение строки типа String из файла
void __fastcall WriteString( // запись строки типа String в файл
   String ws, FILE *fp);
void __fastcall ReadSProgFmFile(void); // прочитать программу по пути из файла
void __fastcall WriteSProgToFile(void); // записать программу по пути в файл
float __fastcall StrToFlt(String);
// Преобразование строки в значение типа float
int __fastcall StrToI(String); // ПРеобразование строки в значение типа int
String __fastcall FltToStr( // Преобразование числа в строку длиной l
   float f, // преобразуемое число
   TFloatFormat ff, // формат
   int l, // длина строки
   int r); // длина дробной части
String __fastcall IntToS( // Преобразование целого в строку длиной l
   int i, // преобразуемое число
   int l); // длина строки
void __fastcall ReadTProgFmFile(void);
// прочитать программу по времени из файла
void __fastcall WriteTProgToFile(void); // записать программу по времени в файл
void __fastcall LeastSquares
   ( // расчет коэффициентов A и B методом наименьших квадратов
   float X[], // массив X
   float Y[], // массив Y
   int N, // размерность массива
   float &A, //
   float &B); //
int __fastcall BUnion(bool b1, bool b2);
// объединение занчений аргументов в целое значение

// настройки сохранения
extern String strDistProg;
extern String strTimeProg;
extern String strProtA;
extern String strProtB;
extern String strTitleProt;
extern String strLoadCalibrA;
extern String strLoadCalibrB;
extern String strTCalibrA;
extern String strTCalibrB;
extern String strRCalibrA;
extern String strRCalibrB;
extern String strSpdCalibr;
extern String strSertPrintProtA;
extern String strSertPrintProtB;
extern bool AutoSave;
extern bool needSaveA, needSaveB;
// индикаторы автосохранения протоколов за испытание
extern bool StendConnection; // индикатор связи со стендом
#ifdef _DEBUG
extern int ThreadCounter;
#endif
#endif
