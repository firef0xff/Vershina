// ---------------------------------------------------------------------------
#include <stdio.h>
#include <process.h>
#include <DateUtils.hpp>
#include <StrUtils.hpp>
#pragma hdrstop
#include "def.h"
#include "opcrw.h"
#include "TyreProt.h"
#include "Common.h"
#include "OPCControl.h"

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

// переменные группы CtrlGr2 ------------------------------------------------
// Блок DB20 - общие параметры
float fDB20[GR2FLOATITEMSNUM];
float *fakt_speed = &fDB20[0]; // DB20,REAL2 фактическая скорость
float *set_speed = &fDB20[1]; // DB20,REAL6 заданная скорость
float *fakt_distance = &fDB20[2]; // DB20,REAL10 общий пробег
float *fakt_distance_1 = &fDB20[3]; // DB20,REAL18 факт. пробег 1
float *fakt_loading_1 = &fDB20[4]; // DB20,REAL22 факт. нагрузка 1
float *fakt_radius_1 = &fDB20[5]; // DB20,REAL30 факт. радиус 1
float *fakt_temper_1 = &fDB20[6]; // DB20,REAL34 факт. температура 1
float *set_speed_1 = &fDB20[7];
// DB20,REAL46 заданная скорость 1 на текущем шаге
float *set_loading_1 = &fDB20[8];
// DB20,REAL50 заданная нагрузка 1 на текущем шаге
float *fakt_distance_2 = &fDB20[9]; // DB20,REAL58 факт. пробег 2
float *fakt_loading_2 = &fDB20[10]; // DB20,REAL62 факт. нагрузка 2
float *fakt_radius_2 = &fDB20[11]; // DB20,REAL70 факт. радиус 2
float *fakt_temper_2 = &fDB20[12]; // DB20,REAL74 факт. температура 2
float *set_speed_2 = &fDB20[13];
// DB20,REAL86 заданная скорость 2 на текущем шаге
float *set_loading_2 = &fDB20[14];
// DB20,REAL90 заданная нагрузка 2 на текущем шаге
float *next_step_distance1 = &fDB20[15];
// DB20,REAL156 номер следующего шага опроса по пробегу 1
float *next_step_distance2 = &fDB20[16];
// DB20,REAL160 номер следующего шага опроса по пробегу 2
float *next_speed1 = &fDB20[17]; // DB20,REAL164 скорость на следующем шаге1
float *next_speed2 = &fDB20[18]; // DB20,REAL168 скорость на следующем шаге2
float *next_loading1 = &fDB20[19]; // DB20,REAL172 нагрузка на следующем шаге1
float *next_loading2 = &fDB20[20]; // DB20,REAL176 нагрузка на следующем шаге2
float *next_set_distance1 = &fDB20[21]; // DB20,REAL196
float *next_set_distance2 = &fDB20[22]; // DB20,REAL200

int i2DB20[GR2INTITEMSNUM];
int *next_set_time1 = &i2DB20[0]; // DB20,DINT188
int *next_set_time2 = &i2DB20[1]; // DB20,DINT192
// адреса переменных в блоке DB20
wchar_t *Gr2ItemsNme[GR2ITEMSNUM] =
{L"S7:[S7 connection_4]DB20,REAL2", L"S7:[S7 connection_4]DB20,REAL6",
   L"S7:[S7 connection_4]DB20,REAL10", L"S7:[S7 connection_4]DB20,REAL18",
   L"S7:[S7 connection_4]DB20,REAL22", L"S7:[S7 connection_4]DB20,REAL30",
   L"S7:[S7 connection_4]DB20,REAL34", L"S7:[S7 connection_4]DB20,REAL46",
   L"S7:[S7 connection_4]DB20,REAL50", L"S7:[S7 connection_4]DB20,REAL58",
   L"S7:[S7 connection_4]DB20,REAL62", L"S7:[S7 connection_4]DB20,REAL70",
   L"S7:[S7 connection_4]DB20,REAL74", L"S7:[S7 connection_4]DB20,REAL86",
   L"S7:[S7 connection_4]DB20,REAL90", L"S7:[S7 connection_4]DB20,REAL156",
   L"S7:[S7 connection_4]DB20,REAL160", L"S7:[S7 connection_4]DB20,REAL164",
   L"S7:[S7 connection_4]DB20,REAL168", L"S7:[S7 connection_4]DB20,REAL172",
   L"S7:[S7 connection_4]DB20,REAL176", L"S7:[S7 connection_4]DB20,REAL196",
   L"S7:[S7 connection_4]DB20,REAL200", L"S7:[S7 connection_4]DB20,DINT188",
   L"S7:[S7 connection_4]DB20,DINT192"};
