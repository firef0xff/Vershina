//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("датчик ЦД9904\поиск устройств\Find_devices.cpp", Network_Scan);
USEFORM("датчик ЦД9904\Клавиатура ввода\num_keyboard.cpp", Num_Pannel);
USEFORM("датчик ЦД9904\настройка датчика\Set_settings.cpp", Settings);
USEFORM("Идентификация пользователей\диалоговые окна\User_Data.cpp", UserData);
USEFORM("Идентификация пользователей\AppManagnent.cpp", AppManagment);
USEFORM("Идентификация пользователей\Login.cpp", LogInwnd);
USEFORM("Идентификация пользователей\диалоговые окна\GroupSelect.cpp", fselGroup);
USEFORM("Head_band.cpp", Headband);
USEFORM("RB_main.cpp", mfRB);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{ // Проверка не запущено ли уже приложение
		CreateMutex(NULL, true, "RBMainMutex");
		int Res=GetLastError();
		bool terminate=false;
		if(Res == ERROR_ALREADY_EXISTS)
		{
			ShowMessage("Это приложение уже запущено!");
			terminate=true;
		}
		if(Res == ERROR_INVALID_HANDLE)
		{
			ShowMessage("Имя mutex object уже имеется в системе!");
			terminate=true;
		}

		if (!terminate)
		{
			Application->Initialize();
			SetApplicationMainFormOnTaskBar(Application, true);
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
//---------------------------------------------------------------------------
