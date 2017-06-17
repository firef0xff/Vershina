//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "num_keyboard.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

		__fastcall TNum_Pannel::TNum_Pannel	(TComponent* Owner,
							size_t _decimals,
							size_t _length,
							double _min_val,
							double _max_val,
							double init_val,
							bool _check_value,
							String separator): TForm(Owner)
{
	Value=(String)init_val;
	decimals=_decimals;
	BTD->Enabled=_decimals;
	length=_length;
	if (_max_val>_min_val)
	{
		max_val=_max_val;
		min_val=_min_val;
	}else
	{
		max_val=_min_val;
		min_val=_max_val;
	}
	if (init_val<min_val)
	{
		Value=(String)min_val;
	}
	if (init_val>max_val)
	{
		Value=(String)max_val;
	}
	Displ->Text=Value;
	if (separator=="")
	{
		Decimal_Separator=".";
	}else
	{
		Decimal_Separator=separator;
	}
	BTD->Caption=Decimal_Separator;
	check_value=_check_value;
}
void 	__fastcall TNum_Pannel::BTClick(TObject *Sender)
{
	TButton *BT=(TButton *)Sender;
	//проверка наличия разделителя
	size_t Separator_pos=Displ->Text.Pos(Decimal_Separator);
	size_t val_len=Displ->Text.Length();
	bool add=false;
	if (Separator_pos)
	{
		//отсчитываем разницу позиции сепаратора и последней цифры
		if ((val_len-Separator_pos)<decimals&&BT->Caption!=Decimal_Separator)
		{  //если еще можно вводить цифры и вводимое не сепаратор
			add=true;
		}
	}else
	{  //сепаратора в строке нет
		if (length>val_len)
		{ //еще можно вводитьсимволы в целую часть
			//проверка первого нуля
			if (Displ->Text=="0")
			{
				Displ->Text="";
				val_len=Displ->Text.Length();
			}
			if (BT->Caption==Decimal_Separator)
			{//был нажат сеператор
				if (!val_len)
				{//до сепаратора ничего не введено рисуем ноль
					Displ->Text="0";
				}
			}
			add=true;
		}else
		{//вводить целые больше некуда
			if (decimals)
			{
				if (!length||!val_len)
				{//проверка наличия введенных символов до него рисуем ноль пред сепаратором
					Displ->Text="0";
				}
				if (BT->Caption!=Decimal_Separator)
				{//был нажат  не сепаратор
					Displ->Text=Displ->Text+Decimal_Separator;
				}
				add=true;
			}
		}
	}
	if (add)
	{
		Displ->Text=Displ->Text+BT->Caption;
		Displ->SelStart=Displ->Text.Length();
	}
}
void 	__fastcall TNum_Pannel::BSClick(TObject *Sender)
{
	Displ->Color=clWindow;
	Displ->Text=Displ->Text.SubString(1,Displ->Text.Length()-1);
	if (!Displ->Text.Length())
	{
    	Displ->Text="0";
	}
	Displ->SelStart=Displ->Text.Length();
}
void 	__fastcall TNum_Pannel::CClick(TObject *Sender)
{
	Displ->Color=clWindow;
	Displ->Text="0";
}
void 	__fastcall TNum_Pannel::OKClick(TObject *Sender)
{
	Value=Displ->Text;
	if (check_value)
	{
		String _val=Value;
		if (Decimal_Separator!=".")
		{
		   _val=Replace(Value,Decimal_Separator,".");
		}
		double __val=_val.ToDouble();
		if (__val<min_val||__val>max_val)
		{
			Displ->Color=clRed;
			String msg="Значение должно быть между "+String(min_val)+" и "+String(max_val);
			MessageBoxW(Handle,msg.w_str(),L"НЕВЕРНОЕ ЗНАЧЕНИЕ",MB_ICONWARNING|MB_OK);
		}else
		{
			ModalResult=mrOk;
			CloseModal();
		}
	}else
	{
		ModalResult=mrOk;
		CloseModal();
	}
}
void 	__fastcall TNum_Pannel::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key)
	{
		//основная
		case 48		:{BT0->Click();	break;}
		case 49		:{BT1->Click();	break;}
		case 50		:{BT2->Click();	break;}
		case 51		:{BT3->Click();	break;}
		case 52		:{BT4->Click();	break;}
		case 53		:{BT5->Click();	break;}
		case 54		:{BT6->Click();	break;}
		case 55		:{BT7->Click();	break;}
		case 56		:{BT8->Click();	break;}
		case 57		:{BT9->Click();	break;}
		case 58		:{BTD->Click();	break;}
		//нумпад
		case 96		:{BT0->Click();	break;}
		case 97		:{BT1->Click();	break;}
		case 98		:{BT2->Click();	break;}
		case 99		:{BT3->Click();	break;}
		case 100	:{BT4->Click();	break;}
		case 101	:{BT5->Click();	break;}
		case 102	:{BT6->Click();	break;}
		case 103	:{BT7->Click();	break;}
		case 104	:{BT8->Click();	break;}
		case 105	:{BT9->Click();	break;}
		//разделитель
		//нум
		case 110	:{BTD->Click();	break;}
		//клава
		case 191	:{BTD->Click();	break;}
		case 190	:{BTD->Click();	break;}
		case 188	:{BTD->Click();	break;}
		//сервисные
		case 8		:{BS->Click();	break;}
		case 46		:{C->Click();	break;}
		case 13		:{OK->Click();	break;}
	default:break;
	}
}
//---------------------------------------------------------------------------

