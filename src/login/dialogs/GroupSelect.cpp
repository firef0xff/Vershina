// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GroupSelect.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TfselGroup::TfselGroup(TComponent* Owner, std::unique_ptr<cSQL>& db)
   : TForm(Owner), DB(db)
{
   // заполнение комбы с группами
   cbGroups->Items->Clear();
   std::unique_ptr<TADOQuery>rez(DB->SendSQL("Select Name from Groups"));
   if (rez && rez->RecordCount)
   {
      for (rez->First(); !rez->Eof; rez->Next())
      {
         cbGroups->Items->AddObject(rez->FieldByName("Name")->Value, nullptr);
      }
   }
}
// ---------------------------------------------------------------------------
