//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Set_settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
__fastcall TSettings::TSettings(TComponent* Owner)
	: TForm(Owner),sens(0)
{
	TNetwork_Scan *scan=new TNetwork_Scan(this);
	addr=-1;
	port="";
	connected=false;
	if (!fromFileSettings()) //���� ������ �� �������� ��� ����� �� ���������� �� ...
	{
		find=scan->FastSearch();
		if (find)
		{
		addr=scan->Adderess;
		port=scan->Port;
		}
		delete scan;
	}
	if (addr>=0&&port!="")
	{
		Addr->Text=(String)addr;
		Port->Text=port;
		//������ ������ � ����
		toFileSettings();
		try
		{
			Connect();
		} catch (...)
		{
			Addr->Text="";
			Port->Text="";
			//addr=-1;
			//port="";
		}
	}else
	{
		Addr->Text="";
		Port->Text="";
	}
}
void TSettings::Connect(void)
{
	if (addr>=0&&port!=""&&!sens)
	{
		if (sens)
		{
			delete sens;
			sens=nullptr;
		}
		sens=new CD_9904::Sensor(port.w_str(),addr);
		connected=true;
	}
}
__fastcall TSettings::~TSettings()
{
	if (sens)
	{
		delete sens;
	}
}
//����������� ����������
void __fastcall TSettings::ChooseClick(TObject *Sender)
{
	if (sens)
	{
		delete sens;
		sens=0;
		connected=false;
	}
	TNetwork_Scan *wnd=new TNetwork_Scan(this,addr,port);
	if (wnd->ShowModal()==mrOk)
	{
		addr=wnd->Adderess;
		port=wnd->Port;
		if (addr>=0)
		{
			Addr->Text=(String)addr;
			Port->Text=port;
			//������ ������ � ����
			toFileSettings();
			Connect();
            UpdateInfo();
		}
	}
	delete wnd;
}
void 			TSettings::UpdateInfo(void)
{
	/*���������� ������������ ����������*/
	String msg="";
	nAddr->Text=(String)addr;
	//������ ������ �������
	unsigned short d=0;
	CD_9904::ErrCode err=sens->Read_Diametr(d);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ �������� ��������:"+CD_9904::Sensor::Get_Err(err);
	}else
	{
		Diam->ItemIndex=Diam->Items->IndexOf(String(d));
	}
	//������ ��������� ����
	CD_9904::Data * data=0;
	err=sens->Tansl_Speed(&data);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ ���������� ����������:"+CD_9904::Sensor::Get_Err(err);
	}else
	{
		if (data)
		{
			Dist1->Text=String(data->Road_1());
			Dist2->Text=String(data->Road_2());
			Time1->Text=data->Time_1().Get_time_string();
			Time2->Text=data->Time_2().Get_time_string();
		}
	}
	delete data;
	if (msg!="")
	{
		MessageBoxW(Handle,msg.w_str(),L"������",MB_ICONERROR|MB_OK);
	}
}
//���������
//---------------�����
void __fastcall TSettings::nAddrKeyPress(TObject *Sender, wchar_t &Key)
{
	snAddr->Click();
}
void __fastcall TSettings::snAddrClick(TObject *Sender)
{
	if (!sens) {return;}
	TNum_Pannel *wnd=new TNum_Pannel(this,0,2,1,32,nAddr->Text.ToIntDef(0),true);
	if (wnd->ShowModal()==mrOk)
	{
		String msg="";
		BYTE _addr=(BYTE)(wnd->Value.ToIntDef(-1));
		if (_addr>0)
		{//�������� ������������� ���������� � ����� �������
			if (sens->Init(_addr)!=CD_9904::ErrCode::Sucsess)
			{
				if (sens->Init((BYTE)addr)==CD_9904::ErrCode::Sucsess)
				{
					CD_9904::ErrCode err=sens->Write_ADDR(_addr);
					if (err==CD_9904::ErrCode::Sucsess)
					{
						addr=(int)_addr;
						Addr->Text=(String)addr;
						nAddr->Text=(String)addr;
					}else
					{
						msg=L"������ �������� ������ ���������� ��������: "+CD_9904::Sensor::Get_Err(err);
					}
				}else
				{
					msg=L"��� ����� � ��������������� �����������.";
				}
			}else
			{
				msg=L"���������� � ����� ������� ��� ����������, ������� ������ ������.";
			}
		}else
		{
			msg=L"������� ����� ������ ��� ����������";
		}
		nAddr->Text=wnd->Value;
		if (msg!="")
		{
			MessageBoxW(Handle,msg.w_str(),L"������",MB_ICONERROR|MB_OK);
		}
	}
	delete wnd;
}
void __fastcall TSettings::DiamClick(TObject *Sender)
{
	if (!sens) {return;}
	String msg="";
	if (Diam->ItemIndex>=0)
	{
		unsigned short d=(unsigned short)(Diam->Items->operator [](Diam->ItemIndex).ToIntDef(1700));
		CD_9904::ErrCode err=sens->Write_Diametr(d);
		if (err==CD_9904::ErrCode::Sucsess)
		{
			err=sens->Read_Diametr(d);
			if (err==CD_9904::ErrCode::Sucsess)
			{
				Diam->ItemIndex=Diam->Items->IndexOf(String(d));
			}else
			{
				msg=L"������ ������ ��������: "+CD_9904::Sensor::Get_Err(err);
			}
		}else
		{
			msg=L"������ ������ ��������: "+CD_9904::Sensor::Get_Err(err);
		}
	}else
	{
		msg=L"�� ������ �������";
	}
	if (msg!="")
	{
		MessageBoxW(Handle,msg.w_str(),L"������",MB_ICONERROR|MB_OK);
	}
}
//---------------���� 1
void __fastcall TSettings::Dist1KeyPress(TObject *Sender, wchar_t &Key)
{
	sDist1->Click();
}
void __fastcall TSettings::sDist1Click(TObject *Sender)
{
	if (!sens) {return;}
	TNum_Pannel *wnd=new TNum_Pannel(this,0,6,0,100000,Dist1->Text.ToIntDef(0),true);
	String msg="";
	if (wnd->ShowModal()==mrOk)
	{
		/*���������� ��������� � ���������� � �������������� � ����*/
		unsigned int _dist=wnd->Value.ToIntDef(0);
		CD_9904::ErrCode err=sens->Write_Road_1(_dist);
		if (err==CD_9904::ErrCode::Sucsess)
		{
			CD_9904::Data *data=0;
			err=sens->Tansl_Speed(&data);
			if (err==CD_9904::ErrCode::Sucsess)
			{
				Dist1->Text=String(data->Road_1());
				delete data;
			}else
			{
				msg=L"������ ������ ���� ���� 1: "+CD_9904::Sensor::Get_Err(err);
			}
		}else
		{
			msg=L"������ ������ ���� ���� 1: "+CD_9904::Sensor::Get_Err(err);
		}
		if (msg!="")
		{
			MessageBoxW(Handle,msg.w_str(),L"������",MB_ICONERROR|MB_OK);
		}
	}
	delete wnd;
}
void __fastcall TSettings::Time1KeyPress(TObject *Sender, wchar_t &Key)
{
	sTime1->Click();
}
void __fastcall TSettings::sTime1Click(TObject *Sender)
{
	if (!sens) {return;}
	String msg="";
	TNum_Pannel *wnd=new TNum_Pannel(this,2,4,0,1000,Time1->Text.ToIntDef(0),true,":");
	if (wnd->ShowModal()==mrOk)
	{
		/*���������� ��������� � ���������� � �������������� � ����*/
		CD_9904::CD_Time *_time=new CD_9904::CD_Time(wnd->Value);
		CD_9904::ErrCode err=sens->Write_Time_1(_time);
		if (err==CD_9904::ErrCode::Sucsess)
		{
			CD_9904::Data *data=0;
			err=sens->Tansl_Speed(&data);
			if (err==CD_9904::ErrCode::Sucsess)
			{
				Time1->Text=data->Time_1().Get_time_string();
				delete data;
			}else
			{
				msg=L"������ ������ ������� ���� 1: "+CD_9904::Sensor::Get_Err(err);
			}
		}else
		{
			msg=L"������ ������ ������� ���� 1: "+CD_9904::Sensor::Get_Err(err);
		}
		if (msg!="")
		{
			MessageBoxW(Handle,msg.w_str(),L"������",MB_ICONERROR|MB_OK);
		}
		delete _time;
	}
	delete wnd;
}
int			TSettings::ResetBus_1(void)
{
	CD_9904::ErrCode err=sens->Write_Road_1(0);
	if (err!=CD_9904::ErrCode::Sucsess) return err;
	CD_9904::CD_Time *_time=new CD_9904::CD_Time();
	err=sens->Write_Time_1(_time);
	delete _time;
	if (err!=CD_9904::ErrCode::Sucsess) return err;
	return CD_9904::ErrCode::Sucsess;
}

