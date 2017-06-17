// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "User_Data.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TUserData::TUserData(TComponent* Owner) : TForm(Owner)
{
}

void __fastcall TUserData::BitBtn1Click(TObject *Sender)
{
   if (leLogin->Text.Trim() != "")
   {
      ModalResult = mrOk;
      CloseModal();
   }
   else
   {
      MessageBoxW(Handle, L"Укажите логин", L"Внимание!",
      MB_ICONWARNING | MB_OK);
   }
}
