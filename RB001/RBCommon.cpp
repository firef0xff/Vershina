//---------------------------------------------------------------------------
#include <stdio.h>
#include <process.h>
#include <DateUtils.hpp>
#include <StrUtils.hpp>
#pragma hdrstop
#include "def.h"
#include "opcrw.h"
#include "TyreProt.h"
#include "RBCommon.h"
#include "OPCControl.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#ifdef _DEBUG
extern int ThreadCounter=0;
#endif
extern OPCRW *pOPC=0;// ��������� �� ����� OPCRW
extern CD_9904_interface *cd_9904=0;
extern HANDLE CD_9904Thread=0;
extern bool needSaveA=false,
			needSaveB=false;     //���������� �������������� ���������� �� ���������
extern bool StendConnection=false;//��������� ����� �� �������

bool  switch_Carriage1=false;     //�������� ��� ��������� ��������� ��������� �������
bool  switch_Carriage2=false;

String 	strDistProg="",
		strTimeProg="",
		strProtA="",
		strProtB="",
		strTitleProt="",
		strLoadCalibrA="",
		strLoadCalibrB="",
		strTCalibrA="",
		strTCalibrB="",
		strRCalibrA="",
		strRCalibrB="",
		strSpdCalibr="",
		strSertPrintProtA="",
		strSertPrintProtB="";
bool AutoSave=false;
TRichEdit *pPrt;                // ��������� �� ��������� ��� ������ ���������
HWND      MainFormHandle;       // ���������� ���� �������� �����
String    LogMess="";           // ������ ��� ������ ��������� � �������
HANDLE    hOPCCtrlThrd;         // Handler ��� ������ CPU
unsigned  OPCCtrlThrdID;        // ������������� ������ CPU
bool      OPCControlOn=false;   // ���������� OPC-�������� ��������
bool      OPCConnectOK=false;   // ���������� � OPC-�������� �����������
int       OldMode1,CurrMode1;   // ���������� � ������� ����� ������/���� ���. 1
int       OldMode2,CurrMode2;   // ���������� � ������� ����� ������/���� ���. 2
int       OldSMode1,CurrSMode1; // ���������� � ������� ����� �����/���� ���. 1
int       OldSMode2,CurrSMode2; // ���������� � ������� ����� �����/���� ���. 2
int       old_step_1=1;         // ���������� ����� ���� �� ���. 1
int       cur_step_1=1;         // ������� ����� ���� �� ���. 1
int       old_step_2=1;         // ���������� ����� ���� �� ���. 2
int       cur_step_2=1;         // ������� ����� ���� �� ���. 2
float     old_speed_1=0.0;      // ���������� �������� �� ���. 1
float     cur_speed_1=0.0;      // ������� �������� �� ���. 1
int       old_time_1=0;         // ����������������� ����������� ���� ���. 1
int       cur_time_1=0;         // ����������������� �������� ���� ���. 1
float     old_dist_1=0.0;       // ���� �� ���������� ���� ���. 1
float     cur_dist_1=0.0;       // ���� �� ������� ���� ���. 1
float     old_load_1=0.0;       // �������� �� ���������� ���� ���. 1
float     cur_load_1=0.0;       // �������� �� ������� ���� ���. 1
float     old_temp_1=0.0;       // ����������� �� ���������� ���� ���. 1
float     cur_temp_1=0.0;       // ����������� �� ������� ���� ���. 1
float     old_radius_1=0.0;     // ������ �� ���������� ���� ���. 1
float     cur_radius_1=0.0;     // ������ �� ������� ���� ���. 1
float     old_speed_2=0.0;      // ���������� �������� �� ���. 2
float     cur_speed_2=0.0;      // ������� �������� �� ���. 2
int       old_time_2=0;         // ����������������� ����������� ���� ���. 2
int       cur_time_2=0;         // ����������������� �������� ���� ���. 2
float     old_dist_2=0.0;       // ���� �� ���������� ���� ���. 2
float     cur_dist_2=0.0;       // ���� �� ������� ���� ���. 2
float     old_load_2=0.0;       // �������� �� ���������� ���� ���. 2
float     cur_load_2=0.0;       // �������� �� ������� ���� ���. 2
float     old_temp_2=0.0;       // ����������� �� ���������� ���� ���. 2
float     cur_temp_2=0.0;       // ����������� �� ������� ���� ���. 2
float     old_radius_2=0.0;     // ������ �� ���������� ���� ���. 2
float     cur_radius_2=0.0;     // ������ �� ������� ���� ���. 2
bool      CurrentStart1=false;  // ������� ��������� ���. 1
bool      CurrentStart2=false;  // ������� ��������� ���. 2
//bool      Handle1On=true;       // ��������� ������� �� ���. 1 ��������
//bool      Handle2On=true;       // ��������� ������� �� ���. 2 ��������
short     OPCCtrlStat=0;        // ����������� ���������� ����� ���������� �������
long      TimerCycleCnt=0;      // ������� ������ �������
// ���������� ���������
//Tyre      *InpTyre,             // �������� ��� ����� � �������������� ���������
//          *TyreA,               // �������� � ���. �
//          *TyreB;               // �������� � ���. �
String    TyreTypeA="�",
          TyreTypeB="�";        // ��� ��������
String    RunProgNameA="���� 1",
          RunProgNameB="���� 2";// ����������� ��������� �������

// ������� ���������� ��� �������� ���������
// ��������� �� ����
String SProgFName="";           // ��� ����� ��� ���������� ��������� �� ����
String SProgName ="";           // ��� ��������� ��������� �� ����
float  STyrePressure=0;         // �������� � ����
int    total_step_S =0;         // ��������� ���-�� ����� ��������� �� ����
float  total_S      =0;         // ��������� ����������������� ��������� �� ����, ��
int    num_S_poll   =0;         // ���������� ������� �� ����
float  poll_step_S[MAXNUMOFPOLLS] ={0}; // ������ ������� �� ����
float  prog_step_S[MAXNUMOFSTEPS] ={0}; // ������ ����� �� ����
float  Ssettings[2][MAXNUMOFSTEPS]={0}; // ������ �������� (1-� �������) � ��������� (2-� �������)
// ��������� �� �������
String TProgFName="";           // ��� ����� ��� ���������� ��������� �� �������
String TProgName ="";           // ��� ��������� ��������� �� �������
float  TTyrePressure=0;         // �������� � ����
int    total_step_T =0;         // ��������� ���-�� ����� ��������� �� �������
int    total_T      =0;         // ��������� ����������������� ��������� �� �������, ����
int    num_T_poll   =0;         // ���������� ������� �� �������
int    poll_step_T[MAXNUMOFPOLLS] ={0}; // ������ ������� �� �������
int    prog_step_T[MAXNUMOFSTEPS] ={0}; // ������ ����� �� �������
float  Tsettings[2][MAXNUMOFSTEPS]={0}; // ������ �������� (1-� �������) � ��������� (2-� �������)

