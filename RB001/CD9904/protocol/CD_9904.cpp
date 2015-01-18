//---------------------------------------------------------------------------
#pragma hdrstop

#include "CD_9904.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
using  namespace CD_9904;
//----------�������� ������ TIME
	CD_Time::CD_Time(unsigned short _hours,BYTE _minits)
{
	hours=_hours;
	minits=_minits;
	if (minits>=60)
	{
		hours++;
		minits-=60;
	}
	if (hours>9999)
	{
		hours=0;
		minits=0;
	}
	time_string=(String)hours+":"+(String)minits;
	msek=(hours*60+minits)*60*1000;
}
	CD_Time::CD_Time(String TimeStr)
{
	size_t delim_pos=TimeStr.Pos(":");
	hours=(unsigned short)(TimeStr.SubString(1,delim_pos-1).ToIntDef(0));
	minits=(BYTE)(TimeStr.SubString(delim_pos+1,TimeStr.Length()-delim_pos).ToIntDef(0));

	if (minits>=60)
	{
		hours++;
		minits-=60;
	}
	if (hours>9999)
	{
		hours=0;
		minits=0;
	}
	time_string=(String)hours+":"+(String)minits;
	msek=(hours*60+minits)*60*1000;
}
	CD_Time::~CD_Time()
{}
//----------�������� ������ data
	Data::Data (BYTE * ans,size_t size):time_1(0),time_2(0)
{
	if (size!=TILE_LEN+18)
	{
	throw Exception("Wrong data length");
	}
 //��������������� ������� ��� ��������
 BYTE SPEED[2];  //���������� �������� ���������� 0,1 ��/�
 BYTE ROAD_1[4]; //���������� ���� ����� 1 ���������� 1 ��
 BYTE ROAD_2[4]; //���������� ���� ����� 2 ���������� 1 ��
 BYTE TIME_1[3]; //����� ��������� 1 ���� -���� �� ���� 2 ���� ���� �� ���� 3 ���� ������
 BYTE TIME_2[3]; //����� ��������� 1 ���� -���� �� ���� 2 ���� ���� �� ���� 3 ���� ������

 SPEED[0]=*(ans+INF_I+0);
 SPEED[1]=*(ans+INF_I+1);
 speed=((double)(*((short*)&SPEED[0])))/10;
 //���� ������ �������
 ROAD_1[0]=*(ans+INF_I+2);
 ROAD_1[1]=*(ans+INF_I+3);
 ROAD_1[2]=*(ans+INF_I+4);
 ROAD_1[3]=0;
 road_1=*((unsigned int *)ROAD_1);
 //����� ������ �������
 TIME_1[0]=*(ans+INF_I+5);
 TIME_1[1]=*(ans+INF_I+6);
 TIME_1[2]=*(ans+INF_I+7);
 time_1=new CD_Time(*((short *)&TIME_1[0]),(short)TIME_1[2]);
 //���� ������ �������
 ROAD_2[0]=*(ans+INF_I+8);
 ROAD_2[1]=*(ans+INF_I+9);
 ROAD_2[2]=*(ans+INF_I+10);
 ROAD_2[3]=0;
 road_2=*((unsigned int *)ROAD_2);
 //����� ������ �������
 TIME_2[0]=*(ans+INF_I+11);
 TIME_2[1]=*(ans+INF_I+12);
 TIME_2[2]=*(ans+INF_I+13);
 time_2=new CD_Time(*((short *)&TIME_2[0]),(short)TIME_2[2]);
 //��������� ���� (�����)
 inform=*(ans+INF_I+14);
}
	Data::~Data()
{
	delete time_1;
	delete time_2;
}
//�������� ������ Sensor
		Sensor::Sensor(wchar_t *_COM,BYTE _addr,bool init)
{

	//������������� �����

	//����������  ���������
	COMMTIMEOUTS *TimeOuts=new COMMTIMEOUTS();
	TimeOuts->ReadIntervalTimeout = 0xFFFFFFFF;
	TimeOuts->ReadTotalTimeoutMultiplier = 0;
	TimeOuts->ReadTotalTimeoutConstant = 0;
	TimeOuts->WriteTotalTimeoutMultiplier = 0;
	TimeOuts->WriteTotalTimeoutConstant =0;

	COM=_COM;
	port_owner=true;
	port=new COMPort(COM,TimeOuts,COMPort::CommMasks::ev_rxchar,4096,2048);
    	//������������� �������� ����� DCB

	DCB *settings=port->Get_port_Settings();
	settings->BaudRate =COMPort::BaudRates::BR_4800;
	settings->ByteSize = 8;
	settings->Parity = COMPort::Patitys::NOparity;
	settings->StopBits = COMPort::StopBits::ONE;
	settings->fAbortOnError = FALSE;
	settings->fDtrControl = DTR_CONTROL_ENABLE;
	settings->fRtsControl = RTS_CONTROL_DISABLE;
	settings->fBinary = TRUE;
	settings->fParity = COMPort::fPatitys::OFF;
	settings->fInX = FALSE;
	settings->fOutX = FALSE;
	settings->XonChar = (BYTE)0x11;
	settings->XoffChar = (BYTE)0x13;
	settings->fErrorChar = FALSE;
	settings->fNull = FALSE;
	settings->fOutxCtsFlow = FALSE;
	settings->fOutxDsrFlow = FALSE;
	settings->XonLim = 1024;
	settings->XoffLim = 1024;
	settings->fDsrSensitivity=FALSE;

	port->Set_DCB_Settings(settings);

	addr=_addr;
	if (init)
	{
		ErrCode err=Init(addr);
		if (err!=ErrCode::Sucsess)
		{
			delete this;
			throw Exception(Get_Err(err));
		}
	}
}
		Sensor::Sensor(COMPort * _port,BYTE _addr)
{
	port=_port;
	COM=port->Get_Com_Name();
	addr=_addr;
	ErrCode err=Init(addr);
	port_owner=false;
	if (err!=ErrCode::Sucsess)
	{
		throw Exception(Get_Err(err));
	}
}
		Sensor::~Sensor()
{
	if (port_owner)
	{
		delete port;
	}
}

