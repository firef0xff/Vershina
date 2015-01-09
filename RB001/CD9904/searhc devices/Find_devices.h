//---------------------------------------------------------------------------

#ifndef Find_devicesH
#define Find_devicesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>

#include "functions.h"
#include "CD_9904.h"
//---------------------------------------------------------------------------
class TNetwork_Scan : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *Speedometers;
	TPanel *Panel1;
	TBitBtn *Cancel;
	TBitBtn *OK;
	TBitBtn *Find_action;
	TProgressBar *PB;
	void __fastcall FormResize(TObject *Sender);
	void __fastcall SpeedometersFixedCellClick(TObject *Sender, int ACol, int ARow);
	void __fastcall SpeedometersDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall OKClick(TObject *Sender);
	void __fastcall Find_actionClick(TObject *Sender);  //поиск всех устройств на портах с сом1 до сом 9

private:	// User declarations
	void 	Greed_Sizing (void);
public:		// User declarations
	bool	FastSearch(void); //поиск первого устройства
	String 	Port;//порт к которому подключено устройство
	int     Adderess;//адрес устройства

	__fastcall TNetwork_Scan(TComponent* Owner);
	__fastcall TNetwork_Scan(TComponent* Owner,int addr,String port);
};

#endif