// ���������� ������ CtrlGr1 ------------------------------------------------
// MEMORY
bool  bGr1[GR1BOOLITEMSNUM];    // ������ ������� �������� � ������ � ����� DB10
bool  *Blowout1     =&bGr1[ 0]; //M02.1 ������ ���� 1
bool  *GuardRail1   =&bGr1[ 1]; //I125.3 ���������� 1
bool  *Pump1On      =&bGr1[ 2]; //M50.1 ����� 1
bool  *Blowout2     =&bGr1[ 3]; //M03.1 ������ ���� 2
bool  *GuardRail2   =&bGr1[ 4]; //I125.7 ���������� 2
bool  *Pump2On      =&bGr1[ 5]; //M50.2 ����� 2
bool  *Carriage1To  =&bGr1[ 6]; //M50.3 ������ ������� ��� 1
bool  *Carriage1From=&bGr1[ 7]; //M50.4 ����� ������� ��� 1
bool  *Carriage2To  =&bGr1[ 8]; //M50.5 ������ ������� ��� 2
bool  *Carriage2From=&bGr1[ 9]; //M50.6 ����� ������� ��� 2
bool  *Carriage1Off =&bGr1[10]; //M02.2 ������� ������� 1 � ��������
bool  *Carriage2Off =&bGr1[11]; //M03.2 ������� ������� 2 � ��������
bool  *ControlLateralA=&bGr1[12];      //M02.3 ���/���� �������� �������� ������� ��� �
bool  *ControlLateralB=&bGr1[13];      //M03.3 ���/���� �������� �������� ������� ��� �
bool  *DestroyLateral1=&bGr1[14];      //M34.0 ��������� ������� 1
bool  *DestroyLateral2=&bGr1[15];      //M34.2 ���������� ������� 2
bool  *DestroyRunning1=&bGr1[16];      //M34.1 ���������� ������� 1
bool  *DestroyRunning2=&bGr1[17];      //M34.3 ���������� ������� 2
bool  *OilLvl=&bGr1[18];				//M34.4 ������� �����
bool  *OilFilter=&bGr1[19];             //M34.5 ����� �������
bool  *ElDriveDrum=&bGr1[20];           //M34.6 ��� ���������� ��������������

//
float fGr1[GR1FLTITEMSNUM];
float *OilTemp			=&fGr1[0]; //DB20,x100 ����������� �����
float *ReadLoading_1	=&fGr1[1]; //DB10,REAL26 �������� 1  ����������
float *ReadLoading_2	=&fGr1[2]; //DB10,REAL62 �������� 2  ����������
float *max_speed		=&fGr1[3]; //DB10,REAL138 ������������ �������� � �����
float *min_speed        =&fGr1[4]; //DB10,REAL__  ����������� �������� � �����
float *min_load_1		=&fGr1[5]; //DB10,REAL142 ���. �������� 1 � �����
float *max_load_1		=&fGr1[6]; //DB10,REAL146 ���� �������� 1 � �����
float *min_load_2		=&fGr1[7]; //DB10,REAL150 ��� �������� 2 � �����
float *max_load_2		=&fGr1[8]; //DB10,REAL154 �������� ��������� 10-20 �� ������� �������� 1
// ���� DB10
bool  *AutoMode1    =&bGr1[21]; //DB10,X2.0 ����� ������� 1
bool  *ManualMode1  =&bGr1[22]; //DB10,X2.1 ����� ������ 1
bool  *Start1       =&bGr1[23]; //DB10,X2.2 ����� ��� 1
bool  *Stop1        =&bGr1[24]; //DB10,X2.3 ���� ��� 1
bool  *Reset1       =&bGr1[25]; //DB10,X2.4 ����� ��� 1
bool  *DrumOn       =&bGr1[26]; //DB10,X2.5 �������� �������
bool  *DrumOff      =&bGr1[27]; //DB10,X2.6 ��������� �������
bool  *KeepLoad1    =&bGr1[28]; //DB10,X3.0 ��������� �������� 1
bool  *AutoMode2    =&bGr1[29]; //DB10,X38.0 ����� ������ 2
bool  *ManualMode2  =&bGr1[30]; //DB10,X38.1 ����� ������ 2
bool  *Start2       =&bGr1[31]; //DB10,X38.2 ����� ��� 2
bool  *Stop2        =&bGr1[32]; //DB10,X38.3 ���� ��� 2
bool  *Reset2       =&bGr1[33]; //DB10,X38.4 ����� ��� 2
bool  *KeepLoad2    =&bGr1[34]; //DB10,X39.0 ��������� �������� 2
bool  *ResetData1	=&bGr1[35]; //M0.7 ����� ����������� ��������� 1
bool  *ResetData2   =&bGr1[36]; //M1.7 ����� ����������� ��������� 2
// ���� DB20 - ����� ���������
int   iDB20[GR1INTITEMSNUM];    // ������ ����� �������� � ����� DB20
int   *fakt_time          =&iDB20[ 0]; //DB20,DINT14 ����� �����
int   *fakt_time_1        =&iDB20[ 1]; //DB20,DINT26 ����. ����� 1
int   *step_write_1       =&iDB20[ 2]; //DB20,DINT38 ����� �������� ���� ������ 1
int   *step_change_1      =&iDB20[ 3]; //DB20,DINT42 ����� �������� �������� ���� 1
int   *fakt_time_2        =&iDB20[ 4]; //DB20,DINT66 ����. ����� 2
int   *step_write_2       =&iDB20[ 5]; //DB20,DINT78 ����� �������� ���� ������ 2
int   *step_change_2      =&iDB20[ 6]; //DB20,DINT82 ����� �������� �������� ���� 2
int   *next_step_time1    =&iDB20[ 7]; //DB20,DINT148 ����� ���������� ���� ������ �� ������� 1
int   *next_step_time2    =&iDB20[ 8]; //DB20,DINT152 ����� ���������� ���� ������ �� ������� 1
int   *next_step_change1  =&iDB20[ 9]; //DB20,DINT180 ����� ���������� �������� ���� 1
int   *next_step_change2  =&iDB20[10]; //DB20,DINT184 ����� ���������� �������� ���� 2
// ������ ���������� � �����������
wchar_t *Gr1ItemsNme[GR1ITEMSNUM]={	L"S7:[S7 connection_4]MX2.1",
									L"S7:[S7 connection_4]IX125.3", // �������� M125 �� I125!!!!!
									L"S7:[S7 connection_4]MX50.1",
									L"S7:[S7 connection_4]MX3.1",
									L"S7:[S7 connection_4]IX125.7",
									L"S7:[S7 connection_4]MX50.2",  // �������� M125 �� I125!!!!!
									L"S7:[S7 connection_4]MX50.3",
									L"S7:[S7 connection_4]MX50.4",
									L"S7:[S7 connection_4]MX50.5",
									L"S7:[S7 connection_4]MX50.6",
									L"S7:[S7 connection_4]MX2.2",
									L"S7:[S7 connection_4]MX3.2",
									L"S7:[S7 connection_4]MX2.3",
									L"S7:[S7 connection_4]MX3.3",
									L"S7:[S7 connection_4]MX34.0",
									L"S7:[S7 connection_4]MX34.2",
									L"S7:[S7 connection_4]MX34.1",
									L"S7:[S7 connection_4]MX34.3",
									L"S7:[S7 connection_4]MX34.4",
									L"S7:[S7 connection_4]MX34.5",
									L"S7:[S7 connection_4]MX34.6",
									//
									L"S7:[S7 connection_4]DB10,X2.0",
									L"S7:[S7 connection_4]DB10,X2.1",
									L"S7:[S7 connection_4]DB10,X2.2",
									L"S7:[S7 connection_4]DB10,X2.3",
									L"S7:[S7 connection_4]DB10,X2.4",
									L"S7:[S7 connection_4]DB10,X2.5",
									L"S7:[S7 connection_4]DB10,X2.6",
									L"S7:[S7 connection_4]DB10,X3.0",
									L"S7:[S7 connection_4]DB10,X38.0",
									L"S7:[S7 connection_4]DB10,X38.1",
									L"S7:[S7 connection_4]DB10,X38.2",
									L"S7:[S7 connection_4]DB10,X38.3",
									L"S7:[S7 connection_4]DB10,X38.4",
									L"S7:[S7 connection_4]DB10,X39.0",
									L"S7:[S7 connection_4]M0.7",
									L"S7:[S7 connection_4]M1.7",
									//idb20
									L"S7:[S7 connection_4]DB20,DINT14",
									L"S7:[S7 connection_4]DB20,DINT26",
									L"S7:[S7 connection_4]DB20,DINT38",
									L"S7:[S7 connection_4]DB20,DINT42",
									L"S7:[S7 connection_4]DB20,DINT66",
									L"S7:[S7 connection_4]DB20,DINT78",
									L"S7:[S7 connection_4]DB20,DINT82",
									L"S7:[S7 connection_4]DB20,DINT148",
									L"S7:[S7 connection_4]DB20,DINT152",
									L"S7:[S7 connection_4]DB20,DINT180",
									L"S7:[S7 connection_4]DB20,DINT184",
									//fgr1
									L"S7:[S7 connection_4]DB20,REAL100",
									L"S7:[S7 connection_4]DB10,REAL26",
									L"S7:[S7 connection_4]DB10,REAL62",
									L"S7:[S7 connection_4]DB10,REAL138",
									L"S7:[S7 connection_4]DB10,REAL158",
									L"S7:[S7 connection_4]DB10,REAL142",
									L"S7:[S7 connection_4]DB10,REAL146",
									L"S7:[S7 connection_4]DB10,REAL150",
									L"S7:[S7 connection_4]DB10,REAL154"
                                  };