// End of CtrlGr2 -----------------------------------------------------------
// переменные группы CtrlGr3 ------------------------------------------------
// блок DB10
int iDB10[GR3INTITEMSNUM];
int *T_end_cycle_1 = &iDB10[0]; // DB10,DINT10 Конечное время цикла 1
int *T_end_cycle_2 = &iDB10[1]; // DB10,DINT46 Конечное время цикла 2
int *type_cycle_1 = &iDB10[2];
// DB10,INT4 Тип цикла 1                  S7:[S7 connection_4]DB10,INT4
int *StepsQty1 = &iDB10[3]; // DB10,INT34 Количество шагов программы 1
int *PollsQty1 = &iDB10[4]; // DB10,INT36 Количество опросов 1
int *type_cycle_2 = &iDB10[5];
// DB10,INT40 Тип цикла 2                 S7:[S7 connection_4]DB10,INT4
int *StepsQty2 = &iDB10[6]; // DB10,INT70 Количество шагов программы 1
int *PollsQty2 = &iDB10[7]; // DB10,INT72 Количество опросов 1
float fDB10[GR3FLTITEMSNUM];
float *S_end_cycle_1 = &fDB10[0];
// DB10,REAL18 Конечный пробег цикла 1    S7:[S7 connection_4]DB10,REAL18
float *DrumSpeed = &fDB10[1]; // DB10,REAL22 Скорость барабана
float *Loading_1 = &fDB10[2]; // DB10,REAL26 Нагрузка 1
float *Radius_1 = &fDB10[3]; // DB10,REAL30 Радиус 1
float *S_end_cycle_2 = &fDB10[4];
// DB10,REAL54 Конечный пробег цикла 2    S7:[S7 connection_4]DB10,REAL18
float *Loading_2 = &fDB10[5]; // DB10,REAL62 Нагрузка 2
float *Radius_2 = &fDB10[6]; // DB10,REAL66 Радиус 2
float *CorrASetSpeed = &fDB10[7]; // DB10,REAL74 Корекция А по заданию скорости
float *CorrBSetSpeed = &fDB10[8]; // DB10,REAL78 Корекция Б по заданию скорости
float *CorrAMeasSpeed = &fDB10[9];
// DB10,REAL82 Корекция А по измерению скорости
float *CorrBMeasSpeed = &fDB10[10];
// DB10,REAL86 Корекция Б по измерению скорости
float *Temp1LowLimit = &fDB10[11];
// DB10,REAL90 Нижний предел датчика температуры 1
float *Temp1UpLimit = &fDB10[12];
// DB10,REAL94 Верхний предел датчика температуры 1
float *CorrAMeasLoad1 = &fDB10[13];
// DB10,REAL98 Корекция А по измерению  нагрузки 1
float *CorrBMeasLoad1 = &fDB10[14];
// DB10,REAL102 Корекция Б по измерению нагрузки 1
float *Temp2LowLimit = &fDB10[15];
// DB10,REAL106 Нижний предел датчика температуры 2
float *Temp2UpLimit = &fDB10[16];
// DB10,REAL110 Верхний предел датчика температуры 2
float *CorrAMeasLoad2 = &fDB10[17];
// DB10,REAL114 Корекция А по измерению  нагрузки 2
float *CorrBMeasLoad2 = &fDB10[18];
// DB10,REAL118 Корекция Б по измерению нагрузки 2
float *Rad1LowLimit = &fDB10[19];
// DB10,REAL122 Нижний предел измерений датчика радиуса 1
float *Rad1UpLimit = &fDB10[20];
// DB10,REAL126 Верхний предел измерений датчика радиуса 1
float *Rad2LowLimit = &fDB10[21];
// DB10,REAL130 Нижний предел измерений датчика радиуса 2
float *Rad2UpLimit = &fDB10[22];
// DB10,REAL134 Верхний предел измерений датчика радиуса 2

