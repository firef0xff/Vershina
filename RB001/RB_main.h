//---------------------------------------------------------------------------

#ifndef RB_mainH
#define RB_mainH
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
class TmfRB : public TForm
{
__published:	// IDE-managed Components
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
    TGroupBox *gbPosition2ControlBox;
    TGroupBox *gbSensors2;
    TButton *btnGeneralStop;
    TAction *acOPCControlStart;
    TAction *acOPCControlStop;
    TPanel *pParam1;
    TPanel *pParam2;
    TTabSheet *tsManual;
    TSplitter *Splitter1;
    TStaticText *stP1TL0C1;
    TStaticText *stP1TL0C2;
    TStaticText *stP1CurDate;
    TStaticText *stP1TTyreType;
    TStaticText *stP1L1TyreTypeA;
    TStaticText *stP1L1TyreTypeB;
    TStaticText *stP1TProgName;
    TStaticText *stP1L2ProgNameA;
    TStaticText *stP1L2ProgNameB;
    TPanel *pP1PT2;
    TPanel *pP1PL1Ttl;
    TPanel *pP1L1C1Ttl;
    TPanel *pP1L1C2Ttl;
    TPanel *pP1L1C3Ttl;
    TPanel *pP1L1C4Ttl;
    TPanel *pP1L1C5Ttl;
    TPanel *pP1L1C6Ttl;
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
    TStaticText *stP1CParL1C4;
    TStaticText *stP1CParL1C5;
    TStaticText *stP1CParL1C6;
    TStaticText *stP1CParL2C1;
    TStaticText *stP1CParL2C2;
    TStaticText *stP1CParL2C3;
    TStaticText *stP1CParL2C4;
    TStaticText *stP1CParL2C5;
    TStaticText *stP1CParL2C6;
    TStaticText *stP1CParL3C1;
    TStaticText *stP1CParL3C2;
    TStaticText *stP1CParL3C3;
    TStaticText *stP1CParL3C4;
    TStaticText *stP1CParL3C5;
    TStaticText *stP1CParL3C6;
    TStaticText *stP1CParL4C6;
    TStaticText *stP1CParL4C5;
    TStaticText *stP1CParL4C4;
    TStaticText *stP1CParL4C3;
    TStaticText *stP1CParL4C2;
    TStaticText *stP1CParL4C1;
    TStaticText *stP1CParL5C1;
    TStaticText *stP1CParL5C2;
    TStaticText *stP1CParL5C3;
    TStaticText *stP1CParL5C4;
    TStaticText *stP1CParL5C5;
    TStaticText *stP1CParL5C6;
    TStaticText *stP1CParL6C1;
    TStaticText *stP1CParL6C2;
    TStaticText *stP1CParL6C3;
    TStaticText *stP1CParL6C4;
    TStaticText *stP1CParL6C5;
    TStaticText *stP1CParL6C6;
    TStaticText *stP1CParL7C1;
    TStaticText *stP1CParL7C2;
    TStaticText *stP1CParL7C3;
    TStaticText *stP1CParL7C4;
    TStaticText *stP1CParL7C5;
    TStaticText *stP1CParL7C6;
    TStaticText *stP1CParL8C1;
    TStaticText *stP1CParL8C2;
    TStaticText *stP1CParL8C3;
    TStaticText *stP1CParL8C4;
    TStaticText *stP1CParL8C5;
    TStaticText *stP1CParL8C6;
    TPanel *pP2TtlL0C1;
    TPanel *pP2TtlL0C2;
    TPanel *pP2TtlL1C1;
    TPanel *pP2TtlL1C2;
    TPanel *pP2TtlL1C4;
    TPanel *pP2TtlL1C3;
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
    TStaticText *stP2CParL1C3;
    TStaticText *stP2CParL2C3;
    TStaticText *stP2CParL3C3;
    TStaticText *stP2CParL4C3;
    TStaticText *stP2CParL5C3;
    TStaticText *stP2CParL6C3;
    TStaticText *stP2CParL7C3;
    TStaticText *stP2CParL1C4;
    TStaticText *stP2CParL2C4;
    TStaticText *stP2CParL3C4;
    TStaticText *stP2CParL4C4;
    TStaticText *stP2CParL5C4;
    TStaticText *stP2CParL6C4;
    TStaticText *stP2CParL7C4;
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
    TGroupBox *gbCarriage2;
    TSpeedButton *sbCarriage2Off;
    TLabel *lCarriage2Off;
    TLabel *l2Load80;
    TLabel *l2Load70;
    TLabel *l2Load60;
    TLabel *l2Load50;
    TLabel *l2Load40;
    TLabel *l2Load30;
    TLabel *l2Load20;
    TLabel *l2Load10;
    TLabel *l2Load00;
    TPanel *pCarr2Ttl;
    TButton *btnCarriage2From;
    TButton *btnCarriage2To;
    TButton *btnCarriage2Stop;
    TPanel *pCarr2Load;
    TLabeledEdit *leCurrentLoad2;
    TLabeledEdit *leSetLoad2;
    TTrackBar *tbCurrentLoad2;
    TLabeledEdit *leCurrentT2;
    TLabeledEdit *leCurrentR2;
    TAction *acDrumOn;
    TAction *acDrumOff;
    TAction *acCarriage1From;
    TAction *acCarriage1Stop;
    TAction *acCarriage1To;
    TAction *acCarriage2To;
    TAction *acCarriage2Stop;
    TAction *acCarriage2From;
    TAction *acGeneralStop;
    TPageControl *pcProtTitle;
    TTabSheet *tsProtocolA;
    TTabSheet *tsProtocolB;
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
    TButton *btnLoadTProgToPosB;
    TButton *btnCheckTProg;
    TFileOpen *acTProgFileOpen;
    TFileSaveAs *acTProgFileSaveAs;
    TSpeedButton *sbCarr1Fm;
    TSpeedButton *sbCarr1To;
    TSpeedButton *sbCarr2To;
    TSpeedButton *sbCarr2Fm;
    TSpeedButton *sbDrumOn;
    TButton *btnNewTProg;
    TTabSheet *tsSProg;
    TTimer *tReadCycleTimer;
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
    TButton *btnLoadSProgToPosB;
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
    TButton *btnLoadProtToPosB;
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
    TPanel *pCurrentProtBTtl;
    TButton *btnLoadTestResPosA;
    TButton *btnSaveTestResPosAToFile;
    TButton *btnPrintTestResPosA;
    TLabeledEdit *leTyreModelB;
    TLabeledEdit *leManufacturerB;
    TLabeledEdit *lePerfSpecNoB;
    TLabeledEdit *leTyreSyzeB;
    TLabeledEdit *leTestCustomerB;
    TLabeledEdit *leTestProcB;
    TLabeledEdit *leDrumD_B;
    TLabeledEdit *leManDateB;
    TLabeledEdit *leSerialNoB;
    TLabeledEdit *leOrderNoB;
    TLabeledEdit *leFormNoB;
    TPanel *pTyreParamBTtl;
    TLabeledEdit *leLoadIndB;
    TLabeledEdit *leSpeedIndB;
    TLabeledEdit *leOuterD_B;
    TLabeledEdit *leMaxLoadB;
    TLabeledEdit *leMaxSpeedB;
    TLabeledEdit *leQMaxPressureB;
    TLabeledEdit *leStaticR_B;
    TLabeledEdit *leTyreWideB;
    TLabeledEdit *leRimB;
    TPanel *pTestResTtlB;
    TLabeledEdit *leTyrePressureB;
    TLabeledEdit *leTestModeB;
    TLabeledEdit *leStepQtyB;
    TLabeledEdit *leTestDurationB;
    TLabeledEdit *lePollsQtyB;
    TStringGrid *sgTestResultB;
    TButton *btnLoadTestResPosB;
    TButton *btnSaveTestResPosBToFile;
    TButton *btnPrintTestResPosB;
    TFileSaveAs *acPrintProtPosAToFile;
    TFileSaveAs *acPrintProtPosBToFile;
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
    TTabSheet *tsLoadCalibrB;
    TPanel *pLoadCalibrATtl;
    TStringGrid *sgLoadCalibrB;
    TButton *btnPrevCalibrLoadB;
    TLabeledEdit *leCurrentLoadSetB;
    TLabeledEdit *leReadLoadB;
    TLabeledEdit *leMeasuredLoadB;
    TButton *btnNextCalibrLoadB;
    TButton *btnClearLoadCalibreTableB;
    TButton *btnLoadCalibrCalcB;
    TButton *btnLoadCalibrTableBPrint;
    TButton *btnPumpOnB;
    TButton *btnPumpOffB;
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
    TFileSaveAs *acPrintLoadCalibrProtB;
    TAction *acPumpOnA;
    TAction *acPumpOffA;
    TAction *acPumpOnB;
    TAction *acPumpOffB;
    TPageControl *pcTempCalibr;
    TTabSheet *tsTCalibrA;
    TTabSheet *tsTCalibrB;
    TPanel *pTCalibrATtl;
    TStringGrid *sgTCalibrA;
    TButton *btnPrevTCalibrA;
    TLabeledEdit *leReadTA;
    TLabeledEdit *leMeasTA;
    TButton *btnNextTCalibrA;
    TButton *btnClearTCalibrTableA;
    TButton *btnTCalibrCalcA;
    TButton *btnTCalibrTableAPrint;
    TPanel *pTCalibrBTtl;
    TStringGrid *sgTCalibrB;
    TButton *btnPrevTCalibrB;
    TLabeledEdit *leReadTB;
    TLabeledEdit *leMeasTB;
    TButton *btnNextTCalibrB;
    TButton *btnClearTCalibrTableB;
    TButton *btnTCalibrCalcB;
    TButton *btnTCalibrTableBPrint;
    TFileSaveAs *acPrintTCalibrProtA;
    TFileSaveAs *acPrintTCalibrProtB;
    TPageControl *pcRadiusCalibr;
    TTabSheet *tsRCalibrA;
    TTabSheet *tsRCalibrB;
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
    TPanel *pRCalibrBTtl;
    TStringGrid *sgRCalibrB;
    TButton *btnPrevRCalibrB;
    TLabeledEdit *leReadRB;
    TLabeledEdit *leMeasRB;
    TButton *btnNextRCalibrB;
    TButton *btnClearRCalibrTableB;
    TButton *btnRCalibrCalcB;
    TButton *btnRCalibrTableBPrint;
    TButton *btnCalibrCarr2Stop;
    TButton *btnCalibrCarr2Fm;
    TButton *btnCalibrCarr2To;
    TFileSaveAs *acPrintRCalibrProtA;
    TFileSaveAs *acPrintRCalibrProtB;
    TTabSheet *tsSert;
    TPageControl *pcSert;
    TTabSheet *tsDrumSpeedSert;
    TTabSheet *tsTemSert;
    TTabSheet *tsLoadSert;
    TPageControl *pcLoadSert;
    TTabSheet *tsLoadSertA;
    TTabSheet *tsLoadSertB;
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
    TPanel *pLoadSertBTtl;
    TStringGrid *sgLoadSertB;
    TButton *btnPrevSertLoadB;
    TLabeledEdit *leCurrentLoadSertSetB;
    TLabeledEdit *leReadLoadSertB;
    TLabeledEdit *leMeasLoadSertB;
    TButton *btnNextSertLoadB;
    TButton *btnLoadSertClearTableB;
    TButton *btnLoadSertCalcB;
    TButton *btnLoadSertPrintProtB;
    TButton *btnLoadSertBToPLC;
    TButton *btnSertPumpOnB;
    TButton *btnSertPumpOffB;
    TFileSaveAs *acLoadSertPrintProtA;
    TFileSaveAs *acLoadSertPrintProtB;
    TPanel *pDrumSpeedSertTtl;
    TLabeledEdit *leSetSpeedCoef;
    TLabeledEdit *leMeasSpeedCoef;
    TButton *btnLoadSpeedCoefToPLC;
    TButton *btnResetCalibrCoeffA;
    TButton *btnResetCalibrCoeffB;
    TButton *btnTLimitsCalcA;
    TPanel *pTSertTtl;
    TGroupBox *gbTSertA;
    TGroupBox *gbTSertB;
    TEdit *edCalcLowLimitA;
    TLabel *lblCalcLimitsA;
    TEdit *edCalcUpLimitA;
    TLabel *lblLowA;
    TLabel *lblHighA;
    TLabel *lblTLoadedLimitsA;
    TEdit *edLoadedLowLimitA;
    TEdit *edLoadedUpLimitA;
    TButton *btnLoadTLimitsA;
    TButton *btnLoadTLimitsB;
    TLabel *lblCalcLimitsB;
    TLabel *lblTLoadedLimitsB;
    TEdit *edCalcLowLimitB;
    TEdit *edLoadedLowLimitB;
    TEdit *edLoadedUpLimitB;
    TEdit *edCalcUpLimitB;
    TLabel *lblHighB;
    TLabel *lblLowB;
    TButton *btnTLimitsCalcB;
    TButton *btnUploadSertBFmPLC;
    TButton *btnUploadSertAFmPLC;
    TTabSheet *tsRadSert;
    TLabeledEdit *leRShiftA;
    TLabeledEdit *leRShiftB;
    TButton *btnRShiftALoadToPLC;
    TButton *btnRShiftBLoadToPLC;
    TPanel *pRSertTtl;
    TFilePrintSetup *acPrintSetup;
    TFontDialog *PrinterFontDialog;
    TAction *Action1;
	TAction *acCD_9904Settings;
	TGroupBox *gbOil;
	TADOConnection *ADC;
	TAction *acSettingsManagment;
	TAction *_acTProgFileSaveAs;
	TAction *_acSProgFileSaveAs;
	TAction *_acProtTitleFileSaveAs;
	TAction *_acPrintProtPosAToFile;
	TAction *_acPrintProtPosBToFile;
	TAction *_acPrintLoadCalibrProtA;
	TAction *_acPrintLoadCalibrProtB;
	TAction *_acLoadSertPrintProtA;
	TAction *_acLoadSertPrintProtB;
	TAction *_acPrintRCalibrProtA;
	TAction *_acPrintRCalibrProtB;
	TAction *_acPrintTCalibrProtA;
	TAction *_acPrintTCalibrProtB;
	TAction *_acPrintSpdCalibrProt;
	TEdit *IndBlowout2;
	TEdit *IndGuardrail2;
	TEdit *IndDestroyLateral2;
	TEdit *IndDestroyRunning2;
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
	TLabeledEdit *leEmMaxLoad_2;
	TLabeledEdit *leEmMaxLoad_1;
	TLabeledEdit *leEmMinLoad_1;
	TLabeledEdit *leEmMinLoad_2;
	TLabeledEdit *leEmMaxSpeedR;
	TLabeledEdit *leEmMaxLoad_2R;
	TLabeledEdit *leEmMaxLoad_1R;
	TLabeledEdit *leEmMinLoad_1R;
	TLabeledEdit *leEmMinLoad_2R;
	TButton *btEmSettings;
	TSpeedButton *sbManualB;
	TSpeedButton *sbAutomatB;
	TGroupBox *rgPos2StartStop;
	TGroupBox *rgPos2Mode;
	TSpeedButton *sbStartB;
	TSpeedButton *sbStopB;
	TLabel *leBManual;
	TLabel *leBAutomat;
	TLabel *leStopB;
	TLabel *leStartB;
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
	TCheckBox *cbControlLateralB;
	TLabeledEdit *leEmMinSpeed;
	TLabeledEdit *leEmMinSpeedR;
	TLabeledEdit *leSetSpeedCoefReal;
	TLabeledEdit *leMeasSpeedCoefReal;
	TButton *btnResetResPosA;
	TButton *btnResetResPosB;
	TLabel *lLoad90;
	TLabel *lLoad100;
	TLabel *lLoad110;
	TLabel *l2Load110;
	TLabel *l2Load100;
	TLabel *l2Load90;
	TLabeledEdit *leEmMinTemp_1;
	TLabeledEdit *leEmMaxTemp_1;
	TLabeledEdit *leEmMaxTemp_2;
	TLabeledEdit *leEmMinTemp_2;
	TLabeledEdit *leEmMinTemp_1R;
	TLabeledEdit *leEmMinTemp_2R;
	TLabeledEdit *leEmMaxTemp_2R;
	TLabeledEdit *leEmMaxTemp_1R;
    void __fastcall OnCommonParamReadExec(TObject *Sender);
	void __fastcall OPCControlStartExec(void);
	void __fastcall OnOPCControlStopExec(TObject *Sender);
    void __fastcall OnReadCycleTimer(TObject *Sender);
    void __fastcall OnRGPos1ModeClick(TObject *Sender);
    void __fastcall OnRGPos1StartStopClick(TObject *Sender);
    void __fastcall OnDrumOn(TObject *Sender);
    void __fastcall OnDrumOff(TObject *Sender);
    void __fastcall OnCarriage1To(TObject *Sender);
    void __fastcall OnCarriage1From(TObject *Sender);
    void __fastcall OnCarriage1Stop(TObject *Sender);
    void __fastcall OnCarriage2To(TObject *Sender);
    void __fastcall OnCarriage2Stop(TObject *Sender);
    void __fastcall OnCarriage2From(TObject *Sender);
    void __fastcall OnRGPos2ModeClick(TObject *Sender);
    void __fastcall OnRGPos2StartStopClick(TObject *Sender);
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
    void __fastcall OnLoadTProgToPosB(TObject *Sender);
    void __fastcall OnStringGridExit(TObject *Sender);
    void __fastcall OnGetEditMask(TObject *Sender, int ACol, int ARow, AnsiString &Value);
    void __fastcall OnSGKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall OnTProgCheck(TObject *Sender);
    void __fastcall OnSGKeyPress(TObject *Sender, char &Key);
    void __fastcall OnSGSEnter(TObject *Sender);
    void __fastcall OnLEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall OnNewTProg(TObject *Sender);
    void __fastcall OnSGTEnter(TObject *Sender);
    void __fastcall OnSProgCheck(TObject *Sender);
    void __fastcall OnNewSProg(TObject *Sender);
    void __fastcall OnLoadSProgToPosB(TObject *Sender);
    void __fastcall OnLoadProtToPosA(TObject *Sender);
    void __fastcall OnLoadTestResFmPosA(TObject *Sender);
    void __fastcall OnClearProt(TObject *Sender);
    void __fastcall OnProtTtlFileSaveAs(TObject *Sender);
    void __fastcall OnProtTtlFileOpen(TObject *Sender);
    void __fastcall OnLoadProtToPosB(TObject *Sender);
    void __fastcall OnLoadTestResFmPosB(TObject *Sender);
    void __fastcall OnCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall OnPrintProtPosAToFile(TObject *Sender);
    void __fastcall OnPrintProtPosBToFile(TObject *Sender);
    void __fastcall OnVCalibrClear(TObject *Sender);
    void __fastcall OnVCalibrCalc(TObject *Sender);
    void __fastcall OnNextCalibrVBtn(TObject *Sender);
    void __fastcall OnPrevCalibrVBtn(TObject *Sender);
    void __fastcall OnCalibrDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
    void __fastcall OnPrintSpdCalibrProtocol(TObject *Sender);
    void __fastcall OnPump1On(TObject *Sender);
    void __fastcall OnPump1Off(TObject *Sender);
    void __fastcall OnPump2On(TObject *Sender);
    void __fastcall OnPump2Off(TObject *Sender);
    void __fastcall OnNextCalibrLoadBtn(TObject *Sender);
    void __fastcall OnPrevCalibrLoadBtn(TObject *Sender);
    void __fastcall OnLoadCalibrTableClear(TObject *Sender);
    void __fastcall OnLoadCalibrCalc(TObject *Sender);
    void __fastcall OnPrintLoadCalibrProtA(TObject *Sender);
    void __fastcall OnPrintLoadCalibrProtB(TObject *Sender);
    void __fastcall OnNextCalibrTBtn(TObject *Sender);
    void __fastcall OnPrevCalibrTBtn(TObject *Sender);
    void __fastcall OnTCalibrTableClear(TObject *Sender);
    void __fastcall OnTCalibrCalc(TObject *Sender);
    void __fastcall OnPrintTCalibrProtA(TObject *Sender);
    void __fastcall OnPrintTCalibrProtB(TObject *Sender);
    void __fastcall OnNextCalibrRBtn(TObject *Sender);
    void __fastcall OnPrevCalibrRBtn(TObject *Sender);
    void __fastcall OnRCalibrTableClear(TObject *Sender);
    void __fastcall OnRCalibrCalc(TObject *Sender);
    void __fastcall OnPrintRCalibrProtA(TObject *Sender);
    void __fastcall OnPrintRCalibrProtB(TObject *Sender);
    void __fastcall OnNextSertLoadBtn(TObject *Sender);
    void __fastcall OnPrevSertLoadBtn(TObject *Sender);
    void __fastcall OnLoadSertTableClear(TObject *Sender);
    void __fastcall OnLoadSertCalc(TObject *Sender);
    void __fastcall OnLoadSertToPLC(TObject *Sender);
    void __fastcall OnPrintLoadSertProtA(TObject *Sender);
    void __fastcall OnPrintLoadSertProtB(TObject *Sender);
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
	void __fastcall acCD_9904SettingsExecute(TObject *Sender);
	void __fastcall onOPCControlStartExec(TObject *Sender);
	void __fastcall acSettingsManagmentExecute(TObject *Sender);
	void __fastcall leSetLoad1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall leSetLoad2KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btEmSettingsClick(TObject *Sender);
	void __fastcall leEmMinLoad_1RKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbControlLateralBClick(TObject *Sender);
	void __fastcall cbControlLateralAClick(TObject *Sender);
	void __fastcall leSetDrumSpeedKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btnResetResPosBClick(TObject *Sender);
	void __fastcall btnResetResPosAClick(TObject *Sender);
private:	// User declarations
    int tsCurrentStatusH, tsCurrentStatusW;
    int pParam1Height,    pParam1Width;
    int pParam2Height,    pParam2Width;
    int tsManualHeight,   tsManualWidth;
    int tsTimeProgHeight, tsTimeProgWidth;
    int tsSProgHeight,    tsSProgWidth;
    int tsNewProtHeight,  tsNewProtWidth;
    int tsProtocolAHeight,tsProtocolAWidth;
    int tsProtocolBHeight,tsProtocolBWidth;
    int tsSpeedCalibrH,   tsSpeedCalibrW;
    int tsLoadCalibrAH,   tsLoadCalibrAW;
    int tsTCalibrAH,      tsTCalibrAW;
    int tsRCalibrAH,      tsRCalibrAW;
	int tsLoadSertAH,     tsLoadSertAW;
	bool closing;//индикатор закрытия программы
	cSQL *DB;

