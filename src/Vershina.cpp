// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <thread>
//---------------------------------------------------------------------------
USEFORM("login\dialogs\GroupSelect.cpp", fselGroup);
USEFORM("login\dialogs\User_Data.cpp", UserData);
USEFORM("login\AppManagnent.cpp", AppManagment);
USEFORM("login\Login.cpp", LogInwnd);
USEFORM("Vershina_main.cpp", mfRB);
USEFORM("splash_screen\Head_band.cpp", Headband);
//---------------------------------------------------------------------------
struct VS2013_threading_fix
{
    VS2013_threading_fix()
    {
        _Cnd_do_broadcast_at_thread_exit();
    }
} threading_fix;

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