// адреса переменных в блоке DB10
wchar_t *Gr3ItemsNme[GR3ITEMSNUM] =
{L"S7:[S7 connection_4]DB10,DINT10", L"S7:[S7 connection_4]DB10,DINT46",
   L"S7:[S7 connection_4]DB10,INT4", L"S7:[S7 connection_4]DB10,INT34",
   L"S7:[S7 connection_4]DB10,INT36", L"S7:[S7 connection_4]DB10,INT40",
   L"S7:[S7 connection_4]DB10,INT70", L"S7:[S7 connection_4]DB10,INT72",
   L"S7:[S7 connection_4]DB10,REAL18", L"S7:[S7 connection_4]DB10,REAL22",
   L"S7:[S7 connection_4]DB10,REAL26", L"S7:[S7 connection_4]DB10,REAL30",
   L"S7:[S7 connection_4]DB10,REAL54", L"S7:[S7 connection_4]DB10,REAL62",
   L"S7:[S7 connection_4]DB10,REAL66", L"S7:[S7 connection_4]DB10,REAL74",
   L"S7:[S7 connection_4]DB10,REAL78", L"S7:[S7 connection_4]DB10,REAL82",
   L"S7:[S7 connection_4]DB10,REAL86", L"S7:[S7 connection_4]DB10,REAL90",
   L"S7:[S7 connection_4]DB10,REAL94", L"S7:[S7 connection_4]DB10,REAL98",
   L"S7:[S7 connection_4]DB10,REAL102", L"S7:[S7 connection_4]DB10,REAL106",
   L"S7:[S7 connection_4]DB10,REAL110", L"S7:[S7 connection_4]DB10,REAL114",
   L"S7:[S7 connection_4]DB10,REAL118", L"S7:[S7 connection_4]DB10,REAL122",
   L"S7:[S7 connection_4]DB10,REAL126", L"S7:[S7 connection_4]DB10,REAL130",
   L"S7:[S7 connection_4]DB10,REAL134", };
// End of CtrlGr3 -----------------------------------------------------------
// переменные группы CtrlGr4 ------------------------------------------------
// блок DB8
float poll_step_SA[MAXNUMOFPOLLS];
// блок DB22
float step_SA[MAXNUMOFSTEPS];
wchar_t *Gr4ItemsNme[GR4ITEMSNUM] =
{NULL};
wchar_t Gr4ItemsAddr[GR4ITEMSNUM][ADDRLEN] =
{L""};
String AddrDB8 = "S7:[S7 connection_4]DB8,REAL", AddrDB22 =
   "S7:[S7 connection_4]DB22,REAL";
// End of CtrlGr4 -----------------------------------------------------------
// переменные группы CtrlGr5 ------------------------------------------------
// блок DB7
int poll_step_TA[MAXNUMOFPOLLS];
// блок DB21
int step_TA[MAXNUMOFSTEPS];
wchar_t *Gr5ItemsNme[GR5ITEMSNUM] =
{NULL};
wchar_t Gr5ItemsAddr[GR5ITEMSNUM][ADDRLEN] =
{L""};
String AddrDB7 = "S7:[S7 connection_4]DB7,DINT", AddrDB21 =
   "S7:[S7 connection_4]DB21,DINT";
