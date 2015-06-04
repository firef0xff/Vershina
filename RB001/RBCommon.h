//---------------------------------------------------------------------------
//#define GR1ITEMSNUM  6     // ���������� ���������� � ������ 1
//#define GR2ITEMSNUM  51    // ���������� ���������� � ������ 2
//// ����������� ����������� ���������
//#define WM_LogPrint  WM_USER
//#define WM_DataShow  WM_USER+1
//#define WM_OPCCmd    WM_USER+2
//// ����� ���������� �� ���������� OPCCtrlStat
//#define IDDLESTAT      0
//#define READGR1        1
//#define WRITEGR1ITEM   2
//// ����� ���������� ��� ������� OnDataShow
//#define COMMONPRMSHOW  0

#ifndef RBCommonH
#define RBCommonH
//---------------------------------------------------------------------------
#include "TyreProt.h"
#include <stdio.h>
#include <Comctrls.hpp>
#include "def.h"
#include "opcrw.h"
#include "CD_9904_interface.h"
#include <boost/thread.hpp>
// ���������� ����� ���������� ----------------------------------------------
extern TRichEdit *pPrt;                    // ��������� �� ��������� ��� ������ ���������
extern HWND      MainFormHandle;           // ���������� ���� �������� �����
extern String    LogMess;                  // ������ ��� ������ ��������� � �������
extern HANDLE    hOPCCtrlThrd;             // Handler ��� ������ CPU
extern unsigned  OPCCtrlThrdID;            // ������������� ������ CPU
extern bool      OPCControlOn;             // ���������� OPC-�������� ��������
extern bool      OPCConnectOK;             // ���������� � OPC-�������� �����������
extern int       OldMode1,CurrMode1;       // ���������� � ������� ����� ������/���� ���. 1
extern int       OldMode2,CurrMode2;       // ���������� � ������� ����� ������/���� ���. 2
extern int       OldSMode1,CurrSMode1;     // ���������� � ������� ����� �����/���� ���. 1
extern int       OldSMode2,CurrSMode2;     // ���������� � ������� ����� �����/���� ���. 2
extern int       old_step_1;               // ���������� ����� ���� �� ���. 1
extern int       cur_step_1;               // ������� ����� ���� �� ���. 1
extern int       old_step_2;               // ���������� ����� ���� �� ���. 2
extern int       cur_step_2;               // ������� ����� ���� �� ���. 2
extern float     old_speed_1;              // ���������� �������� �� ���. 1
extern float     cur_speed_1;              // ������� �������� �� ���. 1
extern int       old_time_1;               // ����������������� ����������� ���� ���. 1
extern int       cur_time_1;               // ����������������� �������� ���� ���. 1
extern float     old_dist_1;               // ���� �� ���������� ���� ���. 1
extern float     cur_dist_1;               // ���� �� ������� ���� ���. 1
extern float     old_load_1;               // �������� �� ���������� ���� ���. 1
extern float     cur_load_1;               // �������� �� ������� ���� ���. 1
extern float     old_temp_1;               // ����������� �� ���������� ���� ���. 1
extern float     cur_temp_1;               // ����������� �� ������� ���� ���. 1
extern float     old_radius_1;             // ������ �� ���������� ���� ���. 1
extern float     cur_radius_1;             // ������ �� ������� ���� ���. 1
extern float     old_speed_2;              // ���������� �������� �� ���. 2
extern float     cur_speed_2;              // ������� �������� �� ���. 2
extern int       old_time_2;               // ����������������� ����������� ���� ���. 2
extern int       cur_time_2;               // ����������������� �������� ���� ���. 2
extern float     old_dist_2;               // ���� �� ���������� ���� ���. 2
extern float     cur_dist_2;               // ���� �� ������� ���� ���. 2
extern float     old_load_2;               // �������� �� ���������� ���� ���. 2
extern float     cur_load_2;               // �������� �� ������� ���� ���. 2
extern float     old_temp_2;               // ����������� �� ���������� ���� ���. 2
extern float     cur_temp_2;               // ����������� �� ������� ���� ���. 2
extern float     old_radius_2;             // ������ �� ���������� ���� ���. 2
extern float     cur_radius_2;             // ������ �� ������� ���� ���. 2
extern bool      CurrentStart1;            // ������� ��������� ���. 1
extern bool      CurrentStart2;            // ������� ��������� ���. 2
//extern bool      Handle1On;                // ��������� ������� �� ���. 1 ��������
//extern bool      Handle2On;                // ��������� ������� �� ���. 2 ��������
extern short     OPCCtrlStat;              // ����������� ���������� ����� ���������� �������
extern long      TimerCycleCnt;            // ������� ������ �������
// ���������� ���������
extern boost::shared_ptr<Tyre> InpTyre,                 // �������� ��� ����� � �������������� ���������
						TyreA,                   // �������� � ���. �
                 		TyreB;                   // �������� � ���. �
extern String    TyreTypeA,
                 TyreTypeB;                // ��� ��������
extern String    RunProgNameA,
                 RunProgNameB;             // ����������� ��������� �������
// ������� ���������� ��� �������� ���������
// ��������� �� ����
extern String SProgFName;                  // ��� ����� ��� ���������� ��������� �� ����
extern String SProgName;                   // ��� ��������� ��������� �� ����
extern float  STyrePressure;               // �������� � ����
extern int    total_step_S;                // ��������� ���-�� ����� ��������� �� ����
extern float  total_S;                     // ��������� ����������������� ��������� �� ����, ��
extern int    num_S_poll;                  // ���������� ������� �� ����
extern float  poll_step_S[MAXNUMOFPOLLS];  // ������ ������� �� ����
extern float  prog_step_S[MAXNUMOFSTEPS];  // ������ ����� �� ����
extern float  Ssettings[2][MAXNUMOFSTEPS]; // ������ �������� (1-� �������) � ��������� (2-� �������)
// ��������� �� �������
extern String TProgFName;                  // ��� ����� ��� ���������� ��������� �� �������
extern String TProgName;                   // ��� ��������� ��������� �� �������
extern float  TTyrePressure;               // �������� � ����
extern int    total_step_T;                // ��������� ���-�� ����� ��������� �� �������
extern int    total_T;                     // ��������� ����������������� ��������� �� �������, ����
extern int    num_T_poll;                  // ���������� ������� �� �������
extern int    poll_step_T[MAXNUMOFPOLLS];  // ������ ������� �� �������
extern int    prog_step_T[MAXNUMOFSTEPS];  // ������ ����� �� �������
extern float  Tsettings[2][MAXNUMOFSTEPS]; // ������ �������� (1-� �������) � ��������� (2-� �������)
// ���������� ������ CtrlGr1 ------------------------------------------------
// MEMORY
extern bool  bGr1[GR1BOOLITEMSNUM]; // ������ ������� �������� � ������ � ����� DB10
extern bool  *Blowout1;             //M02.1 ������ ���� 1
extern bool  *GuardRail1;           //I125.3 ���������� 1
extern bool  *Pump1On;              //M02.3 ����� 1
extern bool  *Blowout2;             //M03.1 ������ ���� 2
extern bool  *GuardRail2;           //I125.7 ���������� 2
extern bool  *Pump2On;              //M03.3 ����� 1
extern bool  *Carriage1To;          //M50.3 ������ ������� ��� 1
extern bool  *Carriage1From;        //M50.4 ����� ������� ��� 1
extern bool  *Carriage2To;          //M50.5 ������ ������� ��� 2
extern bool  *Carriage2From;        //M50.6 ����� ������� ��� 2
extern bool  *Carriage1Off;         //M02.2 ������� ������� 1 � ��������
extern bool  *Carriage2Off;         //M03.2 ������� ������� 2 � ��������
extern bool  switch_Carriage1;
extern bool  switch_Carriage2;
/*<*/
extern bool  *DestroyLateral1;      //M34.0 ��������� ������� 1
extern bool  *DestroyLateral2;      //M34.2 ���������� ������� 2
extern bool  *DestroyRunning1;      //M34.1 ���������� ������� 1
extern bool  *DestroyRunning2;      //M34.3 ���������� ������� 2