ErrCode	Sensor::Init			(BYTE _addr)
{
	addr=_addr;
	size_t ans_len=TILE_LEN+4;
	BYTE *ans=new BYTE[ans_len];
	ErrCode err=Compile_command(0x00,0x03,0,0,0x85,ans,ans_len);
	if (err==ErrCode::Sucsess)
	{
		if (!ans[INF_I]==addr)
		{
			err==ErrCode::Unknown_err;
		}
	}
	delete []ans;
	return err;
}
ErrCode Sensor::Write_ADDR		(BYTE _addr)
{
	size_t ans_len=0;
	ErrCode err=Compile_command(0xC0,0x04,&_addr,1/*sizeof(BYTE)*/,0x00,0,ans_len);
	if (err==ErrCode::Sucsess)
	{
	addr=_addr;
	}
	return err;
}
ErrCode Sensor::Read_Diametr	(unsigned short &Diametr)
{
	size_t ans_len=TILE_LEN+5;
	BYTE *ans=new BYTE[ans_len];
	ErrCode err=Compile_command(0xC1,0x3,0,0,0x85,ans,ans_len);
	if (err==ErrCode::Sucsess)
	{
		Diametr=(int)(*((unsigned short *)(ans+INF_I)));
	}
	delete []ans;
	return err;
}
ErrCode	Sensor::Write_Diametr	(unsigned short Diametr)
{
	size_t ans_len=0;
	ErrCode err=Compile_command(0xC2,0x05,(BYTE *)&Diametr,2/*sizeof(short)*/,0x00,0,ans_len);
	return err;
}
ErrCode	Sensor::Tansl_Speed  	(Data **speed)
{
	size_t ans_len=TILE_LEN+18;
	BYTE *ans=new BYTE[ans_len];
	ErrCode err=Compile_command(0xC3,0x3,0,0,0x85,ans,ans_len);
	if (err==ErrCode::Sucsess)
	{
		*speed=new Data(ans,ans_len);
	}
	delete []ans;
	return err;
}
ErrCode	Sensor::Write_Road_1    (unsigned int road)
{
	size_t ans_len=0;
	BYTE _road[3];
	_road[0]=*(((BYTE*)&road)+2);
	_road[1]=*(((BYTE*)&road)+1);
	_road[2]=*(((BYTE*)&road)+0);
	ErrCode err=Compile_command(0xC4,0x06,&_road[0],sizeof(_road),0x00,0,ans_len);
	return err;
}
ErrCode	Sensor::Write_Road_2    (unsigned int road)
{
	size_t ans_len=0;
	BYTE _road[3];
	_road[0]=*(((BYTE*)&road)+2);
	_road[1]=*(((BYTE*)&road)+1);
	_road[2]=*(((BYTE*)&road)+0);
	ErrCode err=Compile_command(0xC5,0x06,&_road[0],sizeof(_road),0x00,0,ans_len);
	return err;
}
ErrCode	Sensor::Write_Time_1    (CD_Time *time)
{
	size_t ans_len=0;
	BYTE _time[3];
	unsigned short hours=(unsigned short)time->Get_hours();
	BYTE minits=(BYTE)time->Get_minits();
	_time[0]=*(((BYTE*)&hours)+1);
	_time[1]=*(((BYTE*)&hours)+0);
	_time[2]=minits;
	ErrCode err=Compile_command(0xC6,0x06,&_time[0],sizeof(_time),0x00,0,ans_len);
	return err;
}
ErrCode	Sensor::Write_Time_2    (CD_Time *time)
{
	size_t ans_len=0;
	BYTE _time[3];
	unsigned short hours=(unsigned short)time->Get_hours();
	BYTE minits=(BYTE)time->Get_minits();
	_time[0]=*(((BYTE*)&hours)+1);
	_time[1]=*(((BYTE*)&hours)+0);
	_time[2]=minits;
	ErrCode err=Compile_command(0xC7,0x06,&_time[0],sizeof(_time),0x00,0,ans_len);
	return err;
}


