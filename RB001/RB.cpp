//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("login\dialogs\User_Data.cpp", UserData);
USEFORM("login\Login.cpp", LogInwnd);
USEFORM("RB_main.cpp", mfRB);
USEFORM("login\dialogs\GroupSelect.cpp", fselGroup);
USEFORM("CD9904\keypad\num_keyboard.cpp", Num_Pannel);
USEFORM("Head_band.cpp", Headband);
USEFORM("login\AppManagnent.cpp", AppManagment);
USEFORM("CD9904\search_devices\Find_devices.cpp", Network_Scan);
USEFORM("CD9904\sensor_options\Set_settings.cpp", Settings);
USEFORM("ABOUT.cpp", AboutBox);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{ // ѕроверка не запущено ли уже приложение
		CreateMutex(NULL, true, "RBMainMutex");
		int Res=GetLastError();
		bool terminate=false;
		if(Res == ERROR_ALREADY_EXISTS)
		{
			ShowMessage("Ёто приложение уже запущено!");
			terminate=true;
		}
		if(Res == ERROR_INVALID_HANDLE)
		{
			ShowMessage("»м€ mutex object уже имеетс€ в системе!");
			terminate=true;
		}

		if (!terminate)
		{
			Application->Initialize();
			SetApplicationMainFormOnTaskBar(Application, true);
			Application->CreateForm(__classid(TmfRB), &mfRB);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
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
//---------------------------------------------------------------------------