// End of CtrlGr1 -----------------------------------------------------------
// ���������� ������ CtrlGr2 ------------------------------------------------
// ���� DB20 - ����� ���������
float fDB20[GR2FLOATITEMSNUM];
float *fakt_speed         =&fDB20[ 0]; //DB20,REAL2 ����������� ��������
float *set_speed          =&fDB20[ 1]; //DB20,REAL6 �������� ��������
float *fakt_distance      =&fDB20[ 2]; //DB20,REAL10 ����� ������
float *fakt_distance_1    =&fDB20[ 3]; //DB20,REAL18 ����. ������ 1
float *fakt_loading_1     =&fDB20[ 4]; //DB20,REAL22 ����. �������� 1
float *fakt_radius_1      =&fDB20[ 5]; //DB20,REAL30 ����. ������ 1
float *fakt_temper_1      =&fDB20[ 6]; //DB20,REAL34 ����. ����������� 1
float *set_speed_1        =&fDB20[ 7]; //DB20,REAL46 �������� �������� 1 �� ������� ����
float *set_loading_1      =&fDB20[ 8]; //DB20,REAL50 �������� �������� 1 �� ������� ����
float *fakt_distance_2    =&fDB20[ 9]; //DB20,REAL58 ����. ������ 2
float *fakt_loading_2     =&fDB20[10]; //DB20,REAL62 ����. �������� 2
float *fakt_radius_2      =&fDB20[11]; //DB20,REAL70 ����. ������ 2
float *fakt_temper_2      =&fDB20[12]; //DB20,REAL74 ����. ����������� 2
float *set_speed_2        =&fDB20[13]; //DB20,REAL86 �������� �������� 2 �� ������� ����
float *set_loading_2      =&fDB20[14]; //DB20,REAL90 �������� �������� 2 �� ������� ����
float *next_step_distance1=&fDB20[15]; //DB20,REAL156 ����� ���������� ���� ������ �� ������� 1
float *next_step_distance2=&fDB20[16]; //DB20,REAL160 ����� ���������� ���� ������ �� ������� 2
float *next_speed1        =&fDB20[17]; //DB20,REAL164 �������� �� ��������� ����1
float *next_speed2        =&fDB20[18]; //DB20,REAL168 �������� �� ��������� ����2
float *next_loading1      =&fDB20[19]; //DB20,REAL172 �������� �� ��������� ����1
float *next_loading2      =&fDB20[20]; //DB20,REAL176 �������� �� ��������� ����2
float *next_set_distance1 =&fDB20[21]; //DB20,REAL196
float *next_set_distance2 =&fDB20[22]; //DB20,REAL200

int i2DB20[GR2INTITEMSNUM];
int *next_set_time1		  =&i2DB20[0];  //DB20,DINT188
int *next_set_time2       =&i2DB20[1];  //DB20,DINT192
// ������ ���������� � ����� DB20
wchar_t *Gr2ItemsNme[GR2ITEMSNUM]={L"S7:[S7 connection_4]DB20,REAL2",   L"S7:[S7 connection_4]DB20,REAL6",
                                   L"S7:[S7 connection_4]DB20,REAL10",  L"S7:[S7 connection_4]DB20,REAL18",
                                   L"S7:[S7 connection_4]DB20,REAL22",  L"S7:[S7 connection_4]DB20,REAL30",
                                   L"S7:[S7 connection_4]DB20,REAL34",  L"S7:[S7 connection_4]DB20,REAL46",
                                   L"S7:[S7 connection_4]DB20,REAL50",  L"S7:[S7 connection_4]DB20,REAL58",
                                   L"S7:[S7 connection_4]DB20,REAL62",  L"S7:[S7 connection_4]DB20,REAL70",
                                   L"S7:[S7 connection_4]DB20,REAL74",  L"S7:[S7 connection_4]DB20,REAL86",
                                   L"S7:[S7 connection_4]DB20,REAL90",  L"S7:[S7 connection_4]DB20,REAL156",
                                   L"S7:[S7 connection_4]DB20,REAL160", L"S7:[S7 connection_4]DB20,REAL164",
                                   L"S7:[S7 connection_4]DB20,REAL168", L"S7:[S7 connection_4]DB20,REAL172",
								   L"S7:[S7 connection_4]DB20,REAL176", L"S7:[S7 connection_4]DB20,REAL196",
								   L"S7:[S7 connection_4]DB20,REAL200", L"S7:[S7 connection_4]DB20,DINT188",
								   L"S7:[S7 connection_4]DB20,DINT192"									   };