//---------------���� 2
void __fastcall TSettings::Dist2KeyPress(TObject *Sender, wchar_t &Key)
{
	sDist2->Click();
}
void __fastcall TSettings::sDist2Click(TObject *Sender)
{
	if (!sens) {return;}
	String msg="";
	TNum_Pannel *wnd=new TNum_Pannel(this,0,6,0,100000,Dist2->Text.ToIntDef(0),true);
	if (wnd->ShowModal()==mrOk)
	{
		/*���������� ��������� � ���������� � �������������� � ����*/
		unsigned int _dist=wnd->Value.ToIntDef(0);
		CD_9904::ErrCode err=sens->Write_Road_2(_dist);
		if (err==CD_9904::ErrCode::Sucsess)
		{
			CD_9904::Data *data=0;
			err=sens->Tansl_Speed(&data);
			if (err==CD_9904::ErrCode::Sucsess)
			{
				Dist2->Text=String(data->Road_2());
				delete data;
			}else
			{
				msg=L"������ ������ ���� ���� 2: "+CD_9904::Sensor::Get_Err(err);
			}
		}else
		{
			msg=L"������ ������ ���� ���� 2: "+CD_9904::Sensor::Get_Err(err);
		}
		if (msg!="")
		{
			MessageBoxW(Handle,msg.w_str(),L"������",MB_ICONERROR|MB_OK);
		}
	}
	delete wnd;
}
void __fastcall TSettings::Time2KeyPress(TObject *Sender, wchar_t &Key)
{
	sTime2->Click();
}
void __fastcall TSettings::sTime2Click(TObject *Sender)
{
    if (!sens) {return;}
	String msg="";
	TNum_Pannel *wnd=new TNum_Pannel(this,2,4,0,1000,Time2->Text.ToIntDef(0),true,":");
	if (wnd->ShowModal()==mrOk)
	{
		/*���������� ��������� � ���������� � �������������� � ����*/
		CD_9904::CD_Time *_time=new CD_9904::CD_Time(wnd->Value);
		CD_9904::ErrCode err=sens->Write_Time_2(_time);
		if (err==CD_9904::ErrCode::Sucsess)
		{
			CD_9904::Data *data=0;
			err=sens->Tansl_Speed(&data);
			if (err==CD_9904::ErrCode::Sucsess)
			{
				Time2->Text=data->Time_2().Get_time_string();
				delete data;
			}else
			{
				msg=L"������ ������ ������� ���� 1: "+CD_9904::Sensor::Get_Err(err);
			}
		}else
		{
			msg=L"������ ������ ������� ���� 1: "+CD_9904::Sensor::Get_Err(err);
		}
		if (msg!="")
		{
			MessageBoxW(Handle,msg.w_str(),L"������",MB_ICONERROR|MB_OK);
		}
		delete _time;
	}
	delete wnd;
}
int			TSettings::ResetBus_2(void)
{
	CD_9904::ErrCode err=sens->Write_Road_2(0);
	if (err!=CD_9904::ErrCode::Sucsess) return err;
	CD_9904::CD_Time *_time=new CD_9904::CD_Time();
	err=sens->Write_Time_2(_time);
	delete _time;
	if (err!=CD_9904::ErrCode::Sucsess) return err;
	return CD_9904::ErrCode::Sucsess;
}