extern bool  *OilLvl;				//M34.4 ������� �����
extern bool  *OilFilter;            //M34.5 ����� �������
extern bool	 *ElDriveDrum;          //M34.6 ��� ���������� ��������������

extern bool  *ControlLateralA;      //M02.3 ���/���� �������� �������� ������� ��� �
extern bool  *ControlLateralB;      //M03.3 ���/���� �������� �������� ������� ��� B
/*>*/
// ���� DB10
extern bool  *AutoMode1;           //DB10,X2.0 ����� ������� 1              S7:[S7 connection_4]DB10,X2.0
extern bool  *ManualMode1;         //DB10,X2.1 ����� ������ 1
extern bool  *Start1;              //DB10,X2.2 ����� ��� 1
extern bool  *Stop1;               //DB10,X2.3 ���� ��� 1
extern bool  *Reset1;              //DB10,X2.4 ����� ��� 1
extern bool  *DrumOn;              //DB10,X2.5 �������� �������
extern bool  *DrumOff;             //DB10,X2.6 ��������� �������
extern bool  *KeepLoad1;           //DB10,X3.0 ��������� �������� 1
extern bool  *ResetData1;          //M0.7 ����� ����������� ��������� 1
extern bool  *AutoMode2;           //DB10,X38.0 ����� ������ 2
extern bool  *ManualMode2;         //DB10,X38.1 ����� ������ 2
extern bool  *Start2;              //DB10,X38.2 ����� ��� 2
extern bool  *Stop2;               //DB10,X38.3 ���� ��� 2
extern bool  *Reset2;              //DB10,X38.4 ����� ��� 2
extern bool  *KeepLoad2;           //DB10,X39.0 ��������� �������� 2
extern bool  *ResetData2;          //M1.7 ����� ����������� ��������� 2
extern bool  *OverLoad1;           //DB10,X38.5 A ���������� �������� �� ���� �� ������� 1
extern bool  *OverLoad2;           //DB10,X38.6 B ���������� �������� �� ���� �� ������� 2
// ���� DB20 - ����� ���������
extern int   iDB20[GR1INTITEMSNUM];
extern int   *fakt_time;            // ����. (�����) �����
extern int   *fakt_time_1;          // ����. ����� 1
extern int   *step_write_1;         // ����� ���� ��� ������ 1
extern int   *step_change_1;        // ����� �������� ���� 1
extern int   *fakt_time_2;          // ����. ����� 2
extern int   *step_write_2;         // ����� ���� ��� ������ 2
extern int   *step_change_2;        // ����� �������� ���� 2
extern int   *next_step_time1;      // ��������� ��� �� ������� 1
extern int   *next_step_time2;      // ��������� ��� �� ������� 2
extern int   *next_step_change1;    // ����� ���������� �������� ���� 1
extern int   *next_step_change2;    // ����� ���������� �������� ���� 2
/*<*/
extern float fGr1[GR1FLTITEMSNUM];
extern float *OilTemp;               //DB20,x100 ����������� �����
extern float *ReadLoading_1;         //DB10,REAL26 �������� 1  ����������
extern float *ReadLoading_2;         //DB10,REAL62 �������� 2  ����������
extern float *max_speed;   		   //DB10,REAL138 ������������ �������� � �����
extern float *min_speed;           //DB10,REAL ����������� �������� � �����
extern float *min_load_1;  		   //DB10,REAL142 ���. �������� 1 � �����
extern float *max_load_1;   	   //DB10,REAL146 ���� �������� 1 � �����
extern float *min_load_2;   	   //DB10,REAL150 ��� �������� 2 � �����
extern float *max_load_2;   	   //DB10,REAL154 ���� �������� 2 � �����

