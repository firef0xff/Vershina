//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Head_band.cpp", Headband);
USEFORM("RB_main.cpp", mfRB);
USEFORM("login\AppManagnent.cpp", AppManagment);
USEFORM("login\Login.cpp", LogInwnd);
USEFORM("login\dialogs\GroupSelect.cpp", fselGroup);
USEFORM("login\dialogs\User_Data.cpp", UserData);
USEFORM("CD9904\keypad\num_keyboard.cpp", Num_Pannel);
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