// End of CtrlGr5 -----------------------------------------------------------
// переменные группы CtrlGr6 ------------------------------------------------
// блок DB23
float setting_A[2][100];
wchar_t *Gr6ItemsNme[GR6ITEMSNUM] =
{NULL};
wchar_t Gr6ItemsAddr[GR6ITEMSNUM][ADDRLEN] =
{L""};
String AddrDB23 = "S7:[S7 connection_4]DB23,REAL";
// End of CtrlGr6 -----------------------------------------------------------
// переменные группы CtrlGr7 ------------------------------------------------
// блок DB1
int read_TA[MAXNUMOFPOLLS];
// блок DB2
float read_VA[MAXNUMOFPOLLS];
// блок DB3
float read_SA[MAXNUMOFPOLLS];
// блок DB4
float read_LA[MAXNUMOFPOLLS];
// блок DB5
float read_RA[MAXNUMOFPOLLS];
// блок DB6
float read_TempA[MAXNUMOFPOLLS];
// адреса переменных в группе 7
wchar_t *Gr7ItemsNme[GR7ARRAYSNUM] =
{L"S7:[S7 connection_4]DB1,DINT2,250", L"S7:[S7 connection_4]DB2,REAL2,250",
   L"S7:[S7 connection_4]DB3,REAL2,250", L"S7:[S7 connection_4]DB4,REAL2,250",
   L"S7:[S7 connection_4]DB5,REAL2,250", L"S7:[S7 connection_4]DB6,REAL2,250",
};
// End of CtrlGr7 -----------------------------------------------------------
// переменные группы CtrlGr8 ------------------------------------------------
// блок DB18
float poll_step_SB[MAXNUMOFPOLLS];
// блок DB32
float step_SB[MAXNUMOFSTEPS];
// адреса переменных в группе 8
wchar_t *Gr8ItemsNme[GR8ITEMSNUM] =
{NULL};
wchar_t Gr8ItemsAddr[GR8ITEMSNUM][ADDRLEN] =
{L""};
String AddrDB18 = "S7:[S7 connection_4]DB18,REAL", AddrDB32 =
   "S7:[S7 connection_4]DB32,REAL";
// End of CtrlGr8 -----------------------------------------------------------
// переменные группы CtrlGr9 ------------------------------------------------
// блок DB17
int poll_step_TB[MAXNUMOFPOLLS];
// блок DB31
int step_TB[MAXNUMOFSTEPS];
// адреса переменных в группе 9
wchar_t *Gr9ItemsNme[GR9ITEMSNUM] =
{NULL};
wchar_t Gr9ItemsAddr[GR9ITEMSNUM][ADDRLEN] =
{L""};
String AddrDB17 = "S7:[S7 connection_4]DB17,DINT", AddrDB31 =
   "S7:[S7 connection_4]DB31,DINT";
