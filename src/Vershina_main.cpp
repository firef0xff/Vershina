// ---------------------------------------------------------------------------

#include <Printers.hpp>
#include <vcl.h>
#pragma hdrstop
#define MFHEIGHT  750
#define MFWIDTH  1024
#include "def.h"
#include "Common.h"
#include "Vershina_main.h"
#include "sert/TyreProt.h"
#include "splash_screen/Head_band.h"
#include "login/Login.h"
#include "login/AppManagnent.h"
#include "support_functions/functions.h"
#include "src/cpu/cpu_memory.h"
#include <algorithm>

#include "support_functions/print_support.h"
#include "log/log_impl.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmfRB *mfRB;

TPrinter *pProtPrt = Printer(); // указатель на принтер
char DecimalSeparator = '.';

// ---------------------------------------------------------------------------
__fastcall TmfRB::TmfRB(TComponent* Owner) :
   TForm(Owner),
   closing(false),
   InpTyre(""),
   mPosA("A", "Прог 1")
{
   // соединение с базой программы
   String con1 = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=", con2 =
      ";Persist Security Info=False";

   ADC->ConnectionString = con1 + ExtractFilePath(Application->ExeName) +
      "ProgData.mdb" + con2;
   DB.reset(new cSQL(ADC,false));
   std::unique_ptr<TLogInwnd>wnd(new TLogInwnd(this, DB));
   if (wnd->ShowModal() == mrOk)
   {
      std::unique_ptr<THeadband>hbnd(new THeadband(this));
      hbnd->Show();

      // ограничения интерфейса
      if (!wnd->get_Adjust())
      {
         tsCalibration->Hide();
         tsCalibration->PageControl = 0;

         tsSert->Hide();
         tsSert->PageControl = 0;

         acLoadSertPrintProtA->Visible = false;
         acPrintLoadCalibrProtA->Visible = false;
      }
      if (!wnd->get_Work())
      {
         tsCurrentStatus->Hide();
         tsCurrentStatus->PageControl = 0;

         tsManual->Hide();
         tsManual->PageControl = 0;

         tsTestProgramSetting->Hide();
         tsTestProgramSetting->PageControl = 0;

         tsProtocol->Hide();
         tsProtocol->PageControl = 0;

         tsEmSettings->Hide();
         tsEmSettings->PageControl = 0;

         acPrintSetup->Visible = false;
         Action1->Visible = false;
         acProtTitleFileSaveAs->Visible = false;
         _acProtTitleFileSaveAs->Visible = false;
         acProtTitleFileOpen->Visible = false;
         acSProgFileSaveAs->Visible = false;
         _acSProgFileSaveAs->Visible = false;
         acSProgFileOpen->Visible = false;
         acTProgFileSaveAs->Visible = false;
         _acTProgFileSaveAs->Visible = false;
         acTProgFileOpen->Visible = false;

         acGeneralStop->Visible = false;
         acDrumOff->Visible = false;
         acDrumOn->Visible = false;
         acCarriage1To->Visible = false;
         acCarriage1Stop->Visible = false;
         acCarriage1From->Visible = false;
         acPumpOffA->Visible = false;
         acPumpOnA->Visible = false;

         acOPCControlStart->Visible = false;
         acOPCControlStop->Visible = false;
         CommonParamRead->Visible = false;
         acLoadTestResFmPosA->Visible = false;

         acPrintSpdCalibrProt->Visible = false;
         acPrintTCalibrProtA->Visible = false;
         acPrintRCalibrProtA->Visible = false;

         acPrintProtPosAToFile->Visible = false;

         _acPrintSpdCalibrProt->Visible = false;
         _acPrintTCalibrProtA->Visible = false;
         _acPrintRCalibrProtA->Visible = false;

         _acPrintProtPosAToFile->Visible = false;

      }
      if (!wnd->get_Managment())
      {
         acSettingsManagment->Visible = false;
      }
      Application->ProcessMessages();
      DecimalSeparator = '.';
      mfRB->Height = MFHEIGHT;
      mfRB->Width = MFWIDTH;

      cpu::CpuMemory::OnConnected(
      [this]()
      {
         auto& inst_cpu = cpu::CpuMemory::Instance();

         std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
         auto &gr12 = *inst_cpu.mPos1->mGr12;
         mPosA.mLdC.LKQInit( gr12 );
      });

      InitLogger( reLog );
      reLog->Clear();
      pProtPrt->Canvas->Font->Name = "Lucida Console";
      pProtPrt->Canvas->Font->Size = 10;
      LogPrint("Шрифт по умолчанию на принтер: \"" +
         pProtPrt->Canvas->Font->Name + "\"", clMoneyGreen);

      SetCommonParam();
      ShowCommonParam();
      pcRB->ActivePage = tsCurrentStatus;
      sbRB->Panels->Items[0]->Text = "Соединения со стендом нет";
      sbRB->Panels->Items[3]->Text = Now().DateTimeString();
      LogPrint( "Старт программы!", clAqua);
      OnMainFormCreate(this);
      CheckStend(); // проверка соединения и попытка восстановить соединение
      GetSettings(); // чтение настроек сохранения
      // чтение названия последних загруженных программ
      mPosA.RunProgName = GetCurrProgA();
      if (mPosA.RunProgName != "")
      {
         stP1L2ProgNameA->Caption = AnsiString(mPosA.RunProgName.c_str());
      }
   }
   else
   {
      Visible = false;
      Application->Terminate();
   }
}

// ---- End of TmfRB constructor ---------------------------------------------
__fastcall TmfRB::~TmfRB()
{
   // восстановление перед уничтожением
   tsCalibration->PageControl = pcRB;
   tsSert->PageControl = pcRB;
   tsCurrentStatus->PageControl = pcRB;
   tsManual->PageControl = pcRB;
   tsTestProgramSetting->PageControl = pcRB;
   tsProtocol->PageControl = pcRB;
}
// ---- End of TmfRB destructor ----------------------------------------------

void __fastcall TmfRB::OnCommonParamReadExec(TObject *Sender)
{
   auto &inst = cpu::CpuMemory::Instance();
   if ( !inst.IsConnected() )
      return;
   inst.ReadCycleParameters();
   ShowStatus();
   ShowCommonParam();
}
// ---------------------------------------------------------------------------

void TmfRB::SetCommonParam(void)
   // настройка таблицы общих параметров
{
   stP1L1TyreTypeA->Caption = AnsiString(mPosA.TyreType.c_str());
   stP1L2ProgNameA->Caption = AnsiString(mPosA.RunProgName.c_str());
   stP1CurDate->Caption = Now().DateTimeString();
}
// ---- End of SetCommonParam ------------------------------------------------

void TmfRB::DesignSProgTable(void)
   // создание таблицы для ввода программы испытаний по пути
{
   const int Col0Width = 30, Col1Width = 80, Col2Width = 105, Col3Width = 65;
   const int pHeight = 26, pH = 24, Width2 = 50, LSp = 10;
   int Left1 = leSTyrePressure->EditLabel->Width + LSp, Left2 =
      Left1 + leSTotalStepsQty->EditLabel->Width + Width2 + LSp, Width1 =
      Left2 + Width2 - Left1, Top1 = pHeight + LSp, Top2 =
      pHeight * 2 + LSp * 2, Left3 =
      Left2 + Width2 + leTotalTestS->EditLabel->Width + LSp;
   pSProgTtl->Left = 0;
   pSProgTtl->Top = 0;
   pSProgTtl->Width = tsSProgWidth;
   pSProgTtl->Height = pHeight;
   leSProgName->Left = Left1;
   leSProgName->Top = Top1;
   leSProgName->Width = Width1;
   leSProgName->Height = pH;
   leTotalTestS->Left = Left3;
   leTotalTestS->Top = Top1;
   leTotalTestS->Width = Width2;
   leTotalTestS->Height = pH;
   leSTyrePressure->Left = Left1;
   leSTyrePressure->Top = Top2;
   leSTyrePressure->Width = Width2;
   leSTyrePressure->Height = pH;
   leSTotalStepsQty->Left = Left2;
   leSTotalStepsQty->Top = Top2;
   leSTotalStepsQty->Width = Width2;
   leSTotalStepsQty->Height = pH;
   leSPollingTotalQty->Left = Left3;
   leSPollingTotalQty->Top = Top2;
   leSPollingTotalQty->Width = Width2;
   leSPollingTotalQty->Height = pH;
   lSProgTblNme->Top = Top2 + pH + LSp;
   sgSProgram->Top = Top2 + pH * 2 + LSp;
   sgSProgram->ColWidths[0] = Col0Width;
   sgSProgram->ColWidths[1] = Col1Width;
   sgSProgram->ColWidths[2] = Col2Width;
   sgSProgram->ColWidths[3] = Col3Width;
   sgSProgram->Left = tsSProgWidth / 20;

   int STableWidth = Col0Width + Col1Width + Col2Width + Col3Width + 29;
   lSProgTblNme->Left = (STableWidth - lSProgTblNme->Width) / 2 +
      sgSProgram->Left;
   sgSProgram->Width = STableWidth;
   int STableHeight = tsSProgHeight - sgSProgram->Top - 5;
   int RowNo = STableHeight / (sgSProgram->RowHeights[0] + 1);
   STableHeight = RowNo * sgSProgram->RowHeights[0] + RowNo;
   sgSProgram->Height = STableHeight;
   sgSProgram->Cells[0][0] = "№";
   sgSProgram->Cells[1][0] = "Нагрузка, кН";
   sgSProgram->Cells[2][0] = "Скорость, км/час";
   sgSProgram->Cells[3][0] = "  Путь, км";
   for (int i = 0; i < MAXNUMOFSTEPS; i++)
   {
      if (i < 9)
         sgSProgram->Cells[0][i + 1] = "  " + String(i + 1) + ":";
      else if (i < 99)
         sgSProgram->Cells[0][i + 1] = " " + String(i + 1) + ":";
      else
         sgSProgram->Cells[0][i + 1] = String(i + 1) + ":";
   }
   lSPollingTblNme1->Top = lSProgTblNme->Top;
   sgSPolling->Left = sgSProgram->Left + STableWidth + 40;
   sgSPolling->Top = sgSProgram->Top;
   sgSPolling->ColWidths[0] = Col0Width;
   sgSPolling->ColWidths[1] = Col3Width;
   int SPollTableWidth = Col0Width + Col3Width + 27;
   lSPollingTblNme1->Left = (SPollTableWidth - lSPollingTblNme1->Width) / 2 +
      sgSPolling->Left;
   sgSPolling->Width = SPollTableWidth;
   sgSPolling->Height = STableHeight;
   sgSPolling->Cells[0][0] = "№";
   sgSPolling->Cells[1][0] = "  Путь, км";
   for (int i = 0; i < MAXNUMOFPOLLS; i++)
   {
      if (i < 9)
         sgSPolling->Cells[0][i + 1] = "  " + String(i + 1) + ":";
      else if (i < 99)
         sgSPolling->Cells[0][i + 1] = " " + String(i + 1) + ":";
      else
         sgSPolling->Cells[0][i + 1] = String(i + 1) + ":";
   }
   int btnLeft = sgSPolling->Left + SPollTableWidth + 10;
   int btnWidth = tsSProgWidth - btnLeft - 10;
   int btnHeight = 50;
   btnNewSProg->Left = btnLeft;
   btnCheckSProg->Left = btnLeft;
   btnSaveSProgToFile->Left = btnLeft;
   btnOpenSProgFmFile->Left = btnLeft;
   btnLoadSProgToPosA->Left = btnLeft;
   btnNewSProg->Width = btnWidth;
   btnCheckSProg->Width = btnWidth;
   btnSaveSProgToFile->Width = btnWidth;
   btnOpenSProgFmFile->Width = btnWidth;
   btnLoadSProgToPosA->Width = btnWidth;
   btnNewSProg->Height = btnHeight;
   btnCheckSProg->Height = btnHeight;
   btnSaveSProgToFile->Height = btnHeight;
   btnOpenSProgFmFile->Height = btnHeight;
   btnLoadSProgToPosA->Height = btnHeight;
   btnNewSProg->Top = sgSProgram->Top;
   btnCheckSProg->Top = btnNewSProg->Top + btnHeight + 10;
   btnSaveSProgToFile->Top = btnCheckSProg->Top + btnHeight + 10;
   btnOpenSProgFmFile->Top = btnSaveSProgToFile->Top + btnHeight + 10;
   btnLoadSProgToPosA->Top = btnOpenSProgFmFile->Top + btnHeight + 10;
   /* TGridRect myRect;
    myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
    sgSProgram->Selection=myRect;
    sgSPolling->Selection=myRect; */
   btnCheckSProg->Enabled = false;
   btnSaveSProgToFile->Enabled = false;
   btnLoadSProgToPosA->Enabled = false;
}
// ---- End of DesignSProgTable ----------------------------------------------

void TmfRB::DesignLoadSertAPanel(void)
   // расположение компонент на панели калибровки нагрузки поз. А
{

   const int C0W = 30, C1W = 60, C2W = 70, C3W = 70, C4W = 80;
   int TblW = C0W + C1W + C2W + C3W + C4W + 28, H1 = 40, LSp1 = 10;
   int TblH = tsLoadCalibrAH - H1, CellH =
      std::max(ceil(double(TblH / (sert::LCalibr::ITEMS_COUNT + 1))) - 1, 16.0)
      /* , Cell0H=40;TblH-(sert::LCalibr::ITEMS_COUNT+1)*CellH */ ; // -sert::LCalibr::ITEMS_COUNT;
   pLoadSertATtl->Height = H1;
   sgLoadSertA->ColWidths[0] = C0W;
   sgLoadSertA->ColWidths[1] = C1W;
   sgLoadSertA->ColWidths[2] = C2W;
   sgLoadSertA->ColWidths[3] = C3W;
   sgLoadSertA->ColWidths[4] = C4W;
   sgLoadSertA->Width = TblW;
   sgLoadSertA->Cells[0][0] = "№";
   sgLoadSertA->Cells[1][0] = "Задание";
   sgLoadSertA->Cells[2][0] = "Показание";
   sgLoadSertA->Cells[3][0] = "Измерение";
   sgLoadSertA->Cells[4][0] = "Коэффицент";
   sgLoadSertA->RowHeights[0] = CellH;
   for (int i = 1; i < sert::LCalibr::ITEMS_COUNT + 1; i++)
      sgLoadSertA->RowHeights[i] = CellH;
   for (int i = 0; i < sert::LCalibr::ITEMS_COUNT; i++)
   {
      if (i < 9)
         sgLoadSertA->Cells[0][i + 1] = "  " + String(i + 1) + ":";
      else
         sgLoadSertA->Cells[0][i + 1] = " " + String(i + 1) + ":";
      sgLoadSertA->Cells[1][i + 1] = mPosA.mLdC.sTLd[i].c_str();
      if (mPosA.mLdC.ReadoutLd[i] != 0.0)
         sgLoadSertA->Cells[2][i + 1] = "   " + FloatToStrF(mPosA.mLdC.ReadoutLd[i],
         ffFixed, 6, 2);
      else
         sgLoadSertA->Cells[2][i + 1] = "";
      if (mPosA.mLdC.MeasuredLd[i] != 0.0)
         sgLoadSertA->Cells[3][i + 1] =
            "    " + FloatToStrF(mPosA.mLdC.MeasuredLd[i], ffFixed, 6, 2);
      else
         sgLoadSertA->Cells[3][i + 1] = "";
      if (mPosA.mLdC.loaded)
         sgLoadSertA->Cells[4][i + 1] =
            "    " + FloatToStrF(mPosA.mLdC.KA[i], ffFixed, 8, 5);
      else
         sgLoadSertA->Cells[4][i + 1] = "";
   }
   int Top1 = H1 + LSp1, Left11 = TblW + LSp1, LblW1 = 85, BtnW1 = LblW1 * 3,
      BtnW2 = tsSpeedCalibrW - TblW - BtnW1 - LSp1 * 3;
   int Left12 = Left11 + LblW1, Left13 = Left11 + LblW1 * 2, Left2 =
      Left11 + LblW1 * 3 + LSp1, H2 = 50, H3 = 26;
   btnPrevSertLoadA->Left = Left11;
   btnPrevSertLoadA->Top = Top1;
   btnPrevSertLoadA->Width = BtnW1;
   btnPrevSertLoadA->Height = H2;
   btnLoadSertClearTableA->Left = Left2;
   btnLoadSertClearTableA->Top = Top1;
   btnLoadSertClearTableA->Width = BtnW2;
   btnLoadSertClearTableA->Height = H2;
   btnLoadSertCalcA->Left = Left2;
   btnLoadSertCalcA->Top = Top1 + H2 + LSp1;
   btnLoadSertCalcA->Width = BtnW2;
   btnLoadSertCalcA->Height = H2;
   btnLoadSertPrintProtA->Left = Left2;
   btnLoadSertPrintProtA->Top = Top1 + H2 * 2 + LSp1 * 2;
   btnLoadSertPrintProtA->Width = BtnW2;
   btnLoadSertPrintProtA->Height = H2;
   leCurrentLoadSertSetA->Left = Left11;
   leCurrentLoadSertSetA->Top = Top1 + H2 * 2 + LSp1 - H3;
   leCurrentLoadSertSetA->Width = LblW1;
   leCurrentLoadSertSetA->Height = H3;
   leReadLoadSertA->Left = Left12;
   leReadLoadSertA->Top = Top1 + H2 * 2 + LSp1 - H3;
   leReadLoadSertA->Width = LblW1;
   leReadLoadSertA->Height = H3;
   leMeasLoadSertA->Left = Left13;
   leMeasLoadSertA->Top = Top1 + H2 * 2 + LSp1 - H3;
   leMeasLoadSertA->Width = LblW1;
   leMeasLoadSertA->Height = H3;
   btnNextSertLoadA->Left = Left11;
   btnNextSertLoadA->Top = Top1 + H2 * 2 + LSp1 * 2;
   btnNextSertLoadA->Width = BtnW1;
   btnNextSertLoadA->Height = H2;
   btnLoadSertAToPLC->Left = Left2;
   btnLoadSertAToPLC->Top = Top1 + H2 * 3 + LSp1 * 3;
   btnLoadSertAToPLC->Width = BtnW2;
   btnLoadSertAToPLC->Height = H2;
   btnSertPumpOnA->Left = Left11;
   btnSertPumpOnA->Top = Top1 + H2 * 3 + LSp1 * 5;
   btnSertPumpOnA->Width = BtnW1;
   btnSertPumpOnA->Height = H2;
   btnSertPumpOffA->Left = Left11;
   btnSertPumpOffA->Top = Top1 + H2 * 6 + LSp1 * 8;
   btnSertPumpOffA->Width = BtnW1;
   btnSertPumpOffA->Height = H2;
   btnUploadSertAFmPLC->Left = Left2;
   btnUploadSertAFmPLC->Top = Top1 + H2 * 4 + LSp1 * 4;
   btnUploadSertAFmPLC->Width = BtnW2;
   btnUploadSertAFmPLC->Height = H2;
   btnResetCalibrCoeffA->Left = Left2;
   btnResetCalibrCoeffA->Top = Top1 + H2 * 5 + LSp1 * 5;
   btnResetCalibrCoeffA->Width = BtnW2;
   btnResetCalibrCoeffA->Height = H2;
   // mPosA.mLdC.Index=0;
   leCurrentLoadSertSetA->Text = FloatToStrF(mPosA.mLdC.TargetLd[mPosA.mLdC.Index],
      ffFixed, 6, 2);
   leReadLoadSertA->Text = FloatToStrF(mPosA.mLdC.ReadoutLd[mPosA.mLdC.Index],
      ffFixed, 6, 2);
   leMeasLoadSertA->Text = FloatToStrF(mPosA.mLdC.MeasuredLd[mPosA.mLdC.Index],
      ffFixed, 6, 2);
   /* TGridRect myRect;
    myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
    sgLoadSertA->Selection=myRect; */
   btnPrevSertLoadA->Enabled = false;
   btnNextSertLoadA->Enabled = true;
}
// ---- End of DesignLoadSertAPanel ------------------------------------------

void TmfRB::DesignTSertPanel(void)
   // расположение компонент на панели калибровки температуры
{
   int H1 = 26, LSp1 = 10;
   int PWidth = pTSertTtl->Width, PHeight = tsTemSert->Height - H1 - LSp1;
   int GBW = (PWidth - LSp1 * 3) / 2, Top1 = H1 + LSp1;
   pTSertTtl->Height = H1;
   gbTSertA->Top = Top1;
   gbTSertA->Left = LSp1;
   gbTSertA->Width = GBW;
   gbTSertA->Height = PHeight;
}
// ---- End of DesignTSertPanel ----------------------------------------------

void TmfRB::DesignRSertPanel(void)
   // расположение компонент на панели калибровки датчиков радиуса
{
   int H1 = 26, LSp1 = 10;
   // int PWidth=pRSertTtl->Width, PHeight=tsRadSert->Height-H1-LSp1;
   int BtnW = 170, LeW = 40, BtnH = 40, LeH = 20, Top1 = H1 + LSp1 * 5, Top2 =
      Top1 + BtnH + LSp1 * 2;
   int LeLblW = leRShiftA->EditLabel->Width, Left1 = LeLblW + LSp1, Left2 =
      Left1 + LeW + LSp1 * 2;
   pRSertTtl->Height = H1;
   leRShiftA->Left = Left1;
   leRShiftA->Top = Top1;
   leRShiftA->Width = LeW;
   leRShiftA->Height = LeH;
   btnRShiftALoadToPLC->Left = Left2;
   btnRShiftALoadToPLC->Top = Top1 - (BtnH - LeH) / 2;
   btnRShiftALoadToPLC->Width = BtnW;
   btnRShiftALoadToPLC->Height = BtnH;
}
// ---- End of DesignRSertPanel ----------------------------------------------

void TmfRB::DesignLoadCalibrAPanel(void)
   // расположение компонент на панели аттестации нагрузки поз. А
{
   const int C0W = 30, C1W = 60, C2W = 70, C3W = 70, C4W = 80;
   int TblW = C0W + C1W + C2W + C3W + C4W + 30, H1 = 40, LSp1 = 10;
   int TblH = tsLoadCalibrAH - H1, CellH =
      std::max((TblH - 5) / (sert::LSert::ITEMS_COUNT + 1), 16);
   pLoadCalibrBTtl->Height = H1;
   sgLoadCalibrA->ColWidths[0] = C0W;
   sgLoadCalibrA->ColWidths[1] = C1W;
   sgLoadCalibrA->ColWidths[2] = C2W;
   sgLoadCalibrA->ColWidths[3] = C3W;
   sgLoadCalibrA->ColWidths[4] = C4W;
   sgLoadCalibrA->Width = TblW;
   sgLoadCalibrA->Cells[0][0] = "№";
   sgLoadCalibrA->Cells[1][0] = "Задание";
   sgLoadCalibrA->Cells[2][0] = "Измерение";
   sgLoadCalibrA->Cells[3][0] = "Показание";
   sgLoadCalibrA->Cells[4][0] = "Погрешность";
   for (int i = 0; i < sert::LSert::ITEMS_COUNT + 1; i++)
      sgLoadCalibrA->RowHeights[i] = CellH;
   for (int i = 0; i < sert::LSert::ITEMS_COUNT; i++)
   {
      sgLoadCalibrA->RowHeights[i] = CellH;
      if (i < 9)
         sgLoadCalibrA->Cells[0][i + 1] = "  " + String(i + 1) + ":";
      else
         sgLoadCalibrA->Cells[0][i + 1] = " " + String(i + 1) + ":";
      sgLoadCalibrA->Cells[1][i + 1] = mPosA.mLdS.sTLd[i].c_str();
      if (mPosA.mLdS.ReadoutLd[i] != 0.0)
      {
         sgLoadCalibrA->Cells[2][i + 1] =
            "    " + FloatToStrF(mPosA.mLdS.MeasuredLd[i], ffFixed, 6, 2);
         sgLoadCalibrA->Cells[3][i + 1] =
            "    " + FloatToStrF(mPosA.mLdS.ReadoutLd[i], ffFixed, 6, 2);
         sgLoadCalibrA->Cells[4][i + 1] =
            "    " + FloatToStrF(mPosA.mLdS.RelError[i], ffFixed, 6, 2);
      }
      else
      {
         sgLoadCalibrA->Cells[2][i + 1] = "";
         sgLoadCalibrA->Cells[3][i + 1] = "";
         sgLoadCalibrA->Cells[4][i + 1] = "";
      }
   }
   int Top1 = H1 + LSp1, Left11 = TblW + LSp1, LblW1 = 85, BtnW1 = LblW1 * 3,
      BtnW2 = tsSpeedCalibrW - TblW - BtnW1 - LSp1 * 3;
   int Left12 = Left11 + LblW1, Left13 = Left11 + LblW1 * 2, Left2 =
      Left11 + LblW1 * 3 + LSp1, H2 = 50, H3 = 26;
   btnPrevCalibrLoadA->Left = Left11;
   btnPrevCalibrLoadA->Top = Top1;
   btnPrevCalibrLoadA->Width = BtnW1;
   btnPrevCalibrLoadA->Height = H2;
   btnClearLoadCalibreTableA->Left = Left2;
   btnClearLoadCalibreTableA->Top = Top1;
   btnClearLoadCalibreTableA->Width = BtnW2;
   btnClearLoadCalibreTableA->Height = H2;
   btnLoadCalibrCalcA->Left = Left2;
   btnLoadCalibrCalcA->Top = Top1 + H2 + LSp1;
   btnLoadCalibrCalcA->Width = BtnW2;
   btnLoadCalibrCalcA->Height = H2;
   btnLoadCalibrTableAPrint->Left = Left2;
   btnLoadCalibrTableAPrint->Top = Top1 + H2 * 2 + LSp1 * 2;
   btnLoadCalibrTableAPrint->Width = BtnW2;
   btnLoadCalibrTableAPrint->Height = H2;
   leCurrentLoadSetA->Left = Left11;
   leCurrentLoadSetA->Top = Top1 + H2 * 2 + LSp1 - H3;
   leCurrentLoadSetA->Width = LblW1;
   leCurrentLoadSetA->Height = H3;
   leReadLoadA->Left = Left12;
   leReadLoadA->Top = Top1 + H2 * 2 + LSp1 - H3;
   leReadLoadA->Width = LblW1;
   leReadLoadA->Height = H3;
   leMeasuredLoadA->Left = Left13;
   leMeasuredLoadA->Top = Top1 + H2 * 2 + LSp1 - H3;
   leMeasuredLoadA->Width = LblW1;
   leMeasuredLoadA->Height = H3;
   btnNextCalibrLoadA->Left = Left11;
   btnNextCalibrLoadA->Top = Top1 + H2 * 2 + LSp1 * 2;
   btnNextCalibrLoadA->Width = BtnW1;
   btnNextCalibrLoadA->Height = H2;
   btnPumpOnA->Left = Left11;
   btnPumpOnA->Top = Top1 + H2 * 3 + LSp1 * 5;
   btnPumpOnA->Width = BtnW1;
   btnPumpOnA->Height = H2;
   btnPumpOffA->Left = Left11;
   btnPumpOffA->Top = Top1 + H2 * 4 + LSp1 * 6;
   btnPumpOffA->Width = BtnW1;
   btnPumpOffA->Height = H2;
   // mPosA.mLdS.Index=0;
   leCurrentLoadSetA->Text = FloatToStrF(mPosA.mLdS.TargetLd[mPosA.mLdS.Index],
      ffFixed, 6, 2);
   leReadLoadA->Text = FloatToStrF(mPosA.mLdS.ReadoutLd[mPosA.mLdS.Index], ffFixed, 6, 2);
   leMeasuredLoadA->Text = FloatToStrF(mPosA.mLdS.MeasuredLd[mPosA.mLdS.Index],
      ffFixed, 6, 2);
   /* TGridRect myRect;
    myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
    sgLoadCalibrA->Selection=myRect; */
   btnPrevCalibrLoadA->Enabled = false;
   btnNextCalibrLoadA->Enabled = true;
}
// ---- End of DesignLoadCalibrAPanel ----------------------------------------

