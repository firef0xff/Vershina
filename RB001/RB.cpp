//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("������ ��9904\����� ���������\Find_devices.cpp", Network_Scan);
USEFORM("������ ��9904\���������� �����\num_keyboard.cpp", Num_Pannel);
USEFORM("������ ��9904\��������� �������\Set_settings.cpp", Settings);
USEFORM("������������� �������������\���������� ����\User_Data.cpp", UserData);
USEFORM("������������� �������������\AppManagnent.cpp", AppManagment);
USEFORM("������������� �������������\Login.cpp", LogInwnd);
USEFORM("������������� �������������\���������� ����\GroupSelect.cpp", fselGroup);
USEFORM("Head_band.cpp", Headband);
USEFORM("RB_main.cpp", mfRB);
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