bool 	Sensor::Check_CRC       (const BYTE *com)
{
	bool result=false;
	BYTE * Title_CRC=Get_Title_CRC(com);
	BYTE * MSG_CRC=Get_CRC_IFO(com);
	size_t msg_crc_pos=TILE_LEN+(size_t)com[LEN]-CRC_TITLE_INF;

	if (*(com+CRC_TITLE)==*(Title_CRC)&&
		*(com+CRC_TITLE+1)==*(Title_CRC+1)&&
		*(com+msg_crc_pos)==*(MSG_CRC)&&
		*(com+msg_crc_pos+1)==*(MSG_CRC+1))
	{
	result=true;
	}
	delete []Title_CRC;
	delete []MSG_CRC;
	return result;
}
BYTE *	Sensor::Get_Title_CRC 	(const BYTE *com)
{
	short len=(short)(BYTE)com[LEN];
	short addr=(short)(BYTE)com[ADDR];
	short num=(short)(BYTE)com[NUM];

	short crc=len+addr+num+1;
	crc=~crc;
	BYTE *result=new BYTE[CRC_TITLE_LEN];
	for (int i=0; i<CRC_TITLE_LEN; i++)
	{
		result[i]=((BYTE *)&crc)[i];
	}
	return result;
}
BYTE *	Sensor::Get_CRC_IFO   	(const BYTE *com)
{
	short type=(short)com[TYPE];
	short crc=type;
	size_t msg_len=com[LEN]-1-CRC_TITLE_INF;
	for (size_t i=0; i<msg_len; i++)
	{
		crc+=(short)(*(com+INF_I+i));
	}
	crc+=1;
	crc=~crc;
	BYTE *result=new BYTE[CRC_TITLE_INF];
	for (int i=0; i<CRC_TITLE_INF; i++)
	{
		result[i]=((BYTE *)&crc)[i];
	}
	return result;
}

