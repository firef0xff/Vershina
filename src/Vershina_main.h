﻿// ---------------------------------------------------------------------------

#ifndef RB_mainH
#define RB_mainH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnCtrls.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <ActnMenus.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>
#include <XPStyleActnCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Mask.hpp>
#include <Dialogs.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "SQL.h"
#include <System.Actions.hpp>

#include <memory>
#include "pos/ui_pos.h"
#include "prg/time_programm.h"
#include "prg/path_programm.h"
#include "data_updater/data_updater.h"
#include <mutex>

// ---------------------------------------------------------------------------
class TmfRB : public TForm
{
__published: // IDE-managed Components
   TActionManager *amRB;
   TFileExit *RBExit;
   TAction *AboutProg;
   TStatusBar *sbRB;
   TAction *CommonParamRead;
   TPageControl *pcRB;
   TTabSheet *tsCurrentStatus;
   TTabSheet *tsProtocol;
   TTabSheet *tsTestProgramSetting;
   TTabSheet *tsCalibration;
   TTabSheet *tsLog;
   TRichEdit *reLog;
   TPanel *pnlCPU;
   TGroupBox *gbPosition1ControlBox;
   TGroupBox *gbSensors1;
   TButton *btnGeneralStop;
   TAction *acOPCControlStart;
   TAction *acOPCControlStop;
   TPanel *pParam1;
   TPanel *pParam2;
   TTabSheet *tsManual;
   TSplitter *Splitter1;
   TStaticText *stP1TL0C1;
   TStaticText *stP1CurDate;
   TStaticText *stP1TTyreType;
   TStaticText *stP1L1TyreTypeA;
   TStaticText *stP1TProgName;
   TStaticText *stP1L2ProgNameA;
   TPanel *pP1PT2;
   TPanel *pP1PL1Ttl;
   TPanel *pP1L1C1Ttl;
   TPanel *pP1L1C2Ttl;
   TPanel *pP1L1C3Ttl;
   TPanel *pP1PL2Ttl;
   TPanel *pP1PL3Ttl;
   TPanel *pP1PL4Ttl;
   TPanel *pP1PL5Ttl;
   TPanel *pP1PL6Ttl;
   TPanel *pP1PL7Ttl;
   TPanel *pP1PL8Ttl;
   TPanel *pP1PL9Ttl;
   TStaticText *stP1CParL1C1;
   TStaticText *stP1CParL1C2;
   TStaticText *stP1CParL1C3;
   TStaticText *stP1CParL2C1;
   TStaticText *stP1CParL2C2;
   TStaticText *stP1CParL2C3;
   TStaticText *stP1CParL3C1;
   TStaticText *stP1CParL3C2;
   TStaticText *stP1CParL3C3;
   TStaticText *stP1CParL4C3;
   TStaticText *stP1CParL4C2;
   TStaticText *stP1CParL4C1;
   TStaticText *stP1CParL5C1;
   TStaticText *stP1CParL5C2;
   TStaticText *stP1CParL5C3;
   TStaticText *stP1CParL6C1;
   TStaticText *stP1CParL6C2;
   TStaticText *stP1CParL6C3;
   TStaticText *stP1CParL7C1;
   TStaticText *stP1CParL7C2;
   TStaticText *stP1CParL7C3;
   TStaticText *stP1CParL8C1;
   TStaticText *stP1CParL8C2;
   TStaticText *stP1CParL8C3;
   TPanel *pP2TtlL0C1;
   TPanel *pP2TtlL1C1;
   TPanel *pP2TtlL1C2;
   TPanel *pP2TtlL1C0;
   TPanel *pP2TtlL2C0;
   TPanel *pP2TtlL3C0;
   TPanel *pP2TtlL4C0;
   TPanel *pP2TtlL7C0;
   TPanel *pP2TtlL5C0;
   TPanel *pP2TtlL6C0;
   TStaticText *stP2CParL1C1;
   TStaticText *stP2CParL2C1;
   TStaticText *stP2CParL3C1;
   TStaticText *stP2CParL4C1;
   TStaticText *stP2CParL5C1;
   TStaticText *stP2CParL6C1;
   TStaticText *stP2CParL7C1;
   TStaticText *stP2CParL7C2;
   TStaticText *stP2CParL6C2;
   TStaticText *stP2CParL5C2;
   TStaticText *stP2CParL4C2;
   TStaticText *stP2CParL3C2;
   TStaticText *stP2CParL2C2;
   TStaticText *stP2CParL1C2;
   TGroupBox *gbDrum;
   TLabeledEdit *leSetDrumSpeed;
   TPanel *pDrumTtl;
   TButton *btnDrumOn;
   TButton *btnDrumOff;
   TTrackBar *tbCurrentDrumSpeed;
   TPanel *pDrumSpeed;
   TGroupBox *gbCarriage1;
   TSpeedButton *sbCarriage1Off;
   TLabel *lCarriage1Off;
   TPanel *pCarr1Ttl;
   TButton *btnCarriage1From;
   TButton *btnCarriage1To;
   TButton *btnCarriage1Stop;
   TPanel *pCarr1Load;
   TLabel *lSpeed00;
   TLabeledEdit *leCurrentDrumSpeed;
   TLabel *lSpeed200;
   TLabel *lSpeed180;
   TLabel *lSpeed160;
   TLabel *lSpeed140;
   TLabel *lSpeed120;
   TLabel *lSpeed100;
   TLabel *lSpeed80;
   TLabel *lSpeed60;
   TLabel *lSpeed40;
   TLabel *lSpeed20;
   TLabeledEdit *leCurrentLoad1;
   TLabeledEdit *leSetLoad1;
   TTrackBar *tbCurrentLoad1;
   TLabel *lLoad80;
   TLabel *lLoad70;
   TLabel *lLoad60;
   TLabel *lLoad50;
   TLabel *lLoad40;
   TLabel *lLoad30;
   TLabel *lLoad20;
   TLabel *lLoad10;
   TLabel *lLoad0;
   TLabeledEdit *leCurrentT1;
   TLabeledEdit *leCurrentR1;
   TAction *acDrumOn;
   TAction *acDrumOff;
   TAction *acCarriage1From;
   TAction *acCarriage1Stop;
   TAction *acCarriage1To;
   TAction *acGeneralStop;
   TPageControl *pcProtTitle;
   TTabSheet *tsProtocolA;
   TTabSheet *tsNewProtocol;
   TLabeledEdit *leProtocolNo;
   TLabeledEdit *leTyreSize;
   TLabeledEdit *leTyreType;
   TLabeledEdit *leTestProc;
   TLabeledEdit *leStandNo;
   TLabeledEdit *leManufacturer;
   TLabeledEdit *leDrumD;
   TLabeledEdit *leCustomer;
   TLabeledEdit *leSeralNo;
   TLabeledEdit *leFormNo;
   TLabeledEdit *leOrderNo;
   TLabeledEdit *lePerfSpecNo;
   TPanel *pCommonProtData;
   TPanel *pTyreParam;
   TLabeledEdit *leLoadIndex;
   TLabeledEdit *leMaxLoad;
   TLabeledEdit *leSpeedIndex;
   TLabeledEdit *leMaxSpeed;
   TLabeledEdit *leStaticR;
   TLabeledEdit *leOuterD;
   TLabeledEdit *leRim;
   TLabeledEdit *leQMaxPressure;
   TLabeledEdit *leTyreWide;
   TRadioGroup *rgTyreType;
   TPanel *pTestMode;
   TLabeledEdit *leTestLoad;
   TLabeledEdit *leInitPressure;
   TLabeledEdit *leTestSpeed;
   TComboBox *cmbTestMode;
   TLabel *lblTestMode;
   TLabeledEdit *leTestTimePath;
   TLabeledEdit *leAsks;
   TPageControl *pcTestProg;
   TTabSheet *tsTimeProg;
   TFileOpen *acSProgFileOpen;
   TFileSaveAs *acSProgFileSaveAs;
   TAction *acLoadTestResFmPosA;
   TLabeledEdit *leTProgName;
   TLabeledEdit *leTTyrePressure;
   TLabeledEdit *leTTotalStepsQty;
   TLabeledEdit *leTotalTestTime;
   TLabeledEdit *leTPollingTotalQty;
   TStringGrid *sgTProgram;
   TStringGrid *sgTPolling;
   TLabel *lTProgTblNme;
   TLabel *lTPollingTblNme1;
   TButton *btnSaveTProgToFile;
   TButton *btnOpenTProgFmFile;
   TButton *btnLoadTProgToPosA;
   TButton *btnCheckTProg;
   TFileOpen *acTProgFileOpen;
   TFileSaveAs *acTProgFileSaveAs;
   TSpeedButton *sbCarr1Fm;
   TSpeedButton *sbCarr1To;
   TSpeedButton *sbDrumOn;
   TButton *btnNewTProg;
   TTabSheet *tsSProg;
   TPanel *pTProgTtl;
   TPanel *pSProgTtl;
   TLabeledEdit *leSProgName;
   TLabeledEdit *leSTyrePressure;
   TLabeledEdit *leSTotalStepsQty;
   TLabeledEdit *leTotalTestS;
   TLabeledEdit *leSPollingTotalQty;
   TLabel *lSPollingTblNme1;
   TLabel *lSProgTblNme;
   TStringGrid *sgSProgram;
   TStringGrid *sgSPolling;
   TButton *btnNewSProg;
   TButton *btnCheckSProg;
   TButton *btnSaveSProgToFile;
   TButton *btnOpenSProgFmFile;
   TButton *btnLoadSProgToPosA;
   TButton *btnLoadProtToPosA;
   TMaskEdit *meManDate;
   TLabel *lblManDate;
   TPanel *pCurrentProtATtl;
   TLabeledEdit *leTyreModelA;
   TLabeledEdit *leTyreSyzeA;
   TLabeledEdit *leManDateA;
   TLabeledEdit *leSerialNoA;
   TLabeledEdit *leManufacturerA;
   TLabeledEdit *leTestCustomerA;
   TLabeledEdit *leFormNoA;
   TLabeledEdit *leTestProcA;
   TLabeledEdit *leDrumD_A;
   TLabeledEdit *lePerfSpecNoA;
   TLabeledEdit *leOrderNoA;
   TPanel *pTyreParamATtl;
   TLabeledEdit *leLoadIndA;
   TLabeledEdit *leMaxLoadA;
   TLabeledEdit *leSpeedIndA;
   TLabeledEdit *leMaxSpeedA;
   TLabeledEdit *leStaticR_A;
   TLabeledEdit *leTyreWideA;
   TLabeledEdit *leOuterD_A;
   TLabeledEdit *leRimA;
   TLabeledEdit *leQMaxPressureA;
   TButton *btnClearProt;
   TButton *btnSaveProtTtlToFile;
   TButton *btnLoadProtTtlFmFile;
   TActionMainMenuBar *ammbRB;
   TFileSaveAs *acProtTitleFileSaveAs;
   TFileOpen *acProtTitleFileOpen;
   TPanel *pTestResTtlA;
   TLabeledEdit *leTestDurationA;
   TLabeledEdit *leTestModeA;
   TLabeledEdit *leTyrePressureA;
   TLabeledEdit *leStepQtyA;
   TLabeledEdit *lePollsQtyA;
   TStringGrid *sgTestResultA;
   TButton *btnLoadTestResPosA;
   TButton *btnSaveTestResPosAToFile;
   TButton *btnPrintTestResPosA;
   TFileSaveAs *acPrintProtPosAToFile;
   TPageControl *pcCalibration;
   TTabSheet *tsLoadCalibr;
   TTabSheet *tsRadiusCalibr;
   TTabSheet *tsTempCalibr;
   TTabSheet *tsSpeedCalibr;
   TPanel *pSpeedCalibrTtl;
   TStringGrid *sgSpeedCalibr;
   TLabeledEdit *leCurrentVSet;
   TLabeledEdit *leReadV;
   TLabeledEdit *leMeasuredV;
   TButton *btnPrevCalibrV;
   TButton *btnNextCalibrV;
   TButton *btnCalibrVCalc;
   TButton *btnVCalibrDrumOn;
   TButton *btnVCalibrDrumOff;
   TButton *btnClearVCalibreTable;
   TButton *btnSpdCalibrTablePrint;
   TFileSaveAs *acPrintSpdCalibrProt;
   TPageControl *pcLoadCalibr;
   TTabSheet *tsLoadCalibrA;
   TPanel *pLoadCalibrBTtl;
   TStringGrid *sgLoadCalibrA;
   TButton *btnPrevCalibrLoadA;
   TLabeledEdit *leCurrentLoadSetA;
   TLabeledEdit *leReadLoadA;
   TLabeledEdit *leMeasuredLoadA;
   TButton *btnNextCalibrLoadA;
   TButton *btnClearLoadCalibreTableA;
   TButton *btnLoadCalibrCalcA;
   TButton *btnLoadCalibrTableAPrint;
   TButton *btnPumpOnA;
   TButton *btnPumpOffA;
   TFileSaveAs *acPrintLoadCalibrProtA;
   TAction *acPumpOnA;
   TAction *acPumpOffA;
   TPageControl *pcTempCalibr;
   TTabSheet *tsTCalibrA;
   TPanel *pTCalibrATtl;
   TStringGrid *sgTCalibrA;
   TButton *btnPrevTCalibrA;
   TLabeledEdit *leReadTA;
   TLabeledEdit *leMeasTA;
   TButton *btnNextTCalibrA;
   TButton *btnClearTCalibrTableA;
   TButton *btnTCalibrCalcA;
   TButton *btnTCalibrTableAPrint;
   TFileSaveAs *acPrintTCalibrProtA;
   TPageControl *pcRadiusCalibr;
   TTabSheet *tsRCalibrA;
   TPanel *pRCalibrATtl;
   TStringGrid *sgRCalibrA;
   TButton *btnPrevRCalibrA;
   TLabeledEdit *leReadRA;
   TLabeledEdit *leMeasRA;
   TButton *btnNextRCalibrA;
   TButton *btnClearRCalibrTableA;
   TButton *btnRCalibrCalcA;
   TButton *btnRCalibrTableAPrint;
   TButton *btnCalibrCarr1Fm;
   TButton *btnCalibrCarr1Stop;
   TButton *btnCalibrCarr1To;
   TFileSaveAs *acPrintRCalibrProtA;
   TTabSheet *tsSert;
   TPageControl *pcSert;
   TTabSheet *tsDrumSpeedSert;
   TTabSheet *tsTemSert;
   TTabSheet *tsLoadSert;
   TPageControl *pcLoadSert;
   TTabSheet *tsLoadSertA;
   TPanel *pLoadSertATtl;
   TStringGrid *sgLoadSertA;
   TButton *btnPrevSertLoadA;
   TLabeledEdit *leCurrentLoadSertSetA;
   TLabeledEdit *leReadLoadSertA;
   TLabeledEdit *leMeasLoadSertA;
   TButton *btnNextSertLoadA;
   TButton *btnSertPumpOnA;
   TButton *btnSertPumpOffA;
   TButton *btnLoadSertClearTableA;
   TButton *btnLoadSertCalcA;
   TButton *btnLoadSertPrintProtA;
   TButton *btnLoadSertAToPLC;
   TFileSaveAs *acLoadSertPrintProtA;
   TPanel *pDrumSpeedSertTtl;
   TLabeledEdit *leSetSpeedCoef;
   TLabeledEdit *leMeasSpeedCoef;
   TButton *btnLoadSpeedCoefToPLC;
   TButton *btnResetCalibrCoeffA;
   TButton *btnTLimitsCalcA;
   TPanel *pTSertTtl;
   TGroupBox *gbTSertA;
   TEdit *edCalcLowLimitA;
   TLabel *lblCalcLimitsA;
   TEdit *edCalcUpLimitA;
   TLabel *lblLowA;
   TLabel *lblHighA;
   TLabel *lblTLoadedLimitsA;
   TEdit *edLoadedLowLimitA;
   TEdit *edLoadedUpLimitA;
   TButton *btnLoadTLimitsA;
   TButton *btnUploadSertAFmPLC;
   TTabSheet *tsRadSert;
   TLabeledEdit *leRShiftA;
   TButton *btnRShiftALoadToPLC;
   TPanel *pRSertTtl;
   TFilePrintSetup *acPrintSetup;
   TFontDialog *PrinterFontDialog;
   TAction *Action1;
   TGroupBox *gbOil;
   TADOConnection *ADC;
   TAction *acSettingsManagment;
   TAction *_acTProgFileSaveAs;
   TAction *_acSProgFileSaveAs;
   TAction *_acProtTitleFileSaveAs;
   TAction *_acPrintProtPosAToFile;
   TAction *_acPrintLoadCalibrProtA;
   TAction *_acLoadSertPrintProtA;
   TAction *_acPrintRCalibrProtA;
   TAction *_acPrintTCalibrProtA;
   TAction *_acPrintSpdCalibrProt;
   TEdit *IndBlowout1;
   TEdit *IndGuardrail1;
   TEdit *IndDestroyLateral1;
   TEdit *IndDestroyRunning1;
   TEdit *IndOilLvl;
   TEdit *IndlOilFilter;
   TEdit *IndDriveDrum;
   TLabel *Label1;
   TLabel *Label2;
   TEdit *eOilTemp;
   TLabel *TreadCounter;
   TTabSheet *tsEmSettings;
   TGroupBox *GroupBox1;
   TGroupBox *GroupBox2;
   TLabeledEdit *leEmMaxSpeed;
   TLabeledEdit *leEmMaxLoad_1;
   TLabeledEdit *leEmMinLoad_1;
   TLabeledEdit *leEmMaxSpeedR;
   TLabeledEdit *leEmMaxLoad_1R;
   TLabeledEdit *leEmMinLoad_1R;
   TButton *btEmSettings;
   TGroupBox *rgPos1Mode;
   TSpeedButton *sbAutomatA;
   TSpeedButton *sbManualA;
   TLabel *Label3;
   TLabel *Label4;
   TGroupBox *rgPos1StartStop;
   TSpeedButton *sbStartA;
   TSpeedButton *sbStopA;
   TLabel *Label5;
   TLabel *Label6;
   TEdit *eStendConnection;
   TCheckBox *cbControlLateralA;
   TLabeledEdit *leEmMinSpeed;
   TLabeledEdit *leEmMinSpeedR;
   TLabeledEdit *leSetSpeedCoefReal;
   TLabeledEdit *leMeasSpeedCoefReal;
   TButton *btnResetResPosA;
   TLabel *lLoad90;
   TLabel *lLoad100;
   TLabel *lLoad110;
   TLabeledEdit *leEmMinTemp_1;
   TLabeledEdit *leEmMaxTemp_1;
   TLabeledEdit *leEmMinTemp_1R;
   TLabeledEdit *leEmMaxTemp_1R;
   TTimer *ShowTimer;