void TmfRB::DesignRCalibrAPanel(void)
   // расположение компонент на панели аттестации радиуса поз. А
{
   const int C0W = 30, C1W = 70, C2W = 70, C3W = 80;
   int TblW = C0W + C1W + C2W + C3W + 7, H1 = 40, LSp1 = 10;
   sgRCalibrA->RowCount = sert::RSert::ITEMS_COUNT + 1;
   int TblH = tsRCalibrAH - H1, CellH = (TblH - sert::RSert::ITEMS_COUNT / 3) / (sert::RSert::ITEMS_COUNT + 1);
   pRCalibrATtl->Height = H1;
   sgRCalibrA->ColWidths[0] = C0W;
   sgRCalibrA->ColWidths[1] = C1W;
   sgRCalibrA->ColWidths[2] = C2W;
   sgRCalibrA->ColWidths[3] = C3W;
   sgRCalibrA->Width = TblW;
   sgRCalibrA->Cells[0][0] = "№";
   sgRCalibrA->Cells[1][0] = "Показание";
   sgRCalibrA->Cells[2][0] = "Измерение";
   sgRCalibrA->Cells[3][0] = "Погрешность";
   for (int i = 0; i < sert::RSert::ITEMS_COUNT + 1; i++)
      sgRCalibrA->RowHeights[i] = CellH;
   for (int i = 0; i < sert::RSert::ITEMS_COUNT; i++)
   {
      if (i < 9)
         sgRCalibrA->Cells[0][i + 1] = "  " + String(i + 1) + ":";
      else
         sgRCalibrA->Cells[0][i + 1] = " " + String(i + 1) + ":";
      sgRCalibrA->Cells[1][i + 1] = "";
      sgRCalibrA->Cells[2][i + 1] = "";
      sgRCalibrA->Cells[3][i + 1] = "";
   }
   int Top1 = H1 + LSp1, Left11 = TblW + LSp1, LblW1 =
      (tsTCalibrAW - TblW - LSp1 * 3) / 4, BtnW1 = LblW1 * 2, BtnW2 =
      tsTCalibrAW - TblW - BtnW1 - LSp1 * 3;
   int Left12 = Left11 + LblW1, Left2 = Left11 + BtnW1 + LSp1, H2 = 50, H3 = 26;
   int BtnW4 = (tsTCalibrAW - TblW - LSp1 * 4) / 5, BtnW3 = BtnW4 * 2, Top2 =
      Top1 + H2 * 3 + LSp1 * 4, Left3 = Left11 + BtnW3 + LSp1, Left4 =
      Left3 + BtnW4 + LSp1;
   btnPrevRCalibrA->Left = Left11;
   btnPrevRCalibrA->Top = Top1;
   btnPrevRCalibrA->Width = BtnW1;
   btnPrevRCalibrA->Height = H2;
   btnClearRCalibrTableA->Left = Left2;
   btnClearRCalibrTableA->Top = Top1;
   btnClearRCalibrTableA->Width = BtnW2;
   btnClearRCalibrTableA->Height = H2;
   btnRCalibrCalcA->Left = Left2;
   btnRCalibrCalcA->Top = Top1 + H2 + LSp1;
   btnRCalibrCalcA->Width = BtnW2;
   btnRCalibrCalcA->Height = H2;
   btnRCalibrTableAPrint->Left = Left2;
   btnRCalibrTableAPrint->Top = Top1 + H2 * 2 + LSp1 * 2;
   btnRCalibrTableAPrint->Width = BtnW2;
   btnRCalibrTableAPrint->Height = H2;
   leReadRA->Left = Left11;
   leReadRA->Top = Top1 + H2 * 2 + LSp1 - H3;
   leReadRA->Width = LblW1;
   leReadRA->Height = H3;
   leMeasRA->Left = Left12;
   leMeasRA->Top = Top1 + H2 * 2 + LSp1 - H3;
   leMeasRA->Width = LblW1;
   leMeasRA->Height = H3;
   btnNextRCalibrA->Left = Left11;
   btnNextRCalibrA->Top = Top1 + H2 * 2 + LSp1 * 2;
   btnNextRCalibrA->Width = BtnW1;
   btnNextRCalibrA->Height = H2;
   btnCalibrCarr1Fm->Left = Left11;
   btnCalibrCarr1Fm->Top = Top2;
   btnCalibrCarr1Fm->Width = BtnW3;
   btnCalibrCarr1Fm->Height = H2;
   btnCalibrCarr1Stop->Left = Left3;
   btnCalibrCarr1Stop->Top = Top2;
   btnCalibrCarr1Stop->Width = BtnW4;
   btnCalibrCarr1Stop->Height = H2;
   btnCalibrCarr1To->Left = Left4;
   btnCalibrCarr1To->Top = Top2;
   btnCalibrCarr1To->Width = BtnW3;
   btnCalibrCarr1To->Height = H2;
   mPosA.mRS.Index = 0;
   leReadRA->Text = FloatToStrF(mPosA.mRS.ReadoutR[0], ffFixed, 6, 2);
   leMeasRA->Text = FloatToStrF(mPosA.mRS.MeasuredR[0], ffFixed, 6, 2);
   /* TGridRect myRect;
    myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
    sgRCalibrA->Selection=myRect; */
   btnPrevRCalibrA->Enabled = false;
   btnNextRCalibrA->Enabled = true;
}
// ---- End of DesignRCalibrAPanel -------------------------------------------

void TmfRB::DesignTCalibrAPanel(void)
   // расположение компонент на панели аттестации температуры поз. А
{
   const int C0W = 30, C1W = 70, C2W = 70, C3W = 80;
   int TblW = C0W + C1W + C2W + C3W + 7, H1 = 40, LSp1 = 10;
   sgTCalibrA->RowCount = sert::TSert::ITEMS_COUNT + 1;
   int TblH = tsTCalibrAH - H1, CellH = (TblH - sert::TSert::ITEMS_COUNT / 3) / (sert::TSert::ITEMS_COUNT + 1);
   pTCalibrATtl->Height = H1;
   sgTCalibrA->ColWidths[0] = C0W;
   sgTCalibrA->ColWidths[1] = C1W;
   sgTCalibrA->ColWidths[2] = C2W;
   sgTCalibrA->ColWidths[3] = C3W;
   sgTCalibrA->Width = TblW;
   sgTCalibrA->Cells[0][0] = "№";
   sgTCalibrA->Cells[1][0] = "Показание";
   sgTCalibrA->Cells[2][0] = "Измерение";
   sgTCalibrA->Cells[3][0] = "Погрешность";
   for (int i = 0; i < sert::TSert::ITEMS_COUNT + 1; i++)
      sgTCalibrA->RowHeights[i] = CellH;
   for (int i = 0; i < sert::TSert::ITEMS_COUNT; i++)
   {
      if (i < 9)
         sgTCalibrA->Cells[0][i + 1] = "  " + String(i + 1) + ":";
      else
         sgTCalibrA->Cells[0][i + 1] = " " + String(i + 1) + ":";
      if (mPosA.mTS.RelError[i] != 0.0)
      {
         sgTCalibrA->Cells[1][i + 1] = "    " + FloatToStrF(mPosA.mTS.ReadoutT[i],
            ffFixed, 6, 2);
         sgTCalibrA->Cells[2][i + 1] = "    " + FloatToStrF(mPosA.mTS.MeasuredT[i],
            ffFixed, 6, 2);
         sgTCalibrA->Cells[3][i + 1] = "    " + FloatToStrF(mPosA.mTS.RelError[i],
            ffFixed, 6, 2);
      }
      else
      {
         sgTCalibrA->Cells[1][i + 1] = "";
         sgTCalibrA->Cells[2][i + 1] = "";
         sgTCalibrA->Cells[3][i + 1] = "";
      }
   }
   int Top1 = H1 + LSp1, Left11 = TblW + LSp1, LblW1 =
      (tsTCalibrAW - TblW - LSp1 * 3) / 4, BtnW1 = LblW1 * 2, BtnW2 =
      tsTCalibrAW - TblW - BtnW1 - LSp1 * 3;
   int Left12 = Left11 + LblW1, Left2 = Left11 + BtnW1 + LSp1, H2 = 50, H3 = 26;
   btnPrevTCalibrA->Left = Left11;
   btnPrevTCalibrA->Top = Top1;
   btnPrevTCalibrA->Width = BtnW1;
   btnPrevTCalibrA->Height = H2;
   btnClearTCalibrTableA->Left = Left2;
   btnClearTCalibrTableA->Top = Top1;
   btnClearTCalibrTableA->Width = BtnW2;
   btnClearTCalibrTableA->Height = H2;
   btnTCalibrCalcA->Left = Left2;
   btnTCalibrCalcA->Top = Top1 + H2 + LSp1;
   btnTCalibrCalcA->Width = BtnW2;
   btnTCalibrCalcA->Height = H2;
   btnTCalibrTableAPrint->Left = Left2;
   btnTCalibrTableAPrint->Top = Top1 + H2 * 2 + LSp1 * 2;
   btnTCalibrTableAPrint->Width = BtnW2;
   btnTCalibrTableAPrint->Height = H2;
   btnTLimitsCalcA->Left = Left2;
   btnTLimitsCalcA->Top = Top1 + H2 * 3 + LSp1 * 3;
   btnTLimitsCalcA->Width = BtnW2;
   btnTLimitsCalcA->Height = H2;
   leReadTA->Left = Left11;
   leReadTA->Top = Top1 + H2 * 2 + LSp1 - H3;
   leReadTA->Width = LblW1;
   leReadTA->Height = H3;
   leMeasTA->Left = Left12;
   leMeasTA->Top = Top1 + H2 * 2 + LSp1 - H3;
   leMeasTA->Width = LblW1;
   leMeasTA->Height = H3;
   btnNextTCalibrA->Left = Left11;
   btnNextTCalibrA->Top = Top1 + H2 * 2 + LSp1 * 2;
   btnNextTCalibrA->Width = BtnW1;
   btnNextTCalibrA->Height = H2;
   // mPosA.mTS.Index                  =0;
   leReadTA->Text = FloatToStrF(mPosA.mTS.ReadoutT[mPosA.mTS.Index], ffFixed, 6, 2);
   leMeasTA->Text = FloatToStrF(mPosA.mTS.MeasuredT[mPosA.mTS.Index], ffFixed, 6, 2);
   /* TGridRect myRect;
    myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=-1;
    sgTCalibrA->Selection=myRect; */
   btnPrevTCalibrA->Enabled = false;
   btnNextTCalibrA->Enabled = true;
}
// ---- End of DesignTCalibrAPanel -------------------------------------------

void TmfRB::DesignSpdCalibrPanel(void)
   // расположение компонент на панели аттестации барабана
{
   const int C0W = 30, C1W = 60, C2W = 70, C3W = 70, C4W = 80;
   int TblW = C0W + C1W + C2W + C3W + C4W + 29, H1 = 40, LSp1 = 10;
   pSpeedCalibrTtl->Height = H1;
   sgSpeedCalibr->ColWidths[0] = C0W;
   sgSpeedCalibr->ColWidths[1] = C1W;
   sgSpeedCalibr->ColWidths[2] = C2W;
   sgSpeedCalibr->ColWidths[3] = C3W;
   sgSpeedCalibr->ColWidths[4] = C4W;
   sgSpeedCalibr->Width = TblW;
   sgSpeedCalibr->Cells[0][0] = "№";
   sgSpeedCalibr->Cells[1][0] = "Задание";
   sgSpeedCalibr->Cells[2][0] = "Показание";
   sgSpeedCalibr->Cells[3][0] = "Измерение";
   sgSpeedCalibr->Cells[4][0] = "Погрешность";

   for (int i = 0; i < sert::VSert::ITEMS_COUNT; i++)
   {
      if (i < 9)
         sgSpeedCalibr->Cells[0][i + 1] = "  " + String(i + 1) + ":";
      else
         sgSpeedCalibr->Cells[0][i + 1] = " " + String(i + 1) + ":";
      sgSpeedCalibr->Cells[1][i + 1] = VS.sTV[i].c_str();
      sgSpeedCalibr->Cells[2][i + 1] = "";
      sgSpeedCalibr->Cells[3][i + 1] = "";
      sgSpeedCalibr->Cells[4][i + 1] = "";
   }
   int Top1 = H1 + LSp1, Left11 = TblW + LSp1, LblW1 = 85, BtnW1 = LblW1 * 3,
      BtnW2 = tsSpeedCalibrW - TblW - BtnW1 - LSp1 * 3;
   int Left12 = Left11 + LblW1, Left13 = Left11 + LblW1 * 2, Left2 =
      Left11 + LblW1 * 3 + LSp1, H2 = 50, H3 = 26;
   btnPrevCalibrV->Left = Left11;
   btnPrevCalibrV->Top = Top1;
   btnPrevCalibrV->Width = BtnW1;
   btnPrevCalibrV->Height = H2;
   btnClearVCalibreTable->Left = Left2;
   btnClearVCalibreTable->Top = Top1;
   btnClearVCalibreTable->Width = BtnW2;
   btnClearVCalibreTable->Height = H2;
   btnCalibrVCalc->Left = Left2;
   btnCalibrVCalc->Top = Top1 + H2 + LSp1;
   btnCalibrVCalc->Width = BtnW2;
   btnCalibrVCalc->Height = H2;
   btnSpdCalibrTablePrint->Left = Left2;
   btnSpdCalibrTablePrint->Top = Top1 + H2 * 2 + LSp1 * 2;
   btnSpdCalibrTablePrint->Width = BtnW2;
   btnSpdCalibrTablePrint->Height = H2;
   leCurrentVSet->Left = Left11;
   leCurrentVSet->Top = Top1 + H2 * 2 + LSp1 - H3;
   leCurrentVSet->Width = LblW1;
   leCurrentVSet->Height = H3;
   leReadV->Left = Left12;
   leReadV->Top = Top1 + H2 * 2 + LSp1 - H3;
   leReadV->Width = LblW1;
   leReadV->Height = H3;
   leMeasuredV->Left = Left13;
   leMeasuredV->Top = Top1 + H2 * 2 + LSp1 - H3;
   leMeasuredV->Width = LblW1;
   leMeasuredV->Height = H3;
   btnNextCalibrV->Left = Left11;
   btnNextCalibrV->Top = Top1 + H2 * 2 + LSp1 * 2;
   btnNextCalibrV->Width = BtnW1;
   btnNextCalibrV->Height = H2;
   btnVCalibrDrumOn->Left = Left11;
   btnVCalibrDrumOn->Top = Top1 + H2 * 3 + LSp1 * 5;
   btnVCalibrDrumOn->Width = BtnW1;
   btnVCalibrDrumOn->Height = H2;
   btnVCalibrDrumOff->Left = Left11;
   btnVCalibrDrumOff->Top = Top1 + H2 * 4 + LSp1 * 6;
   btnVCalibrDrumOff->Width = BtnW1;
   btnVCalibrDrumOff->Height = H2;

   VS.Index = 0;
   leCurrentVSet->Text = FloatToStrF(VS.TargetV[0], ffFixed, 6, 2);
   leReadV->Text = FloatToStrF(VS.ReadoutV[0], ffFixed, 6, 2);
   leMeasuredV->Text = FloatToStrF(VS.MeasuredV[0], ffFixed, 6, 2);
   /* TGridRect myRect;
    myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=-1;
    sgSpeedCalibr->Selection=myRect; */
   btnPrevCalibrV->Enabled = false;
   btnNextCalibrV->Enabled = true;
   // LogPrint("CalibrTableVisibleRow="+String(sgSpeedCalibr->VisibleRowCount));
}
// ---- End of DesignSpdCalibrPanel ------------------------------------------

void TmfRB::ShowCommonParam(void) // отображение общих параметров
{
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
      return;

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   // если по поз. 1 идет испытание обрабатывать шаг
   auto &cmnp = inst_cpu.mCommonParams;
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   auto &gr2p1 = *inst_cpu.mPos1->mGr2;
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   if (mPosA.CurrSMode == 2)
   {
      if (mPosA.old_step != mPosA.cur_step)
      {
         mPosA.old_speed = mPosA.cur_speed;
         mPosA.old_dist = mPosA.cur_dist;
         mPosA.old_time = mPosA.cur_time;
         mPosA.old_load = mPosA.cur_load;
         mPosA.old_radius = mPosA.cur_radius;
         mPosA.old_temp = mPosA.cur_temp;
      }
      if (mPosA.cur_step > 1)
      {
         if (mPosA.mTyre.TestMode == 0)
         {
            stP2CParL1C1->Caption = AnsiString(dt::mSecToHMSStr(mPosA.old_time).c_str());
            stP2CParL2C1->Caption = FloatToStrF(mPosA.old_dist, ffFixed, 7, 2);
            stP2CParL3C1->Caption = FloatToStrF(mPosA.old_speed, ffFixed, 7, 2);
            stP2CParL4C1->Caption = FloatToStrF(mPosA.old_load, ffFixed, 7, 2);
            stP2CParL5C1->Caption = FloatToStrF(mPosA.old_temp, ffFixed, 5, 1);
            stP2CParL6C1->Caption = FloatToStrF(mPosA.old_radius, ffFixed, 5, 1);
            stP2CParL7C1->Caption = AnsiString(dt::mSecToHMSStr(gr1p1.next_step_time).c_str());
            stP2CParL1C2->Caption = "";
            stP2CParL2C2->Caption = "";
            stP2CParL3C2->Caption = "";
            stP2CParL4C2->Caption = "";
            stP2CParL5C2->Caption = "";
            stP2CParL6C2->Caption = "";
            stP2CParL7C2->Caption = "";
         }
         else
         {
            stP2CParL1C1->Caption = "";
            stP2CParL2C1->Caption = "";
            stP2CParL3C1->Caption = "";
            stP2CParL4C1->Caption = "";
            stP2CParL5C1->Caption = "";
            stP2CParL6C1->Caption = "";
            stP2CParL7C1->Caption = "";
            stP2CParL1C2->Caption = AnsiString(dt::mSecToHMSStr(mPosA.old_time).c_str());
            stP2CParL2C2->Caption = FloatToStrF(mPosA.old_dist, ffFixed, 7, 2);
            stP2CParL3C2->Caption = FloatToStrF(mPosA.old_speed, ffFixed, 7, 2);
            stP2CParL4C2->Caption = FloatToStrF(mPosA.old_load, ffFixed, 7, 2);
            stP2CParL5C2->Caption = FloatToStrF(mPosA.old_temp, ffFixed, 5, 1);
            stP2CParL6C2->Caption = FloatToStrF(mPosA.old_radius, ffFixed, 5, 1);
            stP2CParL7C2->Caption = FloatToStrF(gr2p1.next_step_distance, ffFixed, 7, 2);
         }
      }
      mPosA.old_step = mPosA.cur_step;
      if (mPosA.mTyre.TestMode == 0)
      {
         stP1CParL1C3->Caption = AnsiString(dt::mSecToHMSStr(gr2p1.next_set_time).c_str());
         // время след шага
      }
      else
      {
         stP1CParL2C3->Caption = FloatToStrF(gr2p1.next_set_distance,
         ffFixed, 7, 2); // путь след шага
      }
   }
   else // нет испытаний по поз.1
   {
      stP2CParL1C1->Caption = "";
      stP2CParL2C1->Caption = "";
      stP2CParL3C1->Caption = "";
      stP2CParL4C1->Caption = "";
      stP2CParL5C1->Caption = "";
      stP2CParL6C1->Caption = "";
      stP2CParL7C1->Caption = "";
      stP2CParL1C2->Caption = "";
      stP2CParL2C2->Caption = "";
      stP2CParL3C2->Caption = "";
      stP2CParL4C2->Caption = "";
      stP2CParL5C2->Caption = "";
      stP2CParL6C2->Caption = "";
      stP2CParL7C2->Caption = "";
      stP1CParL2C3->Caption = "";
      stP1CParL1C3->Caption = "";
   }

   // отображение на вкладке "ТЕКУЩЕЕ СОСТОЯНИЕ"
   if (pcRB->ActivePage == tsCurrentStatus)
   {
      stP1CurDate->Caption = Now().DateTimeString();
      if (mPosA.mTyre.TestMode == 0)
         stP1CParL1C1->Caption = AnsiString(dt::mSecToHMSStr(gr3p1.T_end_cycle).c_str());
      else
         stP1CParL1C1->Caption = "";
      stP1CParL1C2->Caption = AnsiString(dt::mSecToHMSStr(gr1p1.fakt_time).c_str());
      if (mPosA.mTyre.TestMode == 1)
         stP1CParL2C1->Caption = FloatToStrF(gr3p1.S_end_cycle, ffFixed, 7, 2);
      else
         stP1CParL2C1->Caption = "";
      stP1CParL2C2->Caption = FloatToStrF(gr2p1.fakt_distance, ffFixed, 7, 2);
      stP1CParL3C1->Caption = FloatToStrF(gr2p1.set_speed, ffFixed, 7, 2);
      stP1CParL3C2->Caption = FloatToStrF(cmnp.fakt_speed, ffFixed, 7, 2);
      stP1CParL3C3->Caption = FloatToStrF(gr2p1.next_speed, ffFixed, 7, 2);
      stP1CParL4C1->Caption = FloatToStrF(gr2p1.set_loading, ffFixed, 7, 2);
      stP1CParL4C2->Caption = FloatToStrF(gr2p1.fakt_loading, ffFixed, 7, 2);
      stP1CParL4C3->Caption = FloatToStrF(gr2p1.next_loading, ffFixed, 7, 2);
      stP1CParL6C2->Caption = FloatToStrF(gr2p1.fakt_temper, ffFixed, 5, 1);
      stP1CParL7C2->Caption = FloatToStrF(gr2p1.fakt_radius, ffFixed, 5, 1);
      stP1CParL8C1->Caption = String(gr1p1.step_change);
      stP1CParL8C3->Caption = String(gr1p1.next_step_change);
   }
   // отображение на вкладке "РУЧНОЙ РЕЖИМ"
   if (pcRB->ActivePage == tsManual)
   {
      leCurrentDrumSpeed->Text = FloatToStrF(cmnp.fakt_speed, ffFixed, 6, 2);
      tbCurrentDrumSpeed->Position = tbCurrentDrumSpeed->Max -static_cast<int>(cmnp.fakt_speed);
      leCurrentLoad1->Text = FloatToStrF(gr2p1.fakt_loading, ffFixed, 7, 2);
      tbCurrentLoad1->Position = tbCurrentLoad1->Max -static_cast<int>(gr2p1.fakt_loading);
      leCurrentT1->Text = FloatToStrF(gr2p1.fakt_temper, ffFixed, 5, 1);
      leCurrentR1->Text = FloatToStrF(gr2p1.fakt_radius, ffFixed, 5, 1);
   }
   // отображение на вкладке "АТТЕСТАЦИЯ"
   if (pcRB->ActivePage == tsCalibration)
   {
      if (pcCalibration->ActivePage == tsSpeedCalibr)
      {
         /* if(*DrumOn) */
         leReadV->Text = FloatToStrF(cmnp.fakt_speed, ffFixed, 6, 2);
         // else       leReadV->Text="0.0";
      }
      else if (pcCalibration->ActivePage == tsLoadCalibr)
      {
         /* if(*KeepLoad1) */
         leReadLoadA->Text = FloatToStrF(gr2p1.fakt_loading, ffFixed, 6, 2);
         // else          leReadLoadA->Text="0.0";
      }
      else if (pcCalibration->ActivePage == tsRadiusCalibr)
      {
         leReadRA->Text = FloatToStrF(gr2p1.fakt_radius, ffFixed, 6, 2); //
      }
      else if (pcCalibration->ActivePage == tsTempCalibr)
      {
         leReadTA->Text = FloatToStrF(gr2p1.fakt_temper, ffFixed, 6, 2); //
      }
   }
   // отображение на вкладке "КАЛИБРОВКА"
   if (pcRB->ActivePage == tsSert)
   {
      if (pcSert->ActivePage == tsLoadSert)
      {
         /* if(*KeepLoad1) */
         leReadLoadSertA->Text = FloatToStrF(gr2p1.fakt_loading, ffFixed, 6, 2);
         // else          leReadLoadSertA->Text="0.0";
      }
      if (pcSert->ActivePage == tsDrumSpeedSert)
      {
         leMeasSpeedCoefReal->Text =
            FloatToStrF(gr3p1.CorrMeasSpeed, ffFixed, 4, 3);
         leSetSpeedCoefReal->Text = FloatToStrF(gr3p1.CorrSetSpeed, ffFixed, 4, 3);
      }
   }
   // отображение на вкладке "Программа испытаний"
   if (pcRB->ActivePage == tsManual)
   {
      if (!leSetLoad1->Focused())
      {
         tbCurrentLoad1->SelEnd = tbCurrentLoad1->Max -static_cast<int>(gr1p1.ReadLoading);
         tbCurrentLoad1->SelStart = tbCurrentLoad1->Max -static_cast<int>(gr1p1.ReadLoading);
         leSetLoad1->Text = FloatToStrF(gr1p1.ReadLoading, ffFixed, 5, 2);
      }
   }
   // аварийные установки
   if (pcRB->ActivePage == tsEmSettings)
   {
      leEmMaxLoad_1->Text = FloatToStrF(gr1p1.max_load, ffFixed, 5, 1);
      leEmMaxSpeed->Text = FloatToStrF(cmnp.max_speed, ffFixed, 5, 1);
      leEmMinSpeed->Text = FloatToStrF(cmnp.min_speed, ffFixed, 5, 1);
      leEmMinLoad_1->Text = FloatToStrF(gr1p1.min_load, ffFixed, 5, 1);

      leEmMinTemp_1->Text = FloatToStrF(gr1p1.min_temp, ffFixed, 5, 1);

      leEmMaxTemp_1->Text = FloatToStrF(gr1p1.max_temp, ffFixed, 5, 1);
   }
}

// ---- End of ShowCommonParam -----------------------------------------------
void __fastcall TmfRB::onOPCControlStartExec(TObject *Sender)
{
   OPCControlStartExec();
}

void __fastcall TmfRB::OPCControlStartExec(void)
{
   LogPrint( "Старт управления стендом");
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      LogPrint( "Ошибка соединения со стендом", clRed);
      sbRB->Panels->Items[0]->Text = "Ошибка соединения со стендом";
      MessageBoxW(Handle, L"Ошибка соединения со стендом",
         L"Ошибка соединения со стендом", MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
      return;
   }

   if ( !ShowTimer->Enabled )
   {
      std::lock_guard<std::recursive_mutex> lock( mCPUMutex );

      sbRB->Panels->Items[0]->Text = "Соединение со стендом установлено";
      // прочитать состояние и установить состояние на панели
      auto &gr1p1 = *inst_cpu.mPos1->mGr1;
      gr1p1.Read();

      // определение и печать текущих режимов
      mPosA.old_step = gr1p1.step_write;
      mPosA.CurrMode = BUnion(gr1p1.AutoMode, gr1p1.ManualMode);
      mPosA.CurrSMode = BUnion(gr1p1.Start, gr1p1.Stop);
      LogPrint( "First mPosA.CurrMode=" + String(mPosA.CurrMode), clSkyBlue);
      LogPrint( "First mPosA.CurrSMode=" + String(mPosA.CurrSMode),
         clSkyBlue);
      LogPrint( "First Auto1: " + BoolToStr(gr1p1.AutoMode, true) +
         ", Man1: " + BoolToStr(gr1p1.ManualMode, true), clSkyBlue);
      LogPrint( "First Start1: " + BoolToStr(gr1p1.Start, true) +
         ", Stop1: " + BoolToStr(gr1p1.Stop, true), clSkyBlue);
      // запрещение обработчика кнопок
      // Handle1On=false;
      // Handle2On=false;
      // обработка считанных режимов, в случае недопустимой комбинации - их изменение
      if ((gr1p1.AutoMode && gr1p1.ManualMode) || (!gr1p1.AutoMode && !gr1p1.ManualMode))
      {
         gr1p1.AutoMode = false;
         gr1p1.ManualMode = true;
         gr1p1.Start = false;
         gr1p1.Stop = true;
         gr1p1.Write();
      }
      // печать текущих режимов
      if (gr1p1.AutoMode)
         LogPrint( "Поз. А в автоматическом режиме!", clWhite);
      else
         LogPrint( "Поз. А в ручном режиме!", clWhite);
      if (gr1p1.Start)
         LogPrint( "Поз. А в режиме Старт!", clWhite);
      else
         LogPrint( "Поз. А в режиме Стоп!", clWhite);

      // сохранение текущих режимов
      mPosA.OldMode = mPosA.CurrMode;
      mPosA.OldSMode = mPosA.CurrSMode;
      // отображение состояния и текущих параметров
      ShowStatus(false);
      ShowCommonParam();
      // запуск цикла опроса
      ShowTimer->Enabled = true;
      // разрешение обработчиков
   }
   else
   {
      sbRB->Panels->Items[2]->Text = "Control alredy ON!";
   }
}

void TmfRB::CheckStend(void)
{
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!(inst_cpu.IsConnected() && ShowTimer->Enabled))
   { // соединение со стендом
      OPCControlStartExec();
   }
}