// End of CtrlGr2 -----------------------------------------------------------
// ���������� ������ CtrlGr3 ------------------------------------------------
// ���� DB10
int  iDB10[GR3INTITEMSNUM];
int   *T_end_cycle_1    =&iDB10[ 0]; //DB10,DINT10 �������� ����� ����� 1
int   *T_end_cycle_2    =&iDB10[ 1]; //DB10,DINT46 �������� ����� ����� 2
int   *type_cycle_1     =&iDB10[ 2]; //DB10,INT4 ��� ����� 1                  S7:[S7 connection_4]DB10,INT4
int   *StepsQty1        =&iDB10[ 3]; //DB10,INT34 ���������� ����� ��������� 1
int   *PollsQty1        =&iDB10[ 4]; //DB10,INT36 ���������� ������� 1
int   *type_cycle_2     =&iDB10[ 5]; //DB10,INT40 ��� ����� 2                 S7:[S7 connection_4]DB10,INT4
int   *StepsQty2        =&iDB10[ 6]; //DB10,INT70 ���������� ����� ��������� 1
int   *PollsQty2        =&iDB10[ 7]; //DB10,INT72 ���������� ������� 1
float fDB10[GR3FLTITEMSNUM];
float *S_end_cycle_1    =&fDB10[ 0]; //DB10,REAL18 �������� ������ ����� 1    S7:[S7 connection_4]DB10,REAL18
float *DrumSpeed        =&fDB10[ 1]; //DB10,REAL22 �������� ��������
float *Loading_1        =&fDB10[ 2]; //DB10,REAL26 �������� 1
float *Radius_1         =&fDB10[ 3]; //DB10,REAL30 ������ 1
float *S_end_cycle_2    =&fDB10[ 4]; //DB10,REAL54 �������� ������ ����� 2    S7:[S7 connection_4]DB10,REAL18
float *Loading_2        =&fDB10[ 5]; //DB10,REAL62 �������� 2
float *Radius_2         =&fDB10[ 6]; //DB10,REAL66 ������ 2
float *CorrASetSpeed    =&fDB10[ 7]; //DB10,REAL74 �������� � �� ������� ��������
float *CorrBSetSpeed    =&fDB10[ 8]; //DB10,REAL78 �������� � �� ������� ��������
float *CorrAMeasSpeed   =&fDB10[ 9]; //DB10,REAL82 �������� � �� ��������� ��������
float *CorrBMeasSpeed   =&fDB10[10]; //DB10,REAL86 �������� � �� ��������� ��������
float *Temp1LowLimit    =&fDB10[11]; //DB10,REAL90 ������ ������ ������� ����������� 1
float *Temp1UpLimit     =&fDB10[12]; //DB10,REAL94 ������� ������ ������� ����������� 1
float *CorrAMeasLoad1   =&fDB10[13]; //DB10,REAL98 �������� � �� ���������  �������� 1
float *CorrBMeasLoad1   =&fDB10[14]; //DB10,REAL102 �������� � �� ��������� �������� 1
float *Temp2LowLimit    =&fDB10[15]; //DB10,REAL106 ������ ������ ������� ����������� 2
float *Temp2UpLimit     =&fDB10[16]; //DB10,REAL110 ������� ������ ������� ����������� 2
float *CorrAMeasLoad2   =&fDB10[17]; //DB10,REAL114 �������� � �� ���������  �������� 2
float *CorrBMeasLoad2   =&fDB10[18]; //DB10,REAL118 �������� � �� ��������� �������� 2
float *Rad1LowLimit     =&fDB10[19]; //DB10,REAL122 ������ ������ ��������� ������� ������� 1
float *Rad1UpLimit      =&fDB10[20]; //DB10,REAL126 ������� ������ ��������� ������� ������� 1
float *Rad2LowLimit     =&fDB10[21]; //DB10,REAL130 ������ ������ ��������� ������� ������� 2
float *Rad2UpLimit      =&fDB10[22]; //DB10,REAL134 ������� ������ ��������� ������� ������� 2
float *Corr_2030SetLoad2=&fDB10[23]; //DB10,REAL158 �������� ��������� 20-30 �� ������� �������� 1
float *Corr_3040SetLoad2=&fDB10[24]; //DB10,REAL162 �������� ��������� 30-40 �� ������� �������� 1
float *Corr_4050SetLoad2=&fDB10[25]; //DB10,REAL166 �������� ��������� 40-50 �� ������� �������� 1
float *Corr_5060SetLoad2=&fDB10[26]; //DB10,REAL170 �������� ��������� 50-60 �� ������� �������� 1
float *Corr_6070SetLoad2=&fDB10[27]; //DB10,REAL174 �������� ��������� 60-70 �� ������� �������� 1
// ������ ���������� � ����� DB10
wchar_t *Gr3ItemsNme[GR3ITEMSNUM]={L"S7:[S7 connection_4]DB10,DINT10",  L"S7:[S7 connection_4]DB10,DINT46",
								   L"S7:[S7 connection_4]DB10,INT4",    L"S7:[S7 connection_4]DB10,INT34",
								   L"S7:[S7 connection_4]DB10,INT36",   L"S7:[S7 connection_4]DB10,INT40",
								   L"S7:[S7 connection_4]DB10,INT70",   L"S7:[S7 connection_4]DB10,INT72",
								   L"S7:[S7 connection_4]DB10,REAL18",  L"S7:[S7 connection_4]DB10,REAL22",
								   L"S7:[S7 connection_4]DB10,REAL26",  L"S7:[S7 connection_4]DB10,REAL30",
								   L"S7:[S7 connection_4]DB10,REAL54",  L"S7:[S7 connection_4]DB10,REAL62",
								   L"S7:[S7 connection_4]DB10,REAL66",  L"S7:[S7 connection_4]DB10,REAL74",
								   L"S7:[S7 connection_4]DB10,REAL78",  L"S7:[S7 connection_4]DB10,REAL82",
								   L"S7:[S7 connection_4]DB10,REAL86",  L"S7:[S7 connection_4]DB10,REAL90",
								   L"S7:[S7 connection_4]DB10,REAL94",  L"S7:[S7 connection_4]DB10,REAL98",
								   L"S7:[S7 connection_4]DB10,REAL102", L"S7:[S7 connection_4]DB10,REAL106",
								   L"S7:[S7 connection_4]DB10,REAL110", L"S7:[S7 connection_4]DB10,REAL114",
								   L"S7:[S7 connection_4]DB10,REAL118", L"S7:[S7 connection_4]DB10,REAL122",
								   L"S7:[S7 connection_4]DB10,REAL126", L"S7:[S7 connection_4]DB10,REAL130",
								   L"S7:[S7 connection_4]DB10,REAL134",
								   L"S7:[S7 connection_4]DB10,REAL158", L"S7:[S7 connection_4]DB10,REAL162",
								   L"S7:[S7 connection_4]DB10,REAL166", L"S7:[S7 connection_4]DB10,REAL170",
								   L"S7:[S7 connection_4]DB10,REAL174"                                     };
// End of CtrlGr3 -----------------------------------------------------------
// ���������� ������ CtrlGr4 ------------------------------------------------
// ���� DB8
float poll_step_SA[MAXNUMOFPOLLS];
// ���� DB22
float step_SA[MAXNUMOFSTEPS];
wchar_t *Gr4ItemsNme[GR4ITEMSNUM]={NULL};
wchar_t Gr4ItemsAddr[GR4ITEMSNUM][ADDRLEN]={L""};
String  AddrDB8 ="S7:[S7 connection_4]DB8,REAL",
        AddrDB22="S7:[S7 connection_4]DB22,REAL";
// End of CtrlGr4 -----------------------------------------------------------
// ���������� ������ CtrlGr5 ------------------------------------------------
// ���� DB7
int   poll_step_TA[MAXNUMOFPOLLS];
// ���� DB21
int   step_TA[MAXNUMOFSTEPS];
wchar_t *Gr5ItemsNme[GR5ITEMSNUM]={NULL};
wchar_t Gr5ItemsAddr[GR5ITEMSNUM][ADDRLEN]={L""};
String  AddrDB7 ="S7:[S7 connection_4]DB7,DINT",
        AddrDB21="S7:[S7 connection_4]DB21,DINT";
// End of CtrlGr5 -----------------------------------------------------------
// ���������� ������ CtrlGr6 ------------------------------------------------
// ���� DB23
float setting_A[2][100];
wchar_t *Gr6ItemsNme[GR6ITEMSNUM]={NULL};
wchar_t Gr6ItemsAddr[GR6ITEMSNUM][ADDRLEN]={L""};
String  AddrDB23="S7:[S7 connection_4]DB23,REAL";
// End of CtrlGr6 -----------------------------------------------------------
// ���������� ������ CtrlGr7 ------------------------------------------------
// ���� DB1
int   read_TA[MAXNUMOFPOLLS];
// ���� DB2
float read_VA[MAXNUMOFPOLLS];
// ���� DB3
float read_SA[MAXNUMOFPOLLS];
// ���� DB4
float read_LA[MAXNUMOFPOLLS];
// ���� DB5
float read_RA[MAXNUMOFPOLLS];
// ���� DB6
float read_TempA[MAXNUMOFPOLLS];
// ������ ���������� � ������ 7
wchar_t *Gr7ItemsNme[GR7ARRAYSNUM]={L"S7:[S7 connection_4]DB1,DINT2,250",
                                    L"S7:[S7 connection_4]DB2,REAL2,250",
                                    L"S7:[S7 connection_4]DB3,REAL2,250",
                                    L"S7:[S7 connection_4]DB4,REAL2,250",
                                    L"S7:[S7 connection_4]DB5,REAL2,250",
                                    L"S7:[S7 connection_4]DB6,REAL2,250",
                                   };
