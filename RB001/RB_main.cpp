//---------------------------------------------------------------------------

#include <Printers.hpp>
#include <vcl.h>
#pragma hdrstop
#define MFHEIGHT  750
#define MFWIDTH  1024
#include "def.h"
#include "opc.h"
#include "opc_i.c"
#include "RBCommon.h"
#include "Sertification.h"
#include "RB_main.h"
#include "opcrw.h"
#include "OPCControl.h"
#include "TyreProt.h"
#include "Head_band.h"
#include "Login.h"
#include "AppManagnent.h"
#include "Threads.h"
#include "ABOUT.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmfRB      *mfRB;
//OPCRW      *pOPC=0;              // указатель на класс OPCRW
boost::shared_ptr<Tyre>  InpTyre(new Tyre());  // покрышка для ввода и редактирования протокола
boost::shared_ptr<Tyre>  	TyreA  (new Tyre());  // покрышка в поз. А
boost::shared_ptr<Tyre>  	TyreB (new Tyre());  // покрышка в поз. Б
boost::shared_ptr<LSert> 	LdSA  (new LSert()); // Сертификация нагрузки поз А
boost::shared_ptr<LSert> 	LdSB (new LSert()); // Сертификация нагрузки поз Б
boost::shared_ptr<TSert> 	TSA  (new TSert()); // Сертификация температуры поз А
boost::shared_ptr<TSert> 	TSB  (new TSert()); // Сертификация температуры поз Б
boost::shared_ptr<RSert> 	RSA  (new RSert()); // Сертификация радиуса поз А
boost::shared_ptr<RSert> 	RSB  (new RSert()); // Сертификация радиуса поз Б
boost::shared_ptr<VSert>    VS   (new VSert()); // сертификация скорости барабана
boost::shared_ptr<LCalibr>  LdCA (new LCalibr()); // калибровка тензодатчика поз. А
boost::shared_ptr<LCalibr>  LdCB (new LCalibr()); // калибровка тензодатчика поз. Б
TPrinter   *pProtPrt = Printer(); // указатель на принтер
//---------------------------------------------------------------------------
__fastcall TmfRB::TmfRB(TComponent* Owner)
    : TForm(Owner),closing(false)
{
	//соединение с базой программы
	String con1="Provider=Microsoft.ACE.OLEDB.12.0;Data Source="
	,con2=";Persist Security Info=False";

	ADC->ConnectionString=con1+ExtractFilePath(Application->ExeName)+"ProgData.mdb"+con2;
	DB=new cSQL(ADC);
	TLogInwnd *wnd=new TLogInwnd(this,DB);
	if (wnd->ShowModal()==mrOk)
	{
		THeadband *hbnd=new THeadband(this);
		hbnd->Show();

		//ограничения интерфейса
		if (!wnd->get_Adjust())
		{
			tsCalibration->Hide();
			tsCalibration->PageControl=0;

			tsSert->Hide();
			tsSert->PageControl=0;

			acLoadSertPrintProtA->Visible=false;
			acLoadSertPrintProtB->Visible=false;

			acPrintLoadCalibrProtB->Visible=false;
			acPrintLoadCalibrProtA->Visible=false;

			acCD_9904Settings->Visible=false;
		}
		if (!wnd->get_Work())
		{
			tsCurrentStatus->Hide();
			tsCurrentStatus->PageControl=0;

			tsManual->Hide();
			tsManual->PageControl=0;

			tsTestProgramSetting->Hide();
			tsTestProgramSetting->PageControl=0;

			tsProtocol->Hide();
			tsProtocol->PageControl=0;

			tsEmSettings->Hide();
			tsEmSettings->PageControl=0;

			acPrintSetup->Visible=false;
			Action1->Visible=false;
			acProtTitleFileSaveAs->Visible=false;
			_acProtTitleFileSaveAs->Visible=false;
			acProtTitleFileOpen->Visible=false;
			acSProgFileSaveAs->Visible=false;
			_acSProgFileSaveAs->Visible=false;
			acSProgFileOpen->Visible=false;
			acTProgFileSaveAs->Visible=false;
			_acTProgFileSaveAs->Visible=false;
			acTProgFileOpen->Visible=false;

			acGeneralStop->Visible=false;
			acCarriage2From->Visible=false;
			acCarriage2Stop->Visible=false;
			acCarriage2To->Visible=false;
			acDrumOff->Visible=false;
			acDrumOn->Visible=false;
			acCarriage1To->Visible=false;
			acCarriage1Stop->Visible=false;
			acCarriage1From->Visible=false;
			acPumpOffB->Visible=false;
			acPumpOnB->Visible=false;
			acPumpOffA->Visible=false;
			acPumpOnA->Visible=false;

			acOPCControlStart->Visible=false;
			acOPCControlStop->Visible=false;
			CommonParamRead->Visible=false;
			acLoadTestResFmPosA->Visible=false;
			acCD_9904Settings->Visible=false;

			acPrintSpdCalibrProt->Visible=false;
			acPrintTCalibrProtB->Visible=false;
			acPrintTCalibrProtA->Visible=false;
			acPrintRCalibrProtB->Visible=false;
			acPrintRCalibrProtA->Visible=false;

			acPrintProtPosBToFile->Visible=false;
			acPrintProtPosAToFile->Visible=false;

			_acPrintSpdCalibrProt->Visible=false;
			_acPrintTCalibrProtB->Visible=false;
			_acPrintTCalibrProtA->Visible=false;
			_acPrintRCalibrProtB->Visible=false;
			_acPrintRCalibrProtA->Visible=false;

			_acPrintProtPosBToFile->Visible=false;
			_acPrintProtPosAToFile->Visible=false;

		}
		if (!wnd->get_Managment())
		{
			acSettingsManagment->Visible=false;
		}
		Application->ProcessMessages();
		cd_9904=0;
		DecimalSeparator='.';
		MainFormHandle=mfRB->Handle;
		mfRB->Height=MFHEIGHT; mfRB->Width=MFWIDTH;
		PntInit();
		LdCA->LKQInit(Q1,A1);
		LdCB->LKQInit(Q2,A2);
		pPrt=reLog;
		reLog->Clear();
		pProtPrt->Canvas->Font->Name="Lucida Console";
		pProtPrt->Canvas->Font->Size=10;
		LogPrint("Шрифт по умолчанию на принтер: \""+pProtPrt->Canvas->Font->Name+"\"",clMoneyGreen);
		//  pProtPrt->Canvas->Font->Pitch=fpFixed;

		//  *fakt_time_1=100000000; *fakt_time_2=10500000;
		//  *fakt_distance_1=102.5; *fakt_distance_2=82.4;
		//  *set_speed_1=53.2;      *set_speed_2=55.2;
		//  *fakt_speed=54.5;
		//  *next_speed1=60.2;      *next_speed2=60.2;
		//  *set_loading_1=21.0;    *set_loading_2=22.0;
		//  *fakt_loading_1=21.2;   *fakt_loading_2=21.8;
		//  *next_loading1=24.2;    *next_loading2=26.2;
		//  *fakt_temper_1=80.5;    *fakt_temper_2=85.5;
		//  *fakt_radius_1=300.0;   *fakt_radius_2=310.0;
		//  *step_change_1=100;     *step_change_2=103;
		//  *next_step_change1=101; *next_step_change2=104;
		//  *next_step_time1=99;    *next_step_time2=95;
		//  *next_step_distance1=10;*next_step_distance2=8.9;

		SetCommonParam();
		ShowCommonParam();
		pcRB->ActivePage=tsCurrentStatus;
		tReadCycleTimer->Enabled=false;
		tReadCycleTimer->Interval=1000;
		sbRB->Panels->Items[0]->Text="Соединения со стендом нет";
		sbRB->Panels->Items[3]->Text=Now().DateTimeString();
		LogPrintF(LogFName(),"Старт программы!",clAqua);
		OnMainFormCreate(this);
		cd_9904 =new CD_9904_interface(this);   //инициация  датчика
	   	CheckStend();//проверка соединения и попытка восстановить соединение
		GetSettings();//чтение настроек сохранения
		//чтение названия последних загруженных программ
		RunProgNameA=GetCurrProgA();
		RunProgNameB=GetCurrProgB();
		if (RunProgNameA!="")
		{
			stP1L2ProgNameA->Caption=RunProgNameA;
		}
		if (RunProgNameB!="")
		{
			stP1L2ProgNameB->Caption=RunProgNameB;
		}
		hbnd->Hide();
		delete wnd;
		delete hbnd;
	}else
	{
		Visible=false;
		delete wnd;
		Application->Terminate();
	}
}
//---- End of TmfRB constructor ---------------------------------------------
__fastcall TmfRB::~TmfRB()
{
	//восстановление перед уничтожением
	tsCalibration->PageControl=pcRB;
	tsSert->PageControl=pcRB;
	tsCurrentStatus->PageControl=pcRB;
	tsManual->PageControl=pcRB;
	tsTestProgramSetting->PageControl=pcRB;
	tsProtocol->PageControl=pcRB;
	//удаление удаляемого
	if (cd_9904)
	{
		delete cd_9904 ;
	}
	if (pOPC)
	{
		delete pOPC;
	}
	if (DB)
	{
     	delete DB;
	}
}
//__fastcall TmfRB::~TmfRB(TComponent* Owner)
//{
//  delete InpTyre;
//  delete TyreA;
//  delete TyreB;
//}
//---- End of TmfRB destructor ----------------------------------------------

void __fastcall TmfRB::OnCommonParamReadExec(TObject *Sender)
{
  pOPC->ReadGr1();
  pOPC->ReadGr2();
  ShowStatus();
  ShowCommonParam();
//  *A1[0]=10; *Q1[0]=1.25;
//  *A2[0]=10; *Q2[0]=1.125;
//  pOPC->WriteGr12();
//  pOPC->WriteGr13();
//  LogPrint("GR11, 12 write");
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::SetCommonParam(void)    // настройка таблицы общих параметров
{
  stP1L1TyreTypeA->Caption=TyreTypeA;
  stP1L1TyreTypeB->Caption=TyreTypeB;
  stP1L2ProgNameA->Caption=RunProgNameA;
  stP1L2ProgNameB->Caption=RunProgNameB;
  stP1CurDate->Caption    =Now().DateTimeString();
}
//---- End of SetCommonParam ------------------------------------------------

void __fastcall TmfRB::DesignSProgTable(void)   // создание таблицы для ввода программы испытаний по пути
{ const int Col0Width=30,Col1Width=80,Col2Width=105,Col3Width=65;
  const int pHeight=26, pH=24, Width2=50, LSp=10;
  int Left1=leSTyrePressure->EditLabel->Width+LSp,
      Left2=Left1+leSTotalStepsQty->EditLabel->Width+Width2+LSp,  Width1=Left2+Width2-Left1,
      Top1=pHeight+LSp, Top2=pHeight*2+LSp*2, Left3=Left2+Width2+leTotalTestS->EditLabel->Width+LSp;
  pSProgTtl->Left         =0;                  pSProgTtl->Top          =0;
  pSProgTtl->Width        =tsSProgWidth;       pSProgTtl->Height       =pHeight;
  leSProgName->Left       =Left1;              leSProgName->Top        =Top1;
  leSProgName->Width      =Width1;             leSProgName->Height     =pH;
  leTotalTestS->Left      =Left3;              leTotalTestS->Top       =Top1;
  leTotalTestS->Width     =Width2;             leTotalTestS->Height    =pH;
  leSTyrePressure->Left   =Left1;              leSTyrePressure->Top    =Top2;
  leSTyrePressure->Width  =Width2;             leSTyrePressure->Height =pH;
  leSTotalStepsQty->Left  =Left2;              leSTotalStepsQty->Top   =Top2;
  leSTotalStepsQty->Width =Width2;             leSTotalStepsQty->Height=pH;
  leSPollingTotalQty->Left=Left3;              leSPollingTotalQty->Top =Top2;
  leSPollingTotalQty->Width=Width2;            leSPollingTotalQty->Height=pH;
  lSProgTblNme->Top       =Top2+pH+LSp;
  sgSProgram->Top         =Top2+pH*2+LSp;
  sgSProgram->ColWidths[0]=Col0Width;          sgSProgram->ColWidths[1]=Col1Width;
  sgSProgram->ColWidths[2]=Col2Width;          sgSProgram->ColWidths[3]=Col3Width;
  sgSProgram->Left        =tsSProgWidth/20;

  int STableWidth=Col0Width+Col1Width+Col2Width+Col3Width+29;
  lSProgTblNme->Left      =(STableWidth-lSProgTblNme->Width)/2+sgSProgram->Left;
  sgSProgram->Width       =STableWidth;
  int STableHeight=tsSProgHeight-sgSProgram->Top-5;
  int RowNo=STableHeight/(sgSProgram->RowHeights[0]+1);
  STableHeight=RowNo*sgSProgram->RowHeights[0]+RowNo;
  sgSProgram->Height=STableHeight;
  sgSProgram->Cells[0][0]="№";                sgSProgram->Cells[1][0]="Нагрузка, кН";
  sgSProgram->Cells[2][0]="Скорость, км/час"; sgSProgram->Cells[3][0]="  Путь, км";
  for (int i = 0; i < MAXNUMOFSTEPS; i++) {
    if(i<9)sgSProgram->Cells[0][i+1]="  "+String(i+1)+":";
    else if(i<99)sgSProgram->Cells[0][i+1]=" "+String(i+1)+":";
    else sgSProgram->Cells[0][i+1]=String(i+1)+":";
  }
  lSPollingTblNme1->Top=lSProgTblNme->Top;
  sgSPolling->Left=sgSProgram->Left+STableWidth+40;
  sgSPolling->Top=sgSProgram->Top;
  sgSPolling->ColWidths[0]=Col0Width;
  sgSPolling->ColWidths[1]=Col3Width;
  int SPollTableWidth=Col0Width+Col3Width+27;
  lSPollingTblNme1->Left=(SPollTableWidth-lSPollingTblNme1->Width)/2+sgSPolling->Left;
  sgSPolling->Width=SPollTableWidth;
  sgSPolling->Height=STableHeight;
  sgSPolling->Cells[0][0]="№";
  sgSPolling->Cells[1][0]="  Путь, км";
  for (int i = 0; i < MAXNUMOFPOLLS; i++) {
    if(i<9)sgSPolling->Cells[0][i+1]="  "+String(i+1)+":";
    else if(i<99)sgSPolling->Cells[0][i+1]=" "+String(i+1)+":";
    else sgSPolling->Cells[0][i+1]=String(i+1)+":";
  }
  int btnLeft=sgSPolling->Left+SPollTableWidth+10;
  int btnWidth=tsSProgWidth-btnLeft-10;
  int btnHeight=50;
  btnNewSProg->Left         =btnLeft;    btnCheckSProg->Left       =btnLeft;
  btnSaveSProgToFile->Left  =btnLeft;    btnOpenSProgFmFile->Left  =btnLeft;
  btnLoadSProgToPosA->Left  =btnLeft;    btnLoadSProgToPosB->Left  =btnLeft;
  btnNewSProg->Width        =btnWidth;   btnCheckSProg->Width      =btnWidth;
  btnSaveSProgToFile->Width =btnWidth;   btnOpenSProgFmFile->Width =btnWidth;
  btnLoadSProgToPosA->Width =btnWidth;   btnLoadSProgToPosB->Width =btnWidth;
  btnNewSProg->Height       =btnHeight;  btnCheckSProg->Height     =btnHeight;
  btnSaveSProgToFile->Height=btnHeight;  btnOpenSProgFmFile->Height=btnHeight;
  btnLoadSProgToPosA->Height=btnHeight;  btnLoadSProgToPosB->Height=btnHeight;
  btnNewSProg->Top          =sgSProgram->Top;
  btnCheckSProg->Top        =btnNewSProg->Top+btnHeight+10;
  btnSaveSProgToFile->Top   =btnCheckSProg->Top+btnHeight+10;
  btnOpenSProgFmFile->Top   =btnSaveSProgToFile->Top+btnHeight+10;
  btnLoadSProgToPosA->Top   =btnOpenSProgFmFile->Top+btnHeight+10;
  btnLoadSProgToPosB->Top   =btnLoadSProgToPosA->Top+btnHeight+10;
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
  sgSProgram->Selection=myRect;
  sgSPolling->Selection=myRect;*/
  btnCheckSProg->Enabled=false;
  btnSaveSProgToFile->Enabled=false;
  btnLoadSProgToPosA->Enabled=false;
  btnLoadSProgToPosB->Enabled=false;
}
//---- End of DesignSProgTable ----------------------------------------------

void __fastcall TmfRB::DesignLoadSertAPanel(void)// расположение компонент на панели калибровки нагрузки поз. А
{

  const int C0W=30,C1W=60,C2W=70,C3W=70,C4W=80;
  int TblW=C0W+C1W+C2W+C3W+C4W+28, H1=40, LSp1=10;
  int TblH=tsLoadCalibrAH-H1, CellH=max(ceil(double(TblH/(LDCQTY+1)))-1, 16.0)/*, Cell0H=40;TblH-(LDCQTY+1)*CellH*/;//-LDCQTY;
  pLoadSertATtl->Height=H1;
  sgLoadSertA->ColWidths[0]=C0W;     sgLoadSertA->ColWidths[1]=C1W;
  sgLoadSertA->ColWidths[2]=C2W;     sgLoadSertA->ColWidths[3]=C3W;
  sgLoadSertA->ColWidths[4]=C4W;
  sgLoadSertA->Width=TblW;
  sgLoadSertA->Cells[0][0]="№";
  sgLoadSertA->Cells[1][0]="Задание";
  sgLoadSertA->Cells[2][0]="Показание";
  sgLoadSertA->Cells[3][0]="Измерение";
  sgLoadSertA->Cells[4][0]="Коэффицент";
  sgLoadSertA->RowHeights[0]=CellH;
  for (int i = 1; i < LDCQTY+1; i++) sgLoadSertA->RowHeights[i]=CellH;
  for (int i = 0; i < LDCQTY; i++) {
    if(i<9)sgLoadSertA->Cells[0][i+1]="  "+String(i+1)+":";
    else   sgLoadSertA->Cells[0][i+1]=" "+String(i+1)+":";
    sgLoadSertA->Cells[1][i+1]=LdCA->sTLd[i];
	if(LdCA->ReadoutLd[i]!=0.0)
      sgLoadSertA->Cells[2][i+1]="   "+FloatToStrF(LdCA->ReadoutLd[i],ffFixed,6,2);
	else
	  sgLoadSertA->Cells[2][i+1]="";
	if(LdCA->MeasuredLd[i]!=0.0)
      sgLoadSertA->Cells[3][i+1]="    "+FloatToStrF(LdCA->MeasuredLd[i],ffFixed,6,2);
	else
	  sgLoadSertA->Cells[3][i+1]="";
	if(LdCA->loaded)
      sgLoadSertA->Cells[4][i+1]="    "+FloatToStrF(LdCA->KA[i],ffFixed,8,5);
	else
	  sgLoadSertA->Cells[4][i+1]="";
  }
  int Top1=H1+LSp1, Left11=TblW+LSp1, LblW1=85, BtnW1=LblW1*3, BtnW2=tsSpeedCalibrW-TblW-BtnW1-LSp1*3;
  int Left12=Left11+LblW1, Left13=Left11+LblW1*2, Left2=Left11+LblW1*3+LSp1, H2=50, H3=26;
  btnPrevSertLoadA->Left       =Left11;       btnPrevSertLoadA->Top         =Top1;
  btnPrevSertLoadA->Width      =BtnW1;        btnPrevSertLoadA->Height      =H2;
  btnLoadSertClearTableA->Left =Left2;        btnLoadSertClearTableA->Top   =Top1;
  btnLoadSertClearTableA->Width=BtnW2;        btnLoadSertClearTableA->Height=H2;
  btnLoadSertCalcA->Left       =Left2;        btnLoadSertCalcA->Top         =Top1+H2+LSp1;
  btnLoadSertCalcA->Width      =BtnW2;        btnLoadSertCalcA->Height      =H2;
  btnLoadSertPrintProtA->Left  =Left2;        btnLoadSertPrintProtA->Top    =Top1+H2*2+LSp1*2;
  btnLoadSertPrintProtA->Width =BtnW2;        btnLoadSertPrintProtA->Height =H2;
  leCurrentLoadSertSetA->Left  =Left11;       leCurrentLoadSertSetA->Top    =Top1+H2*2+LSp1-H3;
  leCurrentLoadSertSetA->Width =LblW1;        leCurrentLoadSertSetA->Height =H3;
  leReadLoadSertA->Left        =Left12;       leReadLoadSertA->Top          =Top1+H2*2+LSp1-H3;
  leReadLoadSertA->Width       =LblW1;        leReadLoadSertA->Height       =H3;
  leMeasLoadSertA->Left        =Left13;       leMeasLoadSertA->Top          =Top1+H2*2+LSp1-H3;
  leMeasLoadSertA->Width       =LblW1;        leMeasLoadSertA->Height       =H3;
  btnNextSertLoadA->Left       =Left11;       btnNextSertLoadA->Top         =Top1+H2*2+LSp1*2;
  btnNextSertLoadA->Width      =BtnW1;        btnNextSertLoadA->Height      =H2;
  btnLoadSertAToPLC->Left      =Left2;        btnLoadSertAToPLC->Top        =Top1+H2*3+LSp1*3;
  btnLoadSertAToPLC->Width     =BtnW2;        btnLoadSertAToPLC->Height     =H2;
  btnSertPumpOnA->Left         =Left11;       btnSertPumpOnA->Top           =Top1+H2*3+LSp1*5;
  btnSertPumpOnA->Width        =BtnW1;        btnSertPumpOnA->Height        =H2;
  btnSertPumpOffA->Left        =Left11;       btnSertPumpOffA->Top          =Top1+H2*6+LSp1*8;
  btnSertPumpOffA->Width       =BtnW1;        btnSertPumpOffA->Height       =H2;
  btnUploadSertAFmPLC->Left    =Left2;        btnUploadSertAFmPLC->Top      =Top1+H2*4+LSp1*4;
  btnUploadSertAFmPLC->Width   =BtnW2;        btnUploadSertAFmPLC->Height   =H2;
  btnResetCalibrCoeffA->Left   =Left2;        btnResetCalibrCoeffA->Top     =Top1+H2*5+LSp1*5;
  btnResetCalibrCoeffA->Width  =BtnW2;        btnResetCalibrCoeffA->Height  =H2;
//  LdCA->Index=0;
  leCurrentLoadSertSetA->Text  =FloatToStrF(LdCA->TargetLd[LdCA->Index],ffFixed,6,2);
  leReadLoadSertA->Text        =FloatToStrF(LdCA->ReadoutLd[LdCA->Index],ffFixed,6,2);
  leMeasLoadSertA->Text        =FloatToStrF(LdCA->MeasuredLd[LdCA->Index],ffFixed,6,2);
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
  sgLoadSertA->Selection=myRect;*/
  btnPrevSertLoadA->Enabled=false;
  btnNextSertLoadA->Enabled= true;
}
//---- End of DesignLoadSertAPanel ------------------------------------------

void __fastcall TmfRB::DesignLoadSertBPanel(void)// расположение компонент на панели калибровки нагрузки поз. Б
{ const int C0W=30,C1W=60,C2W=70,C3W=70,C4W=80;
  int TblW=C0W+C1W+C2W+C3W+C4W+28, H1=40, LSp1=10;
  int TblH=tsLoadCalibrAH-H1, CellH=max(ceil(double(TblH/(LDCQTY+1)))-1, 16.0)/*, Cell0H=40;TblH-(LDCQTY+1)*CellH*/;//-LDCQTY;
  pLoadSertBTtl->Height=H1;
  sgLoadSertB->ColWidths[0]=C0W;     sgLoadSertB->ColWidths[1]=C1W;
  sgLoadSertB->ColWidths[2]=C2W;     sgLoadSertB->ColWidths[3]=C3W;
  sgLoadSertB->ColWidths[4]=C4W;
  sgLoadSertB->Width=TblW;
  sgLoadSertB->Cells[0][0]="№";
  sgLoadSertB->Cells[1][0]="Задание";
  sgLoadSertB->Cells[2][0]="Показание";
  sgLoadSertB->Cells[3][0]="Измерение";
  sgLoadSertB->Cells[4][0]="Коэффицент";
  sgLoadSertB->RowHeights[0]=CellH;
  for (int i = 1; i < LDCQTY+1; i++) sgLoadSertB->RowHeights[i]=CellH;
  for (int i = 0; i < LDCQTY; i++) {
    if(i<9)sgLoadSertB->Cells[0][i+1]="  "+String(i+1)+":";
    else   sgLoadSertB->Cells[0][i+1]=" "+String(i+1)+":";
    sgLoadSertB->Cells[1][i+1]=LdCB->sTLd[i];
	if(LdCB->ReadoutLd[i]!=0.0)
      sgLoadSertB->Cells[2][i+1]="   "+FloatToStrF(LdCB->ReadoutLd[i],ffFixed,6,2);
	else
	  sgLoadSertB->Cells[2][i+1]="";
	if(LdCB->MeasuredLd[i]!=0.0)
      sgLoadSertB->Cells[3][i+1]="    "+FloatToStrF(LdCB->MeasuredLd[i],ffFixed,6,2);
	else
	  sgLoadSertB->Cells[3][i+1]="";
	if(LdCB->loaded)
      sgLoadSertB->Cells[4][i+1]="    "+FloatToStrF(LdCB->KA[i],ffFixed,8,5);
	else
	  sgLoadSertB->Cells[4][i+1]="";
  }
  int Top1=H1+LSp1, Left11=TblW+LSp1, LblW1=85, BtnW1=LblW1*3, BtnW2=tsSpeedCalibrW-TblW-BtnW1-LSp1*3;
  int Left12=Left11+LblW1, Left13=Left11+LblW1*2, Left2=Left11+LblW1*3+LSp1, H2=50, H3=26;
  btnPrevSertLoadB->Left       =Left11;       btnPrevSertLoadB->Top         =Top1;
  btnPrevSertLoadB->Width      =BtnW1;        btnPrevSertLoadB->Height      =H2;
  btnLoadSertClearTableB->Left =Left2;        btnLoadSertClearTableB->Top   =Top1;
  btnLoadSertClearTableB->Width=BtnW2;        btnLoadSertClearTableB->Height=H2;
  btnLoadSertCalcB->Left       =Left2;        btnLoadSertCalcB->Top         =Top1+H2+LSp1;
  btnLoadSertCalcB->Width      =BtnW2;        btnLoadSertCalcB->Height      =H2;
  btnLoadSertPrintProtB->Left  =Left2;        btnLoadSertPrintProtB->Top    =Top1+H2*2+LSp1*2;
  btnLoadSertPrintProtB->Width =BtnW2;        btnLoadSertPrintProtB->Height =H2;
  leCurrentLoadSertSetB->Left  =Left11;       leCurrentLoadSertSetB->Top    =Top1+H2*2+LSp1-H3;
  leCurrentLoadSertSetB->Width =LblW1;        leCurrentLoadSertSetB->Height =H3;
  leReadLoadSertB->Left        =Left12;       leReadLoadSertB->Top          =Top1+H2*2+LSp1-H3;
  leReadLoadSertB->Width       =LblW1;        leReadLoadSertB->Height       =H3;
  leMeasLoadSertB->Left        =Left13;       leMeasLoadSertB->Top          =Top1+H2*2+LSp1-H3;
  leMeasLoadSertB->Width       =LblW1;        leMeasLoadSertB->Height       =H3;
  btnNextSertLoadB->Left       =Left11;       btnNextSertLoadB->Top         =Top1+H2*2+LSp1*2;
  btnNextSertLoadB->Width      =BtnW1;        btnNextSertLoadB->Height      =H2;
  btnLoadSertBToPLC->Left      =Left2;        btnLoadSertBToPLC->Top        =Top1+H2*3+LSp1*3;
  btnLoadSertBToPLC->Width     =BtnW2;        btnLoadSertBToPLC->Height     =H2;
  btnSertPumpOnB->Left         =Left11;       btnSertPumpOnB->Top           =Top1+H2*3+LSp1*5;
  btnSertPumpOnB->Width        =BtnW1;        btnSertPumpOnB->Height        =H2;
  btnSertPumpOffB->Left        =Left11;       btnSertPumpOffB->Top          =Top1+H2*6+LSp1*8;
  btnSertPumpOffB->Width       =BtnW1;        btnSertPumpOffB->Height       =H2;
  btnUploadSertBFmPLC->Left    =Left2;        btnUploadSertBFmPLC->Top      =Top1+H2*4+LSp1*4;
  btnUploadSertBFmPLC->Width   =BtnW2;        btnUploadSertBFmPLC->Height   =H2;
  btnResetCalibrCoeffB->Left   =Left2;        btnResetCalibrCoeffB->Top     =Top1+H2*5+LSp1*5;
  btnResetCalibrCoeffB->Width  =BtnW2;        btnResetCalibrCoeffB->Height  =H2;
//  LdCB->Index=0;
  leCurrentLoadSertSetB->Text  =FloatToStrF(LdCB->TargetLd[LdCB->Index],ffFixed,6,2);
  leReadLoadSertB->Text        =FloatToStrF(LdCB->ReadoutLd[LdCB->Index],ffFixed,6,2);
  leMeasLoadSertB->Text        =FloatToStrF(LdCB->MeasuredLd[LdCB->Index],ffFixed,6,2);
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
  sgLoadSertB->Selection=myRect;*/
  btnPrevSertLoadB->Enabled=false;
  btnNextSertLoadB->Enabled= true;
}
//---- End of DesignLoadSertBPanel ------------------------------------------

void __fastcall TmfRB::DesignTSertPanel(void)  // расположение компонент на панели калибровки температуры
{
  int H1=26, LSp1=10;  int PWidth=pTSertTtl->Width, PHeight=tsTemSert->Height-H1-LSp1;
  int GBW=(PWidth-LSp1*3)/2, Top1=H1+LSp1;
  pTSertTtl->Height=H1;
  gbTSertA->Top    =Top1;      gbTSertB->Top      =Top1;
  gbTSertA->Left   =LSp1;      gbTSertB->Left     =LSp1*2+GBW;
  gbTSertA->Width  =GBW;       gbTSertB->Width    =GBW;
  gbTSertA->Height =PHeight;   gbTSertB->Height   =PHeight;
}
//---- End of DesignTSertPanel ----------------------------------------------

void __fastcall TmfRB::DesignRSertPanel(void)  // расположение компонент на панели калибровки датчиков радиуса
{
  int H1=26, LSp1=10;//  int PWidth=pRSertTtl->Width, PHeight=tsRadSert->Height-H1-LSp1;
  int BtnW=170, LeW=40, BtnH=40, LeH=20, Top1=H1+LSp1*5, Top2=Top1+BtnH+LSp1*2;
  int LeLblW=leRShiftA->EditLabel->Width, Left1=LeLblW+LSp1, Left2=Left1+LeW+LSp1*2;
  pRSertTtl->Height=H1;
  leRShiftA->Left           =Left1;       leRShiftA->Top             =Top1;
  leRShiftA->Width          =LeW;         leRShiftA->Height          =LeH;
  btnRShiftALoadToPLC->Left =Left2;       btnRShiftALoadToPLC->Top   =Top1-(BtnH-LeH)/2;
  btnRShiftALoadToPLC->Width=BtnW;        btnRShiftALoadToPLC->Height=BtnH;
  leRShiftB->Left           =Left1;       leRShiftB->Top             =Top2;
  leRShiftB->Width          =LeW;         leRShiftB->Height          =LeH;
  btnRShiftBLoadToPLC->Left =Left2;       btnRShiftBLoadToPLC->Top   =Top2-(BtnH-LeH)/2;
  btnRShiftBLoadToPLC->Width=BtnW;        btnRShiftBLoadToPLC->Height=BtnH;
}
//---- End of DesignRSertPanel ----------------------------------------------

void __fastcall TmfRB::DesignLoadCalibrAPanel(void)  // расположение компонент на панели аттестации нагрузки поз. А
{ const int C0W=30,C1W=60,C2W=70,C3W=70,C4W=80;
  int TblW=C0W+C1W+C2W+C3W+C4W+30, H1=40, LSp1=10;
  int TblH=tsLoadCalibrAH-H1, CellH=max((TblH-5)/(LDQTY+1), 16);
  pLoadCalibrATtl->Height=H1;
  sgLoadCalibrA->ColWidths[0]=C0W;     sgLoadCalibrA->ColWidths[1]=C1W;
  sgLoadCalibrA->ColWidths[2]=C2W;     sgLoadCalibrA->ColWidths[3]=C3W;
  sgLoadCalibrA->ColWidths[4]=C4W;
  sgLoadCalibrA->Width=TblW;
  sgLoadCalibrA->Cells[0][0]="№";
  sgLoadCalibrA->Cells[1][0]="Задание";
  sgLoadCalibrA->Cells[2][0]="Измерение";
  sgLoadCalibrA->Cells[3][0]="Показание";
  sgLoadCalibrA->Cells[4][0]="Погрешность";
  for (int i = 0; i < LDQTY+1; i++) sgLoadCalibrA->RowHeights[i]=CellH;
  for (int i = 0; i < LDQTY; i++) {
    sgLoadCalibrA->RowHeights[i]=CellH;
    if(i<9)sgLoadCalibrA->Cells[0][i+1]="  "+String(i+1)+":";
    else   sgLoadCalibrA->Cells[0][i+1]=" "+String(i+1)+":";
    sgLoadCalibrA->Cells[1][i+1]=LdSA->sTLd[i];
	if(LdSA->ReadoutLd[i]!=0.0){
      sgLoadCalibrA->Cells[2][i+1]="    "+FloatToStrF(LdSA->MeasuredLd[i],ffFixed,6,2);
      sgLoadCalibrA->Cells[3][i+1]="    "+FloatToStrF(LdSA->ReadoutLd[i],ffFixed,6,2);
      sgLoadCalibrA->Cells[4][i+1]="    "+FloatToStrF(LdSA->RelError[i],ffFixed,6,2);
    }
    else {
      sgLoadCalibrA->Cells[2][i+1]="";
      sgLoadCalibrA->Cells[3][i+1]="";
      sgLoadCalibrA->Cells[4][i+1]="";
    }
  }
  int Top1=H1+LSp1, Left11=TblW+LSp1, LblW1=85, BtnW1=LblW1*3, BtnW2=tsSpeedCalibrW-TblW-BtnW1-LSp1*3;
  int Left12=Left11+LblW1, Left13=Left11+LblW1*2, Left2=Left11+LblW1*3+LSp1, H2=50, H3=26;
  btnPrevCalibrLoadA->Left        =Left11;       btnPrevCalibrLoadA->Top          =Top1;
  btnPrevCalibrLoadA->Width       =BtnW1;        btnPrevCalibrLoadA->Height       =H2;
  btnClearLoadCalibreTableA->Left =Left2;        btnClearLoadCalibreTableA->Top   =Top1;
  btnClearLoadCalibreTableA->Width=BtnW2;        btnClearLoadCalibreTableA->Height=H2;
  btnLoadCalibrCalcA->Left        =Left2;        btnLoadCalibrCalcA->Top          =Top1+H2+LSp1;
  btnLoadCalibrCalcA->Width       =BtnW2;        btnLoadCalibrCalcA->Height       =H2;
  btnLoadCalibrTableAPrint->Left  =Left2;        btnLoadCalibrTableAPrint->Top    =Top1+H2*2+LSp1*2;
  btnLoadCalibrTableAPrint->Width =BtnW2;        btnLoadCalibrTableAPrint->Height =H2;
  leCurrentLoadSetA->Left         =Left11;       leCurrentLoadSetA->Top           =Top1+H2*2+LSp1-H3;
  leCurrentLoadSetA->Width        =LblW1;        leCurrentLoadSetA->Height        =H3;
  leReadLoadA->Left               =Left12;       leReadLoadA->Top                 =Top1+H2*2+LSp1-H3;
  leReadLoadA->Width              =LblW1;        leReadLoadA->Height              =H3;
  leMeasuredLoadA->Left           =Left13;       leMeasuredLoadA->Top             =Top1+H2*2+LSp1-H3;
  leMeasuredLoadA->Width          =LblW1;        leMeasuredLoadA->Height          =H3;
  btnNextCalibrLoadA->Left        =Left11;       btnNextCalibrLoadA->Top          =Top1+H2*2+LSp1*2;
  btnNextCalibrLoadA->Width       =BtnW1;        btnNextCalibrLoadA->Height       =H2;
  btnPumpOnA->Left                =Left11;       btnPumpOnA->Top                  =Top1+H2*3+LSp1*5;
  btnPumpOnA->Width               =BtnW1;        btnPumpOnA->Height               =H2;
  btnPumpOffA->Left               =Left11;       btnPumpOffA->Top                 =Top1+H2*4+LSp1*6;
  btnPumpOffA->Width              =BtnW1;        btnPumpOffA->Height              =H2;
//  LdSA->Index=0;
  leCurrentLoadSetA->Text=FloatToStrF(LdSA->TargetLd[LdSA->Index],ffFixed,6,2);
  leReadLoadA->Text      =FloatToStrF(LdSA->ReadoutLd[LdSA->Index],ffFixed,6,2);
  leMeasuredLoadA->Text  =FloatToStrF(LdSA->MeasuredLd[LdSA->Index],ffFixed,6,2);
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
  sgLoadCalibrA->Selection=myRect;*/
  btnPrevCalibrLoadA->Enabled=false;
  btnNextCalibrLoadA->Enabled= true;
}
//---- End of DesignLoadCalibrAPanel ----------------------------------------

void __fastcall TmfRB::DesignLoadCalibrBPanel(void)  // расположение компонент на панели аттестации нагрузки поз. Б
{ const int C0W=30,C1W=60,C2W=70,C3W=70,C4W=80;
  int TblW=C0W+C1W+C2W+C3W+C4W+30, H1=40, LSp1=10;
  int TblH=tsLoadCalibrAH-H1, CellH=max((TblH-5)/(LDQTY+1), 16);
  pLoadCalibrBTtl->Height=H1;
  sgLoadCalibrB->ColWidths[0]=C0W;     sgLoadCalibrB->ColWidths[1]=C1W;
  sgLoadCalibrB->ColWidths[2]=C2W;     sgLoadCalibrB->ColWidths[3]=C3W;
  sgLoadCalibrB->ColWidths[4]=C4W;
  sgLoadCalibrB->Width=TblW;
  sgLoadCalibrB->Cells[0][0]="№";
  sgLoadCalibrB->Cells[1][0]="Задание";
  sgLoadCalibrB->Cells[2][0]="Измерение";
  sgLoadCalibrB->Cells[3][0]="Показание";
  sgLoadCalibrB->Cells[4][0]="Погрешность";
  for (int i = 0; i < LDQTY+1; i++) sgLoadCalibrB->RowHeights[i]=CellH;
  for (int i = 0; i < LDQTY; i++) {
    if(i<9)sgLoadCalibrB->Cells[0][i+1]="  "+String(i+1)+":";
    else   sgLoadCalibrB->Cells[0][i+1]=" "+String(i+1)+":";
    sgLoadCalibrB->Cells[1][i+1]=LdSB->sTLd[i];
	if(LdSB->ReadoutLd[i]!=0.0) {
      sgLoadCalibrB->Cells[2][i+1]="    "+FloatToStrF(LdSB->MeasuredLd[i],ffFixed,6,2);
      sgLoadCalibrB->Cells[3][i+1]="    "+FloatToStrF(LdSB->ReadoutLd[i],ffFixed,6,2);
      sgLoadCalibrB->Cells[4][i+1]="    "+FloatToStrF(LdSB->RelError[i],ffFixed,6,2);
    }
    else {
      sgLoadCalibrB->Cells[2][i+1]="";
      sgLoadCalibrB->Cells[3][i+1]="";
      sgLoadCalibrB->Cells[4][i+1]="";
    }
  }
  int Top1=H1+LSp1, Left11=TblW+LSp1, LblW1=85, BtnW1=LblW1*3, BtnW2=tsSpeedCalibrW-TblW-BtnW1-LSp1*3;
  int Left12=Left11+LblW1, Left13=Left11+LblW1*2, Left2=Left11+LblW1*3+LSp1, H2=50, H3=26;
  btnPrevCalibrLoadB->Left        =Left11;       btnPrevCalibrLoadB->Top          =Top1;
  btnPrevCalibrLoadB->Width       =BtnW1;        btnPrevCalibrLoadB->Height       =H2;
  btnClearLoadCalibreTableB->Left =Left2;        btnClearLoadCalibreTableB->Top   =Top1;
  btnClearLoadCalibreTableB->Width=BtnW2;        btnClearLoadCalibreTableB->Height=H2;
  btnLoadCalibrCalcB->Left        =Left2;        btnLoadCalibrCalcB->Top          =Top1+H2+LSp1;
  btnLoadCalibrCalcB->Width       =BtnW2;        btnLoadCalibrCalcB->Height       =H2;
  btnLoadCalibrTableBPrint->Left  =Left2;        btnLoadCalibrTableBPrint->Top    =Top1+H2*2+LSp1*2;
  btnLoadCalibrTableBPrint->Width =BtnW2;        btnLoadCalibrTableBPrint->Height =H2;
  leCurrentLoadSetB->Left         =Left11;       leCurrentLoadSetB->Top           =Top1+H2*2+LSp1-H3;
  leCurrentLoadSetB->Width        =LblW1;        leCurrentLoadSetB->Height        =H3;
  leReadLoadB->Left               =Left12;       leReadLoadB->Top                 =Top1+H2*2+LSp1-H3;
  leReadLoadB->Width              =LblW1;        leReadLoadB->Height              =H3;
  leMeasuredLoadB->Left           =Left13;       leMeasuredLoadB->Top             =Top1+H2*2+LSp1-H3;
  leMeasuredLoadB->Width          =LblW1;        leMeasuredLoadB->Height          =H3;
  btnNextCalibrLoadB->Left        =Left11;       btnNextCalibrLoadB->Top          =Top1+H2*2+LSp1*2;
  btnNextCalibrLoadB->Width       =BtnW1;        btnNextCalibrLoadB->Height       =H2;
  btnPumpOnB->Left                =Left11;       btnPumpOnB->Top                  =Top1+H2*3+LSp1*5;
  btnPumpOnB->Width               =BtnW1;        btnPumpOnB->Height               =H2;
  btnPumpOffB->Left               =Left11;       btnPumpOffB->Top                 =Top1+H2*4+LSp1*6;
  btnPumpOffB->Width              =BtnW1;        btnPumpOffB->Height              =H2;
//  LdSB->Index=0;
  leCurrentLoadSetB->Text=FloatToStrF(LdSB->TargetLd[LdSB->Index],ffFixed,6,2);
  leReadLoadB->Text      =FloatToStrF(LdSB->ReadoutLd[LdSB->Index],ffFixed,6,2);
  leMeasuredLoadB->Text  =FloatToStrF(LdSB->MeasuredLd[LdSB->Index],ffFixed,6,2);
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
  sgLoadCalibrB->Selection=myRect;*/
  btnPrevCalibrLoadB->Enabled=false;
  btnNextCalibrLoadB->Enabled= true;
}
//---- End of DesignLoadCalibrBPanel ----------------------------------------

void __fastcall TmfRB::DesignRCalibrAPanel(void)// расположение компонент на панели аттестации радиуса поз. А
{ const int C0W=30,C1W=70,C2W=70,C3W=80;
  int TblW=C0W+C1W+C2W+C3W+7, H1=40, LSp1=10;
  sgRCalibrA->RowCount=RQTY+1;
  int TblH=tsRCalibrAH-H1, CellH=(TblH-RQTY/3)/(RQTY+1);
  pRCalibrATtl->Height=H1;
  sgRCalibrA->ColWidths[0]=C0W;     sgRCalibrA->ColWidths[1]=C1W;
  sgRCalibrA->ColWidths[2]=C2W;     sgRCalibrA->ColWidths[3]=C3W;
  sgRCalibrA->Width=TblW;
  sgRCalibrA->Cells[0][0]="№";
  sgRCalibrA->Cells[1][0]="Показание";
  sgRCalibrA->Cells[2][0]="Измерение";
  sgRCalibrA->Cells[3][0]="Погрешность";
  for (int i = 0; i < RQTY+1; i++) sgRCalibrA->RowHeights[i]=CellH;
  for (int i = 0; i < RQTY; i++) {
    if(i<9)sgRCalibrA->Cells[0][i+1]="  "+String(i+1)+":";
    else   sgRCalibrA->Cells[0][i+1]=" "+String(i+1)+":";
    sgRCalibrA->Cells[1][i+1]="";
    sgRCalibrA->Cells[2][i+1]="";
    sgRCalibrA->Cells[3][i+1]="";
  }
  int Top1=H1+LSp1, Left11=TblW+LSp1, LblW1=(tsTCalibrAW-TblW-LSp1*3)/4,
      BtnW1=LblW1*2, BtnW2=tsTCalibrAW-TblW-BtnW1-LSp1*3;
  int Left12=Left11+LblW1, Left2=Left11+BtnW1+LSp1, H2=50, H3=26;
  int BtnW4=(tsTCalibrAW-TblW-LSp1*4)/5, BtnW3=BtnW4*2, Top2=Top1+H2*3+LSp1*4,
      Left3=Left11+BtnW3+LSp1, Left4=Left3+BtnW4+LSp1;
  btnPrevRCalibrA->Left       =Left11;       btnPrevRCalibrA->Top         =Top1;
  btnPrevRCalibrA->Width      =BtnW1;        btnPrevRCalibrA->Height      =H2;
  btnClearRCalibrTableA->Left =Left2;        btnClearRCalibrTableA->Top   =Top1;
  btnClearRCalibrTableA->Width=BtnW2;        btnClearRCalibrTableA->Height=H2;
  btnRCalibrCalcA->Left       =Left2;        btnRCalibrCalcA->Top         =Top1+H2+LSp1;
  btnRCalibrCalcA->Width      =BtnW2;        btnRCalibrCalcA->Height      =H2;
  btnRCalibrTableAPrint->Left =Left2;        btnRCalibrTableAPrint->Top   =Top1+H2*2+LSp1*2;
  btnRCalibrTableAPrint->Width=BtnW2;        btnRCalibrTableAPrint->Height=H2;
  leReadRA->Left              =Left11;       leReadRA->Top                =Top1+H2*2+LSp1-H3;
  leReadRA->Width             =LblW1;        leReadRA->Height             =H3;
  leMeasRA->Left              =Left12;       leMeasRA->Top                =Top1+H2*2+LSp1-H3;
  leMeasRA->Width             =LblW1;        leMeasRA->Height             =H3;
  btnNextRCalibrA->Left       =Left11;       btnNextRCalibrA->Top         =Top1+H2*2+LSp1*2;
  btnNextRCalibrA->Width      =BtnW1;        btnNextRCalibrA->Height      =H2;
  btnCalibrCarr1Fm->Left      =Left11;       btnCalibrCarr1Fm->Top        =Top2;
  btnCalibrCarr1Fm->Width     =BtnW3;        btnCalibrCarr1Fm->Height     =H2;
  btnCalibrCarr1Stop->Left    =Left3;        btnCalibrCarr1Stop->Top      =Top2;
  btnCalibrCarr1Stop->Width   =BtnW4;        btnCalibrCarr1Stop->Height   =H2;
  btnCalibrCarr1To->Left      =Left4;        btnCalibrCarr1To->Top        =Top2;
  btnCalibrCarr1To->Width     =BtnW3;        btnCalibrCarr1To->Height     =H2;
  RSA->Index                  =0;
  leReadRA->Text              =FloatToStrF(RSA->ReadoutR[0],ffFixed,6,2);
  leMeasRA->Text              =FloatToStrF(RSA->MeasuredR[0],ffFixed,6,2);
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
  sgRCalibrA->Selection=myRect;*/
  btnPrevRCalibrA->Enabled=false;
  btnNextRCalibrA->Enabled= true;
}
//---- End of DesignRCalibrAPanel -------------------------------------------

void __fastcall TmfRB::DesignRCalibrBPanel(void)// расположение компонент на панели аттестации радиуса поз. Б
{ const int C0W=30,C1W=70,C2W=70,C3W=80;
  int TblW=C0W+C1W+C2W+C3W+7, H1=40, LSp1=10;
  sgRCalibrB->RowCount=RQTY+1;
  int TblH=tsRCalibrAH-H1, CellH=(TblH-RQTY/3)/(RQTY+1);
  pRCalibrBTtl->Height=H1;
  sgRCalibrB->ColWidths[0]=C0W;     sgRCalibrB->ColWidths[1]=C1W;
  sgRCalibrB->ColWidths[2]=C2W;     sgRCalibrB->ColWidths[3]=C3W;
  sgRCalibrB->Width=TblW;
  sgRCalibrB->Cells[0][0]="№";
  sgRCalibrB->Cells[1][0]="Показание";
  sgRCalibrB->Cells[2][0]="Измерение";
  sgRCalibrB->Cells[3][0]="Погрешность";
  for (int i = 0; i < RQTY+1; i++) sgRCalibrB->RowHeights[i]=CellH;
  for (int i = 0; i < RQTY; i++) {
    if(i<9)sgRCalibrB->Cells[0][i+1]="  "+String(i+1)+":";
    else   sgRCalibrB->Cells[0][i+1]=" "+String(i+1)+":";
    sgRCalibrB->Cells[1][i+1]="";
    sgRCalibrB->Cells[2][i+1]="";
    sgRCalibrB->Cells[3][i+1]="";
  }
  int Top1=H1+LSp1, Left11=TblW+LSp1, LblW1=(tsTCalibrAW-TblW-LSp1*3)/4,
      BtnW1=LblW1*2, BtnW2=tsTCalibrAW-TblW-BtnW1-LSp1*3;
  int Left12=Left11+LblW1, Left2=Left11+BtnW1+LSp1, H2=50, H3=26;
  int BtnW4=(tsTCalibrAW-TblW-LSp1*4)/5, BtnW3=BtnW4*2, Top2=Top1+H2*3+LSp1*4,
      Left3=Left11+BtnW3+LSp1, Left4=Left3+BtnW4+LSp1;
  btnPrevRCalibrB->Left       =Left11;       btnPrevRCalibrB->Top         =Top1;
  btnPrevRCalibrB->Width      =BtnW1;        btnPrevRCalibrB->Height      =H2;
  btnClearRCalibrTableB->Left =Left2;        btnClearRCalibrTableB->Top   =Top1;
  btnClearRCalibrTableB->Width=BtnW2;        btnClearRCalibrTableB->Height=H2;
  btnRCalibrCalcB->Left       =Left2;        btnRCalibrCalcB->Top         =Top1+H2+LSp1;
  btnRCalibrCalcB->Width      =BtnW2;        btnRCalibrCalcB->Height      =H2;
  btnRCalibrTableBPrint->Left =Left2;        btnRCalibrTableBPrint->Top   =Top1+H2*2+LSp1*2;
  btnRCalibrTableBPrint->Width=BtnW2;        btnRCalibrTableBPrint->Height=H2;
  leReadRB->Left              =Left11;       leReadRB->Top                =Top1+H2*2+LSp1-H3;
  leReadRB->Width             =LblW1;        leReadRB->Height             =H3;
  leMeasRB->Left              =Left12;       leMeasRB->Top                =Top1+H2*2+LSp1-H3;
  leMeasRB->Width             =LblW1;        leMeasRB->Height             =H3;
  btnNextRCalibrB->Left       =Left11;       btnNextRCalibrB->Top         =Top1+H2*2+LSp1*2;
  btnNextRCalibrB->Width      =BtnW1;        btnNextRCalibrB->Height      =H2;
  btnCalibrCarr2Fm->Left      =Left11;       btnCalibrCarr2Fm->Top        =Top2;
  btnCalibrCarr2Fm->Width     =BtnW3;        btnCalibrCarr2Fm->Height     =H2;
  btnCalibrCarr2Stop->Left    =Left3;        btnCalibrCarr2Stop->Top      =Top2;
  btnCalibrCarr2Stop->Width   =BtnW4;        btnCalibrCarr2Stop->Height   =H2;
  btnCalibrCarr2To->Left      =Left4;        btnCalibrCarr2To->Top        =Top2;
  btnCalibrCarr2To->Width     =BtnW3;        btnCalibrCarr2To->Height     =H2;
  RSB->Index                  =0;
  leReadRB->Text              =FloatToStrF(RSB->ReadoutR[0],ffFixed,6,2);
  leMeasRB->Text              =FloatToStrF(RSB->MeasuredR[0],ffFixed,6,2);
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
  sgRCalibrB->Selection=myRect;*/
  btnPrevRCalibrB->Enabled=false;
  btnNextRCalibrB->Enabled= true;
}
//---- End of DesignRCalibrBPanel -------------------------------------------

void __fastcall TmfRB::DesignTCalibrAPanel(void)  // расположение компонент на панели аттестации температуры поз. А
{ const int C0W=30,C1W=70,C2W=70,C3W=80;
  int TblW=C0W+C1W+C2W+C3W+7, H1=40, LSp1=10;
  sgTCalibrA->RowCount=TQTY+1;
  int TblH=tsTCalibrAH-H1, CellH=(TblH-TQTY/3)/(TQTY+1);
  pTCalibrATtl->Height=H1;
  sgTCalibrA->ColWidths[0]=C0W;     sgTCalibrA->ColWidths[1]=C1W;
  sgTCalibrA->ColWidths[2]=C2W;     sgTCalibrA->ColWidths[3]=C3W;
  sgTCalibrA->Width=TblW;
  sgTCalibrA->Cells[0][0]="№";
  sgTCalibrA->Cells[1][0]="Показание";
  sgTCalibrA->Cells[2][0]="Измерение";
  sgTCalibrA->Cells[3][0]="Погрешность";
  for (int i = 0; i < TQTY+1; i++) sgTCalibrA->RowHeights[i]=CellH;
  for (int i = 0; i < TQTY; i++) {
    if(i<9)sgTCalibrA->Cells[0][i+1]="  "+String(i+1)+":";
    else   sgTCalibrA->Cells[0][i+1]=" "+String(i+1)+":";
    if (TSA->RelError[i]!=0.0) {
      sgTCalibrA->Cells[1][i+1]="    "+FloatToStrF(TSA->ReadoutT[i],ffFixed,6,2);
      sgTCalibrA->Cells[2][i+1]="    "+FloatToStrF(TSA->MeasuredT[i],ffFixed,6,2);
      sgTCalibrA->Cells[3][i+1]="    "+FloatToStrF(TSA->RelError[i],ffFixed,6,2);
    }
    else {
      sgTCalibrA->Cells[1][i+1]="";
      sgTCalibrA->Cells[2][i+1]="";
      sgTCalibrA->Cells[3][i+1]="";
    }
  }
  int Top1=H1+LSp1, Left11=TblW+LSp1, LblW1=(tsTCalibrAW-TblW-LSp1*3)/4,
      BtnW1=LblW1*2, BtnW2=tsTCalibrAW-TblW-BtnW1-LSp1*3;
  int Left12=Left11+LblW1, Left2=Left11+BtnW1+LSp1, H2=50, H3=26;
  btnPrevTCalibrA->Left       =Left11;       btnPrevTCalibrA->Top         =Top1;
  btnPrevTCalibrA->Width      =BtnW1;        btnPrevTCalibrA->Height      =H2;
  btnClearTCalibrTableA->Left =Left2;        btnClearTCalibrTableA->Top   =Top1;
  btnClearTCalibrTableA->Width=BtnW2;        btnClearTCalibrTableA->Height=H2;
  btnTCalibrCalcA->Left       =Left2;        btnTCalibrCalcA->Top         =Top1+H2+LSp1;
  btnTCalibrCalcA->Width      =BtnW2;        btnTCalibrCalcA->Height      =H2;
  btnTCalibrTableAPrint->Left =Left2;        btnTCalibrTableAPrint->Top   =Top1+H2*2+LSp1*2;
  btnTCalibrTableAPrint->Width=BtnW2;        btnTCalibrTableAPrint->Height=H2;
  btnTLimitsCalcA->Left       =Left2;        btnTLimitsCalcA->Top         =Top1+H2*3+LSp1*3;
  btnTLimitsCalcA->Width      =BtnW2;        btnTLimitsCalcA->Height      =H2;
  leReadTA->Left              =Left11;       leReadTA->Top                =Top1+H2*2+LSp1-H3;
  leReadTA->Width             =LblW1;        leReadTA->Height             =H3;
  leMeasTA->Left              =Left12;       leMeasTA->Top                =Top1+H2*2+LSp1-H3;
  leMeasTA->Width             =LblW1;        leMeasTA->Height             =H3;
  btnNextTCalibrA->Left       =Left11;       btnNextTCalibrA->Top         =Top1+H2*2+LSp1*2;
  btnNextTCalibrA->Width      =BtnW1;        btnNextTCalibrA->Height      =H2;
//  TSA->Index                  =0;
  leReadTA->Text              =FloatToStrF(TSA->ReadoutT[TSA->Index],ffFixed,6,2);
  leMeasTA->Text              =FloatToStrF(TSA->MeasuredT[TSA->Index],ffFixed,6,2);
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=-1;
  sgTCalibrA->Selection=myRect;*/
  btnPrevTCalibrA->Enabled=false;
  btnNextTCalibrA->Enabled= true;
}
//---- End of DesignTCalibrAPanel -------------------------------------------

void __fastcall TmfRB::DesignTCalibrBPanel(void)  // расположение компонент на панели аттестации температуры поз. Б
{ const int C0W=30,C1W=70,C2W=70,C3W=80;
  int TblW=C0W+C1W+C2W+C3W+7, H1=40, LSp1=10;
  sgTCalibrB->RowCount=TQTY+1;
  int TblH=tsTCalibrAH-H1, CellH=(TblH-TQTY/3)/(TQTY+1);
  pTCalibrBTtl->Height=H1;
  sgTCalibrB->ColWidths[0]=C0W;     sgTCalibrB->ColWidths[1]=C1W;
  sgTCalibrB->ColWidths[2]=C2W;     sgTCalibrB->ColWidths[3]=C3W;
  sgTCalibrB->Width=TblW;
  sgTCalibrB->Cells[0][0]="№";
  sgTCalibrB->Cells[1][0]="Показание";
  sgTCalibrB->Cells[2][0]="Измерение";
  sgTCalibrB->Cells[3][0]="Погрешность";
  for (int i = 0; i < TQTY+1; i++) sgTCalibrB->RowHeights[i]=CellH;
  for (int i = 0; i < TQTY; i++) {
    if(i<9)sgTCalibrB->Cells[0][i+1]="  "+String(i+1)+":";
    else   sgTCalibrB->Cells[0][i+1]=" "+String(i+1)+":";
    if (TSB->RelError[i]!=0.0) {
      sgTCalibrB->Cells[1][i+1]="    "+FloatToStrF(TSB->ReadoutT[i],ffFixed,6,2);
      sgTCalibrB->Cells[2][i+1]="    "+FloatToStrF(TSB->MeasuredT[i],ffFixed,6,2);
      sgTCalibrB->Cells[3][i+1]="    "+FloatToStrF(TSB->RelError[i],ffFixed,6,2);
    }
    else {
      sgTCalibrB->Cells[1][i+1]="";
      sgTCalibrB->Cells[2][i+1]="";
      sgTCalibrB->Cells[3][i+1]="";
    }
  }
  int Top1=H1+LSp1, Left11=TblW+LSp1, LblW1=(tsTCalibrAW-TblW-LSp1*3)/4,
      BtnW1=LblW1*2, BtnW2=tsTCalibrAW-TblW-BtnW1-LSp1*3;
  int Left12=Left11+LblW1, Left2=Left11+BtnW1+LSp1, H2=50, H3=26;
  btnPrevTCalibrB->Left       =Left11;       btnPrevTCalibrB->Top         =Top1;
  btnPrevTCalibrB->Width      =BtnW1;        btnPrevTCalibrB->Height      =H2;
  btnClearTCalibrTableB->Left =Left2;        btnClearTCalibrTableB->Top   =Top1;
  btnClearTCalibrTableB->Width=BtnW2;        btnClearTCalibrTableB->Height=H2;
  btnTCalibrCalcB->Left       =Left2;        btnTCalibrCalcB->Top         =Top1+H2+LSp1;
  btnTCalibrCalcB->Width      =BtnW2;        btnTCalibrCalcB->Height      =H2;
  btnTCalibrTableBPrint->Left =Left2;        btnTCalibrTableBPrint->Top   =Top1+H2*2+LSp1*2;
  btnTCalibrTableBPrint->Width=BtnW2;        btnTCalibrTableBPrint->Height=H2;
  btnTLimitsCalcB->Left       =Left2;        btnTLimitsCalcB->Top         =Top1+H2*3+LSp1*3;
  btnTLimitsCalcB->Width      =BtnW2;        btnTLimitsCalcB->Height      =H2;
  leReadTB->Left              =Left11;       leReadTB->Top                =Top1+H2*2+LSp1-H3;
  leReadTB->Width             =LblW1;        leReadTB->Height             =H3;
  leMeasTB->Left              =Left12;       leMeasTB->Top                =Top1+H2*2+LSp1-H3;
  leMeasTB->Width             =LblW1;        leMeasTB->Height             =H3;
  btnNextTCalibrB->Left       =Left11;       btnNextTCalibrB->Top         =Top1+H2*2+LSp1*2;
  btnNextTCalibrB->Width      =BtnW1;        btnNextTCalibrB->Height      =H2;
//  TSB->Index                  =0;
  leReadTB->Text              =FloatToStrF(TSB->ReadoutT[TSB->Index],ffFixed,6,2);
  leMeasTB->Text              =FloatToStrF(TSB->MeasuredT[TSB->Index],ffFixed,6,2);
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=-1;
  sgTCalibrB->Selection=myRect;*/
  btnPrevTCalibrB->Enabled=false;
  btnNextTCalibrB->Enabled= true;
}
//---- End of DesignTCalibrBAPanel -------------------------------------------

void __fastcall TmfRB::DesignSpdCalibrPanel(void)// расположение компонент на панели аттестации барабана
{ const int C0W=30,C1W=60,C2W=70,C3W=70,C4W=80;
  int TblW=C0W+C1W+C2W+C3W+C4W+29, H1=40, LSp1=10;
  pSpeedCalibrTtl->Height=H1;
  sgSpeedCalibr->ColWidths[0]=C0W;     sgSpeedCalibr->ColWidths[1]=C1W;
  sgSpeedCalibr->ColWidths[2]=C2W;     sgSpeedCalibr->ColWidths[3]=C3W;
  sgSpeedCalibr->ColWidths[4]=C4W;
  sgSpeedCalibr->Width=TblW;
  sgSpeedCalibr->Cells[0][0]="№";
  sgSpeedCalibr->Cells[1][0]="Задание";
  sgSpeedCalibr->Cells[2][0]="Показание";
  sgSpeedCalibr->Cells[3][0]="Измерение";
  sgSpeedCalibr->Cells[4][0]="Погрешность";
  for (int i = 0; i < VQTY; i++) {
    if(i<9)sgSpeedCalibr->Cells[0][i+1]="  "+String(i+1)+":";
    else   sgSpeedCalibr->Cells[0][i+1]=" "+String(i+1)+":";
    sgSpeedCalibr->Cells[1][i+1]=VS->sTV[i];
    sgSpeedCalibr->Cells[2][i+1]="";
    sgSpeedCalibr->Cells[3][i+1]="";
    sgSpeedCalibr->Cells[4][i+1]="";
  }
  int Top1=H1+LSp1, Left11=TblW+LSp1, LblW1=85, BtnW1=LblW1*3, BtnW2=tsSpeedCalibrW-TblW-BtnW1-LSp1*3;
  int Left12=Left11+LblW1, Left13=Left11+LblW1*2, Left2=Left11+LblW1*3+LSp1, H2=50, H3=26;
  btnPrevCalibrV->Left         =Left11;       btnPrevCalibrV->Top           =Top1;
  btnPrevCalibrV->Width        =BtnW1;        btnPrevCalibrV->Height        =H2;
  btnClearVCalibreTable->Left  =Left2;        btnClearVCalibreTable->Top    =Top1;
  btnClearVCalibreTable->Width =BtnW2;        btnClearVCalibreTable->Height =H2;
  btnCalibrVCalc->Left         =Left2;        btnCalibrVCalc->Top           =Top1+H2+LSp1;
  btnCalibrVCalc->Width        =BtnW2;        btnCalibrVCalc->Height        =H2;
  btnSpdCalibrTablePrint->Left =Left2;        btnSpdCalibrTablePrint->Top   =Top1+H2*2+LSp1*2;
  btnSpdCalibrTablePrint->Width=BtnW2;        btnSpdCalibrTablePrint->Height=H2;
  leCurrentVSet->Left          =Left11;       leCurrentVSet->Top            =Top1+H2*2+LSp1-H3;
  leCurrentVSet->Width         =LblW1;        leCurrentVSet->Height         =H3;
  leReadV->Left                =Left12;       leReadV->Top                  =Top1+H2*2+LSp1-H3;
  leReadV->Width               =LblW1;        leReadV->Height               =H3;
  leMeasuredV->Left            =Left13;       leMeasuredV->Top              =Top1+H2*2+LSp1-H3;
  leMeasuredV->Width           =LblW1;        leMeasuredV->Height           =H3;
  btnNextCalibrV->Left         =Left11;       btnNextCalibrV->Top           =Top1+H2*2+LSp1*2;
  btnNextCalibrV->Width        =BtnW1;        btnNextCalibrV->Height        =H2;
  btnVCalibrDrumOn->Left       =Left11;       btnVCalibrDrumOn->Top         =Top1+H2*3+LSp1*5;
  btnVCalibrDrumOn->Width      =BtnW1;        btnVCalibrDrumOn->Height      =H2;
  btnVCalibrDrumOff->Left      =Left11;       btnVCalibrDrumOff->Top        =Top1+H2*4+LSp1*6;
  btnVCalibrDrumOff->Width     =BtnW1;        btnVCalibrDrumOff->Height     =H2;

  VS->Index=0;
  leCurrentVSet->Text=FloatToStrF(VS->TargetV[0],ffFixed,6,2);
  leReadV->Text      =FloatToStrF(VS->ReadoutV[0],ffFixed,6,2);
  leMeasuredV->Text  =FloatToStrF(VS->MeasuredV[0],ffFixed,6,2);
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=-1;
  sgSpeedCalibr->Selection=myRect;*/
  btnPrevCalibrV->Enabled=false;
  btnNextCalibrV->Enabled= true;
//  LogPrint("CalibrTableVisibleRow="+String(sgSpeedCalibr->VisibleRowCount));
}
//---- End of DesignSpdCalibrPanel ------------------------------------------

void __fastcall TmfRB::ShowCommonParam(void)   // отображение общих параметров
{
// если по поз. 1 идет испытание обрабатывать шаг
	if(CurrSMode1==2)
	{
		if(old_step_1!=cur_step_1)
		{
			old_speed_1=cur_speed_1;
			old_dist_1=cur_dist_1;
			old_time_1=cur_time_1;
			old_load_1=cur_load_1;
			old_radius_1=cur_radius_1;
			old_temp_1=cur_temp_1;
		}
		if(cur_step_1>1)
		{
			if(TyreA->TestMode==0)
			{
				stP2CParL1C1->Caption   =mSecToHMSStr(old_time_1);
				stP2CParL2C1->Caption   =FloatToStrF(old_dist_1,ffFixed,7,2);
				stP2CParL3C1->Caption   =FloatToStrF(old_speed_1,ffFixed,7,2);
				stP2CParL4C1->Caption   =FloatToStrF(old_load_1,ffFixed,7,2);
				stP2CParL5C1->Caption   =FloatToStrF(old_temp_1,ffFixed,5,1);
				stP2CParL6C1->Caption   =FloatToStrF(old_radius_1,ffFixed,5,1);
				stP2CParL7C1->Caption   =mSecToHMSStr(*next_step_time1);
				stP2CParL1C2->Caption   ="";
				stP2CParL2C2->Caption   ="";
				stP2CParL3C2->Caption   ="";
				stP2CParL4C2->Caption   ="";
				stP2CParL5C2->Caption   ="";
				stP2CParL6C2->Caption   ="";
				stP2CParL7C2->Caption   ="";
			}else
			{
				stP2CParL1C1->Caption   ="";
				stP2CParL2C1->Caption   ="";
				stP2CParL3C1->Caption   ="";
				stP2CParL4C1->Caption   ="";
				stP2CParL5C1->Caption   ="";
				stP2CParL6C1->Caption   ="";
				stP2CParL7C1->Caption   ="";
				stP2CParL1C2->Caption   =mSecToHMSStr(old_time_1);
				stP2CParL2C2->Caption   =FloatToStrF(old_dist_1,ffFixed,7,2);
				stP2CParL3C2->Caption   =FloatToStrF(old_speed_1,ffFixed,7,2);
				stP2CParL4C2->Caption   =FloatToStrF(old_load_1,ffFixed,7,2);
				stP2CParL5C2->Caption   =FloatToStrF(old_temp_1,ffFixed,5,1);
				stP2CParL6C2->Caption   =FloatToStrF(old_radius_1,ffFixed,5,1);
				stP2CParL7C2->Caption   =FloatToStrF(*next_step_distance1,ffFixed,7,2);
			}
		}
		old_step_1=cur_step_1;
		if (TyreA->TestMode==0)
		{
			stP1CParL1C3->Caption=mSecToHMSStr(*next_set_time1); // время след шага
		}else
		{
			stP1CParL2C3->Caption=FloatToStrF(*next_set_distance1,ffFixed,7,2);// путь след шага
		}
	}else // нет испытаний по поз.1
	{
		stP2CParL1C1->Caption   ="";
		stP2CParL2C1->Caption   ="";
		stP2CParL3C1->Caption   ="";
		stP2CParL4C1->Caption   ="";
		stP2CParL5C1->Caption   ="";
		stP2CParL6C1->Caption   ="";
		stP2CParL7C1->Caption   ="";
		stP2CParL1C2->Caption   ="";
		stP2CParL2C2->Caption   ="";
		stP2CParL3C2->Caption   ="";
		stP2CParL4C2->Caption   ="";
		stP2CParL5C2->Caption   ="";
		stP2CParL6C2->Caption   ="";
		stP2CParL7C2->Caption   ="";
		stP1CParL2C3->Caption	="";
		stP1CParL1C3->Caption   ="";
	}
// если по поз. 2 идет испытание обрабатывать шаг
  if(CurrSMode2==2)
	{
		if(old_step_2!=cur_step_2)
		{
			old_speed_2=cur_speed_2;
			old_dist_2=cur_dist_2;
			old_time_2=cur_time_2;
			old_load_2=cur_load_2;
			old_radius_2=cur_radius_2;
			old_temp_2=cur_temp_2;
		}
		if(cur_step_2>1)
		{
			if(TyreB->TestMode==0)
			{
				stP2CParL1C3->Caption   =mSecToHMSStr(old_time_2);
				stP2CParL2C3->Caption   =FloatToStrF(old_dist_2,ffFixed,7,2);
				stP2CParL3C3->Caption   =FloatToStrF(old_speed_2,ffFixed,7,2);
				stP2CParL4C3->Caption   =FloatToStrF(old_load_2,ffFixed,7,2);
				stP2CParL5C3->Caption   =FloatToStrF(old_temp_2,ffFixed,5,1);
				stP2CParL6C3->Caption   =FloatToStrF(old_radius_2,ffFixed,5,1);
				stP2CParL7C3->Caption   =mSecToHMSStr(*next_step_time2);
				stP2CParL1C4->Caption   ="";
				stP2CParL2C4->Caption   ="";
				stP2CParL3C4->Caption   ="";
				stP2CParL4C4->Caption   ="";
				stP2CParL5C4->Caption   ="";
				stP2CParL6C4->Caption   ="";
				stP2CParL7C4->Caption   ="";
			}else
			{
				stP2CParL1C3->Caption   ="";
				stP2CParL2C3->Caption   ="";
				stP2CParL3C3->Caption   ="";
				stP2CParL4C3->Caption   ="";
				stP2CParL5C3->Caption   ="";
				stP2CParL6C3->Caption   ="";
				stP2CParL7C3->Caption   ="";
				stP2CParL1C4->Caption   =mSecToHMSStr(old_time_2);
				stP2CParL2C4->Caption   =FloatToStrF(old_dist_2,ffFixed,7,2);
				stP2CParL3C4->Caption   =FloatToStrF(old_speed_2,ffFixed,7,2);
				stP2CParL4C4->Caption   =FloatToStrF(old_load_2,ffFixed,7,2);
				stP2CParL5C4->Caption   =FloatToStrF(old_temp_2,ffFixed,5,1);
				stP2CParL6C4->Caption   =FloatToStrF(old_radius_2,ffFixed,5,1);
				stP2CParL7C4->Caption   =FloatToStrF(*next_step_distance2,ffFixed,7,2);
			}
		}
		old_step_2=cur_step_2;
		if (TyreB->TestMode==0)
		{
			stP1CParL1C6->Caption=mSecToHMSStr(*next_set_time2); // время след шага
		}else
		{
			stP1CParL2C6->Caption=FloatToStrF(*next_set_distance2,ffFixed,7,2);// путь след шага
		}
	}else // нет испытаний по поз.2
	{
		stP2CParL1C3->Caption   ="";
		stP2CParL2C3->Caption   ="";
		stP2CParL3C3->Caption   ="";
		stP2CParL4C3->Caption   ="";
		stP2CParL5C3->Caption   ="";
		stP2CParL6C3->Caption   ="";
		stP2CParL7C3->Caption   ="";
		stP2CParL1C4->Caption   ="";
		stP2CParL2C4->Caption   ="";
		stP2CParL3C4->Caption   ="";
		stP2CParL4C4->Caption   ="";
		stP2CParL5C4->Caption   ="";
		stP2CParL6C4->Caption   ="";
		stP2CParL7C4->Caption   ="";
		stP1CParL2C6->Caption   ="";
		stP1CParL1C6->Caption   ="";
	}

// вывод в файл журнала:
//  LogPrintF(LogFName()," Текущая скорость="+FloatToStrF(*fakt_speed,ffFixed,7,2));
// отображение на вкладке "ТЕКУЩЕЕ СОСТОЯНИЕ"
  if(pcRB->ActivePage==tsCurrentStatus){
    stP1CurDate->Caption        =Now().DateTimeString();
    if(TyreA->TestMode==0)
      stP1CParL1C1->Caption     =mSecToHMSStr(*T_end_cycle_1);
    else
      stP1CParL1C1->Caption     ="";
    if(TyreB->TestMode==0)
      stP1CParL1C4->Caption     =mSecToHMSStr(*T_end_cycle_2);
    else
      stP1CParL1C4->Caption     ="";
    stP1CParL1C2->Caption       =mSecToHMSStr(*fakt_time_1);
    stP1CParL1C5->Caption       =mSecToHMSStr(*fakt_time_2);
    if(TyreA->TestMode==1)
      stP1CParL2C1->Caption     =FloatToStrF(*S_end_cycle_1,ffFixed,7,2);
    else
      stP1CParL2C1->Caption     ="";
    if(TyreB->TestMode==1)
      stP1CParL2C4->Caption     =FloatToStrF(*S_end_cycle_2,ffFixed,7,2);
    else
      stP1CParL2C4->Caption     ="";
    stP1CParL2C2->Caption       =FloatToStrF(*fakt_distance_1,ffFixed,7,2);
    stP1CParL2C5->Caption       =FloatToStrF(*fakt_distance_2,ffFixed,7,2);
    stP1CParL3C1->Caption       =FloatToStrF(*set_speed_1,ffFixed,7,2);
    stP1CParL3C4->Caption       =FloatToStrF(*set_speed_2,ffFixed,7,2);
	stP1CParL3C2->Caption       =FloatToStrF(*fakt_speed,ffFixed,7,2);
	stP1CParL3C5->Caption       =FloatToStrF(*fakt_speed,ffFixed,7,2);
    stP1CParL3C3->Caption       =FloatToStrF(*next_speed1,ffFixed,7,2);
    stP1CParL3C6->Caption       =FloatToStrF(*next_speed2,ffFixed,7,2);
    stP1CParL4C1->Caption       =FloatToStrF(*set_loading_1,ffFixed,7,2);
    stP1CParL4C4->Caption       =FloatToStrF(*set_loading_2,ffFixed,7,2);
    stP1CParL4C2->Caption       =FloatToStrF(*fakt_loading_1,ffFixed,7,2);
    stP1CParL4C5->Caption       =FloatToStrF(*fakt_loading_2,ffFixed,7,2);
    stP1CParL4C3->Caption       =FloatToStrF(*next_loading1,ffFixed,7,2);
    stP1CParL4C6->Caption       =FloatToStrF(*next_loading2,ffFixed,7,2);
    stP1CParL6C2->Caption       =FloatToStrF(*fakt_temper_1,ffFixed,5,1);
	stP1CParL6C5->Caption       =FloatToStrF(*fakt_temper_2,ffFixed,5,1);
    stP1CParL7C2->Caption       =FloatToStrF(*fakt_radius_1,ffFixed,5,1);
    stP1CParL7C5->Caption       =FloatToStrF(*fakt_radius_2,ffFixed,5,1);
    stP1CParL8C1->Caption       =String(*step_change_1);
    stP1CParL8C4->Caption       =String(*step_change_2);
    stP1CParL8C3->Caption       =String(*next_step_change1);
	stP1CParL8C6->Caption       =String(*next_step_change2);
  }
// отображение на вкладке "РУЧНОЙ РЕЖИМ"
  if(pcRB->ActivePage==tsManual){
    leCurrentDrumSpeed->Text    =FloatToStrF(*fakt_speed,ffFixed,6,2);
    tbCurrentDrumSpeed->Position=tbCurrentDrumSpeed->Max-int(*fakt_speed);
    leCurrentLoad1->Text        =FloatToStrF(*fakt_loading_1,ffFixed,7,2);
    tbCurrentLoad1->Position    =tbCurrentLoad1->Max-int(*fakt_loading_1);
    leCurrentLoad2->Text        =FloatToStrF(*fakt_loading_2,ffFixed,7,2);
    tbCurrentLoad2->Position    =tbCurrentLoad2->Max-int(*fakt_loading_2);
    leCurrentT1->Text           =FloatToStrF(*fakt_temper_1,ffFixed,5,1);
    leCurrentT2->Text           =FloatToStrF(*fakt_temper_2,ffFixed,5,1);
    leCurrentR1->Text           =FloatToStrF(*fakt_radius_1,ffFixed,5,1);
    leCurrentR2->Text           =FloatToStrF(*fakt_radius_2,ffFixed,5,1);
  }
// отображение на вкладке "АТТЕСТАЦИЯ"
  if(pcRB->ActivePage==tsCalibration){
    if(pcCalibration->ActivePage==tsSpeedCalibr){
      /*if(*DrumOn)*/leReadV->Text=FloatToStrF(*fakt_speed,ffFixed,6,2);
	  //else       leReadV->Text="0.0";
    }
    else if(pcCalibration->ActivePage==tsLoadCalibr) {
	  /*if(*KeepLoad1)*/leReadLoadA->Text=FloatToStrF(*fakt_loading_1,ffFixed,6,2);
	  //else          leReadLoadA->Text="0.0";
	  /*if(*KeepLoad2)*/leReadLoadB->Text=FloatToStrF(*fakt_loading_2,ffFixed,6,2);
	  //else          leReadLoadB->Text="0.0";
    }
    else if(pcCalibration->ActivePage==tsRadiusCalibr) {
	  leReadRA->Text=FloatToStrF(*fakt_radius_1,ffFixed,6,2); //
	  leReadRB->Text=FloatToStrF(*fakt_radius_2,ffFixed,6,2); //
	}
	else if(pcCalibration->ActivePage==tsTempCalibr) {
	  leReadTA->Text=FloatToStrF(*fakt_temper_1,ffFixed,6,2); //
      leReadTB->Text=FloatToStrF(*fakt_temper_2,ffFixed,6,2); //
    }
  }
// отображение на вкладке "КАЛИБРОВКА"
  if(pcRB->ActivePage==tsSert){
	if(pcSert->ActivePage==tsLoadSert){
	  /*if(*KeepLoad1)*/leReadLoadSertA->Text=FloatToStrF(*fakt_loading_1,ffFixed,6,2);
	  //else          leReadLoadSertA->Text="0.0";
	  /*if(*KeepLoad2)*/leReadLoadSertB->Text=FloatToStrF(*fakt_loading_2,ffFixed,6,2);
	  //else          leReadLoadSertB->Text="0.0";
	}
	if (pcSert->ActivePage==tsDrumSpeedSert)
	{
		leMeasSpeedCoefReal->Text=FloatToStrF(*CorrAMeasSpeed,ffFixed,4,3);
		leSetSpeedCoefReal->Text=FloatToStrF(*CorrASetSpeed,ffFixed,4,3);
	}
  }
// отображение на вкладке "Программа испытаний"
	if (pcRB->ActivePage==tsManual)
	{
		if (!leSetLoad1->Focused())
		{
			tbCurrentLoad1->SelEnd  =tbCurrentLoad1->Max-int(*ReadLoading_1);
			tbCurrentLoad1->SelStart=tbCurrentLoad1->Max-int(*ReadLoading_1);
			leSetLoad1->Text=FloatToStrF(*ReadLoading_1,ffFixed,5,2);
		}
		if (!leSetLoad2->Focused())
		{
			tbCurrentLoad2->SelEnd  =tbCurrentLoad2->Max-int(*ReadLoading_2);
			tbCurrentLoad2->SelStart=tbCurrentLoad2->Max-int(*ReadLoading_2);
			leSetLoad2->Text=FloatToStrF(*ReadLoading_2,ffFixed,5,2);
		}
	}
//аварийные установки
	if (pcRB->ActivePage==tsEmSettings)
	{
		leEmMaxLoad_1->Text=FloatToStrF(*max_load_1,ffFixed,5,1);
		leEmMaxLoad_2->Text=FloatToStrF(*max_load_2,ffFixed,5,1);
		leEmMaxSpeed->Text=FloatToStrF(*max_speed,ffFixed,5,1);
		leEmMinSpeed->Text=FloatToStrF(*min_speed,ffFixed,5,1);
		leEmMinLoad_1->Text=FloatToStrF(*min_load_1,ffFixed,5,1);
		leEmMinLoad_2->Text=FloatToStrF(*min_load_2,ffFixed,5,1);

		leEmMinTemp_1->Text=FloatToStrF(*min_temp_1,ffFixed,5,1);
		leEmMinTemp_2->Text=FloatToStrF(*min_temp_2,ffFixed,5,1);

		leEmMaxTemp_1->Text=FloatToStrF(*max_temp_1,ffFixed,5,1);
		leEmMaxTemp_2->Text=FloatToStrF(*max_temp_2,ffFixed,5,1);
	}
}
//---- End of ShowCommonParam -----------------------------------------------
void __fastcall TmfRB::onOPCControlStartExec(TObject *Sender)
{
	OPCControlStartExec();
	if (!cd_9904->Sensor())
	{
		try
		{
			cd_9904->Connect();
			if (!cd_9904->Sensor())
			{
				StendConnection=false;
				LogPrintF(LogFName(),"Ошибка соединения со спидометром ",clYellow); ////вставлена проверка соединения с датчиком
				MessageBoxW(Handle,L"Ошибка соединения со спидометром ",L"Ошибка соединения со спидометром",MB_OK|MB_ICONERROR|MB_DEFBUTTON1);
			}
		} catch (...)
		{
			StendConnection=false;
			LogPrintF(LogFName(),"Ошибка соединения со спидометром ",clYellow); ////вставлена проверка соединения с датчиком
			MessageBoxW(Handle,L"Ошибка соединения со спидометром ",L"Ошибка соединения со спидометром",MB_OK|MB_ICONERROR|MB_DEFBUTTON1);
		}

	}
	if (!CD_9904Thread)
	{
		if (cd_9904->Sensor())
		{
			CD_9904Thread=CreateThread(NULL,0,ListenCD9904,0,0,NULL);//включается прослушка
		}else
		{
        	StendConnection=false;
		}
	}else
	{
		ResumeThread(CD_9904Thread);
	}
}
void __fastcall TmfRB::OPCControlStartExec(void)
{ static OPCNewOK=true;
  LogPrintF(LogFName(),"Старт управления стендом");
  if(OPCNewOK) {
	pOPC = new OPCRW;
	OPCNewOK=false;
  }
  if(OPCConnectOK && !OPCControlOn){
    sbRB->Panels->Items[0]->Text="Соединение со стендом установлено";
    // прочитать состояние и установить состояние на панели
	pOPC->ReadGr1();
	pOPC->ReadGr2();
    pOPC->ReadGr3();
    // определение и печать текущих режимов
    old_step_1=*step_write_1;
    old_step_2=*step_write_2;
    CurrMode1=BUnion(*AutoMode1,*ManualMode1);
    CurrMode2=BUnion(*AutoMode2,*ManualMode2);
    CurrSMode1=BUnion(*Start1,*Stop1);
    CurrSMode2=BUnion(*Start2,*Stop2);
    LogPrintF(LogFName(),"First CurrMode1="+String(CurrMode1),clSkyBlue);
    LogPrintF(LogFName(),"First CurrMode2="+String(CurrMode2),clSkyBlue);
    LogPrintF(LogFName(),"First CurrSMode1="+String(CurrSMode1),clSkyBlue);
    LogPrintF(LogFName(),"First CurrSMode2="+String(CurrSMode2),clSkyBlue);
    LogPrintF(LogFName(),"First Auto1: "+BoolToStr(*AutoMode1,true)+
	  ", Man1: "+BoolToStr(*ManualMode1,true),clSkyBlue);
    LogPrintF(LogFName(),"First Start1: "+BoolToStr(*Start1,true)+
      ", Stop1: "+BoolToStr(*Stop1,true),clSkyBlue);
    LogPrintF(LogFName(),"First Auto2: "+BoolToStr(*AutoMode2,true)+
	  ", Man2: "+BoolToStr(*ManualMode2,true),clSkyBlue);
    LogPrintF(LogFName(),"First Start2: "+BoolToStr(*Start2,true)+
      ", Stop2: "+BoolToStr(*Stop2,true),clSkyBlue);
    // запрещение обработчика кнопок
	//Handle1On=false;
    //Handle2On=false;
    // обработка считанных режимов, в случае недопустимой комбинации - их изменение
    if((*AutoMode1 && *ManualMode1) || (!*AutoMode1 && !*ManualMode1)){
      *AutoMode1=false; *ManualMode1= true;
	  *Start1   =false; *Stop1      = true;
      pOPC->BenchControl(AutoMode1,ManualMode1);
      pOPC->BenchControl(Start1,Stop1);
	}
    if((*AutoMode2 && *ManualMode2) || (!*AutoMode2 && !*ManualMode2)){
      *AutoMode2=false; *ManualMode2= true;
	  *Start2   =false; *Stop2      = true;
      pOPC->BenchControl(AutoMode2,ManualMode2);
      pOPC->BenchControl(Start2,Stop2);
	}
    // печать текущих режимов
    if(*AutoMode1)LogPrintF(LogFName(),"Поз. А в автоматическом режиме!",clWhite);
    else          LogPrintF(LogFName(),"Поз. А в ручном режиме!",clWhite);
    if(*Start1)   LogPrintF(LogFName(),"Поз. А в режиме Старт!",clWhite);
    else          LogPrintF(LogFName(),"Поз. А в режиме Стоп!",clWhite);
    if(*AutoMode2)LogPrintF(LogFName(),"Поз. Б в автоматическом режиме!",clWhite);
    else          LogPrintF(LogFName(),"Поз. Б в ручном режиме!",clWhite);
    if(*Start2)   LogPrintF(LogFName(),"Поз. Б в режиме Старт!",clWhite);
    else          LogPrintF(LogFName(),"Поз. Б в режиме Стоп!",clWhite);
    // сохранение текущих режимов
    OldMode1=CurrMode1;
    OldMode2=CurrMode2;
    OldSMode1=CurrSMode1;
    OldSMode2=CurrSMode2;
    // отображение состояния и текущих параметров
	ShowStatus(false);
    ShowCommonParam();
    // запуск цикла опроса
    OPCControlStart(tReadCycleTimer);
	OPCControlOn=true;
    // разрешение обработчиков
	//Handle1On=true;
	//Handle2On=true;
  }
  else if (OPCConnectOK && OPCControlOn) {
	sbRB->Panels->Items[2]->Text="Control alredy ON!";
  }
  else {
    LogPrintF(LogFName(),"Ошибка соединения со стендом",clRed);
	sbRB->Panels->Items[0]->Text="Ошибка соединения со стендом";
	MessageBoxW(Handle,L"Ошибка соединения со стендом",L"Ошибка соединения со стендом",MB_OK|MB_ICONERROR|MB_DEFBUTTON1);
  }
}
void   			TmfRB::CheckStend(void)
{
	if (!cd_9904->Sensor())
	{//соединение со спидометром
		try
		{
			cd_9904->Connect();
			if (!cd_9904->Sensor())
			{
				StendConnection=false;
				LogPrintF(LogFName(),"Ошибка соединения со спидометром ",clYellow); ////вставлена проверка соединения с датчиком
			   //	MessageBoxW(Handle,L"Ошибка соединения со спидометром ",L"Ошибка соединения со спидометром",MB_OK|MB_ICONERROR|MB_DEFBUTTON1);
			}
		} catch (...)
		{//сбой при попытке подключения
			StendConnection=false;
			LogPrintF(LogFName(),"Ошибка соединения со спидометром ",clYellow); ////вставлена проверка соединения с датчиком
		   //	MessageBoxW(Handle,L"Ошибка соединения со спидометром ",L"Ошибка соединения со спидометром",MB_OK|MB_ICONERROR|MB_DEFBUTTON1);
		}
	}
	if (!CD_9904Thread)
	{
		if (cd_9904->Sensor())
		{
			CD_9904Thread=CreateThread(NULL,0,ListenCD9904,0,0,NULL);//включается прослушка
		}else
		{
        	StendConnection=false;
		}

	}else
	{
		ResumeThread(CD_9904Thread);
	}
	if (!(OPCConnectOK&&OPCControlOn))
	{//соединение со стендом
		OPCControlStartExec();
	}
}
//---- End of OnOPCControlStartExec -----------------------------------------
void __fastcall TmfRB::ShowStatus(bool save)        // отображение состояния на панелях
{
	sbRB->Panels->Items[3]->Text=Now().DateTimeString();
	// определение текущих режимов
	CurrMode1=BUnion(*AutoMode1,*ManualMode1);
	CurrMode2=BUnion(*AutoMode2,*ManualMode2);
	CurrSMode1=BUnion(*Start1,*Stop1);
	CurrSMode2=BUnion(*Start2,*Stop2);
	// печать в случае изменения режима
	if(CurrMode1!=OldMode1)
	{
		LogPrintF(	LogFName(),"Auto1: "+BoolToStr(*AutoMode1,true)+
					", Man1: "+BoolToStr(*ManualMode1,true));
		if(*AutoMode1)
			sbRB->Panels->Items[2]->Text="Поз. А в автоматическом режиме!";
		else
			sbRB->Panels->Items[2]->Text="Поз. А в ручном режиме!";
	}
	if(CurrSMode1!=OldSMode1)
	{
		LogPrintF(	LogFName(),"Start1: "+BoolToStr(*Start1,true)+
					", Stop1: "+BoolToStr(*Stop1,true));
		if(*Start1)
			sbRB->Panels->Items[2]->Text="Старт поз. А!";
		else
			sbRB->Panels->Items[2]->Text="Стоп поз. А!";
	}
	if(CurrMode2!=OldMode2)
	{
		LogPrintF(	LogFName(),"Auto2: "+BoolToStr(*AutoMode2,true)+
					", Man2: "+BoolToStr(*ManualMode2,true));
		if(*AutoMode2)
			sbRB->Panels->Items[2]->Text="Поз. Б в автоматическом режиме!";
		else
			sbRB->Panels->Items[2]->Text="Поз. Б в ручном режиме!";
	}
	if(CurrSMode2!=OldSMode2)
	{
		LogPrintF(	LogFName(),"Start2: "+BoolToStr(*Start2,true)+
					", Stop2: "+BoolToStr(*Stop2,true));
		if(*Start2)
			sbRB->Panels->Items[2]->Text="Старт поз. Б!";
		else
			sbRB->Panels->Items[2]->Text="Стоп поз. Б!";
	}

	sbManualA->Down=*ManualMode1;
	sbAutomatA->Down=*AutoMode1 ;
	rgPos1StartStop->Enabled=*AutoMode1;
	sbStartA->Enabled=*AutoMode1;
	sbStopA->Enabled=*AutoMode1;
	sbStartA->Down=*Start1;
	sbStopA->Down=*Stop1;
	cbControlLateralA->Checked=*ControlLateralA;
	if (*Stop1&&needSaveA&&save)
	{
        TyreA->Stop = Now();
		btnLoadTestResPosA->Click();  //авто сохраниние
	}

	sbManualB->Down=*ManualMode2;
	sbAutomatB->Down=*AutoMode2 ;
	rgPos2StartStop->Enabled=*AutoMode2;
	sbStartB->Enabled=*AutoMode2;
	sbStopB->Enabled=*AutoMode2;
	sbStartB->Down=*Start2;
	sbStopB->Down=*Stop2;
	cbControlLateralB->Checked=*ControlLateralB;
	if (*Stop2&&needSaveB&&save)
	{
        TyreB->Stop = Now();
		btnLoadTestResPosB->Click();  //авто сохраниние
	}
	// обработка остальных индикаторов

	sbCarr1Fm->Down     =*Carriage1From;
	sbCarr1To->Down     =*Carriage1To;
	sbCarr2Fm->Down     =*Carriage2From;
	sbCarr2To->Down     =*Carriage2To;
	sbDrumOn->Down      =*DrumOn;

	SetIndication(IndBlowout1,!*Blowout1);
	SetIndication(IndBlowout2,!*Blowout2);
	SetIndication(IndGuardrail1,*GuardRail1);
	SetIndication(IndGuardrail2,*GuardRail2);
	static bool oldBlowout1=*Blowout1,oldBlowout2=*Blowout2;//инициализация тем что пришло с контроллера
	if (*Blowout1==true&&oldBlowout1!=*Blowout1)//произошол разрыв
	{
		String msg="Разрыв в позиции А";
		if (*DestroyLateral1)
		{
			msg="Разрыв боковой в позиции А";
		}
		if (*DestroyRunning1)
		{
        	msg="Разрыв беговой в позиции А";
		}
		sbRB->Panels->Items[2]->Text=msg;
		LogPrint(Now().TimeString()+"--"+msg,clRed);
	}
	if (*Blowout2==true&&oldBlowout2!=*Blowout2)//произошол разрыв
	{
		String msg="Разрыв в позиции Б";
		if (*DestroyLateral2)
		{
			msg="Разрыв боковой в позиции Б";
		}
		if (*DestroyRunning2)
		{
			msg="Разрыв беговой в позиции Б";
		}
		sbRB->Panels->Items[2]->Text=msg;
		LogPrint(Now().TimeString()+"--"+msg,clRed);
	}
	oldBlowout1=*Blowout1;
	oldBlowout2=*Blowout2;
	SetIndication(IndDestroyLateral1,!*DestroyLateral1);
	SetIndication(IndDestroyLateral2,!*DestroyLateral2);
	SetIndication(IndDestroyRunning1,!*DestroyRunning1);
	SetIndication(IndDestroyRunning2,!*DestroyRunning2);

	SetIndication(IndOilLvl,*OilLvl);
	SetIndication(IndlOilFilter,*OilFilter);
	SetIndication(IndDriveDrum,*ElDriveDrum);

	eOilTemp->Text=FloatToStrF(*OilTemp,ffGeneral,3,3);
	if (*OilTemp<LOWTEMP)
	{
		eOilTemp->Color=clSkyBlue;
	}else
	if (*OilTemp>HIGHTTEMP)
	{
		eOilTemp->Color=clRed;
	}else
	{
		eOilTemp->Color=clGreen;
	}

	static bool oldstate=false;
	SetIndication(eStendConnection,StendConnection);
	if (oldstate!=StendConnection)//запись в логах изменения состояния
	{
		if (StendConnection)
		{//соединение установлено
			LogPrintF(LogFName(),"Соединение со стендом установлено",clRed);
		}else
		{//соединение потеряно
			LogPrintF(LogFName(),"Соединение со стендом потеряно",clRed);
		}
	}
	oldstate=StendConnection;//запоминание текущего состояния связи


	if (!sbCarriage1Off->Down&&*Carriage1Off&&!switch_Carriage1)
	{
		sbRB->Panels->Items[2]->Text="Каретка А в исходном положении!";
		LogPrintF(LogFName(),"Каретка А в исходном положении!",clWhite);
	}
	sbCarriage1Off->Down=*Carriage1Off;
	switch_Carriage1=*Carriage1Off;

	if (!sbCarriage2Off->Down&&*Carriage2Off&&!switch_Carriage2)
	{
		sbRB->Panels->Items[2]->Text="Каретка Б в исходном положении!";
		LogPrintF(LogFName(),"Каретка Б в исходном положении!",clWhite);
	}
	sbCarriage2Off->Down=*Carriage2Off;
	switch_Carriage2=*Carriage2Off;
	// сохранение режимов
	OldMode1=CurrMode1;
	OldMode2=CurrMode2;
	OldSMode1=CurrSMode1;
	OldSMode2=CurrSMode2;

    static bool over_load1(false);
    static bool over_load2(false);

    if (*OverLoad1 != over_load1)
    {
        if (*OverLoad1)
        {
            sbRB->Panels->Items[2]->Text="Превышение нагрузки на шаге на стороне 1";
            LogPrintF(LogFName(),"Превышение нагрузки на шаге на стороне 1",clYellow);
            ShowMessage("Превышение нагрузки на шаге на стороне 1");
        }
        over_load1 = *OverLoad1;
    }

    if (*OverLoad2 != over_load2)
    {
        if (*OverLoad2)
        {
            sbRB->Panels->Items[2]->Text="Превышение нагрузки на шаге на стороне 2";
            LogPrintF(LogFName(),"Превышение нагрузки на шаге на стороне 2",clYellow);
            ShowMessage("Превышение нагрузки на шаге на стороне 2");
        }
        over_load2 = *OverLoad2;
    }
}
//---- End of ShowStatus ----------------------------------------------------

void __fastcall TmfRB::OnOPCControlStopExec(TObject *Sender)
{
  LogPrintF(LogFName(),"OPC Control OFF!",clAqua);
  OPCControlOn=false;
  OPCControlStop(tReadCycleTimer);
  sbRB->Panels->Items[0]->Text="Соединения со стендом нет";
}
//---- End of OnOPCControlStopExec ------------------------------------------

void __fastcall TmfRB::OnLogPrint(TMessage& wm)  // обработчик сообщений печати в окне протокола
{
  LogPrint(LogMess,(TColor)wm.LParam);
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnDataShow(TMessage& wm)   // обработчик сообщений отображения данных
// WParam - номер строки сообщений, LParam - номер поля в строке сообщений
{
  switch(wm.WParam)
	{case COMMONPRMSHOW:
	   ShowCommonParam();
	   break;
	 default:
       ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnOPCCmd(TMessage& wm)     // обработчик сообщений-команд для запросов к OPC-серверу
{ LogPrint("OnOPCCmd procedure!",clOlive);
  switch(wm.WParam)
	{case READGR1:
       if(pOPC->ReadGr1() && pOPC->ReadGr2())ShowStatus();
       else {
         LogMess="ReadGr1 error!";
         SendMessage(MainFormHandle,WM_LogPrint,0,(long)clRed);
       }
       break;
     case WRITEGR1ITEM:
         *Stop1=!*Stop1;
         pOPC->WriteGr1(Stop1);
       break;
	 default:
       ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnReadCycleTimer(TObject *Sender)
{
	static int connection_try=0;
	if (!StendConnection)
	{
		connection_try++;
		tReadCycleTimer->Interval=connection_try>3?30000:1000;
		CheckStend();
		Application->ProcessMessages();
	}else
	{
		connection_try=0;
		tReadCycleTimer->Interval=1000;
	}
	if (StendConnection)
	{
		pOPC->ReadCycleParameters();
		sbRB->Panels->Items[1]->Text="Cnt="+String(NextCycleCount());
		if(CurrSMode1==2)
		{
			cur_speed_1=*fakt_speed;
			cur_dist_1=*fakt_distance_1;
			cur_time_1=*fakt_time_1;
			cur_load_1=*fakt_loading_1;
			cur_radius_1=*fakt_radius_1;
			cur_temp_1=*fakt_temper_1;
			cur_step_1=*step_write_1;
		}

		if(CurrSMode2==2)
		{
			cur_speed_2=*fakt_speed;
			cur_dist_2=*fakt_distance_2;
			cur_time_2=*fakt_time_2;
			cur_load_2=*fakt_loading_2;
			cur_radius_2=*fakt_radius_2;
			cur_temp_2=*fakt_temper_2;
			cur_step_2=*step_write_2;
		}

		ShowStatus();
		ShowCommonParam();
		#ifdef _DEBUG
		TreadCounter->Caption=String(ThreadCounter);
		#endif
	}
}
void			TmfRB::ClearStepVals1(void)
{
	cur_speed_1=0.0;
	cur_dist_1=0.0;
	cur_time_1=0.0;
	cur_load_1=0.0;
	cur_radius_1=0.0;
	cur_temp_1=0.0;
	cur_step_1=0;

	old_step_1=0;
	old_speed_1=0.0;
	old_dist_1=0.0;
	old_time_1=0.0;
	old_load_1=0.0;
	old_radius_1=0.0;
	old_temp_1=0.0;
}
void		   	TmfRB::ClearStepVals2(void)
{
	cur_speed_2=0.0;
	cur_dist_2=0.0;
	cur_time_2=0.0;
	cur_load_2=0.0;
	cur_radius_2=0.0;
	cur_temp_2=0.0;
	cur_step_2=0;

	old_step_2=0;
	old_speed_2=0.0;
	old_dist_2=0.0;
	old_time_2=0.0;
	old_load_2=0.0;
	old_radius_2=0.0;
	old_temp_2=0.0;
}
//---- End of OnReadCycleTimer ----------------------------------------------

void __fastcall TmfRB::OnRGPos1ModeClick(TObject *Sender)
{
	CheckStend();
	if(OPCConnectOK)
	{
		if(sbAutomatA->Down&&!sbManualA->Down)
		{
			*AutoMode1= true; *ManualMode1=false;
			sbRB->Panels->Items[2]->Text="Поз. А в автоматическом режиме!";
			LogPrintF(LogFName(),"Поз. А в автоматическом режиме!",clWhite);
		}
		else
		{
			*AutoMode1=false; *ManualMode1= true;
			sbRB->Panels->Items[2]->Text="Поз. А в ручном режиме!";
			LogPrintF(LogFName(),"Поз. А в ручном режиме!",clWhite);
		}
		OPCControlPause(tReadCycleTimer);
		pOPC->BenchControl(AutoMode1,ManualMode1);
		OPCControlResume(tReadCycleTimer);
	}
	else
	{
		sbAutomatA->Down=false;
		sbManualA->Down=true;
		*AutoMode1=false; *ManualMode1= true;
		sbRB->Panels->Items[2]->Text="Нельзя выдать команду - нет соединения со стендом!";
	}
}
//---- End of OnRGPos1ModeClick ---------------------------------------------

void __fastcall TmfRB::OnRGPos1StartStopClick(TObject *Sender)
{
	CheckStend();
	if(OPCConnectOK)
	{
		if(sbStartA->Down&&!sbStopA->Down)
		{
			*Start1= true; *Stop1=false;
			needSaveA=true;
			ClearStepVals1();
			UpdateProgData();
			if ( TyreA->Start == TDateTime() )
				TyreA->Start = Now();
			TyreA->Stop = TDateTime();
			sbRB->Panels->Items[2]->Text="Старт поз. А!";
			LogPrintF(LogFName(),"Старт поз. А!",clWhite);
		}
		else
		{
			*Start1=false; *Stop1= true;
			if (needSaveA)
			{
				TyreA->Stop = Now();
				btnLoadTestResPosA->Click();  //авто сохраниние
			}
			sbRB->Panels->Items[2]->Text="Стоп поз. А!";
			LogPrintF(LogFName(),"Стоп поз. А!",clWhite);
		}
		OPCControlPause(tReadCycleTimer);
		pOPC->BenchControl(Start1,Stop1);
		OPCControlResume(tReadCycleTimer);
	}
	else
	{
		sbStartA->Down=false;
		sbStopA->Down=true;
		*Start1=false; *Stop1= true;
		sbRB->Panels->Items[2]->Text="Нельзя выдать команду - нет соединения со стендом!";
	}
}
//---- End of OnRGPos1StartStopClick ----------------------------------------
void __fastcall TmfRB::cbControlLateralAClick(TObject *Sender)
{//вкл/выкл контроля бокового разрыва поз А
	*ControlLateralA=cbControlLateralA->Checked;
	pOPC->WriteGr1(ControlLateralA);
}

void __fastcall TmfRB::OnRGPos2ModeClick(TObject *Sender)
{
	CheckStend();
	if(OPCConnectOK)
	{
		if(sbAutomatB->Down&&!sbManualB->Down)
		{
			*AutoMode2= true; *ManualMode2=false;
			sbRB->Panels->Items[2]->Text="Поз. Б в автоматическом режиме!";
			LogPrintF(LogFName(),"Поз. Б в автоматическом режиме!",clWhite);
		}
		else
		{
			*AutoMode2=false; *ManualMode2= true;
			sbRB->Panels->Items[2]->Text="Поз. Б в ручном режиме!";
			LogPrintF(LogFName(),"Поз. Б в ручном режиме!",clWhite);
		}
		OPCControlPause(tReadCycleTimer);
		pOPC->BenchControl(AutoMode2,ManualMode2);
		OPCControlResume(tReadCycleTimer);
	}
	else
	{
		sbAutomatB->Down=false;
		sbManualB->Down=true;
		*AutoMode2=false; *ManualMode2= true;
		sbRB->Panels->Items[2]->Text="Нельзя выдать команду - нет соединения со стендом!";
	}
}
//---- End of OnRGPos2ModeClick ---------------------------------------------

void __fastcall TmfRB::OnRGPos2StartStopClick(TObject *Sender)
{
	CheckStend();
	if(OPCConnectOK)
	{
		if(sbStartB->Down&&!sbStopB->Down)
		{
			*Start2= true; *Stop2=false;
			needSaveB=true;
			ClearStepVals2();
			UpdateProgData();
			if ( TyreB->Start == TDateTime() )
            	TyreB->Start = Now();
            TyreB->Stop = TDateTime();
			sbRB->Panels->Items[2]->Text="Старт поз. Б!";
			LogPrintF(LogFName(),"Старт поз. Б!",clWhite);
		}
		else
		{
			*Start2=false; *Stop2= true;
			if (needSaveB)
			{
                TyreB->Stop = Now();
				btnLoadTestResPosB->Click();  //авто сохраниние
			}
			sbRB->Panels->Items[2]->Text="Стоп поз. Б!";
			LogPrintF(LogFName(),"Стоп поз. Б!",clWhite);
		}
		OPCControlPause(tReadCycleTimer);
		pOPC->BenchControl(Start2,Stop2);
		OPCControlResume(tReadCycleTimer);
	}
	else
	{
		sbStartB->Down=false;
		sbStopB->Down=true;
		*Start2=false; *Stop2= true;
		sbRB->Panels->Items[2]->Text="Нельзя выдать команду - нет соединения со стендом!";
	}
}
//---- End of OnRGPos2StartStopClick ----------------------------------------
void __fastcall TmfRB::cbControlLateralBClick(TObject *Sender)
{//вкл/выкл контроля бокового разрыва поз Б
	*ControlLateralB=cbControlLateralB->Checked;
	pOPC->WriteGr1(ControlLateralB);
}

void __fastcall TmfRB::OnDrumOn(TObject *Sender)
{
  CheckStend();
  if(OPCConnectOK){
	if(*ManualMode1 && *ManualMode2){
	  *DrumOn=true; *DrumOff=false;
	  if(pcRB->ActivePage==tsManual){
		double t=leSetDrumSpeed->Text.Trim().ToDouble();
		if (CheckSpeed(t))
		{
			*DrumSpeed=t;
		}else
		{
			MessageBox(Handle,_T("Значение скорости должно быть в пределах от MIN_SPEED до MAX_SPEED"),_T("Ошибка"),MB_ICONERROR|MB_OK);
			return;
		}

        tbCurrentDrumSpeed->SelEnd  =tbCurrentDrumSpeed->Max-int(*DrumSpeed);
		tbCurrentDrumSpeed->SelStart=tbCurrentDrumSpeed->Max-int(*DrumSpeed);
//        LogPrint("Mode: Manual, DrumSpeed="+FloatToStr(*DrumSpeed));
      }
      if(pcRB->ActivePage==tsCalibration){
        if(pcCalibration->ActivePage==tsSpeedCalibr){
          *DrumSpeed=VS->TargetV[VS->Index];
//          LogPrint("Mode: SpeedCalibr, DrumSpeed="+FloatToStr(*DrumSpeed));
        }
      }
      OPCControlPause(tReadCycleTimer);
	  pOPC->BenchControl(DrumOn,DrumOff,DrumSpeed);
	  OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Барабан включен!";
	  LogPrintF(LogFName(),"Барабан включен");
    }
    else {
      sbRB->Panels->Items[2]->Text="Барабан не включен - стенд не в ручном режиме!";
    }
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя включить барабан - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnDrumOff(TObject *Sender)
{
 CheckStend();
 if(OPCConnectOK){
    if(*ManualMode1 && *ManualMode2){
      *DrumOn=false; *DrumOff=true;
      OPCControlPause(tReadCycleTimer);
      pOPC->BenchControl(DrumOn,DrumOff);
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Барабан выключен!";
	  LogPrintF(LogFName(),"Барабан выключен");
    }
    else {
      sbRB->Panels->Items[2]->Text="Барабан не выключен - стенд не в ручном режиме!";
    }
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя выключить барабан - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnCarriage1To(TObject *Sender)
{
  CheckStend();
  if(OPCConnectOK){
	if(*ManualMode1){
		double t=leSetLoad1->Text.Trim().ToDouble();
		if (CheckLoad(t))
		{
			*Loading_1=t;
		}else
		{
            MessageBox(Handle,_T("Значение нагрузки должно быть в пределах от 0 до 115"),_T("Ошибка"),MB_ICONERROR|MB_OK);
			return;
		}
      tbCurrentLoad1->SelEnd  =tbCurrentLoad1->Max-int(*Loading_1);
      tbCurrentLoad1->SelStart=tbCurrentLoad1->Max-int(*Loading_1);
      *Carriage1To=true; *Carriage1From=false;
      sbCarr1Fm->Down     =*Carriage1From;
      sbCarr1To->Down     =*Carriage1To;
      OPCControlPause(tReadCycleTimer);
      pOPC->BenchControl(Carriage1From,Carriage1To,Loading_1);
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Каретка А движется к барабану!";
      LogPrintF(LogFName(),"Ручной режим, каретка 1 к барабану, установлена нагрузка="+FloatToStr(*Loading_1));
    }
    else {
      sbRB->Panels->Items[2]->Text="Каретка А не включена - стенд не в ручном режиме!";
    }
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя включить каретку А - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnCarriage1From(TObject *Sender)
{
  CheckStend();
  if(OPCConnectOK){
	if(*ManualMode1){
		double t=leSetLoad1->Text.Trim().ToDouble();
		if (CheckLoad(t))
		{
			*Loading_1=t;
		}else
		{
            MessageBox(Handle,_T("Значение нагрузки должно быть в пределах от 0 до 115"),_T("Ошибка"),MB_ICONERROR|MB_OK);
			return;
		}
	  tbCurrentLoad1->SelEnd  =tbCurrentLoad1->Max-int(*Loading_1);
	  tbCurrentLoad1->SelStart=tbCurrentLoad1->Max-int(*Loading_1);
	  *Carriage1To=false; *Carriage1From=true;
	  sbCarr1Fm->Down     =*Carriage1From;
	  sbCarr1To->Down     =*Carriage1To;
	  OPCControlPause(tReadCycleTimer);
	  pOPC->BenchControl(Carriage1From,Carriage1To,Loading_1);
	  OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Каретка А движется от барабана!";
      LogPrintF(LogFName(),"Ручной режим, каретка 1 от барабана, установлена нагрузка="+FloatToStr(*Loading_1));
    }
    else {
      sbRB->Panels->Items[2]->Text="Каретка А не включена - стенд не в ручном режиме!";
    }
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя включить каретку А - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnCarriage1Stop(TObject *Sender)
{
  CheckStend();
  if(OPCConnectOK){
    if(*ManualMode1){
      *Carriage1To=false; *Carriage1From=false;
      sbCarr1Fm->Down     =*Carriage1From;
      sbCarr1To->Down     =*Carriage1To;
      OPCControlPause(tReadCycleTimer);
      pOPC->BenchControl(Carriage1From,Carriage1To);
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Каретка А остановлена!";
      LogPrintF(LogFName(),"Ручной режим, каретка 1 остановлена");
    }
    else {
      sbRB->Panels->Items[2]->Text="Каретка А не остановлена - стенд не в ручном режиме!";
    }
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя остановить каретку А - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnCarriage2To(TObject *Sender)
{
  CheckStend();
  if(OPCConnectOK){
	if(*ManualMode2){
		double t=leSetLoad2->Text.Trim().ToDouble();
		if (CheckLoad(t))
		{
			*Loading_2=t;
		}else
		{
            MessageBox(Handle,_T("Значение нагрузки должно быть в пределах от 0 до 115"),_T("Ошибка"),MB_ICONERROR|MB_OK);
			return;
		}
      tbCurrentLoad2->SelEnd  =tbCurrentLoad2->Max-int(*Loading_2);
      tbCurrentLoad2->SelStart=tbCurrentLoad2->Max-int(*Loading_2);
      *Carriage2To=true; *Carriage2From=false;
      sbCarr2Fm->Down     =*Carriage2From;
      sbCarr2To->Down     =*Carriage2To;
      OPCControlPause(tReadCycleTimer);
      pOPC->BenchControl(Carriage2From,Carriage2To,Loading_2);
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Каретка Б движется к барабану!";
      LogPrintF(LogFName(),"Ручной режим, каретка 2 к барабану, установлена нагрузка="+FloatToStr(*Loading_2));
    }
    else {
      sbRB->Panels->Items[2]->Text="Каретка Б не включена - стенд не в ручном режиме!";
    }
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя включить каретку Б - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnCarriage2Stop(TObject *Sender)
{
  CheckStend();
  if(OPCConnectOK){
    if(*ManualMode2){
      *Carriage2To=false; *Carriage2From=false;
      sbCarr2Fm->Down     =*Carriage2From;
      sbCarr2To->Down     =*Carriage2To;
      OPCControlPause(tReadCycleTimer);
      pOPC->BenchControl(Carriage2From,Carriage2To);
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Каретка Б остановлена!";
      LogPrintF(LogFName(),"Ручной режим, каретка 2 остановлена");
    }
    else {
      sbRB->Panels->Items[2]->Text="Каретка Б не остановлена - стенд не в ручном режиме!";
    }
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя остановить каретку Б - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnCarriage2From(TObject *Sender)
{
  CheckStend();
  if(OPCConnectOK){
	if(*ManualMode2){
		double t=leSetLoad2->Text.Trim().ToDouble();
		if (CheckLoad(t))
		{
			*Loading_2=t;
		}else
		{
            MessageBox(Handle,_T("Значение нагрузки должно быть в пределах от 0 до 115"),_T("Ошибка"),MB_ICONERROR|MB_OK);
			return;
		}
	  tbCurrentLoad2->SelEnd  =tbCurrentLoad2->Max-int(*Loading_2);
	  tbCurrentLoad2->SelStart=tbCurrentLoad2->Max-int(*Loading_2);
      *Carriage2To=false; *Carriage2From=true;
      sbCarr2Fm->Down     =*Carriage2From;
      sbCarr2To->Down     =*Carriage2To;
      OPCControlPause(tReadCycleTimer);
      pOPC->BenchControl(Carriage2From,Carriage2To,Loading_2);
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Каретка Б движется от барабана!";
      LogPrintF(LogFName(),"Ручной режим, каретка 2 от барабана, установлена нагрузка="+FloatToStr(*Loading_2));
    }
    else {
      sbRB->Panels->Items[2]->Text="Каретка Б не включена - стенд не в ручном режиме!";
    }
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя включить каретку Б - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnGeneralStop(TObject *Sender)
{
	CheckStend();
	if(OPCConnectOK)
	{
		//*Reset1=true;  *Reset2=true;
		*Start1=false; *Stop1= true;
		*Start2=false; *Stop2= true;
		OPCControlPause(tReadCycleTimer);
		pOPC->BenchControl(Start1,Stop1);
		pOPC->BenchControl(Start2,Stop2);
		OPCControlResume(tReadCycleTimer);
		sbRB->Panels->Items[2]->Text="Стенд остановлен!";
		LogPrintF(LogFName(),"Общая остановка стенда!");
	}
	else
	{
		sbRB->Panels->Items[2]->Text="Нельзя остановить стенд - нет соединения со стендом!";
	}
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnTestModeChange(TObject *Sender)
{
  if(cmbTestMode->ItemIndex==0){
    leTestTimePath->EditLabel->Caption="Время обкатки, ч: ";
  }
  else {
    leTestTimePath->EditLabel->Caption="Путь обкатки, км: ";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnMainFormCreate(TObject *Sender)
{
  //Handle1On=false;
  //Handle2On=false;
  mfRB->Left=0; mfRB->Top=0;
  mfRB->Height=MFHEIGHT; mfRB->Width=MFWIDTH;
  tsCurrentStatusH=tsCurrentStatus->Height;
  tsCurrentStatusW=tsCurrentStatus->Width;
  pParam1Height     =pParam1->Height;
  pParam1Width      =pParam1->Width;
  pParam2Height     =pParam2->Height;
  pParam2Width      =pParam2->Width;
  tsManualHeight    =tsManual->Height;
  tsManualWidth     =tsManual->Width;
  tsTimeProgHeight  =tsTimeProg->Height;
  tsTimeProgWidth   =tsTimeProg->Width;
  tsSProgHeight     =tsSProg->Height;
  tsSProgWidth      =tsSProg->Width;
  tsNewProtHeight   =tsNewProtocol->Height;
  tsNewProtWidth    =tsNewProtocol->Width;
  tsProtocolAHeight =tsProtocolA->Height;
  tsProtocolAWidth  =tsProtocolA->Width;
  tsProtocolBHeight =tsProtocolB->Height;
  tsProtocolBWidth  =tsProtocolB->Width;
  tsSpeedCalibrH    =tsSpeedCalibr->Height;
  tsSpeedCalibrW    =tsSpeedCalibr->Width;
  tsLoadCalibrAH    =tsLoadCalibrA->Height;
  tsLoadCalibrAW    =tsLoadCalibrA->Width;
  tsTCalibrAH       =tsTCalibrA->Height;
  tsTCalibrAW       =tsTCalibrA->Width;
  tsRCalibrAH       =tsRCalibrA->Height;
  tsRCalibrAW       =tsRCalibrA->Width;
  tsLoadSertAH      =tsLoadSertA->Height;
  tsLoadSertAW      =tsLoadSertA->Width;
  DesignNewProtPanel();
  DesignProtAPanel();
  DesignProtBPanel();
  DesignSProgTable();
  DesignTProgTable();
  DesignCmmnParPanel();
  DesignManualPanel();
  DesignLoadSertAPanel();
  DesignLoadSertBPanel();
  DesignLoadCalibrAPanel();
  DesignLoadCalibrBPanel();
  DesignRCalibrAPanel();
  DesignRCalibrBPanel();
  DesignTCalibrAPanel();
  DesignTCalibrBPanel();
  DesignSpdCalibrPanel();
  DesignTSertPanel();
  DesignRSertPanel();
  //Handle1On=true;
  //Handle2On=true;
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnSProgFileOpen(TObject *Sender)
{
  SProgFName=acSProgFileOpen->Dialog->FileName;
  LogPrint("Загрузить программу по пути из файла \""+SProgFName+"\"!",clAqua);
  ReadSProgFmFile();
  ShowSProg();
  btnCheckSProg->Enabled=false;
  btnSaveSProgToFile->Enabled=true;
  btnLoadSProgToPosA->Enabled=true;
  btnLoadSProgToPosB->Enabled=true;
  sbRB->Panels->Items[2]->Text="Программа по пути загружена из файла \""+FileNameParse(SProgFName)+"\"!";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnSProgFileSaveAs(TObject *Sender)
{//Сохранить в файле программу по пути
	//проверка вызывающего действия
	if (Sender==acSProgFileSaveAs)
	{//ручное сохранение
		SProgFName=acSProgFileSaveAs->Dialog->FileName;
		acSProgFileSaveAs->Dialog->FileName="";
	}else
	{//автосейв
		SProgFName=strDistProg+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.sprg'");
	}
  LogPrint("Сохранить программу по пути в файле \""+SProgFName+"\"!",clAqua);
  WriteSProgToFile();
  sbRB->Panels->Items[2]->Text="Программа по пути сохранена в файле \""+FileNameParse(SProgFName)+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadSProgToPosA(TObject *Sender)
{
	if (!CheckProgLoad(sgSProgram,1,10.0))
	{
		return;
	}
  LogPrint("Загрузка программы по пути в поз. А!",clAqua);
  sbRB->Panels->Items[2]->Text="Загрузка программы по пути в поз. А!";
  // читаем программу из ячеек и загружаем в контроллер поз. А
  for (int i = 0; i < MAXNUMOFSTEPS; i++) {
	setting_A[0][i]=Ssettings[0][i];
	setting_A[1][i]=Ssettings[1][i];
	step_SA[i]     =prog_step_S[i];
  }
  for (int i = 0; i < MAXNUMOFPOLLS; i++) {
	poll_step_SA[i]=poll_step_S[i];
  }
  RunProgNameA=SProgName;
  SetCurrProgA(RunProgNameA);
  stP1L2ProgNameA->Caption=RunProgNameA;
  TyreA->InitPressure     =StrToFlt(leSTyrePressure->Text);
  *S_end_cycle_1          =TyreA->TotalS           =StrToFlt(leTotalTestS->Text);
  *T_end_cycle_1          =TyreA->TotalTime        =0;
  *type_cycle_1           =TyreA->TestMode         =1;
  *StepsQty1              =TyreA->StepsNo          =StrToInt(leSTotalStepsQty->Text);
  *PollsQty1              =TyreA->PollsNo          =StrToInt(leSPollingTotalQty->Text);
  LogPrintF(LogFName(),"Программа по пути, поз. А: путь="+FloatToStrF(*S_end_cycle_1,ffFixed,9,2)+
                       ", шагов программы="+String(*StepsQty1)+", опросов="+String(*PollsQty1));
  CheckStend();
  if(OPCConnectOK) {
    OPCControlPause(tReadCycleTimer);
    pOPC->TestParamWrite(S_end_cycle_1,T_end_cycle_1,type_cycle_1,StepsQty1,PollsQty1);
    pOPC->WriteGr4();
    pOPC->WriteGr6();
    OPCControlResume(tReadCycleTimer);
    LogPrintF(LogFName(),"Программа по пути загружена в поз. А!");
    sbRB->Panels->Items[2]->Text="Программа по пути загружена в поз. А!";
  }
  else {
    sbRB->Panels->Items[2]->Text="Недьзя загрузить программу по пути в поз. А - нет связи со станком!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadSProgToPosB(TObject *Sender)
{
	if (!CheckProgLoad(sgSProgram,1,10.0))
	{
		return;
	}
  LogPrint("Загрузка программы по пути в поз. Б!",clAqua);
  sbRB->Panels->Items[2]->Text="Загрузка программы по пути в поз. Б!";
  // читаем программу из ячеек и загружаем в контроллер поз. B
 for (int i = 0; i < MAXNUMOFSTEPS; i++) {
	setting_B[0][i]=Ssettings[0][i];
	setting_B[1][i]=Ssettings[1][i];
	step_SB[i]     =prog_step_S[i];
  }
  for (int i = 0; i < MAXNUMOFPOLLS; i++) {
	poll_step_SB[i]=poll_step_S[i];
  }
  RunProgNameB=SProgName;
  SetCurrProgB(RunProgNameB);
  stP1L2ProgNameB->Caption=RunProgNameB;
  TyreB->InitPressure     =StrToFlt(leSTyrePressure->Text);
  *S_end_cycle_2          =TyreB->TotalS           =StrToFlt(leTotalTestS->Text);
  *T_end_cycle_2          =TyreB->TotalTime        =0;
  *type_cycle_2           =TyreB->TestMode         =1;
  *StepsQty2              =TyreB->StepsNo          =StrToInt(leSTotalStepsQty->Text);
  *PollsQty2              =TyreB->PollsNo          =StrToInt(leSPollingTotalQty->Text);
  LogPrintF(LogFName(),"Программа по пути, поз. Б: путь="+FloatToStrF(*S_end_cycle_2,ffFixed,9,2)+
                       ", шагов программы="+String(*StepsQty2)+", опросов="+String(*PollsQty2));
  CheckStend();
  if(OPCConnectOK) {
    OPCControlPause(tReadCycleTimer);
	pOPC->TestParamWrite(S_end_cycle_2,T_end_cycle_2,type_cycle_2,StepsQty2,PollsQty2);
    pOPC->WriteGr8();
    pOPC->WriteGr10();
    OPCControlResume(tReadCycleTimer);
    sbRB->Panels->Items[2]->Text="Программа по пути загружена в поз. Б!";
  }
  else {
    sbRB->Panels->Items[2]->Text="Недьзя загрузить программу по пути в поз. Б - нет связи со станком!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::DesignTProgTable(void)   // создание таблицы для ввода программы испытаний по времени
{ const int Col0Width=30,Col1Width=80,Col2Width=105,Col3Width=67,Col4Width=30;
  const int pHeight=26, pH=24, LSp=10;
  int Left1=leTTyrePressure->EditLabel->Width+LSp,
      Top1=pHeight+LSp, Top2=pHeight+pH+LSp*2, Width2=50;
  int Left2=leTTotalStepsQty->EditLabel->Width+Left1+Width2+LSp, Width3=tsTimeProgWidth/14;
  if(Width3<66)Width3=66;
  int Width1=Left2+Width2-Left1;
  int Left3=Left1+Width1+leTotalTestTime->EditLabel->Width+LSp;
  pTProgTtl->Left          =0;                  pTProgTtl->Top          =0;
  pTProgTtl->Width         =tsTimeProgWidth;    pTProgTtl->Height       =pHeight;

  leTProgName->Left        =Left1;              leTProgName->Top        =Top1;
  leTProgName->Width       =Width1;             leTProgName->Height     =pH;
  leTotalTestTime->Left    =Left3;              leTotalTestTime->Top    =Top1;
  leTotalTestTime->Width   =Width3;             leTotalTestTime->Height =pH;
  leTTyrePressure->Left    =Left1;              leTTyrePressure->Top    =Top2;
  leTTyrePressure->Width   =Width2;             leTTyrePressure->Height =pH;
  leTTotalStepsQty->Left   =Left2;              leTTotalStepsQty->Top   =Top2;
  leTTotalStepsQty->Width  =Width2;             leTTotalStepsQty->Height=pH;
  leTPollingTotalQty->Left =Left3;              leTPollingTotalQty->Top =Top2;
  leTPollingTotalQty->Width=Width3;
  lTProgTblNme->Top        =Top2+pH+LSp;
  sgTProgram->Top          =Top2+pH*2+LSp;
  sgTProgram->Left         =tsTimeProgWidth/20;

  int TTableWidth=Col0Width+Col1Width+Col2Width+Col3Width+Col4Width+30;
  lTProgTblNme->Left      =(TTableWidth-lTProgTblNme->Width)/2+sgTProgram->Left;
  sgTProgram->Width       =TTableWidth;
  int TTableHeight=tsTimeProgHeight-sgTProgram->Top-5;
  int RowNo=TTableHeight/(sgTProgram->RowHeights[0]+1);
  TTableHeight=RowNo*sgTProgram->RowHeights[0]+RowNo;
  sgTProgram->Height=TTableHeight;
  sgTProgram->ColWidths[0]=Col0Width;          sgTProgram->ColWidths[1]=Col1Width;
  sgTProgram->ColWidths[2]=Col2Width;          sgTProgram->ColWidths[3]=Col3Width;
  sgTProgram->ColWidths[4]=Col4Width;
  sgTProgram->Cells[0][0]="№";                sgTProgram->Cells[1][0]="Нагрузка, кН";
  sgTProgram->Cells[2][0]="Скорость, км/час"; sgTProgram->Cells[3][0]="Время, час";
  sgTProgram->Cells[4][0]="мин";
  for (int i = 0; i < MAXNUMOFSTEPS; i++) {
    if(i<9)sgTProgram->Cells[0][i+1]="  "+String(i+1)+":";
    else if(i<99)sgTProgram->Cells[0][i+1]=" "+String(i+1)+":";
    else sgTProgram->Cells[0][i+1]=String(i+1)+":";
  }
  lTPollingTblNme1->Top=lTProgTblNme->Top;
  sgTPolling->Left=sgTProgram->Left+TTableWidth+40;
  sgTPolling->Top=sgTProgram->Top;
  sgTPolling->ColWidths[0]=Col0Width;
  sgTPolling->ColWidths[1]=Col3Width;
  sgTPolling->ColWidths[2]=Col4Width;
  int TPollTableWidth=Col0Width+Col3Width+Col4Width+30;
  lTPollingTblNme1->Left=(TPollTableWidth-lTPollingTblNme1->Width)/2+sgTPolling->Left;
  sgTPolling->Width=TPollTableWidth;
  sgTPolling->Height=TTableHeight;
  sgTPolling->Cells[0][0]="№";
  sgTPolling->Cells[1][0]="Время, час";
  sgTPolling->Cells[2][0]="мин";
  for (int i = 0; i < MAXNUMOFPOLLS; i++) {
    if(i<9)sgTPolling->Cells[0][i+1]="  "+String(i+1)+":";
    else if(i<99)sgTPolling->Cells[0][i+1]=" "+String(i+1)+":";
    else sgTPolling->Cells[0][i+1]=String(i+1)+":";
  }
  int btnLeft=sgTPolling->Left+TPollTableWidth+10;
  int btnWidth=tsTimeProgWidth-btnLeft-10;
  int btnHeight=50;
  btnNewTProg->Left         =btnLeft;    btnCheckTProg->Left       =btnLeft;
  btnSaveTProgToFile->Left  =btnLeft;    btnOpenTProgFmFile->Left  =btnLeft;
  btnLoadTProgToPosA->Left  =btnLeft;    btnLoadTProgToPosB->Left  =btnLeft;
  btnNewTProg->Width        =btnWidth;   btnCheckTProg->Width      =btnWidth;
  btnSaveTProgToFile->Width =btnWidth;   btnOpenTProgFmFile->Width =btnWidth;
  btnLoadTProgToPosA->Width =btnWidth;   btnLoadTProgToPosB->Width =btnWidth;
  btnNewTProg->Height       =btnHeight;  btnCheckTProg->Height     =btnHeight;
  btnSaveTProgToFile->Height=btnHeight;  btnOpenTProgFmFile->Height=btnHeight;
  btnLoadTProgToPosA->Height=btnHeight;  btnLoadTProgToPosB->Height=btnHeight;
  btnNewTProg->Top          =sgTProgram->Top;
  btnCheckTProg->Top        =btnNewTProg->Top+btnHeight+10;
  btnSaveTProgToFile->Top   =btnCheckTProg->Top+btnHeight+10;
  btnOpenTProgFmFile->Top   =btnSaveTProgToFile->Top+btnHeight+10;
  btnLoadTProgToPosA->Top   =btnOpenTProgFmFile->Top+btnHeight+10;
  btnLoadTProgToPosB->Top   =btnLoadTProgToPosA->Top+btnHeight+10;
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=-1;
  sgTProgram->Selection=myRect;
  sgTPolling->Selection=myRect;*/
  btnCheckTProg->Enabled=false;
  btnSaveTProgToFile->Enabled=false;
  btnLoadTProgToPosA->Enabled=false;
  btnLoadTProgToPosB->Enabled=false;
}
//---- End of DesignTProgTabe -----------------------------------------------

void __fastcall TmfRB::OnMFResize(TObject *Sender)
{
	if (closing) {return;}//смысл перерисовывать если программа закрывается
  //Handle1On=false;
  //Handle2On=false;
  tsCurrentStatusH=tsCurrentStatus->Height;
  tsCurrentStatusW=tsCurrentStatus->Width;
  pParam1Height     =pParam1->Height;
  pParam1Width      =pParam1->Width;
  pParam2Height     =pParam2->Height;
  pParam2Width      =pParam2->Width;
  tsManualHeight    =tsManual->Height;
  tsManualWidth     =tsManual->Width;
  tsTimeProgHeight  =tsTimeProg->Height;
  tsTimeProgWidth   =tsTimeProg->Width;
  tsSProgHeight     =tsSProg->Height;
  tsSProgWidth      =tsSProg->Width;
  tsNewProtHeight   =tsNewProtocol->Height;
  tsNewProtWidth    =tsNewProtocol->Width;
  tsProtocolAHeight =tsProtocolA->Height;
  tsProtocolAWidth  =tsProtocolA->Width;
  tsProtocolBHeight =tsProtocolB->Height;
  tsProtocolBWidth  =tsProtocolB->Width;
  tsSpeedCalibrH    =tsSpeedCalibr->Height;
  tsSpeedCalibrW    =tsSpeedCalibr->Width;
  tsLoadCalibrAH    =tsLoadCalibrA->Height;
  tsLoadCalibrAW    =tsLoadCalibrA->Width;
  tsTCalibrAH       =tsTCalibrA->Height;
  tsTCalibrAW       =tsTCalibrA->Width;
  tsRCalibrAH       =tsRCalibrA->Height;
  tsRCalibrAW       =tsRCalibrA->Width;
  tsLoadSertAH      =tsLoadSertA->Height;
  tsLoadSertAW      =tsLoadSertA->Width;
  DesignNewProtPanel();
  DesignProtAPanel();
  DesignProtBPanel();
  DesignTProgTable();
  DesignSProgTable();
  DesignCmmnParPanel();
  DesignManualPanel();
  DesignLoadSertAPanel();
  DesignLoadSertBPanel();
  DesignLoadCalibrAPanel();
  DesignLoadCalibrBPanel();
  DesignRCalibrAPanel();
  DesignRCalibrBPanel();
  DesignTCalibrAPanel();
  DesignTCalibrBPanel();
  DesignSpdCalibrPanel();
  DesignTSertPanel();
  DesignRSertPanel();
  //Handle1On=true;
  //Handle2On=true;
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnTProgFileSaveAs(TObject *Sender)
{//Сохранить в файле программу по времени
//проверка вызывающего действия
	if (Sender==acTProgFileSaveAs)
	{//ручное сохранение
		TProgFName=acTProgFileSaveAs->Dialog->FileName;
		acTProgFileSaveAs->Dialog->FileName="";
	}else
	{//автосейв
		TProgFName=strTimeProg+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.tprg'");
	}
  sbRB->Panels->Items[2]->Text="Сохраняем программу по времени в файл!";

  LogPrint("Программа по времени сохраняется в файле \""+TProgFName+"\"!",clAqua);
  WriteTProgToFile();
  sbRB->Panels->Items[2]->Text="Программа по времени сохранена в файле \""+FileNameParse(TProgFName)+"\"";
  btnCheckTProg->Enabled=false;
  btnSaveTProgToFile->Enabled=true;
  btnLoadTProgToPosA->Enabled=true;
  btnLoadTProgToPosB->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnTProgFileOpen(TObject *Sender)
{
  sbRB->Panels->Items[2]->Text="Читаем программу по времени из файла!";
  TProgFName=acTProgFileOpen->Dialog->FileName;
  LogPrint("Программа по времени читается из файла \""+FileNameParse(TProgFName)+"\"!",clAqua);
  ReadTProgFmFile();
  sbRB->Panels->Items[2]->Text="Программа по времени прочитана из файла \""+FileNameParse(TProgFName)+"\"";
  ShowTProg();
  btnCheckTProg->Enabled=false;
  btnSaveTProgToFile->Enabled=true;
  btnLoadTProgToPosA->Enabled=true;
  btnLoadTProgToPosB->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadTProgToPosA(TObject *Sender)
{
	if (!CheckProgLoad(sgTProgram,1,10.0))
	{
    	return;
	}

  sbRB->Panels->Items[2]->Text="Загрузка программы по времени в поз. А!";
  // читаем программу из ячеек и загружаем в контроллер поз. А
  for (int i = 0; i < MAXNUMOFSTEPS; i++) {
	setting_A[0][i]=Tsettings[0][i];
	setting_A[1][i]=Tsettings[1][i];
	step_TA[i]     =prog_step_T[i];
  }
  for (int i = 0; i < MAXNUMOFPOLLS; i++) {
	poll_step_TA[i]=poll_step_T[i];
  }
  RunProgNameA=TProgName;
  SetCurrProgA(RunProgNameA);
  stP1L2ProgNameA->Caption=RunProgNameA;
  TyreA->InitPressure     =StrToFlt(leTTyrePressure->Text);
  *S_end_cycle_1          =TyreA->TotalS           =0;
  *T_end_cycle_1          =TyreA->TotalTime        =total_T;
  *type_cycle_1           =TyreA->TestMode         =0;
  *StepsQty1              =TyreA->StepsNo          =StrToInt(leTTotalStepsQty->Text);
  *PollsQty1              =TyreA->PollsNo          =StrToInt(leTPollingTotalQty->Text);
  ShowProtAData();
  LogPrintF(LogFName(),"Программа по времени, поз. А: время="+String(*T_end_cycle_1)+
                       ", шагов программы="+String(*StepsQty1)+", опросов="+String(*PollsQty1));
  CheckStend();
  if(OPCConnectOK) {
	OPCControlPause(tReadCycleTimer);
	btnResetResPosA->Click();
	pOPC->TestParamWrite(S_end_cycle_1,T_end_cycle_1,type_cycle_1,StepsQty1,PollsQty1);
    pOPC->WriteGr5();
	pOPC->WriteGr6();
    OPCControlResume(tReadCycleTimer);
    btnCheckTProg->Enabled=false;
    btnSaveTProgToFile->Enabled=true;
    btnLoadTProgToPosA->Enabled=true;
    btnLoadTProgToPosB->Enabled=true;
    LogPrintF(LogFName(),"Программа по времени загружена в поз. А!");
    LogPrint("Программа по времени загружена в поз. А!",clAqua);
	sbRB->Panels->Items[2]->Text="Программа по времени загружена в поз. А!";

  }
  else {
    sbRB->Panels->Items[2]->Text="Недьзя загрузить программу по времени в поз. А - нет связи со станком!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadTProgToPosB(TObject *Sender)
{
	if (!CheckProgLoad(sgTProgram,1,10.0))
	{
    	return;
	}
  sbRB->Panels->Items[2]->Text="Загрузка программы по времени в поз. Б!";
  // читаем программу из ячеек и загружаем в контроллер поз. Б
  for (int i = 0; i < MAXNUMOFSTEPS; i++) {
	setting_B[0][i]=Tsettings[0][i];
	setting_B[1][i]=Tsettings[1][i];
	step_TB[i]     =prog_step_T[i];
  }
  for (int i = 0; i < MAXNUMOFPOLLS; i++) {
	poll_step_TB[i]=poll_step_T[i];
  }
  RunProgNameB=TProgName;
  SetCurrProgB(RunProgNameB);
  stP1L2ProgNameB->Caption=RunProgNameB;
  TyreB->InitPressure     =StrToFlt(leSTyrePressure->Text);
  *S_end_cycle_2          =TyreB->TotalS           =0;
  *T_end_cycle_2          =TyreB->TotalTime        =total_T;
  *type_cycle_2           =TyreB->TestMode         =0;
  *StepsQty2              =TyreB->StepsNo          =StrToInt(leTTotalStepsQty->Text);
  *PollsQty2              =TyreB->PollsNo          =StrToInt(leTPollingTotalQty->Text);
  ShowProtBData();
  LogPrintF(LogFName(),"Программа по времени, поз. Б: время="+String(*T_end_cycle_2)+
					   ", шагов программы="+String(*StepsQty2)+", опросов="+String(*PollsQty2));
  CheckStend();
  if(OPCConnectOK) {
	OPCControlPause(tReadCycleTimer);
	btnResetResPosB->Click();
    pOPC->TestParamWrite(S_end_cycle_2,T_end_cycle_2,type_cycle_2,StepsQty2,PollsQty2);
    pOPC->WriteGr9();
    pOPC->WriteGr10();
    OPCControlResume(tReadCycleTimer);
    btnCheckTProg->Enabled=false;
    btnSaveTProgToFile->Enabled=true;
    btnLoadTProgToPosA->Enabled=true;
    btnLoadTProgToPosB->Enabled=true;
    LogPrintF(LogFName(),"Программа по времени загружена в поз. Б!");
    LogPrint("Программа по времени загружена в поз. Б!",clAqua);
    sbRB->Panels->Items[2]->Text="Программа по времени загружена в поз. Б!";
  }
  else {
    sbRB->Panels->Items[2]->Text="Недьзя загрузить программу по времени в поз. Б - нет связи со станком!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnStringGridExit(TObject *Sender)
{
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
  ((TStringGrid *)Sender)->Selection=myRect; */
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnGetEditMask(TObject *Sender, int ACol, int ARow, AnsiString &Value)
{
  if(((TStringGrid *)Sender)==sgTProgram){
    switch (ACol) {
      case 1:
        Value="!999\,99;1;_";
        break;
      case 2:
        Value="!999\,99;1;_";
        break;
      case 3:
        Value="!999;1;_";
        break;
      case 4:
        Value="!99;1;_";
        break;
      default:
        Value="";
    }
  }
  if (((TStringGrid *)Sender)==sgTPolling) {
    switch (ACol) {
      case 1:
        Value="!999;1;_";
        break;
      case 2:
        Value="!99;1;_";
        break;
      default:
        Value="";
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnSGKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
  if (Key==VK_RETURN) {
    if(((TStringGrid *)Sender)->Col<((TStringGrid *)Sender)->ColCount-1){
      ((TStringGrid *)Sender)->Col++;
    }
    else {
      ((TStringGrid *)Sender)->Col=1;
      if(((TStringGrid *)Sender)->Row<((TStringGrid *)Sender)->RowCount-1)
        ((TStringGrid *)Sender)->Row++;
      else  
        ((TStringGrid *)Sender)->Row=1;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnSGKeyPress(TObject *Sender, char &Key)
{
  if (Key==',')
  {
  	Key='.';
  }
  Set <char, '0','9'> Dig;
  Dig << '0' << '1' << '2' << '3' << '4' << '5' << '6' << '7' << '8' << '9';
//  LogPrint("Key="+String((unsigned short)Key),clRed);
  if(!Dig.Contains(Key)&&Key != '\b' && Key != DecimalSeparator && Key != VK_RETURN && Key != VK_TAB) {
    Key=0;
    Beep();
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnTProgCheck(TObject *Sender)
{
	//чистка старых данных
	ClearTProg();
	// читаем программу из ячеек таблиц, проверяем и записываем в массивы
	TProgName=leTProgName->Text;
	TTyrePressure=StrToFlt(leTTyrePressure->Text); leTTyrePressure->Text=FloatToStrF(TTyrePressure,ffFixed,6,1);
	total_step_T=0; total_T=0;
	for (int i = 0; i < MAXNUMOFSTEPS; i++)
	{
		double 	Load=StrToFlt(sgTProgram->Cells[1][i+1]),
				Speed=StrToFlt(sgTProgram->Cells[2][i+1]);
		int		Time=StrToI(sgTProgram->Cells[3][i+1])*3600*1000+StrToI(sgTProgram->Cells[4][i+1])*60*1000;
		if (!CheckLoad(Load)||!CheckSpeed(Speed)||(!CheckTime(Time)&&Time))
		{
			ClearTProg();//чистка данных
			AnsiString msg="Введено не корректное значение в строке "+AnsiString(i+1);
			MessageBox(Handle,msg.c_str(),_T("Ошибка"),MB_ICONERROR|MB_OK);
			return;
		}
		Tsettings[0][i]=Load;
		if(Tsettings[0][i]==0)
		{  // если нагрузка в этой строчке равна 0
			if(i>0)total_step_T=i;
			else
			{
				sbRB->Panels->Items[2]->Text="Не задано ни одного значения нагрузки!";
				MessageBox(Handle,_T("Не задано ни одного значения нагрузки!"),_T("Ошибка"),MB_ICONERROR|MB_OK);
				ClearTProg();//чистка данных
			}
			break;                 // то прекратить ввод из таблицы
		}
		sgTProgram->Cells[1][i+1]=FloatToStrF(Tsettings[0][i],ffFixed,6,2);

		Tsettings[1][i]=Speed;
		if(Tsettings[1][i]==0)
		{ // если скорость равна 0
			if(i>0)
			{              // если строка не первая - взять из предыдущей строки
				Tsettings[1][i]=Tsettings[1][i-1];
			}
			else
			{                 // иначе ни одной скорости не задано - прекратить ввод из таблицы
				sbRB->Panels->Items[2]->Text="Не задано ни одного значения скорости!";
				total_step_T=0;
				MessageBox(Handle,_T("Не задано ни одного значения скорости!"),_T("Ошибка"),MB_ICONERROR|MB_OK);
				ClearTProg();//чистка данных
				break;
			}
		}
		sgTProgram->Cells[2][i+1]=FloatToStrF(Tsettings[1][i],ffFixed,6,2);

		prog_step_T[i]=Time;
		if (prog_step_T[i]==0)
		{ // если продолжительность шага равна 0
			if(i>0)
			{               // если строка не первая - взять из предыдущей строки
				prog_step_T[i]=prog_step_T[i-1];
			}
			else
			{                 // иначе не задано продолжительности - прекратить ввод из таблицы
				sbRB->Panels->Items[2]->Text="Не задано ни одного значения продолжительности шага!";
				total_step_T=0;
				MessageBox(Handle,_T("Не задано ни одного значения продолжительности шага!"),_T("Ошибка"),MB_ICONERROR|MB_OK);
				ClearTProg();//чистка данных
				break;
			}
		}
		sgTProgram->Cells[3][i+1]=String(prog_step_T[i]/1000/3600);
		sgTProgram->Cells[4][i+1]=String((prog_step_T[i]/1000-prog_step_T[i]/1000/3600*3600)/60);
		total_T+=prog_step_T[i];
	}
	leTTotalStepsQty->Text=String(total_step_T);
	if(total_step_T==0)
	{
		leTotalTestTime->Text="";
		return;
	}
	leTotalTestTime->Text=mSecToHMSStr(total_T);
	num_T_poll=0; int total_poll_T=0;
	for (int i = 0; i < MAXNUMOFPOLLS; i++)
	{
		int Time=StrToI(sgTPolling->Cells[1][i+1])*3600*1000+StrToI(sgTPolling->Cells[2][i+1])*60*1000;
		if (!CheckTime(Time)&&Time)
		{
			ClearTProg();//чистка данных
			AnsiString msg="Введено не корректное значение опроса в строке "+AnsiString(i+1);
			MessageBox(Handle,msg.c_str(),_T("Ошибка"),MB_ICONERROR|MB_OK);
			return;
		}
		poll_step_T[i]=Time;
		if(poll_step_T[i]==0)
		{
			if(i==0)
			{
				sbRB->Panels->Items[2]->Text="Не задано ни одного времени опроса!";
				MessageBox(Handle,_T("Не задано ни одного времени опроса!"),_T("Ошибка"),MB_ICONERROR|MB_OK);
				ClearTProg();//чистка данных
				break;
			}
			else
			{
				poll_step_T[i]=poll_step_T[i-1];
			}
		}
		sgTPolling->Cells[1][i+1]=String(poll_step_T[i]/1000/3600);
		sgTPolling->Cells[2][i+1]=String((poll_step_T[i]/1000-poll_step_T[i]/1000/3600*3600)/60);
		total_poll_T+=poll_step_T[i]; num_T_poll++;
		if (total_poll_T>=total_T)
			break;
	}
	if(num_T_poll==0)
	{
		leTPollingTotalQty->Text="";
		return;
	}
	leTPollingTotalQty->Text=String(num_T_poll);
	sbRB->Panels->Items[2]->Text="Программа проверена!";
	btnCheckTProg->Enabled=false;
	btnSaveTProgToFile->Enabled=true;
	btnLoadTProgToPosA->Enabled=true;
	btnLoadTProgToPosB->Enabled=true;
}
//---- End of OnTProgCheck --------------------------------------------------

void __fastcall TmfRB::OnSGSEnter(TObject *Sender)
{
  btnCheckSProg->Enabled=true;
  btnSaveSProgToFile->Enabled=false;
  btnLoadSProgToPosA->Enabled=false;
  btnLoadSProgToPosB->Enabled=false;
}
//---- End of OnSGSEnter ----------------------------------------------------

void __fastcall TmfRB::OnLEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
  if(Key==VK_RETURN) {
    FindNextControl((TWinControl *)Sender,true,true,false)->SetFocus();
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::DesignCmmnParPanel(void)// расположение компонент на панели общих параметров
{ int C0Width=pParam1Width/4;
  int C1_6Width=(pParam1Width-C0Width)/6;
  int C1_4Width=C1_6Width*3/2/3*3;
  C1_6Width=C1_4Width/3*2;
  C0Width=pParam1Width-C1_6Width*6;
  pParam1Height=13*tsCurrentStatusH/22;
  pParam2Height=tsCurrentStatusH-pParam1Height-Splitter1->Height;
  pParam1->Height=pParam1Height;
  pParam2->Height=pParam2Height;
  int p1RowHeight=pParam1Height/13;
  if(p1RowHeight>30)p1RowHeight=30;
  stP1CurDate->Left     =0;                   stP1CurDate->Top       =0;
  stP1CurDate->Width    =C0Width;             stP1CurDate->Height    =p1RowHeight;
  stP1TL0C1->Left       =C0Width;             stP1TL0C1->Top         =0;
  stP1TL0C1->Width      =C1_6Width*3;         stP1TL0C1->Height      =p1RowHeight;
  stP1TL0C2->Left       =C0Width+C1_6Width*3; stP1TL0C2->Top         =0;
  stP1TL0C2->Width      =C1_6Width*3;         stP1TL0C2->Height      =p1RowHeight;
  stP1TTyreType->Left   =0;                   stP1TTyreType->Top     =p1RowHeight;
  stP1TTyreType->Width  =C0Width;             stP1TTyreType->Height  =p1RowHeight;
  stP1L1TyreTypeA->Left =C0Width;             stP1L1TyreTypeA->Top   =p1RowHeight;
  stP1L1TyreTypeA->Width=C1_6Width*3;         stP1L1TyreTypeA->Height=p1RowHeight;
  stP1L1TyreTypeB->Left =C0Width+C1_6Width*3; stP1L1TyreTypeB->Top   =p1RowHeight;
  stP1L1TyreTypeB->Width=C1_6Width*3;         stP1L1TyreTypeB->Height=p1RowHeight;
  stP1TProgName->Left   =0;                   stP1TProgName->Top     =p1RowHeight*2;
  stP1TProgName->Width  =C0Width;             stP1TProgName->Height  =p1RowHeight;
  stP1L2ProgNameA->Left =C0Width;             stP1L2ProgNameA->Top   =p1RowHeight*2;
  stP1L2ProgNameA->Width=C1_6Width*3;         stP1L2ProgNameA->Height=p1RowHeight;
  stP1L2ProgNameB->Left =C0Width+C1_6Width*3; stP1L2ProgNameB->Top   =p1RowHeight*2;
  stP1L2ProgNameB->Width=C1_6Width*3;         stP1L2ProgNameB->Height=p1RowHeight;
  pP1PT2->Left          =0;                   pP1PT2->Top            =p1RowHeight*3;
  pP1PT2->Width         =pParam1Width;        pP1PT2->Height         =p1RowHeight;
  pP1PL1Ttl->Left       =0;                   pP1PL1Ttl->Top         =p1RowHeight*4;
  pP1PL1Ttl->Width      =C0Width;             pP1PL1Ttl->Height      =p1RowHeight;
  pP1PL2Ttl->Left       =0;                   pP1PL2Ttl->Top         =p1RowHeight*5;
  pP1PL2Ttl->Width      =C0Width;             pP1PL2Ttl->Height      =p1RowHeight;
  pP1PL3Ttl->Left       =0;                   pP1PL3Ttl->Top         =p1RowHeight*6;
  pP1PL3Ttl->Width      =C0Width;             pP1PL3Ttl->Height      =p1RowHeight;
  pP1PL4Ttl->Left       =0;                   pP1PL4Ttl->Top         =p1RowHeight*7;
  pP1PL4Ttl->Width      =C0Width;             pP1PL4Ttl->Height      =p1RowHeight;
  pP1PL5Ttl->Left       =0;                   pP1PL5Ttl->Top         =p1RowHeight*8;
  pP1PL5Ttl->Width      =C0Width;             pP1PL5Ttl->Height      =p1RowHeight;
  pP1PL6Ttl->Left       =0;                   pP1PL6Ttl->Top         =p1RowHeight*9;
  pP1PL6Ttl->Width      =C0Width;             pP1PL6Ttl->Height      =p1RowHeight;
  pP1PL7Ttl->Left       =0;                   pP1PL7Ttl->Top         =p1RowHeight*10;
  pP1PL7Ttl->Width      =C0Width;             pP1PL7Ttl->Height      =p1RowHeight;
  pP1PL8Ttl->Left       =0;                   pP1PL8Ttl->Top         =p1RowHeight*11;
  pP1PL8Ttl->Width      =C0Width;             pP1PL8Ttl->Height      =p1RowHeight;
  pP1PL9Ttl->Left       =0;                   pP1PL9Ttl->Top         =p1RowHeight*12;
  pP1PL9Ttl->Width      =C0Width;             pP1PL9Ttl->Height      =p1RowHeight;
  pP1L1C1Ttl->Left      =C0Width;             pP1L1C1Ttl->Top        =p1RowHeight*4;
  pP1L1C1Ttl->Width     =C1_6Width;           pP1L1C1Ttl->Height     =p1RowHeight;
  pP1L1C2Ttl->Left      =C0Width+C1_6Width;   pP1L1C2Ttl->Top        =p1RowHeight*4;
  pP1L1C2Ttl->Width     =C1_6Width;           pP1L1C2Ttl->Height     =p1RowHeight;
  pP1L1C3Ttl->Left      =C0Width+C1_6Width*2; pP1L1C3Ttl->Top        =p1RowHeight*4;
  pP1L1C3Ttl->Width     =C1_6Width;           pP1L1C3Ttl->Height     =p1RowHeight;
  pP1L1C4Ttl->Left      =C0Width+C1_6Width*3; pP1L1C4Ttl->Top        =p1RowHeight*4;
  pP1L1C4Ttl->Width     =C1_6Width;           pP1L1C4Ttl->Height     =p1RowHeight;
  pP1L1C5Ttl->Left      =C0Width+C1_6Width*4; pP1L1C5Ttl->Top        =p1RowHeight*4;
  pP1L1C5Ttl->Width     =C1_6Width;           pP1L1C5Ttl->Height     =p1RowHeight;
  pP1L1C6Ttl->Left      =C0Width+C1_6Width*5; pP1L1C6Ttl->Top        =p1RowHeight*4;
  pP1L1C6Ttl->Width     =C1_6Width;           pP1L1C6Ttl->Height     =p1RowHeight;
  stP1CParL1C1->Left    =C0Width;             stP1CParL1C1->Top      =p1RowHeight*5;
  stP1CParL1C1->Width   =C1_6Width;           stP1CParL1C1->Height   =p1RowHeight;
  stP1CParL1C2->Left    =C0Width+C1_6Width;   stP1CParL1C2->Top      =p1RowHeight*5;
  stP1CParL1C2->Width   =C1_6Width;           stP1CParL1C2->Height   =p1RowHeight;
  stP1CParL1C3->Left    =C0Width+C1_6Width*2; stP1CParL1C3->Top      =p1RowHeight*5;
  stP1CParL1C3->Width   =C1_6Width;           stP1CParL1C3->Height   =p1RowHeight;
  stP1CParL1C4->Left    =C0Width+C1_6Width*3; stP1CParL1C4->Top      =p1RowHeight*5;
  stP1CParL1C4->Width   =C1_6Width;           stP1CParL1C4->Height   =p1RowHeight;
  stP1CParL1C5->Left    =C0Width+C1_6Width*4; stP1CParL1C5->Top      =p1RowHeight*5;
  stP1CParL1C5->Width   =C1_6Width;           stP1CParL1C5->Height   =p1RowHeight;
  stP1CParL1C6->Left    =C0Width+C1_6Width*5; stP1CParL1C6->Top      =p1RowHeight*5;
  stP1CParL1C6->Width   =C1_6Width;           stP1CParL1C6->Height   =p1RowHeight;
  stP1CParL2C1->Left    =C0Width;             stP1CParL2C1->Top      =p1RowHeight*6;
  stP1CParL2C1->Width   =C1_6Width;           stP1CParL2C1->Height   =p1RowHeight;
  stP1CParL2C2->Left    =C0Width+C1_6Width;   stP1CParL2C2->Top      =p1RowHeight*6;
  stP1CParL2C2->Width   =C1_6Width;           stP1CParL2C2->Height   =p1RowHeight;
  stP1CParL2C3->Left    =C0Width+C1_6Width*2; stP1CParL2C3->Top      =p1RowHeight*6;
  stP1CParL2C3->Width   =C1_6Width;           stP1CParL2C3->Height   =p1RowHeight;
  stP1CParL2C4->Left    =C0Width+C1_6Width*3; stP1CParL2C4->Top      =p1RowHeight*6;
  stP1CParL2C4->Width   =C1_6Width;           stP1CParL2C4->Height   =p1RowHeight;
  stP1CParL2C5->Left    =C0Width+C1_6Width*4; stP1CParL2C5->Top      =p1RowHeight*6;
  stP1CParL2C5->Width   =C1_6Width;           stP1CParL2C5->Height   =p1RowHeight;
  stP1CParL2C6->Left    =C0Width+C1_6Width*5; stP1CParL2C6->Top      =p1RowHeight*6;
  stP1CParL2C6->Width   =C1_6Width;           stP1CParL2C6->Height   =p1RowHeight;
  stP1CParL3C1->Left    =C0Width;             stP1CParL3C1->Top      =p1RowHeight*7;
  stP1CParL3C1->Width   =C1_6Width;           stP1CParL3C1->Height   =p1RowHeight;
  stP1CParL3C2->Left    =C0Width+C1_6Width;   stP1CParL3C2->Top      =p1RowHeight*7;
  stP1CParL3C2->Width   =C1_6Width;           stP1CParL3C2->Height   =p1RowHeight;
  stP1CParL3C3->Left    =C0Width+C1_6Width*2; stP1CParL3C3->Top      =p1RowHeight*7;
  stP1CParL3C3->Width   =C1_6Width;           stP1CParL3C3->Height   =p1RowHeight;
  stP1CParL3C4->Left    =C0Width+C1_6Width*3; stP1CParL3C4->Top      =p1RowHeight*7;
  stP1CParL3C4->Width   =C1_6Width;           stP1CParL3C4->Height   =p1RowHeight;
  stP1CParL3C5->Left    =C0Width+C1_6Width*4; stP1CParL3C5->Top      =p1RowHeight*7;
  stP1CParL3C5->Width   =C1_6Width;           stP1CParL3C5->Height   =p1RowHeight;
  stP1CParL3C6->Left    =C0Width+C1_6Width*5; stP1CParL3C6->Top      =p1RowHeight*7;
  stP1CParL3C6->Width   =C1_6Width;           stP1CParL3C6->Height   =p1RowHeight;
  stP1CParL4C1->Left    =C0Width;             stP1CParL4C1->Top      =p1RowHeight*8;
  stP1CParL4C1->Width   =C1_6Width;           stP1CParL4C1->Height   =p1RowHeight;
  stP1CParL4C2->Left    =C0Width+C1_6Width;   stP1CParL4C2->Top      =p1RowHeight*8;
  stP1CParL4C2->Width   =C1_6Width;           stP1CParL4C2->Height   =p1RowHeight;
  stP1CParL4C3->Left    =C0Width+C1_6Width*2; stP1CParL4C3->Top      =p1RowHeight*8;
  stP1CParL4C3->Width   =C1_6Width;           stP1CParL4C3->Height   =p1RowHeight;
  stP1CParL4C4->Left    =C0Width+C1_6Width*3; stP1CParL4C4->Top      =p1RowHeight*8;
  stP1CParL4C4->Width   =C1_6Width;           stP1CParL4C4->Height   =p1RowHeight;
  stP1CParL4C5->Left    =C0Width+C1_6Width*4; stP1CParL4C5->Top      =p1RowHeight*8;
  stP1CParL4C5->Width   =C1_6Width;           stP1CParL4C5->Height   =p1RowHeight;
  stP1CParL4C6->Left    =C0Width+C1_6Width*5; stP1CParL4C6->Top      =p1RowHeight*8;
  stP1CParL4C6->Width   =C1_6Width;           stP1CParL4C6->Height   =p1RowHeight;
  stP1CParL5C1->Left    =C0Width;             stP1CParL5C1->Top      =p1RowHeight*9;
  stP1CParL5C1->Width   =C1_6Width;           stP1CParL5C1->Height   =p1RowHeight;
  stP1CParL5C2->Left    =C0Width+C1_6Width;   stP1CParL5C2->Top      =p1RowHeight*9;
  stP1CParL5C2->Width   =C1_6Width;           stP1CParL5C2->Height   =p1RowHeight;
  stP1CParL5C3->Left    =C0Width+C1_6Width*2; stP1CParL5C3->Top      =p1RowHeight*9;
  stP1CParL5C3->Width   =C1_6Width;           stP1CParL5C3->Height   =p1RowHeight;
  stP1CParL5C4->Left    =C0Width+C1_6Width*3; stP1CParL5C4->Top      =p1RowHeight*9;
  stP1CParL5C4->Width   =C1_6Width;           stP1CParL5C4->Height   =p1RowHeight;
  stP1CParL5C5->Left    =C0Width+C1_6Width*4; stP1CParL5C5->Top      =p1RowHeight*9;
  stP1CParL5C5->Width   =C1_6Width;           stP1CParL5C5->Height   =p1RowHeight;
  stP1CParL5C6->Left    =C0Width+C1_6Width*5; stP1CParL5C6->Top      =p1RowHeight*9;
  stP1CParL5C6->Width   =C1_6Width;           stP1CParL5C6->Height   =p1RowHeight;
  stP1CParL6C1->Left    =C0Width;             stP1CParL6C1->Top      =p1RowHeight*10;
  stP1CParL6C1->Width   =C1_6Width;           stP1CParL6C1->Height   =p1RowHeight;
  stP1CParL6C2->Left    =C0Width+C1_6Width;   stP1CParL6C2->Top      =p1RowHeight*10;
  stP1CParL6C2->Width   =C1_6Width;           stP1CParL6C2->Height   =p1RowHeight;
  stP1CParL6C3->Left    =C0Width+C1_6Width*2; stP1CParL6C3->Top      =p1RowHeight*10;
  stP1CParL6C3->Width   =C1_6Width;           stP1CParL6C3->Height   =p1RowHeight;
  stP1CParL6C4->Left    =C0Width+C1_6Width*3; stP1CParL6C4->Top      =p1RowHeight*10;
  stP1CParL6C4->Width   =C1_6Width;           stP1CParL6C4->Height   =p1RowHeight;
  stP1CParL6C5->Left    =C0Width+C1_6Width*4; stP1CParL6C5->Top      =p1RowHeight*10;
  stP1CParL6C5->Width   =C1_6Width;           stP1CParL6C5->Height   =p1RowHeight;
  stP1CParL6C6->Left    =C0Width+C1_6Width*5; stP1CParL6C6->Top      =p1RowHeight*10;
  stP1CParL6C6->Width   =C1_6Width;           stP1CParL6C6->Height   =p1RowHeight;
  stP1CParL7C1->Left    =C0Width;             stP1CParL7C1->Top      =p1RowHeight*11;
  stP1CParL7C1->Width   =C1_6Width;           stP1CParL7C1->Height   =p1RowHeight;
  stP1CParL7C2->Left    =C0Width+C1_6Width;   stP1CParL7C2->Top      =p1RowHeight*11;
  stP1CParL7C2->Width   =C1_6Width;           stP1CParL7C2->Height   =p1RowHeight;
  stP1CParL7C3->Left    =C0Width+C1_6Width*2; stP1CParL7C3->Top      =p1RowHeight*11;
  stP1CParL7C3->Width   =C1_6Width;           stP1CParL7C3->Height   =p1RowHeight;
  stP1CParL7C4->Left    =C0Width+C1_6Width*3; stP1CParL7C4->Top      =p1RowHeight*11;
  stP1CParL7C4->Width   =C1_6Width;           stP1CParL7C4->Height   =p1RowHeight;
  stP1CParL7C5->Left    =C0Width+C1_6Width*4; stP1CParL7C5->Top      =p1RowHeight*11;
  stP1CParL7C5->Width   =C1_6Width;           stP1CParL7C5->Height   =p1RowHeight;
  stP1CParL7C6->Left    =C0Width+C1_6Width*5; stP1CParL7C6->Top      =p1RowHeight*11;
  stP1CParL7C6->Width   =C1_6Width;           stP1CParL7C6->Height   =p1RowHeight;
  stP1CParL8C1->Left    =C0Width;             stP1CParL8C1->Top      =p1RowHeight*12;
  stP1CParL8C1->Width   =C1_6Width;           stP1CParL8C1->Height   =p1RowHeight;
  stP1CParL8C2->Left    =C0Width+C1_6Width;   stP1CParL8C2->Top      =p1RowHeight*12;
  stP1CParL8C2->Width   =C1_6Width;           stP1CParL8C2->Height   =p1RowHeight;
  stP1CParL8C3->Left    =C0Width+C1_6Width*2; stP1CParL8C3->Top      =p1RowHeight*12;
  stP1CParL8C3->Width   =C1_6Width;           stP1CParL8C3->Height   =p1RowHeight;
  stP1CParL8C4->Left    =C0Width+C1_6Width*3; stP1CParL8C4->Top      =p1RowHeight*12;
  stP1CParL8C4->Width   =C1_6Width;           stP1CParL8C4->Height   =p1RowHeight;
  stP1CParL8C5->Left    =C0Width+C1_6Width*4; stP1CParL8C5->Top      =p1RowHeight*12;
  stP1CParL8C5->Width   =C1_6Width;           stP1CParL8C5->Height   =p1RowHeight;
  stP1CParL8C6->Left    =C0Width+C1_6Width*5; stP1CParL8C6->Top      =p1RowHeight*12;
  stP1CParL8C6->Width   =C1_6Width;           stP1CParL8C6->Height   =p1RowHeight;
  C0Width=pParam2Width/4;
  C1_6Width=(pParam2Width-C0Width)/6;
  C1_4Width=C1_6Width*3/2/3*3;
  C1_6Width=C1_4Width/3*2;
  C0Width=pParam2Width-C1_6Width*6;
  p1RowHeight=pParam2Height/9;
  if(p1RowHeight>30)p1RowHeight=30;
  pP2TtlL0C1->Left      =C0Width;             pP2TtlL0C1->Top        =0;
  pP2TtlL0C1->Width     =C1_4Width*2;         pP2TtlL0C1->Height     =p1RowHeight;
  pP2TtlL0C2->Left      =C0Width+C1_4Width*2; pP2TtlL0C2->Top        =0;
  pP2TtlL0C2->Width     =C1_4Width*2;         pP2TtlL0C2->Height     =p1RowHeight;
  pP2TtlL1C1->Left      =C0Width;             pP2TtlL1C1->Top        =p1RowHeight;
  pP2TtlL1C1->Width     =C1_4Width;           pP2TtlL1C1->Height     =p1RowHeight;
  pP2TtlL1C2->Left      =C0Width+C1_4Width;   pP2TtlL1C2->Top        =p1RowHeight;
  pP2TtlL1C2->Width     =C1_4Width;           pP2TtlL1C2->Height     =p1RowHeight;
  pP2TtlL1C3->Left      =C0Width+C1_4Width*2; pP2TtlL1C3->Top        =p1RowHeight;
  pP2TtlL1C3->Width     =C1_4Width;           pP2TtlL1C3->Height     =p1RowHeight;
  pP2TtlL1C4->Left      =C0Width+C1_4Width*3; pP2TtlL1C4->Top        =p1RowHeight;
  pP2TtlL1C4->Width     =C1_4Width;           pP2TtlL1C4->Height     =p1RowHeight;
  pP2TtlL1C0->Left      =0;                   pP2TtlL1C0->Top        =p1RowHeight*2;
  pP2TtlL1C0->Width     =C0Width;             pP2TtlL1C0->Height     =p1RowHeight;
  pP2TtlL2C0->Left      =0;                   pP2TtlL2C0->Top        =p1RowHeight*3;
  pP2TtlL2C0->Width     =C0Width;             pP2TtlL2C0->Height     =p1RowHeight;
  pP2TtlL3C0->Left      =0;                   pP2TtlL3C0->Top        =p1RowHeight*4;
  pP2TtlL3C0->Width     =C0Width;             pP2TtlL3C0->Height     =p1RowHeight;
  pP2TtlL4C0->Left      =0;                   pP2TtlL4C0->Top        =p1RowHeight*5;
  pP2TtlL4C0->Width     =C0Width;             pP2TtlL4C0->Height     =p1RowHeight;
  pP2TtlL5C0->Left      =0;                   pP2TtlL5C0->Top        =p1RowHeight*6;
  pP2TtlL5C0->Width     =C0Width;             pP2TtlL5C0->Height     =p1RowHeight;
  pP2TtlL6C0->Left      =0;                   pP2TtlL6C0->Top        =p1RowHeight*7;
  pP2TtlL6C0->Width     =C0Width;             pP2TtlL6C0->Height     =p1RowHeight;
  pP2TtlL7C0->Left      =0;                   pP2TtlL7C0->Top        =p1RowHeight*8;
  pP2TtlL7C0->Width     =C0Width;             pP2TtlL7C0->Height     =p1RowHeight;
  stP2CParL1C1->Left    =C0Width;             stP2CParL1C1->Top      =p1RowHeight*2;
  stP2CParL1C1->Width   =C1_4Width;           stP2CParL1C1->Height   =p1RowHeight;
  stP2CParL1C2->Left    =C0Width+C1_4Width;   stP2CParL1C2->Top      =p1RowHeight*2;
  stP2CParL1C2->Width   =C1_4Width;           stP2CParL1C2->Height   =p1RowHeight;
  stP2CParL1C3->Left    =C0Width+C1_4Width*2; stP2CParL1C3->Top      =p1RowHeight*2;
  stP2CParL1C3->Width   =C1_4Width;           stP2CParL1C3->Height   =p1RowHeight;
  stP2CParL1C4->Left    =C0Width+C1_4Width*3; stP2CParL1C4->Top      =p1RowHeight*2;
  stP2CParL1C4->Width   =C1_4Width;           stP2CParL1C4->Height   =p1RowHeight;

  stP2CParL2C1->Left    =C0Width;             stP2CParL2C1->Top      =p1RowHeight*3;
  stP2CParL2C1->Width   =C1_4Width;           stP2CParL2C1->Height   =p1RowHeight;
  stP2CParL2C2->Left    =C0Width+C1_4Width;   stP2CParL2C2->Top      =p1RowHeight*3;
  stP2CParL2C2->Width   =C1_4Width;           stP2CParL2C2->Height   =p1RowHeight;
  stP2CParL2C3->Left    =C0Width+C1_4Width*2; stP2CParL2C3->Top      =p1RowHeight*3;
  stP2CParL2C3->Width   =C1_4Width;           stP2CParL2C3->Height   =p1RowHeight;
  stP2CParL2C4->Left    =C0Width+C1_4Width*3; stP2CParL2C4->Top      =p1RowHeight*3;
  stP2CParL2C4->Width   =C1_4Width;           stP2CParL2C4->Height   =p1RowHeight;

  stP2CParL3C1->Left    =C0Width;             stP2CParL3C1->Top      =p1RowHeight*4;
  stP2CParL3C1->Width   =C1_4Width;           stP2CParL3C1->Height   =p1RowHeight;
  stP2CParL3C2->Left    =C0Width+C1_4Width;   stP2CParL3C2->Top      =p1RowHeight*4;
  stP2CParL3C2->Width   =C1_4Width;           stP2CParL3C2->Height   =p1RowHeight;
  stP2CParL3C3->Left    =C0Width+C1_4Width*2; stP2CParL3C3->Top      =p1RowHeight*4;
  stP2CParL3C3->Width   =C1_4Width;           stP2CParL3C3->Height   =p1RowHeight;
  stP2CParL3C4->Left    =C0Width+C1_4Width*3; stP2CParL3C4->Top      =p1RowHeight*4;
  stP2CParL3C4->Width   =C1_4Width;           stP2CParL3C4->Height   =p1RowHeight;

  stP2CParL4C1->Left    =C0Width;             stP2CParL4C1->Top      =p1RowHeight*5;
  stP2CParL4C1->Width   =C1_4Width;           stP2CParL4C1->Height   =p1RowHeight;
  stP2CParL4C2->Left    =C0Width+C1_4Width;   stP2CParL4C2->Top      =p1RowHeight*5;
  stP2CParL4C2->Width   =C1_4Width;           stP2CParL4C2->Height   =p1RowHeight;
  stP2CParL4C3->Left    =C0Width+C1_4Width*2; stP2CParL4C3->Top      =p1RowHeight*5;
  stP2CParL4C3->Width   =C1_4Width;           stP2CParL4C3->Height   =p1RowHeight;
  stP2CParL4C4->Left    =C0Width+C1_4Width*3; stP2CParL4C4->Top      =p1RowHeight*5;
  stP2CParL4C4->Width   =C1_4Width;           stP2CParL4C4->Height   =p1RowHeight;

  stP2CParL5C1->Left    =C0Width;             stP2CParL5C1->Top      =p1RowHeight*6;
  stP2CParL5C1->Width   =C1_4Width;           stP2CParL5C1->Height   =p1RowHeight;
  stP2CParL5C2->Left    =C0Width+C1_4Width;   stP2CParL5C2->Top      =p1RowHeight*6;
  stP2CParL5C2->Width   =C1_4Width;           stP2CParL5C2->Height   =p1RowHeight;
  stP2CParL5C3->Left    =C0Width+C1_4Width*2; stP2CParL5C3->Top      =p1RowHeight*6;
  stP2CParL5C3->Width   =C1_4Width;           stP2CParL5C3->Height   =p1RowHeight;
  stP2CParL5C4->Left    =C0Width+C1_4Width*3; stP2CParL5C4->Top      =p1RowHeight*6;
  stP2CParL5C4->Width   =C1_4Width;           stP2CParL5C4->Height   =p1RowHeight;

  stP2CParL6C1->Left    =C0Width;             stP2CParL6C1->Top      =p1RowHeight*7;
  stP2CParL6C1->Width   =C1_4Width;           stP2CParL6C1->Height   =p1RowHeight;
  stP2CParL6C2->Left    =C0Width+C1_4Width;   stP2CParL6C2->Top      =p1RowHeight*7;
  stP2CParL6C2->Width   =C1_4Width;           stP2CParL6C2->Height   =p1RowHeight;
  stP2CParL6C3->Left    =C0Width+C1_4Width*2; stP2CParL6C3->Top      =p1RowHeight*7;
  stP2CParL6C3->Width   =C1_4Width;           stP2CParL6C3->Height   =p1RowHeight;
  stP2CParL6C4->Left    =C0Width+C1_4Width*3; stP2CParL6C4->Top      =p1RowHeight*7;
  stP2CParL6C4->Width   =C1_4Width;           stP2CParL6C4->Height   =p1RowHeight;

  stP2CParL7C1->Left    =C0Width;             stP2CParL7C1->Top      =p1RowHeight*8;
  stP2CParL7C1->Width   =C1_4Width;           stP2CParL7C1->Height   =p1RowHeight;
  stP2CParL7C2->Left    =C0Width+C1_4Width;   stP2CParL7C2->Top      =p1RowHeight*8;
  stP2CParL7C2->Width   =C1_4Width;           stP2CParL7C2->Height   =p1RowHeight;
  stP2CParL7C3->Left    =C0Width+C1_4Width*2; stP2CParL7C3->Top      =p1RowHeight*8;
  stP2CParL7C3->Width   =C1_4Width;           stP2CParL7C3->Height   =p1RowHeight;
  stP2CParL7C4->Left    =C0Width+C1_4Width*3; stP2CParL7C4->Top      =p1RowHeight*8;
  stP2CParL7C4->Width   =C1_4Width;           stP2CParL7C4->Height   =p1RowHeight;
}
//---- End of DesignCmmnParPanel --------------------------------------------

void __fastcall TmfRB::DesignManualPanel(void) // расположение компонент на панели ручного управления
{
  int gbHeight=tsManualHeight-20;
  int gbWidth1=tsManualWidth/19*5;
  int gbWidth2=(tsManualWidth-gbWidth1-30)/2;
  int leWidth=leCurrentLoad1->EditLabel->Width+2;
  int leEdHeight=leCurrentLoad1->EditLabel->Height+2;
  int leHeight=30;
  int TickdH             =(gbHeight)/22-3;
  gbCarriage1->Left      =10;                   gbCarriage1->Top        =10;
  gbCarriage1->Width     =gbWidth2;             gbCarriage1->Height     =gbHeight;

  pCarr1Load->Left       =10;                   pCarr1Load->Top         =20;
  pCarr1Load->Width      =gbWidth2-20;          pCarr1Load->Height      =26;
  leCurrentLoad1->Left   =30;                   leCurrentLoad1->Top     =56+leEdHeight;
  leCurrentLoad1->Width  =leWidth;              leCurrentLoad1->Height  =leHeight;
  leSetLoad1->Left       =30;                   leSetLoad1->Top         =56+leEdHeight*2+20+leHeight;
  leSetLoad1->Width      =leWidth;              leSetLoad1->Height      =leHeight;
  tbCurrentLoad1->Left   =leWidth*2+30;         tbCurrentLoad1->Top     =leCurrentLoad1->Top-leEdHeight;
  tbCurrentLoad1->Width  =50;                   tbCurrentLoad1->Height  =gbHeight/2;
  leCurrentT1->Left      =leWidth*2+20;         leCurrentT1->Top        =tbCurrentLoad1->Top+gbHeight/2+5;
  leCurrentT1->Width     =leWidth;              leCurrentT1->Height     =leHeight;
  leCurrentR1->Left      =leWidth*2+20;         leCurrentR1->Top        =leCurrentT1->Top+leHeight+10;
  leCurrentR1->Width     =leWidth;              leCurrentR1->Height     =leHeight;
  lLoad0->Left           =leWidth*2+85;         lLoad0->Top             =tbCurrentLoad1->Top+gbHeight/2-27;
  lLoad0->Width          =30;                   lLoad0->Height          =20;
  lLoad10->Left          =leWidth*2+85;         lLoad10->Top            =tbCurrentLoad1->Top+gbHeight/2-27-TickdH;
  lLoad10->Width         =30;                   lLoad10->Height         =20;
  lLoad20->Left          =leWidth*2+85;         lLoad20->Top            =tbCurrentLoad1->Top+gbHeight/2-27-TickdH*2;
  lLoad20->Width         =30;                   lLoad20->Height         =20;
  lLoad30->Left          =leWidth*2+85;         lLoad30->Top            =tbCurrentLoad1->Top+gbHeight/2-27-TickdH*3;
  lLoad30->Width         =30;                   lLoad30->Height         =20;
  lLoad40->Left          =leWidth*2+85;         lLoad40->Top            =tbCurrentLoad1->Top+gbHeight/2-27-TickdH*4;
  lLoad40->Width         =30;                   lLoad40->Height         =20;
  lLoad50->Left          =leWidth*2+85;         lLoad50->Top            =tbCurrentLoad1->Top+gbHeight/2-27-TickdH*5;
  lLoad50->Width         =30;                   lLoad50->Height         =20;
  lLoad60->Left          =leWidth*2+85;         lLoad60->Top            =tbCurrentLoad1->Top+gbHeight/2-27-TickdH*6;
  lLoad60->Width         =30;                   lLoad60->Height         =20;
  lLoad70->Left          =leWidth*2+85;         lLoad70->Top            =tbCurrentLoad1->Top+gbHeight/2-27-TickdH*7;
  lLoad70->Width         =30;                   lLoad70->Height         =20;
  lLoad80->Left          =leWidth*2+85;         lLoad80->Top            =tbCurrentLoad1->Top+gbHeight/2-27-TickdH*8;
  lLoad80->Width         =30;                   lLoad80->Height         =20;
  lLoad90->Left          =leWidth*2+85;         lLoad90->Top            =tbCurrentLoad1->Top+gbHeight/2-27-TickdH*9;
  lLoad90->Width         =30;                   lLoad90->Height         =20;
  lLoad100->Left         =leWidth*2+85;         lLoad100->Top           =tbCurrentLoad1->Top+gbHeight/2-27-TickdH*10;
  lLoad100->Width        =30;                   lLoad100->Height        =20;
  lLoad110->Left         =leWidth*2+85;         lLoad110->Top           =tbCurrentLoad1->Top+gbHeight/2-27-TickdH*11;
  lLoad110->Width        =30;                   lLoad110->Height        =20;
  pCarr1Ttl->Left        =10;                   pCarr1Ttl->Top          =leCurrentR1->Top+leHeight+10;
  pCarr1Ttl->Width       =gbWidth2-20;          pCarr1Ttl->Height       =26;
  int btnTop             =pCarr1Ttl->Top+36;
  btnCarriage1From->Left =5;                    btnCarriage1From->Top   =btnTop;
  btnCarriage1From->Width=112;                  btnCarriage1From->Height=40;
  btnCarriage1Stop->Left =(gbWidth2-286)/2+117; btnCarriage1Stop->Top   =btnTop;
  btnCarriage1Stop->Width=62;                   btnCarriage1Stop->Height=40;
  btnCarriage1To->Left   =gbWidth2-5-102;       btnCarriage1To->Top     =btnTop;
  btnCarriage1To->Width  =102;                  btnCarriage1To->Height  =40;
  sbCarr1Fm->Left        =5;                    sbCarr1Fm->Top          =btnTop+45;
  sbCarr1Fm->Width       =25;                   sbCarr1Fm->Height       =26;
  sbCarr1To->Left        =gbWidth2-5-25;        sbCarr1To->Top          =btnTop+45;
  sbCarr1To->Width       =25;                   sbCarr1To->Height       =26;
  sbCarriage1Off->Left   =5;                    sbCarriage1Off->Top     =btnTop+76;
  sbCarriage1Off->Width  =25;                   sbCarriage1Off->Height  =26;
  lCarriage1Off->Left    =33;                   lCarriage1Off->Top      =btnTop+76;
  lCarriage1Off->Width   =165;                  lCarriage1Off->Height   =26;

  gbCarriage2->Left      =gbWidth1+gbWidth2+20; gbCarriage2->Top        =10;
  gbCarriage2->Width     =gbWidth2;             gbCarriage2->Height     =gbHeight;
  pCarr2Load->Left       =10;                   pCarr2Load->Top         =20;
  pCarr2Load->Width      =gbWidth2-20;          pCarr2Load->Height      =26;
  leCurrentLoad2->Left   =30;                   leCurrentLoad2->Top     =56+leEdHeight;
  leCurrentLoad2->Width  =leWidth;              leCurrentLoad2->Height  =leHeight;
  leSetLoad2->Left       =30;                   leSetLoad2->Top         =56+leEdHeight*2+20+leHeight;
  leSetLoad2->Width      =leWidth;              leSetLoad2->Height      =leHeight;
  tbCurrentLoad2->Left   =leWidth*2+30;         tbCurrentLoad2->Top     =leCurrentLoad2->Top-leEdHeight;
  tbCurrentLoad2->Width  =50;                   tbCurrentLoad2->Height  =gbHeight/2;
  leCurrentT2->Left      =leWidth*2+20;         leCurrentT2->Top        =tbCurrentLoad2->Top+gbHeight/2+5;
  leCurrentT2->Width     =leWidth;              leCurrentT2->Height     =leHeight;
  leCurrentR2->Left      =leWidth*2+20;         leCurrentR2->Top        =leCurrentT2->Top+leHeight+10;
  leCurrentR2->Width     =leWidth;              leCurrentR2->Height     =leHeight;
  l2Load00->Left         =leWidth*2+85;         l2Load00->Top           =tbCurrentLoad2->Top+gbHeight/2-27;
  l2Load00->Width        =30;                   l2Load00->Height        =20;
  l2Load10->Left         =leWidth*2+85;         l2Load10->Top           =tbCurrentLoad2->Top+gbHeight/2-27-TickdH;
  l2Load10->Width        =30;                   l2Load10->Height        =20;
  l2Load20->Left         =leWidth*2+85;         l2Load20->Top           =tbCurrentLoad2->Top+gbHeight/2-27-TickdH*2;
  l2Load20->Width        =30;                   l2Load20->Height        =20;
  l2Load30->Left         =leWidth*2+85;         l2Load30->Top           =tbCurrentLoad2->Top+gbHeight/2-27-TickdH*3;
  l2Load30->Width        =30;                   l2Load30->Height        =20;
  l2Load40->Left         =leWidth*2+85;         l2Load40->Top           =tbCurrentLoad2->Top+gbHeight/2-27-TickdH*4;
  l2Load40->Width        =30;                   l2Load40->Height        =20;
  l2Load50->Left         =leWidth*2+85;         l2Load50->Top           =tbCurrentLoad2->Top+gbHeight/2-27-TickdH*5;
  l2Load50->Width        =30;                   l2Load50->Height        =20;
  l2Load60->Left         =leWidth*2+85;         l2Load60->Top           =tbCurrentLoad2->Top+gbHeight/2-27-TickdH*6;
  l2Load60->Width        =30;                   l2Load60->Height        =20;
  l2Load70->Left         =leWidth*2+85;         l2Load70->Top           =tbCurrentLoad2->Top+gbHeight/2-27-TickdH*7;
  l2Load70->Width        =30;                   l2Load70->Height        =20;
  l2Load80->Left         =leWidth*2+85;         l2Load80->Top           =tbCurrentLoad2->Top+gbHeight/2-27-TickdH*8;
  l2Load80->Width        =30;                   l2Load80->Height        =20;
  l2Load90->Left         =leWidth*2+85;         l2Load90->Top           =tbCurrentLoad2->Top+gbHeight/2-27-TickdH*9;
  l2Load90->Width        =30;                   l2Load90->Height        =20;
  l2Load100->Left        =leWidth*2+85;         l2Load100->Top          =tbCurrentLoad2->Top+gbHeight/2-27-TickdH*10;
  l2Load100->Width       =30;                   l2Load100->Height       =20;
  l2Load110->Left        =leWidth*2+85;         l2Load110->Top          =tbCurrentLoad2->Top+gbHeight/2-27-TickdH*11;
  l2Load110->Width       =30;                   l2Load110->Height       =20;
  pCarr2Ttl->Left        =10;                   pCarr2Ttl->Top          =leCurrentR2->Top+leHeight+10;
  pCarr2Ttl->Width       =gbWidth2-20;          pCarr2Ttl->Height       =26;
  btnTop             =pCarr2Ttl->Top+36;
  btnCarriage2To->Left   =5;                    btnCarriage2To->Top     =btnTop;
  btnCarriage2To->Width  =102;                  btnCarriage2To->Height  =40;
  btnCarriage2Stop->Left =(gbWidth2-294)/2+107; btnCarriage2Stop->Top   =btnTop;
  btnCarriage2Stop->Width=62;                   btnCarriage2Stop->Height=40;
  btnCarriage2From->Left =gbWidth2-5-120;       btnCarriage2From->Top   =btnTop;
  btnCarriage2From->Width=120;                  btnCarriage2From->Height=40;
  sbCarr2To->Left        =5;                    sbCarr2To->Top          =btnTop+45;
  sbCarr2To->Width       =25;                   sbCarr2To->Height       =26;
  sbCarr2Fm->Left        =gbWidth2-5-25;        sbCarr2Fm->Top          =btnTop+45;
  sbCarr2Fm->Width       =25;                   sbCarr2Fm->Height       =26;
  sbCarriage2Off->Left   =gbWidth2-5-25;        sbCarriage2Off->Top     =btnTop+76;
  sbCarriage2Off->Width  =25;                   sbCarriage2Off->Height  =26;
  lCarriage2Off->Left    =gbWidth2-5-25-150;    lCarriage2Off->Top      =btnTop+76;
  lCarriage2Off->Width   =150;                  lCarriage2Off->Height   =26;

  gbDrum->Left             =gbWidth2+15;        gbDrum->Top               =10;
  gbDrum->Width            =gbWidth1;           gbDrum->Height            =gbHeight;
  pDrumSpeed->Left         =10;                 pDrumSpeed->Top           =20;
  pDrumSpeed->Width        =gbWidth1-20;        pDrumSpeed->Height        =26;
  leCurrentDrumSpeed->Left =20;                 leCurrentDrumSpeed->Top   =56+leEdHeight;
  leCurrentDrumSpeed->Width=leWidth;            leCurrentDrumSpeed->Height=leHeight;
  leSetDrumSpeed->Left     =20;                 leSetDrumSpeed->Top       =56+leEdHeight*2+20+leHeight;
  leSetDrumSpeed->Width    =leWidth;            leSetDrumSpeed->Height    =leHeight;
  tbCurrentDrumSpeed->Left =leWidth+30;         tbCurrentDrumSpeed->Top   =leCurrentDrumSpeed->Top-leEdHeight;
  tbCurrentDrumSpeed->Width=50;                 tbCurrentDrumSpeed->Height=gbHeight/5*3;
  TickdH                   =(gbHeight)/5*3/10-3;
  int tbDSTop              =tbCurrentDrumSpeed->Top+gbHeight/5*3-27;
  int TickLeft             =leWidth*2+20;
  lSpeed00->Left           =TickLeft;           lSpeed00->Top             =tbDSTop;
  lSpeed00->Width          =30;                 lSpeed00->Height          =20;
  lSpeed20->Left           =TickLeft;           lSpeed20->Top             =tbDSTop-TickdH;
  lSpeed20->Width          =30;                 lSpeed20->Height          =20;
  lSpeed40->Left           =TickLeft;           lSpeed40->Top             =tbDSTop-TickdH*2+1;
  lSpeed40->Width          =30;                 lSpeed40->Height          =20;
  lSpeed60->Left           =TickLeft;           lSpeed60->Top             =tbDSTop-TickdH*3;
  lSpeed60->Width          =30;                 lSpeed60->Height          =20;
  lSpeed80->Left           =TickLeft;           lSpeed80->Top             =tbDSTop-TickdH*4+1;
  lSpeed80->Width          =30;                 lSpeed80->Height          =20;
  lSpeed100->Left          =TickLeft;           lSpeed100->Top            =tbDSTop-TickdH*5;
  lSpeed100->Width         =30;                 lSpeed100->Height         =20;
  lSpeed120->Left          =TickLeft;           lSpeed120->Top            =tbDSTop-TickdH*6-3;
  lSpeed120->Width         =30;                 lSpeed120->Height         =20;
  lSpeed140->Left          =TickLeft;           lSpeed140->Top            =tbDSTop-TickdH*7-4;
  lSpeed140->Width         =30;                 lSpeed140->Height         =20;
  lSpeed160->Left          =TickLeft;           lSpeed160->Top            =tbDSTop-TickdH*8-4;
  lSpeed160->Width         =30;                 lSpeed160->Height         =20;
  lSpeed180->Left          =TickLeft;           lSpeed180->Top            =tbDSTop-TickdH*9-4;
  lSpeed180->Width         =30;                 lSpeed180->Height         =20;
  lSpeed200->Left          =TickLeft;           lSpeed200->Top            =tbDSTop-TickdH*10-5;
  lSpeed200->Width         =30;                 lSpeed200->Height         =20;
  sbDrumOn->Left           =10;                 sbDrumOn->Top             =tbDSTop;
  sbDrumOn->Width          =25;                 sbDrumOn->Height          =26;
  pDrumTtl->Left           =10;                 pDrumTtl->Top             =pCarr1Ttl->Top;
  pDrumTtl->Width          =gbWidth1-20;        pDrumTtl->Height          =26;
  btnDrumOn->Left          =(gbWidth1-150)/2;   btnDrumOn->Top            =btnTop;
  btnDrumOn->Width         =150;                btnDrumOn->Height         =40;
  btnDrumOff->Left         =(gbWidth1-150)/2;   btnDrumOff->Top           =btnTop+60;
  btnDrumOff->Width        =150;                btnDrumOff->Height        =40;
}
//---- End of DesignManualPanel ---------------------------------------------

void __fastcall TmfRB::ShowTProg(void)         // отобразить программу по времени на экране
{
  leTProgName->Text=TProgName;
  leTTyrePressure->Text=FloatToStrF(TTyrePressure,ffFixed,6,1);
  leTTotalStepsQty->Text=String(total_step_T);
  leTotalTestTime->Text=mSecToHMSStr(total_T);
  leTPollingTotalQty->Text=String(num_T_poll);
  for (int i = 0; i < total_step_T; i++) {
    sgTProgram->Cells[1][i+1]=FloatToStrF(Tsettings[0][i],ffFixed,6,2);
    sgTProgram->Cells[2][i+1]=FloatToStrF(Tsettings[1][i],ffFixed,6,2);
    sgTProgram->Cells[3][i+1]=String(prog_step_T[i]/1000/3600);
    sgTProgram->Cells[4][i+1]=String((prog_step_T[i]/1000-prog_step_T[i]/1000/3600*3600)/60);
  }
  for (int i = 0; i < num_T_poll; i++) {
    sgTPolling->Cells[1][i+1]=String(poll_step_T[i]/1000/3600);
    sgTPolling->Cells[2][i+1]=String((poll_step_T[i]/1000-poll_step_T[i]/1000/3600*3600)/60);
  }
}
//---- End of ShowTProg -----------------------------------------------------

void __fastcall TmfRB::ShowSProg(void)         // отобразить программу по пути на экране
{
  leSProgName->Text=SProgName;
  leSTyrePressure->Text=FloatToStrF(STyrePressure,ffFixed,6,1);
  leSTotalStepsQty->Text=String(total_step_S);
  leTotalTestS->Text=FloatToStrF(total_S,ffFixed,7,2);
  leSPollingTotalQty->Text=String(num_S_poll);
  for (int i = 0; i < total_step_S; i++) {
    sgSProgram->Cells[1][i+1]=FloatToStrF(Ssettings[0][i],ffFixed,6,2);
    sgSProgram->Cells[2][i+1]=FloatToStrF(Ssettings[1][i],ffFixed,6,2);
    sgSProgram->Cells[3][i+1]=FloatToStrF(prog_step_S[i],ffFixed,6,2);
  }
  for (int i = 0; i < num_S_poll; i++) {
    sgSPolling->Cells[1][i+1]=FloatToStrF(poll_step_S[i],ffFixed,6,2);
  }
}
//---- End of ShowSProg -----------------------------------------------------

void __fastcall TmfRB::OnNewTProg(TObject *Sender)
{
  leTProgName->Text="";             TProgName="";
  leTTyrePressure->Text="";         TTyrePressure=0.0;
  leTTotalStepsQty->Text="";        total_step_T=0;
  leTotalTestTime->Text="00:00:00"; total_T=0;
  leTPollingTotalQty->Text="";      num_T_poll=0;
  for (int i = 0; i < MAXNUMOFSTEPS; i++) {
    sgTProgram->Cells[1][i+1]="";
    sgTProgram->Cells[2][i+1]="";
    sgTProgram->Cells[3][i+1]="";
    sgTProgram->Cells[4][i+1]="";
  }
  for (int i = 0; i < MAXNUMOFPOLLS; i++) {
	sgTPolling->Cells[1][i+1]="";
	sgTPolling->Cells[2][i+1]="";
  }
  	ClearTProg();//удаление старых данных из массивов
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnSGTEnter(TObject *Sender)
{
  btnCheckTProg->Enabled=true;
  btnSaveTProgToFile->Enabled=false;
  btnLoadTProgToPosA->Enabled=false;
  btnLoadTProgToPosB->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnSProgCheck(TObject *Sender)
{
	ClearSProg();//чистка старых данных
	// читаем программу из ячеек таблиц, проверяем и записываем в массивы
	SProgName=leSProgName->Text;
	STyrePressure=StrToFlt(leSTyrePressure->Text);
	leSTyrePressure->Text=FloatToStrF(STyrePressure,ffFixed,6,1);
	total_step_S=0; total_S=0;
	// ввод из первой таблицы нагрузок, скоростей и путей
	for (int i = 0; i < MAXNUMOFSTEPS; i++)
	{
		double 	Load=StrToFlt(sgSProgram->Cells[1][i+1]),
				Speed=StrToFlt(sgSProgram->Cells[2][i+1]),
				Distance=StrToFlt(sgSProgram->Cells[3][i+1]);
		if (!CheckLoad(Load)||!CheckSpeed(Speed)||(!CheckDistance(Distance)&&Distance))
		{
			ClearSProg();//чистка данных
			AnsiString msg="Введено не корректное значение в строке "+AnsiString(i+1);
			MessageBox(Handle,msg.c_str(),_T("Ошибка"),MB_ICONERROR|MB_OK);
			return;
		}
		Ssettings[0][i]=Load;//нагрузки
		if(Ssettings[0][i]==0)
		{  // если нагрузка в этой строчке равна 0
			if(i>0)total_step_S=i;  // строка не первая - запомнить количество шагов программы по пути
			else {sbRB->Panels->Items[2]->Text="Не задано ни одного значения нагрузки!";}
			break;                  // и прекратить ввод из таблицы
		}
		sgSProgram->Cells[1][i+1]=FloatToStrF(Ssettings[0][i],ffFixed,6,2);

		Ssettings[1][i]=Speed; //скорости
		if(Ssettings[1][i]==0)
		{ // если скорость равна 0
			if(i>0)
			{              // если строка не первая - взять из предыдущей строки
				Ssettings[1][i]=Ssettings[1][i-1];
			}
			else
			{                 // иначе ни одной скорости не задано - прекратить ввод из таблицы
				MessageBox(Handle,_T("Не задано ни одного значения скорости!"),_T("Ошибка"),MB_ICONERROR|MB_OK);
				sbRB->Panels->Items[2]->Text="Не задано ни одного значения скорости!";
				total_step_S=0;
				ClearSProg();//чистка данных
				break;
			}
		}

		sgSProgram->Cells[2][i+1]=FloatToStrF(Ssettings[1][i],ffFixed,6,2);
		prog_step_S[i]=Distance;
		if (prog_step_S[i]==0)
		{ // если длина пути шага равна 0
			if(i>0)
			{               // если строка не первая - взять из предыдущей строки
				prog_step_S[i]=prog_step_S[i-1];
			}
			else
			{                 // иначе не задано длины пути шага - прекратить ввод из таблицы
				MessageBox(Handle,_T("Не задано ни одного значения пути шага!"),_T("Ошибка"),MB_ICONERROR|MB_OK);
				sbRB->Panels->Items[2]->Text="Не задано ни одного значения пути шага!";
				total_step_S=0;
				ClearSProg();//чистка данных
				break;
			}
		}
		sgSProgram->Cells[3][i+1]=FloatToStrF(prog_step_S[i],ffFixed,6,2);
		total_S+=prog_step_S[i];
	} // конец обработки таблицы нагрузок, скоростей и путей
	leSTotalStepsQty->Text=String(total_step_S);
	if(total_step_S==0)
	{
		leTotalTestTime->Text="";
		return;
	}
	leTotalTestS->Text=FloatToStrF(total_S,ffFixed,6,2);
	num_S_poll=0; float total_poll_S=0;
	// ввод из второй таблицы опросов по пути
	for (int i = 0; i < MAXNUMOFPOLLS; i++)
	{
		double Distance=StrToFlt(sgSPolling->Cells[1][i+1]);
		if (!CheckDistance(Distance)&&Distance)
		{
			ClearSProg();//чистка данных
			AnsiString msg="Введено не корректное значение опроса в строке "+AnsiString(i+1);
			MessageBox(Handle,msg.c_str(),_T("Ошибка"),MB_ICONERROR|MB_OK);
			ClearSProg();//чистка данных
			return;
		}
		poll_step_S[i]=Distance;
		if(poll_step_S[i]==0)
		{
			if(i==0)
			{
				MessageBox(Handle,_T("Не задано ни одного пути для опроса!"),_T("Ошибка"),MB_ICONERROR|MB_OK);
				sbRB->Panels->Items[2]->Text="Не задано ни одного пути для опроса!";
				ClearSProg();//чистка данных
				break;
			}
			else
			{
				poll_step_S[i]=poll_step_S[i-1];
			}
		}
		sgSPolling->Cells[1][i+1]=FloatToStrF(poll_step_S[i],ffFixed,6,2);
		total_poll_S+=poll_step_S[i];
		num_S_poll++;
		if (total_poll_S>=total_S)
			break;
	}
	if(num_S_poll==0)
	{
		leSPollingTotalQty->Text="";
		return;
	}
	leSPollingTotalQty->Text=String(num_S_poll);
	sbRB->Panels->Items[2]->Text="Программа проверена!";
	btnCheckSProg->Enabled=false;
	btnSaveSProgToFile->Enabled=true;
	btnLoadSProgToPosA->Enabled=true;
	btnLoadSProgToPosB->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnNewSProg(TObject *Sender)
{
  leSProgName->Text="";             SProgName="";
  leSTyrePressure->Text="";         STyrePressure=0.0;
  leSTotalStepsQty->Text="";        total_step_S=0;
  leTotalTestS->Text="0";           total_S=0;
  leSPollingTotalQty->Text="";      num_S_poll=0;
  for (int i = 0; i < MAXNUMOFSTEPS; i++) {
    sgSProgram->Cells[1][i+1]="";
    sgSProgram->Cells[2][i+1]="";
    sgSProgram->Cells[3][i+1]="";
  }
  for (int i = 0; i < MAXNUMOFPOLLS; i++) {
	sgSPolling->Cells[1][i+1]="";
  }
  ClearSProg();//чистка старых данных
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::ShowProtAData(void)     // отобразить шапку протокола в панели поз. А
{
  pCurrentProtATtl->Caption="ПРОТОКОЛ ИСПЫТАНИЙ"//№ "+String(TyreA->ProtNo)+
                            " НА СТЕНДЕ "+TyreA->StandName+" (ПОЗ. А)";
  leTyreSyzeA->Text        =TyreA->Size;
  leTyreModelA->Text       =TyreA->Model;
  leManDateA->Text         =TyreA->CustomDate();//DateToStr(TyreA->ManufactDate);
  leSerialNoA->Text        =String(TyreA->SerialNo);
  leManufacturerA->Text    =TyreA->Manufacturer;
  leTestCustomerA->Text    =TyreA->TestCustomer;
  leFormNoA->Text          =String(TyreA->FormNo);
  lePerfSpecNoA->Text      =String(TyreA->PerfSpecNo);
  leTestProcA->Text        =TyreA->TestProcedure;
  leDrumD_A->Text          =FloatToStrF(TyreA->DrumDiameter,ffFixed,7,2);
  leOrderNoA->Text         =String(TyreA->OrderNo);
  if(TyreA->Type==0)
	pTyreParamATtl->Caption="ХАРАКТЕРИСТИКИ ИСПЫТЫВАЕМОЙ"/* РАДИАЛЬНОЙ */"ШИНЫ";
  else
	pTyreParamATtl->Caption="ХАРАКТЕРИСТИКИ ИСПЫТЫВАЕМОЙ"/* ДИАГОНАЛЬНОЙ */"ШИНЫ";
  leLoadIndA->Text         =TyreA->LoadIndex;
  leMaxLoadA->Text         =FloatToStrF(TyreA->MaxLoad,ffFixed,6,2);
  leSpeedIndA->Text        =TyreA->SpeedInd;
  leMaxSpeedA->Text        =FloatToStrF(TyreA->MaxSpeed,ffFixed,6,2);
  leTyreWideA->Text        =FloatToStrF(TyreA->ProfileWide,ffFixed,6,2);
  LogPrint("Profile Wide A="+FloatToStrF(TyreA->ProfileWide,ffFixed,6,1),clAqua);
  leStaticR_A->Text        =FloatToStrF(TyreA->StaticR,ffFixed,6,1);
  leOuterD_A->Text         =FloatToStrF(TyreA->OuterD,ffFixed,6,2);
  leRimA->Text             =TyreA->WheelRim;
  leQMaxPressureA->Text    =FloatToStrF(TyreA->MaxLoadPress,ffFixed,6,2);
  pTestResTtlA->Caption    ="РЕЗУЛЬТАТЫ ИСПЫТАНИЙ";
  leTyrePressureA->Text    =FloatToStrF(TyreA->InitPressure,ffFixed,6,2);
  if(TyreA->TestMode){
    leTestModeA->Text     ="по пути";
    leTestDurationA->EditLabel->Caption="путь обкатки, км";
    leTestDurationA->Text =FloatToStrF(TyreA->TotalS,ffFixed,7,2);
  }
  else               {
    leTestModeA->Text     ="по времени";
    leTestDurationA->EditLabel->Caption="время обкатки";
    leTestDurationA->Text =mSecToHMSStr(TyreA->TotalTime);
  }
  leStepQtyA->Text        =String(TyreA->StepsNo);
  lePollsQtyA->Text       =String(TyreA->PollsNo);
}
//---- End of ShowProtAData -------------------------------------------------

void __fastcall TmfRB::ShowProtBData(void)     // отобразить шапку протокола в панели поз. Б
{
  pCurrentProtBTtl->Caption="ПРОТОКОЛ ИСПЫТАНИЙ"// № "+String(TyreB->ProtNo)+
                            " НА СТЕНДЕ "+TyreB->StandName+" (ПОЗ. Б)";
  leTyreSyzeB->Text        =TyreB->Size;
  leTyreModelB->Text       =TyreB->Model;
  leManDateB->Text         =TyreB->CustomDate();//DateToStr(TyreB->ManufactDate);
  leSerialNoB->Text        =String(TyreB->SerialNo);
  leManufacturerB->Text    =TyreB->Manufacturer;
  leTestCustomerB->Text    =TyreB->TestCustomer;
  leFormNoB->Text          =String(TyreB->FormNo);
  lePerfSpecNoB->Text      =String(TyreB->PerfSpecNo);
  leTestProcB->Text        =TyreB->TestProcedure;
  leDrumD_B->Text          =FloatToStrF(TyreB->DrumDiameter,ffFixed,7,2);
  leOrderNoB->Text         =String(TyreB->OrderNo);
  if(TyreB->Type==0)
	pTyreParamBTtl->Caption="ХАРАКТЕРИСТИКИ ИСПЫТЫВАЕМОЙ"/* РАДИАЛЬНОЙ */"ШИНЫ";
  else
    pTyreParamBTtl->Caption="ХАРАКТЕРИСТИКИ ИСПЫТЫВАЕМОЙ"/* ДИАГОНАЛЬНОЙ */"ШИНЫ";
  leLoadIndB->Text         =TyreB->LoadIndex;
  leMaxLoadB->Text         =FloatToStrF(TyreB->MaxLoad,ffFixed,6,2);
  leSpeedIndB->Text        =TyreB->SpeedInd;
  leMaxSpeedB->Text        =FloatToStrF(TyreB->MaxSpeed,ffFixed,6,2);
  leTyreWideB->Text        =FloatToStrF(TyreB->ProfileWide,ffFixed,6,2);
  leStaticR_B->Text        =FloatToStrF(TyreB->StaticR,ffFixed,6,1);
  leOuterD_B->Text         =FloatToStrF(TyreB->OuterD,ffFixed,6,2);
  leRimB->Text             =TyreB->WheelRim;
  leQMaxPressureB->Text    =FloatToStrF(TyreB->MaxLoadPress,ffFixed,6,2);
  pTestResTtlB->Caption    ="РЕЗУЛЬТАТЫ ИСПЫТАНИЙ";
  leTyrePressureB->Text    =FloatToStrF(TyreB->InitPressure,ffFixed,6,2);
  if(TyreB->TestMode){
    leTestModeB->Text     ="по пути";
    leTestDurationB->EditLabel->Caption="путь обкатки, км";
    leTestDurationB->Text =FloatToStrF(TyreB->TotalS,ffFixed,7,2);
  }
  else               {
    leTestModeB->Text     ="по времени";
    leTestDurationB->EditLabel->Caption="время обкатки";
    leTestDurationB->Text =mSecToHMSStr(TyreB->TotalTime);
  }
  leStepQtyB->Text        =String(TyreB->StepsNo);
  lePollsQtyB->Text       =String(TyreB->PollsNo);
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::ReadProtDataFmScrn(void)// прочитать данные протокола из экрана в InpTyre
{
  InpTyre->ProtNo       =StrToI(leProtocolNo->Text);
  InpTyre->Size         =leTyreSize->Text;
  InpTyre->Model        =leTyreType->Text;
  InpTyre->TestProcedure=leTestProc->Text;
  InpTyre->StandName    =leStandNo->Text;
  InpTyre->Manufacturer =leManufacturer->Text;
  InpTyre->DrumDiameter =StrToFloat(leDrumD->Text);
  InpTyre->TestCustomer =leCustomer->Text;
  //InpTyre->ManufactDate =StrToDate(meManDate->EditText);
  InpTyre->CustomDate(meManDate->EditText);
  InpTyre->SerialNo     =StrToI(leSeralNo->Text);
  InpTyre->PerfSpecNo   =StrToI(lePerfSpecNo->Text);
  InpTyre->OrderNo      =StrToI(leOrderNo->Text);
  InpTyre->FormNo       =StrToI(leFormNo->Text);
  InpTyre->LoadIndex    =leLoadIndex->Text;
  InpTyre->MaxLoad      =StrToFlt(leMaxLoad->Text);
  InpTyre->SpeedInd     =leSpeedIndex->Text;
  InpTyre->MaxSpeed     =StrToFlt(leMaxSpeed->Text);
  InpTyre->StaticR      =StrToFlt(leStaticR->Text);
  InpTyre->OuterD       =StrToFlt(leOuterD->Text);
  InpTyre->WheelRim     =leRim->Text;
  InpTyre->MaxLoadPress =StrToFlt(leQMaxPressure->Text);
  InpTyre->ProfileWide  =StrToI(leTyreWide->Text);
  InpTyre->Type         =rgTyreType->ItemIndex;
//  InpTyre->CurrentLoad  =StrToFlt(leTestLoad->Text);
//  InpTyre->InitPressure =StrToFlt(leInitPressure->Text);
//  InpTyre->CurrentSpeed =StrToFlt(leTestSpeed->Text);
  InpTyre->TestMode     =cmbTestMode->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::DesignNewProtPanel(void)// расположение компонент на панели нового протокола
{ int LblShift11=leProtocolNo->EditLabel->Width, LblShift12=leDrumD->EditLabel->Width,
      LblShift13=lblManDate->Width, LblShift14=leFormNo->EditLabel->Width;
  int LblShift21=leMaxLoad->EditLabel->Width, LblShift22=leQMaxPressure->EditLabel->Width,
      LblShift23=leTyreWide->EditLabel->Width;
  int LineH0=26, Left0=3, Left1=Left0+LblShift11, PnlWidth=tsNewProtWidth-Left0*2, Top1=1, LineSpace1=5,
      LineH =25, Top2=Top1+LineH0+LineSpace1, LineSpase2=LineH+LineSpace1, LblWidth1=tsNewProtWidth/10;
  if(LblWidth1<80)LblWidth1=80;
  int Left2=Left1+LblWidth1+LblShift12+Left0+10, Left3=Left2+LblWidth1+LblShift13+Left0, LblWidth2=Left3+LblWidth1-Left2,
      LblWidth3=tsNewProtWidth/20; if(LblWidth3<40)LblWidth3=40;
  int Left4=Left3+LblWidth1+LblShift14+Left0; if((Left4+LblWidth3)<PnlWidth+Left0)Left4=PnlWidth+Left0-LblWidth3;
  pCommonProtData->Left =Left0;                  pCommonProtData->Top     =Top1;
  pCommonProtData->Width=PnlWidth;               pCommonProtData->Height  =LineH0;
  leProtocolNo->Left    =Left1;                  leProtocolNo->Top        =Top2;
  leProtocolNo->Width   =LblWidth1;              leProtocolNo->Height     =LineH;
  leTyreSize->Left      =Left1;                  leTyreSize->Top          =Top2+LineSpase2;
  leTyreSize->Width     =LblWidth1;              leTyreSize->Height       =LineH;
  leTyreType->Left      =Left1;                  leTyreType->Top          =Top2+LineSpase2*2;
  leTyreType->Width     =LblWidth1;              leTyreType->Height       =LineH;
  leTestProc->Left      =Left1;                  leTestProc->Top          =Top2+LineSpase2*3;
  leTestProc->Width     =LblWidth1;              leTestProc->Height       =LineH;
  leCustomer->Left      =Left2;                  leCustomer->Top          =Top2;
  leCustomer->Width     =LblWidth2;              leCustomer->Height       =LineH;
  leStandNo->Left       =Left2;                  leStandNo->Top           =Top2+LineSpase2;
  leStandNo->Width      =LblWidth1;              leStandNo->Height        =LineH;
  leManufacturer->Left  =Left2;                  leManufacturer->Top      =Top2+LineSpase2*2;
  leManufacturer->Width =LblWidth1;              leManufacturer->Height   =LineH;
  leDrumD->Left         =Left2;                  leDrumD->Top             =Top2+LineSpase2*3;
  leDrumD->Width        =LblWidth1;              leDrumD->Height          =LineH;
  lblManDate->Left      =Left2+LblWidth1+Left0;  lblManDate->Top          =Top2+LineSpase2;
  meManDate->Left       =Left3;                  meManDate->Top           =Top2+LineSpase2;
  meManDate->Width      =LblWidth1;              meManDate->Height        =LineH;
  leSeralNo->Left       =Left3;                  leSeralNo->Top           =Top2+LineSpase2*2;
  leSeralNo->Width      =LblWidth1;              leSeralNo->Height        =LineH;
  lePerfSpecNo->Left    =Left3;                  lePerfSpecNo->Top        =Top2+LineSpase2*3;
  lePerfSpecNo->Width   =LblWidth1;              lePerfSpecNo->Height     =LineH;
  leOrderNo->Left       =Left4;                  leOrderNo->Top           =Top2+LineSpase2;
  leOrderNo->Width      =LblWidth3;              leOrderNo->Height        =LineH;
  leFormNo->Left        =Left4;                  leFormNo->Top            =Top2+LineSpase2*2;
  leFormNo->Width       =LblWidth3;              leFormNo->Height         =LineH;
  pTyreParam->Left      =Left0;                  pTyreParam->Top          =Top2+LineSpase2*3+LineSpace1+LineH;
  pTyreParam->Width     =PnlWidth;               pTyreParam->Height       =LineH0;
  int Top3=pTyreParam->Top+LineH0+LineSpace1;
  int MaxLblShift2=LblShift21>LblShift22?LblShift21:LblShift22;
  MaxLblShift2=MaxLblShift2>LblShift23?MaxLblShift2:LblShift23;
  int LblSt=(PnlWidth-(MaxLblShift2*3+LblWidth1*3))/2;
  Left1=Left0+MaxLblShift2+10; Left2=Left1+LblWidth1+MaxLblShift2+LblSt;
  Left3=Left2+LblWidth1+MaxLblShift2+LblSt; if((Left3+LblWidth1)<PnlWidth+Left0)Left3=PnlWidth+Left0-LblWidth1;
  Left4=PnlWidth+Left0-rgTyreType->Width;   LblWidth2=LblWidth1*3/2; if(LblWidth2<140)LblWidth2=140;
  leLoadIndex->Left     =Left1;                  leLoadIndex->Top         =Top3;
  leLoadIndex->Width    =LblWidth1;              leLoadIndex->Height      =LineH;
  leMaxLoad->Left       =Left1;                  leMaxLoad->Top           =Top3+LineSpase2;
  leMaxLoad->Width      =LblWidth1;              leMaxLoad->Height        =LineH;
  leSpeedIndex->Left    =Left1;                  leSpeedIndex->Top        =Top3+LineSpase2*2;
  leSpeedIndex->Width   =LblWidth1;              leSpeedIndex->Height     =LineH;
  leMaxSpeed->Left      =Left1;                  leMaxSpeed->Top          =Top3+LineSpase2*3;
  leMaxSpeed->Width     =LblWidth1;              leMaxSpeed->Height       =LineH;
  leStaticR->Left       =Left2;                  leStaticR->Top           =Top3;
  leStaticR->Width      =LblWidth1;              leStaticR->Height        =LineH;
  leOuterD->Left        =Left2;                  leOuterD->Top            =Top3+LineSpase2;
  leOuterD->Width       =LblWidth1;              leOuterD->Height         =LineH;
  leRim->Left           =Left2;                  leRim->Top               =Top3+LineSpase2*2;
  leRim->Width          =LblWidth1;              leRim->Height            =LineH;
  leQMaxPressure->Left  =Left2;                  leQMaxPressure->Top      =Top3+LineSpase2*3;
  leQMaxPressure->Width =LblWidth1;              leQMaxPressure->Height   =LineH;
  leTyreWide->Left      =Left3;                  leTyreWide->Top          =Top3;
  leTyreWide->Width     =LblWidth1;              leTyreWide->Height       =LineH;
  rgTyreType->Left      =Left4-20;               rgTyreType->Top          =Top3+LineSpase2;
  /*rgTyreType->Width     =LblWidth2;*/              rgTyreType->Height       =LineSpase2*2;
//  pTestMode->Left       =Left0;                  pTestMode->Top           =Top3+LineSpase2*3+LineH+LineSpace1;
//  pTestMode->Width      =PnlWidth;               pTestMode->Height        =LineH0;
//  int Top4=pTestMode->Top+LineH0+LineSpace1;
//  leTestLoad->Left      =Left1;                  leTestLoad->Top          =Top4;
//  leTestLoad->Width     =LblWidth1;              leTestLoad->Height       =LineH;
//  leInitPressure-;
//  leTestSpeed->Text);
//  lblTestMode->Left     =Left2-lblTestMode->Width; lblTestMode->Top       =Top4;
//  cmbTestMode->Left     =Left2;                    cmbTestMode->Top       =Top4;
  int Top5=Top3+LineSpase2*3+LineH0+LineH+LineSpace1*2,//Top4+cmbTestMode->Height+LineSpase2,
      btnWidth=(PnlWidth-60)/5;
  btnClearProt->Left         =Left0;               btnClearProt->Top           =Top5;
  btnClearProt->Width        =btnWidth;            btnClearProt->Height        =LineH*2;
  btnSaveProtTtlToFile->Left =Left0+btnWidth+15;   btnSaveProtTtlToFile->Top   =Top5;
  btnSaveProtTtlToFile->Width=btnWidth;            btnSaveProtTtlToFile->Height=LineH*2;
  btnLoadProtTtlFmFile->Left =Left0+btnWidth*2+30; btnLoadProtTtlFmFile->Top   =Top5;
  btnLoadProtTtlFmFile->Width=btnWidth;            btnLoadProtTtlFmFile->Height=LineH*2;
  btnLoadProtToPosA->Left    =Left0+btnWidth*3+45; btnLoadProtToPosA->Top      =Top5;
  btnLoadProtToPosA->Width   =btnWidth;            btnLoadProtToPosA->Height   =LineH*2;
  btnLoadProtToPosB->Left    =Left0+btnWidth*4+60; btnLoadProtToPosB->Top      =Top5;
  btnLoadProtToPosB->Width   =btnWidth;            btnLoadProtToPosB->Height   =LineH*2;
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::DesignProtAPanel(void)  // расположение компонент на панели протокола поз. А
{
  int LblShift11=lePerfSpecNoA->EditLabel->Width, LblShift12=leTestProcA->EditLabel->Width,
      LblShift13=leManDateA->EditLabel->Width, LblShift14=leSerialNoA->EditLabel->Width;
  int LblShift21=leTyrePressureA->EditLabel->Width, LblShift22=leMaxLoadA->EditLabel->Width,
      LblShift23=leStaticR_A->EditLabel->Width;
  int LblShift31=leStepQtyA->EditLabel->Width, LblShift32=lePollsQtyA->EditLabel->Width;
  int LineH0=26, Left0=3, Left1=Left0+LblShift11, PnlWidth=tsNewProtWidth-Left0*2, Top1=1, LineSpace1=5,
      LineH =25, Top2=Top1+LineH0+LineSpace1, LblWidth1=tsNewProtWidth/10;
  if(LblWidth1<80)LblWidth1=80;
  int Left2=Left1+LblWidth1+LblShift12+Left0*3, Left3=Left2+LblWidth1+LblShift13+Left0*3+20,
      LblWidth2=Left3+LblWidth1-Left2, LblWidth3=tsNewProtWidth/20;
  if(LblWidth3<40)LblWidth3=40;
  int Left4=Left3+LblWidth1+LblShift14+Left0*3; if((Left4+LblWidth3)<PnlWidth+Left0)Left4=PnlWidth+Left0-LblWidth3;
//  LogPrint("LS11="+  String(LblShift11)+", LS12="+String(LblShift12)+
//           ", LS13="+String(LblShift13)+", LS14="+String(LblShift11));
//  LogPrint("LblW1="+String(LblWidth1)+", Lft1="+String(Left1)+", Lft2="+String(Left2)+
//           ", Lft3="+String(Left3)+", Lft4="+String(Left4));

  pCurrentProtATtl->Left=Left0;               pCurrentProtATtl->Top=Top1;
  pCurrentProtATtl->Width=PnlWidth;           pCurrentProtATtl->Height=LineH0;
  leManufacturerA->Left  =Left1;              leManufacturerA->Top    =Top2;
  leManufacturerA->Width =LblWidth1;          leManufacturerA->Height =LineH;
  leTyreModelA->Left     =Left1;              leTyreModelA->Top       =Top2+LineH;
  leTyreModelA->Width    =LblWidth1;          leTyreModelA->Height    =LineH;
  lePerfSpecNoA->Left    =Left1;              lePerfSpecNoA->Top      =Top2+LineH*2;
  lePerfSpecNoA->Width   =LblWidth1;          lePerfSpecNoA->Height   =LineH;
  leTestCustomerA->Left  =Left2;              leTestCustomerA->Top    =Top2;
  leTestCustomerA->Width =LblWidth2;          leTestCustomerA->Height =LineH;
  leTyreSyzeA->Left      =Left2;              leTyreSyzeA->Top        =Top2+LineH;
  leTyreSyzeA->Width     =LblWidth1;          leTyreSyzeA->Height     =LineH;
  leTestProcA->Left      =Left2;              leTestProcA->Top        =Top2+LineH*2;
  leTestProcA->Width     =LblWidth1;          leTestProcA->Height     =LineH;
  leManDateA->Left       =Left3;              leManDateA->Top         =Top2+LineH;
  leManDateA->Width      =LblWidth1;          leManDateA->Height      =LineH;
  leDrumD_A->Left        =Left3;              leDrumD_A->Top          =Top2+LineH*2;
  leDrumD_A->Width       =LblWidth1;          leDrumD_A->Height       =LineH;
  leOrderNoA->Left       =Left4;              leOrderNoA->Top         =Top2;
  leOrderNoA->Width      =LblWidth3;          leOrderNoA->Height      =LineH;
  leSerialNoA->Left      =Left4;              leSerialNoA->Top        =Top2+LineH;
  leSerialNoA->Width     =LblWidth3;          leSerialNoA->Height     =LineH;
  leFormNoA->Left        =Left4;              leFormNoA->Top          =Top2+LineH*2;
  leFormNoA->Width       =LblWidth3;          leFormNoA->Height       =LineH;
  pTyreParamATtl->Left   =Left0;              pTyreParamATtl->Top     =Top2+LineH*3+LineSpace1;
  pTyreParamATtl->Width  =PnlWidth;           pTyreParamATtl->Height  =LineH0;
  int Top3=Top2+LineH*3+LineSpace1*2+LineH0;  //LblWidth1=tsNewProtWidth/10;
  Left1=Left0+LblShift21; Left2=Left1+LblWidth1+LblShift22+Left0*3+10;
  Left3=Left2+LblWidth1+LblShift23+Left0*3; if((Left3+LblWidth1)<PnlWidth+Left0)Left3=PnlWidth+Left0-LblWidth1;
  leLoadIndA->Left       =Left1;              leLoadIndA->Top         =Top3;
  leLoadIndA->Width      =LblWidth1;          leLoadIndA->Height      =LineH;
  leSpeedIndA->Left      =Left1;              leSpeedIndA->Top        =Top3+LineH;
  leSpeedIndA->Width     =LblWidth1;          leSpeedIndA->Height     =LineH;
  leOuterD_A->Left       =Left1;              leOuterD_A->Top         =Top3+LineH*2;
  leOuterD_A->Width      =LblWidth1;          leOuterD_A->Height      =LineH;
  leMaxLoadA->Left       =Left2;              leMaxLoadA->Top         =Top3;
  leMaxLoadA->Width      =LblWidth1;          leMaxLoadA->Height      =LineH;
  leMaxSpeedA->Left      =Left2;              leMaxSpeedA->Top        =Top3+LineH;
  leMaxSpeedA->Width     =LblWidth1;          leMaxSpeedA->Height     =LineH;
  leQMaxPressureA->Left  =Left2;              leQMaxPressureA->Top    =Top3+LineH*2;
  leQMaxPressureA->Width =LblWidth1;          leQMaxPressureA->Height =LineH;
  leStaticR_A->Left      =Left3;              leStaticR_A->Top        =Top3;
  leStaticR_A->Width     =LblWidth1;          leStaticR_A->Height     =LineH;
  leTyreWideA->Left      =Left3;              leTyreWideA->Top        =Top3+LineH;
  leTyreWideA->Width     =LblWidth1;          leTyreWideA->Height     =LineH;
  leRimA->Left           =Left3;              leRimA->Top             =Top3+LineH*2;
  leRimA->Width          =LblWidth1;          leRimA->Height          =LineH;
  pTestResTtlA->Left     =Left0;              pTestResTtlA->Top       =Top3+LineH*3+LineSpace1;
  pTestResTtlA->Width    =PnlWidth;           pTestResTtlA->Height    =LineH0;
  Left2=Left1+LblWidth1+LblShift31+Left0*3;
  Left3=Left2+LblWidth1+LblShift32+Left0*3; if((Left3+LblWidth1)<PnlWidth+Left0)Left3=PnlWidth+Left0-LblWidth1;
  int Top4=Top3+LineH*3+LineSpace1*2+LineH0;
  leTyrePressureA->Left  =Left1;              leTyrePressureA->Top    =Top4;
  leTyrePressureA->Width =LblWidth1;          leTyrePressureA->Height =LineH;
  leTestModeA->Left      =Left2;              leTestModeA->Top        =Top4;
  leTestModeA->Width     =LblWidth1*2;        leTestModeA->Height     =LineH;
  leStepQtyA->Left       =Left2;              leStepQtyA->Top         =Top4+LineH;
  leStepQtyA->Width      =LblWidth1;          leStepQtyA->Height      =LineH;
  leTestDurationA->Left  =Left3;              leTestDurationA->Top    =Top4;
  leTestDurationA->Width =LblWidth1;          leTestDurationA->Height =LineH;
  lePollsQtyA->Left      =Left3;              lePollsQtyA->Top        =Top4+LineH;
  lePollsQtyA->Width     =LblWidth1;          lePollsQtyA->Height     =LineH;
  int Top5=Top4+LineH*2+LineSpace1;
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=-1;
  sgTestResultA->Selection=myRect;*/
  int Col0W=30, Col1W=60, Col2W=105, Col3W=75, Col4W=80, Col5W=73, Col6W=100;
  int TTableWidth=Col0W+Col1W+Col2W+Col3W+Col4W+Col5W+Col6W+30;
  sgTestResultA->Left     =Left0;             sgTestResultA->Top      =Top5;
  int TTableHeight=tsProtocolAHeight-Top5-5;
  int RowNo=TTableHeight/(sgTestResultA->RowHeights[0]+1);
  TTableHeight=RowNo*sgTestResultA->RowHeights[0]+RowNo;
  sgTestResultA->Width    =TTableWidth;       sgTestResultA->Height   =TTableHeight;
  sgTestResultA->ColWidths[0]=Col0W;          sgTestResultA->ColWidths[1]=Col1W;
  sgTestResultA->ColWidths[2]=Col2W;          sgTestResultA->ColWidths[3]=Col3W;
  sgTestResultA->ColWidths[4]=Col4W;          sgTestResultA->ColWidths[5]=Col5W;
  sgTestResultA->ColWidths[6]=Col6W;
  sgTestResultA->Cells[0][0]="№";                sgTestResultA->Cells[1][0]="Время";
  sgTestResultA->Cells[2][0]="Скорость, км/час"; sgTestResultA->Cells[3][0]="Пробег, км";
  sgTestResultA->Cells[4][0]="Нагрузка, кН";     sgTestResultA->Cells[5][0]="Радиус, мм";
  sgTestResultA->Cells[6][0]="Температура, С";
  for (int i = 0; i < MAXNUMOFPOLLS; i++) {
    if(i<9)sgTestResultA->Cells[0][i+1]="  "+String(i+1)+":";
    else if(i<99)sgTestResultA->Cells[0][i+1]=" "+String(i+1)+":";
    else sgTestResultA->Cells[0][i+1]=String(i+1)+":";
  }
  Left1=Left0+TTableWidth+10;
  int BtnWidth=tsNewProtWidth-Left1-10, BtnHeight=(tsNewProtHeight-Top5-20)/3;
  if(BtnHeight>45)BtnHeight=45;
  btnLoadTestResPosA->Left       =Left1;      btnLoadTestResPosA->Top         =Top5;
  btnLoadTestResPosA->Width      =BtnWidth;   btnLoadTestResPosA->Height      =BtnHeight;

  btnSaveTestResPosAToFile->Left =Left1;      btnSaveTestResPosAToFile->Top   =Top5+BtnHeight+10;
  btnSaveTestResPosAToFile->Width=BtnWidth;   btnSaveTestResPosAToFile->Height=BtnHeight;

  btnPrintTestResPosA->Left      =Left1;      btnPrintTestResPosA->Top        =Top5+BtnHeight*2+20;
  btnPrintTestResPosA->Width     =BtnWidth;   btnPrintTestResPosA->Height     =BtnHeight;

  btnResetResPosA->Left			 =Left1;      btnResetResPosA->Top		  =Top5+BtnHeight*3+30;
  btnResetResPosA->Width		 =BtnWidth;   btnResetResPosA->Height     =BtnHeight;
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::DesignProtBPanel(void)  // расположение компонент на панели протокола поз. Б
{
  int LblShift11=lePerfSpecNoB->EditLabel->Width, LblShift12=leTestProcB->EditLabel->Width,
      LblShift13=leManDateB->EditLabel->Width, LblShift14=leSerialNoB->EditLabel->Width;
  int LblShift21=leTyrePressureB->EditLabel->Width, LblShift22=leMaxLoadB->EditLabel->Width,
      LblShift23=leStaticR_B->EditLabel->Width;
  int LblShift31=leStepQtyB->EditLabel->Width, LblShift32=lePollsQtyB->EditLabel->Width;
  int LineH0=26, Left0=3, Left1=Left0+LblShift11, PnlWidth=tsNewProtWidth-Left0*2, Top1=1, LineSpace1=5,
      LineH =25, Top2=Top1+LineH0+LineSpace1, LblWidth1=tsNewProtWidth/10;
  if(LblWidth1<80)LblWidth1=80;
  int Left2=Left1+LblWidth1+LblShift12+Left0*3, Left3=Left2+LblWidth1+LblShift13+Left0*3+20,
      LblWidth2=Left3+LblWidth1-Left2, LblWidth3=tsNewProtWidth/20;
  if(LblWidth3<40)LblWidth3=40;
  int Left4=Left3+LblWidth1+LblShift14+Left0*3; if((Left4+LblWidth3)<PnlWidth+Left0)Left4=PnlWidth+Left0-LblWidth3;

  pCurrentProtBTtl->Left=Left0;               pCurrentProtBTtl->Top=Top1;
  pCurrentProtBTtl->Width=PnlWidth;           pCurrentProtBTtl->Height=LineH0;
  leManufacturerB->Left  =Left1;              leManufacturerB->Top    =Top2;
  leManufacturerB->Width =LblWidth1;          leManufacturerB->Height =LineH;
  leTyreModelB->Left     =Left1;              leTyreModelB->Top       =Top2+LineH;
  leTyreModelB->Width    =LblWidth1;          leTyreModelB->Height    =LineH;
  lePerfSpecNoB->Left    =Left1;              lePerfSpecNoB->Top      =Top2+LineH*2;
  lePerfSpecNoB->Width   =LblWidth1;          lePerfSpecNoB->Height   =LineH;
  leTestCustomerB->Left  =Left2;              leTestCustomerB->Top    =Top2;
  leTestCustomerB->Width =LblWidth2;          leTestCustomerB->Height =LineH;
  leTyreSyzeB->Left      =Left2;              leTyreSyzeB->Top        =Top2+LineH;
  leTyreSyzeB->Width     =LblWidth1;          leTyreSyzeB->Height     =LineH;
  leTestProcB->Left      =Left2;              leTestProcB->Top        =Top2+LineH*2;
  leTestProcB->Width     =LblWidth1;          leTestProcB->Height     =LineH;
  leManDateB->Left       =Left3;              leManDateB->Top         =Top2+LineH;
  leManDateB->Width      =LblWidth1;          leManDateB->Height      =LineH;
  leDrumD_B->Left        =Left3;              leDrumD_B->Top          =Top2+LineH*2;
  leDrumD_B->Width       =LblWidth1;          leDrumD_B->Height       =LineH;
  leOrderNoB->Left       =Left4;              leOrderNoB->Top         =Top2;
  leOrderNoB->Width      =LblWidth3;          leOrderNoB->Height      =LineH;
  leSerialNoB->Left      =Left4;              leSerialNoB->Top        =Top2+LineH;
  leSerialNoB->Width     =LblWidth3;          leSerialNoB->Height     =LineH;
  leFormNoB->Left        =Left4;              leFormNoB->Top          =Top2+LineH*2;
  leFormNoB->Width       =LblWidth3;          leFormNoB->Height       =LineH;
  pTyreParamBTtl->Left   =Left0;              pTyreParamBTtl->Top     =Top2+LineH*3+LineSpace1;
  pTyreParamBTtl->Width  =PnlWidth;           pTyreParamBTtl->Height  =LineH0;
  int Top3=Top2+LineH*3+LineSpace1*2+LineH0;  //LblWidth1=tsNewProtWidth/16;
  Left1=Left0+LblShift21; Left2=Left1+LblWidth1+LblShift22+Left0*3+10;
  Left3=Left2+LblWidth1+LblShift23+Left0*3; if((Left3+LblWidth1)<PnlWidth+Left0)Left3=PnlWidth+Left0-LblWidth1;
  leLoadIndB->Left       =Left1;              leLoadIndB->Top         =Top3;
  leLoadIndB->Width      =LblWidth1;          leLoadIndB->Height      =LineH;
  leSpeedIndB->Left      =Left1;              leSpeedIndB->Top        =Top3+LineH;
  leSpeedIndB->Width     =LblWidth1;          leSpeedIndB->Height     =LineH;
  leOuterD_B->Left       =Left1;              leOuterD_B->Top         =Top3+LineH*2;
  leOuterD_B->Width      =LblWidth1;          leOuterD_B->Height      =LineH;
  leMaxLoadB->Left       =Left2;              leMaxLoadB->Top         =Top3;
  leMaxLoadB->Width      =LblWidth1;          leMaxLoadB->Height      =LineH;
  leMaxSpeedB->Left      =Left2;              leMaxSpeedB->Top        =Top3+LineH;
  leMaxSpeedB->Width     =LblWidth1;          leMaxSpeedB->Height     =LineH;
  leQMaxPressureB->Left  =Left2;              leQMaxPressureB->Top    =Top3+LineH*2;
  leQMaxPressureB->Width =LblWidth1;          leQMaxPressureB->Height =LineH;
  leStaticR_B->Left      =Left3;              leStaticR_B->Top        =Top3;
  leStaticR_B->Width     =LblWidth1;          leStaticR_B->Height     =LineH;
  leTyreWideB->Left      =Left3;              leTyreWideB->Top        =Top3+LineH;
  leTyreWideB->Width     =LblWidth1;          leTyreWideB->Height     =LineH;
  leRimB->Left           =Left3;              leRimB->Top             =Top3+LineH*2;
  leRimB->Width          =LblWidth1;          leRimB->Height          =LineH;
  pTestResTtlB->Left     =Left0;              pTestResTtlB->Top       =Top3+LineH*3+LineSpace1;
  pTestResTtlB->Width    =PnlWidth;           pTestResTtlB->Height    =LineH0;
  Left2=Left1+LblWidth1+LblShift31+Left0*3;
  Left3=Left2+LblWidth1+LblShift32+Left0*3; if((Left3+LblWidth1)<PnlWidth+Left0)Left3=PnlWidth+Left0-LblWidth1;
  int Top4=Top3+LineH*3+LineSpace1*2+LineH0;
  leTyrePressureB->Left  =Left1;              leTyrePressureB->Top    =Top4;
  leTyrePressureB->Width =LblWidth1;          leTyrePressureB->Height =LineH;
  leTestModeB->Left      =Left2;              leTestModeB->Top        =Top4;
  leTestModeB->Width     =LblWidth1*2;        leTestModeB->Height     =LineH;
  leStepQtyB->Left       =Left2;              leStepQtyB->Top         =Top4+LineH;
  leStepQtyB->Width      =LblWidth1;          leStepQtyB->Height      =LineH;
  leTestDurationB->Left  =Left3;              leTestDurationB->Top    =Top4;
  leTestDurationB->Width =LblWidth1;          leTestDurationB->Height =LineH;
  lePollsQtyB->Left      =Left3;              lePollsQtyB->Top        =Top4+LineH;
  lePollsQtyB->Width     =LblWidth1;          lePollsQtyB->Height     =LineH;
  int Top5=Top4+LineH*2+LineSpace1;
  /*TGridRect myRect;
  myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=-1;
  sgTestResultB->Selection=myRect;*/
  int Col0W=30, Col1W=60, Col2W=105, Col3W=75, Col4W=80, Col5W=73, Col6W=100;
  int TTableWidth=Col0W+Col1W+Col2W+Col3W+Col4W+Col5W+Col6W+30;
  sgTestResultB->Left     =Left0;             sgTestResultB->Top      =Top5;
  int TTableHeight=tsProtocolAHeight-Top5-5;
  int RowNo=TTableHeight/(sgTestResultB->RowHeights[0]+1);
  TTableHeight=RowNo*sgTestResultB->RowHeights[0]+RowNo;
  sgTestResultB->Width    =TTableWidth;       sgTestResultB->Height   =TTableHeight;
  sgTestResultB->ColWidths[0]=Col0W;          sgTestResultB->ColWidths[1]=Col1W;
  sgTestResultB->ColWidths[2]=Col2W;          sgTestResultB->ColWidths[3]=Col3W;
  sgTestResultB->ColWidths[4]=Col4W;          sgTestResultB->ColWidths[5]=Col5W;
  sgTestResultB->ColWidths[6]=Col6W;
  sgTestResultB->Cells[0][0]="№";                sgTestResultB->Cells[1][0]="Время";
  sgTestResultB->Cells[2][0]="Скорость, км/час"; sgTestResultB->Cells[3][0]="Пробег, км";
  sgTestResultB->Cells[4][0]="Нагрузка, кН";     sgTestResultB->Cells[5][0]="Радиус, мм";
  sgTestResultB->Cells[6][0]="Температура, С";
  for (int i = 0; i < MAXNUMOFPOLLS; i++) {
    if(i<9)sgTestResultB->Cells[0][i+1]="  "+String(i+1)+":";
    else if(i<99)sgTestResultB->Cells[0][i+1]=" "+String(i+1)+":";
    else sgTestResultB->Cells[0][i+1]=String(i+1)+":";
  }
  Left1=Left0+TTableWidth+10;
  int BtnWidth=tsNewProtWidth-Left1-10, BtnHeight=(tsNewProtHeight-Top5-20)/3;
  if(BtnHeight>45)BtnHeight=45;

  btnLoadTestResPosB->Left       =Left1;      btnLoadTestResPosB->Top         =Top5;
  btnLoadTestResPosB->Width      =BtnWidth;   btnLoadTestResPosB->Height      =BtnHeight;

  btnSaveTestResPosBToFile->Left =Left1;      btnSaveTestResPosBToFile->Top   =Top5+BtnHeight+10;
  btnSaveTestResPosBToFile->Width=BtnWidth;   btnSaveTestResPosBToFile->Height=BtnHeight;

  btnPrintTestResPosB->Left      =Left1;      btnPrintTestResPosB->Top        =Top5+BtnHeight*2+20;
  btnPrintTestResPosB->Width     =BtnWidth;   btnPrintTestResPosB->Height     =BtnHeight;

  btnResetResPosB->Left			 =Left1;      btnResetResPosB->Top		  =Top5+BtnHeight*3+30;
  btnResetResPosB->Width		 =BtnWidth;   btnResetResPosB->Height     =BtnHeight;
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnClearProt(TObject *Sender)
{
  leProtocolNo->Text    ="";           leTyreSize->Text      ="";
  leTyreType->Text      ="";           leTestProc->Text      ="";
  leStandNo->Text       ="14";         leManufacturer->Text  ="";
  leDrumD->Text         ="1700";       leCustomer->Text      ="";
  meManDate->EditText   ="00.00.2010"; leSeralNo->Text       =0;
  lePerfSpecNo->Text    ="";           leOrderNo->Text       ="";
  leFormNo->Text        ="";           leLoadIndex->Text     ="";
  leMaxLoad->Text       ="";           leSpeedIndex->Text    ="";
  leMaxSpeed->Text      ="";           leStaticR->Text       ="";
  leOuterD->Text        ="";           leRim->Text           ="";
  leQMaxPressure->Text  ="";           leTyreWide->Text      ="";
  rgTyreType->ItemIndex =0;            cmbTestMode->ItemIndex=0;
//  InpTyre->CurrentLoad  =StrToFlt(leTestLoad->Text);
//  InpTyre->InitPressure =StrToFlt(leInitPressure->Text);
//  InpTyre->CurrentSpeed =StrToFlt(leTestSpeed->Text);
  LogPrint("Экран протокола очищен для ввода нового протокола");
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnProtTtlFileSaveAs(TObject *Sender)
{//Сохранить в файле заголовок протокола
	String FileName;
	if (Sender==acProtTitleFileSaveAs)
	{//ручное сохранение
		FileName=acProtTitleFileSaveAs->Dialog->FileName;
		acProtTitleFileSaveAs->Dialog->FileName="";
	}else
	{//автосейв
		FileName=strTitleProt+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.prottitle'");
	}
  InpTyre->WriteTyreToFile(FileName);
  LogPrint("Протокол сохранен в файле \""+FileName+"\"");
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnProtTtlFileOpen(TObject *Sender)
{
  InpTyre->ReadTyreFmFile(acProtTitleFileOpen->Dialog->FileName);
  ShowProtDataOnScrn();
  LogPrint("Протокол прочитан из файла \""+acProtTitleFileOpen->Dialog->FileName+"\"");
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadProtToPosA(TObject *Sender)
{
  ReadProtDataFmScrn();
  *TyreA=*InpTyre;
  ShowProtAData();
  TyreTypeA=TyreA->Model;
  stP1L1TyreTypeA->Caption=TyreTypeA;
  LogPrint("Протокол загружен в поз. А");
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadProtToPosB(TObject *Sender)
{
  ReadProtDataFmScrn();
  *TyreB=*InpTyre;
  ShowProtBData();
  TyreTypeB=TyreB->Model;
  stP1L1TyreTypeB->Caption=TyreTypeB;
  LogPrint("Протокол загружен в поз. Б");
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::ShowProtDataOnScrn(void)// отобразить данные протокола из InpTyre на экране
{
  leProtocolNo->Text    =String(InpTyre->ProtNo);
  leTyreSize->Text      =InpTyre->Size;
  leTyreType->Text      =InpTyre->Model;
  leTestProc->Text      =InpTyre->TestProcedure;
  leStandNo->Text       =InpTyre->StandName;
  leManufacturer->Text  =InpTyre->Manufacturer;
  leDrumD->Text         =FloatToStrF(InpTyre->DrumDiameter,ffFixed,6,2);
  leCustomer->Text      =InpTyre->TestCustomer;
  meManDate->EditText   =InpTyre->CustomDate();
  leSeralNo->Text       =String(InpTyre->SerialNo);
  lePerfSpecNo->Text    =String(InpTyre->PerfSpecNo);
  leOrderNo->Text       =String(InpTyre->OrderNo);
  leFormNo->Text        =String(InpTyre->FormNo);
  leLoadIndex->Text     =InpTyre->LoadIndex;
  leMaxLoad->Text       =FloatToStrF(InpTyre->MaxLoad,ffFixed,6,2);
  leSpeedIndex->Text    =InpTyre->SpeedInd;
  leMaxSpeed->Text      =FloatToStrF(InpTyre->MaxSpeed,ffFixed,6,2);
  leStaticR->Text       =FloatToStrF(InpTyre->StaticR,ffFixed,6,2);
  leOuterD->Text        =FloatToStrF(InpTyre->OuterD,ffFixed,6,2);
  leRim->Text           =InpTyre->WheelRim;
  leQMaxPressure->Text  =FloatToStrF(InpTyre->MaxLoadPress,ffFixed,6,2);
  leTyreWide->Text      =String(InpTyre->ProfileWide);
  rgTyreType->ItemIndex =InpTyre->Type;
  cmbTestMode->ItemIndex=InpTyre->TestMode;
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadTestResFmPosA(TObject *Sender)
{
	#ifndef _mDEBUG
	CheckStend();
	if(!OPCConnectOK){return;}
	#endif	
  OPCControlPause(tReadCycleTimer);
  LogPrint("Загрузка результатов испытаний из контроллера по поз. A");
  pOPC->ReadGr3();
  pOPC->ReadGr7();
  OPCControlResume(tReadCycleTimer);
  TyreA->TotalS           =*S_end_cycle_1; //fakt_distance_1
  TyreA->TotalTime        =*T_end_cycle_1; //fakt_time_1
  TyreA->TestMode         =*type_cycle_1;
  TyreA->StepsNo          =*StepsQty1;
  TyreA->PollsNo          =*PollsQty1;
  ShowProtAData();
  #ifdef _mDEBUG
	TyreA->PollsNo=20;
  #endif
	TyreA->Clear();
	SGClear(sgTestResultA,0);//чистка таблицы
	for (int i = 0; i < MAXNUMOFPOLLS&&i<TyreA->PollsNo; i++)
	{
		if(read_TA[i]!=0&&read_VA[i]!=0&&read_SA[i]!=0&&read_LA[i]!=0&&read_RA[i]!=0&&read_TempA[i])
		{  //+1 для отображения строки данных после пуволнения программы     + отсечка пустых данных
			sgTestResultA->Cells[0][sgTestResultA->RowCount-1]=String(i+1)+":";
			sgTestResultA->Cells[1][sgTestResultA->RowCount-1]=mSecToHMSStr(read_TA[i]);                TyreA->rT[i]   =read_TA[i];
			sgTestResultA->Cells[2][sgTestResultA->RowCount-1]=FloatToStrF(read_VA[i],ffFixed,6,2);     TyreA->rV[i]   =read_VA[i];
			sgTestResultA->Cells[3][sgTestResultA->RowCount-1]=FloatToStrF(read_SA[i],ffFixed,6,2);     TyreA->rS[i]   =read_SA[i];
			sgTestResultA->Cells[4][sgTestResultA->RowCount-1]=FloatToStrF(read_LA[i],ffFixed,6,2);     TyreA->rL[i]   =read_LA[i];
			sgTestResultA->Cells[5][sgTestResultA->RowCount-1]=FloatToStrF(read_RA[i],ffFixed,6,2);     TyreA->rR[i]   =read_RA[i];
			sgTestResultA->Cells[6][sgTestResultA->RowCount-1]=FloatToStrF(read_TempA[i],ffFixed,6,2);  TyreA->rTemp[i]=read_TempA[i];
			sgTestResultA->RowCount++;
		}
	}
	if (sgTestResultA->RowCount>2)
	{
		sgTestResultA->RowCount--;
	}
  sbRB->Panels->Items[2]->Text="Результаты испытаний по поз. А загружены";
  btnSaveTestResPosAToFile->Click();//сохранение
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadTestResFmPosB(TObject *Sender)
{
	#ifndef _mDEBUG
	CheckStend();
	if(!OPCConnectOK){return;}
	#endif	
  OPCControlPause(tReadCycleTimer);
  LogPrint("Загрузка результатов испытаний из контроллера по поз. B");
  pOPC->ReadGr3();
  pOPC->ReadGr11();
  OPCControlResume(tReadCycleTimer);
  TyreB->TotalS           =*S_end_cycle_2;  //fakt_distance_2
  TyreB->TotalTime        =*T_end_cycle_2;  //fakt_time_2
  TyreB->TestMode         =*type_cycle_2;
  TyreB->StepsNo          =*StepsQty2;
  TyreB->PollsNo          =*PollsQty2;
  ShowProtBData();
  #ifdef _mDEBUG
	TyreB->PollsNo=20;
  #endif
	TyreB->Clear();
	SGClear(sgTestResultB,0);//чистка таблицы
	for (int i = 0; i < MAXNUMOFPOLLS&&i<TyreB->PollsNo; i++)
	{
		if(read_TB[i]!=0&&read_VB[i]!=0&&read_SB[i]!=0&&read_LB[i]!=0&&read_RB[i]!=0&&read_TempB[i])
		{//+1 для отображения строки данных после пуволнения программы   + отсечка пустых данных
			sgTestResultB->Cells[0][sgTestResultB->RowCount-1]=String(i+1)+":";
			sgTestResultB->Cells[1][sgTestResultB->RowCount-1]=mSecToHMSStr(read_TB[i]);                TyreB->rT[i]   =read_TB[i];
			sgTestResultB->Cells[2][sgTestResultB->RowCount-1]=FloatToStrF(read_VB[i],ffFixed,6,2);     TyreB->rV[i]   =read_VB[i];
			sgTestResultB->Cells[3][sgTestResultB->RowCount-1]=FloatToStrF(read_SB[i],ffFixed,6,2);     TyreB->rS[i]   =read_SB[i];
			sgTestResultB->Cells[4][sgTestResultB->RowCount-1]=FloatToStrF(read_LB[i],ffFixed,6,2);     TyreB->rL[i]   =read_LB[i];
			sgTestResultB->Cells[5][sgTestResultB->RowCount-1]=FloatToStrF(read_RB[i],ffFixed,6,2);     TyreB->rR[i]   =read_RB[i];
			sgTestResultB->Cells[6][sgTestResultB->RowCount-1]=FloatToStrF(read_TempB[i],ffFixed,6,2);  TyreB->rTemp[i]=read_TempB[i];
			sgTestResultB->RowCount++;
		}
	}
	if (sgTestResultB->RowCount>2)
	{
		sgTestResultB->RowCount--;
	}
  sbRB->Panels->Items[2]->Text="Результаты испытаний по поз. Б загружены";
  btnSaveTestResPosBToFile->Click();//сохранение
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnCloseQuery(TObject *Sender, bool &CanClose)
{
  int res=Application->MessageBox(L"Подтвердите завершение работы",
								   L"Выйти из программы?",
								   MB_YESNO+MB_ICONQUESTION+MB_DEFBUTTON2);
  if(res==IDNO)CanClose=false;
  else {
						// exit from prog
  	TerminateThread(CD_9904Thread,0);
  InpTyre.reset();
  TyreA.reset();
  TyreB.reset();
  VS.reset();
  LdSA.reset();
  LdSB.reset();
  TSA.reset();
  TSB.reset();
  RSA.reset();
  RSB.reset();
  LdCA.reset();
  LdCB.reset();
  closing=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintProtPosAToFile(TObject *Sender)
{//Сохранить результаты испытаний в файле  А
	String FileName;
	if (Sender==acPrintProtPosAToFile)
	{//ручное сохранение
		FileName=acPrintProtPosAToFile->Dialog->FileName;
		acPrintProtPosAToFile->Dialog->FileName="";
	}else
	{//автосейв
		FileName=strProtA+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.prtprot'");
	}
  TyreA->PrintProtToFile(FileName,"А");
  needSaveA=!*Stop1;
  LogPrint("Результаты испытаний по поз. А сохранены в файле \""+FileName+"\"");
  sbRB->Panels->Items[2]->Text="Результаты испытаний по поз. А сохранены в файле \""+FileName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintProtPosBToFile(TObject *Sender)
{//Сохранить результаты испытаний в файле Б
	String FileName;
	if (Sender==acProtTitleFileSaveAs)
	{//ручное сохранение
		FileName=acPrintProtPosBToFile->Dialog->FileName;
		acPrintProtPosBToFile->Dialog->FileName="";
	}else
	{//автосейв
		FileName=strProtB+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.prtprot'");
	}
  TyreB->PrintProtToFile(FileName,"Б");
  needSaveB=!*Stop2;
  LogPrint("Результаты испытаний по поз. Б сохранены в файле \""+FileName+"\"");
  sbRB->Panels->Items[2]->Text="Результаты испытаний по поз. Б сохранены в файле \""+FileName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnVCalibrClear(TObject *Sender)
{
  DesignSpdCalibrPanel();
  VS->Clear();
  sbRB->Panels->Items[2]->Text="Таблица аттестации скорости барабана очищена!";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnVCalibrCalc(TObject *Sender)
{ int ind=VS->Index;
  VS->MeasuredV[ind]=StrToFlt(leMeasuredV->Text);
  VS->ReadoutV[ind] =StrToFlt(leReadV->Text);
  if(VS->MeasuredV[ind]>0){
    VS->RelError[ind]=(VS->MeasuredV[ind]-VS->ReadoutV[ind]);
    sgSpeedCalibr->Cells[2][ind+1]="    "+FloatToStrF(VS->ReadoutV[ind],ffFixed,6,2);
    sgSpeedCalibr->Cells[3][ind+1]="    "+FloatToStrF(VS->MeasuredV[ind],ffFixed,6,2);
    sgSpeedCalibr->Cells[4][ind+1]="    "+FloatToStrF(VS->RelError[ind],ffFixed,6,2);
    sbRB->Panels->Items[2]->Text="Значение погрешности рассчитано!";
  }
  else {
    sbRB->Panels->Items[2]->Text="Не введено измеренное значение скорости!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnNextCalibrVBtn(TObject *Sender)
{ int Ind=VS->Index;
  int RowCnt=sgSpeedCalibr->RowCount;
// перерисовка предыдущей ячейки
  if     (Ind< 9)sgSpeedCalibr->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind<RowCnt-1)sgSpeedCalibr->Cells[0][Ind+1]=" "+String(Ind+1)+":";
  VS->Index++;
  btnPrevCalibrV->Enabled=true;
  if(VS->Index>=RowCnt-2){
    VS->Index=RowCnt-2;
    btnNextCalibrV->Enabled=false;
//    return;
  }
// перерисовка текущей ячейки
  Ind=VS->Index;
//  sbRB->Panels->Items[2]->Text="Ind="+String(Ind);
  if     (Ind< 9)sgSpeedCalibr->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind<RowCnt-1)sgSpeedCalibr->Cells[0][Ind+1]=" " +String(Ind+1)+":";
// прокрутка таблицы
//  LogPrint("Next: TopRow="+String(sgSpeedCalibr->TopRow)+", VS->Index="+String(Ind),clAqua);
  bool IndLowerThenMiddleTable=((Ind-sgSpeedCalibr->TopRow) > ((sgSpeedCalibr->VisibleRowCount)/2-1));
  bool RowRestGreatThenTable=(sgSpeedCalibr->RowCount-sgSpeedCalibr->TopRow)>(sgSpeedCalibr->VisibleRowCount);
  if( IndLowerThenMiddleTable && RowRestGreatThenTable)
      sgSpeedCalibr->TopRow++;
  leCurrentVSet->Text=FloatToStrF(VS->TargetV[VS->Index],ffFixed,6,2);
  *DrumSpeed=VS->TargetV[VS->Index];
//  LogPrint("Mode: Next Speed, DrumSpeed="+FloatToStr(*DrumSpeed));
  CheckStend();
  if(OPCConnectOK) {
    pOPC->WriteGr3(DrumSpeed);
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя задать скорость - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrevCalibrVBtn(TObject *Sender)
{ int Ind=VS->Index;
  int RowCnt=sgSpeedCalibr->RowCount;
// перерисовка предыдущей ячейки
  if      (Ind<9)sgSpeedCalibr->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind<RowCnt-1)sgSpeedCalibr->Cells[0][Ind+1]=" "+String(Ind+1)+":";
  VS->Index--;
  btnNextCalibrV->Enabled=true;
  if(VS->Index<=0){
    VS->Index=0;
    btnPrevCalibrV->Enabled=false;
//    return;
  }
// перерисовка текущей ячейки
  Ind=VS->Index;
  if      (Ind<9)sgSpeedCalibr->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind<RowCnt-1)sgSpeedCalibr->Cells[0][Ind+1]=" "+String(Ind+1)+":";
// прокрутка таблицы
//  LogPrint("Prev: TopRow="+String(sgSpeedCalibr->TopRow)+", VS->Index="+String(Ind),clAqua);
  bool IndAboveThenMiddleTable=((Ind-sgSpeedCalibr->TopRow) < ((sgSpeedCalibr->VisibleRowCount)/2-1));
//  bool RowRestGreatThenTable=(sgSpeedCalibr->RowCount-sgSpeedCalibr->TopRow)>(sgSpeedCalibr->VisibleRowCount);
  if( IndAboveThenMiddleTable && sgSpeedCalibr->TopRow>1)
      sgSpeedCalibr->TopRow--;
  leCurrentVSet->Text=FloatToStrF(VS->TargetV[VS->Index],ffFixed,6,2);
  *DrumSpeed=VS->TargetV[VS->Index];
//  LogPrint("Mode: Previous Speed, DrumSpeed="+FloatToStr(*DrumSpeed));
  CheckStend();
  if(OPCConnectOK) {
    pOPC->WriteGr3(DrumSpeed);
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя задать скорость - нет соединения со стендом!";
  }

}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnCalibrDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{ int SlctRow;
  if((TStringGrid*) Sender==sgSpeedCalibr){
    SlctRow=(VS->Index+1);
//    LogPrint("Selected Speed row is "+String(SlctRow),clAqua);
  }
  else if((TStringGrid*) Sender==sgLoadCalibrA){
    SlctRow=(LdSA->Index+1);
//    LogPrint("Selected Load A row is "+String(SlctRow),clAqua);
  }
  else if((TStringGrid*) Sender==sgLoadCalibrB){
    SlctRow=(LdSB->Index+1);
//    LogPrint("Selected Load B row is "+String(SlctRow),clAqua);
  }
  else if((TStringGrid*) Sender==sgTCalibrA){
    SlctRow=(TSA->Index+1);
//    LogPrint("Selected Load B row is "+String(SlctRow),clAqua);
  }
  else if((TStringGrid*) Sender==sgTCalibrB){
    SlctRow=(TSB->Index+1);
//    LogPrint("Selected Load B row is "+String(SlctRow),clAqua);
  }
  else if((TStringGrid*) Sender==sgRCalibrA){
    SlctRow=(RSA->Index+1);
//    LogPrint("Selected Load B row is "+String(SlctRow),clAqua);
  }
  else if((TStringGrid*) Sender==sgRCalibrB){
    SlctRow=(RSB->Index+1);
//    LogPrint("Selected Load B row is "+String(SlctRow),clAqua);
  }
  else if((TStringGrid*) Sender==sgLoadSertA){
    SlctRow=(LdCA->Index+1);
//    LogPrint("Selected Load B row is "+String(SlctRow),clAqua);
  }
  else if((TStringGrid*) Sender==sgLoadSertB){
    SlctRow=(LdCB->Index+1);
//    LogPrint("Selected Load B row is "+String(SlctRow),clAqua);
  }
  else return;
  if((ACol==0) && (ARow==SlctRow)) {
    ((TStringGrid*) Sender)->Canvas->Brush->Color=clAqua;
    ((TStringGrid*) Sender)->Canvas->FillRect(Rect);
    ((TStringGrid*) Sender)->Canvas->TextOutA(Rect.Left,Rect.Top,sgSpeedCalibr->Cells[ACol][ARow]);
  }    
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintSpdCalibrProtocol(TObject *Sender)
{//Распечатать протокол (Аттестация барабана)
	String FileName;
	if (Sender==acPrintSpdCalibrProt)
	{//ручное сохранение
		FileName=acPrintSpdCalibrProt->Dialog->FileName;
		acPrintSpdCalibrProt->Dialog->FileName="";
	}else
	{//автосейв
		FileName=strSpdCalibr+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.scprt'");
	}
  VS->PrintProtocol(FileName);
  LogPrint("Протокол аттестации барабана сохранен в файле \""+FileName+"\"");
  sbRB->Panels->Items[2]->Text="Протокол аттестации барабана сохранен в файле \""+FileName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPump1On(TObject *Sender)
{
  CheckStend();
  if(OPCConnectOK){
    if(*ManualMode1 && *ManualMode2){
      *Pump1On=true; *KeepLoad1=true;
	  if(pcRB->ActivePage==tsCalibration){
//        if(pcCalibration->ActivePage==tsLoadCalibrA || pcCalibration->ActivePage==tsLoadCalibrB){
		  *Loading_1=LdSA->TargetLd[LdSA->Index];
		  LogPrint("Mode: LoadSert, LoadingA="+FloatToStr(*Loading_1));
		  LogPrintF(LogFName(),"Режим аттестации нагрузки, насос 1 включен, установлена нагрузка="+FloatToStr(*Loading_1));
//		}
	  }
	  else if(pcRB->ActivePage==tsSert){
		if(pcSert->ActivePage==tsLoadSert){
		  *Loading_1=LdCA->TargetLd[LdCA->Index];
		  LogPrint("Mode: LoadCalibr, LoadingA="+FloatToStr(*Loading_1));
		  LogPrintF(LogFName(),"Режим калибровки нагрузки, насос 1 включен, установлена нагрузка="+FloatToStr(*Loading_1));
		  leCurrentLoadSertSetA->Text=FloatToStrF(*Loading_1,ffFixed,6,2);
		}
	  }
      OPCControlPause(tReadCycleTimer);
      pOPC->BenchControl(Pump1On,KeepLoad1,Loading_1);
      OPCControlResume(tReadCycleTimer);
	  sbRB->Panels->Items[2]->Text="Насос 1 включен!";
	#ifdef USEPROCESSDELAY
	TLabeledEdit *leMeasLoad=0;
	if (Sender==btnSertPumpOnA)
	{
		leMeasLoad=leMeasLoadSertA;
	}
	if (Sender==btnPumpOnA)
	{
		leMeasLoad=leMeasuredLoadA;
	}
	if (leMeasLoad)
	{
		leMeasLoad->ReadOnly=true;
		leMeasLoad->Color=clSilver;
		const slp=500;//500 мс для слипа
		for (int i =0; i <DELAY_TIME ; i+=slp)
		{
			Sleep(slp);
			Application->ProcessMessages();//обработка сообщений винды
		}
		leMeasLoad->Color=clWindow;
		leMeasLoad->ReadOnly=false;
	}
	#endif
    }
    else {
      sbRB->Panels->Items[2]->Text="Насос 1 не включен - стенд не в ручном режиме!";
    }
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя включить насос - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPump1Off(TObject *Sender)
{
  CheckStend();
  if(OPCConnectOK){
    if(*ManualMode1 && *ManualMode2){
      *Pump1On=false; *KeepLoad1=false;
      OPCControlPause(tReadCycleTimer);
      pOPC->BenchControl(Pump1On,KeepLoad1);
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Насос 1 выключен!";
	  LogPrintF(LogFName(),"Насос 1 выключен");
    }
    else {
      sbRB->Panels->Items[2]->Text="Насос 1 не выключен - стенд не в ручном режиме!";
    }
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя выключить насос - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPump2On(TObject *Sender)
{
  CheckStend();
  if(OPCConnectOK){
    if(*ManualMode1 && *ManualMode2){
      *Pump1On=true; *KeepLoad2=true;
	  if(pcRB->ActivePage==tsCalibration){
//		if(pcCalibration->ActivePage==tsLoadCalibrA || pcCalibration->ActivePage==tsLoadCalibrB){
		  *Loading_2=LdSB->TargetLd[LdSB->Index];
//		  leCurrentLoadSertSetB->Text=FloatToStrF(*Loading_2,ffFixed,6,2);
		  LogPrint("Mode: LoadSert, LoadingB="+FloatToStr(*Loading_2));
		  LogPrintF(LogFName(),"Режим аттестации нагрузки, насос 2 включен, установлена нагрузка="+FloatToStr(*Loading_2));
//		}
	  }
	  else if(pcRB->ActivePage==tsSert) {
		*Loading_2=LdCB->TargetLd[LdCB->Index];
//		leCurrentLoadSertSetB->Text=FloatToStrF(*Loading_2,ffFixed,6,2);
		LogPrint("Mode: LoadCalibr, LoadingB="+FloatToStr(*Loading_2));
		LogPrintF(LogFName(),"Режим калибровки нагрузки, насос 2 включен, установлена нагрузка="+FloatToStr(*Loading_2));
	  }
	  OPCControlPause(tReadCycleTimer);
      pOPC->BenchControl(Pump2On,KeepLoad2,Loading_2);
      OPCControlResume(tReadCycleTimer);
	  sbRB->Panels->Items[2]->Text="Насос 2 включен!";
	#ifdef USEPROCESSDELAY
	TLabeledEdit *leMeasLoad=0;
	if (Sender==btnSertPumpOnB)
	{
		leMeasLoad=leMeasLoadSertB;
	}
	if (Sender==btnPumpOnB)
	{
		leMeasLoad=leMeasuredLoadB;
	}
	if (leMeasLoad)
	{
		leMeasLoad->ReadOnly=true;
		leMeasLoad->Color=clSilver;
		const slp=500;//500 мс для слипа
		for (int i =0; i <DELAY_TIME ; i+=slp)
		{
			Sleep(slp);
			Application->ProcessMessages();//обработка сообщений винды
		}
		leMeasLoad->Color=clWindow;
		leMeasLoad->ReadOnly=false;
	}
	#endif
    }
    else {
      sbRB->Panels->Items[2]->Text="Насос 2 не включен - стенд не в ручном режиме!";
    }
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя включить насос - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPump2Off(TObject *Sender)
{
  CheckStend();
  if(OPCConnectOK){
    if(*ManualMode1 && *ManualMode2){
      *Pump2On=false; *KeepLoad2=false;
      OPCControlPause(tReadCycleTimer);
      pOPC->BenchControl(Pump2On,KeepLoad2);
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Насос 2 выключен!";
	  LogPrintF(LogFName(),"Насос 2 выключен");
    }
    else {
      sbRB->Panels->Items[2]->Text="Насос 2 не выключен - стенд не в ручном режиме!";
    }
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя выключить насос - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnNextCalibrLoadBtn(TObject *Sender)
{ LSert *LdSert; TButton *btnNext, *btnPrev;
  TStringGrid *sgLoad; TLabeledEdit *leLoadSet, *leMeasLoad;
  float *Loading; int pos;
  if((TButton *)Sender==btnNextCalibrLoadA){
    LdSert    =LdSA.get();
    btnNext   =btnNextCalibrLoadA;
    btnPrev   =btnPrevCalibrLoadA;
    sgLoad    =sgLoadCalibrA;
    leLoadSet =leCurrentLoadSetA;
    leMeasLoad=leMeasuredLoadA;
    Loading   =Loading_1;
    pos       =0;
  }
  else if((TButton *)Sender==btnNextCalibrLoadB){
    LdSert    =LdSB.get();
    btnNext   =btnNextCalibrLoadB;
    btnPrev   =btnPrevCalibrLoadB;
    sgLoad    =sgLoadCalibrB;
    leLoadSet =leCurrentLoadSetB;
	leMeasLoad=leMeasuredLoadB;
    Loading   =Loading_2;
    pos       =1;
  }
  else return;
  int Ind=LdSert->Index;
  int RowCnt=sgLoad->RowCount;
// перерисовка предыдущей ячейки
  if     (Ind <        9)sgLoad->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgLoad->Cells[0][Ind+1]=" "+String(Ind+1)+":";
  LdSert->Index++;
  btnPrev->Enabled=true;
  if(LdSert->Index>=RowCnt-2){
    LdSert->Index=RowCnt-2;
	btnNext->Enabled=false;
//    return;
  }
// перерисовка текущей ячейки
  Ind=LdSert->Index;
  if     (Ind <        9)sgLoad->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgLoad->Cells[0][Ind+1]=" " +String(Ind+1)+":";
// прокрутка таблицы не требуется так как вся таблица на экране
  sgLoad->TopRow=1;
  leLoadSet->Text =FloatToStrF(LdSert->TargetLd[LdSert->Index],ffFixed,6,2);
  leMeasLoad->Text="0.0";
  #ifdef USEPROCESSDELAY
  leMeasLoad->ReadOnly=true;
  leMeasLoad->Color=clSilver;
  #endif
  *Loading        =LdSert->TargetLd[LdSert->Index];
  if(pos==0)LogPrint("Mode: Next load A, load="+FloatToStr(*Loading));
  if(pos==1)LogPrint("Mode: Next load B, load="+FloatToStr(*Loading));
  CheckStend();
  if(OPCConnectOK) {
	pOPC->WriteGr3(Loading);
	#ifdef USEPROCESSDELAY
	const slp=500;//500 мс для слипа
	for (int i =0; i <DELAY_TIME ; i+=slp)
	{
		Sleep(slp);
		Application->ProcessMessages();//обработка сообщений винды
	}
	leMeasLoad->Color=clWindow;
	leMeasLoad->ReadOnly=false;
	#endif
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя задать нагрузку - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrevCalibrLoadBtn(TObject *Sender)
{ LSert *LdSert; TButton *btnNext, *btnPrev;
  TStringGrid *sgLoad; TLabeledEdit *leLoadSet, *leMeasLoad;
  float *Loading; int pos;
  if((TButton *)Sender==btnPrevCalibrLoadA){
	LdSert    =LdSA.get();
    btnNext   =btnNextCalibrLoadA;
    btnPrev   =btnPrevCalibrLoadA;
    sgLoad    =sgLoadCalibrA;
    leLoadSet =leCurrentLoadSetA;
    leMeasLoad=leMeasuredLoadA;
    Loading   =Loading_1;
    pos       =0;
  }
  else if((TButton *)Sender==btnPrevCalibrLoadB){
    LdSert    =LdSB.get();
    btnNext   =btnNextCalibrLoadB;
    btnPrev   =btnPrevCalibrLoadB;
    sgLoad    =sgLoadCalibrB;
    leLoadSet =leCurrentLoadSetB;
    leMeasLoad=leMeasuredLoadB;
    Loading   =Loading_2;
    pos       =1;
  }
  else return;
  int Ind=LdSert->Index;// LdSA->Index;
  int RowCnt=sgLoad->RowCount; //sgLoadCalibrA->RowCount;
// перерисовка предыдущей ячейки
  if     (Ind <        9)sgLoad->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgLoad->Cells[0][Ind+1]=" "+String(Ind+1)+":";
  LdSert->Index--;
  btnNext->Enabled=true;
  if(LdSert->Index <= 0){
    LdSert->Index=0;
    btnPrev->Enabled=false;
//    return;
  }
// перерисовка текущей ячейки
  Ind=LdSert->Index;//Ind=LdSA->Index;
//  sbRB->Panels->Items[2]->Text="Ind="+String(Ind);
  if     (Ind <        9)sgLoad->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgLoad->Cells[0][Ind+1]=" " +String(Ind+1)+":";
// прокрутка таблицы не требуется так как вся таблица на экране
//  LogPrint("Next: TopRow="+String(sgLoad->TopRow)+", LdSA->Index="+String(Ind),clAqua);
//  bool IndAboveThenMiddleTable=((Ind-sgLoad->TopRow) < ((sgLoad->VisibleRowCount)/2-1));
//  if(IndAboveThenMiddleTable && sgLoad->TopRow>1)
  sgLoad->TopRow=1;
  leLoadSet->Text =FloatToStrF(LdSert->TargetLd[Ind]/*LdSA->TargetLd[LdSA->Index]*/,ffFixed,6,2);
  leMeasLoad->Text="0.0";
  #ifdef USEPROCESSDELAY
  leMeasLoad->ReadOnly=true;
  leMeasLoad->Color=clSilver;
  #endif
  *Loading        =LdSert->TargetLd[Ind];//LdSA->TargetLd[LdSA->Index];
  if(pos==0)LogPrint("Mode: Next load A, load="+FloatToStr(*Loading));
  if(pos==1)LogPrint("Mode: Next load B, load="+FloatToStr(*Loading));
  CheckStend();
  if(OPCConnectOK) {
	pOPC->WriteGr3(Loading);
	#ifdef USEPROCESSDELAY
	const slp=500;//500 мс для слипа
	for (int i =0; i <DELAY_TIME ; i+=slp)
	{
		Sleep(slp);
		Application->ProcessMessages();//обработка сообщений винды
	}
	leMeasLoad->Color=clWindow;
	leMeasLoad->ReadOnly=false;
	#endif
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя задать нагрузку - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadCalibrTableClear(TObject *Sender)
{
  if((TButton *)Sender==btnClearLoadCalibreTableA){
    LdSA->Clear();
    DesignLoadCalibrAPanel();
    sbRB->Panels->Items[2]->Text="Таблица аттестации нагрузки поз. А очищена!";
  }
  else if((TButton *)Sender==btnClearLoadCalibreTableB){
    LdSB->Clear();
    DesignLoadCalibrBPanel();
    sbRB->Panels->Items[2]->Text="Таблица аттестации нагрузки поз. Б очищена!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadCalibrCalc(TObject *Sender)
{ LSert *LdSert;
  TStringGrid *sgLoad; TLabeledEdit *leMeasLoad, *leReadoutLoad;
  if((TButton *)Sender==btnLoadCalibrCalcA){
	LdSert       =LdSA.get();
    sgLoad       =sgLoadCalibrA;
    leMeasLoad   =leMeasuredLoadA;
    leReadoutLoad=leReadLoadA;
  }
  else if((TButton *)Sender==btnLoadCalibrCalcB){
    LdSert       =LdSB.get();
    sgLoad       =sgLoadCalibrB;
    leMeasLoad   =leMeasuredLoadB;
    leReadoutLoad=leReadLoadB;
  }
  int ind=LdSert->Index;
  LdSert->MeasuredLd[ind]=StrToFlt(leMeasLoad->Text);
  LdSert->ReadoutLd[ind] =StrToFlt(leReadoutLoad->Text);
  if(LdSert->MeasuredLd[ind]>0){
    LdSert->RelError[ind]=(LdSert->MeasuredLd[ind]-LdSert->ReadoutLd[ind])/LdSert->MeasuredLd[ind]*100.0;
    sgLoad->Cells[2][ind+1]="    "+FloatToStrF(LdSert->MeasuredLd[ind],ffFixed,6,2);
    sgLoad->Cells[3][ind+1]="    "+FloatToStrF(LdSert->ReadoutLd[ind],ffFixed,6,2);
    sgLoad->Cells[4][ind+1]="    "+FloatToStrF(LdSert->RelError[ind],ffFixed,6,2);
    sbRB->Panels->Items[2]->Text="Значение погрешности рассчитано!";
  }
  else {
    sbRB->Panels->Items[2]->Text="Не введено измеренное значение нагрузки!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintLoadCalibrProtA(TObject *Sender)
{//Распечатать протокол (Аттестация по нагрузке) А
	String FileName;
	if (Sender==acPrintLoadCalibrProtA)
	{//ручное сохранение
		FileName=acPrintLoadCalibrProtA->Dialog->FileName;
		acPrintLoadCalibrProtA->Dialog->FileName="";
	}else
	{//автосейв
		FileName=strLoadCalibrA+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.lcprt'");
	}
  LdSA->PrintProtocol(FileName,"А");
  LogPrint("Протокол аттестации нагрузки поз. А сохранен в файле \""+FileName+"\"");
  sbRB->Panels->Items[2]->Text="Протокол аттестации нагрузки поз. А сохранен в файле \""+FileName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintLoadCalibrProtB(TObject *Sender)
{//Распечатать протокол (Аттестация по нагрузке) Б
	String FileName;
	if (Sender==acPrintLoadCalibrProtB)
	{//ручное сохранение
		FileName=acPrintLoadCalibrProtB->Dialog->FileName;
		acPrintLoadCalibrProtB->Dialog->FileName="";
	}else
	{//автосейв
		FileName=strLoadCalibrB+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.lcprt'");
	}
  LdSB->PrintProtocol(FileName,"Б");
  LogPrint("Протокол аттестации нагрузки поз. Б сохранен в файле \""+FileName+"\"");
  sbRB->Panels->Items[2]->Text="Протокол аттестации нагрузки поз. Б сохранен в файле \""+FileName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnNextCalibrTBtn(TObject *Sender)
{ TSert *TS; TButton *btnNext, *btnPrev;
  TStringGrid *sgTbl; TLabeledEdit *leMeas;
  float *Loading; //int pos=0;
  if((TButton *)Sender==btnNextTCalibrA){
	TS     =TSA.get();
    btnNext=btnNextTCalibrA;
    btnPrev=btnPrevTCalibrA;
    sgTbl  =sgTCalibrA;
    leMeas =leMeasTA;
//    pos    =0;
  }
  else if((TButton *)Sender==btnNextTCalibrB){
    TS     =TSB.get();
    btnNext=btnNextTCalibrB;
    btnPrev=btnPrevTCalibrB;
    sgTbl  =sgTCalibrB;
    leMeas =leMeasTB;
//    pos    =1;
  }
  else return;
  int Ind=TS->Index;
  int RowCnt=sgTbl->RowCount;
// перерисовка предыдущей ячейки
  if     (Ind <        9)sgTbl->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgTbl->Cells[0][Ind+1]=" "+String(Ind+1)+":";
  TS->Index++;
  btnPrev->Enabled=true;
  if(TS->Index>=RowCnt-2){
    TS->Index=RowCnt-2;
    btnNext->Enabled=false;
//    return;
  }
// перерисовка текущей ячейки
  Ind=TS->Index;
  if     (Ind <        9)sgTbl->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgTbl->Cells[0][Ind+1]=" " +String(Ind+1)+":";
// прокрутка таблицы не требуется так как вся таблица на экране
//  LogPrint("Next: TopRow="+String(sgLoadCalibrA->TopRow)+", LdSA->Index="+String(Ind),clAqua);
//  bool IndLowerThenMiddleTable=((Ind-sgLoadCalibrA->TopRow) > ((sgLoadCalibrA->VisibleRowCount)/2-1));
//  bool RowRestGreatThenTable=(sgLoadCalibrA->RowCount-sgLoadCalibrA->TopRow)>(sgLoadCalibrA->VisibleRowCount);
//  if(IndLowerThenMiddleTable && RowRestGreatThenTable)
//      sgLoadCalibrA->TopRow++;
  sgTbl->TopRow=1;
  leMeas->Text="0.0";
//  if(pos==0)LogPrint("Mode: Next T A, Temp="+leMeas->Text);
//  if(pos==1)LogPrint("Mode: Next T B, Temp="+leMeas->Text);
//  if(OPCConnectOK) {
//    pOPC->WriteGr3(Loading);
//  }
//  else {
//    sbRB->Panels->Items[2]->Text="Нельзя задать нагрузку - нет соединения со стендом!";
//  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrevCalibrTBtn(TObject *Sender)
{ TSert *TS; TButton *btnNext, *btnPrev;
  TStringGrid *sgTbl; TLabeledEdit *leMeas;
  float *Loading; //int pos=0;
  if((TButton *)Sender==btnPrevTCalibrA){
	TS     =TSA.get();
    btnNext=btnNextTCalibrA;
    btnPrev=btnPrevTCalibrA;
    sgTbl  =sgTCalibrA;
    leMeas =leMeasTA;
//    pos    =0;
  }
  else if((TButton *)Sender==btnPrevTCalibrB){
    TS     =TSB.get();
    btnNext=btnNextTCalibrB;
    btnPrev=btnPrevTCalibrB;
    sgTbl  =sgTCalibrB;
    leMeas =leMeasTB;
//    pos    =1;
  }
  else return;
  int Ind=TS->Index;
  int RowCnt=sgTbl->RowCount;
// перерисовка предыдущей ячейки
  if     (Ind <        9)sgTbl->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgTbl->Cells[0][Ind+1]=" "+String(Ind+1)+":";
  TS->Index--;
  btnNext->Enabled=true;
  if(TS->Index<=0){
    TS->Index=0;
    btnPrev->Enabled=false;
  }
// перерисовка текущей ячейки
  Ind=TS->Index;
  if     (Ind <        9)sgTbl->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgTbl->Cells[0][Ind+1]=" " +String(Ind+1)+":";
// прокрутка таблицы не требуется так как вся таблица на экране
//  LogPrint("Next: TopRow="+String(sgLoadCalibrA->TopRow)+", LdSA->Index="+String(Ind),clAqua);
//  bool IndLowerThenMiddleTable=((Ind-sgLoadCalibrA->TopRow) > ((sgLoadCalibrA->VisibleRowCount)/2-1));
//  bool RowRestGreatThenTable=(sgLoadCalibrA->RowCount-sgLoadCalibrA->TopRow)>(sgLoadCalibrA->VisibleRowCount);
//  if(IndLowerThenMiddleTable && RowRestGreatThenTable)
//      sgLoadCalibrA->TopRow++;
  sgTbl->TopRow=1;
  leMeas->Text="0.0";
//  if(pos==0)LogPrint("Mode: Prev T A, Temp="+leMeas->Text);
//  if(pos==1)LogPrint("Mode: Prev T B, Temp="+leMeas->Text);
//  if(OPCConnectOK) {
//    pOPC->WriteGr3(Loading);
//  }
//  else {
//    sbRB->Panels->Items[2]->Text="Нельзя задать нагрузку - нет соединения со стендом!";
//  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnTCalibrTableClear(TObject *Sender)
{
  if((TButton *)Sender==btnClearTCalibrTableA){
    TSA->Clear();
    DesignTCalibrAPanel();
    sbRB->Panels->Items[2]->Text="Таблица аттестации датчика температуры поз. А очищена!";
  }
  else if((TButton *)Sender==btnClearTCalibrTableB){
    TSB->Clear();
    DesignTCalibrBPanel();
    sbRB->Panels->Items[2]->Text="Таблица аттестации датчика температуры поз. Б очищена!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnTCalibrCalc(TObject *Sender)
{ TSert *TS;
  TStringGrid *sgTbl; TLabeledEdit *leMeas, *leRead;
  if((TButton *)Sender==btnTCalibrCalcA){
	TS       =TSA.get();
    sgTbl    =sgTCalibrA;
    leMeas   =leMeasTA;
    leRead   =leReadTA;
  }
  else if((TButton *)Sender==btnTCalibrCalcB){
    TS       =TSB.get();
    sgTbl    =sgTCalibrB;
    leMeas   =leMeasTB;
    leRead   =leReadTB;
  }
  int ind=TS->Index;
  TS->MeasuredT[ind]=StrToFlt(leMeas->Text);
  TS->ReadoutT[ind] =StrToFlt(leRead->Text);
//  TS->ReadoutT[ind] =TS->MeasuredT[ind]*(1.0+float(50-random(100))/5000.0);   // DEBUG!!!!!!!!!!!!!!!!!!!
//  leRead->Text      =FloatToStrF(TS->ReadoutT[ind],ffFixed,6,2);              // DEBUG!!!!!!!!!!!!!!!!!!!
  if(TS->MeasuredT[ind]>0){
    TS->RelError[ind]=(TS->MeasuredT[ind]-TS->ReadoutT[ind]);
    sgTbl->Cells[1][ind+1]="    "+FloatToStrF(TS->ReadoutT[ind],ffFixed,6,2);
    sgTbl->Cells[2][ind+1]="    "+FloatToStrF(TS->MeasuredT[ind],ffFixed,6,2);
    sgTbl->Cells[3][ind+1]="    "+FloatToStrF(TS->RelError[ind],ffFixed,6,2);
    sbRB->Panels->Items[2]->Text="Значение погрешности рассчитано!";
  }
  else {
    sbRB->Panels->Items[2]->Text="Не введено измеренное значение температуры!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintTCalibrProtA(TObject *Sender)
{//Распечатать протокол (Аттестация по температуре) А
	String FileName;
	if (Sender==acPrintTCalibrProtA)
	{//ручное сохранение
		FileName=acPrintTCalibrProtA->Dialog->FileName;
		acPrintTCalibrProtA->Dialog->FileName="";
	}else
	{//автосейв
		FileName=strTCalibrA+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.tcprt'");
	}
  TSA->PrintProtocol(FileName,"А");
  LogPrint("Протокол аттестации датчика температуры поз. А сохранен в файле \""+FileName+"\"");
  sbRB->Panels->Items[2]->Text="Протокол аттестации датчика температуры поз. А сохранен в файле \""+FileName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintTCalibrProtB(TObject *Sender)
{//Распечатать протокол (Аттестация по температуре) Б
	String FileName;
	if (Sender==acPrintTCalibrProtB)
	{//ручное сохранение
		FileName=acPrintTCalibrProtB->Dialog->FileName;
		acPrintTCalibrProtB->Dialog->FileName="";
	}else
	{//автосейв
		FileName=strTCalibrB+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.tcprt'");
	}
  TSB->PrintProtocol(FileName,"Б");
  LogPrint("Протокол аттестации датчика температуры поз. Б сохранен в файле \""+FileName+"\"");
  sbRB->Panels->Items[2]->Text="Протокол аттестации датчика температуры поз. Б сохранен в файле \""+FileName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnNextCalibrRBtn(TObject *Sender)
{ RSert *RS; TButton *btnNext, *btnPrev;
  TStringGrid *sgTbl; TLabeledEdit *leMeas;
  if((TButton *)Sender==btnNextRCalibrA){
	RS     =RSA.get();
    btnNext=btnNextRCalibrA;
    btnPrev=btnPrevRCalibrA;
    sgTbl  =sgRCalibrA;
    leMeas =leMeasRA;
  }
  else if((TButton *)Sender==btnNextRCalibrB){
    RS     =RSB.get();
    btnNext=btnNextRCalibrB;
    btnPrev=btnPrevRCalibrB;
    sgTbl  =sgRCalibrB;
    leMeas =leMeasRB;
  }
  else return;
  int Ind=RS->Index;
  int RowCnt=sgTbl->RowCount;
// перерисовка предыдущей ячейки
  if     (Ind <        9)sgTbl->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgTbl->Cells[0][Ind+1]=" "+String(Ind+1)+":";
  RS->Index++;
  btnPrev->Enabled=true;
  if(RS->Index>=RowCnt-2){
    RS->Index=RowCnt-2;
    btnNext->Enabled=false;
//    return;
  }
// перерисовка текущей ячейки
  Ind=RS->Index;
  if     (Ind <        9)sgTbl->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgTbl->Cells[0][Ind+1]=" " +String(Ind+1)+":";
// прокрутка таблицы не требуется так как вся таблица на экране
//  LogPrint("Next: TopRow="+String(sgLoadCalibrA->TopRow)+", LdSA->Index="+String(Ind),clAqua);
//  bool IndLowerThenMiddleTable=((Ind-sgLoadCalibrA->TopRow) > ((sgLoadCalibrA->VisibleRowCount)/2-1));
//  bool RowRestGreatThenTable=(sgLoadCalibrA->RowCount-sgLoadCalibrA->TopRow)>(sgLoadCalibrA->VisibleRowCount);
//  if(IndLowerThenMiddleTable && RowRestGreatThenTable)
//      sgLoadCalibrA->TopRow++;
  sgTbl->TopRow=1;
  leMeas->Text="0.0";
//  if(pos==0)LogPrint("Mode: Next T A, Temp="+leMeas->Text);
//  if(pos==1)LogPrint("Mode: Next T B, Temp="+leMeas->Text);
//  if(OPCConnectOK) {
//    pOPC->WriteGr3(Loading);
//  }
//  else {
//    sbRB->Panels->Items[2]->Text="Нельзя задать нагрузку - нет соединения со стендом!";
//  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrevCalibrRBtn(TObject *Sender)
{ RSert *RS; TButton *btnNext, *btnPrev;
  TStringGrid *sgTbl; TLabeledEdit *leMeas;
  if((TButton *)Sender==btnPrevRCalibrA){
	RS     =RSA.get();
    btnNext=btnNextRCalibrA;
    btnPrev=btnPrevRCalibrA;
    sgTbl  =sgRCalibrA;
    leMeas =leMeasRA;
  }
  else if((TButton *)Sender==btnPrevRCalibrB){
    RS     =RSB.get();
    btnNext=btnNextRCalibrB;
    btnPrev=btnPrevRCalibrB;
    sgTbl  =sgRCalibrB;
    leMeas =leMeasRB;
  }
  else return;
  int Ind=RS->Index;
  int RowCnt=sgTbl->RowCount;
// перерисовка предыдущей ячейки
  if     (Ind <        9)sgTbl->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgTbl->Cells[0][Ind+1]=" "+String(Ind+1)+":";
  RS->Index--;
  btnPrev->Enabled=true;
  if(RS->Index<=0){
    RS->Index=0;
    btnNext->Enabled=false;
//    return;
  }
// перерисовка текущей ячейки
  Ind=RS->Index;
  if     (Ind <        9)sgTbl->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgTbl->Cells[0][Ind+1]=" " +String(Ind+1)+":";
// прокрутка таблицы не требуется так как вся таблица на экране
//  LogPrint("Next: TopRow="+String(sgLoadCalibrA->TopRow)+", LdSA->Index="+String(Ind),clAqua);
//  bool IndLowerThenMiddleTable=((Ind-sgLoadCalibrA->TopRow) > ((sgLoadCalibrA->VisibleRowCount)/2-1));
//  bool RowRestGreatThenTable=(sgLoadCalibrA->RowCount-sgLoadCalibrA->TopRow)>(sgLoadCalibrA->VisibleRowCount);
//  if(IndLowerThenMiddleTable && RowRestGreatThenTable)
//      sgLoadCalibrA->TopRow++;
  sgTbl->TopRow=1;
  leMeas->Text="0.0";
//  if(pos==0)LogPrint("Mode: Next T A, Temp="+leMeas->Text);
//  if(pos==1)LogPrint("Mode: Next T B, Temp="+leMeas->Text);
//  if(OPCConnectOK) {
//    pOPC->WriteGr3(Loading);
//  }
//  else {
//    sbRB->Panels->Items[2]->Text="Нельзя задать нагрузку - нет соединения со стендом!";
//  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnRCalibrTableClear(TObject *Sender)
{
  if((TButton *)Sender==btnClearRCalibrTableA){
    RSA->Clear();
    DesignRCalibrAPanel();
    sbRB->Panels->Items[2]->Text="Таблица аттестации радиуса поз. А очищена!";
  }
  else if((TButton *)Sender==btnClearRCalibrTableB){
    RSB->Clear();
    DesignRCalibrBPanel();
    sbRB->Panels->Items[2]->Text="Таблица аттестации радиуса поз. Б очищена!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnRCalibrCalc(TObject *Sender)
{ RSert *RS;
  TStringGrid *sgTbl; TLabeledEdit *leMeas, *leRead;
  if((TButton *)Sender==btnRCalibrCalcA){
	RS       =RSA.get();
    sgTbl    =sgRCalibrA;
    leMeas   =leMeasRA;
    leRead   =leReadRA;
  }
  else if((TButton *)Sender==btnRCalibrCalcB){
    RS       =RSB.get();
    sgTbl    =sgRCalibrB;
    leMeas   =leMeasRB;
    leRead   =leReadRB;
  }
  int ind=RS->Index;
  RS->MeasuredR[ind]=StrToFlt(leMeas->Text);
  RS->ReadoutR[ind] =StrToFlt(leRead->Text);
  if(RS->MeasuredR[ind]>0){
    RS->RelError[ind]=(RS->MeasuredR[ind]-RS->ReadoutR[ind]);
    sgTbl->Cells[1][ind+1]="    "+FloatToStrF(RS->ReadoutR[ind],ffFixed,6,2);
    sgTbl->Cells[2][ind+1]="    "+FloatToStrF(RS->MeasuredR[ind],ffFixed,6,2);
    sgTbl->Cells[3][ind+1]="    "+FloatToStrF(RS->RelError[ind],ffFixed,6,2);
    sbRB->Panels->Items[2]->Text="Значение погрешности рассчитано!";
  }
  else {
    sbRB->Panels->Items[2]->Text="Не введено измеренное значение радиуса!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintRCalibrProtA(TObject *Sender)
{//Распечатать протокол (Аттестация по радиусу) А
	String FileName;
	if (Sender==acPrintRCalibrProtA)
	{//ручное сохранение
		FileName=acPrintRCalibrProtA->Dialog->FileName;
		acPrintRCalibrProtA->Dialog->FileName="";
	}else
	{//автосейв
		FileName=strRCalibrA+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.rcprt'");
	}
  RSA->PrintProtocol(FileName,"А");
  LogPrint("Протокол аттестации датчика положения поз. А сохранен в файле \""+FileName+"\"");
  sbRB->Panels->Items[2]->Text="Протокол аттестации датчика положения поз. А сохранен в файле \""+FileName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintRCalibrProtB(TObject *Sender)
{//Распечатать протокол (Аттестация по радиусу) Б
	String FileName;
	if (Sender==acPrintRCalibrProtB)
	{//ручное сохранение
		FileName=acPrintRCalibrProtB->Dialog->FileName;
		acPrintRCalibrProtB->Dialog->FileName="";
	}else
	{//автосейв
		FileName=strRCalibrB+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.rcprt'");
	}
  RSB->PrintProtocol(FileName,"Б");
  LogPrint("Протокол аттестации датчика положения поз. Б сохранен в файле \""+FileName+"\"");
  sbRB->Panels->Items[2]->Text="Протокол аттестации датчика положения поз. Б сохранен в файле \""+FileName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnNextSertLoadBtn(TObject *Sender)
{ LCalibr    *LdCalibr; TButton *btnNext, *btnPrev;
  TStringGrid *sgLoad; TLabeledEdit *leLoadSet, *leMeasLoad;
  float *Loading; int pos;
  if((TButton *)Sender==btnNextSertLoadA){
	LdCalibr  =LdCA.get();
    btnNext   =btnNextSertLoadA;
    btnPrev   =btnPrevSertLoadA;
    sgLoad    =sgLoadSertA;
    leLoadSet =leCurrentLoadSertSetA;
    leMeasLoad=leMeasLoadSertA;
    Loading   =Loading_1;
    pos       =0;
  }
  else if((TButton *)Sender==btnNextSertLoadB){
    LdCalibr  =LdCB.get();
    btnNext   =btnNextSertLoadB;
    btnPrev   =btnPrevSertLoadB;
    sgLoad    =sgLoadSertB;
    leLoadSet =leCurrentLoadSertSetB;
    leMeasLoad=leMeasLoadSertB;
    Loading   =Loading_2;
    pos       =1;
  }
  else return;
  int Ind=LdCalibr->Index;
  int RowCnt=sgLoad->RowCount;
// перерисовка предыдущей ячейки
  if     (Ind <        9)sgLoad->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgLoad->Cells[0][Ind+1]=" "+String(Ind+1)+":";
  LdCalibr->Index++;
  btnPrev->Enabled=true;
  if(LdCalibr->Index>=RowCnt-2){
    LdCalibr->Index=RowCnt-2;
    btnNext->Enabled=false;
  }
// перерисовка текущей ячейки
  Ind=LdCalibr->Index;
  if     (Ind <        9)sgLoad->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgLoad->Cells[0][Ind+1]=" " +String(Ind+1)+":";
// прокрутка таблицы не требуется так как вся таблица на экране
  sgLoad->TopRow=1;
  leLoadSet->Text =FloatToStrF(LdCalibr->TargetLd[LdCalibr->Index],ffFixed,6,2);
  leMeasLoad->Text="0.0";
  #ifdef USEPROCESSDELAY
  leMeasLoad->ReadOnly=true;
  leMeasLoad->Color=clSilver;
  #endif
  *Loading        =LdCalibr->TargetLd[LdCalibr->Index];
  if(pos==0)LogPrint("Mode: Next load A, load="+FloatToStr(*Loading));
  if(pos==1)LogPrint("Mode: Next load B, load="+FloatToStr(*Loading));
  CheckStend();
  if(OPCConnectOK) {
	pOPC->WriteGr3(Loading);
	#ifdef USEPROCESSDELAY
	const slp=500;//500 мс для слипа
	for (int i =0; i <DELAY_TIME ; i+=slp)
	{
		Sleep(slp);
		Application->ProcessMessages();//обработка сообщений винды
	}
	leMeasLoad->Color=clWindow;
	leMeasLoad->ReadOnly=false;
	#endif
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя задать нагрузку - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrevSertLoadBtn(TObject *Sender)
{ LCalibr    *LdCalibr; TButton *btnNext, *btnPrev;
  TStringGrid *sgLoad; TLabeledEdit *leLoadSet, *leMeasLoad;
  float *Loading; int pos;
  if((TButton *)Sender==btnPrevSertLoadA){
	LdCalibr  =LdCA.get();
    btnNext   =btnNextSertLoadA;
    btnPrev   =btnPrevSertLoadA;
    sgLoad    =sgLoadSertA;
    leLoadSet =leCurrentLoadSertSetA;
    leMeasLoad=leMeasLoadSertA;
    Loading   =Loading_1;
    pos       =0;
  }
  else if((TButton *)Sender==btnPrevSertLoadB){
    LdCalibr  =LdCB.get();
    btnNext   =btnNextSertLoadB;
    btnPrev   =btnPrevSertLoadB;
    sgLoad    =sgLoadSertB;
    leLoadSet =leCurrentLoadSertSetB;
    leMeasLoad=leMeasLoadSertB;
    Loading   =Loading_2;
    pos       =1;
  }
  else return;
  int Ind=LdCalibr->Index;
  int RowCnt=sgLoad->RowCount;
// перерисовка предыдущей ячейки
  if     (Ind <        9)sgLoad->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgLoad->Cells[0][Ind+1]=" "+String(Ind+1)+":";
  LdCalibr->Index--;
  btnNext->Enabled=true;
  if(LdCalibr->Index<=0){
    LdCalibr->Index=0;
    btnPrev->Enabled=false;
  }
// перерисовка текущей ячейки
  Ind=LdCalibr->Index;
  if     (Ind <        9)sgLoad->Cells[0][Ind+1]="  "+String(Ind+1)+":";
  else if(Ind < RowCnt-1)sgLoad->Cells[0][Ind+1]=" " +String(Ind+1)+":";
// прокрутка таблицы не требуется так как вся таблица на экране
  sgLoad->TopRow=1;
  leLoadSet->Text =FloatToStrF(LdCalibr->TargetLd[LdCalibr->Index],ffFixed,6,2);
  leMeasLoad->Text="0.0";
  #ifdef USEPROCESSDELAY
  leMeasLoad->ReadOnly=true;
  leMeasLoad->Color=clSilver;
  #endif
  *Loading        =LdCalibr->TargetLd[LdCalibr->Index];
  if(pos==0)LogPrint("Mode: Next load A, load="+FloatToStr(*Loading));
  if(pos==1)LogPrint("Mode: Next load B, load="+FloatToStr(*Loading));
  CheckStend();
  if(OPCConnectOK) {
	pOPC->WriteGr3(Loading);
	#ifdef USEPROCESSDELAY
	const slp=500;//500 мс для слипа
	for (int i =0; i <DELAY_TIME ; i+=slp)
	{
		Sleep(slp);
		Application->ProcessMessages();//обработка сообщений винды
	}
	leMeasLoad->Color=clWindow;
	leMeasLoad->ReadOnly=false;
	#endif
  }
  else {
    sbRB->Panels->Items[2]->Text="Нельзя задать нагрузку - нет соединения со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadSertTableClear(TObject *Sender)
{  if((TButton *)Sender==btnLoadSertClearTableA){
    LdCA->Clear();
    DesignLoadSertAPanel();
    sbRB->Panels->Items[2]->Text="Таблица калибровки тензодатчика поз. А очищена!";
  }
  else if((TButton *)Sender==btnLoadSertClearTableB){
    LdCB->Clear();
    DesignLoadSertBPanel();
    sbRB->Panels->Items[2]->Text="Таблица калибровки тензодатчика поз. Б очищена!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadSertCalc(TObject *Sender)
{ LCalibr *LdCalibr;
  TStringGrid *sgLoad; TLabeledEdit *leMeasLoad, *leReadoutLoad;
  if((TButton *)Sender==btnLoadSertCalcA){
	LdCalibr     =LdCA.get();
    sgLoad       =sgLoadSertA;
    leReadoutLoad=leReadLoadSertA;
    leMeasLoad   =leMeasLoadSertA;
  }
  else if((TButton *)Sender==btnLoadSertCalcB){
    LdCalibr     =LdCB.get();
    sgLoad       =sgLoadSertB;
    leReadoutLoad=leReadLoadSertB;
    leMeasLoad   =leMeasLoadSertB;
  }
  else return;
  int ind=LdCalibr->Index;
//  leReadoutLoad->Text=FloatToStrF(LdCalibr->TargetLd[ind]+0.25,ffFixed,6,2); // DEBUG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  LdCalibr->MeasuredLd[ind]=StrToFlt(leMeasLoad->Text);
  LdCalibr->ReadoutLd[ind] =StrToFlt(leReadoutLoad->Text);
  if(LdCalibr->MeasuredLd[ind]>0 && LdCalibr->ReadoutLd[ind]>0){
    LdCalibr->KA[ind]=(LdCalibr->MeasuredLd[ind]/LdCalibr->ReadoutLd[ind]);
	sgLoad->Cells[2][ind+1]="    "+FloatToStrF(LdCalibr->ReadoutLd[ind],ffFixed,6,2);
	sgLoad->Cells[3][ind+1]="    "+FloatToStrF(LdCalibr->MeasuredLd[ind],ffFixed,6,2);
	sgLoad->Cells[4][ind+1]="    "+FloatToStrF(LdCalibr->KA[ind],ffFixed,8,5);
	sbRB->Panels->Items[2]->Text="Значение коэффициента рассчитано!";
  }
  else if(LdCalibr->MeasuredLd[ind]==0){
	sbRB->Panels->Items[2]->Text="Не введено измеренное значение нагрузки!";
  }
  else if(LdCalibr->ReadoutLd[ind]==0) {
    sbRB->Panels->Items[2]->Text="Значение нагрузки на мониторе равно 0!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadSertToPLC(TObject *Sender)
{ CheckStend();
  if((TButton *)Sender==btnLoadSertAToPLC){

	if(OPCConnectOK) {
      OPCControlPause(tReadCycleTimer);
//      pOPC->ReadGr12();                         // прочитали коэффициенты А из DB71
//      LdCA->LKRead(A1);                         // сохранили прочитанные коэффициенты в ReadKA
//      LdCA->LKMult();                           // перемножили прочитанные ReadKA и расчитанные KA
	  ReadLSertTable(LdCA.get(),sgLoadSertA);         // прочитали коэффициенты KA из таблицы
      LdCA->LKSetting(A1);                      // сохранили итоговые КА в А1
      pOPC->WriteGr12();                        // записали А1 в DB71
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Коэффициенты калибровки тензодатчика по поз. А загружены в контроллер!";
    }
    else {
      sbRB->Panels->Items[2]->Text="Нельзя загрузить коэффициенты - нет связи со стендом!";
    }
  }
  else if((TButton *)Sender==btnLoadSertBToPLC){
    if(OPCConnectOK) {
      OPCControlPause(tReadCycleTimer);
//      pOPC->ReadGr13();                         // прочитали коэффициенты А из DB70
//      LdCB->LKRead(A2);                         // сохранили прочитанные коэффициенты в ReadKA
//      LdCB->LKMult();                           // перемножили прочитанные ReadKA и расчитанные KA
      ReadLSertTable(LdCB.get(),sgLoadSertB);         // прочитали коэффициенты KA из таблицы
      LdCB->LKSetting(A2);                      // сохранили итоговые КА в А1
      pOPC->WriteGr13();                        // записали А2 в DB70
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Коэффициенты калибровки тензодатчика по поз. Б загружены в контроллер!";
    }
    else {
      sbRB->Panels->Items[2]->Text="Нельзя загрузить коэффициенты - нет связи со стендом!";
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintLoadSertProtA(TObject *Sender)
{//Распечатать протокол (калибровка тезодатчиков) А
	String FileName;
	if (Sender==acLoadSertPrintProtA)
	{//ручное сохранение
		FileName=acLoadSertPrintProtA->Dialog->FileName;
		acLoadSertPrintProtA->Dialog->FileName="";
	}else
	{//автосейв
		FileName=strSertPrintProtA+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.tcprt'");
	}
  LdCA->PrintProtocol(FileName,"А");
  LogPrint("Протокол калибровки тензодатчика поз. А сохранен в файле \""+FileName+"\"");
  sbRB->Panels->Items[2]->Text="Протокол калибровки тензодатчика поз. А сохранен в файле \""+FileName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintLoadSertProtB(TObject *Sender)
{//Распечатать протокол (калибровка тезодатчиков) Б
	String FileName;
	if (Sender==acLoadSertPrintProtB)
	{//ручное сохранение
		FileName=acLoadSertPrintProtB->Dialog->FileName;
		acLoadSertPrintProtB->Dialog->FileName="";
	}else
	{//автосейв
		FileName=strSertPrintProtB+Now().FormatString("yyyy_mm_dd_hh_nn_ss'.tcprt'");
	}
  LdCB->PrintProtocol(FileName,"Б");
  LogPrint("Протокол калибровки тензодатчика поз. Б сохранен в файле \""+FileName+"\"");
  sbRB->Panels->Items[2]->Text="Протокол калибровки тензодатчика поз. Б сохранен в файле \""+FileName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadSpeedCoefToPLC(TObject *Sender)
{
  *CorrASetSpeed =StrToFlt(leSetSpeedCoef->Text);
  *CorrAMeasSpeed=StrToFlt(leMeasSpeedCoef->Text);
  LogPrint("Коэффициент корректировки задания скорости: "+FloatToStrF(*CorrASetSpeed,ffFixed,7,4),clAqua);
  LogPrint("Коэффициент корректировки измерения скорости: "+FloatToStrF(*CorrAMeasSpeed,ffFixed,7,4),clAqua);
  CheckStend();
  if(OPCConnectOK) {
      OPCControlPause(tReadCycleTimer);
      pOPC->WriteGr3(CorrASetSpeed);
      pOPC->WriteGr3(CorrAMeasSpeed);
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Коэффициенты корректировки скорости загружены в контроллер!";
    }
    else {
      sbRB->Panels->Items[2]->Text="Нельзя загрузить коэффициенты - нет связи со стендом!";
    }

}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnLSertCoefReset(TObject *Sender)
{
  int res=Application->MessageBox(L"Сброс коэффициентов калибровки (результаты предидущей калибровки будут потеряны)!",
								   L"Подтвердите сброс!",
								   MB_YESNO+MB_ICONQUESTION+MB_DEFBUTTON2);
  if(res==IDNO)return;
  CheckStend();
  if((TButton *)Sender==btnResetCalibrCoeffA){
	if(OPCConnectOK) {
      OPCControlPause(tReadCycleTimer);
      ResetKA(A1);                              // сбросили коэффициенты А1 в единичку
      pOPC->WriteGr12();                        // записали А1 в DB71
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Коэффициенты калибровки тензодатчика по поз. А в контроллере сброшены!";
    }
    else {
      sbRB->Panels->Items[2]->Text="Нельзя загрузить коэффициенты - нет связи со стендом!";
    }
  }
  else if((TButton *)Sender==btnResetCalibrCoeffB){
    if(OPCConnectOK) {
      OPCControlPause(tReadCycleTimer);
      ResetKA(A2);                              // сбросили коэффициенты А2 в единичку
      pOPC->WriteGr13();                        // записали А2 в DB70
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Коэффициенты калибровки тензодатчика по поз. Б в контроллере сброшены!";
    }
    else {
      sbRB->Panels->Items[2]->Text="Нельзя загрузить коэффициенты - нет связи со стендом!";
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnSGSelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{ int EditedCol;
  if((TStringGrid*) Sender==sgLoadSertA){
    EditedCol=4;
//    LogPrint("sgLoadSertA, ACol="+String(ACol),clLime);
  }
  else if((TStringGrid*) Sender==sgLoadSertB){
    EditedCol=4;
//    LogPrint("sgLoadSertB, ACol="+String(ACol),clLime);
  }
  else return;
  if(ACol==EditedCol){
    ((TStringGrid*) Sender)->Options << goEditing;
//    LogPrint("ACol==EditedCol!",clLime);
  }
  else               {
//    LogPrint("ACol!=EditedCol!",clRed);
    ((TStringGrid*) Sender)->Options >> goEditing;
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnTLimitsCalc(TObject *Sender)
{ TSert *TS;
//  TStringGrid *sgTemp;
  TEdit *edLowLimit, *edUpLimit;
  if((TButton *)Sender==btnTLimitsCalcA){
	TS        =TSA.get();
//    sgTemp    =sgTCalibrA;
    edLowLimit=edCalcLowLimitA;
    edUpLimit =edCalcUpLimitA;
  }
  else if((TButton *)Sender==btnTLimitsCalcB){
    TS        =TSB.get();
//    sgTemp    =sgTCalibrB;
	edLowLimit=edCalcLowLimitB;
    edUpLimit =edCalcUpLimitB;
  }
  else return;
  int NT=0;
  while(TS->ReadoutT[NT]!=0.0)NT++;
//  NT--;
  LogPrint("Number of non zero rows is "+String(NT),clLime);
  if(NT<=1) {
    LogPrint("Cлишком мало данных для расчета - нужно хотя бы 2 точки!",clRed);
    return;
  }
  float A,B,LowLim,UpLim;
  LeastSquares(TS->MeasuredT,TS->ReadoutT,NT,A,B);
  LowLim=A*LOWTLIM+B;
  UpLim=A*UPPERTLIM+B;
  LogPrint("A="+FloatToStrF(A,ffFixed,6,2)+", B="+FloatToStrF(B,ffFixed,6,2),clLime);
  edLowLimit->Text=FloatToStrF(LowLim,ffFixed,6,2);
  edUpLimit->Text =FloatToStrF(UpLim,ffFixed,6,2);
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnTLimitsLoadToPLC(TObject *Sender)
{ int pos;
  float *TempLowLimit, *TempUpLimit;
  TEdit *edLowLimit, *edUpLimit;
  if((TButton *)Sender==btnLoadTLimitsA){
	edLowLimit=edLoadedLowLimitA;
    edUpLimit =edLoadedUpLimitA;
	TempLowLimit=Temp1LowLimit;
    TempUpLimit =Temp1UpLimit;
    pos=0;
  }
  else if((TButton *)Sender==btnLoadTLimitsB){
	edLowLimit=edLoadedLowLimitB;
    edUpLimit =edLoadedUpLimitB;
	TempLowLimit=Temp2LowLimit;
    TempUpLimit =Temp2UpLimit;
    pos=1;
  }
  else return;
  *TempLowLimit=StrToFlt(edLowLimit->Text);
  *TempUpLimit =StrToFlt(edUpLimit->Text);
  CheckStend();
  if(OPCConnectOK){
    OPCControlPause(tReadCycleTimer);
	pOPC->WriteGr3(TempLowLimit);                        // записали TLow в DB10
    pOPC->WriteGr3(TempUpLimit);                         // записали TUpper в DB10
    OPCControlResume(tReadCycleTimer);
    if(pos==0)sbRB->Panels->Items[2]->Text="Пределы измерения температуры по поз. А загружены в контроллер!";
    else      sbRB->Panels->Items[2]->Text="Пределы измерения температуры по поз. Б загружены в контроллер!";
  }
  else {
      sbRB->Panels->Items[2]->Text="Нельзя загрузить пределы измерения температуры - нет связи со стендом!";
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::ReadLSertTable(                  // считывание значений из таблицы в массив
                                      LCalibr *LC,
                                      TStringGrid *Table)
{
  for (int i =0; i < LDCQTY; i++) {
	String tmp=Table->Cells[4][i+1];
	if (DecimalSeparator=='.')
	{
		tmp=Replace(tmp,",",String(DecimalSeparator));
	}else
	{
		tmp=Replace(tmp,".",String(DecimalSeparator));
	}
	LC->KA[i]=StrToFlt(tmp);
  }
}
//---- End of ReadLSertTable ------------------------------------------------

void __fastcall TmfRB::OnUploadLSertFmPLC(TObject *Sender)
{ CheckStend();
  if((TButton *)Sender==btnUploadSertAFmPLC){
	if(OPCConnectOK) {
      OPCControlPause(tReadCycleTimer);
      pOPC->ReadGr12();                         // прочитали коэффициенты А из DB71
      LdCA->LKRead(A1);                         // сохранили прочитанные коэффициенты в ReadKA
      for (int i =0; i < LDCQTY; i++) {         // записали коэффициенты в таблицу
		sgLoadSertA->Cells[4][i+1]=FloatToStrF(LdCA->/*Read*/KA[i],ffFixed,8,5);
      }
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Коэффициенты калибровки тензодатчика по поз. А загружены из контроллера!";
    }
    else {
      sbRB->Panels->Items[2]->Text="Нельзя прочитать коэффициенты - нет связи со стендом!";
    }
  }
  else if((TButton *)Sender==btnUploadSertBFmPLC){
	if(OPCConnectOK) {
      OPCControlPause(tReadCycleTimer);
      pOPC->ReadGr13();                         // прочитали коэффициенты А из DB70
	  LdCB->LKRead(A2);                         // сохранили прочитанные коэффициенты в ReadKA
      for (int i =0; i < LDCQTY; i++) {         // записали коэффициенты в таблицу
        sgLoadSertB->Cells[4][i+1]=FloatToStrF(LdCB->/*Read*/KA[i],ffFixed,8,5);
      }
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Коэффициенты калибровки тензодатчика по поз. Б загружены из контроллера!";
    }
    else {
      sbRB->Panels->Items[2]->Text="Нельзя прочитать коэффициенты - нет связи со стендом!";
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnRShiftLoadToPLC(TObject *Sender)
{ float shift;
  CheckStend();
  if((TButton *)Sender==btnRShiftALoadToPLC){
    if(OPCConnectOK) {
      OPCControlPause(tReadCycleTimer);
      LogPrintF(LogFName(),"Текущие значения пределов радиусов для поз. А:");
      LogPrintF(LogFName(),"Нижний: "+FloatToStrF(*Rad1LowLimit,ffFixed,7,2)+", верхний: "+FloatToStrF(*Rad1UpLimit,ffFixed,7,2));
      shift=StrToFlt(leRShiftA->Text);
      *Rad1LowLimit+=shift; *Rad1UpLimit+=shift;
      LogPrintF(LogFName(),"Новые значения пределов радиусов для поз. А:");
      LogPrintF(LogFName(),"Нижний: "+FloatToStrF(*Rad1LowLimit,ffFixed,7,2)+", верхний: "+FloatToStrF(*Rad1UpLimit,ffFixed,7,2));
      pOPC->WriteGr3(Rad1LowLimit);
      pOPC->WriteGr3(Rad1UpLimit);
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Новые значения пределов радиуса по поз. А загружены в контроллер!";
    }
    else {
      sbRB->Panels->Items[2]->Text="Нельзя загрузить смещения - нет связи со стендом!";
    }
  }
  else if((TButton *)Sender==btnRShiftBLoadToPLC){
    if(OPCConnectOK) {
      LogPrintF(LogFName(),"Текущие значения пределов радиусов для поз. Б:");
      LogPrintF(LogFName(),"Нижний: "+FloatToStrF(*Rad2LowLimit,ffFixed,7,2)+", верхний: "+FloatToStrF(*Rad2UpLimit,ffFixed,7,2));
      shift=StrToFlt(leRShiftB->Text);
      *Rad2LowLimit+=shift; *Rad2UpLimit+=shift;
      LogPrintF(LogFName(),"Новые значения пределов радиусов для поз. Б:");
      LogPrintF(LogFName(),"Нижний: "+FloatToStrF(*Rad2LowLimit,ffFixed,7,2)+", верхний: "+FloatToStrF(*Rad2UpLimit,ffFixed,7,2));
      pOPC->WriteGr3(Rad2LowLimit);
      pOPC->WriteGr3(Rad2UpLimit);
      OPCControlResume(tReadCycleTimer);
      sbRB->Panels->Items[2]->Text="Новые значения пределов радиуса по поз. Б загружены в контроллер!";
    }
    else {
      sbRB->Panels->Items[2]->Text="Нельзя загрузить смещения - нет связи со стендом!";
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintProtocol(TObject *Sender)
{
  if((TButton *)Sender==btnPrintTestResPosA){
    sbRB->Panels->Items[2]->Text="Печать протокола испытаний по поз. А!";
	TyreA->PrintProtocol(pProtPrt,"А");
    sbRB->Panels->Items[2]->Text="Протокол испытаний по поз. А выведен на принтер!";
    LogPrintF(LogFName(),"Протокол испытаний по поз. А выведен на принтер!",clSkyBlue);
  }
  if((TButton *)Sender==btnPrintTestResPosB){
    sbRB->Panels->Items[2]->Text="Печать протокола испытаний по поз. Б!";
    TyreB->PrintProtocol(pProtPrt,"Б");
    sbRB->Panels->Items[2]->Text="Протокол испытаний по поз. Б выведен на принтер!";
    LogPrintF(LogFName(),"Протокол испытаний по поз. Б выведен на принтер!",clSkyBlue);
  }
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrinterFontSelect(TObject *Sender)
{
  if(PrinterFontDialog->Execute()){
    pProtPrt->Canvas->Font->Assign(PrinterFontDialog->Font);
    LogPrint("Выбран шрифт \""+PrinterFontDialog->Font->Name+"\"",clMoneyGreen);
  }

}
//---------------------------------------------------------------------------

void __fastcall TmfRB::acCD_9904SettingsExecute(TObject *Sender)
{
	if (cd_9904)
	{
		if (CD_9904Thread)
		{
			TerminateThread(CD_9904Thread,0);
		}
		cd_9904->Set_Settings();
		if (cd_9904->Sensor())
		{
			CD_9904Thread=CreateThread(NULL,0,ListenCD9904,0,0,NULL);//включается прослушка
		}else
		{
        	StendConnection=false;
		}
	}
}
void __fastcall TmfRB::acSettingsManagmentExecute(TObject *Sender)
{
	TAppManagment *wnd=new TAppManagment(this,DB);
	wnd->ShowModal();
	GetSettings();
	delete wnd;
}
void			TmfRB::GetSettings(void)
{
	AutoSave=			TAppManagment::Get_param(L"File_Save_Mode",DB)=="Auto"?true:false;
	strDistProg=		TAppManagment::Get_param(L"Sprog",DB);
	strTimeProg=		TAppManagment::Get_param(L"Tprog",DB);
	strProtA=			TAppManagment::Get_param(L"TestResPosA",DB);
	strProtB=			TAppManagment::Get_param(L"TestResPosB",DB);
	strTitleProt=		TAppManagment::Get_param(L"ProtTtl",DB);

	strLoadCalibrA=     TAppManagment::Get_param(L"LoadCalibrTableA",DB);
	strLoadCalibrB=		TAppManagment::Get_param(L"LoadCalibrTableB",DB);
	strTCalibrA=        TAppManagment::Get_param(L"TCalibrTableA",DB);
	strTCalibrB=		TAppManagment::Get_param(L"TCalibrTableB",DB);
	strRCalibrA=        TAppManagment::Get_param(L"RCalibrTableA",DB);
	strRCalibrB=		TAppManagment::Get_param(L"RCalibrTableB",DB);
	strSpdCalibr=		TAppManagment::Get_param(L"SpdCalibrTable",DB);

	strSertPrintProtA=	TAppManagment::Get_param(L"LoadSertPrintProtA",DB);
	strSertPrintProtB=	TAppManagment::Get_param(L"LoadSertPrintProtB",DB);
	//проверка наличия директорий

	strDistProg=		DirectoryExists(strDistProg)?strDistProg:String();
	strTimeProg=		DirectoryExists(strTimeProg)?strTimeProg:String();
	strProtA=			DirectoryExists(strProtA)?strProtA:String();
	strProtB=			DirectoryExists(strProtB)?strProtB:String();
	strTitleProt=		DirectoryExists(strTitleProt)?strTitleProt:String();
	strLoadCalibrA=		DirectoryExists(strLoadCalibrA)?strLoadCalibrA:String();
	strLoadCalibrB=		DirectoryExists(strLoadCalibrB)?strLoadCalibrB:String();
	strTCalibrA=		DirectoryExists(strTCalibrA)?strTCalibrA:String();
	strTCalibrB=		DirectoryExists(strTCalibrB)?strTCalibrB:String();
	strRCalibrA=		DirectoryExists(strRCalibrA)?strRCalibrA:String();
	strRCalibrB=		DirectoryExists(strRCalibrB)?strRCalibrB:String();
	strSpdCalibr=		DirectoryExists(strSpdCalibr)?strSpdCalibr:String();
	strSertPrintProtA=	DirectoryExists(strSertPrintProtA)?strSertPrintProtA:String();
	strSertPrintProtB=	DirectoryExists(strSertPrintProtB)?strSertPrintProtB:String();

	/*переподключение функций по настройкам*/
	if (AutoSave)
	{
		//замена в меню

		amRB->ActionBars->operator [](0)->Items->operator [](0)->Items->operator [](1)->Action=
			strDistProg!=""?(TCustomAction *)_acTProgFileSaveAs:(TCustomAction *)acTProgFileSaveAs;

		amRB->ActionBars->operator [](0)->Items->operator [](0)->Items->operator [](3)->Action=
			strDistProg!=""?(TCustomAction *)_acSProgFileSaveAs:(TCustomAction *)acSProgFileSaveAs;

		amRB->ActionBars->operator [](0)->Items->operator [](0)->Items->operator [](5)->Action=
			strTitleProt!=""?(TCustomAction *)_acProtTitleFileSaveAs:(TCustomAction *)acProtTitleFileSaveAs;

		//замена на элементах управления если указан путь
		//btnSaveSProgToFile->Action		=strDistProg		!=""?(TCustomAction *)_acSProgFileSaveAs		:(TCustomAction *)acSProgFileSaveAs;
		//btnSaveTProgToFile->Action		=strTimeProg		!=""?(TCustomAction *)_acTProgFileSaveAs		:(TCustomAction *)acTProgFileSaveAs;
		//btnSaveProtTtlToFile->Action	=strTitleProt		!=""?(TCustomAction *)_acProtTitleFileSaveAs	:(TCustomAction *)acProtTitleFileSaveAs;
		btnSaveTestResPosAToFile->Action=strProtA			!=""?(TCustomAction *)_acPrintProtPosAToFile	:(TCustomAction *)acPrintProtPosAToFile;
		btnSaveTestResPosBToFile->Action=strProtB			!=""?(TCustomAction *)_acPrintProtPosBToFile	:(TCustomAction *)acPrintProtPosBToFile;
		btnSpdCalibrTablePrint->Action	=strSpdCalibr		!=""?(TCustomAction *)_acPrintSpdCalibrProt		:(TCustomAction *)acPrintSpdCalibrProt;
		btnLoadCalibrTableAPrint->Action=strLoadCalibrA		!=""?(TCustomAction *)_acPrintLoadCalibrProtA	:(TCustomAction *)acPrintLoadCalibrProtA;
		btnLoadCalibrTableBPrint->Action=strLoadCalibrB		!=""?(TCustomAction *)_acPrintLoadCalibrProtB	:(TCustomAction *)acPrintLoadCalibrProtB;
		btnTCalibrTableAPrint->Action	=strTCalibrA		!=""?(TCustomAction *)_acPrintTCalibrProtA		:(TCustomAction *)acPrintTCalibrProtA;
		btnTCalibrTableBPrint->Action	=strTCalibrB		!=""?(TCustomAction *)_acPrintTCalibrProtB		:(TCustomAction *)acPrintTCalibrProtB;
		btnRCalibrTableAPrint->Action	=strRCalibrA		!=""?(TCustomAction *)_acPrintRCalibrProtA		:(TCustomAction *)acPrintRCalibrProtA;
		btnRCalibrTableBPrint->Action	=strRCalibrB		!=""?(TCustomAction *)_acPrintRCalibrProtB		:(TCustomAction *)acPrintRCalibrProtB;
		btnLoadSertPrintProtA->Action	=strSertPrintProtA	!=""?(TCustomAction *)_acLoadSertPrintProtA		:(TCustomAction *)acLoadSertPrintProtA;
		btnLoadSertPrintProtB->Action	=strSertPrintProtB	!=""?(TCustomAction *)_acLoadSertPrintProtB		:(TCustomAction *)acLoadSertPrintProtB;

	}else
	{
		//замена в меню
		amRB->ActionBars->operator [](0)->Items->operator [](0)->Items->operator [](1)->Action=acTProgFileSaveAs;
		amRB->ActionBars->operator [](0)->Items->operator [](0)->Items->operator [](3)->Action=acSProgFileSaveAs;
		amRB->ActionBars->operator [](0)->Items->operator [](0)->Items->operator [](5)->Action=acProtTitleFileSaveAs;

		//замена на элементах управления
		//btnSaveSProgToFile->Action		=acSProgFileSaveAs;
		//btnSaveTProgToFile->Action		=acTProgFileSaveAs;
	    //btnSaveProtTtlToFile->Action	=acProtTitleFileSaveAs;
		btnSaveTestResPosAToFile->Action=acPrintProtPosAToFile;
		btnSaveTestResPosBToFile->Action=acPrintProtPosBToFile;
		btnSpdCalibrTablePrint->Action	=acPrintSpdCalibrProt;
		btnLoadCalibrTableAPrint->Action=acPrintLoadCalibrProtA;
		btnLoadCalibrTableBPrint->Action=acPrintLoadCalibrProtB;
		btnTCalibrTableAPrint->Action	=acPrintTCalibrProtA;
		btnTCalibrTableBPrint->Action	=acPrintTCalibrProtB;
		btnRCalibrTableAPrint->Action	=acPrintRCalibrProtA;
		btnRCalibrTableBPrint->Action	=acPrintRCalibrProtB;
		btnLoadSertPrintProtA->Action	=acLoadSertPrintProtA;
		btnLoadSertPrintProtB->Action	=acLoadSertPrintProtB;
	 }
	//установка директорий по умолчанию
		//диалоги сохранения
	acSProgFileSaveAs->		Dialog->InitialDir =strDistProg;
	acTProgFileSaveAs->		Dialog->InitialDir =strTimeProg;
	acProtTitleFileSaveAs->	Dialog->InitialDir =strTitleProt;
	acPrintProtPosAToFile->	Dialog->InitialDir =strProtA;
	acPrintProtPosBToFile->	Dialog->InitialDir =strProtB;
	acPrintSpdCalibrProt->	Dialog->InitialDir =strSpdCalibr;
	acPrintLoadCalibrProtA->Dialog->InitialDir =strLoadCalibrA;
	acPrintLoadCalibrProtB->Dialog->InitialDir =strLoadCalibrB;
	acPrintTCalibrProtA->	Dialog->InitialDir =strTCalibrA;
	acPrintTCalibrProtB->	Dialog->InitialDir =strTCalibrB;
	acPrintRCalibrProtA->	Dialog->InitialDir =strRCalibrA;
	acPrintRCalibrProtB->	Dialog->InitialDir =strRCalibrB;
	acLoadSertPrintProtA->	Dialog->InitialDir =strSertPrintProtA;
	acLoadSertPrintProtB->	Dialog->InitialDir =strSertPrintProtB;

		//загрузка
	acTProgFileOpen->		Dialog->InitialDir =strTimeProg;//Загрузить из файла программу по времени
	acSProgFileOpen->		Dialog->InitialDir =strDistProg;//Загрузить из файла программу по пути
	acProtTitleFileOpen->	Dialog->InitialDir =strTitleProt;//Загрузить из файла заголовок протокола

}
void			TmfRB::SetIndication(TEdit *Indicator,bool state)
{
	Indicator->Color=state?clLime:clRed;
}

//задание параметров по Enter
void __fastcall TmfRB::leSetLoad1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==13)
	{
		CheckStend();
		if(OPCConnectOK)
		{
			if(*ManualMode1)
			{
				double t=leSetLoad1->Text.Trim().ToDouble();
				if (CheckLoad(t))
				{
					*Loading_1=t;
					tbCurrentLoad1->SelEnd  =tbCurrentLoad1->Max-int(*Loading_1);
	  				tbCurrentLoad1->SelStart=tbCurrentLoad1->Max-int(*Loading_1);
					OPCControlPause(tReadCycleTimer);
					pOPC->WriteGr3(Loading_1);
					OPCControlResume(tReadCycleTimer);
					tsManual->SetFocus();
				}else
				{
                    MessageBox(Handle,_T("Значение нагрузки должно быть в пределах от 0 до 115"),_T("Ошибка"),MB_ICONERROR|MB_OK);
				}
			}
		}
	}
}
void __fastcall TmfRB::leSetLoad2KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==13)
	{
		CheckStend();
		if(OPCConnectOK)
		{
			if(*ManualMode2)
			{
				double t=leSetLoad2->Text.Trim().ToDouble();
				if (CheckLoad(t))
				{
					*Loading_2=t;
					tbCurrentLoad2->SelEnd  =tbCurrentLoad2->Max-int(*Loading_2);
	  				tbCurrentLoad2->SelStart=tbCurrentLoad2->Max-int(*Loading_2);
					OPCControlPause(tReadCycleTimer);
					pOPC->WriteGr3(Loading_2);
					OPCControlResume(tReadCycleTimer);
					tsManual->SetFocus();
				}else
				{
                    MessageBox(Handle,_T("Значение нагрузки должно быть в пределах от 0 до 115"),_T("Ошибка"),MB_ICONERROR|MB_OK);
				}
			}
		}
	}
}
void __fastcall TmfRB::leSetDrumSpeedKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==13)
	{
		CheckStend();
		if(OPCConnectOK&&*ManualMode1 && *ManualMode2)
		{
			*DrumOn=true; *DrumOff=false;
			if(pcRB->ActivePage==tsManual)
			{
				double t=leSetDrumSpeed->Text.Trim().ToDouble();
				if (CheckSpeed(t))
				{
					*DrumSpeed=t;
					tbCurrentDrumSpeed->SelEnd  =tbCurrentDrumSpeed->Max-int(*DrumSpeed);
					tbCurrentDrumSpeed->SelStart=tbCurrentDrumSpeed->Max-int(*DrumSpeed);
					OPCControlPause(tReadCycleTimer);
					pOPC->WriteGr3(DrumSpeed);
					OPCControlResume(tReadCycleTimer);
                    tsManual->SetFocus();
				}else
				{
					MessageBox(Handle,_T("Значение скорости должно быть в пределах от 0 до 170"),_T("Ошибка"),MB_ICONERROR|MB_OK);
					return;
				}
			}
		}
	}
}
//сохранение имени программы в базе
void			TmfRB::SetCurrProgA(String name)
{
	TAppManagment::Set_Param(L"ProgNameA",name,DB);
}
String			TmfRB::GetCurrProgA(void)
{
	return TAppManagment::Get_param(L"ProgNameA",DB);
}
void			TmfRB::SetCurrProgB(String name)
{
	TAppManagment::Set_Param(L"ProgNameB",name,DB);
}
String			TmfRB::GetCurrProgB(void)
{
	return TAppManagment::Get_param(L"ProgNameB",DB);
}
void			TmfRB::UpdateProgData(void) //обновление данных по программе из контроллера
{
	pOPC->ReadGr3();
	TyreA->TotalS           =*S_end_cycle_1;
	TyreA->TotalTime        =*T_end_cycle_1;
	TyreA->TestMode         =*type_cycle_1;
	TyreA->StepsNo          =*StepsQty1;
	TyreA->PollsNo          =*PollsQty1;
	TyreB->TotalS           =*S_end_cycle_2;
	TyreB->TotalTime        =*T_end_cycle_2;
	TyreB->TestMode         =*type_cycle_2;
	TyreB->StepsNo          =*StepsQty2;
	TyreB->PollsNo          =*PollsQty2;
}
// аварийные установки
void __fastcall TmfRB::btEmSettingsClick(TObject *Sender)
{
	CheckStend();
	if (!OPCConnectOK) {return;}

	bool err=false,value=false;
	//проверка значения
	try
	{
		double t=leEmMaxLoad_1R->Text.Trim().ToDouble();
		if (CheckLoad(t))
		{
			*max_load_1=t;
			pOPC->WriteGr1(max_load_1);
			leEmMaxLoad_1R->Color=clLime;
		}else
		{
			leEmMaxLoad_1R->Color=clRed;
			value=true;
		}
	} catch (...)
	{
		err=true;
		leEmMaxLoad_1R->Color=clRed;
	}
	//проверка значения
	try
	{
		double t=leEmMaxLoad_2R->Text.Trim().ToDouble();
		if (CheckLoad(t))
		{
			*max_load_2=t;
			pOPC->WriteGr1(max_load_2);
			leEmMaxLoad_2R->Color=clLime;
		}else
		{
			leEmMaxLoad_2R->Color=clRed;
			value=true;
		}
	} catch (...)
	{
		leEmMaxLoad_2R->Color=clRed;
		err=true;
	}
	//проверка значения
	try
	{
		double t=leEmMaxSpeedR->Text.Trim().ToDouble();
		if (CheckSpeed(t))
		{
			*max_speed=t;
			pOPC->WriteGr1(max_speed);
			leEmMaxSpeedR->Color=clLime;
		}else
		{
			leEmMaxSpeedR->Color=clRed;
			value=true;
		}
	} catch (...)
	{
		leEmMaxSpeedR->Color=clRed;
		err=true;
	}
		//проверка значения
	try
	{
		double t=leEmMinSpeedR->Text.Trim().ToDouble();
		if (CheckSpeed(t))
		{
			*min_speed=t;
			pOPC->WriteGr1(min_speed);
			leEmMinSpeedR->Color=clLime;
		}else
		{
			leEmMinSpeedR->Color=clRed;
			value=true;
		}
	} catch (...)
	{
		leEmMinSpeedR->Color=clRed;
		err=true;
	}
	//проверка значения
	try
	{
		double t=leEmMinLoad_1R->Text.Trim().ToDouble();
		if (CheckLoad(t))
		{
			*min_load_1=t;
			pOPC->WriteGr1(min_load_1);
			leEmMinLoad_1R->Color=clLime;
		}else
		{
			leEmMinLoad_1R->Color=clRed;
			value=true;
		}
	} catch (...)
	{
		leEmMinLoad_1R->Color=clRed;
		err=true;
	}
	//проверка значения
	try
	{
		double t=leEmMinLoad_2R->Text.Trim().ToDouble();
		if (CheckLoad(t))
		{
			*min_load_2=t;
			pOPC->WriteGr1(min_load_2);
			leEmMinLoad_2R->Color=clLime;
		}else
		{
			leEmMinLoad_2R->Color=clRed;
			value=true;
		}
	} catch (...)
	{
		leEmMinLoad_2R->Color=clRed;
		err=true;
	}

    //проверка значения
    try
    {
        double t=leEmMinTemp_1R->Text.Trim().ToDouble();
        *min_temp_1=t;
        pOPC->WriteGr1(min_temp_1);
        leEmMinTemp_1R->Color=clLime;
    } catch (...)
    {
        leEmMinTemp_1R->Color=clRed;
    }
    //проверка значения
    try
    {
        double t=leEmMaxTemp_1R->Text.Trim().ToDouble();
        *max_temp_1=t;
        pOPC->WriteGr1(max_temp_1);
        leEmMaxTemp_1R->Color=clLime;
    } catch (...)
    {
        leEmMaxTemp_1R->Color=clRed;
    }
    //проверка значения
    try
    {
        double t=leEmMinTemp_2R->Text.Trim().ToDouble();
        *min_temp_2=t;
        pOPC->WriteGr1(min_temp_2);
        leEmMinTemp_2R->Color=clLime;
    } catch (...)
    {
        leEmMinTemp_2R->Color=clRed;
    }
    //проверка значения
    try
    {
        double t=leEmMaxTemp_2R->Text.Trim().ToDouble();
        *max_temp_2=t;
        pOPC->WriteGr1(max_temp_2);
        leEmMaxTemp_2R->Color=clLime;
    } catch (...)
    {
        leEmMaxTemp_2R->Color=clRed;
    }


	if (err)
	{
		MessageBox(Handle,_T("Введено не корректное значение"),_T("Ошибка"),MB_ICONERROR|MB_OK);
	}
	if (value)
	{
        MessageBox(Handle,_T("Значение нагрузки должно быть в пределах от 0 до 115\n Значение скорости должно быть в пределах от 0 до 170"),_T("Ошибка"),MB_ICONERROR|MB_OK);
	}
}
void __fastcall TmfRB::leEmMinLoad_1RKeyPress(TObject *Sender, wchar_t &Key)
{
	TLabeledEdit *lb=(TLabeledEdit *)Sender;
	lb->Color=clWindow;
}
//---------------------------------------------------------------------------
//проверки вводимых данных
bool			TmfRB::CheckLoad(double load)
{
	return load>=MIN_LOAD&&load<=MAX_LOAD;
}
bool            TmfRB::CheckSpeed(double Speed)
{
	return Speed>=MIN_SPEED&&Speed<=MAX_SPEED;
}
bool			TmfRB::CheckTime(int Time)
{
	return Time>0;
}
bool			TmfRB::CheckDistance(double Dist)
{
	return Dist>0;
}

bool 	TmfRB::CheckProgLoad(TStringGrid *sg,int col,double min_val)
{
	for (int i = 1,sz=sg->RowCount; i < sz; ++i)
	{
		if (sg->Cells[col][i].Length()&&sg->Cells[col][i].ToDouble()<min_val)
		{
			String err="Недопустимо низкое значение нагрузки в строке "+String(i);
			MessageBoxW(Handle,err.w_str(),L"Недопустимо низкое значение нагрузки",MB_OK|MB_ICONERROR|MB_DEFBUTTON1);
			return false;
		}
	}
	return true;
}

//---------------------------------------------------------------------------

void __fastcall TmfRB::btnResetResPosAClick(TObject *Sender)
{
	#ifndef _mDEBUG
	CheckStend();
	if(!OPCConnectOK){return;}
	#endif

	OPCControlPause(tReadCycleTimer);
	LogPrint("Сброс результатов испытаний из контроллера по поз. A");
	/**S_end_cycle_1=0;
	*T_end_cycle_1=0;
	*type_cycle_1=0;
	*StepsQty1=0;
	*PollsQty1=0;     */

	//pOPC->WriteGr3(S_end_cycle_1);
	//pOPC->WriteGr3(T_end_cycle_1);
	//pOPC->WriteGr3(type_cycle_1);
	//pOPC->WriteGr3(StepsQty1);
	//pOPC->WriteGr3(PollsQty1);

	*ResetData1=true;
	pOPC->WriteGr1(ResetData1);
	//pOPC->ResetGr7();
	OPCControlResume(tReadCycleTimer);
	TyreA->TotalS           =*S_end_cycle_1;
	TyreA->TotalTime        =*T_end_cycle_1;
	TyreA->TestMode         =*type_cycle_1;
	TyreA->StepsNo          =*StepsQty1;
	TyreA->PollsNo          =*PollsQty1;

	TyreA->Clear();
	SGClear(sgTestResultA,0);//чистка таблицы
	ShowProtAData();
}

void __fastcall TmfRB::btnResetResPosBClick(TObject *Sender)
{
	#ifndef _mDEBUG
	CheckStend();
	if(!OPCConnectOK){return;}
	#endif

	OPCControlPause(tReadCycleTimer);
	LogPrint("Сброс результатов испытаний из контроллера по поз. B");
	/**S_end_cycle_2=0;
	*T_end_cycle_2=0;
	*type_cycle_2=0;
	*StepsQty2=0;
	*PollsQty2=0;     */

	//pOPC->WriteGr3(S_end_cycle_2);
	//pOPC->WriteGr3(T_end_cycle_2);
	//pOPC->WriteGr3(type_cycle_2);
	//pOPC->WriteGr3(StepsQty2);
	//pOPC->WriteGr3(PollsQty2);

	*ResetData2=true;
	pOPC->WriteGr1(ResetData2);
	//pOPC->ResetGr11();

	OPCControlResume(tReadCycleTimer);
	TyreB->TotalS           =*S_end_cycle_2;
	TyreB->TotalTime        =*T_end_cycle_2;
	TyreB->TestMode         =*type_cycle_2;
	TyreB->StepsNo          =*StepsQty2;
	TyreB->PollsNo          =*PollsQty2;

	TyreB->Clear();
	SGClear(sgTestResultB,0);//чистка таблицы
	ShowProtBData();
}




void __fastcall TmfRB::AboutProgExecute(TObject *Sender)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::btResetBClick(TObject *Sender)
{
	*ResetData2=true;
	pOPC->WriteGr1(ResetData2);
    CD_reset2=true;
}
//---------------------------------------------------------------------------

void __fastcall TmfRB::btResetAClick(TObject *Sender)
{
	*ResetData1=true;
	pOPC->WriteGr1(ResetData1);
	CD_reset1=true;
}
//---------------------------------------------------------------------------

