// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("login\dialogs\GroupSelect.cpp", fselGroup);
USEFORM("login\AppManagnent.cpp", AppManagment);
USEFORM("login\dialogs\User_Data.cpp", UserData);
USEFORM("login\Login.cpp", LogInwnd);
USEFORM("Vershina_main.cpp", mfRB);
USEFORM("splash_screen\Head_band.cpp", Headband);
//---------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   { // Проверка не запущено ли уже приложение
      CreateMutex(NULL, true, "RBMainMutex");
      int Res = GetLastError();
      bool terminate = false;
      if (Res == ERROR_ALREADY_EXISTS)
      {
         ShowMessage("Это приложение уже запущено!");
         terminate = true;
      }
      if (Res == ERROR_INVALID_HANDLE)
      {
         ShowMessage("Имя mutex object уже имеется в системе!");
         terminate = true;
      }

      if (!terminate)
      {
         UnicodeString s;
         Application->Initialize();
         Application->MainFormOnTaskBar = true;
         Application->CreateForm(__classid(TmfRB), &mfRB);
       Application->Run();
      }
   }
   catch (Exception &exception)
   {
      Application->ShowException(&exception);
   }
   catch (...)
   {
      try
      {
         throw Exception("");
      }
      catch (Exception &exception)
      {
         Application->ShowException(&exception);
      }
   }
   return 0;
}
// ---------------------------------------------------------------------------