// End of CtrlGr7 -----------------------------------------------------------
// ���������� ������ CtrlGr8 ------------------------------------------------
// ���� DB18
float poll_step_SB[MAXNUMOFPOLLS];
// ���� DB32
float step_SB[MAXNUMOFSTEPS];
// ������ ���������� � ������ 8
wchar_t *Gr8ItemsNme[GR8ITEMSNUM]={NULL};
wchar_t Gr8ItemsAddr[GR8ITEMSNUM][ADDRLEN]={L""};
String  AddrDB18="S7:[S7 connection_4]DB18,REAL",
        AddrDB32="S7:[S7 connection_4]DB32,REAL";
// End of CtrlGr8 -----------------------------------------------------------
// ���������� ������ CtrlGr9 ------------------------------------------------
// ���� DB17
int   poll_step_TB[MAXNUMOFPOLLS];
// ���� DB31
int   step_TB[MAXNUMOFSTEPS];
// ������ ���������� � ������ 9
wchar_t *Gr9ItemsNme[GR9ITEMSNUM]={NULL};
wchar_t Gr9ItemsAddr[GR9ITEMSNUM][ADDRLEN]={L""};
String  AddrDB17="S7:[S7 connection_4]DB17,DINT",
        AddrDB31="S7:[S7 connection_4]DB31,DINT";
// End of CtrlGr9 -----------------------------------------------------------
// ���������� ������ CtrlGr10 -----------------------------------------------
// ���� DB33
float setting_B[2][MAXNUMOFSTEPS];
// ������ ���������� � ������ 10
wchar_t *Gr10ItemsNme[GR10ITEMSNUM]={NULL};
wchar_t Gr10ItemsAddr[GR10ITEMSNUM][ADDRLEN]={L""};
String  AddrDB33="S7:[S7 connection_4]DB33,REAL";
// End of CtrlGr10 ----------------------------------------------------------
// ���������� ������ CtrlGr11 -----------------------------------------------
// ���� DB11
int   read_TB[MAXNUMOFPOLLS];
// ���� DB12
float read_VB[MAXNUMOFPOLLS];
// ���� DB13
float read_SB[MAXNUMOFPOLLS];
// ���� DB14
float read_LB[MAXNUMOFPOLLS];
// ���� DB15
float read_RB[MAXNUMOFPOLLS];
// ���� DB16
float read_TempB[MAXNUMOFPOLLS];
// ������ ���������� � ������ 11
wchar_t *Gr11ItemsNme[GR11ARRAYSNUM]={L"S7:[S7 connection_4]DB11,DINT2,250",
                                      L"S7:[S7 connection_4]DB12,REAL2,250",
                                      L"S7:[S7 connection_4]DB13,REAL2,250",
                                      L"S7:[S7 connection_4]DB14,REAL2,250",
                                      L"S7:[S7 connection_4]DB15,REAL2,250",
                                      L"S7:[S7 connection_4]DB16,REAL2,250",
                                     };
// End of CtrlGr11 ----------------------------------------------------------
// ���������� ������ CtrlGr12 -----------------------------------------------
// ���� DB71
float fDB71[GR12ITEMSNUM];
float *A1[GR12ARRAYSIZE];    //DB71,REAL2-172 ������������ ��������� ���. 1    S7:[S7 connection_4]DB10,REAL18
float *Q1[GR12ARRAYSIZE];    //DB71,REAL6-176 ������� �������� ������������� ��������� ���. 1    S7:[S7 connection_4]DB10,REAL18
// ������ ���������� � ������ 12
wchar_t *Gr12ItemsNme[GR12ITEMSNUM]={//����������� ��������� ������ ���
									 L"S7:[S7 connection_4]DB71,REAL180", L"S7:[S7 connection_4]DB71,REAL188",
									 L"S7:[S7 connection_4]DB71,REAL196", L"S7:[S7 connection_4]DB71,REAL204",
									 L"S7:[S7 connection_4]DB71,REAL212",
									 L"S7:[S7 connection_4]DB71,REAL2",   L"S7:[S7 connection_4]DB71,REAL10",
									 L"S7:[S7 connection_4]DB71,REAL18",  L"S7:[S7 connection_4]DB71,REAL26",
									 L"S7:[S7 connection_4]DB71,REAL34",  L"S7:[S7 connection_4]DB71,REAL42",
									 L"S7:[S7 connection_4]DB71,REAL50",  L"S7:[S7 connection_4]DB71,REAL58",
                                     L"S7:[S7 connection_4]DB71,REAL66",  L"S7:[S7 connection_4]DB71,REAL74",
                                     L"S7:[S7 connection_4]DB71,REAL260", L"S7:[S7 connection_4]DB71,REAL268",
                                     L"S7:[S7 connection_4]DB71,REAL276", L"S7:[S7 connection_4]DB71,REAL284",
                                     L"S7:[S7 connection_4]DB71,REAL292",


									 //����������� ��������� �������� ���
                                     L"S7:[S7 connection_4]DB71,REAL300", L"S7:[S7 connection_4]DB71,REAL312",
                                     L"S7:[S7 connection_4]DB71,REAL320", L"S7:[S7 connection_4]DB71,REAL328",
                                     L"S7:[S7 connection_4]DB71,REAL336",
									 L"S7:[S7 connection_4]DB71,REAL100", L"S7:[S7 connection_4]DB71,REAL108",
									 L"S7:[S7 connection_4]DB71,REAL116", L"S7:[S7 connection_4]DB71,REAL124",
									 L"S7:[S7 connection_4]DB71,REAL132", L"S7:[S7 connection_4]DB71,REAL140",
									 L"S7:[S7 connection_4]DB71,REAL148", L"S7:[S7 connection_4]DB71,REAL156",
									 L"S7:[S7 connection_4]DB71,REAL164", L"S7:[S7 connection_4]DB71,REAL172",
									 L"S7:[S7 connection_4]DB71,REAL220", L"S7:[S7 connection_4]DB71,REAL228",
									 L"S7:[S7 connection_4]DB71,REAL236", L"S7:[S7 connection_4]DB71,REAL244",
									 L"S7:[S7 connection_4]DB71,REAL252",

									 //������� �������� ������ ���
									 L"S7:[S7 connection_4]DB71,REAL184", L"S7:[S7 connection_4]DB71,REAL192",
									 L"S7:[S7 connection_4]DB71,REAL200", L"S7:[S7 connection_4]DB71,REAL208",
									 L"S7:[S7 connection_4]DB71,REAL216",
									 L"S7:[S7 connection_4]DB71,REAL6",   L"S7:[S7 connection_4]DB71,REAL14",
									 L"S7:[S7 connection_4]DB71,REAL22",  L"S7:[S7 connection_4]DB71,REAL30",
									 L"S7:[S7 connection_4]DB71,REAL38",  L"S7:[S7 connection_4]DB71,REAL46",
									 L"S7:[S7 connection_4]DB71,REAL54",  L"S7:[S7 connection_4]DB71,REAL62",
                                     L"S7:[S7 connection_4]DB71,REAL70",  L"S7:[S7 connection_4]DB71,REAL78",
                                     L"S7:[S7 connection_4]DB71,REAL264", L"S7:[S7 connection_4]DB71,REAL272",
                                     L"S7:[S7 connection_4]DB71,REAL280", L"S7:[S7 connection_4]DB71,REAL288",
                                     L"S7:[S7 connection_4]DB71,REAL296",


									 //������� �������� �������� ���

                                     L"S7:[S7 connection_4]DB71,REAL304", L"S7:[S7 connection_4]DB71,REAL308",
                                     L"S7:[S7 connection_4]DB71,REAL316", L"S7:[S7 connection_4]DB71,REAL324",
                                     L"S7:[S7 connection_4]DB71,REAL332",
                                     L"S7:[S7 connection_4]DB71,REAL104", L"S7:[S7 connection_4]DB71,REAL112",
									 L"S7:[S7 connection_4]DB71,REAL120", L"S7:[S7 connection_4]DB71,REAL128",
									 L"S7:[S7 connection_4]DB71,REAL136", L"S7:[S7 connection_4]DB71,REAL144",
									 L"S7:[S7 connection_4]DB71,REAL152", L"S7:[S7 connection_4]DB71,REAL160",
									 L"S7:[S7 connection_4]DB71,REAL168", L"S7:[S7 connection_4]DB71,REAL176",
									 L"S7:[S7 connection_4]DB71,REAL224", L"S7:[S7 connection_4]DB71,REAL232",
									 L"S7:[S7 connection_4]DB71,REAL240", L"S7:[S7 connection_4]DB71,REAL248",
									 L"S7:[S7 connection_4]DB71,REAL256"
								    };