// End of CtrlGr9 -----------------------------------------------------------
// переменные группы CtrlGr10 -----------------------------------------------
// блок DB33
float setting_B[2][MAXNUMOFSTEPS];
// адреса переменных в группе 10
wchar_t *Gr10ItemsNme[GR10ITEMSNUM] =
{NULL};
wchar_t Gr10ItemsAddr[GR10ITEMSNUM][ADDRLEN] =
{L""};
String AddrDB33 = "S7:[S7 connection_4]DB33,REAL";
// End of CtrlGr10 ----------------------------------------------------------
// переменные группы CtrlGr11 -----------------------------------------------
// блок DB11
int read_TB[MAXNUMOFPOLLS];
// блок DB12
float read_VB[MAXNUMOFPOLLS];
// блок DB13
float read_SB[MAXNUMOFPOLLS];
// блок DB14
float read_LB[MAXNUMOFPOLLS];
// блок DB15
float read_RB[MAXNUMOFPOLLS];
// блок DB16
float read_TempB[MAXNUMOFPOLLS];
// адреса переменных в группе 11
wchar_t *Gr11ItemsNme[GR11ARRAYSNUM] =
{L"S7:[S7 connection_4]DB11,DINT2,250", L"S7:[S7 connection_4]DB12,REAL2,250",
   L"S7:[S7 connection_4]DB13,REAL2,250", L"S7:[S7 connection_4]DB14,REAL2,250",
   L"S7:[S7 connection_4]DB15,REAL2,250", L"S7:[S7 connection_4]DB16,REAL2,250",
};
// End of CtrlGr11 ----------------------------------------------------------
// переменные группы CtrlGr12 -----------------------------------------------
// блок DB71
float fDB71[GR12ITEMSNUM];
float *A1[GR12ARRAYSIZE];
// DB71,REAL2-172 Коэффициенты коррекции поз. 1    S7:[S7 connection_4]DB10,REAL18
float *Q1[GR12ARRAYSIZE];
// DB71,REAL6-176 границы действия коэффициентов коррекции поз. 1    S7:[S7 connection_4]DB10,REAL18
// адреса переменных в группе 12
wchar_t *Gr12ItemsNme[GR12ITEMSNUM] =
{ // Коэффициент коррекции прямой ход
   L"S7:[S7 connection_4]DB71,REAL180", L"S7:[S7 connection_4]DB71,REAL188",
   L"S7:[S7 connection_4]DB71,REAL196", L"S7:[S7 connection_4]DB71,REAL204",
   L"S7:[S7 connection_4]DB71,REAL212", L"S7:[S7 connection_4]DB71,REAL2",
   L"S7:[S7 connection_4]DB71,REAL10", L"S7:[S7 connection_4]DB71,REAL18",
   L"S7:[S7 connection_4]DB71,REAL26", L"S7:[S7 connection_4]DB71,REAL34",
   L"S7:[S7 connection_4]DB71,REAL42", L"S7:[S7 connection_4]DB71,REAL50",
   L"S7:[S7 connection_4]DB71,REAL58", L"S7:[S7 connection_4]DB71,REAL66",
   L"S7:[S7 connection_4]DB71,REAL74", L"S7:[S7 connection_4]DB71,REAL260",
   L"S7:[S7 connection_4]DB71,REAL268", L"S7:[S7 connection_4]DB71,REAL276",
   L"S7:[S7 connection_4]DB71,REAL284", L"S7:[S7 connection_4]DB71,REAL292",

   // Коэффициент коррекции обратный ход
   L"S7:[S7 connection_4]DB71,REAL300", L"S7:[S7 connection_4]DB71,REAL308",
   L"S7:[S7 connection_4]DB71,REAL316", L"S7:[S7 connection_4]DB71,REAL324",
   L"S7:[S7 connection_4]DB71,REAL332", L"S7:[S7 connection_4]DB71,REAL100",
   L"S7:[S7 connection_4]DB71,REAL108", L"S7:[S7 connection_4]DB71,REAL116",
   L"S7:[S7 connection_4]DB71,REAL124", L"S7:[S7 connection_4]DB71,REAL132",
   L"S7:[S7 connection_4]DB71,REAL140", L"S7:[S7 connection_4]DB71,REAL148",
   L"S7:[S7 connection_4]DB71,REAL156", L"S7:[S7 connection_4]DB71,REAL164",
   L"S7:[S7 connection_4]DB71,REAL172", L"S7:[S7 connection_4]DB71,REAL220",
   L"S7:[S7 connection_4]DB71,REAL228", L"S7:[S7 connection_4]DB71,REAL236",
   L"S7:[S7 connection_4]DB71,REAL244", L"S7:[S7 connection_4]DB71,REAL252",

   // Граница действия прямой ход
   L"S7:[S7 connection_4]DB71,REAL184", L"S7:[S7 connection_4]DB71,REAL192",
   L"S7:[S7 connection_4]DB71,REAL200", L"S7:[S7 connection_4]DB71,REAL208",
   L"S7:[S7 connection_4]DB71,REAL216", L"S7:[S7 connection_4]DB71,REAL6",
   L"S7:[S7 connection_4]DB71,REAL14", L"S7:[S7 connection_4]DB71,REAL22",
   L"S7:[S7 connection_4]DB71,REAL30", L"S7:[S7 connection_4]DB71,REAL38",
   L"S7:[S7 connection_4]DB71,REAL46", L"S7:[S7 connection_4]DB71,REAL54",
   L"S7:[S7 connection_4]DB71,REAL62", L"S7:[S7 connection_4]DB71,REAL70",
   L"S7:[S7 connection_4]DB71,REAL78", L"S7:[S7 connection_4]DB71,REAL264",
   L"S7:[S7 connection_4]DB71,REAL272", L"S7:[S7 connection_4]DB71,REAL280",
   L"S7:[S7 connection_4]DB71,REAL288", L"S7:[S7 connection_4]DB71,REAL296",

   // Граница действия обратный ход
   L"S7:[S7 connection_4]DB71,REAL304", L"S7:[S7 connection_4]DB71,REAL312",
   L"S7:[S7 connection_4]DB71,REAL320", L"S7:[S7 connection_4]DB71,REAL328",
   L"S7:[S7 connection_4]DB71,REAL336", L"S7:[S7 connection_4]DB71,REAL104",
   L"S7:[S7 connection_4]DB71,REAL112", L"S7:[S7 connection_4]DB71,REAL120",
   L"S7:[S7 connection_4]DB71,REAL128", L"S7:[S7 connection_4]DB71,REAL136",
   L"S7:[S7 connection_4]DB71,REAL144", L"S7:[S7 connection_4]DB71,REAL152",
   L"S7:[S7 connection_4]DB71,REAL160", L"S7:[S7 connection_4]DB71,REAL168",
   L"S7:[S7 connection_4]DB71,REAL176", L"S7:[S7 connection_4]DB71,REAL224",
   L"S7:[S7 connection_4]DB71,REAL232", L"S7:[S7 connection_4]DB71,REAL240",
   L"S7:[S7 connection_4]DB71,REAL248", L"S7:[S7 connection_4]DB71,REAL256"};

