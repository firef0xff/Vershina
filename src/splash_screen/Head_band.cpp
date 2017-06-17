// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Head_band.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall THeadband::THeadband(TComponent* Owner) : TForm(Owner)
{
}

// ---------------------------------------------------------------------------
void __fastcall THeadband::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   CanClose = false;
}