   void __fastcall OnCommonParamReadExec(TObject *Sender);
   void __fastcall OPCControlStartExec(void);
   void __fastcall OnOPCControlStopExec(TObject *Sender);
   void __fastcall OnRGPos1ModeClick(TObject *Sender);
   void __fastcall OnRGPos1StartStopClick(TObject *Sender);
   void __fastcall OnDrumOn(TObject *Sender);
   void __fastcall OnDrumOff(TObject *Sender);
   void __fastcall OnCarriage1To(TObject *Sender);
   void __fastcall OnCarriage1From(TObject *Sender);
   void __fastcall OnCarriage1Stop(TObject *Sender);
   void __fastcall OnGeneralStop(TObject *Sender);
   void __fastcall OnTestModeChange(TObject *Sender);
   void __fastcall OnMainFormCreate(TObject *Sender);
   void __fastcall OnSProgFileOpen(TObject *Sender);
   void __fastcall OnSProgFileSaveAs(TObject *Sender);
   void __fastcall OnLoadSProgToPosA(TObject *Sender);
   void __fastcall OnMFResize(TObject *Sender);
   void __fastcall OnTProgFileSaveAs(TObject *Sender);
   void __fastcall OnTProgFileOpen(TObject *Sender);
   void __fastcall OnLoadTProgToPosA(TObject *Sender);
   void __fastcall OnStringGridExit(TObject *Sender);
   void __fastcall OnGetEditMask(TObject *Sender, int ACol, int ARow,
      AnsiString &Value);
   void __fastcall OnSGKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
   void __fastcall OnTProgCheck(TObject *Sender);
   void __fastcall OnSGKeyPress(TObject *Sender, char &Key);
   void __fastcall OnSGSEnter(TObject *Sender);
   void __fastcall OnLEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
   void __fastcall OnNewTProg(TObject *Sender);
   void __fastcall OnSGTEnter(TObject *Sender);
   void __fastcall OnSProgCheck(TObject *Sender);
   void __fastcall OnNewSProg(TObject *Sender);
   void __fastcall OnLoadProtToPosA(TObject *Sender);
   void __fastcall OnLoadTestResFmPosA(TObject *Sender);
   void __fastcall OnClearProt(TObject *Sender);
   void __fastcall OnProtTtlFileSaveAs(TObject *Sender);
   void __fastcall OnProtTtlFileOpen(TObject *Sender);
   void __fastcall OnCloseQuery(TObject *Sender, bool &CanClose);
   void __fastcall OnPrintProtPosAToFile(TObject *Sender);
   void __fastcall OnVCalibrClear(TObject *Sender);
   void __fastcall OnVCalibrCalc(TObject *Sender);
   void __fastcall OnNextCalibrVBtn(TObject *Sender);
   void __fastcall OnPrevCalibrVBtn(TObject *Sender);
   void __fastcall OnCalibrDrawCell(TObject *Sender, int ACol, int ARow,
      TRect &Rect, TGridDrawState State);
   void __fastcall OnPrintSpdCalibrProtocol(TObject *Sender);
   void __fastcall OnPump1On(TObject *Sender);
   void __fastcall OnPump1Off(TObject *Sender);
   void __fastcall OnNextCalibrLoadBtn(TObject *Sender);
   void __fastcall OnPrevCalibrLoadBtn(TObject *Sender);
   void __fastcall OnLoadCalibrTableClear(TObject *Sender);
   void __fastcall OnLoadCalibrCalc(TObject *Sender);
   void __fastcall OnPrintLoadCalibrProtA(TObject *Sender);
   void __fastcall OnNextCalibrTBtn(TObject *Sender);
   void __fastcall OnPrevCalibrTBtn(TObject *Sender);
   void __fastcall OnTCalibrTableClear(TObject *Sender);
   void __fastcall OnTCalibrCalc(TObject *Sender);
   void __fastcall OnPrintTCalibrProtA(TObject *Sender);
   void __fastcall OnNextCalibrRBtn(TObject *Sender);
   void __fastcall OnPrevCalibrRBtn(TObject *Sender);
   void __fastcall OnRCalibrTableClear(TObject *Sender);
   void __fastcall OnRCalibrCalc(TObject *Sender);
   void __fastcall OnPrintRCalibrProtA(TObject *Sender);
   void __fastcall OnNextSertLoadBtn(TObject *Sender);
   void __fastcall OnPrevSertLoadBtn(TObject *Sender);
   void __fastcall OnLoadSertTableClear(TObject *Sender);
   void __fastcall OnLoadSertCalc(TObject *Sender);
   void __fastcall OnLoadSertToPLC(TObject *Sender);
   void __fastcall OnPrintLoadSertProtA(TObject *Sender);
   void __fastcall OnLoadSpeedCoefToPLC(TObject *Sender);
   void __fastcall OnLSertCoefReset(TObject *Sender);
   void __fastcall OnSGSelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect);
   void __fastcall OnTLimitsCalc(TObject *Sender);
   void __fastcall OnTLimitsLoadToPLC(TObject *Sender);
   void __fastcall OnUploadLSertFmPLC(TObject *Sender);
   void __fastcall OnRShiftLoadToPLC(TObject *Sender);
   void __fastcall OnPrintProtocol(TObject *Sender);
   void __fastcall OnPrinterFontSelect(TObject *Sender);
   void __fastcall onOPCControlStartExec(TObject *Sender);
   void __fastcall acSettingsManagmentExecute(TObject *Sender);
   void __fastcall leSetLoad1KeyPress(TObject *Sender, wchar_t &Key);
   void __fastcall btEmSettingsClick(TObject *Sender);
   void __fastcall leEmMinLoad_1RKeyPress(TObject *Sender, wchar_t &Key);
   void __fastcall cbControlLateralAClick(TObject *Sender);
   void __fastcall leSetDrumSpeedKeyPress(TObject *Sender, wchar_t &Key);
   void __fastcall btnResetResPosAClick(TObject *Sender);
   void __fastcall OnReadCycleTimer(TObject *Sender);

