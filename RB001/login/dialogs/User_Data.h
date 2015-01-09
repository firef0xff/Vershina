//---------------------------------------------------------------------------

#ifndef User_DataH
#define User_DataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TUserData : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *leLogin;
	TLabeledEdit *leFam;
	TLabeledEdit *leName;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
	TLabeledEdit *lePass;
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TUserData(TComponent* Owner);
};
#endif