void __fastcall TSettings::DefaultsClick(TObject *Sender)
{
	String msg="";
    if (!sens) {return;}
	unsigned short d=1700;
	unsigned int _dist=0;
	CD_9904::CD_Time *_time=new CD_9904::CD_Time(0,0);
	//������ ������������ ����������
	CD_9904::ErrCode err=sens->Write_Diametr(d);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ �������� ��������:"+CD_9904::Sensor::Get_Err(err);
	}
	err=sens->Write_Road_1(_dist);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ ���� �� ���� 1:"+CD_9904::Sensor::Get_Err(err);
	}
	err=sens->Write_Road_2(_dist);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ ���� �� ���� 2:"+CD_9904::Sensor::Get_Err(err);
	}
	err=sens->Write_Time_1(_time);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ ������� �� ���� 1:"+CD_9904::Sensor::Get_Err(err);
	}
	err=sens->Write_Time_2(_time);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ ������� �� ���� 2:"+CD_9904::Sensor::Get_Err(err);
	}
	delete _time;
	/*���������� ������������ ����������*/
	nAddr->Text=(String)addr;

	//������ ������ �������
	err=sens->Read_Diametr(d);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ �������� ��������:"+CD_9904::Sensor::Get_Err(err);
	}else
	{
		Diam->ItemIndex=Diam->Items->IndexOf(String(d));
	}

	//������ ��������� ����
	CD_9904::Data * data=0;
	err=sens->Tansl_Speed(&data);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ ���������� ����������:"+CD_9904::Sensor::Get_Err(err);
	}else
	{
		if (data)
		{
			Dist1->Text=String(data->Road_1());
			Dist2->Text=String(data->Road_2());
			Time1->Text=data->Time_1().Get_time_string();
			Time2->Text=data->Time_2().Get_time_string();
		}
	}
	delete data;
	if (msg!="")
	{
    	MessageBoxW(Handle,msg.w_str(),L"������",MB_ICONERROR|MB_OK);
	}
}
void			TSettings::Set_DefaultSettings (void)
{
	String msg="";
    if (!sens) {return;}
	unsigned short d=1700;
	unsigned int _dist=0;
	CD_9904::CD_Time *_time=new CD_9904::CD_Time(0,0);
	//������ ������������ ����������
	CD_9904::ErrCode err=sens->Write_Diametr(d);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ �������� ��������:"+CD_9904::Sensor::Get_Err(err);
	}
	err=sens->Write_Road_1(_dist);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ ���� �� ���� 1:"+CD_9904::Sensor::Get_Err(err);
	}
	err=sens->Write_Road_2(_dist);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ ���� �� ���� 2:"+CD_9904::Sensor::Get_Err(err);
	}
	err=sens->Write_Time_1(_time);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ ������� �� ���� 1:"+CD_9904::Sensor::Get_Err(err);
	}
	err=sens->Write_Time_2(_time);
	if (err!=CD_9904::ErrCode::Sucsess)
	{
		msg=msg+"\n������ ������ ������� �� ���� 2:"+CD_9904::Sensor::Get_Err(err);
	}
	delete _time;
}
//��������� ������ �   � ChooseClick
bool 			TSettings::fromFileSettings	(void)
{
	fstream file;
	bool result=false;
	AnsiString part=ExtractFilePath(Application->ExeName)+L"CD_9904_settings.stg";
	//������� ����� ���� � ������� � �������
	file.open(part.c_str(),ios::in);
	if (file.is_open())
	{   //������ ������
		file>>addr;
		char tmpstr[10]={0};
		file>>tmpstr;
		port=String(tmpstr);
		if (addr>=0&&port!="") {result=true;}
	}
	file.close();
	return result;
}
bool 			TSettings::toFileSettings	(void)
{
	fstream file;
	AnsiString part=ExtractFilePath(Application->ExeName)+L"CD_9904_settings.stg";
	file.open(part.c_str(),ios::out|ios::trunc);
	bool result=file.is_open();
	if (result)
	{   //������
		file<<addr<<endl;
		file<<AnsiString(port).c_str();
	}
	file.close();
	return result;
}
void __fastcall TSettings::Timer1Timer(TObject *Sender)
{
   	UpdateInfo();
}
void __fastcall TSettings::FormClose(TObject *Sender, TCloseAction &Action)
{
	//Timer1->Enabled=false;
}
void __fastcall TSettings::FormShow(TObject *Sender)
{
	//Timer1->Enabled=true;
}
