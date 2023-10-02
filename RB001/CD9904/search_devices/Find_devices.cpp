//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Find_devices.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <memory>
		__fastcall 	TNetwork_Scan::TNetwork_Scan(TComponent* Owner)
	: TForm(Owner)
{
	Greed_Sizing();
	//инициализаци€ поиска устройств
	Speedometers->Cells[0][0]="¬ыбор";
	Speedometers->Cells[1][0]="јдрес";
	Speedometers->Cells[2][0]="ѕорт";
	for (int i = 1; i < Speedometers->RowCount; i++)
	{//обнуление старого выбора
		Speedometers->Cells[0][i]=0;
	}
	Port="";
	Adderess=-1;
	//установка параметров шрифта отрисовки текста в сетке
	Speedometers->Canvas->Font->Style=Speedometers->Font->Style;
	Speedometers->Canvas->Font->Size=Speedometers->Font->Size;
}
		__fastcall 	TNetwork_Scan::TNetwork_Scan(TComponent* Owner,int addr,String port): TForm(Owner)
{
Greed_Sizing();
	//инициализаци€ поиска устройств
	Speedometers->Cells[0][0]="¬ыбор";
	Speedometers->Cells[1][0]="јдресс";
	Speedometers->Cells[2][0]="ѕорт";
	for (int i = 1; i < Speedometers->RowCount; i++)
	{//обнуление старого выбора
		Speedometers->Cells[0][i]=0;
	}
	Port=port;
	Adderess=addr;
	//установка параметров шрифта отрисовки текста в сетке
	Speedometers->Canvas->Font->Style=Speedometers->Font->Style;
	Speedometers->Canvas->Font->Size=Speedometers->Font->Size;
}
void 	__fastcall 	TNetwork_Scan::FormResize(TObject *Sender)
{
Greed_Sizing();
}
void 				TNetwork_Scan::Greed_Sizing (void)
{//управление размерами сетки
	for (int i = 0; i < Speedometers->ColCount; i++)
	{
		int k=0;//ширина колонки в процентах
		switch (i)
		{
		case 0:{k=40;break;}
		case 1:{k=27;break;}
		case 2:{k=27;break;}
		default:{k=0;break;}
		}
    	Speedometers->ColWidths[i]=k*Speedometers->Width/100;
	}
}

void 	__fastcall 	TNetwork_Scan::SpeedometersFixedCellClick(TObject *Sender,
		  int ACol, int ARow)
{//выбор устройства
	if (ARow)//проверка  на клик по списку а не по заголовку
	{
		bool prev=Speedometers->Cells[0][ARow].ToIntDef(0); //запомнить состо€ние перед обнулением
		for (int i = 1; i < Speedometers->RowCount; i++) //обнуление старого выбора
		{
			Speedometers->Cells[0][i]=0;
		}
		//новый выбор
		if (!prev) //если было включено то выключить если было выключено то включить
		{
			Speedometers->Cells[0][ARow]="1";
		}
	Speedometers->Repaint();
	}
	return;
}
void 	__fastcall 	TNetwork_Scan::SpeedometersDrawCell(TObject *Sender, int ACol,
		  int ARow, TRect &Rect, TGridDrawState State)
{
	TStringGrid *SG=(TStringGrid *)Sender;
	const int size=70;
	//рисовка выбранной строки
	if(!ACol&&ARow)
	{
		SG->Canvas->Brush->Color=clBtnFace;
		SG->Canvas->FillRect(Rect);
		TRect r = Rect;

		r.left+=(r.Width()-size)/2;;
		r.top += (Rect.Height()-size)/2;
		r.right = r.left + size;
		r.bottom = r.top + size;
		if (SG->Cells[0][ARow]=="1")
		{
			DrawFrameControl(SG->Canvas->Handle, &r, DFC_BUTTON, DFCS_BUTTONCHECK|DFCS_CHECKED);
		} else
		{
			DrawFrameControl(SG->Canvas->Handle, &r, DFC_BUTTON, DFCS_BUTTONCHECK);
		}
	}else
	{
		if (!ARow)
		{
			SG->Canvas->Brush->Color=clBtnFace;
		}else
		{
			if (SG->Cells[0][ARow]=="1")
			{
				SG->Canvas->Brush->Color=clGreen;
			}else
			{
                SG->Canvas->Brush->Color=clWindow;
			}
		}
		SG->Canvas->FillRect(Rect);
		String text=SG->Cells[ACol][ARow];
		if (text.Length())
		{
			int x,y;//расчет позиции рисовки

			x=Rect.left+(Rect.Width()-SG->Canvas->TextWidth(text))/2;
			y=Rect.top+(Rect.Height()-SG->Canvas->TextHeight(text))/2;
			SG->Canvas->TextOut(x,y,text);
		}
	}
	return;
}
void 	__fastcall 	TNetwork_Scan::OKClick(TObject *Sender)
{
	for (int i = 1; i < Speedometers->RowCount; i++)
	{
		if (Speedometers->Cells[0][i]=="1")
		{
			Port=Speedometers->Cells[2][i];
			Adderess=Speedometers->Cells[1][i].ToIntDef(-1);
		}
	}
	return;
}
void 	__fastcall 	TNetwork_Scan::Find_actionClick(TObject *Sender)
{//оппределение количества доступных компортов
	const int port_count=4;
	const int device_count=32;
	SGClear(Speedometers,0);
	PB->Max=port_count*device_count;
	PB->Position=0;
	for (int i = 1; i <=port_count ; i++)
	{
        std::shared_ptr<CD_9904::Sensor> sens;
		String Port_Name="COM"+String(i);
		try
		{
            sens.reset(new CD_9904::Sensor(Port_Name.w_str(),1,false));
			// перебор адресов (1..32) отклик с них
			for (char j=1; j<=device_count; j++)
			{
				if (sens->Init(j)==CD_9904::ErrCode::Sucsess)
				{
					int row=Speedometers->RowCount-1;
					Speedometers->Cells[1][row]=String((int)j);
					Speedometers->Cells[2][row]=Port_Name;
					if (Port_Name==Port&&String((int)j)==Adderess)
					{
						Speedometers->Cells[2][row]="1";
					}
					Speedometers->RowCount++;
				}
				PB->Position+=1;
				Application->ProcessMessages();//обработка сообщений винды
			}
		}
		catch (...)
		{
			PB->Position+=device_count;
		}
	}
	if (Speedometers->RowCount>2)
	{
		Speedometers->RowCount--;
	}
	Speedometers->Repaint();
}
bool				TNetwork_Scan::FastSearch(void)
{   //заглушка дл€ теста
	#ifdef _DEBUG
	Adderess=1;
	Port="COM1";
	return true;
	#endif

	bool find=false;
	for (int i = 1; i <=4&&!find; i++)
    {
        std::shared_ptr<CD_9904::Sensor>sens;
		String Port_Name="COM"+String(i);
		try
		{
            sens.reset(new CD_9904::Sensor(Port_Name.w_str(),1,false));
			// перебор адресов (1..32) отклик с них
			for (char j=1; j<=32&&!find; j++)
			{
				if (sens->Init(j)==CD_9904::ErrCode::Sucsess)
				{
					Adderess=(int)j;
					Port=Port_Name;
					find=true;
				}
				Application->ProcessMessages();//обработка сообщений винды
			}
		}
		catch (...)
		{
			PB->Position+=32;
		}
	}
	return find;
}