// ---- End of OnOPCControlStartExec -----------------------------------------
void TmfRB::ShowStatus(bool save) // отображение состояния на панелях
{
   auto& inst_cpu = cpu::CpuMemory::Instance();
   static bool oldstate = false;
   SetIndication(eStendConnection, inst_cpu.IsConnected());
   if (oldstate != inst_cpu.IsConnected()) // запись в логах изменения состояния
   {
      if (inst_cpu.IsConnected())
      { // соединение установлено
         LogPrint( "Соединение со стендом установлено", clRed);
      }
      else
      { // соединение потеряно
         LogPrint( "Соединение со стендом потеряно", clRed);
      }
   }
   oldstate = inst_cpu.IsConnected(); // запоминание текущего состояния связи


   if (!inst_cpu.IsConnected())
      return;

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   auto &cmnp = inst_cpu.mCommonParams;
   sbRB->Panels->Items[3]->Text = Now().DateTimeString();
   // определение текущих режимов
   mPosA.CurrMode = BUnion(gr1p1.AutoMode, gr1p1.ManualMode);
   mPosA.CurrSMode = BUnion(gr1p1.Start, gr1p1.Stop);
   // печать в случае изменения режима
   if (mPosA.CurrMode != mPosA.OldMode)
   {
      LogPrint( "Auto1: " + BoolToStr(gr1p1.AutoMode, true) +
         ", Man1: " + BoolToStr(gr1p1.ManualMode, true));
      if (gr1p1.AutoMode)
         sbRB->Panels->Items[2]->Text = "Поз. А в автоматическом режиме!";
      else
         sbRB->Panels->Items[2]->Text = "Поз. А в ручном режиме!";
   }
   if (mPosA.CurrSMode != mPosA.OldSMode)
   {
      LogPrint( "Start1: " + BoolToStr(gr1p1.Start, true) +
         ", Stop1: " + BoolToStr(gr1p1.Stop, true));
      if (gr1p1.Start)
         sbRB->Panels->Items[2]->Text = "Старт поз. А!";
      else
         sbRB->Panels->Items[2]->Text = "Стоп поз. А!";
   }

   sbManualA->Down = gr1p1.ManualMode;
   sbAutomatA->Down = gr1p1.AutoMode;
   rgPos1StartStop->Enabled = gr1p1.AutoMode;
   sbStartA->Enabled = gr1p1.AutoMode;
   sbStopA->Enabled = gr1p1.AutoMode;
   sbStartA->Down = gr1p1.Start;
   sbStopA->Down = gr1p1.Stop;
   cbControlLateralA->Checked = gr1p1.ControlLateral;
   if (gr1p1.Stop && mPosA.needSave && save)
   {
      mPosA.mTyre.Stop = dt::Now();
      btnLoadTestResPosA->Click(); // авто сохраниние
   }
   // обработка остальных индикаторов

   sbCarr1Fm->Down = gr1p1.CarriageFrom;
   sbCarr1To->Down = gr1p1.CarriageTo;
   sbDrumOn->Down = cmnp.DrumOn;

   SetIndication(IndBlowout1, !gr1p1.Blowout);
   SetIndication(IndGuardrail1, gr1p1.GuardRail);
   static bool oldBlowout1 = gr1p1.Blowout;
   // инициализация тем что пришло с контроллера
   if (gr1p1.Blowout == true && oldBlowout1 != gr1p1.Blowout) // произошол разрыв
   {
      String msg = "Разрыв в позиции А";
      if (gr1p1.DestroyLateral)
      {
         msg = "Разрыв боковой в позиции А";
      }
      if (gr1p1.DestroyRunning)
      {
         msg = "Разрыв беговой в позиции А";
      }
      sbRB->Panels->Items[2]->Text = msg;
      LogPrint(Now().TimeString() + "--" + msg, clRed);
   }

   oldBlowout1 = gr1p1.Blowout;
   SetIndication(IndDestroyLateral1, !gr1p1.DestroyLateral);
   SetIndication(IndDestroyRunning1, !gr1p1.DestroyRunning);

   SetIndication(IndOilLvl, cmnp.OilLvl);
   SetIndication(IndlOilFilter, cmnp.OilFilter);
   SetIndication(IndDriveDrum, cmnp.ElDriveDrum);

   eOilTemp->Text = FloatToStrF(cmnp.OilTemp, ffGeneral, 3, 3);
   if (cmnp.OilTemp < LOWTEMP)
   {
      eOilTemp->Color = clSkyBlue;
   }
   else if (cmnp.OilTemp > HIGHTTEMP)
   {
      eOilTemp->Color = clRed;
   }
   else
   {
      eOilTemp->Color = clGreen;
   }
   if (!sbCarriage1Off->Down && gr1p1.CarriageOff && !mPosA.switch_Carriage)
   {
      sbRB->Panels->Items[2]->Text = "Каретка А в исходном положении!";
      LogPrint( "Каретка А в исходном положении!", clWhite);
   }
   sbCarriage1Off->Down = gr1p1.CarriageOff;
   mPosA.switch_Carriage = gr1p1.CarriageOff;

   // сохранение режимов
   mPosA.OldMode = mPosA.CurrMode;
   mPosA.OldSMode = mPosA.CurrSMode;

   static bool over_load1(false);

   if (gr1p1.OverLoad != over_load1)
   {
      if (gr1p1.OverLoad)
      {
         sbRB->Panels->Items[2]->Text =
            "Превышение нагрузки на шаге на стороне 1";
         LogPrint( "Превышение нагрузки на шаге на стороне 1",
            clYellow);
         ShowMessage("Превышение нагрузки на шаге на стороне 1");
      }
      over_load1 = gr1p1.OverLoad;
   }
}
// ---- End of ShowStatus ----------------------------------------------------

void __fastcall TmfRB::OnOPCControlStopExec(TObject *Sender)
{
   LogPrint( "OPC Control OFF!", clAqua);
   ShowTimer->Enabled = false;
   sbRB->Panels->Items[0]->Text = "Соединения со стендом нет";
}
// ---- End of OnOPCControlStopExec ------------------------------------------

void __fastcall TmfRB::OnReadCycleTimer(TObject */*Sender*/)
{
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
      return;

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   auto &gr2p1 = *inst_cpu.mPos1->mGr2;
   auto &cmnp = inst_cpu.mCommonParams;

   inst_cpu.ReadCycleParameters();
   sbRB->Panels->Items[1]->Text = "Cnt=" + String(++mCount);
   if (mPosA.CurrSMode == 2)
   {
      mPosA.cur_speed = cmnp.fakt_speed;
      mPosA.cur_dist = gr2p1.fakt_distance;
      mPosA.cur_time = gr1p1.fakt_time;
      mPosA.cur_load = gr2p1.fakt_loading;
      mPosA.cur_radius = gr2p1.fakt_radius;
      mPosA.cur_temp = gr2p1.fakt_temper;
      mPosA.cur_step = gr1p1.step_write;
   }

   ShowStatus();
   ShowCommonParam();
}

void TmfRB::ClearStepVals1(void)
{
   mPosA.cur_speed = 0.0;
   mPosA.cur_dist = 0.0;
   mPosA.cur_time = 0.0;
   mPosA.cur_load = 0.0;
   mPosA.cur_radius = 0.0;
   mPosA.cur_temp = 0.0;
   mPosA.cur_step = 0;

   mPosA.old_step = 0;
   mPosA.old_speed = 0.0;
   mPosA.old_dist = 0.0;
   mPosA.old_time = 0.0;
   mPosA.old_load = 0.0;
   mPosA.old_radius = 0.0;
   mPosA.old_temp = 0.0;
}

// ---- End of OnReadCycleTimer ----------------------------------------------

void __fastcall TmfRB::OnRGPos1ModeClick(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbAutomatA->Down = false;
      sbManualA->Down = true;
      sbRB->Panels->Items[2]->Text = "Нельзя выдать команду - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   if (sbAutomatA->Down && !sbManualA->Down)
   {
      gr1p1.AutoMode = true;
      gr1p1.ManualMode = false;
      sbRB->Panels->Items[2]->Text = "Поз. А в автоматическом режиме!";
      LogPrint( "Поз. А в автоматическом режиме!", clWhite);
   }
   else
   {
      gr1p1.AutoMode = false;
      gr1p1.ManualMode = true;
      sbRB->Panels->Items[2]->Text = "Поз. А в ручном режиме!";
      LogPrint( "Поз. А в ручном режиме!", clWhite);
   }
   gr1p1.Write();

}
// ---- End of OnRGPos1ModeClick ---------------------------------------------

void __fastcall TmfRB::OnRGPos1StartStopClick(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbStartA->Down = false;
      sbStopA->Down = true;
      sbRB->Panels->Items[2]->Text = "Нельзя выдать команду - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   if (sbStartA->Down && !sbStopA->Down)
   {
      gr1p1.Start = true;
      gr1p1.Stop = false;
      mPosA.needSave = true;
      ClearStepVals1();
      UpdateProgData();
      if (mPosA.mTyre.Start == dt::DateTime())
         mPosA.mTyre.Start = dt::Now();
      mPosA.mTyre.Stop = dt::DateTime();
      sbRB->Panels->Items[2]->Text = "Старт поз. А!";
      LogPrint( "Старт поз. А!", clWhite);
   }
   else
   {
      gr1p1.Start = false;
      gr1p1.Stop = true;
      if (mPosA.needSave)
      {
         mPosA.mTyre.Stop = dt::Now();
         btnLoadTestResPosA->Click(); // авто сохраниние
      }
      sbRB->Panels->Items[2]->Text = "Стоп поз. А!";
      LogPrint( "Стоп поз. А!", clWhite);
   }
   gr1p1.Write();
}

// ---- End of OnRGPos1StartStopClick ----------------------------------------
void __fastcall TmfRB::cbControlLateralAClick(TObject *Sender)
{ // вкл/выкл контроля бокового разрыва поз А
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
      return;

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   gr1p1.ControlLateral = cbControlLateralA->Checked;
   gr1p1.Write();
}

