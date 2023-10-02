//---------------------------------------------------------------------------

#ifndef Set_settingsH
#define Set_settingsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

#ifndef nullptr
	#define nullptr 0
#endif

#include <fstream>
#include "num_keyboard.h"
#include "Find_devices.h"
#include "CD_9904.h"
#include <thread>
#include <memory>
class TSettings : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *Choose;
	TLabeledEdit *Addr;
	TLabeledEdit *Port;
	TComboBox *Diam;
	TLabel *Label1;
	TLabeledEdit *Dist1;
	TLabeledEdit *Time1;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox4;
	TLabeledEdit *nAddr;
	TBitBtn *sDist1;
	TGroupBox *GroupBox2;
	TLabeledEdit *Dist2;
	TLabeledEdit *Time2;
	TBitBtn *snAddr;
	TGroupBox *GroupBox5;
	TBitBtn *OK;
	TBitBtn *Cancel;
	TBitBtn *Defaults;
	TBitBtn *sTime1;
	TBitBtn *sDist2;
	TBitBtn *sTime2;
	TTimer *Timer1;
	TBitBtn *btUpdate;
	void __fastcall sDist1Click(TObject *Sender);
	void __fastcall sTime1Click(TObject *Sender);
	void __fastcall sDist2Click(TObject *Sender);
	void __fastcall sTime2Click(TObject *Sender);
	void __fastcall snAddrClick(TObject *Sender);
	void __fastcall DiamClick(TObject *Sender);
	void __fastcall ChooseClick(TObject *Sender);
	void __fastcall DefaultsClick(TObject *Sender);
	void __fastcall Dist1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall Time1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall Dist2KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall Time2KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall nAddrKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations

	std::shared_ptr<CD_9904::Sensor> sens;
	bool fromFileSettings(void);
	bool toFileSettings(void);
	void UpdateInfo(void);
	bool find;
	int addr;
	String port;
	bool connected;
public:		// User declarations
	CD_9904::Sensor * Get_Sensor(void)const{if (connected){return sens.get();}else {return 0;}};
	void	Set_DefaultSettings (void);
	void 	Connect(void);
	int	ResetBus_1(void);
	int	ResetBus_2(void);
	__fastcall TSettings(TComponent* Owner);
	__fastcall ~TSettings();
};


#endif