private: // User declarations
   int tsCurrentStatusH, tsCurrentStatusW;
   int pParam1Height, pParam1Width;
   int pParam2Height, pParam2Width;
   int tsManualHeight, tsManualWidth;
   int tsTimeProgHeight, tsTimeProgWidth;
   int tsSProgHeight, tsSProgWidth;
   int tsNewProtHeight, tsNewProtWidth;
   int tsProtocolAHeight, tsProtocolAWidth;
   int tsProtocolBHeight, tsProtocolBWidth;
   int tsSpeedCalibrH, tsSpeedCalibrW;
   int tsLoadCalibrAH, tsLoadCalibrAW;
   int tsTCalibrAH, tsTCalibrAW;
   int tsRCalibrAH, tsRCalibrAW;
   int tsLoadSertAH, tsLoadSertAW;
   bool closing;

   std::unique_ptr<cSQL>DB;

   Tyre InpTyre;
   sert::VSert VS;
   TimeProgramm TimePrg;
   PathProgramm PathPrg;

   UIPosData mPosA;
   UICommonData mData;
//   timer::Timer mTimerAction;
   int mCount = 0;
   std::recursive_mutex mCPUMutex;

   void SetCommonParam(void);
   void ShowCommonParam(void);
   void ShowStatus(bool save = true);
   void DesignSProgTable(void);
   void DesignTProgTable(void);
   void DesignCmmnParPanel(void);
   void DesignManualPanel(void);
   void DesignNewProtPanel(void);
   void DesignProtAPanel(void);
   void DesignLoadCalibrAPanel(void);
   void DesignRCalibrAPanel(void);
   void DesignTCalibrAPanel(void);
   void DesignSpdCalibrPanel(void);
   void DesignLoadSertAPanel(void);
   void DesignTSertPanel(void);
   void DesignRSertPanel(void);
   void ShowTProg(void);
   void ShowSProg(void);
   void ReadProtDataFmScrn(void);
   void ShowProtDataOnScrn(void);
   void ShowProtAData(void);
   void ReadLSertTable(sert::LCalibr *, TStringGrid *);
   void CheckStend(void);
   void GetSettings(void);
   void SetIndication(TEdit *Indicator, bool state);
   void SetCurrProgA(std::string const& name);
   std::string GetCurrProgA(void);
   void SetCurrProgB(const std::string &name);
   std::string GetCurrProgB(void);
   void UpdateProgData(void);
   bool CheckLoad(double load, float& value, TColor& color);
   bool CheckSpeed(double Speed, float& value, TColor& color);
   bool CheckLoad(double load);
   bool CheckSpeed(double Speed);
   bool CheckTime(int Time);
   bool CheckDistance(double Dist);
   void ClearStepVals1(void);
   bool CheckProgLoad(TStringGrid *sg, int col, double min_val);


public: // User declarations
   __fastcall TmfRB(TComponent* Owner);
   __fastcall ~TmfRB();
};

// ---------------------------------------------------------------------------
extern PACKAGE TmfRB *mfRB;
// ---------------------------------------------------------------------------
#endif