void __fastcall TmfRB::OnDrumOn(TObject *Sender)
{

   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя включить барабан - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &cmnp = inst_cpu.mCommonParams;
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   if (gr1p1.ManualMode)
   {
      cmnp.DrumOn = true;
      cmnp.DrumOff = false;
      if (pcRB->ActivePage == tsManual)
      {
         double t = leSetDrumSpeed->Text.Trim().ToDouble();
         if (CheckSpeed(t))
         {
            cmnp.DrumSpeed = t;
         }
         else
         {
            MessageBox(Handle,
               _T("Значение скорости должно быть в пределах от MIN_SPEED до MAX_SPEED")
               , _T("Ошибка"), MB_ICONERROR | MB_OK);
            return;
         }

         tbCurrentDrumSpeed->SelEnd = tbCurrentDrumSpeed->Max -static_cast<int>(cmnp.DrumSpeed);
         tbCurrentDrumSpeed->SelStart = tbCurrentDrumSpeed->Max -static_cast<int>(cmnp.DrumSpeed);
      }
      if (pcRB->ActivePage == tsCalibration)
      {
         if (pcCalibration->ActivePage == tsSpeedCalibr)
         {
            cmnp.DrumSpeed = VS.TargetV[VS.Index];
         }
      }
      cmnp.Write();
      sbRB->Panels->Items[2]->Text = "Барабан включен!";
      LogPrint( "Барабан включен");
   }
   else
   {
      sbRB->Panels->Items[2]->Text =
         "Барабан не включен - стенд не в ручном режиме!";
   }

}
// ---------------------------------------------------------------------------
void __fastcall TmfRB::OnDrumOff(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя выключить барабан - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &cmnp = inst_cpu.mCommonParams;
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   if (gr1p1.ManualMode)
   {
      cmnp.DrumOn = false;
      cmnp.DrumOff = true;
      cmnp.Write();
      sbRB->Panels->Items[2]->Text = "Барабан выключен!";
      LogPrint( "Барабан выключен");
   }
   else
   {
      sbRB->Panels->Items[2]->Text =
         "Барабан не выключен - стенд не в ручном режиме!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnCarriage1To(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя включить каретку А - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   if (gr1p1.ManualMode)
   {
      double t = leSetLoad1->Text.Trim().ToDouble();
      if (CheckLoad(t))
         gr3p1.Loading = t;
      else
      {
         MessageBox(Handle,
            _T("Значение нагрузки должно быть в пределах от 0 до 115"),
            _T("Ошибка"), MB_ICONERROR | MB_OK);
         return;
      }
      tbCurrentLoad1->SelEnd = tbCurrentLoad1->Max -static_cast<int>(gr3p1.Loading);
      tbCurrentLoad1->SelStart = tbCurrentLoad1->Max -static_cast<int>(gr3p1.Loading);
      gr1p1.CarriageTo = true;
      gr1p1.CarriageFrom = false;
      sbCarr1Fm->Down = gr1p1.CarriageFrom;
      sbCarr1To->Down = gr1p1.CarriageTo;
      gr3p1.Write();
      gr1p1.Write();
      sbRB->Panels->Items[2]->Text = "Каретка А движется к барабану!";
      LogPrint(
         "Ручной режим, каретка 1 к барабану, установлена нагрузка=" +
         FloatToStr(gr3p1.Loading));
   }
   else
   {
      sbRB->Panels->Items[2]->Text =
         "Каретка А не включена - стенд не в ручном режиме!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnCarriage1From(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя включить каретку А - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   if (gr1p1.ManualMode)
   {
      double t = leSetLoad1->Text.Trim().ToDouble();
      if (CheckLoad(t))
         gr3p1.Loading = t;
      else
      {
         MessageBox(Handle,
            _T("Значение нагрузки должно быть в пределах от 0 до 115"),
            _T("Ошибка"), MB_ICONERROR | MB_OK);
         return;
      }
      tbCurrentLoad1->SelEnd = tbCurrentLoad1->Max -static_cast<int>(gr3p1.Loading);
      tbCurrentLoad1->SelStart = tbCurrentLoad1->Max -static_cast<int>(gr3p1.Loading);
      gr1p1.CarriageTo = false;
      gr1p1.CarriageFrom = true;
      sbCarr1Fm->Down = gr1p1.CarriageFrom;
      sbCarr1To->Down = gr1p1.CarriageTo;
      gr3p1.Write();
      gr1p1.Write();
      sbRB->Panels->Items[2]->Text = "Каретка А движется от барабана!";
      LogPrint(
         "Ручной режим, каретка 1 от барабана, установлена нагрузка=" +
         FloatToStr(gr3p1.Loading));
   }
   else
   {
      sbRB->Panels->Items[2]->Text =
         "Каретка А не включена - стенд не в ручном режиме!";
   }

}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnCarriage1Stop(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя остановить каретку А - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   if (gr1p1.ManualMode)
   {
      gr1p1.CarriageTo = false;
      gr1p1.CarriageFrom = false;
      sbCarr1Fm->Down = gr1p1.CarriageFrom;
      sbCarr1To->Down = gr1p1.CarriageTo;
      gr1p1.Write();
      sbRB->Panels->Items[2]->Text = "Каретка А остановлена!";
      LogPrint( "Ручной режим, каретка 1 остановлена");
   }
   else
   {
      sbRB->Panels->Items[2]->Text =
         "Каретка А не остановлена - стенд не в ручном режиме!";
   }

}
// --------------------------------------------------------------------------

void __fastcall TmfRB::OnGeneralStop(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя остановить стенд - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   // *Reset1=true;  *Reset2=true;
   gr1p1.Start = false;
   gr1p1.Stop = true;
   sbRB->Panels->Items[2]->Text = "Стенд остановлен!";
   LogPrint( "Общая остановка стенда!");

}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnTestModeChange(TObject *Sender)
{
   if (cmbTestMode->ItemIndex == 0)
   {
      leTestTimePath->EditLabel->Caption = "Время обкатки, ч: ";
   }
   else
   {
      leTestTimePath->EditLabel->Caption = "Путь обкатки, км: ";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnMainFormCreate(TObject *Sender)
{
   mfRB->Left = 0;
   mfRB->Top = 0;
   mfRB->Height = MFHEIGHT;
   mfRB->Width = MFWIDTH;
   tsCurrentStatusH = tsCurrentStatus->Height;
   tsCurrentStatusW = tsCurrentStatus->Width;
   pParam1Height = pParam1->Height;
   pParam1Width = pParam1->Width;
   pParam2Height = pParam2->Height;
   pParam2Width = pParam2->Width;
   tsManualHeight = tsManual->Height;
   tsManualWidth = tsManual->Width;
   tsTimeProgHeight = tsTimeProg->Height;
   tsTimeProgWidth = tsTimeProg->Width;
   tsSProgHeight = tsSProg->Height;
   tsSProgWidth = tsSProg->Width;
   tsNewProtHeight = tsNewProtocol->Height;
   tsNewProtWidth = tsNewProtocol->Width;
   tsProtocolAHeight = tsProtocolA->Height;
   tsProtocolAWidth = tsProtocolA->Width;
   tsSpeedCalibrH = tsSpeedCalibr->Height;
   tsSpeedCalibrW = tsSpeedCalibr->Width;
   tsLoadCalibrAH = tsLoadCalibrA->Height;
   tsLoadCalibrAW = tsLoadCalibrA->Width;
   tsTCalibrAH = tsTCalibrA->Height;
   tsTCalibrAW = tsTCalibrA->Width;
   tsRCalibrAH = tsRCalibrA->Height;
   tsRCalibrAW = tsRCalibrA->Width;
   tsLoadSertAH = tsLoadSertA->Height;
   tsLoadSertAW = tsLoadSertA->Width;
   DesignNewProtPanel();
   DesignProtAPanel();
   DesignSProgTable();
   DesignTProgTable();
   DesignCmmnParPanel();
   DesignManualPanel();
   DesignLoadSertAPanel();
   DesignLoadCalibrAPanel();
   DesignRCalibrAPanel();
   DesignTCalibrAPanel();
   DesignSpdCalibrPanel();
   DesignTSertPanel();
   DesignRSertPanel();
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnSProgFileOpen(TObject *Sender)
{
   PathPrg.SProgFName = AnsiString(acSProgFileOpen->Dialog->FileName).c_str();
   LogPrint("Загрузить программу по пути из файла \"" + AnsiString(PathPrg.SProgFName.c_str()) + "\"!",
      clAqua);
   PathPrg.Load();
   ShowSProg();
   btnCheckSProg->Enabled = false;
   btnSaveSProgToFile->Enabled = true;
   btnLoadSProgToPosA->Enabled = true;
   sbRB->Panels->Items[2]->Text = "Программа по пути загружена из файла \"" +
      FileNameParse(AnsiString(PathPrg.SProgFName.c_str())) + "\"!";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnSProgFileSaveAs(TObject *Sender)
{ // Сохранить в файле программу по пути
   // проверка вызывающего действия
   if (Sender == acSProgFileSaveAs)
   { // ручное сохранение
      PathPrg.SProgFName = AnsiString(acSProgFileSaveAs->Dialog->FileName).c_str();
      acSProgFileSaveAs->Dialog->FileName = "";
   }
   else
   { // автосейв
      PathPrg.SProgFName = AnsiString(mData.strDistProg.c_str() + Now().FormatString
         ("yyyy_mm_dd_hh_nn_ss'.sprg'")).c_str();
   }
   LogPrint("Сохранить программу по пути в файле \"" + AnsiString(PathPrg.SProgFName.c_str()) + "\"!",
      clAqua);
   PathPrg.Save();
   sbRB->Panels->Items[2]->Text = "Программа по пути сохранена в файле \"" +
      FileNameParse(AnsiString(PathPrg.SProgFName.c_str())) + "\"";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadSProgToPosA(TObject *Sender)
{
   if (!CheckProgLoad(sgSProgram, 1, 10.0))
   {
      return;
   }
   LogPrint("Загрузка программы по пути в поз. А!", clAqua);

   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Недьзя загрузить программу по пути в поз. А - нет связи со станком!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   sbRB->Panels->Items[2]->Text = "Загрузка программы по пути в поз. А!";
   // читаем программу из ячеек и загружаем в контроллер поз. А
   auto &gr4 = *inst_cpu.mPos1->mGr4;
   auto &gr6 = *inst_cpu.mPos1->mGr6;
   PathPrg.ToCpu( gr4, gr6 );
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   mPosA.RunProgName = PathPrg.SProgName;
   SetCurrProgA(mPosA.RunProgName);
   stP1L2ProgNameA->Caption = AnsiString(mPosA.RunProgName.c_str());
   mPosA.mTyre.InitPressure = StrToFlt(leSTyrePressure->Text);
   gr3p1.S_end_cycle = mPosA.mTyre.TotalS = StrToFlt(leTotalTestS->Text);
   gr3p1.T_end_cycle = mPosA.mTyre.TotalTime = 0;
   gr3p1.type_cycle = mPosA.mTyre.TestMode = 1;
   gr3p1.StepsQty = mPosA.mTyre.StepsNo = StrToInt(leSTotalStepsQty->Text);
   gr3p1.PollsQty = mPosA.mTyre.PollsNo = StrToInt(leSPollingTotalQty->Text);
   LogPrint( "Программа по пути, поз. А: путь=" +
      FloatToStrF(gr3p1.S_end_cycle, ffFixed, 9, 2) + ", шагов программы=" +
      String(gr3p1.StepsQty) + ", опросов=" + String(gr3p1.PollsQty));

   gr3p1.Write();
   gr4.Write();
   gr6.Write();
   LogPrint( "Программа по пути загружена в поз. А!");
   sbRB->Panels->Items[2]->Text = "Программа по пути загружена в поз. А!";
}
// ---------------------------------------------------------------------------

void TmfRB::DesignTProgTable(void)
   // создание таблицы для ввода программы испытаний по времени
{
   const int Col0Width = 30, Col1Width = 80, Col2Width = 105, Col3Width = 67,
      Col4Width = 30;
   const int pHeight = 26, pH = 24, LSp = 10;
   int Left1 = leTTyrePressure->EditLabel->Width + LSp, Top1 = pHeight + LSp,
      Top2 = pHeight + pH + LSp * 2, Width2 = 50;
   int Left2 = leTTotalStepsQty->EditLabel->Width + Left1 + Width2 + LSp,
      Width3 = tsTimeProgWidth / 14;
   if (Width3 < 66)
      Width3 = 66;
   int Width1 = Left2 + Width2 - Left1;
   int Left3 = Left1 + Width1 + leTotalTestTime->EditLabel->Width + LSp;
   pTProgTtl->Left = 0;
   pTProgTtl->Top = 0;
   pTProgTtl->Width = tsTimeProgWidth;
   pTProgTtl->Height = pHeight;

   leTProgName->Left = Left1;
   leTProgName->Top = Top1;
   leTProgName->Width = Width1;
   leTProgName->Height = pH;
   leTotalTestTime->Left = Left3;
   leTotalTestTime->Top = Top1;
   leTotalTestTime->Width = Width3;
   leTotalTestTime->Height = pH;
   leTTyrePressure->Left = Left1;
   leTTyrePressure->Top = Top2;
   leTTyrePressure->Width = Width2;
   leTTyrePressure->Height = pH;
   leTTotalStepsQty->Left = Left2;
   leTTotalStepsQty->Top = Top2;
   leTTotalStepsQty->Width = Width2;
   leTTotalStepsQty->Height = pH;
   leTPollingTotalQty->Left = Left3;
   leTPollingTotalQty->Top = Top2;
   leTPollingTotalQty->Width = Width3;
   lTProgTblNme->Top = Top2 + pH + LSp;
   sgTProgram->Top = Top2 + pH * 2 + LSp;
   sgTProgram->Left = tsTimeProgWidth / 20;

   int TTableWidth = Col0Width + Col1Width + Col2Width + Col3Width +
      Col4Width + 30;
   lTProgTblNme->Left = (TTableWidth - lTProgTblNme->Width) / 2 +
      sgTProgram->Left;
   sgTProgram->Width = TTableWidth;
   int TTableHeight = tsTimeProgHeight - sgTProgram->Top - 5;
   int RowNo = TTableHeight / (sgTProgram->RowHeights[0] + 1);
   TTableHeight = RowNo * sgTProgram->RowHeights[0] + RowNo;
   sgTProgram->Height = TTableHeight;
   sgTProgram->ColWidths[0] = Col0Width;
   sgTProgram->ColWidths[1] = Col1Width;
   sgTProgram->ColWidths[2] = Col2Width;
   sgTProgram->ColWidths[3] = Col3Width;
   sgTProgram->ColWidths[4] = Col4Width;
   sgTProgram->Cells[0][0] = "№";
   sgTProgram->Cells[1][0] = "Нагрузка, кН";
   sgTProgram->Cells[2][0] = "Скорость, км/час";
   sgTProgram->Cells[3][0] = "Время, час";
   sgTProgram->Cells[4][0] = "мин";
   for (int i = 0; i < MAXNUMOFSTEPS; i++)
   {
      if (i < 9)
         sgTProgram->Cells[0][i + 1] = "  " + String(i + 1) + ":";
      else if (i < 99)
         sgTProgram->Cells[0][i + 1] = " " + String(i + 1) + ":";
      else
         sgTProgram->Cells[0][i + 1] = String(i + 1) + ":";
   }
   lTPollingTblNme1->Top = lTProgTblNme->Top;
   sgTPolling->Left = sgTProgram->Left + TTableWidth + 40;
   sgTPolling->Top = sgTProgram->Top;
   sgTPolling->ColWidths[0] = Col0Width;
   sgTPolling->ColWidths[1] = Col3Width;
   sgTPolling->ColWidths[2] = Col4Width;
   int TPollTableWidth = Col0Width + Col3Width + Col4Width + 30;
   lTPollingTblNme1->Left = (TPollTableWidth - lTPollingTblNme1->Width) / 2 +
      sgTPolling->Left;
   sgTPolling->Width = TPollTableWidth;
   sgTPolling->Height = TTableHeight;
   sgTPolling->Cells[0][0] = "№";
   sgTPolling->Cells[1][0] = "Время, час";
   sgTPolling->Cells[2][0] = "мин";
   for (int i = 0; i < MAXNUMOFPOLLS; i++)
   {
      if (i < 9)
         sgTPolling->Cells[0][i + 1] = "  " + String(i + 1) + ":";
      else if (i < 99)
         sgTPolling->Cells[0][i + 1] = " " + String(i + 1) + ":";
      else
         sgTPolling->Cells[0][i + 1] = String(i + 1) + ":";
   }
   int btnLeft = sgTPolling->Left + TPollTableWidth + 10;
   int btnWidth = tsTimeProgWidth - btnLeft - 10;
   int btnHeight = 50;
   btnNewTProg->Left = btnLeft;
   btnCheckTProg->Left = btnLeft;
   btnSaveTProgToFile->Left = btnLeft;
   btnOpenTProgFmFile->Left = btnLeft;
   btnLoadTProgToPosA->Left = btnLeft;
   btnNewTProg->Width = btnWidth;
   btnCheckTProg->Width = btnWidth;
   btnSaveTProgToFile->Width = btnWidth;
   btnOpenTProgFmFile->Width = btnWidth;
   btnLoadTProgToPosA->Width = btnWidth;
   btnNewTProg->Height = btnHeight;
   btnCheckTProg->Height = btnHeight;
   btnSaveTProgToFile->Height = btnHeight;
   btnOpenTProgFmFile->Height = btnHeight;
   btnLoadTProgToPosA->Height = btnHeight;
   btnNewTProg->Top = sgTProgram->Top;
   btnCheckTProg->Top = btnNewTProg->Top + btnHeight + 10;
   btnSaveTProgToFile->Top = btnCheckTProg->Top + btnHeight + 10;
   btnOpenTProgFmFile->Top = btnSaveTProgToFile->Top + btnHeight + 10;
   btnLoadTProgToPosA->Top = btnOpenTProgFmFile->Top + btnHeight + 10;

   btnCheckTProg->Enabled = false;
   btnSaveTProgToFile->Enabled = false;
   btnLoadTProgToPosA->Enabled = false;
}
// ---- End of DesignTProgTabe -----------------------------------------------

void __fastcall TmfRB::OnMFResize(TObject *Sender)
{
   if (closing)
   {
      return;
   } // смысл перерисовывать если программа закрывается
   // Handle1On=false;
   // Handle2On=false;
   tsCurrentStatusH = tsCurrentStatus->Height;
   tsCurrentStatusW = tsCurrentStatus->Width;
   pParam1Height = pParam1->Height;
   pParam1Width = pParam1->Width;
   pParam2Height = pParam2->Height;
   pParam2Width = pParam2->Width;
   tsManualHeight = tsManual->Height;
   tsManualWidth = tsManual->Width;
   tsTimeProgHeight = tsTimeProg->Height;
   tsTimeProgWidth = tsTimeProg->Width;
   tsSProgHeight = tsSProg->Height;
   tsSProgWidth = tsSProg->Width;
   tsNewProtHeight = tsNewProtocol->Height;
   tsNewProtWidth = tsNewProtocol->Width;
   tsProtocolAHeight = tsProtocolA->Height;
   tsProtocolAWidth = tsProtocolA->Width;
   tsSpeedCalibrH = tsSpeedCalibr->Height;
   tsSpeedCalibrW = tsSpeedCalibr->Width;
   tsLoadCalibrAH = tsLoadCalibrA->Height;
   tsLoadCalibrAW = tsLoadCalibrA->Width;
   tsTCalibrAH = tsTCalibrA->Height;
   tsTCalibrAW = tsTCalibrA->Width;
   tsRCalibrAH = tsRCalibrA->Height;
   tsRCalibrAW = tsRCalibrA->Width;
   tsLoadSertAH = tsLoadSertA->Height;
   tsLoadSertAW = tsLoadSertA->Width;
   DesignNewProtPanel();
   DesignProtAPanel();
   DesignTProgTable();
   DesignSProgTable();
   DesignCmmnParPanel();
   DesignManualPanel();
   DesignLoadSertAPanel();
   DesignLoadCalibrAPanel();
   DesignRCalibrAPanel();
   DesignTCalibrAPanel();
   DesignSpdCalibrPanel();
   DesignTSertPanel();
   DesignRSertPanel();

}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnTProgFileSaveAs(TObject *Sender)
{ // Сохранить в файле программу по времени
   // проверка вызывающего действия
   if (Sender == acTProgFileSaveAs)
   { // ручное сохранение
      TimePrg.TProgFName = AnsiString( acTProgFileSaveAs->Dialog->FileName ).c_str();
      acTProgFileSaveAs->Dialog->FileName = "";
   }
   else
   { // автосейв
      TimePrg.TProgFName = AnsiString(mData.strTimeProg.c_str() + Now().FormatString("yyyy_mm_dd_hh_nn_ss'.tprg'")).c_str();
   }
   sbRB->Panels->Items[2]->Text = "Сохраняем программу по времени в файл!";

   LogPrint("Программа по времени сохраняется в файле \"" + AnsiString(TimePrg.TProgFName.c_str()) + "\"!",
      clAqua);
   TimePrg.Save();
   sbRB->Panels->Items[2]->Text = "Программа по времени сохранена в файле \"" +
      FileNameParse(AnsiString(TimePrg.TProgFName.c_str())) + "\"";
   btnCheckTProg->Enabled = false;
   btnSaveTProgToFile->Enabled = true;
   btnLoadTProgToPosA->Enabled = true;
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnTProgFileOpen(TObject *Sender)
{
   sbRB->Panels->Items[2]->Text = "Читаем программу по времени из файла!";
   TimePrg.TProgFName = AnsiString(acTProgFileOpen->Dialog->FileName).c_str();
   LogPrint("Программа по времени читается из файла \"" +
      FileNameParse(AnsiString(TimePrg.TProgFName.c_str())) + "\"!", clAqua);
   TimePrg.Load();
   sbRB->Panels->Items[2]->Text = "Программа по времени прочитана из файла \"" +
      FileNameParse(AnsiString(TimePrg.TProgFName.c_str())) + "\"";
   ShowTProg();
   btnCheckTProg->Enabled = false;
   btnSaveTProgToFile->Enabled = true;
   btnLoadTProgToPosA->Enabled = true;
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadTProgToPosA(TObject *Sender)
{
   if (!CheckProgLoad(sgTProgram, 1, 10.0))
   {
      return;
   }

   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Недьзя загрузить программу по времени в поз. А - нет связи со станком!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr5 = *inst_cpu.mPos1->mGr5;
   auto &gr6 = *inst_cpu.mPos1->mGr6;
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   sbRB->Panels->Items[2]->Text = "Загрузка программы по времени в поз. А!";
   TimePrg.ToCpu( gr5, gr6 );
   mPosA.RunProgName = TimePrg.TProgName;
   SetCurrProgA(mPosA.RunProgName);
   stP1L2ProgNameA->Caption = AnsiString(mPosA.RunProgName.c_str());
   mPosA.mTyre.InitPressure = StrToFlt(leTTyrePressure->Text);
   gr3p1.S_end_cycle = mPosA.mTyre.TotalS = 0;
   gr3p1.T_end_cycle = mPosA.mTyre.TotalTime = TimePrg.total_T;
   gr3p1.type_cycle = mPosA.mTyre.TestMode = 0;
   gr3p1.StepsQty = mPosA.mTyre.StepsNo = StrToInt(leTTotalStepsQty->Text);
   gr3p1.PollsQty = mPosA.mTyre.PollsNo = StrToInt(leTPollingTotalQty->Text);
   ShowProtAData();
   LogPrint( "Программа по времени, поз. А: время=" +
      String(gr3p1.T_end_cycle) + ", шагов программы=" + String(gr3p1.StepsQty) +
      ", опросов=" + String(gr3p1.PollsQty));


   btnResetResPosA->Click();
   gr3p1.Write();
   gr5.Write();
   gr6.Write();
   btnCheckTProg->Enabled = false;
   btnSaveTProgToFile->Enabled = true;
   btnLoadTProgToPosA->Enabled = true;
   LogPrint( "Программа по времени загружена в поз. А!");
   LogPrint("Программа по времени загружена в поз. А!", clAqua);
   sbRB->Panels->Items[2]->Text = "Программа по времени загружена в поз. А!";

}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnStringGridExit(TObject *Sender)
{
   /* TGridRect myRect;
    myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=0;
    ((TStringGrid *)Sender)->Selection=myRect; */
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnGetEditMask(TObject *Sender, int ACol, int ARow,
   AnsiString &Value)
{
   if (((TStringGrid*)Sender) == sgTProgram)
   {
      switch (ACol)
      {
      case 1:
         Value = "!999,99;1;_";
         break;
      case 2:
         Value = "!999,99;1;_";
         break;
      case 3:
         Value = "!999;1;_";
         break;
      case 4:
         Value = "!99;1;_";
         break;
      default:
         Value = "";
      }
   }
   if (((TStringGrid*)Sender) == sgTPolling)
   {
      switch (ACol)
      {
      case 1:
         Value = "!999;1;_";
         break;
      case 2:
         Value = "!99;1;_";
         break;
      default:
         Value = "";
      }
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnSGKeyDown(TObject *Sender, WORD &Key,
   TShiftState Shift)
{
   if (Key == VK_RETURN)
   {
      if (((TStringGrid*)Sender)->Col < ((TStringGrid*)Sender)->ColCount - 1)
      {
         ((TStringGrid *)Sender)->Col++;
      }
      else
      {
         ((TStringGrid *)Sender)->Col = 1;
         if (((TStringGrid *)Sender)->Row < ((TStringGrid *)Sender)
            ->RowCount - 1)
            ((TStringGrid *)Sender)->Row++;
         else
            ((TStringGrid *)Sender)->Row = 1;
      }
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnSGKeyPress(TObject *Sender, char &Key)
{
   if (Key == ',')
   {
      Key = '.';
   }
   Set < char, '0', '9' > Dig;
   Dig << '0' << '1' << '2' << '3' << '4' << '5' << '6' << '7' << '8' << '9';
   // LogPrint("Key="+String((unsigned short)Key),clRed);
   if (!Dig.Contains(Key) && Key != '\b' && Key != DecimalSeparator && Key !=
      VK_RETURN && Key != VK_TAB)
   {
      Key = 0;
      Beep();
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnTProgCheck(TObject *Sender)
{
   // чистка старых данных
   TimePrg.Clear();
   // читаем программу из ячеек таблиц, проверяем и записываем в массивы
   TimePrg.TProgName = AnsiString(leTProgName->Text).c_str();
   TimePrg.TTyrePressure = StrToFlt(leTTyrePressure->Text);
   leTTyrePressure->Text = FloatToStrF(TimePrg.TTyrePressure, ffFixed, 6, 1);
   TimePrg.total_step_T = 0;
   TimePrg.total_T = 0;
   for (int i = 0; i < MAXNUMOFSTEPS; i++)
   {
      double Load = StrToFlt(sgTProgram->Cells[1][i + 1]), Speed =
         StrToFlt(sgTProgram->Cells[2][i + 1]);
      int Time = StrToI(sgTProgram->Cells[3][i + 1]) * 3600 * 1000 +
         StrToI(sgTProgram->Cells[4][i + 1]) * 60 * 1000;
      if (!CheckLoad(Load) || !CheckSpeed(Speed) || (!CheckTime(Time) && Time))
      {
         TimePrg.Clear(); // чистка данных
         AnsiString msg = "Введено не корректное значение в строке " +
            AnsiString(i + 1);
         MessageBox(Handle, msg.c_str(), _T("Ошибка"), MB_ICONERROR | MB_OK);
         return;
      }
      TimePrg.Tsettings[0][i] = Load;
      if (TimePrg.Tsettings[0][i] == 0)
      { // если нагрузка в этой строчке равна 0
         if (i > 0)
            TimePrg.total_step_T = i;
         else
         {
            sbRB->Panels->Items[2]->Text =
               "Не задано ни одного значения нагрузки!";
            MessageBox(Handle, _T("Не задано ни одного значения нагрузки!"),
               _T("Ошибка"), MB_ICONERROR | MB_OK);
            TimePrg.Clear(); // чистка данных
         }
         break; // то прекратить ввод из таблицы
      }
      sgTProgram->Cells[1][i + 1] = FloatToStrF(TimePrg.Tsettings[0][i], ffFixed, 6, 2);

      TimePrg.Tsettings[1][i] = Speed;
      if (TimePrg.Tsettings[1][i] == 0)
      { // если скорость равна 0
         if (i > 0)
         { // если строка не первая - взять из предыдущей строки
            TimePrg.Tsettings[1][i] = TimePrg.Tsettings[1][i - 1];
         }
         else
         { // иначе ни одной скорости не задано - прекратить ввод из таблицы
            sbRB->Panels->Items[2]->Text =
               "Не задано ни одного значения скорости!";
            TimePrg.total_step_T = 0;
            MessageBox(Handle, _T("Не задано ни одного значения скорости!"),
               _T("Ошибка"), MB_ICONERROR | MB_OK);
            TimePrg.Clear(); // чистка данных
            break;
         }
      }
      sgTProgram->Cells[2][i + 1] = FloatToStrF(TimePrg.Tsettings[1][i], ffFixed, 6, 2);

      TimePrg.prog_step_T[i] = Time;
      if (TimePrg.prog_step_T[i] == 0)
      { // если продолжительность шага равна 0
         if (i > 0)
         { // если строка не первая - взять из предыдущей строки
            TimePrg.prog_step_T[i] = TimePrg.prog_step_T[i - 1];
         }
         else
         { // иначе не задано продолжительности - прекратить ввод из таблицы
            sbRB->Panels->Items[2]->Text =
               "Не задано ни одного значения продолжительности шага!";
            TimePrg.total_step_T = 0;
            MessageBox(Handle,
               _T("Не задано ни одного значения продолжительности шага!"),
               _T("Ошибка"), MB_ICONERROR | MB_OK);
            TimePrg.Clear(); // чистка данных
            break;
         }
      }
      sgTProgram->Cells[3][i + 1] = String(TimePrg.prog_step_T[i] / 1000 / 3600);
      sgTProgram->Cells[4][i + 1] =
         String((TimePrg.prog_step_T[i] / 1000 -
         TimePrg.prog_step_T[i] / 1000 / 3600 * 3600) / 60);
      TimePrg.total_T += TimePrg.prog_step_T[i];
   }
   leTTotalStepsQty->Text = String(TimePrg.total_step_T);
   if (TimePrg.total_step_T == 0)
   {
      leTotalTestTime->Text = "";
      return;
   }
   leTotalTestTime->Text = AnsiString(dt::mSecToHMSStr(TimePrg.total_T).c_str());
   TimePrg.num_T_poll = 0;
   int total_poll_T = 0;
   for (int i = 0; i < MAXNUMOFPOLLS; i++)
   {
      int Time = StrToI(sgTPolling->Cells[1][i + 1]) * 3600 * 1000 +
         StrToI(sgTPolling->Cells[2][i + 1]) * 60 * 1000;
      if (!CheckTime(Time) && Time)
      {
         TimePrg.Clear(); // чистка данных
         AnsiString msg = "Введено не корректное значение опроса в строке " +
            AnsiString(i + 1);
         MessageBox(Handle, msg.c_str(), _T("Ошибка"), MB_ICONERROR | MB_OK);
         return;
      }
      TimePrg.poll_step_T[i] = Time;
      if (TimePrg.poll_step_T[i] == 0)
      {
         if (i == 0)
         {
            sbRB->Panels->Items[2]->Text =
               "Не задано ни одного времени опроса!";
            MessageBox(Handle, _T("Не задано ни одного времени опроса!"),
               _T("Ошибка"), MB_ICONERROR | MB_OK);
            TimePrg.Clear(); // чистка данных
            break;
         }
         else
         {
            TimePrg.poll_step_T[i] = TimePrg.poll_step_T[i - 1];
         }
      }
      sgTPolling->Cells[1][i + 1] = String(TimePrg.poll_step_T[i] / 1000 / 3600);
      sgTPolling->Cells[2][i + 1] =
         String((TimePrg.poll_step_T[i] / 1000 -
         TimePrg.poll_step_T[i] / 1000 / 3600 * 3600) / 60);
      total_poll_T += TimePrg.poll_step_T[i];
      TimePrg.num_T_poll++;
      if (total_poll_T >= TimePrg.total_T)
         break;
   }
   if (TimePrg.num_T_poll == 0)
   {
      leTPollingTotalQty->Text = "";
      return;
   }
   leTPollingTotalQty->Text = String(TimePrg.num_T_poll);
   sbRB->Panels->Items[2]->Text = "Программа проверена!";
   btnCheckTProg->Enabled = false;
   btnSaveTProgToFile->Enabled = true;
   btnLoadTProgToPosA->Enabled = true;
}
// ---- End of OnTProgCheck --------------------------------------------------

void __fastcall TmfRB::OnSGSEnter(TObject *Sender)
{
   btnCheckSProg->Enabled = true;
   btnSaveSProgToFile->Enabled = false;
   btnLoadSProgToPosA->Enabled = false;
}
// ---- End of OnSGSEnter ----------------------------------------------------

void __fastcall TmfRB::OnLEKeyDown(TObject *Sender, WORD &Key,
   TShiftState Shift)
{
   if (Key == VK_RETURN)
   {
      FindNextControl((TWinControl *)Sender, true, true, false)->SetFocus();
   }
}
// ---------------------------------------------------------------------------

void TmfRB::DesignCmmnParPanel(void)
   // расположение компонент на панели общих параметров
{
   int C0Width = pParam1Width / 4;
   int C1_6Width = (pParam1Width - C0Width) / 6;
   int C1_4Width = C1_6Width * 3 / 2;
   C0Width = pParam1Width - C1_6Width * 6;
   C1_6Width = C1_4Width * 2 / 3 * 2;
   pParam1Height = 13 * tsCurrentStatusH / 22;
   pParam2Height = tsCurrentStatusH - pParam1Height - Splitter1->Height;
   pParam1->Height = pParam1Height;
   pParam2->Height = pParam2Height;
   int p1RowHeight = pParam1Height / 13;
   if (p1RowHeight > 30)
      p1RowHeight = 30;
   stP1CurDate->Left = 0;
   stP1CurDate->Top = 0;
   stP1CurDate->Width = C0Width;
   stP1CurDate->Height = p1RowHeight;
   stP1TL0C1->Left = C0Width;
   stP1TL0C1->Top = 0;
   stP1TL0C1->Width = C1_6Width * 3;
   stP1TL0C1->Height = p1RowHeight;
   stP1TTyreType->Left = 0;
   stP1TTyreType->Top = p1RowHeight;
   stP1TTyreType->Width = C0Width;
   stP1TTyreType->Height = p1RowHeight;
   stP1L1TyreTypeA->Left = C0Width;
   stP1L1TyreTypeA->Top = p1RowHeight;
   stP1L1TyreTypeA->Width = C1_6Width * 3;
   stP1L1TyreTypeA->Height = p1RowHeight;
   stP1TProgName->Left = 0;
   stP1TProgName->Top = p1RowHeight * 2;
   stP1TProgName->Width = C0Width;
   stP1TProgName->Height = p1RowHeight;
   stP1L2ProgNameA->Left = C0Width;
   stP1L2ProgNameA->Top = p1RowHeight * 2;
   stP1L2ProgNameA->Width = C1_6Width * 3;
   stP1L2ProgNameA->Height = p1RowHeight;
   pP1PT2->Left = 0;
   pP1PT2->Top = p1RowHeight * 3;
   pP1PT2->Width = pParam1Width;
   pP1PT2->Height = p1RowHeight;
   pP1PL1Ttl->Left = 0;
   pP1PL1Ttl->Top = p1RowHeight * 4;
   pP1PL1Ttl->Width = C0Width;
   pP1PL1Ttl->Height = p1RowHeight;
   pP1PL2Ttl->Left = 0;
   pP1PL2Ttl->Top = p1RowHeight * 5;
   pP1PL2Ttl->Width = C0Width;
   pP1PL2Ttl->Height = p1RowHeight;
   pP1PL3Ttl->Left = 0;
   pP1PL3Ttl->Top = p1RowHeight * 6;
   pP1PL3Ttl->Width = C0Width;
   pP1PL3Ttl->Height = p1RowHeight;
   pP1PL4Ttl->Left = 0;
   pP1PL4Ttl->Top = p1RowHeight * 7;
   pP1PL4Ttl->Width = C0Width;
   pP1PL4Ttl->Height = p1RowHeight;
   pP1PL5Ttl->Left = 0;
   pP1PL5Ttl->Top = p1RowHeight * 8;
   pP1PL5Ttl->Width = C0Width;
   pP1PL5Ttl->Height = p1RowHeight;
   pP1PL6Ttl->Left = 0;
   pP1PL6Ttl->Top = p1RowHeight * 9;
   pP1PL6Ttl->Width = C0Width;
   pP1PL6Ttl->Height = p1RowHeight;
   pP1PL7Ttl->Left = 0;
   pP1PL7Ttl->Top = p1RowHeight * 10;
   pP1PL7Ttl->Width = C0Width;
   pP1PL7Ttl->Height = p1RowHeight;
   pP1PL8Ttl->Left = 0;
   pP1PL8Ttl->Top = p1RowHeight * 11;
   pP1PL8Ttl->Width = C0Width;
   pP1PL8Ttl->Height = p1RowHeight;
   pP1PL9Ttl->Left = 0;
   pP1PL9Ttl->Top = p1RowHeight * 12;
   pP1PL9Ttl->Width = C0Width;
   pP1PL9Ttl->Height = p1RowHeight;
   pP1L1C1Ttl->Left = C0Width;
   pP1L1C1Ttl->Top = p1RowHeight * 4;
   pP1L1C1Ttl->Width = C1_6Width;
   pP1L1C1Ttl->Height = p1RowHeight;
   pP1L1C2Ttl->Left = C0Width + C1_6Width;
   pP1L1C2Ttl->Top = p1RowHeight * 4;
   pP1L1C2Ttl->Width = C1_6Width;
   pP1L1C2Ttl->Height = p1RowHeight;
   pP1L1C3Ttl->Left = C0Width + C1_6Width * 2;
   pP1L1C3Ttl->Top = p1RowHeight * 4;
   pP1L1C3Ttl->Width = C1_6Width;
   pP1L1C3Ttl->Height = p1RowHeight;
   stP1CParL1C1->Left = C0Width;
   stP1CParL1C1->Top = p1RowHeight * 5;
   stP1CParL1C1->Width = C1_6Width;
   stP1CParL1C1->Height = p1RowHeight;
   stP1CParL1C2->Left = C0Width + C1_6Width;
   stP1CParL1C2->Top = p1RowHeight * 5;
   stP1CParL1C2->Width = C1_6Width;
   stP1CParL1C2->Height = p1RowHeight;
   stP1CParL1C3->Left = C0Width + C1_6Width * 2;
   stP1CParL1C3->Top = p1RowHeight * 5;
   stP1CParL1C3->Width = C1_6Width;
   stP1CParL1C3->Height = p1RowHeight;
   stP1CParL2C1->Left = C0Width;
   stP1CParL2C1->Top = p1RowHeight * 6;
   stP1CParL2C1->Width = C1_6Width;
   stP1CParL2C1->Height = p1RowHeight;
   stP1CParL2C2->Left = C0Width + C1_6Width;
   stP1CParL2C2->Top = p1RowHeight * 6;
   stP1CParL2C2->Width = C1_6Width;
   stP1CParL2C2->Height = p1RowHeight;
   stP1CParL2C3->Left = C0Width + C1_6Width * 2;
   stP1CParL2C3->Top = p1RowHeight * 6;
   stP1CParL2C3->Width = C1_6Width;
   stP1CParL2C3->Height = p1RowHeight;
   stP1CParL3C1->Left = C0Width;
   stP1CParL3C1->Top = p1RowHeight * 7;
   stP1CParL3C1->Width = C1_6Width;
   stP1CParL3C1->Height = p1RowHeight;
   stP1CParL3C2->Left = C0Width + C1_6Width;
   stP1CParL3C2->Top = p1RowHeight * 7;
   stP1CParL3C2->Width = C1_6Width;
   stP1CParL3C2->Height = p1RowHeight;
   stP1CParL3C3->Left = C0Width + C1_6Width * 2;
   stP1CParL3C3->Top = p1RowHeight * 7;
   stP1CParL3C3->Width = C1_6Width;
   stP1CParL3C3->Height = p1RowHeight;
   stP1CParL4C1->Left = C0Width;
   stP1CParL4C1->Top = p1RowHeight * 8;
   stP1CParL4C1->Width = C1_6Width;
   stP1CParL4C1->Height = p1RowHeight;
   stP1CParL4C2->Left = C0Width + C1_6Width;
   stP1CParL4C2->Top = p1RowHeight * 8;
   stP1CParL4C2->Width = C1_6Width;
   stP1CParL4C2->Height = p1RowHeight;
   stP1CParL4C3->Left = C0Width + C1_6Width * 2;
   stP1CParL4C3->Top = p1RowHeight * 8;
   stP1CParL4C3->Width = C1_6Width;
   stP1CParL4C3->Height = p1RowHeight;
   stP1CParL5C1->Left = C0Width;
   stP1CParL5C1->Top = p1RowHeight * 9;
   stP1CParL5C1->Width = C1_6Width;
   stP1CParL5C1->Height = p1RowHeight;
   stP1CParL5C2->Left = C0Width + C1_6Width;
   stP1CParL5C2->Top = p1RowHeight * 9;
   stP1CParL5C2->Width = C1_6Width;
   stP1CParL5C2->Height = p1RowHeight;
   stP1CParL5C3->Left = C0Width + C1_6Width * 2;
   stP1CParL5C3->Top = p1RowHeight * 9;
   stP1CParL5C3->Width = C1_6Width;
   stP1CParL5C3->Height = p1RowHeight;
   stP1CParL6C1->Left = C0Width;
   stP1CParL6C1->Top = p1RowHeight * 10;
   stP1CParL6C1->Width = C1_6Width;
   stP1CParL6C1->Height = p1RowHeight;
   stP1CParL6C2->Left = C0Width + C1_6Width;
   stP1CParL6C2->Top = p1RowHeight * 10;
   stP1CParL6C2->Width = C1_6Width;
   stP1CParL6C2->Height = p1RowHeight;
   stP1CParL6C3->Left = C0Width + C1_6Width * 2;
   stP1CParL6C3->Top = p1RowHeight * 10;
   stP1CParL6C3->Width = C1_6Width;
   stP1CParL6C3->Height = p1RowHeight;
   stP1CParL7C1->Left = C0Width;
   stP1CParL7C1->Top = p1RowHeight * 11;
   stP1CParL7C1->Width = C1_6Width;
   stP1CParL7C1->Height = p1RowHeight;
   stP1CParL7C2->Left = C0Width + C1_6Width;
   stP1CParL7C2->Top = p1RowHeight * 11;
   stP1CParL7C2->Width = C1_6Width;
   stP1CParL7C2->Height = p1RowHeight;
   stP1CParL7C3->Left = C0Width + C1_6Width * 2;
   stP1CParL7C3->Top = p1RowHeight * 11;
   stP1CParL7C3->Width = C1_6Width;
   stP1CParL7C3->Height = p1RowHeight;
   stP1CParL8C1->Left = C0Width;
   stP1CParL8C1->Top = p1RowHeight * 12;
   stP1CParL8C1->Width = C1_6Width;
   stP1CParL8C1->Height = p1RowHeight;
   stP1CParL8C2->Left = C0Width + C1_6Width;
   stP1CParL8C2->Top = p1RowHeight * 12;
   stP1CParL8C2->Width = C1_6Width;
   stP1CParL8C2->Height = p1RowHeight;
   stP1CParL8C3->Left = C0Width + C1_6Width * 2;
   stP1CParL8C3->Top = p1RowHeight * 12;
   stP1CParL8C3->Width = C1_6Width;
   stP1CParL8C3->Height = p1RowHeight;
   C0Width = pParam2Width / 4;
   C1_6Width = (pParam2Width - C0Width) / 6;
   C0Width = pParam2Width - C1_6Width * 6;
   C1_4Width = C1_6Width * 3 / 2 * 2;
   p1RowHeight = pParam2Height / 9;
   if (p1RowHeight > 30)
      p1RowHeight = 30;
   pP2TtlL0C1->Left = C0Width;
   pP2TtlL0C1->Top = 0;
   pP2TtlL0C1->Width = C1_4Width * 2;
   pP2TtlL0C1->Height = p1RowHeight;
   pP2TtlL1C1->Left = C0Width;
   pP2TtlL1C1->Top = p1RowHeight;
   pP2TtlL1C1->Width = C1_4Width;
   pP2TtlL1C1->Height = p1RowHeight;
   pP2TtlL1C2->Left = C0Width + C1_4Width;
   pP2TtlL1C2->Top = p1RowHeight;
   pP2TtlL1C2->Width = C1_4Width;
   pP2TtlL1C2->Height = p1RowHeight;
   pP2TtlL1C0->Left = 0;
   pP2TtlL1C0->Top = p1RowHeight * 2;
   pP2TtlL1C0->Width = C0Width;
   pP2TtlL1C0->Height = p1RowHeight;
   pP2TtlL2C0->Left = 0;
   pP2TtlL2C0->Top = p1RowHeight * 3;
   pP2TtlL2C0->Width = C0Width;
   pP2TtlL2C0->Height = p1RowHeight;
   pP2TtlL3C0->Left = 0;
   pP2TtlL3C0->Top = p1RowHeight * 4;
   pP2TtlL3C0->Width = C0Width;
   pP2TtlL3C0->Height = p1RowHeight;
   pP2TtlL4C0->Left = 0;
   pP2TtlL4C0->Top = p1RowHeight * 5;
   pP2TtlL4C0->Width = C0Width;
   pP2TtlL4C0->Height = p1RowHeight;
   pP2TtlL5C0->Left = 0;
   pP2TtlL5C0->Top = p1RowHeight * 6;
   pP2TtlL5C0->Width = C0Width;
   pP2TtlL5C0->Height = p1RowHeight;
   pP2TtlL6C0->Left = 0;
   pP2TtlL6C0->Top = p1RowHeight * 7;
   pP2TtlL6C0->Width = C0Width;
   pP2TtlL6C0->Height = p1RowHeight;
   pP2TtlL7C0->Left = 0;
   pP2TtlL7C0->Top = p1RowHeight * 8;
   pP2TtlL7C0->Width = C0Width;
   pP2TtlL7C0->Height = p1RowHeight;
   stP2CParL1C1->Left = C0Width;
   stP2CParL1C1->Top = p1RowHeight * 2;
   stP2CParL1C1->Width = C1_4Width;
   stP2CParL1C1->Height = p1RowHeight;
   stP2CParL1C2->Left = C0Width + C1_4Width;
   stP2CParL1C2->Top = p1RowHeight * 2;
   stP2CParL1C2->Width = C1_4Width;
   stP2CParL1C2->Height = p1RowHeight;

   stP2CParL2C1->Left = C0Width;
   stP2CParL2C1->Top = p1RowHeight * 3;
   stP2CParL2C1->Width = C1_4Width;
   stP2CParL2C1->Height = p1RowHeight;
   stP2CParL2C2->Left = C0Width + C1_4Width;
   stP2CParL2C2->Top = p1RowHeight * 3;
   stP2CParL2C2->Width = C1_4Width;
   stP2CParL2C2->Height = p1RowHeight;

   stP2CParL3C1->Left = C0Width;
   stP2CParL3C1->Top = p1RowHeight * 4;
   stP2CParL3C1->Width = C1_4Width;
   stP2CParL3C1->Height = p1RowHeight;
   stP2CParL3C2->Left = C0Width + C1_4Width;
   stP2CParL3C2->Top = p1RowHeight * 4;
   stP2CParL3C2->Width = C1_4Width;
   stP2CParL3C2->Height = p1RowHeight;

   stP2CParL4C1->Left = C0Width;
   stP2CParL4C1->Top = p1RowHeight * 5;
   stP2CParL4C1->Width = C1_4Width;
   stP2CParL4C1->Height = p1RowHeight;
   stP2CParL4C2->Left = C0Width + C1_4Width;
   stP2CParL4C2->Top = p1RowHeight * 5;
   stP2CParL4C2->Width = C1_4Width;
   stP2CParL4C2->Height = p1RowHeight;

   stP2CParL5C1->Left = C0Width;
   stP2CParL5C1->Top = p1RowHeight * 6;
   stP2CParL5C1->Width = C1_4Width;
   stP2CParL5C1->Height = p1RowHeight;
   stP2CParL5C2->Left = C0Width + C1_4Width;
   stP2CParL5C2->Top = p1RowHeight * 6;
   stP2CParL5C2->Width = C1_4Width;
   stP2CParL5C2->Height = p1RowHeight;

   stP2CParL6C1->Left = C0Width;
   stP2CParL6C1->Top = p1RowHeight * 7;
   stP2CParL6C1->Width = C1_4Width;
   stP2CParL6C1->Height = p1RowHeight;
   stP2CParL6C2->Left = C0Width + C1_4Width;
   stP2CParL6C2->Top = p1RowHeight * 7;
   stP2CParL6C2->Width = C1_4Width;
   stP2CParL6C2->Height = p1RowHeight;

   stP2CParL7C1->Left = C0Width;
   stP2CParL7C1->Top = p1RowHeight * 8;
   stP2CParL7C1->Width = C1_4Width;
   stP2CParL7C1->Height = p1RowHeight;
   stP2CParL7C2->Left = C0Width + C1_4Width;
   stP2CParL7C2->Top = p1RowHeight * 8;
   stP2CParL7C2->Width = C1_4Width;
   stP2CParL7C2->Height = p1RowHeight;
}
// ---- End of DesignCmmnParPanel --------------------------------------------

void TmfRB::DesignManualPanel(void)
   // расположение компонент на панели ручного управления
{
   int gbHeight = tsManualHeight - 20;
   int gbWidth1 = tsManualWidth / 19 * 5;
   int gbWidth2 = (tsManualWidth - gbWidth1 - 30) / 2;
   int leWidth = leCurrentLoad1->EditLabel->Width + 2;
   int leEdHeight = leCurrentLoad1->EditLabel->Height + 2;
   int leHeight = 30;
   int TickdH = (gbHeight) / 22 - 3;
   gbCarriage1->Left = 10;
   gbCarriage1->Top = 10;
   gbCarriage1->Width = gbWidth2;
   gbCarriage1->Height = gbHeight;

   pCarr1Load->Left = 10;
   pCarr1Load->Top = 20;
   pCarr1Load->Width = gbWidth2 - 20;
   pCarr1Load->Height = 26;
   leCurrentLoad1->Left = 30;
   leCurrentLoad1->Top = 56 + leEdHeight;
   leCurrentLoad1->Width = leWidth;
   leCurrentLoad1->Height = leHeight;
   leSetLoad1->Left = 30;
   leSetLoad1->Top = 56 + leEdHeight * 2 + 20 + leHeight;
   leSetLoad1->Width = leWidth;
   leSetLoad1->Height = leHeight;
   tbCurrentLoad1->Left = leWidth * 2 + 30;
   tbCurrentLoad1->Top = leCurrentLoad1->Top - leEdHeight;
   tbCurrentLoad1->Width = 50;
   tbCurrentLoad1->Height = gbHeight / 2;
   leCurrentT1->Left = leWidth * 2 + 20;
   leCurrentT1->Top = tbCurrentLoad1->Top + gbHeight / 2 + 5;
   leCurrentT1->Width = leWidth;
   leCurrentT1->Height = leHeight;
   leCurrentR1->Left = leWidth * 2 + 20;
   leCurrentR1->Top = leCurrentT1->Top + leHeight + 10;
   leCurrentR1->Width = leWidth;
   leCurrentR1->Height = leHeight;
   lLoad0->Left = leWidth * 2 + 85;
   lLoad0->Top = tbCurrentLoad1->Top + gbHeight / 2 - 27;
   lLoad0->Width = 30;
   lLoad0->Height = 20;
   lLoad10->Left = leWidth * 2 + 85;
   lLoad10->Top = tbCurrentLoad1->Top + gbHeight / 2 - 27 - TickdH;
   lLoad10->Width = 30;
   lLoad10->Height = 20;
   lLoad20->Left = leWidth * 2 + 85;
   lLoad20->Top = tbCurrentLoad1->Top + gbHeight / 2 - 27 - TickdH * 2;
   lLoad20->Width = 30;
   lLoad20->Height = 20;
   lLoad30->Left = leWidth * 2 + 85;
   lLoad30->Top = tbCurrentLoad1->Top + gbHeight / 2 - 27 - TickdH * 3;
   lLoad30->Width = 30;
   lLoad30->Height = 20;
   lLoad40->Left = leWidth * 2 + 85;
   lLoad40->Top = tbCurrentLoad1->Top + gbHeight / 2 - 27 - TickdH * 4;
   lLoad40->Width = 30;
   lLoad40->Height = 20;
   lLoad50->Left = leWidth * 2 + 85;
   lLoad50->Top = tbCurrentLoad1->Top + gbHeight / 2 - 27 - TickdH * 5;
   lLoad50->Width = 30;
   lLoad50->Height = 20;
   lLoad60->Left = leWidth * 2 + 85;
   lLoad60->Top = tbCurrentLoad1->Top + gbHeight / 2 - 27 - TickdH * 6;
   lLoad60->Width = 30;
   lLoad60->Height = 20;
   lLoad70->Left = leWidth * 2 + 85;
   lLoad70->Top = tbCurrentLoad1->Top + gbHeight / 2 - 27 - TickdH * 7;
   lLoad70->Width = 30;
   lLoad70->Height = 20;
   lLoad80->Left = leWidth * 2 + 85;
   lLoad80->Top = tbCurrentLoad1->Top + gbHeight / 2 - 27 - TickdH * 8;
   lLoad80->Width = 30;
   lLoad80->Height = 20;
   lLoad90->Left = leWidth * 2 + 85;
   lLoad90->Top = tbCurrentLoad1->Top + gbHeight / 2 - 27 - TickdH * 9;
   lLoad90->Width = 30;
   lLoad90->Height = 20;
   lLoad100->Left = leWidth * 2 + 85;
   lLoad100->Top = tbCurrentLoad1->Top + gbHeight / 2 - 27 - TickdH * 10;
   lLoad100->Width = 30;
   lLoad100->Height = 20;
   lLoad110->Left = leWidth * 2 + 85;
   lLoad110->Top = tbCurrentLoad1->Top + gbHeight / 2 - 27 - TickdH * 11;
   lLoad110->Width = 30;
   lLoad110->Height = 20;
   pCarr1Ttl->Left = 10;
   pCarr1Ttl->Top = leCurrentR1->Top + leHeight + 10;
   pCarr1Ttl->Width = gbWidth2 - 20;
   pCarr1Ttl->Height = 26;
   int btnTop = pCarr1Ttl->Top + 36;
   btnCarriage1From->Left = 5;
   btnCarriage1From->Top = btnTop;
   btnCarriage1From->Width = 112;
   btnCarriage1From->Height = 40;
   btnCarriage1Stop->Left = (gbWidth2 - 286) / 2 + 117;
   btnCarriage1Stop->Top = btnTop;
   btnCarriage1Stop->Width = 62;
   btnCarriage1Stop->Height = 40;
   btnCarriage1To->Left = gbWidth2 - 5 - 102;
   btnCarriage1To->Top = btnTop;
   btnCarriage1To->Width = 102;
   btnCarriage1To->Height = 40;
   sbCarr1Fm->Left = 5;
   sbCarr1Fm->Top = btnTop + 45;
   sbCarr1Fm->Width = 25;
   sbCarr1Fm->Height = 26;
   sbCarr1To->Left = gbWidth2 - 5 - 25;
   sbCarr1To->Top = btnTop + 45;
   sbCarr1To->Width = 25;
   sbCarr1To->Height = 26;
   sbCarriage1Off->Left = 5;
   sbCarriage1Off->Top = btnTop + 76;
   sbCarriage1Off->Width = 25;
   sbCarriage1Off->Height = 26;
   lCarriage1Off->Left = 33;
   lCarriage1Off->Top = btnTop + 76;
   lCarriage1Off->Width = 165;
   lCarriage1Off->Height = 26;

   gbDrum->Left = gbWidth2 + 15;
   gbDrum->Top = 10;
   gbDrum->Width = gbWidth1;
   gbDrum->Height = gbHeight;
   pDrumSpeed->Left = 10;
   pDrumSpeed->Top = 20;
   pDrumSpeed->Width = gbWidth1 - 20;
   pDrumSpeed->Height = 26;
   leCurrentDrumSpeed->Left = 20;
   leCurrentDrumSpeed->Top = 56 + leEdHeight;
   leCurrentDrumSpeed->Width = leWidth;
   leCurrentDrumSpeed->Height = leHeight;
   leSetDrumSpeed->Left = 20;
   leSetDrumSpeed->Top = 56 + leEdHeight * 2 + 20 + leHeight;
   leSetDrumSpeed->Width = leWidth;
   leSetDrumSpeed->Height = leHeight;
   tbCurrentDrumSpeed->Left = leWidth + 30;
   tbCurrentDrumSpeed->Top = leCurrentDrumSpeed->Top - leEdHeight;
   tbCurrentDrumSpeed->Width = 50;
   tbCurrentDrumSpeed->Height = gbHeight / 5 * 3;
   TickdH = (gbHeight) / 5 * 3 / 10 - 3;
   int tbDSTop = tbCurrentDrumSpeed->Top + gbHeight / 5 * 3 - 27;
   int TickLeft = leWidth * 2 + 20;
   lSpeed00->Left = TickLeft;
   lSpeed00->Top = tbDSTop;
   lSpeed00->Width = 30;
   lSpeed00->Height = 20;
   lSpeed20->Left = TickLeft;
   lSpeed20->Top = tbDSTop - TickdH;
   lSpeed20->Width = 30;
   lSpeed20->Height = 20;
   lSpeed40->Left = TickLeft;
   lSpeed40->Top = tbDSTop - TickdH * 2 + 1;
   lSpeed40->Width = 30;
   lSpeed40->Height = 20;
   lSpeed60->Left = TickLeft;
   lSpeed60->Top = tbDSTop - TickdH * 3;
   lSpeed60->Width = 30;
   lSpeed60->Height = 20;
   lSpeed80->Left = TickLeft;
   lSpeed80->Top = tbDSTop - TickdH * 4 + 1;
   lSpeed80->Width = 30;
   lSpeed80->Height = 20;
   lSpeed100->Left = TickLeft;
   lSpeed100->Top = tbDSTop - TickdH * 5;
   lSpeed100->Width = 30;
   lSpeed100->Height = 20;
   lSpeed120->Left = TickLeft;
   lSpeed120->Top = tbDSTop - TickdH * 6 - 3;
   lSpeed120->Width = 30;
   lSpeed120->Height = 20;
   lSpeed140->Left = TickLeft;
   lSpeed140->Top = tbDSTop - TickdH * 7 - 4;
   lSpeed140->Width = 30;
   lSpeed140->Height = 20;
   lSpeed160->Left = TickLeft;
   lSpeed160->Top = tbDSTop - TickdH * 8 - 4;
   lSpeed160->Width = 30;
   lSpeed160->Height = 20;
   lSpeed180->Left = TickLeft;
   lSpeed180->Top = tbDSTop - TickdH * 9 - 4;
   lSpeed180->Width = 30;
   lSpeed180->Height = 20;
   lSpeed200->Left = TickLeft;
   lSpeed200->Top = tbDSTop - TickdH * 10 - 5;
   lSpeed200->Width = 30;
   lSpeed200->Height = 20;
   sbDrumOn->Left = 10;
   sbDrumOn->Top = tbDSTop;
   sbDrumOn->Width = 25;
   sbDrumOn->Height = 26;
   pDrumTtl->Left = 10;
   pDrumTtl->Top = pCarr1Ttl->Top;
   pDrumTtl->Width = gbWidth1 - 20;
   pDrumTtl->Height = 26;
   btnDrumOn->Left = (gbWidth1 - 150) / 2;
   btnDrumOn->Top = btnTop;
   btnDrumOn->Width = 150;
   btnDrumOn->Height = 40;
   btnDrumOff->Left = (gbWidth1 - 150) / 2;
   btnDrumOff->Top = btnTop + 60;
   btnDrumOff->Width = 150;
   btnDrumOff->Height = 40;
}
// ---- End of DesignManualPanel ---------------------------------------------

void TmfRB::ShowTProg(void)
   // отобразить программу по времени на экране
{
   leTProgName->Text = AnsiString(TimePrg.TProgName.c_str());
   leTTyrePressure->Text = FloatToStrF(TimePrg.TTyrePressure, ffFixed, 6, 1);
   leTTotalStepsQty->Text = String(TimePrg.total_step_T);
   leTotalTestTime->Text = AnsiString(dt::mSecToHMSStr(TimePrg.total_T).c_str());
   leTPollingTotalQty->Text = String(TimePrg.num_T_poll);
   for (int i = 0; i < TimePrg.total_step_T; i++)
   {
      sgTProgram->Cells[1][i + 1] = FloatToStrF(TimePrg.Tsettings[0][i], ffFixed, 6, 2);
      sgTProgram->Cells[2][i + 1] = FloatToStrF(TimePrg.Tsettings[1][i], ffFixed, 6, 2);
      sgTProgram->Cells[3][i + 1] = String(TimePrg.prog_step_T[i] / 1000 / 3600);
      sgTProgram->Cells[4][i + 1] =
         String((TimePrg.prog_step_T[i] / 1000 -
         TimePrg.prog_step_T[i] / 1000 / 3600 * 3600) / 60);
   }
   for (int i = 0; i < TimePrg.num_T_poll; i++)
   {
      sgTPolling->Cells[1][i + 1] = String(TimePrg.poll_step_T[i] / 1000 / 3600);
      sgTPolling->Cells[2][i + 1] =
         String((TimePrg.poll_step_T[i] / 1000 -
         TimePrg.poll_step_T[i] / 1000 / 3600 * 3600) / 60);
   }
}
// ---- End of ShowTProg -----------------------------------------------------

void TmfRB::ShowSProg(void) // отобразить программу по пути на экране
{
   leSProgName->Text = AnsiString(PathPrg.SProgName.c_str());
   leSTyrePressure->Text = FloatToStrF(PathPrg.STyrePressure, ffFixed, 6, 1);
   leSTotalStepsQty->Text = String(PathPrg.total_step_S);
   leTotalTestS->Text = FloatToStrF(PathPrg.total_S, ffFixed, 7, 2);
   leSPollingTotalQty->Text = String(PathPrg.num_S_poll);
   for (int i = 0; i < PathPrg.total_step_S; i++)
   {
      sgSProgram->Cells[1][i + 1] = FloatToStrF(PathPrg.Ssettings[0][i], ffFixed, 6, 2);
      sgSProgram->Cells[2][i + 1] = FloatToStrF(PathPrg.Ssettings[1][i], ffFixed, 6, 2);
      sgSProgram->Cells[3][i + 1] = FloatToStrF(PathPrg.prog_step_S[i], ffFixed, 6, 2);
   }
   for (int i = 0; i < PathPrg.num_S_poll; i++)
   {
      sgSPolling->Cells[1][i + 1] = FloatToStrF(PathPrg.poll_step_S[i], ffFixed, 6, 2);
   }
}
// ---- End of ShowSProg -----------------------------------------------------

void __fastcall TmfRB::OnNewTProg(TObject *Sender)
{
   leTProgName->Text = "";
   TimePrg.TProgName = "";
   leTTyrePressure->Text = "";
   TimePrg.TTyrePressure = 0.0;
   leTTotalStepsQty->Text = "";
   TimePrg.total_step_T = 0;
   leTotalTestTime->Text = "00:00:00";
   TimePrg.total_T = 0;
   leTPollingTotalQty->Text = "";
   TimePrg.num_T_poll = 0;
   for (int i = 0; i < MAXNUMOFSTEPS; i++)
   {
      sgTProgram->Cells[1][i + 1] = "";
      sgTProgram->Cells[2][i + 1] = "";
      sgTProgram->Cells[3][i + 1] = "";
      sgTProgram->Cells[4][i + 1] = "";
   }
   for (int i = 0; i < MAXNUMOFPOLLS; i++)
   {
      sgTPolling->Cells[1][i + 1] = "";
      sgTPolling->Cells[2][i + 1] = "";
   }
   TimePrg.Clear(); // удаление старых данных из массивов
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnSGTEnter(TObject *Sender)
{
   btnCheckTProg->Enabled = true;
   btnSaveTProgToFile->Enabled = false;
   btnLoadTProgToPosA->Enabled = false;
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnSProgCheck(TObject *Sender)
{
   PathPrg.Clear(); // чистка старых данных
   // читаем программу из ячеек таблиц, проверяем и записываем в массивы
   PathPrg.SProgName = AnsiString(leSProgName->Text).c_str();
   PathPrg.STyrePressure = StrToFlt(leSTyrePressure->Text);
   leSTyrePressure->Text = FloatToStrF(PathPrg.STyrePressure, ffFixed, 6, 1);
   PathPrg.total_step_S = 0;
   PathPrg.total_S = 0;
   // ввод из первой таблицы нагрузок, скоростей и путей
   for (int i = 0; i < MAXNUMOFSTEPS; i++)
   {
      double Load = StrToFlt(sgSProgram->Cells[1][i + 1]), Speed =
         StrToFlt(sgSProgram->Cells[2][i + 1]), Distance =
         StrToFlt(sgSProgram->Cells[3][i + 1]);
      if (!CheckLoad(Load) || !CheckSpeed(Speed) ||
         (!CheckDistance(Distance) && Distance))
      {
         PathPrg.Clear(); // чистка данных
         AnsiString msg = "Введено не корректное значение в строке " +
            AnsiString(i + 1);
         MessageBox(Handle, msg.c_str(), _T("Ошибка"), MB_ICONERROR | MB_OK);
         return;
      }
      PathPrg.Ssettings[0][i] = Load; // нагрузки
      if (PathPrg.Ssettings[0][i] == 0)
      { // если нагрузка в этой строчке равна 0
         if (i > 0)
            PathPrg.total_step_S = i;
         // строка не первая - запомнить количество шагов программы по пути
         else
         {
            sbRB->Panels->Items[2]->Text =
               "Не задано ни одного значения нагрузки!";
         }
         break; // и прекратить ввод из таблицы
      }
      sgSProgram->Cells[1][i + 1] = FloatToStrF(PathPrg.Ssettings[0][i], ffFixed, 6, 2);

      PathPrg.Ssettings[1][i] = Speed; // скорости
      if (PathPrg.Ssettings[1][i] == 0)
      { // если скорость равна 0
         if (i > 0)
         { // если строка не первая - взять из предыдущей строки
            PathPrg.Ssettings[1][i] = PathPrg.Ssettings[1][i - 1];
         }
         else
         { // иначе ни одной скорости не задано - прекратить ввод из таблицы
            MessageBox(Handle, _T("Не задано ни одного значения скорости!"),
               _T("Ошибка"), MB_ICONERROR | MB_OK);
            sbRB->Panels->Items[2]->Text =
               "Не задано ни одного значения скорости!";
            PathPrg.total_step_S = 0;
            PathPrg.Clear(); // чистка данных
            break;
         }
      }

      sgSProgram->Cells[2][i + 1] = FloatToStrF(PathPrg.Ssettings[1][i], ffFixed, 6, 2);
      PathPrg.prog_step_S[i] = Distance;
      if (PathPrg.prog_step_S[i] == 0)
      { // если длина пути шага равна 0
         if (i > 0)
         { // если строка не первая - взять из предыдущей строки
            PathPrg.prog_step_S[i] = PathPrg.prog_step_S[i - 1];
         }
         else
         { // иначе не задано длины пути шага - прекратить ввод из таблицы
            MessageBox(Handle, _T("Не задано ни одного значения пути шага!"),
               _T("Ошибка"), MB_ICONERROR | MB_OK);
            sbRB->Panels->Items[2]->Text =
               "Не задано ни одного значения пути шага!";
            PathPrg.total_step_S = 0;
            PathPrg.Clear(); // чистка данных
            break;
         }
      }
      sgSProgram->Cells[3][i + 1] = FloatToStrF(PathPrg.prog_step_S[i], ffFixed, 6, 2);
      PathPrg.total_S += PathPrg.prog_step_S[i];
   } // конец обработки таблицы нагрузок, скоростей и путей
   leSTotalStepsQty->Text = String(PathPrg.total_step_S);
   if (PathPrg.total_step_S == 0)
   {
      leTotalTestTime->Text = "";
      return;
   }
   leTotalTestS->Text = FloatToStrF(PathPrg.total_S, ffFixed, 6, 2);
   PathPrg.num_S_poll = 0;
   float total_poll_S = 0;
   // ввод из второй таблицы опросов по пути
   for (int i = 0; i < MAXNUMOFPOLLS; i++)
   {
      double Distance = StrToFlt(sgSPolling->Cells[1][i + 1]);
      if (!CheckDistance(Distance) && Distance)
      {
         PathPrg.Clear(); // чистка данных
         AnsiString msg = "Введено не корректное значение опроса в строке " +
            AnsiString(i + 1);
         MessageBox(Handle, msg.c_str(), _T("Ошибка"), MB_ICONERROR | MB_OK);
         return;
      }
      PathPrg.poll_step_S[i] = Distance;
      if (PathPrg.poll_step_S[i] == 0)
      {
         if (i == 0)
         {
            MessageBox(Handle, _T("Не задано ни одного пути для опроса!"),
               _T("Ошибка"), MB_ICONERROR | MB_OK);
            sbRB->Panels->Items[2]->Text =
               "Не задано ни одного пути для опроса!";
            PathPrg.Clear(); // чистка данных
            break;
         }
         else
         {
            PathPrg.poll_step_S[i] = PathPrg.poll_step_S[i - 1];
         }
      }
      sgSPolling->Cells[1][i + 1] = FloatToStrF(PathPrg.poll_step_S[i], ffFixed, 6, 2);
      total_poll_S += PathPrg.poll_step_S[i];
      PathPrg.num_S_poll++;
      if (total_poll_S >= PathPrg.total_S)
         break;
   }
   if (PathPrg.num_S_poll == 0)
   {
      leSPollingTotalQty->Text = "";
      return;
   }
   leSPollingTotalQty->Text = String(PathPrg.num_S_poll);
   sbRB->Panels->Items[2]->Text = "Программа проверена!";
   btnCheckSProg->Enabled = false;
   btnSaveSProgToFile->Enabled = true;
   btnLoadSProgToPosA->Enabled = true;
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnNewSProg(TObject *Sender)
{
   leSProgName->Text = "";
   PathPrg.SProgName = "";
   leSTyrePressure->Text = "";
   PathPrg.STyrePressure = 0.0;
   leSTotalStepsQty->Text = "";
   PathPrg.total_step_S = 0;
   leTotalTestS->Text = "0";
   PathPrg.total_S = 0;
   leSPollingTotalQty->Text = "";
   PathPrg.num_S_poll = 0;
   for (int i = 0; i < MAXNUMOFSTEPS; i++)
   {
      sgSProgram->Cells[1][i + 1] = "";
      sgSProgram->Cells[2][i + 1] = "";
      sgSProgram->Cells[3][i + 1] = "";
   }
   for (int i = 0; i < MAXNUMOFPOLLS; i++)
   {
      sgSPolling->Cells[1][i + 1] = "";
   }
   PathPrg.Clear(); // чистка старых данных
}
// ---------------------------------------------------------------------------

void TmfRB::ShowProtAData(void)
   // отобразить шапку протокола в панели поз. А
{
   pCurrentProtATtl->Caption =
      "ПРОТОКОЛ ИСПЫТАНИЙ" // № "+String(mPosA.mTyre.ProtNo)+
      " НА СТЕНДЕ " + AnsiString(mPosA.mTyre.StandName.c_str()) + " (ПОЗ. А)";
   leTyreSyzeA->Text = AnsiString(mPosA.mTyre.Size.c_str());
   leTyreModelA->Text = AnsiString(mPosA.mTyre.Model.c_str());
   leManDateA->Text = AnsiString(mPosA.mTyre.CustomDate().c_str()); // DateToStr(mPosA.mTyre.ManufactDate);
   leSerialNoA->Text = String(mPosA.mTyre.SerialNo);
   leManufacturerA->Text = AnsiString(mPosA.mTyre.Manufacturer.c_str());
   leTestCustomerA->Text = AnsiString(mPosA.mTyre.TestCustomer.c_str());
   leFormNoA->Text = String(mPosA.mTyre.FormNo);
   lePerfSpecNoA->Text = String(mPosA.mTyre.PerfSpecNo);
   leTestProcA->Text = AnsiString(mPosA.mTyre.TestProcedure.c_str());
   leDrumD_A->Text = FloatToStrF(mPosA.mTyre.DrumDiameter, ffFixed, 7, 2);
   leOrderNoA->Text = String(mPosA.mTyre.OrderNo);
   if (mPosA.mTyre.Type == 0)
      pTyreParamATtl->Caption =
         "ХАРАКТЕРИСТИКИ ИСПЫТЫВАЕМОЙ" /* РАДИАЛЬНОЙ */ "ШИНЫ";
   else
      pTyreParamATtl->Caption =
         "ХАРАКТЕРИСТИКИ ИСПЫТЫВАЕМОЙ" /* ДИАГОНАЛЬНОЙ */ "ШИНЫ";
   leLoadIndA->Text = AnsiString(mPosA.mTyre.LoadIndex.c_str());
   leMaxLoadA->Text = FloatToStrF(mPosA.mTyre.MaxLoad, ffFixed, 6, 2);
   leSpeedIndA->Text = AnsiString(mPosA.mTyre.SpeedInd.c_str());
   leMaxSpeedA->Text = FloatToStrF(mPosA.mTyre.MaxSpeed, ffFixed, 6, 2);
   leTyreWideA->Text = FloatToStrF(mPosA.mTyre.ProfileWide, ffFixed, 6, 2);
   LogPrint("Profile Wide A=" + FloatToStrF(mPosA.mTyre.ProfileWide, ffFixed, 6, 1),
      clAqua);
   leStaticR_A->Text = FloatToStrF(mPosA.mTyre.StaticR, ffFixed, 6, 1);
   leOuterD_A->Text = FloatToStrF(mPosA.mTyre.OuterD, ffFixed, 6, 2);
   leRimA->Text = AnsiString(mPosA.mTyre.WheelRim.c_str());
   leQMaxPressureA->Text = FloatToStrF(mPosA.mTyre.MaxLoadPress, ffFixed, 6, 2);
   pTestResTtlA->Caption = "РЕЗУЛЬТАТЫ ИСПЫТАНИЙ";
   leTyrePressureA->Text = FloatToStrF(mPosA.mTyre.InitPressure, ffFixed, 6, 2);
   if (mPosA.mTyre.TestMode)
   {
      leTestModeA->Text = "по пути";
      leTestDurationA->EditLabel->Caption = "путь обкатки, км";
      leTestDurationA->Text = FloatToStrF(mPosA.mTyre.TotalS, ffFixed, 7, 2);
   }
   else
   {
      leTestModeA->Text = "по времени";
      leTestDurationA->EditLabel->Caption = "время обкатки";
      leTestDurationA->Text = AnsiString(dt::mSecToHMSStr(mPosA.mTyre.TotalTime).c_str());
   }
   leStepQtyA->Text = String(mPosA.mTyre.StepsNo);
   lePollsQtyA->Text = String(mPosA.mTyre.PollsNo);
}
// ---- End of ShowProtAData -------------------------------------------------

void TmfRB::ReadProtDataFmScrn(void)
   // прочитать данные протокола из экрана в InpTyre
{
   InpTyre.ProtNo = StrToI(leProtocolNo->Text);
   InpTyre.Size = AnsiString(leTyreSize->Text).c_str();
   InpTyre.Model = AnsiString(leTyreType->Text).c_str();
   InpTyre.TestProcedure = AnsiString(leTestProc->Text).c_str();
   InpTyre.StandName = AnsiString(leStandNo->Text).c_str();
   InpTyre.Manufacturer = AnsiString(leManufacturer->Text).c_str();
   InpTyre.DrumDiameter = StrToFloat(leDrumD->Text);
   InpTyre.TestCustomer = AnsiString(leCustomer->Text).c_str();
   // InpTyre.ManufactDate =StrToDate(meManDate->EditText);
   InpTyre.CustomDate(AnsiString(meManDate->EditText).c_str());
   InpTyre.SerialNo = StrToI(leSeralNo->Text);
   InpTyre.PerfSpecNo = StrToI(lePerfSpecNo->Text);
   InpTyre.OrderNo = StrToI(leOrderNo->Text);
   InpTyre.FormNo = StrToI(leFormNo->Text);
   InpTyre.LoadIndex = AnsiString(leLoadIndex->Text).c_str();
   InpTyre.MaxLoad = StrToFlt(leMaxLoad->Text);
   InpTyre.SpeedInd = AnsiString(leSpeedIndex->Text).c_str();
   InpTyre.MaxSpeed = StrToFlt(leMaxSpeed->Text);
   InpTyre.StaticR = StrToFlt(leStaticR->Text);
   InpTyre.OuterD = StrToFlt(leOuterD->Text);
   InpTyre.WheelRim = AnsiString(leRim->Text).c_str();
   InpTyre.MaxLoadPress = StrToFlt(leQMaxPressure->Text);
   InpTyre.ProfileWide = StrToI(leTyreWide->Text);
   InpTyre.Type = rgTyreType->ItemIndex;
   // InpTyre.CurrentLoad  =StrToFlt(leTestLoad->Text);
   // InpTyre.InitPressure =StrToFlt(leInitPressure->Text);
   // InpTyre.CurrentSpeed =StrToFlt(leTestSpeed->Text);
   InpTyre.TestMode = cmbTestMode->ItemIndex;
}
// ---------------------------------------------------------------------------

void TmfRB::DesignNewProtPanel(void)
   // расположение компонент на панели нового протокола
{
   int LblShift11 = leProtocolNo->EditLabel->Width, LblShift12 =
      leDrumD->EditLabel->Width, LblShift13 = lblManDate->Width, LblShift14 =
      leFormNo->EditLabel->Width;
   int LblShift21 = leMaxLoad->EditLabel->Width, LblShift22 =
      leQMaxPressure->EditLabel->Width, LblShift23 =
      leTyreWide->EditLabel->Width;
   int LineH0 = 26, Left0 = 3, Left1 = Left0 + LblShift11, PnlWidth =
      tsNewProtWidth - Left0 * 2, Top1 = 1, LineSpace1 = 5, LineH = 25, Top2 =
      Top1 + LineH0 + LineSpace1, LineSpase2 = LineH + LineSpace1, LblWidth1 =
      tsNewProtWidth / 10;
   if (LblWidth1 < 80)
      LblWidth1 = 80;
   int Left2 = Left1 + LblWidth1 + LblShift12 + Left0 + 10, Left3 =
      Left2 + LblWidth1 + LblShift13 + Left0, LblWidth2 =
      Left3 + LblWidth1 - Left2, LblWidth3 = tsNewProtWidth / 20;
   if (LblWidth3 < 40)
      LblWidth3 = 40;
   int Left4 = Left3 + LblWidth1 + LblShift14 + Left0;
   if ((Left4 + LblWidth3) < PnlWidth + Left0)
      Left4 = PnlWidth + Left0 - LblWidth3;
   pCommonProtData->Left = Left0;
   pCommonProtData->Top = Top1;
   pCommonProtData->Width = PnlWidth;
   pCommonProtData->Height = LineH0;
   leProtocolNo->Left = Left1;
   leProtocolNo->Top = Top2;
   leProtocolNo->Width = LblWidth1;
   leProtocolNo->Height = LineH;
   leTyreSize->Left = Left1;
   leTyreSize->Top = Top2 + LineSpase2;
   leTyreSize->Width = LblWidth1;
   leTyreSize->Height = LineH;
   leTyreType->Left = Left1;
   leTyreType->Top = Top2 + LineSpase2 * 2;
   leTyreType->Width = LblWidth1;
   leTyreType->Height = LineH;
   leTestProc->Left = Left1;
   leTestProc->Top = Top2 + LineSpase2 * 3;
   leTestProc->Width = LblWidth1;
   leTestProc->Height = LineH;
   leCustomer->Left = Left2;
   leCustomer->Top = Top2;
   leCustomer->Width = LblWidth2;
   leCustomer->Height = LineH;
   leStandNo->Left = Left2;
   leStandNo->Top = Top2 + LineSpase2;
   leStandNo->Width = LblWidth1;
   leStandNo->Height = LineH;
   leManufacturer->Left = Left2;
   leManufacturer->Top = Top2 + LineSpase2 * 2;
   leManufacturer->Width = LblWidth1;
   leManufacturer->Height = LineH;
   leDrumD->Left = Left2;
   leDrumD->Top = Top2 + LineSpase2 * 3;
   leDrumD->Width = LblWidth1;
   leDrumD->Height = LineH;
   lblManDate->Left = Left2 + LblWidth1 + Left0;
   lblManDate->Top = Top2 + LineSpase2;
   meManDate->Left = Left3;
   meManDate->Top = Top2 + LineSpase2;
   meManDate->Width = LblWidth1;
   meManDate->Height = LineH;
   leSeralNo->Left = Left3;
   leSeralNo->Top = Top2 + LineSpase2 * 2;
   leSeralNo->Width = LblWidth1;
   leSeralNo->Height = LineH;
   lePerfSpecNo->Left = Left3;
   lePerfSpecNo->Top = Top2 + LineSpase2 * 3;
   lePerfSpecNo->Width = LblWidth1;
   lePerfSpecNo->Height = LineH;
   leOrderNo->Left = Left4;
   leOrderNo->Top = Top2 + LineSpase2;
   leOrderNo->Width = LblWidth3;
   leOrderNo->Height = LineH;
   leFormNo->Left = Left4;
   leFormNo->Top = Top2 + LineSpase2 * 2;
   leFormNo->Width = LblWidth3;
   leFormNo->Height = LineH;
   pTyreParam->Left = Left0;
   pTyreParam->Top = Top2 + LineSpase2 * 3 + LineSpace1 + LineH;
   pTyreParam->Width = PnlWidth;
   pTyreParam->Height = LineH0;
   int Top3 = pTyreParam->Top + LineH0 + LineSpace1;
   int MaxLblShift2 = LblShift21 > LblShift22 ? LblShift21 : LblShift22;
   MaxLblShift2 = MaxLblShift2 > LblShift23 ? MaxLblShift2 : LblShift23;
   int LblSt = (PnlWidth - (MaxLblShift2 * 3 + LblWidth1 * 3)) / 2;
   Left1 = Left0 + MaxLblShift2 + 10;
   Left2 = Left1 + LblWidth1 + MaxLblShift2 + LblSt;
   Left3 = Left2 + LblWidth1 + MaxLblShift2 + LblSt;
   if ((Left3 + LblWidth1) < PnlWidth + Left0)
      Left3 = PnlWidth + Left0 - LblWidth1;
   Left4 = PnlWidth + Left0 - rgTyreType->Width;
   LblWidth2 = LblWidth1 * 3 / 2;
   if (LblWidth2 < 140)
      LblWidth2 = 140;
   leLoadIndex->Left = Left1;
   leLoadIndex->Top = Top3;
   leLoadIndex->Width = LblWidth1;
   leLoadIndex->Height = LineH;
   leMaxLoad->Left = Left1;
   leMaxLoad->Top = Top3 + LineSpase2;
   leMaxLoad->Width = LblWidth1;
   leMaxLoad->Height = LineH;
   leSpeedIndex->Left = Left1;
   leSpeedIndex->Top = Top3 + LineSpase2 * 2;
   leSpeedIndex->Width = LblWidth1;
   leSpeedIndex->Height = LineH;
   leMaxSpeed->Left = Left1;
   leMaxSpeed->Top = Top3 + LineSpase2 * 3;
   leMaxSpeed->Width = LblWidth1;
   leMaxSpeed->Height = LineH;
   leStaticR->Left = Left2;
   leStaticR->Top = Top3;
   leStaticR->Width = LblWidth1;
   leStaticR->Height = LineH;
   leOuterD->Left = Left2;
   leOuterD->Top = Top3 + LineSpase2;
   leOuterD->Width = LblWidth1;
   leOuterD->Height = LineH;
   leRim->Left = Left2;
   leRim->Top = Top3 + LineSpase2 * 2;
   leRim->Width = LblWidth1;
   leRim->Height = LineH;
   leQMaxPressure->Left = Left2;
   leQMaxPressure->Top = Top3 + LineSpase2 * 3;
   leQMaxPressure->Width = LblWidth1;
   leQMaxPressure->Height = LineH;
   leTyreWide->Left = Left3;
   leTyreWide->Top = Top3;
   leTyreWide->Width = LblWidth1;
   leTyreWide->Height = LineH;
   rgTyreType->Left = Left4 - 20;
   rgTyreType->Top = Top3 + LineSpase2;
   /* rgTyreType->Width     =LblWidth2; */ rgTyreType->Height = LineSpase2 * 2;
   // pTestMode->Left       =Left0;                  pTestMode->Top           =Top3+LineSpase2*3+LineH+LineSpace1;
   // pTestMode->Width      =PnlWidth;               pTestMode->Height        =LineH0;
   // int Top4=pTestMode->Top+LineH0+LineSpace1;
   // leTestLoad->Left      =Left1;                  leTestLoad->Top          =Top4;
   // leTestLoad->Width     =LblWidth1;              leTestLoad->Height       =LineH;
   // leInitPressure-;
   // leTestSpeed->Text);
   // lblTestMode->Left     =Left2-lblTestMode->Width; lblTestMode->Top       =Top4;
   // cmbTestMode->Left     =Left2;                    cmbTestMode->Top       =Top4;
   int Top5 = Top3 + LineSpase2 * 3 + LineH0 + LineH + LineSpace1 * 2,
      // Top4+cmbTestMode->Height+LineSpase2,
      btnWidth = (PnlWidth - 60) / 5;
   btnClearProt->Left = Left0;
   btnClearProt->Top = Top5;
   btnClearProt->Width = btnWidth;
   btnClearProt->Height = LineH * 2;
   btnSaveProtTtlToFile->Left = Left0 + btnWidth + 15;
   btnSaveProtTtlToFile->Top = Top5;
   btnSaveProtTtlToFile->Width = btnWidth;
   btnSaveProtTtlToFile->Height = LineH * 2;
   btnLoadProtTtlFmFile->Left = Left0 + btnWidth * 2 + 30;
   btnLoadProtTtlFmFile->Top = Top5;
   btnLoadProtTtlFmFile->Width = btnWidth;
   btnLoadProtTtlFmFile->Height = LineH * 2;
   btnLoadProtToPosA->Left = Left0 + btnWidth * 3 + 45;
   btnLoadProtToPosA->Top = Top5;
   btnLoadProtToPosA->Width = btnWidth;
   btnLoadProtToPosA->Height = LineH * 2;
}
// ---------------------------------------------------------------------------

void TmfRB::DesignProtAPanel(void)
   // расположение компонент на панели протокола поз. А
{
   int LblShift11 = lePerfSpecNoA->EditLabel->Width, LblShift12 =
      leTestProcA->EditLabel->Width, LblShift13 = leManDateA->EditLabel->Width,
      LblShift14 = leSerialNoA->EditLabel->Width;
   int LblShift21 = leTyrePressureA->EditLabel->Width, LblShift22 =
      leMaxLoadA->EditLabel->Width, LblShift23 = leStaticR_A->EditLabel->Width;
   int LblShift31 = leStepQtyA->EditLabel->Width, LblShift32 =
      lePollsQtyA->EditLabel->Width;
   int LineH0 = 26, Left0 = 3, Left1 = Left0 + LblShift11, PnlWidth =
      tsNewProtWidth - Left0 * 2, Top1 = 1, LineSpace1 = 5, LineH = 25, Top2 =
      Top1 + LineH0 + LineSpace1, LblWidth1 = tsNewProtWidth / 10;
   if (LblWidth1 < 80)
      LblWidth1 = 80;
   int Left2 = Left1 + LblWidth1 + LblShift12 + Left0 * 3, Left3 =
      Left2 + LblWidth1 + LblShift13 + Left0 * 3 + 20, LblWidth2 =
      Left3 + LblWidth1 - Left2, LblWidth3 = tsNewProtWidth / 20;
   if (LblWidth3 < 40)
      LblWidth3 = 40;
   int Left4 = Left3 + LblWidth1 + LblShift14 + Left0 * 3;
   if ((Left4 + LblWidth3) < PnlWidth + Left0)
      Left4 = PnlWidth + Left0 - LblWidth3;
   // LogPrint("LS11="+  String(LblShift11)+", LS12="+String(LblShift12)+
   // ", LS13="+String(LblShift13)+", LS14="+String(LblShift11));
   // LogPrint("LblW1="+String(LblWidth1)+", Lft1="+String(Left1)+", Lft2="+String(Left2)+
   // ", Lft3="+String(Left3)+", Lft4="+String(Left4));

   pCurrentProtATtl->Left = Left0;
   pCurrentProtATtl->Top = Top1;
   pCurrentProtATtl->Width = PnlWidth;
   pCurrentProtATtl->Height = LineH0;
   leManufacturerA->Left = Left1;
   leManufacturerA->Top = Top2;
   leManufacturerA->Width = LblWidth1;
   leManufacturerA->Height = LineH;
   leTyreModelA->Left = Left1;
   leTyreModelA->Top = Top2 + LineH;
   leTyreModelA->Width = LblWidth1;
   leTyreModelA->Height = LineH;
   lePerfSpecNoA->Left = Left1;
   lePerfSpecNoA->Top = Top2 + LineH * 2;
   lePerfSpecNoA->Width = LblWidth1;
   lePerfSpecNoA->Height = LineH;
   leTestCustomerA->Left = Left2;
   leTestCustomerA->Top = Top2;
   leTestCustomerA->Width = LblWidth2;
   leTestCustomerA->Height = LineH;
   leTyreSyzeA->Left = Left2;
   leTyreSyzeA->Top = Top2 + LineH;
   leTyreSyzeA->Width = LblWidth1;
   leTyreSyzeA->Height = LineH;
   leTestProcA->Left = Left2;
   leTestProcA->Top = Top2 + LineH * 2;
   leTestProcA->Width = LblWidth1;
   leTestProcA->Height = LineH;
   leManDateA->Left = Left3;
   leManDateA->Top = Top2 + LineH;
   leManDateA->Width = LblWidth1;
   leManDateA->Height = LineH;
   leDrumD_A->Left = Left3;
   leDrumD_A->Top = Top2 + LineH * 2;
   leDrumD_A->Width = LblWidth1;
   leDrumD_A->Height = LineH;
   leOrderNoA->Left = Left4;
   leOrderNoA->Top = Top2;
   leOrderNoA->Width = LblWidth3;
   leOrderNoA->Height = LineH;
   leSerialNoA->Left = Left4;
   leSerialNoA->Top = Top2 + LineH;
   leSerialNoA->Width = LblWidth3;
   leSerialNoA->Height = LineH;
   leFormNoA->Left = Left4;
   leFormNoA->Top = Top2 + LineH * 2;
   leFormNoA->Width = LblWidth3;
   leFormNoA->Height = LineH;
   pTyreParamATtl->Left = Left0;
   pTyreParamATtl->Top = Top2 + LineH * 3 + LineSpace1;
   pTyreParamATtl->Width = PnlWidth;
   pTyreParamATtl->Height = LineH0;
   int Top3 = Top2 + LineH * 3 + LineSpace1 * 2 + LineH0;
   // LblWidth1=tsNewProtWidth/10;
   Left1 = Left0 + LblShift21;
   Left2 = Left1 + LblWidth1 + LblShift22 + Left0 * 3 + 10;
   Left3 = Left2 + LblWidth1 + LblShift23 + Left0 * 3;
   if ((Left3 + LblWidth1) < PnlWidth + Left0)
      Left3 = PnlWidth + Left0 - LblWidth1;
   leLoadIndA->Left = Left1;
   leLoadIndA->Top = Top3;
   leLoadIndA->Width = LblWidth1;
   leLoadIndA->Height = LineH;
   leSpeedIndA->Left = Left1;
   leSpeedIndA->Top = Top3 + LineH;
   leSpeedIndA->Width = LblWidth1;
   leSpeedIndA->Height = LineH;
   leOuterD_A->Left = Left1;
   leOuterD_A->Top = Top3 + LineH * 2;
   leOuterD_A->Width = LblWidth1;
   leOuterD_A->Height = LineH;
   leMaxLoadA->Left = Left2;
   leMaxLoadA->Top = Top3;
   leMaxLoadA->Width = LblWidth1;
   leMaxLoadA->Height = LineH;
   leMaxSpeedA->Left = Left2;
   leMaxSpeedA->Top = Top3 + LineH;
   leMaxSpeedA->Width = LblWidth1;
   leMaxSpeedA->Height = LineH;
   leQMaxPressureA->Left = Left2;
   leQMaxPressureA->Top = Top3 + LineH * 2;
   leQMaxPressureA->Width = LblWidth1;
   leQMaxPressureA->Height = LineH;
   leStaticR_A->Left = Left3;
   leStaticR_A->Top = Top3;
   leStaticR_A->Width = LblWidth1;
   leStaticR_A->Height = LineH;
   leTyreWideA->Left = Left3;
   leTyreWideA->Top = Top3 + LineH;
   leTyreWideA->Width = LblWidth1;
   leTyreWideA->Height = LineH;
   leRimA->Left = Left3;
   leRimA->Top = Top3 + LineH * 2;
   leRimA->Width = LblWidth1;
   leRimA->Height = LineH;
   pTestResTtlA->Left = Left0;
   pTestResTtlA->Top = Top3 + LineH * 3 + LineSpace1;
   pTestResTtlA->Width = PnlWidth;
   pTestResTtlA->Height = LineH0;
   Left2 = Left1 + LblWidth1 + LblShift31 + Left0 * 3;
   Left3 = Left2 + LblWidth1 + LblShift32 + Left0 * 3;
   if ((Left3 + LblWidth1) < PnlWidth + Left0)
      Left3 = PnlWidth + Left0 - LblWidth1;
   int Top4 = Top3 + LineH * 3 + LineSpace1 * 2 + LineH0;
   leTyrePressureA->Left = Left1;
   leTyrePressureA->Top = Top4;
   leTyrePressureA->Width = LblWidth1;
   leTyrePressureA->Height = LineH;
   leTestModeA->Left = Left2;
   leTestModeA->Top = Top4;
   leTestModeA->Width = LblWidth1 * 2;
   leTestModeA->Height = LineH;
   leStepQtyA->Left = Left2;
   leStepQtyA->Top = Top4 + LineH;
   leStepQtyA->Width = LblWidth1;
   leStepQtyA->Height = LineH;
   leTestDurationA->Left = Left3;
   leTestDurationA->Top = Top4;
   leTestDurationA->Width = LblWidth1;
   leTestDurationA->Height = LineH;
   lePollsQtyA->Left = Left3;
   lePollsQtyA->Top = Top4 + LineH;
   lePollsQtyA->Width = LblWidth1;
   lePollsQtyA->Height = LineH;
   int Top5 = Top4 + LineH * 2 + LineSpace1;
   /* TGridRect myRect;
    myRect.Left=myRect.Right=myRect.Top=myRect.Bottom=-1;
    sgTestResultA->Selection=myRect; */
   int Col0W = 30, Col1W = 60, Col2W = 105, Col3W = 75, Col4W = 80, Col5W = 73,
      Col6W = 100;
   int TTableWidth = Col0W + Col1W + Col2W + Col3W + Col4W + Col5W + Col6W + 30;
   sgTestResultA->Left = Left0;
   sgTestResultA->Top = Top5;
   int TTableHeight = tsProtocolAHeight - Top5 - 5;
   int RowNo = TTableHeight / (sgTestResultA->RowHeights[0] + 1);
   TTableHeight = RowNo * sgTestResultA->RowHeights[0] + RowNo;
   sgTestResultA->Width = TTableWidth;
   sgTestResultA->Height = TTableHeight;
   sgTestResultA->ColWidths[0] = Col0W;
   sgTestResultA->ColWidths[1] = Col1W;
   sgTestResultA->ColWidths[2] = Col2W;
   sgTestResultA->ColWidths[3] = Col3W;
   sgTestResultA->ColWidths[4] = Col4W;
   sgTestResultA->ColWidths[5] = Col5W;
   sgTestResultA->ColWidths[6] = Col6W;
   sgTestResultA->Cells[0][0] = "№";
   sgTestResultA->Cells[1][0] = "Время";
   sgTestResultA->Cells[2][0] = "Скорость, км/час";
   sgTestResultA->Cells[3][0] = "Пробег, км";
   sgTestResultA->Cells[4][0] = "Нагрузка, кН";
   sgTestResultA->Cells[5][0] = "Радиус, мм";
   sgTestResultA->Cells[6][0] = "Температура, С";
   for (int i = 0; i < MAXNUMOFPOLLS; i++)
   {
      if (i < 9)
         sgTestResultA->Cells[0][i + 1] = "  " + String(i + 1) + ":";
      else if (i < 99)
         sgTestResultA->Cells[0][i + 1] = " " + String(i + 1) + ":";
      else
         sgTestResultA->Cells[0][i + 1] = String(i + 1) + ":";
   }
   Left1 = Left0 + TTableWidth + 10;
   int BtnWidth = tsNewProtWidth - Left1 - 10, BtnHeight =
      (tsNewProtHeight - Top5 - 20) / 3;
   if (BtnHeight > 45)
      BtnHeight = 45;
   btnLoadTestResPosA->Left = Left1;
   btnLoadTestResPosA->Top = Top5;
   btnLoadTestResPosA->Width = BtnWidth;
   btnLoadTestResPosA->Height = BtnHeight;

   btnSaveTestResPosAToFile->Left = Left1;
   btnSaveTestResPosAToFile->Top = Top5 + BtnHeight + 10;
   btnSaveTestResPosAToFile->Width = BtnWidth;
   btnSaveTestResPosAToFile->Height = BtnHeight;

   btnPrintTestResPosA->Left = Left1;
   btnPrintTestResPosA->Top = Top5 + BtnHeight * 2 + 20;
   btnPrintTestResPosA->Width = BtnWidth;
   btnPrintTestResPosA->Height = BtnHeight;

   btnResetResPosA->Left = Left1;
   btnResetResPosA->Top = Top5 + BtnHeight * 3 + 30;
   btnResetResPosA->Width = BtnWidth;
   btnResetResPosA->Height = BtnHeight;
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnClearProt(TObject *Sender)
{
   leProtocolNo->Text = "";
   leTyreSize->Text = "";
   leTyreType->Text = "";
   leTestProc->Text = "";
   leStandNo->Text = "13";
   leManufacturer->Text = "";
   leDrumD->Text = "1700";
   leCustomer->Text = "";
   meManDate->EditText = "00.00.2010";
   leSeralNo->Text = 0;
   lePerfSpecNo->Text = "";
   leOrderNo->Text = "";
   leFormNo->Text = "";
   leLoadIndex->Text = "";
   leMaxLoad->Text = "";
   leSpeedIndex->Text = "";
   leMaxSpeed->Text = "";
   leStaticR->Text = "";
   leOuterD->Text = "";
   leRim->Text = "";
   leQMaxPressure->Text = "";
   leTyreWide->Text = "";
   rgTyreType->ItemIndex = 0;
   cmbTestMode->ItemIndex = 0;
   // InpTyre.CurrentLoad  =StrToFlt(leTestLoad->Text);
   // InpTyre.InitPressure =StrToFlt(leInitPressure->Text);
   // InpTyre.CurrentSpeed =StrToFlt(leTestSpeed->Text);
   LogPrint("Экран протокола очищен для ввода нового протокола");
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnProtTtlFileSaveAs(TObject *Sender)
{ // Сохранить в файле заголовок протокола
   String FileName;
   if (Sender == acProtTitleFileSaveAs)
   { // ручное сохранение
      FileName = acProtTitleFileSaveAs->Dialog->FileName;
      acProtTitleFileSaveAs->Dialog->FileName = "";
   }
   else
   { // автосейв
      FileName = mData.strTitleProt.c_str() + Now().FormatString
         ("yyyy_mm_dd_hh_nn_ss'.prottitle'");
   }
   InpTyre.WriteToFile(AnsiString(FileName).c_str());
   LogPrint("Протокол сохранен в файле \"" + FileName + "\"");
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnProtTtlFileOpen(TObject *Sender)
{
   InpTyre.ReadFromFile(AnsiString(acProtTitleFileOpen->Dialog->FileName).c_str());
   ShowProtDataOnScrn();
   LogPrint("Протокол прочитан из файла \"" +
      acProtTitleFileOpen->Dialog->FileName + "\"");
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadProtToPosA(TObject *Sender)
{
   ReadProtDataFmScrn();
   mPosA.mTyre.ImportTemplate( InpTyre );
   ShowProtAData();
   mPosA.TyreType = mPosA.mTyre.Model;
   stP1L1TyreTypeA->Caption = AnsiString(mPosA.TyreType.c_str());
   LogPrint("Протокол загружен в поз. А");
}
// ---------------------------------------------------------------------------

void TmfRB::ShowProtDataOnScrn(void)
   // отобразить данные протокола из InpTyre на экране
{
   leProtocolNo->Text = String(InpTyre.ProtNo);
   leTyreSize->Text = AnsiString(InpTyre.Size.c_str());
   leTyreType->Text = AnsiString(InpTyre.Model.c_str());
   leTestProc->Text = AnsiString(InpTyre.TestProcedure.c_str());
   leStandNo->Text = AnsiString(InpTyre.StandName.c_str());
   leManufacturer->Text = AnsiString(InpTyre.Manufacturer.c_str());
   leDrumD->Text = FloatToStrF(InpTyre.DrumDiameter, ffFixed, 6, 2);
   leCustomer->Text = AnsiString(InpTyre.TestCustomer.c_str());
   meManDate->EditText = AnsiString(InpTyre.CustomDate().c_str());
   leSeralNo->Text = String(InpTyre.SerialNo);
   lePerfSpecNo->Text = String(InpTyre.PerfSpecNo);
   leOrderNo->Text = String(InpTyre.OrderNo);
   leFormNo->Text = String(InpTyre.FormNo);
   leLoadIndex->Text = AnsiString(InpTyre.LoadIndex.c_str());
   leMaxLoad->Text = FloatToStrF(InpTyre.MaxLoad, ffFixed, 6, 2);
   leSpeedIndex->Text = AnsiString(InpTyre.SpeedInd.c_str());
   leMaxSpeed->Text = FloatToStrF(InpTyre.MaxSpeed, ffFixed, 6, 2);
   leStaticR->Text = FloatToStrF(InpTyre.StaticR, ffFixed, 6, 2);
   leOuterD->Text = FloatToStrF(InpTyre.OuterD, ffFixed, 6, 2);
   leRim->Text = AnsiString(InpTyre.WheelRim.c_str());
   leQMaxPressure->Text = FloatToStrF(InpTyre.MaxLoadPress, ffFixed, 6, 2);
   leTyreWide->Text = String(InpTyre.ProfileWide);
   rgTyreType->ItemIndex = InpTyre.Type;
   cmbTestMode->ItemIndex = InpTyre.TestMode;
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadTestResFmPosA(TObject *Sender)
{
#ifndef _mDEBUG
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      return;
   }
#endif
   LogPrint("Загрузка результатов испытаний из контроллера по поз. A");
   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   auto &gr7 = *inst_cpu.mPos1->mGr7;
   gr3p1.Read();
   gr7.Read();
   mPosA.mTyre.TotalS = gr3p1.S_end_cycle; // fakt_distance_1
   mPosA.mTyre.TotalTime = gr3p1.T_end_cycle; // fakt_time_1
   mPosA.mTyre.TestMode = gr3p1.type_cycle;
   mPosA.mTyre.StepsNo = gr3p1.StepsQty;
   mPosA.mTyre.PollsNo = gr3p1.PollsQty;
   ShowProtAData();
#ifdef _mDEBUG
   mPosA.mTyre.PollsNo = 20;
#endif
   mPosA.mTyre.Clear();
   SGClear(sgTestResultA, 0); // чистка таблицы
   for (int i = 0; i < MAXNUMOFPOLLS && i < mPosA.mTyre.PollsNo; i++)
   {
      if (gr7.read_T[i] != 0 && gr7.read_V[i] != 0 && gr7.read_S[i] != 0 && gr7.read_L[i]
         != 0 && gr7.read_R[i] != 0 && gr7.read_Temp[i])
      { // +1 для отображения строки данных после пуволнения программы     + отсечка пустых данных
         sgTestResultA->Cells[0][sgTestResultA->RowCount - 1] =
            String(i + 1) + ":";
         sgTestResultA->Cells[1][sgTestResultA->RowCount - 1] =
            AnsiString(dt::mSecToHMSStr(gr7.read_T[i]).c_str());
         mPosA.mTyre.rT[i] = gr7.read_T[i];
         sgTestResultA->Cells[2][sgTestResultA->RowCount - 1] =
            FloatToStrF(gr7.read_V[i], ffFixed, 6, 2);
         mPosA.mTyre.rV[i] = gr7.read_V[i];
         sgTestResultA->Cells[3][sgTestResultA->RowCount - 1] =
            FloatToStrF(gr7.read_S[i], ffFixed, 6, 2);
         mPosA.mTyre.rS[i] = gr7.read_S[i];
         sgTestResultA->Cells[4][sgTestResultA->RowCount - 1] =
            FloatToStrF(gr7.read_L[i], ffFixed, 6, 2);
         mPosA.mTyre.rL[i] = gr7.read_L[i];
         sgTestResultA->Cells[5][sgTestResultA->RowCount - 1] =
            FloatToStrF(gr7.read_R[i], ffFixed, 6, 2);
         mPosA.mTyre.rR[i] = gr7.read_R[i];
         sgTestResultA->Cells[6][sgTestResultA->RowCount - 1] =
            FloatToStrF(gr7.read_Temp[i], ffFixed, 6, 2);
         mPosA.mTyre.rTemp[i] = gr7.read_Temp[i];
         sgTestResultA->RowCount++;
      }
   }
   if (sgTestResultA->RowCount > 2)
   {
      sgTestResultA->RowCount--;
   }
   sbRB->Panels->Items[2]->Text = "Результаты испытаний по поз. А загружены";
   btnSaveTestResPosAToFile->Click(); // сохранение
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnCloseQuery(TObject *Sender, bool &CanClose)
{
   int res = MessageBoxW(Handle, L"Подтвердите завершение работы",
      L"Выйти из программы?", MB_YESNO + MB_ICONQUESTION + MB_DEFBUTTON2);
   if (res == IDNO)
   {
      CanClose = false;
   }
   else // exit from prog
   {
      closing = true;
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintProtPosAToFile(TObject *Sender)
{ // Сохранить результаты испытаний в файле  А
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
      return;
   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   String FileName;
   if (Sender == acPrintProtPosAToFile)
   { // ручное сохранение
      FileName = acPrintProtPosAToFile->Dialog->FileName;
      acPrintProtPosAToFile->Dialog->FileName = "";
   }
   else
   { // автосейв
      FileName = mPosA.strProt.c_str() + Now().FormatString("yyyy_mm_dd_hh_nn_ss'.prtprot'");
   }
   mPosA.mTyre.PrintProtToFile(AnsiString(FileName).c_str());
   mPosA.needSave = !gr1p1.Stop;
   LogPrint("Результаты испытаний по поз. А сохранены в файле \"" +
      FileName + "\"");
   sbRB->Panels->Items[2]->Text =
      "Результаты испытаний по поз. А сохранены в файле \"" + FileName + "\"";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnVCalibrClear(TObject *Sender)
{
   DesignSpdCalibrPanel();
   VS.Clear();
   sbRB->Panels->Items[2]->Text =
      "Таблица аттестации скорости барабана очищена!";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnVCalibrCalc(TObject *Sender)
{
   int ind = VS.Index;
   VS.MeasuredV[ind] = StrToFlt(leMeasuredV->Text);
   VS.ReadoutV[ind] = StrToFlt(leReadV->Text);
   if (VS.MeasuredV[ind] > 0)
   {
      VS.RelError[ind] = (VS.MeasuredV[ind] - VS.ReadoutV[ind]);
      sgSpeedCalibr->Cells[2][ind + 1] = "    " + FloatToStrF(VS.ReadoutV[ind],
         ffFixed, 6, 2);
      sgSpeedCalibr->Cells[3][ind + 1] =
         "    " + FloatToStrF(VS.MeasuredV[ind], ffFixed, 6, 2);
      sgSpeedCalibr->Cells[4][ind + 1] = "    " + FloatToStrF(VS.RelError[ind],
         ffFixed, 6, 2);
      sbRB->Panels->Items[2]->Text = "Значение погрешности рассчитано!";
   }
   else
   {
      sbRB->Panels->Items[2]->Text = "Не введено измеренное значение скорости!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnNextCalibrVBtn(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя задать скорость - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &cmnp = inst_cpu.mCommonParams;

   int Ind = VS.Index;
   int RowCnt = sgSpeedCalibr->RowCount;
   // перерисовка предыдущей ячейки
   if (Ind < 9)
      sgSpeedCalibr->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgSpeedCalibr->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   VS.Index++;
   btnPrevCalibrV->Enabled = true;
   if (VS.Index >= RowCnt - 2)
   {
      VS.Index = RowCnt - 2;
      btnNextCalibrV->Enabled = false;
      // return;
   }
   // перерисовка текущей ячейки
   Ind = VS.Index;
   // sbRB->Panels->Items[2]->Text="Ind="+String(Ind);
   if (Ind < 9)
      sgSpeedCalibr->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgSpeedCalibr->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   // прокрутка таблицы
   // LogPrint("Next: TopRow="+String(sgSpeedCalibr->TopRow)+", VS.Index="+String(Ind),clAqua);
   bool IndLowerThenMiddleTable =
      ((Ind - sgSpeedCalibr->TopRow) >
      ((sgSpeedCalibr->VisibleRowCount) / 2 - 1));
   bool RowRestGreatThenTable =
      (sgSpeedCalibr->RowCount - sgSpeedCalibr->TopRow) >
      (sgSpeedCalibr->VisibleRowCount);
   if (IndLowerThenMiddleTable && RowRestGreatThenTable)
      sgSpeedCalibr->TopRow++;
   leCurrentVSet->Text = FloatToStrF(VS.TargetV[VS.Index], ffFixed, 6, 2);
   cmnp.DrumSpeed = VS.TargetV[VS.Index];
   cmnp.Write();

}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrevCalibrVBtn(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя задать скорость - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &cmnp = inst_cpu.mCommonParams;
   int Ind = VS.Index;
   int RowCnt = sgSpeedCalibr->RowCount;
   // перерисовка предыдущей ячейки
   if (Ind < 9)
      sgSpeedCalibr->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgSpeedCalibr->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   VS.Index--;
   btnNextCalibrV->Enabled = true;
   if (VS.Index <= 0)
   {
      VS.Index = 0;
      btnPrevCalibrV->Enabled = false;
      // return;
   }
   // перерисовка текущей ячейки
   Ind = VS.Index;
   if (Ind < 9)
      sgSpeedCalibr->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgSpeedCalibr->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   // прокрутка таблицы
   // LogPrint("Prev: TopRow="+String(sgSpeedCalibr->TopRow)+", VS.Index="+String(Ind),clAqua);
   bool IndAboveThenMiddleTable =
      ((Ind - sgSpeedCalibr->TopRow) <
      ((sgSpeedCalibr->VisibleRowCount) / 2 - 1));
   // bool RowRestGreatThenTable=(sgSpeedCalibr->RowCount-sgSpeedCalibr->TopRow)>(sgSpeedCalibr->VisibleRowCount);
   if (IndAboveThenMiddleTable && sgSpeedCalibr->TopRow > 1)
      sgSpeedCalibr->TopRow--;
   leCurrentVSet->Text = FloatToStrF(VS.TargetV[VS.Index], ffFixed, 6, 2);
   cmnp.DrumSpeed = VS.TargetV[VS.Index];
   cmnp.Write();
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnCalibrDrawCell(TObject *Sender, int ACol, int ARow,
   TRect &Rect, TGridDrawState State)
{
   int SlctRow;
   if ((TStringGrid*) Sender == sgSpeedCalibr)
   {
      SlctRow = (VS.Index + 1);
      // LogPrint("Selected Speed row is "+String(SlctRow),clAqua);
   }
   else if ((TStringGrid*) Sender == sgLoadCalibrA)
   {
      SlctRow = (mPosA.mLdS.Index + 1);
      // LogPrint("Selected Load A row is "+String(SlctRow),clAqua);
   }
   else if ((TStringGrid*) Sender == sgTCalibrA)
   {
      SlctRow = (mPosA.mTS.Index + 1);
      // LogPrint("Selected Load B row is "+String(SlctRow),clAqua);
   }
   else if ((TStringGrid*) Sender == sgRCalibrA)
   {
      SlctRow = (mPosA.mRS.Index + 1);
      // LogPrint("Selected Load B row is "+String(SlctRow),clAqua);
   }
   else if ((TStringGrid*) Sender == sgLoadSertA)
   {
      SlctRow = (mPosA.mLdC.Index + 1);
      // LogPrint("Selected Load B row is "+String(SlctRow),clAqua);
   }
   else
      return;
   if ((ACol == 0) && (ARow == SlctRow))
   {
      ((TStringGrid*) Sender)->Canvas->Brush->Color = clAqua;
      ((TStringGrid*) Sender)->Canvas->FillRect(Rect);
      ((TStringGrid*) Sender)->Canvas->TextOutA(Rect.Left, Rect.Top,
         sgSpeedCalibr->Cells[ACol][ARow]);
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintSpdCalibrProtocol(TObject *Sender)
{ // Распечатать протокол (Аттестация барабана)
   AnsiString FileName;
   if (Sender == acPrintSpdCalibrProt)
   { // ручное сохранение
      FileName = acPrintSpdCalibrProt->Dialog->FileName;
      acPrintSpdCalibrProt->Dialog->FileName = "";
   }
   else
   { // автосейв
      FileName = mData.strSpdCalibr.c_str() + Now().FormatString
         ("yyyy_mm_dd_hh_nn_ss'.scprt'");
   }
   VS.PrintProtocol(FileName.c_str());
   LogPrint("Протокол аттестации барабана сохранен в файле \"" +
      FileName + "\"");
   sbRB->Panels->Items[2]->Text =
      "Протокол аттестации барабана сохранен в файле \"" + FileName + "\"";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPump1On(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя включить насос - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;

   if (gr1p1.ManualMode)
   {
      gr1p1.PumpOn = true;
      gr1p1.KeepLoad = true;
      if (pcRB->ActivePage == tsCalibration)
      {
         // if(pcCalibration->ActivePage==tsLoadCalibrA || pcCalibration->ActivePage==tsLoadCalibrB){
         gr3p1.Loading = mPosA.mLdS.TargetLd[mPosA.mLdS.Index];
         LogPrint("Mode: LoadSert, LoadingA=" + FloatToStr(gr3p1.Loading));
         LogPrint(
            "Режим аттестации нагрузки, насос 1 включен, установлена нагрузка=" +
            FloatToStr(gr3p1.Loading));
         // }
      }
      else if (pcRB->ActivePage == tsSert)
      {
         if (pcSert->ActivePage == tsLoadSert)
         {
            gr3p1.Loading = mPosA.mLdC.TargetLd[mPosA.mLdC.Index];
            LogPrint("Mode: LoadCalibr, LoadingA=" + FloatToStr(gr3p1.Loading));
            LogPrint(
               "Режим калибровки нагрузки, насос 1 включен, установлена нагрузка=" +
               FloatToStr(gr3p1.Loading));
            leCurrentLoadSertSetA->Text =
               FloatToStrF(gr3p1.Loading, ffFixed, 6, 2);
         }
      }
      gr3p1.Write();
      gr1p1.Write();
      sbRB->Panels->Items[2]->Text = "Насос 1 включен!";
#ifdef USEPROCESSDELAY
      TLabeledEdit *leMeasLoad = 0;
      if (Sender == btnSertPumpOnA)
      {
         leMeasLoad = leMeasLoadSertA;
      }
      if (Sender == btnPumpOnA)
      {
         leMeasLoad = leMeasuredLoadA;
      }
      if (leMeasLoad)
      {
         leMeasLoad->ReadOnly = true;
         leMeasLoad->Color = clSilver;
         const int slp = 500; // 500 мс для слипа
         for (int i = 0; i < DELAY_TIME; i += slp)
         {
            Sleep(slp);
            Application->ProcessMessages(); // обработка сообщений винды
         }
         leMeasLoad->Color = clWindow;
         leMeasLoad->ReadOnly = false;
      }
#endif
   }
   else
   {
      sbRB->Panels->Items[2]->Text =
         "Насос 1 не включен - стенд не в ручном режиме!";
   }


}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPump1Off(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя выключить насос - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   if (gr1p1.ManualMode)
   {
      gr1p1.PumpOn = false;
      gr1p1.KeepLoad = false;
      gr1p1.Write();
      sbRB->Panels->Items[2]->Text = "Насос 1 выключен!";
      LogPrint( "Насос 1 выключен");
   }
   else
   {
      sbRB->Panels->Items[2]->Text =
         "Насос 1 не выключен - стенд не в ручном режиме!";
   }

}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnNextCalibrLoadBtn(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя задать нагрузку - нет соединения со стендом!";
      return;
   }


   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   sert::LSert *LdSert;
   TButton *btnNext, *btnPrev;
   TStringGrid *sgLoad;
   TLabeledEdit *leLoadSet, *leMeasLoad;
   float *Loading;
   int pos;
   if ((TButton*)Sender == btnNextCalibrLoadA)
   {
      LdSert = &mPosA.mLdS;
      btnNext = btnNextCalibrLoadA;
      btnPrev = btnPrevCalibrLoadA;
      sgLoad = sgLoadCalibrA;
      leLoadSet = leCurrentLoadSetA;
      leMeasLoad = leMeasuredLoadA;
      Loading = &gr3p1.Loading;
      pos = 0;
   }
   else
      return;
   int Ind = LdSert->Index;
   int RowCnt = sgLoad->RowCount;
   // перерисовка предыдущей ячейки
   if (Ind < 9)
      sgLoad->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgLoad->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   LdSert->Index++;
   btnPrev->Enabled = true;
   if (LdSert->Index >= RowCnt - 2)
   {
      LdSert->Index = RowCnt - 2;
      btnNext->Enabled = false;
      // return;
   }
   // перерисовка текущей ячейки
   Ind = LdSert->Index;
   if (Ind < 9)
      sgLoad->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgLoad->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   // прокрутка таблицы не требуется так как вся таблица на экране
   sgLoad->TopRow = 1;
   leLoadSet->Text = FloatToStrF(LdSert->TargetLd[LdSert->Index],
      ffFixed, 6, 2);
   leMeasLoad->Text = "0.0";
#ifdef USEPROCESSDELAY
   leMeasLoad->ReadOnly = true;
   leMeasLoad->Color = clSilver;
#endif
   *Loading = LdSert->TargetLd[LdSert->Index];
   if (pos == 0)
      LogPrint("Mode: Next load A, load=" + FloatToStr(*Loading));
   if (pos == 1)
      LogPrint("Mode: Next load B, load=" + FloatToStr(*Loading));

   for ( cpu::Position* ptr: inst_cpu.mPos )
      ptr->mGr3->Write();
#ifdef USEPROCESSDELAY
   const int slp = 500; // 500 мс для слипа
   for (int i = 0; i < DELAY_TIME; i += slp)
   {
      Sleep(slp);
      Application->ProcessMessages(); // обработка сообщений винды
   }
   leMeasLoad->Color = clWindow;
   leMeasLoad->ReadOnly = false;
#endif
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrevCalibrLoadBtn(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя задать нагрузку - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   sert::LSert *LdSert;
   TButton *btnNext, *btnPrev;
   TStringGrid *sgLoad;
   TLabeledEdit *leLoadSet, *leMeasLoad;
   float *Loading;
   int pos;
   if ((TButton*)Sender == btnPrevCalibrLoadA)
   {
      LdSert = &mPosA.mLdS;
      btnNext = btnNextCalibrLoadA;
      btnPrev = btnPrevCalibrLoadA;
      sgLoad = sgLoadCalibrA;
      leLoadSet = leCurrentLoadSetA;
      leMeasLoad = leMeasuredLoadA;
      Loading = &gr3p1.Loading;
      pos = 0;
   }
   else
      return;
   int Ind = LdSert->Index; // mPosA.mLdS.Index;
   int RowCnt = sgLoad->RowCount; // sgLoadCalibrA->RowCount;
   // перерисовка предыдущей ячейки
   if (Ind < 9)
      sgLoad->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgLoad->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   LdSert->Index--;
   btnNext->Enabled = true;
   if (LdSert->Index <= 0)
   {
      LdSert->Index = 0;
      btnPrev->Enabled = false;
      // return;
   }
   // перерисовка текущей ячейки
   Ind = LdSert->Index; // Ind=mPosA.mLdS.Index;
   // sbRB->Panels->Items[2]->Text="Ind="+String(Ind);
   if (Ind < 9)
      sgLoad->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgLoad->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   // прокрутка таблицы не требуется так как вся таблица на экране
   // LogPrint("Next: TopRow="+String(sgLoad->TopRow)+", mPosA.mLdS.Index="+String(Ind),clAqua);
   // bool IndAboveThenMiddleTable=((Ind-sgLoad->TopRow) < ((sgLoad->VisibleRowCount)/2-1));
   // if(IndAboveThenMiddleTable && sgLoad->TopRow>1)
   sgLoad->TopRow = 1;
   leLoadSet->Text =
      FloatToStrF(LdSert->TargetLd[Ind] /* mPosA.mLdS.TargetLd[mPosA.mLdS.Index] */ ,
      ffFixed, 6, 2);
   leMeasLoad->Text = "0.0";
#ifdef USEPROCESSDELAY
   leMeasLoad->ReadOnly = true;
   leMeasLoad->Color = clSilver;
#endif
   *Loading = LdSert->TargetLd[Ind]; // mPosA.mLdS.TargetLd[mPosA.mLdS.Index];
   if (pos == 0)
      LogPrint("Mode: Next load A, load=" + FloatToStr(*Loading));
   if (pos == 1)
      LogPrint("Mode: Next load B, load=" + FloatToStr(*Loading));

   for ( cpu::Position* ptr: inst_cpu.mPos )
      ptr->mGr3->Write();
#ifdef USEPROCESSDELAY
   const int slp = 500; // 500 мс для слипа
   for (int i = 0; i < DELAY_TIME; i += slp)
   {
      Sleep(slp);
      Application->ProcessMessages(); // обработка сообщений винды
   }
   leMeasLoad->Color = clWindow;
   leMeasLoad->ReadOnly = false;
#endif
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadCalibrTableClear(TObject *Sender)
{
   if ((TButton*)Sender == btnClearLoadCalibreTableA)
   {
      mPosA.mLdS.Clear();
      DesignLoadCalibrAPanel();
      sbRB->Panels->Items[2]->Text =
         "Таблица аттестации нагрузки поз. А очищена!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadCalibrCalc(TObject *Sender)
{
   sert::LSert *LdSert;
   TStringGrid *sgLoad;
   TLabeledEdit *leMeasLoad, *leReadoutLoad;
   if ((TButton*)Sender == btnLoadCalibrCalcA)
   {
      LdSert = &mPosA.mLdS;
      sgLoad = sgLoadCalibrA;
      leMeasLoad = leMeasuredLoadA;
      leReadoutLoad = leReadLoadA;
   }
   int ind = LdSert->Index;
   LdSert->MeasuredLd[ind] = StrToFlt(leMeasLoad->Text);
   LdSert->ReadoutLd[ind] = StrToFlt(leReadoutLoad->Text);
   if (LdSert->MeasuredLd[ind] > 0)
   {
      LdSert->RelError[ind] = (LdSert->MeasuredLd[ind] - LdSert->ReadoutLd[ind])
         / LdSert->MeasuredLd[ind] * 100.0;
      sgLoad->Cells[2][ind + 1] = "    " + FloatToStrF(LdSert->MeasuredLd[ind],
         ffFixed, 6, 2);
      sgLoad->Cells[3][ind + 1] = "    " + FloatToStrF(LdSert->ReadoutLd[ind],
         ffFixed, 6, 2);
      sgLoad->Cells[4][ind + 1] = "    " + FloatToStrF(LdSert->RelError[ind],
         ffFixed, 6, 2);
      sbRB->Panels->Items[2]->Text = "Значение погрешности рассчитано!";
   }
   else
   {
      sbRB->Panels->Items[2]->Text = "Не введено измеренное значение нагрузки!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintLoadCalibrProtA(TObject *Sender)
{ // Распечатать протокол (Аттестация по нагрузке) А
   AnsiString FileName;
   if (Sender == acPrintLoadCalibrProtA)
   { // ручное сохранение
      FileName = acPrintLoadCalibrProtA->Dialog->FileName;
      acPrintLoadCalibrProtA->Dialog->FileName = "";
   }
   else
   { // автосейв
      FileName = mPosA.strLoadCalibr.c_str() + Now().FormatString
         ("yyyy_mm_dd_hh_nn_ss'.lcprt'");
   }
   mPosA.mLdS.PrintProtocol(FileName.c_str());
   LogPrint("Протокол аттестации нагрузки поз. А сохранен в файле \"" +
      FileName + "\"");
   sbRB->Panels->Items[2]->Text =
      "Протокол аттестации нагрузки поз. А сохранен в файле \"" +
      FileName + "\"";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnNextCalibrTBtn(TObject *Sender)
{
   sert::TSert *TS;
   TButton *btnNext, *btnPrev;
   TStringGrid *sgTbl;
   TLabeledEdit *leMeas;
   float *Loading; // int pos=0;
   if ((TButton*)Sender == btnNextTCalibrA)
   {
      TS = &mPosA.mTS;
      btnNext = btnNextTCalibrA;
      btnPrev = btnPrevTCalibrA;
      sgTbl = sgTCalibrA;
      leMeas = leMeasTA;
      // pos    =0;
   }
   else
      return;
   int Ind = TS->Index;
   int RowCnt = sgTbl->RowCount;
   // перерисовка предыдущей ячейки
   if (Ind < 9)
      sgTbl->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgTbl->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   TS->Index++;
   btnPrev->Enabled = true;
   if (TS->Index >= RowCnt - 2)
   {
      TS->Index = RowCnt - 2;
      btnNext->Enabled = false;
      // return;
   }
   // перерисовка текущей ячейки
   Ind = TS->Index;
   if (Ind < 9)
      sgTbl->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgTbl->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   // прокрутка таблицы не требуется так как вся таблица на экране
   // LogPrint("Next: TopRow="+String(sgLoadCalibrA->TopRow)+", mPosA.mLdS.Index="+String(Ind),clAqua);
   // bool IndLowerThenMiddleTable=((Ind-sgLoadCalibrA->TopRow) > ((sgLoadCalibrA->VisibleRowCount)/2-1));
   // bool RowRestGreatThenTable=(sgLoadCalibrA->RowCount-sgLoadCalibrA->TopRow)>(sgLoadCalibrA->VisibleRowCount);
   // if(IndLowerThenMiddleTable && RowRestGreatThenTable)
   // sgLoadCalibrA->TopRow++;
   sgTbl->TopRow = 1;
   leMeas->Text = "0.0";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrevCalibrTBtn(TObject *Sender)
{
   sert::TSert *TS;
   TButton *btnNext, *btnPrev;
   TStringGrid *sgTbl;
   TLabeledEdit *leMeas;
   float *Loading; // int pos=0;
   if ((TButton*)Sender == btnPrevTCalibrA)
   {
      TS = &mPosA.mTS;
      btnNext = btnNextTCalibrA;
      btnPrev = btnPrevTCalibrA;
      sgTbl = sgTCalibrA;
      leMeas = leMeasTA;
      // pos    =0;
   }
   else
      return;
   int Ind = TS->Index;
   int RowCnt = sgTbl->RowCount;
   // перерисовка предыдущей ячейки
   if (Ind < 9)
      sgTbl->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgTbl->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   TS->Index--;
   btnNext->Enabled = true;
   if (TS->Index <= 0)
   {
      TS->Index = 0;
      btnPrev->Enabled = false;
   }
   // перерисовка текущей ячейки
   Ind = TS->Index;
   if (Ind < 9)
      sgTbl->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgTbl->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   sgTbl->TopRow = 1;
   leMeas->Text = "0.0";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnTCalibrTableClear(TObject *Sender)
{
   if ((TButton*)Sender == btnClearTCalibrTableA)
   {
      mPosA.mTS.Clear();
      DesignTCalibrAPanel();
      sbRB->Panels->Items[2]->Text =
         "Таблица аттестации датчика температуры поз. А очищена!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnTCalibrCalc(TObject *Sender)
{
   sert::TSert *TS;
   TStringGrid *sgTbl;
   TLabeledEdit *leMeas, *leRead;
   if ((TButton*)Sender == btnTCalibrCalcA)
   {
      TS = &mPosA.mTS;
      sgTbl = sgTCalibrA;
      leMeas = leMeasTA;
      leRead = leReadTA;
   }
   int ind = TS->Index;
   TS->MeasuredT[ind] = StrToFlt(leMeas->Text);
   TS->ReadoutT[ind] = StrToFlt(leRead->Text);
   // TS->ReadoutT[ind] =TS->MeasuredT[ind]*(1.0+float(50-random(100))/5000.0);   // DEBUG!!!!!!!!!!!!!!!!!!!
   // leRead->Text      =FloatToStrF(TS->ReadoutT[ind],ffFixed,6,2);              // DEBUG!!!!!!!!!!!!!!!!!!!
   if (TS->MeasuredT[ind] > 0)
   {
      TS->RelError[ind] = (TS->MeasuredT[ind] - TS->ReadoutT[ind]);
      sgTbl->Cells[1][ind + 1] = "    " + FloatToStrF(TS->ReadoutT[ind],
         ffFixed, 6, 2);
      sgTbl->Cells[2][ind + 1] = "    " + FloatToStrF(TS->MeasuredT[ind],
         ffFixed, 6, 2);
      sgTbl->Cells[3][ind + 1] = "    " + FloatToStrF(TS->RelError[ind],
         ffFixed, 6, 2);
      sbRB->Panels->Items[2]->Text = "Значение погрешности рассчитано!";
   }
   else
   {
      sbRB->Panels->Items[2]->Text =
         "Не введено измеренное значение температуры!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintTCalibrProtA(TObject *Sender)
{ // Распечатать протокол (Аттестация по температуре) А
   AnsiString FileName;
   if (Sender == acPrintTCalibrProtA)
   { // ручное сохранение
      FileName = acPrintTCalibrProtA->Dialog->FileName;
      acPrintTCalibrProtA->Dialog->FileName = "";
   }
   else
   { // автосейв
      FileName = mPosA.strTCalibr.c_str() + Now().FormatString
         ("yyyy_mm_dd_hh_nn_ss'.tcprt'");
   }
   mPosA.mTS.PrintProtocol(FileName.c_str());
   LogPrint("Протокол аттестации датчика температуры поз. А сохранен в файле \""
      + FileName + "\"");
   sbRB->Panels->Items[2]->Text =
      "Протокол аттестации датчика температуры поз. А сохранен в файле \"" +
      FileName + "\"";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnNextCalibrRBtn(TObject *Sender)
{
   sert::RSert *RS;
   TButton *btnNext, *btnPrev;
   TStringGrid *sgTbl;
   TLabeledEdit *leMeas;
   if ((TButton*)Sender == btnNextRCalibrA)
   {
      RS = &mPosA.mRS;
      btnNext = btnNextRCalibrA;
      btnPrev = btnPrevRCalibrA;
      sgTbl = sgRCalibrA;
      leMeas = leMeasRA;
   }
   else
      return;
   int Ind = RS->Index;
   int RowCnt = sgTbl->RowCount;
   // перерисовка предыдущей ячейки
   if (Ind < 9)
      sgTbl->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgTbl->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   RS->Index++;
   btnPrev->Enabled = true;
   if (RS->Index >= RowCnt - 2)
   {
      RS->Index = RowCnt - 2;
      btnNext->Enabled = false;
      // return;
   }
   // перерисовка текущей ячейки
   Ind = RS->Index;
   if (Ind < 9)
      sgTbl->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgTbl->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   sgTbl->TopRow = 1;
   leMeas->Text = "0.0";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrevCalibrRBtn(TObject *Sender)
{
   sert::RSert *RS;
   TButton *btnNext, *btnPrev;
   TStringGrid *sgTbl;
   TLabeledEdit *leMeas;
   if ((TButton*)Sender == btnPrevRCalibrA)
   {
      RS = &mPosA.mRS;
      btnNext = btnNextRCalibrA;
      btnPrev = btnPrevRCalibrA;
      sgTbl = sgRCalibrA;
      leMeas = leMeasRA;
   }
   else
      return;
   int Ind = RS->Index;
   int RowCnt = sgTbl->RowCount;
   // перерисовка предыдущей ячейки
   if (Ind < 9)
      sgTbl->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgTbl->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   RS->Index--;
   btnPrev->Enabled = true;
   if (RS->Index <= 0)
   {
      RS->Index = 0;
      btnNext->Enabled = false;
      // return;
   }
   // перерисовка текущей ячейки
   Ind = RS->Index;
   if (Ind < 9)
      sgTbl->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgTbl->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   // sgLoadCalibrA->TopRow++;
   sgTbl->TopRow = 1;
   leMeas->Text = "0.0";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnRCalibrTableClear(TObject *Sender)
{
   if ((TButton*)Sender == btnClearRCalibrTableA)
   {
      mPosA.mRS.Clear();
      DesignRCalibrAPanel();
      sbRB->Panels->Items[2]->Text =
         "Таблица аттестации радиуса поз. А очищена!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnRCalibrCalc(TObject *Sender)
{
   sert::RSert *RS;
   TStringGrid *sgTbl;
   TLabeledEdit *leMeas, *leRead;
   if ((TButton*)Sender == btnRCalibrCalcA)
   {
      RS = &mPosA.mRS;
      sgTbl = sgRCalibrA;
      leMeas = leMeasRA;
      leRead = leReadRA;
   }
   int ind = RS->Index;
   RS->MeasuredR[ind] = StrToFlt(leMeas->Text);
   RS->ReadoutR[ind] = StrToFlt(leRead->Text);
   if (RS->MeasuredR[ind] > 0)
   {
      RS->RelError[ind] = (RS->MeasuredR[ind] - RS->ReadoutR[ind]);
      sgTbl->Cells[1][ind + 1] = "    " + FloatToStrF(RS->ReadoutR[ind],
         ffFixed, 6, 2);
      sgTbl->Cells[2][ind + 1] = "    " + FloatToStrF(RS->MeasuredR[ind],
         ffFixed, 6, 2);
      sgTbl->Cells[3][ind + 1] = "    " + FloatToStrF(RS->RelError[ind],
         ffFixed, 6, 2);
      sbRB->Panels->Items[2]->Text = "Значение погрешности рассчитано!";
   }
   else
   {
      sbRB->Panels->Items[2]->Text = "Не введено измеренное значение радиуса!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintRCalibrProtA(TObject *Sender)
{ // Распечатать протокол (Аттестация по радиусу) А
   AnsiString FileName;
   if (Sender == acPrintRCalibrProtA)
   { // ручное сохранение
      FileName = acPrintRCalibrProtA->Dialog->FileName;
      acPrintRCalibrProtA->Dialog->FileName = "";
   }
   else
   { // автосейв
      FileName = mPosA.strRCalibr.c_str() + Now().FormatString
         ("yyyy_mm_dd_hh_nn_ss'.rcprt'");
   }
   mPosA.mRS.PrintProtocol(FileName.c_str());
   LogPrint("Протокол аттестации датчика положения поз. А сохранен в файле \"" +
      FileName + "\"");
   sbRB->Panels->Items[2]->Text =
      "Протокол аттестации датчика положения поз. А сохранен в файле \"" +
      FileName + "\"";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnNextSertLoadBtn(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя задать нагрузку - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   sert::LCalibr *LdCalibr;
   TButton *btnNext, *btnPrev;
   TStringGrid *sgLoad;
   TLabeledEdit *leLoadSet, *leMeasLoad;
   float *Loading;
   int pos;
   if ((TButton*)Sender == btnNextSertLoadA)
   {
      LdCalibr = &mPosA.mLdC;
      btnNext = btnNextSertLoadA;
      btnPrev = btnPrevSertLoadA;
      sgLoad = sgLoadSertA;
      leLoadSet = leCurrentLoadSertSetA;
      leMeasLoad = leMeasLoadSertA;
      Loading = &gr3p1.Loading;
      pos = 0;
   }
   else
      return;
   int Ind = LdCalibr->Index;
   int RowCnt = sgLoad->RowCount;
   // перерисовка предыдущей ячейки
   if (Ind < 9)
      sgLoad->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgLoad->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   LdCalibr->Index++;
   btnPrev->Enabled = true;
   if (LdCalibr->Index >= RowCnt - 2)
   {
      LdCalibr->Index = RowCnt - 2;
      btnNext->Enabled = false;
   }
   // перерисовка текущей ячейки
   Ind = LdCalibr->Index;
   if (Ind < 9)
      sgLoad->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgLoad->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   // прокрутка таблицы не требуется так как вся таблица на экране
   sgLoad->TopRow = 1;
   leLoadSet->Text = FloatToStrF(LdCalibr->TargetLd[LdCalibr->Index],
      ffFixed, 6, 2);
   leMeasLoad->Text = "0.0";
#ifdef USEPROCESSDELAY
   leMeasLoad->ReadOnly = true;
   leMeasLoad->Color = clSilver;
#endif
   *Loading = LdCalibr->TargetLd[LdCalibr->Index];
   if (pos == 0)
      LogPrint("Mode: Next load A, load=" + FloatToStr(*Loading));
   if (pos == 1)
      LogPrint("Mode: Next load B, load=" + FloatToStr(*Loading));


   for ( cpu::Position* ptr: inst_cpu.mPos )
      ptr->mGr3->Write();
#ifdef USEPROCESSDELAY
   const int slp = 500; // 500 мс для слипа
   for (int i = 0; i < DELAY_TIME; i += slp)
   {
      Sleep(slp);
      Application->ProcessMessages(); // обработка сообщений винды
   }
   leMeasLoad->Color = clWindow;
   leMeasLoad->ReadOnly = false;
#endif

}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrevSertLoadBtn(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя задать нагрузку - нет соединения со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   sert::LCalibr *LdCalibr;
   TButton *btnNext, *btnPrev;
   TStringGrid *sgLoad;
   TLabeledEdit *leLoadSet, *leMeasLoad;
   float *Loading;
   int pos;
   if ((TButton*)Sender == btnPrevSertLoadA)
   {
      LdCalibr = &mPosA.mLdC;
      btnNext = btnNextSertLoadA;
      btnPrev = btnPrevSertLoadA;
      sgLoad = sgLoadSertA;
      leLoadSet = leCurrentLoadSertSetA;
      leMeasLoad = leMeasLoadSertA;
      Loading = &gr3p1.Loading;
      pos = 0;
   }
   else
      return;
   int Ind = LdCalibr->Index;
   int RowCnt = sgLoad->RowCount;
   // перерисовка предыдущей ячейки
   if (Ind < 9)
      sgLoad->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgLoad->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   LdCalibr->Index--;
   btnNext->Enabled = true;
   if (LdCalibr->Index <= 0)
   {
      LdCalibr->Index = 0;
      btnPrev->Enabled = false;
   }
   // перерисовка текущей ячейки
   Ind = LdCalibr->Index;
   if (Ind < 9)
      sgLoad->Cells[0][Ind + 1] = "  " + String(Ind + 1) + ":";
   else if (Ind < RowCnt - 1)
      sgLoad->Cells[0][Ind + 1] = " " + String(Ind + 1) + ":";
   // прокрутка таблицы не требуется так как вся таблица на экране
   sgLoad->TopRow = 1;
   leLoadSet->Text = FloatToStrF(LdCalibr->TargetLd[LdCalibr->Index],
      ffFixed, 6, 2);
   leMeasLoad->Text = "0.0";
#ifdef USEPROCESSDELAY
   leMeasLoad->ReadOnly = true;
   leMeasLoad->Color = clSilver;
#endif
   *Loading = LdCalibr->TargetLd[LdCalibr->Index];
   if (pos == 0)
      LogPrint("Mode: Next load A, load=" + FloatToStr(*Loading));
   if (pos == 1)
      LogPrint("Mode: Next load B, load=" + FloatToStr(*Loading));

   for ( cpu::Position* ptr: inst_cpu.mPos )
      ptr->mGr3->Write();
#ifdef USEPROCESSDELAY
   const int slp = 500; // 500 мс для слипа
   for (int i = 0; i < DELAY_TIME; i += slp)
   {
      Sleep(slp);
      Application->ProcessMessages(); // обработка сообщений винды
   }
   leMeasLoad->Color = clWindow;
   leMeasLoad->ReadOnly = false;
#endif
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadSertTableClear(TObject *Sender)
{
   if ((TButton*)Sender == btnLoadSertClearTableA)
   {
      mPosA.mLdC.Clear();
      DesignLoadSertAPanel();
      sbRB->Panels->Items[2]->Text =
         "Таблица калибровки тензодатчика поз. А очищена!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadSertCalc(TObject *Sender)
{
   sert::LCalibr *LdCalibr;
   TStringGrid *sgLoad;
   TLabeledEdit *leMeasLoad, *leReadoutLoad;
   if ((TButton*)Sender == btnLoadSertCalcA)
   {
      LdCalibr = &mPosA.mLdC;
      sgLoad = sgLoadSertA;
      leReadoutLoad = leReadLoadSertA;
      leMeasLoad = leMeasLoadSertA;
   }
   else
      return;
   int ind = LdCalibr->Index;
   // leReadoutLoad->Text=FloatToStrF(LdCalibr->TargetLd[ind]+0.25,ffFixed,6,2); // DEBUG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   LdCalibr->MeasuredLd[ind] = StrToFlt(leMeasLoad->Text);
   LdCalibr->ReadoutLd[ind] = StrToFlt(leReadoutLoad->Text);
   if (LdCalibr->MeasuredLd[ind] > 0 && LdCalibr->ReadoutLd[ind] > 0)
   {
      LdCalibr->KA[ind] =
         (LdCalibr->MeasuredLd[ind] / LdCalibr->ReadoutLd[ind]);
      sgLoad->Cells[2][ind + 1] = "    " + FloatToStrF(LdCalibr->ReadoutLd[ind],
         ffFixed, 6, 2);
      sgLoad->Cells[3][ind + 1] =
         "    " + FloatToStrF(LdCalibr->MeasuredLd[ind], ffFixed, 6, 2);
      sgLoad->Cells[4][ind + 1] = "    " + FloatToStrF(LdCalibr->KA[ind],
         ffFixed, 8, 5);
      sbRB->Panels->Items[2]->Text = "Значение коэффициента рассчитано!";
   }
   else if (LdCalibr->MeasuredLd[ind] == 0)
   {
      sbRB->Panels->Items[2]->Text = "Не введено измеренное значение нагрузки!";
   }
   else if (LdCalibr->ReadoutLd[ind] == 0)
   {
      sbRB->Panels->Items[2]->Text = "Значение нагрузки на мониторе равно 0!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadSertToPLC(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя загрузить коэффициенты - нет связи со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   if ((TButton*)Sender == btnLoadSertAToPLC)
   {
      ReadLSertTable(&mPosA.mLdC, sgLoadSertA);
      // прочитали коэффициенты KA из таблицы
      auto &gr12 = *inst_cpu.mPos1->mGr12;
      mPosA.mLdC.LKSetting(gr12); // сохранили итоговые КА в А1
      gr12.Write(); // записали А1 в DB71
      sbRB->Panels->Items[2]->Text =
         "Коэффициенты калибровки тензодатчика по поз. А загружены в контроллер!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintLoadSertProtA(TObject *Sender)
{ // Распечатать протокол (калибровка тезодатчиков) А
   AnsiString FileName;
   if (Sender == acLoadSertPrintProtA)
   { // ручное сохранение
      FileName = acLoadSertPrintProtA->Dialog->FileName;
      acLoadSertPrintProtA->Dialog->FileName = "";
   }
   else
   { // автосейв
      FileName = mPosA.strSertPrintProt.c_str() + Now().FormatString
         ("yyyy_mm_dd_hh_nn_ss'.tcprt'");
   }
   mPosA.mLdC.PrintProtocol(FileName.c_str());
   LogPrint("Протокол калибровки тензодатчика поз. А сохранен в файле \"" +
      FileName + "\"");
   sbRB->Panels->Items[2]->Text =
      "Протокол калибровки тензодатчика поз. А сохранен в файле \"" +
      FileName + "\"";
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnLoadSpeedCoefToPLC(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя загрузить коэффициенты - нет связи со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   gr3p1.CorrSetSpeed = StrToFlt(leSetSpeedCoef->Text);
   gr3p1.CorrMeasSpeed = StrToFlt(leMeasSpeedCoef->Text);
   LogPrint("Коэффициент корректировки задания скорости: " +
      FloatToStrF(gr3p1.CorrSetSpeed, ffFixed, 7, 4), clAqua);
   LogPrint("Коэффициент корректировки измерения скорости: " +
      FloatToStrF(gr3p1.CorrMeasSpeed, ffFixed, 7, 4), clAqua);

   gr3p1.Write();
   sbRB->Panels->Items[2]->Text =
      "Коэффициенты корректировки скорости загружены в контроллер!";

}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnLSertCoefReset(TObject *Sender)
{
   int res = Application->MessageBox
      (L"Сброс коэффициентов калибровки (результаты предидущей калибровки будут потеряны)!",
      L"Подтвердите сброс!", MB_YESNO + MB_ICONQUESTION + MB_DEFBUTTON2);
   if (res == IDNO)
      return;
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя загрузить коэффициенты - нет связи со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   if ((TButton*)Sender == btnResetCalibrCoeffA)
   {
      auto &gr12 = *inst_cpu.mPos1->mGr12;
      gr12.ResetKA(); // сбросили коэффициенты А1 в единичку // записали А1 в DB71
      sbRB->Panels->Items[2]->Text =
         "Коэффициенты калибровки тензодатчика по поз. А в контроллере сброшены!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnSGSelectCell(TObject *Sender, int ACol, int ARow,
   bool &CanSelect)
{
   int EditedCol;
   if ((TStringGrid*) Sender == sgLoadSertA)
   {
      EditedCol = 4;
      // LogPrint("sgLoadSertA, ACol="+String(ACol),clLime);
   }
   else
      return;
   if (ACol == EditedCol)
   {
      ((TStringGrid*) Sender)->Options << goEditing;
      // LogPrint("ACol==EditedCol!",clLime);
   }
   else
   {
      // LogPrint("ACol!=EditedCol!",clRed);
      ((TStringGrid*) Sender)->Options >> goEditing;
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnTLimitsCalc(TObject *Sender)
{
   sert::TSert *TS;
   // TStringGrid *sgTemp;
   TEdit *edLowLimit, *edUpLimit;
   if ((TButton*)Sender == btnTLimitsCalcA)
   {
      TS = &mPosA.mTS;
      // sgTemp    =sgTCalibrA;
      edLowLimit = edCalcLowLimitA;
      edUpLimit = edCalcUpLimitA;
   }
   else
      return;
   int NT = 0;
   while (TS->ReadoutT[NT] != 0.0)
      NT++;
   // NT--;
   LogPrint("Number of non zero rows is " + String(NT), clLime);
   if (NT <= 1)
   {
      LogPrint("Cлишком мало данных для расчета - нужно хотя бы 2 точки!"
         , clRed);
      return;
   }
   float A, B, LowLim, UpLim;
   LeastSquares(TS->MeasuredT, TS->ReadoutT, NT, A, B);
   LowLim = A * LOWTLIM + B;
   UpLim = A * UPPERTLIM + B;
   LogPrint("A=" + FloatToStrF(A, ffFixed, 6, 2) + ", B=" + FloatToStrF(B,
      ffFixed, 6, 2), clLime);
   edLowLimit->Text = FloatToStrF(LowLim, ffFixed, 6, 2);
   edUpLimit->Text = FloatToStrF(UpLim, ffFixed, 6, 2);
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnTLimitsLoadToPLC(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя загрузить пределы измерения температуры - нет связи со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   int pos;
   float *TempLowLimit, *TempUpLimit;
   TEdit *edLowLimit, *edUpLimit;
   if ((TButton*)Sender == btnLoadTLimitsA)
   {
      edLowLimit = edLoadedLowLimitA;
      edUpLimit = edLoadedUpLimitA;
      TempLowLimit = &gr3p1.TempLowLimit;
      TempUpLimit = &gr3p1.TempUpLimit;
      pos = 0;
   }
   else
      return;
   *TempLowLimit = StrToFlt(edLowLimit->Text);
   *TempUpLimit = StrToFlt(edUpLimit->Text);

   for ( cpu::Position* ptr: inst_cpu.mPos )
      ptr->mGr3->Write();
   if (pos == 0)
      sbRB->Panels->Items[2]->Text =
         "Пределы измерения температуры по поз. А загружены в контроллер!";
   else
      sbRB->Panels->Items[2]->Text =
         "Пределы измерения температуры по поз. Б загружены в контроллер!";
}
// ---------------------------------------------------------------------------

void TmfRB::ReadLSertTable
   ( // считывание значений из таблицы в массив
   sert::LCalibr *LC, TStringGrid *Table)
{
   for (int i = 0; i < sert::LCalibr::ITEMS_COUNT; i++)
   {
      String tmp = Table->Cells[4][i + 1];
      if (DecimalSeparator == '.')
      {
         tmp = Replace(tmp, ",", String(DecimalSeparator));
      }
      else
      {
         tmp = Replace(tmp, ".", String(DecimalSeparator));
      }
      LC->KA[i] = StrToFlt(tmp);
   }
}
// ---- End of ReadLSertTable ------------------------------------------------

void __fastcall TmfRB::OnUploadLSertFmPLC(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя прочитать коэффициенты - нет связи со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   if ((TButton*)Sender == btnUploadSertAFmPLC)
   {
      auto &gr12 = *inst_cpu.mPos1->mGr12;
      gr12.Read(); // прочитали коэффициенты А из DB71
      mPosA.mLdC.LKRead(gr12); // сохранили прочитанные коэффициенты в ReadKA
      for (int i = 0; i < sert::LCalibr::ITEMS_COUNT; i++)
      { // записали коэффициенты в таблицу
         sgLoadSertA->Cells[4][i + 1] =
            FloatToStrF(mPosA.mLdC. /* Read */ KA[i], ffFixed, 8, 5);
      }
      sbRB->Panels->Items[2]->Text =
         "Коэффициенты калибровки тензодатчика по поз. А загружены из контроллера!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnRShiftLoadToPLC(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
   {
      sbRB->Panels->Items[2]->Text =
         "Нельзя загрузить смещения - нет связи со стендом!";
      return;
   }

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   float shift = 0 ;
   if ((TButton*)Sender == btnRShiftALoadToPLC)
   {
      LogPrint(
         "Текущие значения пределов радиусов для поз. А:");
      LogPrint( "Нижний: " + FloatToStrF(gr3p1.RadLowLimit, ffFixed,
         7, 2) + ", верхний: " + FloatToStrF(gr3p1.RadUpLimit, ffFixed, 7, 2));
      shift = StrToFlt(leRShiftA->Text);
      gr3p1.RadLowLimit += shift;
      gr3p1.RadUpLimit += shift;
      LogPrint( "Новые значения пределов радиусов для поз. А:");
      LogPrint( "Нижний: " + FloatToStrF(gr3p1.RadLowLimit, ffFixed,
         7, 2) + ", верхний: " + FloatToStrF(gr3p1.RadUpLimit, ffFixed, 7, 2));
      gr3p1.Write();
      sbRB->Panels->Items[2]->Text =
         "Новые значения пределов радиуса по поз. А загружены в контроллер!";
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrintProtocol(TObject *Sender)
{
   if ((TButton*)Sender == btnPrintTestResPosA)
   {
      sbRB->Panels->Items[2]->Text = "Печать протокола испытаний по поз. А!";
      printing::Print( pProtPrt, mPosA.mTyre );
      sbRB->Panels->Items[2]->Text =
         "Протокол испытаний по поз. А выведен на принтер!";
      LogPrint( "Протокол испытаний по поз. А выведен на принтер!",
         clSkyBlue);
   }
}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::OnPrinterFontSelect(TObject *Sender)
{
   if (PrinterFontDialog->Execute())
   {
      pProtPrt->Canvas->Font->Assign(PrinterFontDialog->Font);
      LogPrint("Выбран шрифт \"" + PrinterFontDialog->Font->Name + "\"",
         clMoneyGreen);
   }

}
// ---------------------------------------------------------------------------

void __fastcall TmfRB::acSettingsManagmentExecute(TObject *Sender)
{
   std::unique_ptr<TAppManagment>wnd(new TAppManagment(this, DB));
   wnd->ShowModal();
   GetSettings();
}

void TmfRB::GetSettings(void)
{
   mData.AutoSave = TAppManagment::Get_param(L"File_Save_Mode", DB) == "Auto" ?
      true : false;
   mData.strDistProg = TAppManagment::Get_param(L"Sprog", DB);
   mData.strTimeProg = TAppManagment::Get_param(L"Tprog", DB);
   mPosA.strProt = TAppManagment::Get_param(L"TestResPosA", DB);
   mData.strTitleProt = TAppManagment::Get_param(L"ProtTtl", DB);

   mPosA.strLoadCalibr = TAppManagment::Get_param(L"LoadCalibrTableA", DB);
   mPosA.strTCalibr = TAppManagment::Get_param(L"TCalibrTableA", DB);
   mPosA.strRCalibr = TAppManagment::Get_param(L"RCalibrTableA", DB);
   mData.strSpdCalibr = TAppManagment::Get_param(L"SpdCalibrTable", DB);

   mPosA.strSertPrintProt = TAppManagment::Get_param(L"LoadSertPrintProtA", DB);
   // проверка наличия директорий

   mData.strDistProg = DirectoryExists(mData.strDistProg.c_str()) ? mData.strDistProg : std::string();
   mData.strTimeProg = DirectoryExists(mData.strTimeProg.c_str()) ? mData.strTimeProg : std::string();
   mPosA.strProt = DirectoryExists(mPosA.strProt.c_str()) ? mPosA.strProt : std::string();
   mData.strTitleProt = DirectoryExists(mData.strTitleProt.c_str()) ? mData.strTitleProt : std::string();
   mPosA.strLoadCalibr = DirectoryExists(mPosA.strLoadCalibr.c_str()) ? mPosA.strLoadCalibr : std::string();
   mPosA.strTCalibr = DirectoryExists(mPosA.strTCalibr.c_str()) ? mPosA.strTCalibr : std::string();
   mPosA.strRCalibr = DirectoryExists(mPosA.strRCalibr.c_str()) ? mPosA.strRCalibr : std::string();
   mData.strSpdCalibr = DirectoryExists(mData.strSpdCalibr.c_str()) ? mData.strSpdCalibr : std::string();
   mPosA.strSertPrintProt = DirectoryExists(mPosA.strSertPrintProt.c_str()) ? mPosA.strSertPrintProt : std::string();

   /* переподключение функций по настройкам */
   if (mData.AutoSave)
   {
      // замена в меню

      amRB->ActionBars->operator[](0)->Items->operator[](0)->Items->operator[]
         (1)->Action = mData.strDistProg != "" ? (TCustomAction*)_acTProgFileSaveAs :
         (TCustomAction*)acTProgFileSaveAs;

      amRB->ActionBars->operator[](0)->Items->operator[](0)->Items->operator[]
         (3)->Action = mData.strDistProg != "" ? (TCustomAction*)_acSProgFileSaveAs :
         (TCustomAction*)acSProgFileSaveAs;

      amRB->ActionBars->operator[](0)->Items->operator[](0)->Items->operator[]
         (5)->Action = mData.strTitleProt != "" ?
         (TCustomAction*)_acProtTitleFileSaveAs :
         (TCustomAction*)acProtTitleFileSaveAs;

      // замена на элементах управления если указан путь
      // btnSaveSProgToFile->Action      =mData.strDistProg      !=""?(TCustomAction *)_acSProgFileSaveAs      :(TCustomAction *)acSProgFileSaveAs;
      // btnSaveTProgToFile->Action      =mData.strTimeProg      !=""?(TCustomAction *)_acTProgFileSaveAs      :(TCustomAction *)acTProgFileSaveAs;
      // btnSaveProtTtlToFile->Action   =mData.strTitleProt      !=""?(TCustomAction *)_acProtTitleFileSaveAs   :(TCustomAction *)acProtTitleFileSaveAs;
      btnSaveTestResPosAToFile->Action = mPosA.strProt != "" ?
         (TCustomAction*)_acPrintProtPosAToFile :
         (TCustomAction*)acPrintProtPosAToFile;
      btnSpdCalibrTablePrint->Action = mData.strSpdCalibr != "" ?
         (TCustomAction*)_acPrintSpdCalibrProt :
         (TCustomAction*)acPrintSpdCalibrProt;
      btnLoadCalibrTableAPrint->Action = mPosA.strLoadCalibr != "" ?
         (TCustomAction*)_acPrintLoadCalibrProtA :
         (TCustomAction*)acPrintLoadCalibrProtA;
      btnTCalibrTableAPrint->Action = mPosA.strTCalibr != "" ?
         (TCustomAction*)_acPrintTCalibrProtA :
         (TCustomAction*)acPrintTCalibrProtA;
      btnRCalibrTableAPrint->Action = mPosA.strRCalibr != "" ?
         (TCustomAction*)_acPrintRCalibrProtA :
         (TCustomAction*)acPrintRCalibrProtA;
      btnLoadSertPrintProtA->Action = mPosA.strSertPrintProt != "" ?
         (TCustomAction*)_acLoadSertPrintProtA :
         (TCustomAction*)acLoadSertPrintProtA;
   }
   else
   {
      // замена в меню
      amRB->ActionBars->operator[](0)->Items->operator[](0)->Items->operator[]
         (1)->Action = acTProgFileSaveAs;
      amRB->ActionBars->operator[](0)->Items->operator[](0)->Items->operator[]
         (3)->Action = acSProgFileSaveAs;
      amRB->ActionBars->operator[](0)->Items->operator[](0)->Items->operator[]
         (5)->Action = acProtTitleFileSaveAs;

      // замена на элементах управления
      // btnSaveSProgToFile->Action      =acSProgFileSaveAs;
      // btnSaveTProgToFile->Action      =acTProgFileSaveAs;
      // btnSaveProtTtlToFile->Action   =acProtTitleFileSaveAs;
      btnSaveTestResPosAToFile->Action = acPrintProtPosAToFile;
      btnSpdCalibrTablePrint->Action = acPrintSpdCalibrProt;
      btnLoadCalibrTableAPrint->Action = acPrintLoadCalibrProtA;
      btnTCalibrTableAPrint->Action = acPrintTCalibrProtA;
      btnRCalibrTableAPrint->Action = acPrintRCalibrProtA;
      btnLoadSertPrintProtA->Action = acLoadSertPrintProtA;
   }
   // установка директорий по умолчанию
   // диалоги сохранения
   acSProgFileSaveAs->Dialog->InitialDir = mData.strDistProg.c_str();
   acTProgFileSaveAs->Dialog->InitialDir = mData.strTimeProg.c_str();
   acProtTitleFileSaveAs->Dialog->InitialDir = mData.strTitleProt.c_str();
   acPrintProtPosAToFile->Dialog->InitialDir = mPosA.strProt.c_str();
   acPrintSpdCalibrProt->Dialog->InitialDir = mData.strSpdCalibr.c_str();
   acPrintLoadCalibrProtA->Dialog->InitialDir = mPosA.strLoadCalibr.c_str();
   acPrintTCalibrProtA->Dialog->InitialDir = mPosA.strTCalibr.c_str();
   acPrintRCalibrProtA->Dialog->InitialDir = mPosA.strRCalibr.c_str();
   acLoadSertPrintProtA->Dialog->InitialDir = mPosA.strSertPrintProt.c_str();

   // загрузка
   acTProgFileOpen->Dialog->InitialDir = mData.strTimeProg.c_str();
   // Загрузить из файла программу по времени
   acSProgFileOpen->Dialog->InitialDir = mData.strDistProg.c_str();
   // Загрузить из файла программу по пути
   acProtTitleFileOpen->Dialog->InitialDir = mData.strTitleProt.c_str();
   // Загрузить из файла заголовок протокола

}

void TmfRB::SetIndication(TEdit *Indicator, bool state)
{
   Indicator->Color = state ? clLime : clRed;
}

// задание параметров по Enter
void __fastcall TmfRB::leSetLoad1KeyPress(TObject *Sender, wchar_t &Key)
{
   if (Key == 13)
   {
      CheckStend();
      auto& inst_cpu = cpu::CpuMemory::Instance();
      if (!inst_cpu.IsConnected())
         return;

      std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
      auto &gr1p1 = *inst_cpu.mPos1->mGr1;
      auto &gr3p1 = *inst_cpu.mPos1->mGr3;
      if (gr1p1.ManualMode)
      {
         double t = leSetLoad1->Text.Trim().ToDouble();
         if (CheckLoad(t))
         {
            gr3p1.Loading = t;
            tbCurrentLoad1->SelEnd = tbCurrentLoad1->Max -int(gr3p1.Loading);
            tbCurrentLoad1->SelStart = tbCurrentLoad1->Max -int(gr3p1.Loading);
            gr3p1.Write();
            tsManual->SetFocus();
         }
         else
         {
            MessageBox(Handle,
               _T("Значение нагрузки должно быть в пределах от 0 до 115"),
               _T("Ошибка"), MB_ICONERROR | MB_OK);
         }
      }
   }
}

void __fastcall TmfRB::leSetDrumSpeedKeyPress(TObject *Sender, wchar_t &Key)
{
   if (Key == 13)
   {
      CheckStend();
      auto& inst_cpu = cpu::CpuMemory::Instance();
      if (!inst_cpu.IsConnected())
         return;

      std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
      auto &cmnp = inst_cpu.mCommonParams;
      auto &gr1p1 = *inst_cpu.mPos1->mGr1;
      if ( gr1p1.ManualMode)
      {
         cmnp.DrumOn = true;
         cmnp.DrumOff = false;
         if (pcRB->ActivePage == tsManual)
         {
            double t = leSetDrumSpeed->Text.Trim().ToDouble();
            if (CheckSpeed(t))
            {
               cmnp.DrumSpeed = t;
               tbCurrentDrumSpeed->SelEnd = tbCurrentDrumSpeed->Max -int(cmnp.DrumSpeed);
               tbCurrentDrumSpeed->SelStart = tbCurrentDrumSpeed->Max -int(cmnp.DrumSpeed);
               cmnp.Write();
               tsManual->SetFocus();
            }
            else
            {
               MessageBox(Handle,
                  _T("Значение скорости должно быть в пределах от 0 до 170"),
                  _T("Ошибка"), MB_ICONERROR | MB_OK);
               return;
            }
         }
      }
   }
}

// сохранение имени программы в базе
void TmfRB::SetCurrProgA(const std::string &name)
{
   TAppManagment::Set_Param(L"ProgNameA", name.c_str(), DB);
}

std::string TmfRB::GetCurrProgA(void)
{
   return TAppManagment::Get_param(L"ProgNameA", DB);
}

void TmfRB::UpdateProgData(void)
   // обновление данных по программе из контроллера
{
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
      return;

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   for ( cpu::Position* ptr: inst_cpu.mPos )
      ptr->mGr3->Read();

   mPosA.mTyre.TotalS = gr3p1.S_end_cycle;
   mPosA.mTyre.TotalTime = gr3p1.T_end_cycle;
   mPosA.mTyre.TestMode = gr3p1.type_cycle;
   mPosA.mTyre.StepsNo = gr3p1.StepsQty;
   mPosA.mTyre.PollsNo = gr3p1.PollsQty;
}

// аварийные установки
void __fastcall TmfRB::btEmSettingsClick(TObject *Sender)
{
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
      return;

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   auto &cmnp = inst_cpu.mCommonParams;
   bool err = false, value = false;
   // проверка значения
   try
   {
      value += CheckLoad( leEmMaxLoad_1R, gr1p1.max_load);
      value += CheckSpeed( leEmMaxSpeedR, cmnp.max_speed );
      value += CheckSpeed( leEmMinSpeedR, cmnp.min_speed);
      value += CheckLoad( leEmMinLoad_1R, gr1p1.min_load);

      gr1p1.min_temp = leEmMinTemp_1R->Text.Trim().ToDouble();
      gr1p1.max_temp = leEmMaxTemp_1R->Text.Trim().ToDouble();
      gr1p1.Write();
      cmnp.Write();
      leEmMinTemp_1R->Color = clLime;
      leEmMaxTemp_1R->Color = clLime;
   }
   catch (...)
   {
      err = true;
      leEmMaxLoad_1R->Color = clRed;
      leEmMaxLoad_1R->Color = clRed;
      leEmMaxSpeedR->Color = clRed;
      leEmMinSpeedR->Color = clRed;
      leEmMinLoad_1R->Color = clRed;
      leEmMinTemp_1R->Color = clRed;
      leEmMaxTemp_1R->Color = clRed;
   }

   if (err)
   {
      MessageBox(Handle, _T("Введено не корректное значение"), _T("Ошибка"),
         MB_ICONERROR | MB_OK);
   }
   if (value)
   {
      MessageBox(Handle,
         _T("Значение нагрузки должно быть в пределах от 0 до 115\n Значение скорости должно быть в пределах от 0 до 170")
         , _T("Ошибка"), MB_ICONERROR | MB_OK);
   }
}

void __fastcall TmfRB::leEmMinLoad_1RKeyPress(TObject *Sender, wchar_t &Key)
{
   TLabeledEdit *lb = (TLabeledEdit*)Sender;
   lb->Color = clWindow;
}

// ---------------------------------------------------------------------------
// проверки вводимых данных
bool TmfRB::CheckLoad(double load, float& value, TColor& color)
{
   bool res = CheckLoad( load );
   if (res)
   {
      value = load;
      color = clLime;
   }
   else
      color = clRed;

   return !res;
}

bool TmfRB::CheckSpeed(double Speed, float& value, TColor& color)
{
   bool res = CheckSpeed( Speed );
   if (res)
   {
      value = Speed;
      color = clLime;
   }
   else
      color = clRed;

   return !res;
}

bool TmfRB::CheckLoad(double load)
{
   return load >= MIN_LOAD && load <= MAX_LOAD;
}
bool TmfRB::CheckSpeed(double Speed)
{
   return Speed >= MIN_SPEED && Speed <= MAX_SPEED;
}

bool TmfRB::CheckTime(int Time)
{
   return Time > 0;
}

bool TmfRB::CheckDistance(double Dist)
{
   return Dist > 0;
}

bool TmfRB::CheckProgLoad(TStringGrid *sg, int col, double min_val)
{
   for (int i = 1, sz = sg->RowCount; i < sz; ++i)
   {
      if (sg->Cells[col][i].Length() && sg->Cells[col][i].ToDouble() < min_val)
      {
         String err = "Недопустимо низкое значение нагрузки в строке " +
            String(i);
         MessageBoxW(Handle, err.w_str(),
            L"Недопустимо низкое значение нагрузки",
            MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
         return false;
      }
   }
   return true;
}

// ---------------------------------------------------------------------------

void __fastcall TmfRB::btnResetResPosAClick(TObject *Sender)
{
#ifndef _mDEBUG
   CheckStend();
   auto& inst_cpu = cpu::CpuMemory::Instance();
   if (!inst_cpu.IsConnected())
      return;
#endif

   std::lock_guard<std::recursive_mutex> lock( mCPUMutex );
   auto &gr1p1 = *inst_cpu.mPos1->mGr1;
   auto &gr3p1 = *inst_cpu.mPos1->mGr3;
   auto &gr7 = *inst_cpu.mPos1->mGr7;

   LogPrint("Сброс результатов испытаний из контроллера по поз. A");

   gr1p1.ResetData = true;
   gr1p1.Write();
   gr7.Reset();
   gr3p1.Read();

   mPosA.mTyre.TotalS = gr3p1.S_end_cycle;
   mPosA.mTyre.TotalTime = gr3p1.T_end_cycle;
   mPosA.mTyre.TestMode = gr3p1.type_cycle;
   mPosA.mTyre.StepsNo = gr3p1.StepsQty;
   mPosA.mTyre.PollsNo = gr3p1.PollsQty;

   mPosA.mTyre.Clear();
   SGClear(sgTestResultA, 0); // чистка таблицы
   ShowProtAData();
}