    void __fastcall SetCommonParam(void);    // настройка таблицы общих параметров
    void __fastcall ShowCommonParam(void);   // отображение общих параметров
	void __fastcall OnLogPrint(TMessage&);   // обработчик сообщений печати в окне протокола
	void __fastcall OnDataShow(TMessage&);   // обработчик сообщений отображения данных
	void __fastcall OnOPCCmd(TMessage&);     // обработчик сообщений-команд для запросов к OPC-серверу
    void __fastcall ShowStatus(bool save=true);        // отображение состояния на панелях
	void __fastcall DesignSProgTable(void);  // создание таблицы для ввода программы испытаний по пути
    void __fastcall DesignTProgTable(void);  // создание таблицы для ввода программы испытаний по времени
	void __fastcall DesignCmmnParPanel(void);// расположение компонент на панели общих параметров
    void __fastcall DesignManualPanel(void); // расположение компонент на панели ручного управления
    void __fastcall DesignNewProtPanel(void);// расположение компонент на панели нового протокола
    void __fastcall DesignProtAPanel(void);  // расположение компонент на панели протокола поз. А
    void __fastcall DesignProtBPanel(void);  // расположение компонент на панели протокола поз. Б
    void __fastcall DesignLoadCalibrAPanel(void);  // расположение компонент на панели аттестации нагрузки поз. А
    void __fastcall DesignLoadCalibrBPanel(void);  // расположение компонент на панели аттестации нагрузки поз. Б
    void __fastcall DesignRCalibrAPanel(void);// расположение компонент на панели аттестации радиуса поз. А
    void __fastcall DesignRCalibrBPanel(void);// расположение компонент на панели аттестации радиуса поз. Б
    void __fastcall DesignTCalibrAPanel(void);// расположение компонент на панели аттестации температуры поз. А
    void __fastcall DesignTCalibrBPanel(void);// расположение компонент на панели аттестации температуры поз. Б
    void __fastcall DesignSpdCalibrPanel(void);// расположение компонент на панели аттестации барабана
    void __fastcall DesignLoadSertAPanel(void);// расположение компонент на панели калибровки нагрузки поз. А
    void __fastcall DesignLoadSertBPanel(void);// расположение компонент на панели калибровки нагрузки поз. Б
    void __fastcall DesignTSertPanel(void);  // расположение компонент на панели калибровки температуры
    void __fastcall DesignRSertPanel(void);  // расположение компонент на панели калибровки датчиков радиуса
    void __fastcall ShowTProg(void);         // отобразить программу по времени на экране
	void __fastcall ShowSProg(void);         // отобразить программу по пути на экране
    void __fastcall ReadProtDataFmScrn(void);// прочитать данные протокола из экрана в InpTyre
	void __fastcall ShowProtDataOnScrn(void);// отобразить данные протокола из InpTyre на экране
    void __fastcall ShowProtAData(void);     // отобразить шапку протокола в панели поз. А
    void __fastcall ShowProtBData(void);     // отобразить шапку протокола в панели поз. Б
    void __fastcall ReadLSertTable(LCalibr *,TStringGrid *);// считывание значений из таблицы в массив
	void			CheckStend(void);//проверка соединения со стендом и попытка подключения
	void			GetSettings(void);//чтение настроек программы
	void			SetIndication(TEdit *Indicator,bool state);//управление инидикацией программы
	void			SetCurrProgA(String name);
	String			GetCurrProgA(void);
	void			SetCurrProgB(String name);
	String			GetCurrProgB(void);
	void			UpdateProgData(void);
	bool			CheckLoad(double load);//проверка значения нагрузки
	bool            CheckSpeed(double Speed);//проверка значения скорости
	bool			CheckTime(int Time);//проверка корректности ввода времени
	bool			CheckDistance(double Dist);//проверка корректности ввода пути
	void			ClearStepVals1(void);  //чистка значений цыкла
	void			ClearStepVals2(void);
private:
	bool 	CheckProgLoad(TStringGrid *sg,int col,double min_val);

public:		// User declarations
	__fastcall TmfRB(TComponent* Owner);     // конструктор
    __fastcall ~TmfRB();    // деструктор
// карта сообщений Windows
	BEGIN_MESSAGE_MAP
//	  MESSAGE_HANDLER(WM_POWERBROADCAST,TWMPower,OnWakeup)  // сообщения питания
	  MESSAGE_HANDLER(WM_LogPrint,TMessage,OnLogPrint)      // сообщение печати в окне протокола
	  MESSAGE_HANDLER(WM_DataShow,TMessage,OnDataShow)      // сообщение отобразить данные
	  MESSAGE_HANDLER(WM_OPCCmd,TMessage,OnOPCCmd)          // сообщение-команда запроса к OPC-серверу
//	  MESSAGE_HANDLER(WM_StatusShow,TMessage,OnStatus)      // сообщение печати в строке состояния
//	  MESSAGE_HANDLER(WM_Cycle,TMessage,OnCycle)            // сообщение CPU об очередном цикле
	END_MESSAGE_MAP(TComponent)
};

//---------------------------------------------------------------------------
extern PACKAGE TmfRB *mfRB;
//---------------------------------------------------------------------------
#endif
