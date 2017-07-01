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

// переменные группы CtrlGr3 ------------------------------------------------
// блок DB10
extern int iDB10[GR3INTITEMSNUM];
extern int *T_end_cycle_1; // DB10,DINT10 Тип цикла 1
extern int *T_end_cycle_2; // DB10,DINT46 Тип цикла 2
extern int *type_cycle_1;
// DB10,INT4 Тип цикла 1                  S7:[S7 connection_4]DB10,INT4
extern int *StepsQty1; // DB10,INT34 Количество шагов программы 1
extern int *PollsQty1; // DB10,INT36 Количество опросов 1
extern int *type_cycle_2;
// DB10,INT40 Тип цикла 2                 S7:[S7 connection_4]DB10,INT4
extern int *StepsQty2; // DB10,INT70 Количество шагов программы 1
extern int *PollsQty2; // DB10,INT72 Количество опросов 1
extern float fDB10[GR3FLTITEMSNUM];
extern float *S_end_cycle_1;
// DB10,REAL18 Конечный пробег цикла 1    S7:[S7 connection_4]DB10,REAL18
extern float *DrumSpeed; // DB10,REAL22 Скорость барабана
extern float *Loading_1; // DB10,REAL26 Нагрузка 1
extern float *Radius_1; // DB10,REAL30 Радиус 1
extern float *S_end_cycle_2;
// DB10,REAL54 Конечный пробег цикла 2    S7:[S7 connection_4]DB10,REAL18
extern float *Loading_2; // DB10,REAL62 Нагрузка 2
extern float *Radius_2; // DB10,REAL66 Радиус 2
extern float *CorrASetSpeed; // DB10,REAL74 Корекция А по заданию скорости
extern float *CorrBSetSpeed; // DB10,REAL78 Корекция Б по заданию скорости
extern float *CorrAMeasSpeed; // DB10,REAL82 Корекция А по измерению скорости
extern float *CorrBMeasSpeed; // DB10,REAL86 Корекция Б по измерению скорости
extern float *Temp1LowLimit; // DB10,REAL90 Нижний предел датчика температуры 1
extern float *Temp1UpLimit; // DB10,REAL94 Верхний предел датчика температуры 1
extern float *CorrAMeasLoad1; // DB10,REAL98 Корекция А по измерению  нагрузки 1
extern float *CorrBMeasLoad1; // DB10,REAL102 Корекция Б по измерению нагрузки 1
extern float *Temp2LowLimit; // DB10,REAL106 Нижний предел датчика температуры 2
extern float *Temp2UpLimit; // DB10,REAL110 Верхний предел датчика температуры 2
extern float *CorrAMeasLoad2;
// DB10,REAL114 Корекция А по измерению  нагрузки 2
extern float *CorrBMeasLoad2; // DB10,REAL118 Корекция Б по измерению нагрузки 2
extern float *Rad1LowLimit;
// DB10,REAL122 Нижний предел измерений датчика радиуса 1
extern float *Rad1UpLimit;
// DB10,REAL126 Верхний предел измерений датчика радиуса 1
extern float *Rad2LowLimit;
// DB10,REAL130 Нижний предел измерений датчика радиуса 2
extern float *Rad2UpLimit;
// DB10,REAL134 Верхний предел измерений датчика радиуса 2