extern float *min_temp_1;          //DB10,REAL158 ����������� ����������� � ��� �
extern float *max_temp_1;          //DB10,REAL162 ������������ ����������� � ��� �
extern float *min_temp_2;          //DB10,REAL166 ����������� ����������� � ��� �
extern float *max_temp_2;          //DB10,REAL170 ������������ ����������� � ��� �
/*>*/

// ������ ���������� � �����������
extern wchar_t *Gr1ItemsNme[GR1ITEMSNUM];
// End of CtrlGr1 -----------------------------------------------------------
// ���������� ������ CtrlGr2 ------------------------------------------------
// ���� DB20 - ����� ���������
extern float fDB20[GR2FLOATITEMSNUM];
extern float *fakt_speed;           // ����������� ��������
extern float *set_speed;            // �������� �������� �� ������� ����
extern float *fakt_distance;        // ����. (�����) ������
extern float *fakt_distance_1;      // ����. ������ 1
extern float *fakt_loading_1;       // ����. �������� 1
extern float *fakt_radius_1;        // ����. ������ 1
extern float *fakt_temper_1;        // ����. ����������� 1
extern float *set_speed_1;          // �������� �������� 1 �� ������� ����
extern float *set_loading_1;        // �������� �������� 1 �� ������� ����
extern float *fakt_distance_2;      // ����. ������ 2
extern float *fakt_loading_2;       // ����. �������� 2
extern float *fakt_radius_2;        // ����. ������ 2
extern float *fakt_temper_2;        // ����. ����������� 2
extern float *set_speed_2;          // �������� �������� 2 �� ������� ����
extern float *set_loading_2;        // �������� �������� 2 �� ������� ����
extern float *next_step_distance1;  // ��������� ��� �� ������� 1
extern float *next_step_distance2;  // ��������� ��� �� ������� 2
extern float *next_speed1;          // �������� �� ��������� ����1
extern float *next_speed2;          // �������� �� ��������� ����2
extern float *next_loading1;        // �������� �� ��������� ����1
extern float *next_loading2;        // �������� �� ��������� ����2
extern float *next_set_distance1;   //DB20,REAL196 ��������� ���������� ����
extern float *next_set_distance2;   //DB20,REAL200 ��������� ���������� ����

