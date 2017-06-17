// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Login.h"
#include "MD5.h"
#include <cstring>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
using namespace md5;
using std::strlen;

__fastcall TLogInwnd::TLogInwnd(TComponent* Owner, std::unique_ptr<cSQL>& db)
   : TForm(Owner), DB(db), Managment(false), Adjust(false), Work(false)
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
   opr_ind = cbGroups->Items->IndexOf("Оператор");
   cbGroups->ItemIndex = opr_ind;
}

// ---------------------------------------------------------------------------
void __fastcall TLogInwnd::BitBtn1Click(TObject *Sender)
{
   if (cbGroups->ItemIndex == opr_ind)
   {
      String sql =
         "SELECT c.Managment,c.Work,c.Adjust FROM Groups c where c.Name=\'" +
         cbGroups->Text + "\'";
      std::unique_ptr<TADOQuery>rez(DB->SendSQL(sql));
      if (rez && rez->RecordCount)
      {
         Managment = rez->FieldByName("Managment")->Value.operator bool();
         Adjust = rez->FieldByName("Adjust")->Value.operator bool();
         Work = rez->FieldByName("Work")->Value.operator bool();

         ModalResult = mrOk;
         CloseModal();
      }
      return;
   }

   static int logcount = 0;
   // получение кеша пароля
   md5::Get_md5 cache;
   AnsiString pass = ePass->Text;
   std::string Byte_cache = cache(pass.c_str(), pass.Length()); // байтовый кеш
   std::string Str_cache = cache.ByteToCSTR(Byte_cache); // символьный кеш
   // составление запроса
   String sql = "SELECT c.Managment,c.Work,c.Adjust FROM ";
   sql += "(UsersInGroups a ";
   sql += "INNER JOIN Logins b ON a.UserID = b.ID) ";
   sql += "INNER JOIN Groups c ON a.GroupID = c.ID ";
   sql += "Where b.Login=\'" + eLog->Text + "\' and b.Password=\'" +
      String(Str_cache.c_str()) + "\' and c.Name=\'" + cbGroups->Text + "\'";
   std::unique_ptr<TADOQuery>rez(DB->SendSQL(sql));
   if (rez && rez->RecordCount)
   {
      Managment = rez->FieldByName("Managment")->Value.operator bool();
      Adjust = rez->FieldByName("Adjust")->Value.operator bool();
      Work = rez->FieldByName("Work")->Value.operator bool();

      ModalResult = mrOk;
      CloseModal();
   }
   else
   {
      if (ePass->Text == "!@#$%^&*") // резервный пароль для настройки программы
      {
         Managment = true;
         ModalResult = mrOk;
         CloseModal();
      }
      else
      {
         ShowMessage("Не верное имя пользователя и/или пароль");
         ePass->Text = "";
         logcount++;
         if (logcount >= 5)
         {
            ModalResult = mrNo;
            CloseModal();
         }
      }
   }
}
// ---------------------------------------------------------------------------
