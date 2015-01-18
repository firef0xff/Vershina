//---------------------------------------------------------------------------

#ifndef Head_bandH
#define Head_bandH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class THeadband : public TForm
{
__published:	// IDE-managed Components
	TImage *Image;
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
public:		// User declarations
	__fastcall THeadband(TComponent* Owner);
};
#endif