ErrCode Sensor::Compile_command	(	BYTE _type,		BYTE data_len,
									BYTE *s_data,	size_t s_data_len,
									BYTE r_type,	BYTE *r_data,   size_t &r_data_len)
{
//��� 1 ���������� ���������
	BYTE * com=Get_Com_Title(data_len);
	ErrCode err=ErrCode::Sucsess;
	if (com)
	{//��������� ��������
		//������ ����
		com[TYPE]=_type;
		//�������� �� ������������� �������� ������
		if (s_data&&s_data_len)
		{//������� ������������ ������
			for (size_t i = 0; i < s_data_len; i++)
			{
				*(com+INF_I+i)=*(s_data+i);
			}
		}
		//���������� �rc ���� ��� �������� ����������� ����
		BYTE *crc=Get_CRC_IFO(com);
		if (crc)
		{//��� ��������, ���������� � �����
			com[TILE_LEN+(int)data_len-2]=crc[0];				//crc  1 byte
			com[TILE_LEN+(int)data_len-1]=crc[1];        		//crc  2 byte
			delete []crc;
			crc=0;
			//�������� ���������
			err=SendMessage(com);
			if (err==ErrCode::Sucsess)
			{   //�������� ������������� ������ �������� ������
				if (r_data&&r_data_len)
				{//������ ������ ����������
					for (size_t i = 0; i<r_data_len; i++){*(r_data+i)=0;}
					port->Read(r_data,r_data_len);
					//�������� ������
					if (*(r_data+SYNC)==0x16&&
						*(r_data+TYPE)==r_type&&
						Check_CRC(r_data)//�������� CRC
						)
					{
						err=ErrCode::Sucsess;
					}else
					{
					err=ErrCode::Unknown_err;
					}
				}
			}
		}else
		{//������ ���������� ���
			err=ErrCode::Unknown_err;
		}
		//��������� ������ ������
		delete []com;
		com=0;
		return err;
	}else
	{//������ ���������� ���������
		return ErrCode::Unknown_err;
	}
}
BYTE *  Sensor::Get_Com_Title	(size_t len)
{
	if (len<0x3||len>0x12)
	{
	throw Exception("����������� �������");
	}
	BYTE *com=new BYTE[TILE_LEN+len];
	com[SYNC]=0x16;						//SYNC
	com[LEN]=(BYTE)len;					//LEN
	com[ADDR]=addr;       				//ADDR
	com[NUM]=0x0;						//NUM
	BYTE *crc=Get_Title_CRC(com);
	if (crc)
	{
		com[CRC_TITLE]=crc[0];					//crc title 1 byte
		com[CRC_TITLE+1]=crc[1];        		//crc title 2 byte
		delete []crc;
		crc=0;
		return com;
	}else
	{
		delete []com;
		com=0;
		return 0;
	}
}
ErrCode Sensor::SendMessage		(const BYTE *com)
{
	size_t length=TILE_LEN+(int)com[1];
	ErrCode result=ErrCode::Sucsess;
	bool Answer=false;
	for (int i = 0; i < 3&&!Answer; i++)
	{
		//������
		port->DTR_oFF();
		//port->Clear_Com_Buff(COMPort::Purge_flags::RXCLEAR|COMPort::Purge_flags::TXCLEAR);
		port->Write(com,length);
		port->DTR_On(120,500);
		//������ ���� ������
		size_t len=TILE_LEN+4;
		BYTE *Err=new BYTE[len];
		for (size_t i = 0; i<len; i++){Err[i]=0;}
		port->Read(Err,len);
		//�������� ������
		/*������ ����� ������� ����� � �������� ����� ��� �����,
		 �� � ������ �� ������ ���� ���� ��� ����� ������
		 ��������� � ����� ���������� � ������ ������*/
		if (*(Err+SYNC)==0x16&&
			*(Err+TYPE)==0x80&&
			Check_CRC(Err))//�������� CRC
		{
			//���������� ���� ������
			result=Err[INF_I];
			Answer=true;
		}else
		{
			port->Clear_Com_Buff(	COMPort::Purge_flags::TXABORT|
									COMPort::Purge_flags::RXABORT|
									COMPort::Purge_flags::TXCLEAR|
									COMPort::Purge_flags::RXCLEAR);
		}
		delete []Err;
	}
	if (!Answer)
	{
	result=ErrCode::Unknown_err;
	}
	return result;
}

String  Sensor::Get_Err			(ErrCode err)
{
	switch (err)
	{
		case ErrCode::CRC_Title: 		return "CD_9044::Wrong CRC_Title";
		case ErrCode::Addr_Err: 		return "CD_9044::Wrong Address";
		case ErrCode::CRC_Info: 		return "CD_9044::Wrong CRC_Info";
		case ErrCode::Unknown_command: 	return "CD_9044::Unknown command";
		case ErrCode::Too_long_message: return "CD_9044::Too long message";
		case ErrCode::Time_out_err: 	return "CD_9044::Time out Error";
		case ErrCode::Ident_err: 		return "CD_9044::Identifications Error";
		case ErrCode::Sucsess: 			return "CD_9044::Sucsess";
	default: 							return "CD_9044::Unkown Error";
	}
}