// End of CtrlGr12 ----------------------------------------------------------
// ���������� ������ CtrlGr13 -----------------------------------------------
// ���� DB70
float fDB70[GR13ITEMSNUM];
float *A2[GR13ARRAYSIZE];    //DB70,REAL2-172 ������������ ��������� ���. 2    S7:[S7 connection_4]DB10,REAL18
float *Q2[GR13ARRAYSIZE];    //DB70,REAL6-176 ������� �������� ������������� ��������� ���. 2    S7:[S7 connection_4]DB10,REAL18
// ������ ���������� � ������ 13
wchar_t *Gr13ItemsNme[GR13ITEMSNUM]={//����������� ��������� ������ ���
									 L"S7:[S7 connection_4]DB70,REAL180", L"S7:[S7 connection_4]DB70,REAL188",
									 L"S7:[S7 connection_4]DB70,REAL196", L"S7:[S7 connection_4]DB70,REAL204",
									 L"S7:[S7 connection_4]DB70,REAL212",
									 L"S7:[S7 connection_4]DB70,REAL2",   L"S7:[S7 connection_4]DB70,REAL10",
									 L"S7:[S7 connection_4]DB70,REAL18",  L"S7:[S7 connection_4]DB70,REAL26",
									 L"S7:[S7 connection_4]DB70,REAL34",  L"S7:[S7 connection_4]DB70,REAL42",
									 L"S7:[S7 connection_4]DB70,REAL50",  L"S7:[S7 connection_4]DB70,REAL58",
                                     L"S7:[S7 connection_4]DB70,REAL66",  L"S7:[S7 connection_4]DB70,REAL74",
                                     L"S7:[S7 connection_4]DB70,REAL260", L"S7:[S7 connection_4]DB70,REAL268",
                                     L"S7:[S7 connection_4]DB70,REAL276", L"S7:[S7 connection_4]DB70,REAL284",
                                     L"S7:[S7 connection_4]DB70,REAL292",


									 //����������� ��������� �������� ���
                                     L"S7:[S7 connection_4]DB70,REAL300", L"S7:[S7 connection_4]DB70,REAL312",
                                     L"S7:[S7 connection_4]DB70,REAL320", L"S7:[S7 connection_4]DB70,REAL328",
                                     L"S7:[S7 connection_4]DB70,REAL336",                                     
                                     L"S7:[S7 connection_4]DB70,REAL100", L"S7:[S7 connection_4]DB70,REAL108",
									 L"S7:[S7 connection_4]DB70,REAL116", L"S7:[S7 connection_4]DB70,REAL124",
									 L"S7:[S7 connection_4]DB70,REAL132", L"S7:[S7 connection_4]DB70,REAL140",
									 L"S7:[S7 connection_4]DB70,REAL148", L"S7:[S7 connection_4]DB70,REAL156",
									 L"S7:[S7 connection_4]DB70,REAL164", L"S7:[S7 connection_4]DB70,REAL172",
									 L"S7:[S7 connection_4]DB70,REAL220", L"S7:[S7 connection_4]DB70,REAL228",
									 L"S7:[S7 connection_4]DB70,REAL236", L"S7:[S7 connection_4]DB70,REAL244",
									 L"S7:[S7 connection_4]DB70,REAL252",

									 //������� �������� ������ ���
									 L"S7:[S7 connection_4]DB70,REAL184", L"S7:[S7 connection_4]DB70,REAL192",
									 L"S7:[S7 connection_4]DB70,REAL200", L"S7:[S7 connection_4]DB70,REAL208",
									 L"S7:[S7 connection_4]DB70,REAL216",
									 L"S7:[S7 connection_4]DB70,REAL6",   L"S7:[S7 connection_4]DB70,REAL14",
									 L"S7:[S7 connection_4]DB70,REAL22",  L"S7:[S7 connection_4]DB70,REAL30",
									 L"S7:[S7 connection_4]DB70,REAL38",  L"S7:[S7 connection_4]DB70,REAL46",
									 L"S7:[S7 connection_4]DB70,REAL54",  L"S7:[S7 connection_4]DB70,REAL62",
									 L"S7:[S7 connection_4]DB70,REAL70",  L"S7:[S7 connection_4]DB70,REAL78",
                                     L"S7:[S7 connection_4]DB70,REAL264", L"S7:[S7 connection_4]DB70,REAL272",
                                     L"S7:[S7 connection_4]DB70,REAL280", L"S7:[S7 connection_4]DB70,REAL288",
                                     L"S7:[S7 connection_4]DB70,REAL296",


									 //������� �������� �������� ���
                                     L"S7:[S7 connection_4]DB70,REAL304", L"S7:[S7 connection_4]DB70,REAL308",
                                     L"S7:[S7 connection_4]DB70,REAL316", L"S7:[S7 connection_4]DB70,REAL324",
                                     L"S7:[S7 connection_4]DB70,REAL332",                                     
									 L"S7:[S7 connection_4]DB70,REAL104", L"S7:[S7 connection_4]DB70,REAL112",
									 L"S7:[S7 connection_4]DB70,REAL120", L"S7:[S7 connection_4]DB70,REAL128",
									 L"S7:[S7 connection_4]DB70,REAL136", L"S7:[S7 connection_4]DB70,REAL144",
									 L"S7:[S7 connection_4]DB70,REAL152", L"S7:[S7 connection_4]DB70,REAL160",
									 L"S7:[S7 connection_4]DB70,REAL168", L"S7:[S7 connection_4]DB70,REAL176",
									 L"S7:[S7 connection_4]DB70,REAL224", L"S7:[S7 connection_4]DB70,REAL232",
									 L"S7:[S7 connection_4]DB70,REAL240", L"S7:[S7 connection_4]DB70,REAL248",
									 L"S7:[S7 connection_4]DB70,REAL256"
									};
// End of CtrlGr12 ----------------------------------------------------------