extern int i2DB20[GR2INTITEMSNUM];
extern int *next_set_time1;  		//DB20,DINT188  ����� ���������� ����
extern int *next_set_time2;  		//DB20,DINT192   ����� ���������� ����
// ������ ���������� � ����� DB20
extern wchar_t *Gr2ItemsNme[GR2ITEMSNUM];
// End of CtrlGr2 -----------------------------------------------------------
// ���������� ������ CtrlGr3 ------------------------------------------------
// ���� DB10
extern int   iDB10[GR3INTITEMSNUM];
extern int   *T_end_cycle_1;       //DB10,DINT10 ��� ����� 1
extern int   *T_end_cycle_2;       //DB10,DINT46 ��� ����� 2
extern int   *type_cycle_1;        //DB10,INT4 ��� ����� 1                  S7:[S7 connection_4]DB10,INT4
extern int   *StepsQty1;           //DB10,INT34 ���������� ����� ��������� 1
extern int   *PollsQty1;           //DB10,INT36 ���������� ������� 1
extern int   *type_cycle_2;        //DB10,INT40 ��� ����� 2                 S7:[S7 connection_4]DB10,INT4
extern int   *StepsQty2;           //DB10,INT70 ���������� ����� ��������� 1
extern int   *PollsQty2;           //DB10,INT72 ���������� ������� 1
extern float fDB10[GR3FLTITEMSNUM];
extern float *S_end_cycle_1;       //DB10,REAL18 �������� ������ ����� 1    S7:[S7 connection_4]DB10,REAL18
extern float *DrumSpeed;           //DB10,REAL22 �������� ��������
extern float *Loading_1;           //DB10,REAL26 �������� 1
extern float *Radius_1;            //DB10,REAL30 ������ 1
extern float *S_end_cycle_2;       //DB10,REAL54 �������� ������ ����� 2    S7:[S7 connection_4]DB10,REAL18
extern float *Loading_2;           //DB10,REAL62 �������� 2
extern float *Radius_2;            //DB10,REAL66 ������ 2
extern float *CorrASetSpeed;       //DB10,REAL74 �������� � �� ������� ��������
extern float *CorrBSetSpeed;       //DB10,REAL78 �������� � �� ������� ��������
extern float *CorrAMeasSpeed;      //DB10,REAL82 �������� � �� ��������� ��������
extern float *CorrBMeasSpeed;      //DB10,REAL86 �������� � �� ��������� ��������
extern float *Temp1LowLimit;       //DB10,REAL90 ������ ������ ������� ����������� 1
extern float *Temp1UpLimit;        //DB10,REAL94 ������� ������ ������� ����������� 1
extern float *CorrAMeasLoad1;      //DB10,REAL98 �������� � �� ���������  �������� 1
extern float *CorrBMeasLoad1;      //DB10,REAL102 �������� � �� ��������� �������� 1
extern float *Temp2LowLimit;       //DB10,REAL106 ������ ������ ������� ����������� 2
extern float *Temp2UpLimit;        //DB10,REAL110 ������� ������ ������� ����������� 2
extern float *CorrAMeasLoad2;      //DB10,REAL114 �������� � �� ���������  �������� 2
extern float *CorrBMeasLoad2;      //DB10,REAL118 �������� � �� ��������� �������� 2
extern float *Rad1LowLimit;        //DB10,REAL122 ������ ������ ��������� ������� ������� 1
extern float *Rad1UpLimit;         //DB10,REAL126 ������� ������ ��������� ������� ������� 1
extern float *Rad2LowLimit;        //DB10,REAL130 ������ ������ ��������� ������� ������� 2
extern float *Rad2UpLimit;         //DB10,REAL134 ������� ������ ��������� ������� ������� 2