// End of CtrlGr12 ----------------------------------------------------------
// переменные группы CtrlGr13 -----------------------------------------------
// блок DB70
float fDB70[GR13ITEMSNUM];
float *A2[GR13ARRAYSIZE];
// DB70,REAL2-172 Коэффициенты коррекции поз. 2    S7:[S7 connection_4]DB10,REAL18
float *Q2[GR13ARRAYSIZE];
// DB70,REAL6-176 границы действия коэффициентов коррекции поз. 2    S7:[S7 connection_4]DB10,REAL18
// адреса переменных в группе 13
wchar_t *Gr13ItemsNme[GR13ITEMSNUM] =
{ // Коэффициент коррекции прямой ход
   L"S7:[S7 connection_4]DB70,REAL180", L"S7:[S7 connection_4]DB70,REAL188",
   L"S7:[S7 connection_4]DB70,REAL196", L"S7:[S7 connection_4]DB70,REAL204",
   L"S7:[S7 connection_4]DB70,REAL212", L"S7:[S7 connection_4]DB70,REAL2",
   L"S7:[S7 connection_4]DB70,REAL10", L"S7:[S7 connection_4]DB70,REAL18",
   L"S7:[S7 connection_4]DB70,REAL26", L"S7:[S7 connection_4]DB70,REAL34",
   L"S7:[S7 connection_4]DB70,REAL42", L"S7:[S7 connection_4]DB70,REAL50",
   L"S7:[S7 connection_4]DB70,REAL58", L"S7:[S7 connection_4]DB70,REAL66",
   L"S7:[S7 connection_4]DB70,REAL74", L"S7:[S7 connection_4]DB70,REAL260",
   L"S7:[S7 connection_4]DB70,REAL268", L"S7:[S7 connection_4]DB70,REAL276",
   L"S7:[S7 connection_4]DB70,REAL284", L"S7:[S7 connection_4]DB70,REAL292",

   // Коэффициент коррекции обратный ход

   L"S7:[S7 connection_4]DB70,REAL300", L"S7:[S7 connection_4]DB70,REAL308",
   L"S7:[S7 connection_4]DB70,REAL316", L"S7:[S7 connection_4]DB70,REAL324",
   L"S7:[S7 connection_4]DB70,REAL332", L"S7:[S7 connection_4]DB70,REAL100",
   L"S7:[S7 connection_4]DB70,REAL108", L"S7:[S7 connection_4]DB70,REAL116",
   L"S7:[S7 connection_4]DB70,REAL124", L"S7:[S7 connection_4]DB70,REAL132",
   L"S7:[S7 connection_4]DB70,REAL140", L"S7:[S7 connection_4]DB70,REAL148",
   L"S7:[S7 connection_4]DB70,REAL156", L"S7:[S7 connection_4]DB70,REAL164",
   L"S7:[S7 connection_4]DB70,REAL172", L"S7:[S7 connection_4]DB70,REAL220",
   L"S7:[S7 connection_4]DB70,REAL228", L"S7:[S7 connection_4]DB70,REAL236",
   L"S7:[S7 connection_4]DB70,REAL244", L"S7:[S7 connection_4]DB70,REAL252",

   // Граница действия прямой ход
   L"S7:[S7 connection_4]DB70,REAL184", L"S7:[S7 connection_4]DB70,REAL192",
   L"S7:[S7 connection_4]DB70,REAL200", L"S7:[S7 connection_4]DB70,REAL208",
   L"S7:[S7 connection_4]DB70,REAL216", L"S7:[S7 connection_4]DB70,REAL6",
   L"S7:[S7 connection_4]DB70,REAL14", L"S7:[S7 connection_4]DB70,REAL22",
   L"S7:[S7 connection_4]DB70,REAL30", L"S7:[S7 connection_4]DB70,REAL38",
   L"S7:[S7 connection_4]DB70,REAL46", L"S7:[S7 connection_4]DB70,REAL54",
   L"S7:[S7 connection_4]DB70,REAL62", L"S7:[S7 connection_4]DB70,REAL70",
   L"S7:[S7 connection_4]DB70,REAL78", L"S7:[S7 connection_4]DB70,REAL264",
   L"S7:[S7 connection_4]DB70,REAL272", L"S7:[S7 connection_4]DB70,REAL280",
   L"S7:[S7 connection_4]DB70,REAL288", L"S7:[S7 connection_4]DB70,REAL296",

   // Граница действия обратный ход

   L"S7:[S7 connection_4]DB70,REAL304", L"S7:[S7 connection_4]DB70,REAL312",
   L"S7:[S7 connection_4]DB70,REAL320", L"S7:[S7 connection_4]DB70,REAL328",
   L"S7:[S7 connection_4]DB70,REAL336", L"S7:[S7 connection_4]DB70,REAL104",
   L"S7:[S7 connection_4]DB70,REAL112", L"S7:[S7 connection_4]DB70,REAL120",
   L"S7:[S7 connection_4]DB70,REAL128", L"S7:[S7 connection_4]DB70,REAL136",
   L"S7:[S7 connection_4]DB70,REAL144", L"S7:[S7 connection_4]DB70,REAL152",
   L"S7:[S7 connection_4]DB70,REAL160", L"S7:[S7 connection_4]DB70,REAL168",
   L"S7:[S7 connection_4]DB70,REAL176", L"S7:[S7 connection_4]DB70,REAL224",
   L"S7:[S7 connection_4]DB70,REAL232", L"S7:[S7 connection_4]DB70,REAL240",
   L"S7:[S7 connection_4]DB70,REAL248", L"S7:[S7 connection_4]DB70,REAL256"};
// End of CtrlGr12 ----------------------------------------------------------

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
void __fastcall PntInit(void) // инициализация указателей для групп 12 и 13
{
   for (int i = 0; i < GR12ARRAYSIZE; i++)
   {
      A1[i] = &fDB71[i];
      Q1[i] = &fDB71[i + GR12ARRAYSIZE];
   }
   for (int i = 0; i < GR13ARRAYSIZE; i++)
   {
      A2[i] = &fDB70[i];
      Q2[i] = &fDB70[i + GR13ARRAYSIZE];
   }
}
// ---- End of PntInit -------------------------------------------------------

void __fastcall ResetKA(float *A[]) // сброс массива А в единичку
{
   for (int i = 0; i < GR12ARRAYSIZE; i++)
   {
      *A[i] = 1.0;
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