//����� ��������� �� �������
void	ClearTProg	(void)
{
	for (size_t i = 0; i <MAXNUMOFPOLLS; i++)// ������ ������� �� �������
	{
		poll_step_T[i]=0;
	}
	for (size_t i = 0; i <MAXNUMOFSTEPS; i++)
	{
		prog_step_T[i]=0; // ������ ����� �� �������
		Tsettings[0][i]=0; // ������ �������� (1-� �������)
		Tsettings[1][i]=0;  // ������ ��������� (2-� �������)
	}
	TProgFName="";                  // ��� ����� ��� ���������� ��������� �� �������
	TProgName="";                   // ��� ��������� ��������� �� �������
	TTyrePressure=0.0;               // �������� � ����
	total_step_T=0;                // ��������� ���-�� ����� ��������� �� �������
	total_T=0;                     // ��������� ����������������� ��������� �� �������, ����
	num_T_poll=0;                  // ���������� ������� �� �������
}
//����� ��������� �� ����
void	ClearSProg	(void)
{
	for (size_t i = 0; i <MAXNUMOFPOLLS; i++)// ������ ������� �� ����
	{
		poll_step_S[i]=0;
	}
	for (size_t i = 0; i <MAXNUMOFSTEPS; i++)
	{
		prog_step_S[i]=0; // ������ ����� �� �������
		Ssettings[0][i]=0; // ������ �������� (1-� �������)
		Ssettings[1][i]=0;  // ������ ��������� (2-� �������)
	}
	SProgFName="";                  // ��� ����� ��� ���������� ��������� �� ����
	SProgName="";                   // ��� ��������� ��������� �� ����
	STyrePressure=0.0;               // �������� � ����
	total_step_S=0;                // ��������� ���-�� ����� ��������� �� ����
	total_S=0.0;                     // ��������� ����������������� ��������� �� ����, ��
	num_S_poll=0;                  // ���������� ������� �� ����
}
// ����� ������� ------------------------------------------------------------
void __fastcall PntInit(void)            // ������������� ���������� ��� ����� 12 � 13
{
  for(int i=0;i<GR12ARRAYSIZE;i++){
    A1[i] = &fDB71[i];
    Q1[i] = &fDB71[i+GR12ARRAYSIZE];
  }
  for(int i=0;i<GR13ARRAYSIZE;i++){
    A2[i] = &fDB70[i];
    Q2[i] = &fDB70[i+GR13ARRAYSIZE];
  }
}
//---- End of PntInit -------------------------------------------------------

void __fastcall ResetKA(float *A[])      // ����� ������� � � ��������
{
  for (int i=0; i<GR12ARRAYSIZE; i++) {
    *A[i]=1.0;  
  }
}
//---- End of ResetKA -------------------------------------------------------

// ������ ����� Str � ���� ��������� ������ CClr ----------------------------
void __fastcall LogPrint(String Str,TColor CClr)
{
  pPrt->SelAttributes->Color=CClr;
  pPrt->Lines->Add(Str);
}
//---- End of LogPrint ------------------------------------------------------

// ����� ��������� � ���� ��������� ��� ������ SendMessage
void __fastcall SLogPrint(String Str,TColor CClr)
{
  LogMess=Str;
  SendMessage(MainFormHandle,WM_LogPrint,0,(long)CClr);
}
//---- End of SLogPrint -----------------------------------------------------

// ����� ��������� � ���� ��������� ��� ������ PostMessage
void __fastcall PLogPrint(String Str,TColor CClr)
{
  LogMess=Str;
  PostMessage(MainFormHandle,WM_LogPrint,0,(long)CClr);
}
//---- End of PLogPrint -----------------------------------------------------

void __fastcall OPCControlStart(TTimer* t)// ������ ���������� �������
{
  OPCControlOn=true;
  t->Enabled=true;
//  hOPCCtrlThrd=(HANDLE)_beginthreadex(NULL,4096,OPCControl,NULL,0,&OPCCtrlThrdID);
//  LogPrint("OPC control thread ID is: "+String(OPCCtrlThrdID),clLime);
  ResumeThread(CD_9904Thread);
}
//---- End of OPCControlStart -----------------------------------------------

void     __fastcall OPCControlPause(TTimer* t) // ������������ ���������� �������
{
  LogPrint("������������ �������� �����������!",clLime);
  t->Enabled=false;
  SuspendThread(CD_9904Thread);
}
//---- End of OPCControlPause -----------------------------------------------

void     __fastcall OPCControlResume(TTimer* t)// ������������� ���������� �������
{
  LogPrint("������������� �������� �����������!",clLime);
  t->Enabled=true;
  ResumeThread(CD_9904Thread);
}
//---- End of OPCControlResume ----------------------------------------------

void __fastcall OPCControlStop(TTimer* t) // ������� ���������� �������
{
  LogPrint("������� �������� �����������!",clLime);
  t->Enabled=false;
  OPCControlOn=false;
  SuspendThread(CD_9904Thread);
}
//---- End of OPCControlStop ------------------------------------------------

String __fastcall mSecToHMSStr(int tm)    // ������� ������ ���-�� ���� � ������ ��:��:��
{
  int s=tm/1000,h,m;
  h=s/3600;
  s-=h*3600;
  m=s/60;
  s-=m*60;
  String ws="";
  //����
  if(h==0)      ws ="00:";
  else if(h<10) ws ="0"+String(h)+":";
  else          ws =String(h)+":";
  #ifdef _NOS_SHOW_SEK
  //������
  if(m==0)      ws+="00";
  else if(m<10) ws+="0"+String(m);
  else          ws+=String(m);
  #endif
  #ifndef _NOS_SHOW_SEK
  //������
  if(m==0)      ws+="00:";
  else if(m<10) ws+="0"+String(m)+":";
  else          ws+=String(m)+":";
  //�������
  if(s==0)      ws+="00";
  else if(s<10) ws+="0"+String(s);
  else          ws+=String(s);
  #endif
  return ws;
}
//---- End of mSecToHMSStr --------------------------------------------------

void __fastcall ReadSProgFmFile(void)   // ��������� ��������� �� ���� �� �����
{ FILE *fparam; float w;
  if((fparam=fopen(AnsiString(SProgFName).c_str(),"rb"))==NULL){
    LogPrint("Can't open file \""+SProgFName+"\" for reading!",clRed);
    return;
  }
  SProgName=ReadString(fparam);
  fread(&STyrePressure,sizeof(float),1,fparam);
  fread(&total_step_S,sizeof(int),1,fparam);
  fread(&total_S,sizeof(float),1,fparam);
  fread(&num_S_poll,sizeof(int),1,fparam);
  fread(&Ssettings[0][0],sizeof(Ssettings),1,fparam);
  fread(&prog_step_S[0],sizeof(prog_step_S),1,fparam);
  fread(&poll_step_S[0],sizeof(poll_step_S),1,fparam);
  fclose(fparam);
//  LogPrint("Total_S="+FloatToStrF(total_S,ffFixed,7,2),clAqua);
//  LogPrint("Num_S_poll="+String(num_S_poll),clAqua);
//  LogPrint("poll_step__S[0]="+FloatToStrF(poll_step_S[0],ffFixed,7,2),clAqua);
//  LogPrint("Total_S="+FloatToStrF(total_S,ffFixed,7,2),clAqua);
}
//---- End of ReadSProgFmFile -----------------------------------------------

void __fastcall WriteSProgToFile(void)  // �������� ��������� �� ���� � ����
{ FILE *fparam;
  if((fparam=fopen(AnsiString(SProgFName).c_str(),"wb"))==NULL){
    LogPrint("Can't open file \""+SProgFName+"\" for writing!",clRed);
    return;
  }
  WriteString(SProgName,fparam);
  fwrite(&STyrePressure,sizeof(float),1,fparam);
  fwrite(&total_step_S,sizeof(int),1,fparam);
  fwrite(&total_S,sizeof(float),1,fparam);
  fwrite(&num_S_poll,sizeof(int),1,fparam);
  fwrite(&Ssettings[0][0],sizeof(Ssettings),1,fparam);
  fwrite(&prog_step_S[0],sizeof(prog_step_S),1,fparam);
  fwrite(&poll_step_S[0],sizeof(poll_step_S),1,fparam);
  fclose(fparam);
//  LogPrint("Total_S="+FloatToStrF(total_S,ffFixed,7,2),clAqua);
//  LogPrint("Num_S_poll="+String(num_S_poll),clAqua);
//  LogPrint("poll_step__S[0]="+FloatToStrF(poll_step_S[0],ffFixed,7,2),clAqua);
//  LogPrint("Total_S="+FloatToStrF(total_S,ffFixed,7,2),clAqua);
}
//---- End of WriteSProgFmFile ----------------------------------------------