// ������ ���������� � ������ 3
extern wchar_t *Gr3ItemsNme[GR3ITEMSNUM];
// End of CtrlGr3 -----------------------------------------------------------
// ���������� ������ CtrlGr4 ------------------------------------------------
// ���� DB8
extern float poll_step_SA[MAXNUMOFPOLLS];
// ���� DB22
extern float step_SA[MAXNUMOFSTEPS];
// ������ ���������� � ������ 4
extern wchar_t *Gr4ItemsNme[GR4ITEMSNUM];
extern wchar_t Gr4ItemsAddr[GR4ITEMSNUM][ADDRLEN];
extern String  AddrDB8,AddrDB22;
// End of CtrlGr4 -----------------------------------------------------------
// ���������� ������ CtrlGr5 ------------------------------------------------
// ���� DB7
extern int   poll_step_TA[MAXNUMOFPOLLS];
// ���� DB21
extern int   step_TA[MAXNUMOFSTEPS];
// ������ ���������� � ������ 5
extern wchar_t *Gr5ItemsNme[GR5ITEMSNUM];
extern wchar_t Gr5ItemsAddr[GR5ITEMSNUM][ADDRLEN];
extern String  AddrDB7, AddrDB21;
// End of CtrlGr5 -----------------------------------------------------------
// ���������� ������ CtrlGr6 ------------------------------------------------
// ���� DB23
extern float setting_A[2][MAXNUMOFSTEPS];
// ������ ���������� � ������ 6
extern wchar_t *Gr6ItemsNme[GR6ITEMSNUM];
extern wchar_t Gr6ItemsAddr[GR6ITEMSNUM][ADDRLEN];
extern String  AddrDB23;
// End of CtrlGr6 -----------------------------------------------------------
// ���������� ������ CtrlGr7 ------------------------------------------------
// ���� DB1
extern int   read_TA[MAXNUMOFPOLLS];
// ���� DB2
extern float read_VA[MAXNUMOFPOLLS];
// ���� DB3
extern float read_SA[MAXNUMOFPOLLS];
// ���� DB4
extern float read_LA[MAXNUMOFPOLLS];
// ���� DB5
extern float read_RA[MAXNUMOFPOLLS];
// ���� DB6
extern float read_TempA[MAXNUMOFPOLLS];
// ������ ���������� � ������ 7
extern wchar_t *Gr7ItemsNme[GR7ARRAYSNUM];
// End of CtrlGr7 -----------------------------------------------------------
// ���������� ������ CtrlGr8 ------------------------------------------------
// ���� DB18
extern float poll_step_SB[MAXNUMOFPOLLS];
// ���� DB32
extern float step_SB[MAXNUMOFSTEPS];
// ������ ���������� � ������ 8
extern wchar_t *Gr8ItemsNme[GR8ITEMSNUM];
extern wchar_t Gr8ItemsAddr[GR8ITEMSNUM][ADDRLEN];
extern String  AddrDB18,AddrDB32;
// End of CtrlGr8 -----------------------------------------------------------
// ���������� ������ CtrlGr9 ------------------------------------------------
// ���� DB17
extern int   poll_step_TB[MAXNUMOFPOLLS];
// ���� DB31
extern int   step_TB[MAXNUMOFSTEPS];
// ������ ���������� � ������ 9
extern wchar_t *Gr9ItemsNme[GR9ITEMSNUM];
extern wchar_t Gr9ItemsAddr[GR9ITEMSNUM][ADDRLEN];
extern String  AddrDB17, AddrDB31;
// End of CtrlGr9 -----------------------------------------------------------
// ���������� ������ CtrlGr10 -----------------------------------------------
// ���� DB33
extern float setting_B[2][MAXNUMOFSTEPS];
// ������ ���������� � ������ 10
extern wchar_t *Gr10ItemsNme[GR10ITEMSNUM];
extern wchar_t Gr10ItemsAddr[GR10ITEMSNUM][ADDRLEN];
extern String  AddrDB33;
// End of CtrlGr10 ----------------------------------------------------------
// ���������� ������ CtrlGr11 -----------------------------------------------
// ���� DB11
extern int   read_TB[MAXNUMOFPOLLS];
// ���� DB12
extern float read_VB[MAXNUMOFPOLLS];
// ���� DB13
extern float read_SB[MAXNUMOFPOLLS];
// ���� DB14
extern float read_LB[MAXNUMOFPOLLS];
// ���� DB15
extern float read_RB[MAXNUMOFPOLLS];
// ���� DB16
extern float read_TempB[MAXNUMOFPOLLS];
// ������ ���������� � ������ 11
extern wchar_t *Gr11ItemsNme[GR11ARRAYSNUM];
// End of CtrlGr11 ----------------------------------------------------------
// ���������� ������ CtrlGr12 -----------------------------------------------
// ���� DB71
extern float fDB71[GR12ITEMSNUM];
extern float *A1[GR12ARRAYSIZE];    //DB71,REAL2-172 ������������ ��������� ���. 1    S7:[S7 connection_4]DB10,REAL18
extern float *Q1[GR12ARRAYSIZE];    //DB71,REAL6-176 ������� �������� ������������� ��������� ���. 1    S7:[S7 connection_4]DB10,REAL18
// ������ ���������� � ������ 12
extern wchar_t *Gr12ItemsNme[GR12ITEMSNUM];
// End of CtrlGr12 ----------------------------------------------------------
// ���������� ������ CtrlGr13 -----------------------------------------------
// ���� DB70
extern float fDB70[GR13ITEMSNUM];
extern float *A2[GR13ARRAYSIZE];    //DB70,REAL2-172 ������������ ��������� ���. 2    S7:[S7 connection_4]DB10,REAL18
extern float *Q2[GR13ARRAYSIZE];    //DB70,REAL6-176 ������� �������� ������������� ��������� ���. 2    S7:[S7 connection_4]DB10,REAL18
// ������ ���������� � ������ 13
extern wchar_t *Gr13ItemsNme[GR12ITEMSNUM];
// End of CtrlGr12 ----------------------------------------------------------