// адреса переменных в группе 3
extern wchar_t *Gr3ItemsNme[GR3ITEMSNUM];
// End of CtrlGr3 -----------------------------------------------------------
// переменные группы CtrlGr4 ------------------------------------------------
// блок DB8
extern float poll_step_SA[MAXNUMOFPOLLS];
// блок DB22
extern float step_SA[MAXNUMOFSTEPS];
// адреса переменных в группе 4
extern wchar_t *Gr4ItemsNme[GR4ITEMSNUM];
extern wchar_t Gr4ItemsAddr[GR4ITEMSNUM][ADDRLEN];
extern String AddrDB8, AddrDB22;
// End of CtrlGr4 -----------------------------------------------------------
// переменные группы CtrlGr5 ------------------------------------------------
// блок DB7
extern int poll_step_TA[MAXNUMOFPOLLS];
// блок DB21
extern int step_TA[MAXNUMOFSTEPS];
// адреса переменных в группе 5
extern wchar_t *Gr5ItemsNme[GR5ITEMSNUM];
extern wchar_t Gr5ItemsAddr[GR5ITEMSNUM][ADDRLEN];
extern String AddrDB7, AddrDB21;
// End of CtrlGr5 -----------------------------------------------------------
// переменные группы CtrlGr6 ------------------------------------------------
// блок DB23
extern float setting_A[2][MAXNUMOFSTEPS];
// адреса переменных в группе 6
extern wchar_t *Gr6ItemsNme[GR6ITEMSNUM];
extern wchar_t Gr6ItemsAddr[GR6ITEMSNUM][ADDRLEN];
extern String AddrDB23;
// End of CtrlGr6 -----------------------------------------------------------
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
// переменные группы CtrlGr8 ------------------------------------------------
// блок DB18
extern float poll_step_SB[MAXNUMOFPOLLS];
// блок DB32
extern float step_SB[MAXNUMOFSTEPS];
// адреса переменных в группе 8
extern wchar_t *Gr8ItemsNme[GR8ITEMSNUM];
extern wchar_t Gr8ItemsAddr[GR8ITEMSNUM][ADDRLEN];
extern String AddrDB18, AddrDB32;
// End of CtrlGr8 -----------------------------------------------------------
// переменные группы CtrlGr9 ------------------------------------------------
// блок DB17
extern int poll_step_TB[MAXNUMOFPOLLS];
// блок DB31
extern int step_TB[MAXNUMOFSTEPS];
// адреса переменных в группе 9
extern wchar_t *Gr9ItemsNme[GR9ITEMSNUM];
extern wchar_t Gr9ItemsAddr[GR9ITEMSNUM][ADDRLEN];
extern String AddrDB17, AddrDB31;
// End of CtrlGr9 -----------------------------------------------------------
// переменные группы CtrlGr10 -----------------------------------------------
// блок DB33
extern float setting_B[2][MAXNUMOFSTEPS];
// адреса переменных в группе 10
extern wchar_t *Gr10ItemsNme[GR10ITEMSNUM];
extern wchar_t Gr10ItemsAddr[GR10ITEMSNUM][ADDRLEN];
extern String AddrDB33;
// End of CtrlGr10 ----------------------------------------------------------
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
// переменные группы CtrlGr12 -----------------------------------------------
// блок DB71
extern float fDB71[GR12ITEMSNUM];
extern float *A1[GR12ARRAYSIZE];
// DB71,REAL2-172 Коэффициенты коррекции поз. 1    S7:[S7 connection_4]DB10,REAL18
extern float *Q1[GR12ARRAYSIZE];
// DB71,REAL6-176 границы действия коэффициентов коррекции поз. 1    S7:[S7 connection_4]DB10,REAL18
// адреса переменных в группе 12
extern wchar_t *Gr12ItemsNme[GR12ITEMSNUM];
// End of CtrlGr12 ----------------------------------------------------------
// переменные группы CtrlGr13 -----------------------------------------------
// блок DB70
extern float fDB70[GR13ITEMSNUM];
extern float *A2[GR13ARRAYSIZE];
// DB70,REAL2-172 Коэффициенты коррекции поз. 2    S7:[S7 connection_4]DB10,REAL18
extern float *Q2[GR13ARRAYSIZE];
// DB70,REAL6-176 границы действия коэффициентов коррекции поз. 2    S7:[S7 connection_4]DB10,REAL18
// адреса переменных в группе 13
extern wchar_t *Gr13ItemsNme[GR12ITEMSNUM];
// End of CtrlGr12 ----------------------------------------------------------

// объявление общих функций -------------------------------------------------
void ClearTProg(void); // сброс программы по времени
void ClearSProg(void); // сброс программы по пути
void __fastcall PntInit(void); // инициализация указателей для групп 12 и 13
void __fastcall ResetKA(float *A[]); // сброс массива А в единичку
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
