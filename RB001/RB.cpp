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
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{ // �������� �� �������� �� ��� ����������
		CreateMutex(NULL, true, "RBMainMutex");
		int Res=GetLastError();
		bool terminate=false;
		if(Res == ERROR_ALREADY_EXISTS)
		{
			ShowMessage("��� ���������� ��� ��������!");
			terminate=true;
		}
		if(Res == ERROR_INVALID_HANDLE)
		{
			ShowMessage("��� mutex object ��� ������� � �������!");
			terminate=true;
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
//---------------------------------------------------------------------------