////////////////////////////////////////////////////////////////////////////////
////////////////////////��������� ������� ��������//////////////////////////////
extern CD_9904_interface *cd_9904;
extern HANDLE CD_9904Thread;
////////////////////////////////////////////////////////////////////////////////


// ���������� ����� ������� -------------------------------------------------
void				ClearTProg	(void);		   //����� ��������� �� �������
void				ClearSProg	(void);        //����� ��������� �� ����
void     __fastcall PntInit(void);            // ������������� ���������� ��� ����� 12 � 13
void     __fastcall ResetKA(float *A[]);      // ����� ������� � � ��������
void     __fastcall LogPrint(                 // ����� ��������� � ���� ���������
                             String,TColor=clWhite);
void     __fastcall SLogPrint(                // ����� ��������� � ���� ��������� ��� ������ SendMessage
                             String,TColor=clWhite);
void     __fastcall PLogPrint(                // ����� ��������� � ���� ��������� ��� ������ PostMessage
                             String,TColor=clWhite);
void     __fastcall LogPrintF(                // ����� ��������� � ���� �������
                             String FNme,     // ��� ����� �������
                             String Mess,     // ���������
                             TColor=clLime);  // ���� ��������� � ����
String   __fastcall LogFName(void);           // ��������� ����� ����� �������
String   __fastcall FileNameParse(            // ������� ��������� ����� ����� �� ������� ����
							 String SFN);
int      __fastcall NextCycleCount(void);     // ���������� ����� �������� �� 1
void     __fastcall OPCControlStart(TTimer*); // ������ ���������� �������
void     __fastcall OPCControlStop(TTimer*);  // ������� ���������� �������
void     __fastcall OPCControlPause(TTimer*); // ������������ ���������� �������
void     __fastcall OPCControlResume(TTimer*);// ������������� ���������� �������
String   __fastcall mSecToHMSStr(int tm);     // ������� ������ ���-�� ���� � ������ ��:��:��
String   __fastcall ReadString(FILE *fp);     // ������ ������ ���� String �� �����
void     __fastcall WriteString(              // ������ ������ ���� String � ����
                                String ws,
                                FILE *fp);
void     __fastcall ReadSProgFmFile(void);    // ��������� ��������� �� ���� �� �����
void     __fastcall WriteSProgToFile(void);   // �������� ��������� �� ���� � ����
float    __fastcall StrToFlt(String);         // �������������� ������ � �������� ���� float
int      __fastcall StrToI(String);           // �������������� ������ � �������� ���� int
String   __fastcall FltToStr(                 // �������������� ����� � ������ ������ l
                      float f,                // ������������� �����
                      TFloatFormat ff,        // ������
                      int l,                  // ����� ������
                      int r);                 // ����� ������� �����
String   __fastcall IntToS(                   // �������������� ������ � ������ ������ l
                      int i,                  // ������������� �����
                      int l);                 // ����� ������
void     __fastcall ReadTProgFmFile(void);    // ��������� ��������� �� ������� �� �����
void     __fastcall WriteTProgToFile(void);   // �������� ��������� �� ������� � ����
void     __fastcall LeastSquares(             // ������ ������������� A � B ������� ���������� ���������
					             float X[],   // ������ X
					             float Y[],   // ������ Y
					             int   N,     // ����������� �������
					             float &A,    //
					             float &B);   //
int      __fastcall BUnion(bool b1, bool b2); // ����������� �������� ���������� � ����� ��������


//��������� ����������
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
extern bool needSaveA,
			needSaveB;    //���������� �������������� ���������� �� ���������
extern bool StendConnection;//��������� ����� �� �������
extern OPCRW *pOPC;// ��������� �� ����� OPCRW
#ifdef _DEBUG
extern int ThreadCounter;
#endif
#endif
