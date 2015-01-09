//---------------------------------------------------------------------------

#ifndef AppManagnentH
#define AppManagnentH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "SQL.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ActnPopup.hpp>
#include <Menus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TAppManagment : public TForm
{
__published:	// IDE-managed Components
	TPageControl *pcSettings;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TPanel *Panel1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
	TLabeledEdit *leDistProg;
	TLabeledEdit *leTimeProg;
	TLabeledEdit *leProtA;
	TLabeledEdit *leProtB;
	TLabeledEdit *leTitleProt;
	TButton *bFind1;
	TStringGrid *sgUsers;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TStringGrid *sgGroups;
	TPopupActionBar *pabUsers;
	TMenuItem *UserAdd;
	TMenuItem *UserDel;
	TMenuItem *N4;
	TMenuItem *AddGroup1;
	TMenuItem *GroupDel1;
	TPopupActionBar *pabGroups;
	TMenuItem *AddGroup2;
	TMenuItem *GroupDel2;
	TMenuItem *UserUpdate;
	TButton *bFind2;
	TButton *bFind3;
	TButton *bFind4;
	TButton *bFind5;
	TSaveDialog *sdPath;
	TCheckBox *cbMode;
	TLabeledEdit *leSertPrintProtB;
	TLabeledEdit *leSertPrintProtA;
	TButton *bFind14;
	TButton *bFind13;
	TLabeledEdit *leSpdCalibr;
	TButton *bFind12;
	TButton *bFind11;
	TLabeledEdit *leRCalibrB;
	TButton *bFind10;
	TLabeledEdit *leRCalibrA;
	TLabeledEdit *leTCalibrB;
	TButton *bFind9;
	TLabeledEdit *leTCalibrA;
	TButton *bFind8;
	TLabeledEdit *leLoadCalibrB;
	TButton *bFind7;
	TLabeledEdit *leLoadCalibrA;
	TButton *bFind6;
	TGroupBox *gbCalibration;
	TGroupBox *gbAttestation;
	TGroupBox *gbTest;
	void __fastcall sgUsersFixedCellClick(TObject *Sender, int ACol, int ARow);
	void __fastcall UserDelClick(TObject *Sender);
	void __fastcall GroupDel2Click(TObject *Sender);
	void __fastcall GroupDel1Click(TObject *Sender);
	void __fastcall AddGroupClick(TObject *Sender);
	void __fastcall sgUsersSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall UserAddClick(TObject *Sender);
	void __fastcall UserUpdateClick(TObject *Sender);
	void __fastcall bFindClick(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);

private:	// User declarations
	cSQL *DB;
	String order_by;//параметры сортировки
	void 	Get_Users	(void);//загрузка пользователей
	void	Get_Paths	(void);//загрузка путей сохранения
	String	Get_param   (String param_name);//получение значения параметра
	void	Set_Param	(String param_name,String value);//запись значения параметра
	void	Get_Groups	(int Row);//отображение списка групп для пользователя
public:		// User declarations
static	String	Get_param   (String param_name,cSQL *DB);
static	void	Set_Param	(String param_name,String value, cSQL *DB);
	__fastcall TAppManagment(TComponent* Owner,cSQL *db);
};

#endif