float __fastcall StrToFlt(String ws)    // �������������� ������ � �������� ���� float
{ String s;
  s=Trim(ws);
  if(s=="") return 0.0;
  int PointPos=s.Pos(".");
  if(PointPos)
    s=TrimRight(s.SubString(1,PointPos-1))+"."+Trim(s.SubString(PointPos+1,100));
  int CommaPos=s.Pos(",");
  if(CommaPos)
    s=TrimRight(s.SubString(1,PointPos-1))+"."+Trim(s.SubString(PointPos+1,100));
  return StrToFloat(s);
}
//---- End of StrToFlt ------------------------------------------------------

int __fastcall StrToI(String ws)       // �������������� ������ � �������� ���� int
{ String s;
  s=Trim(ws);
  if(s=="") return 0;
  else return StrToInt(s);
}
//---- End of StrToI --------------------------------------------------------

String __fastcall ReadString(FILE *fp) // ������ ������ ���� String �� �����
{ char is[1024]; short it;
  fread(&it,sizeof(short),1,fp);
  fread(is,sizeof(char),it,fp); is[it]=0;
  return String(is);
}
//---- End of ReadString ----------------------------------------------------

void __fastcall WriteString(            // ������ ������ ���� String � ����
                            String ws,
                            FILE *fp)
{
  short it=strlen(AnsiString(ws).c_str());
  fwrite(&it,sizeof(short),1,fp);
  fwrite(AnsiString(ws).c_str(),sizeof(char),it,fp);
}
//---- End of WriteString ---------------------------------------------------

void __fastcall ReadTProgFmFile(void)   // ��������� ��������� �� ������� �� �����
{ FILE *fparam;
  if((fparam=fopen(AnsiString(TProgFName).c_str(),"rb"))==NULL){
    LogPrint("Can't open file \""+TProgFName+"\" for reading!",clRed);
    return;
  }
  TProgName=ReadString(fparam);
  fread(&TTyrePressure,sizeof(float),1,fparam);
  fread(&total_step_T,sizeof(int),1,fparam);
  fread(&total_T,sizeof(int),1,fparam);
  fread(&num_T_poll,sizeof(int),1,fparam);
  fread(&Tsettings[0][0],sizeof(Tsettings),1,fparam);
  fread(&prog_step_T[0],sizeof(prog_step_T),1,fparam);
  fread(&poll_step_T[0],sizeof(poll_step_T),1,fparam);
  fclose(fparam);
  LogPrint("Loading TProg fm file: Total T="+mSecToHMSStr(total_T),clLime);
}
//---- End of ReadTProgFmFile -----------------------------------------------

void __fastcall WriteTProgToFile(void)  // �������� ��������� �� ������� � ����
{ FILE *fparam;
  if((fparam=fopen(AnsiString(TProgFName).c_str(),"wb"))==NULL){
    LogPrint("Can't open file \""+TProgFName+"\" for writing!",clRed);
    return;
  }
  WriteString(TProgName,fparam);
  fwrite(&TTyrePressure,sizeof(float),1,fparam);
  fwrite(&total_step_T,sizeof(int),1,fparam);
  fwrite(&total_T,sizeof(int),1,fparam);
  fwrite(&num_T_poll,sizeof(int),1,fparam);
  fwrite(&Tsettings[0][0],sizeof(Tsettings),1,fparam);
  fwrite(&prog_step_T[0],sizeof(prog_step_T),1,fparam);
  fwrite(&poll_step_T[0],sizeof(poll_step_T),1,fparam);
  fclose(fparam);
}
//---- End of WriteTProgFmFile ----------------------------------------------

String __fastcall FileNameParse(              // ������� ��������� ����� ����� �� ������� ����
								String SFN)   // ������ ��� �����
{  String wfname=SFN;
   if(wfname.Length()>0) {
	 int slPos=wfname.Pos("\\");
	 while(slPos){
	   wfname=wfname.SubString(slPos+1,1000);
	   slPos=wfname.Pos("\\");
	 }
   }
   return wfname;
}
//---- End of FileNameParse -------------------------------------------------

int __fastcall NextCycleCount(void)     // ���������� ����� �������� �� 1
{
  if((++TimerCycleCnt)>=MAXINT)TimerCycleCnt=0;
  return TimerCycleCnt;
}
//---- End of NextCycleCount ------------------------------------------------

void __fastcall LeastSquares(                     // ������ ������������� A � B ������� ���������� ���������
					         float X[],           // ������ X
					         float Y[],           // ������ Y
					         int   N,             // ���������� ��������� � ��������
				   	         float &A,            // ����������� A
					         float &B)            // ����������� B
{ int i;
  double SXi, SYi, SXiYi, SXi2, Ndbl;
  SXi=0; SYi=0; SXiYi=0; SXi2=0; Ndbl=N;
  for(i=0;i<N;i++) {
	SXi  +=X[i];
	SYi  +=Y[i];
	SXiYi+=X[i]*Y[i];
	SXi2 +=X[i]*X[i];
  }
  A=(Ndbl*SXiYi-SXi*SYi)/(Ndbl*SXi2-SXi*SXi);
  B=(SYi-A*SXi)/Ndbl;
}
//---- End of LeastSquares --------------------------------------------------

void     __fastcall LogPrintF(                // ����� ��������� � ���� �������
                              String FNme,    // ��� ����� �������
                              String Mess,    // ���������
                              TColor wcl)     // ���� ��������� � ����
{ FILE *fparam;
  if((fparam=fopen(AnsiString(FNme).c_str(),"at+"))==NULL){
    LogPrint("Can't open logfile \""+FNme+"\" for writing!",clRed);
    return;
  }
//  LogPrint("Write to file \""+FNme+"\" mess: \""+Mess+"\"",wcl);
  LogPrint("Logfile mess: "+Now().TimeString()+" \""+Mess+"\"",wcl);
  fprintf(fparam,"%8s: %s\n",AnsiString(Now().TimeString()).c_str(),AnsiString(Mess).c_str());
  fclose(fparam);
}
//---- End of LogPrintF -----------------------------------------------------

String   __fastcall LogFName(void)            // ��������� ����� ����� �������
{ String wfname;
  wfname="RBLogFile";
  wfname+=IntToStr(YearOf(Now()));
  int month=MonthOf(Now());
  if(month<10)wfname+="0";
  wfname+=IntToStr(month);
  int day=DayOf(Now());
  if(day<10)wfname+="0";
  wfname+=IntToStr(day)+".log";
  return wfname;
}
//---- End of LogFName ------------------------------------------------------

int __fastcall BUnion(bool b1, bool b2) // ����������� �������� ���������� � ����� ��������
{
  return (int(b1)<<1)+int(b2);
}
//---- End of BUnion --------------------------------------------------------

String   __fastcall FltToStr(                 // �������������� ����� � ������ ������ l
                      float f,                // ������������� �����
                      TFloatFormat ff,        // ������
                      int l,                  // ����� ������
                      int r)                  // ����� ������� �����
{
  String ws;
  ws=FloatToStrF(f,ff,l,r);
  int wl=ws.Length();
  if(wl<l) {
    ws=String(DupeString(' ',l-wl))+ws;
  }
  return ws;
}
//---- End of FltToStr -----------------------------------------------------

String   __fastcall IntToS(                   // �������������� ������ � ������ ������ l
                      int i,                  // ������������� �����
                      int l)                  // ����� ������
{
  String ws;
  ws=String(i);
  int wl=ws.Length();
  if(wl<l) {
    ws=String(DupeString(' ',l-wl))+ws;
  }
  return ws;
}
//---- End of IntToS ------------------------------------------------------
