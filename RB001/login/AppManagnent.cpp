//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AppManagnent.h"
#include "MD5.h"
#include <cstring.h>
#include  "functions.h"
#include "MD5.h"
#include "GroupSelect.h"
#include "User_Data.h"
using namespace  md5;
using std::strlen;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TAppManagment::TAppManagment(TComponent* Owner,cSQL *db)
	: TForm(Owner),DB(db)
{
	//инициализаци€ интерфейса
	sgUsers->Cells[1][0]="Ћогин";
	sgUsers->Cells[2][0]="»м€";
	sgUsers->Cells[3][0]="‘амили€";
	AutoWidthSG(sgUsers);

	order_by="order by login asc ";
	//загрузка текущих настроек
		//пути сохранени€
	Get_Paths();
	//список пользователей
	Get_Users();

}
void 	TAppManagment::Get_Users	(void)
{
	TADOQuery *rez=DB->SendSQL("Select login,name,family from logins "+order_by);
	SGClear(sgUsers,0);
	if (rez&&rez->RecordCount)
	{
		for (rez->First(); !rez->Eof; rez->Next())
		{
			sgUsers->Cells[1][sgUsers->RowCount-1]=rez->FieldByName("login")->Value.IsNull()?UnicodeString():rez->FieldByName("login")->Value.operator UnicodeString();
			sgUsers->Cells[2][sgUsers->RowCount-1]=rez->FieldByName("name")->Value.IsNull()?UnicodeString():rez->FieldByName("name")->Value.operator UnicodeString();;
			sgUsers->Cells[3][sgUsers->RowCount-1]=rez->FieldByName("family")->Value.IsNull()?UnicodeString():rez->FieldByName("family")->Value.operator UnicodeString();;
			sgUsers->RowCount++;
		}
		if (sgUsers->RowCount>sgUsers->FixedRows+1)
		{
        	sgUsers->RowCount--;
		}
	}
	Get_Groups(sgUsers->Row);
	AutoWidthSG(sgUsers);
	delete rez;
}
void	TAppManagment::Get_Paths	(void)
{
	cbMode->Checked=Get_param(L"File_Save_Mode")=="Auto"?true:false;
	leDistProg->Text=Get_param(L"Sprog");
	leTimeProg->Text=Get_param(L"Tprog");
	leProtA->Text=Get_param(L"TestResPosA");
	leProtB->Text=Get_param(L"TestResPosB");
	leTitleProt->Text=Get_param(L"ProtTtl");

	leLoadCalibrA->Text=Get_param(L"LoadCalibrTableA");
	leLoadCalibrB->Text=Get_param(L"LoadCalibrTableB");
	leTCalibrA->Text=Get_param(L"TCalibrTableA");
	leTCalibrB->Text=Get_param(L"TCalibrTableB");
	leRCalibrA->Text=Get_param(L"RCalibrTableA");
	leRCalibrB->Text=Get_param(L"RCalibrTableB");
	leSpdCalibr->Text=Get_param(L"SpdCalibrTable");

	leSertPrintProtA->Text=Get_param(L"LoadSertPrintProtA");
	leSertPrintProtB->Text=Get_param(L"LoadSertPrintProtB");
}
String	TAppManagment::Get_param    (String param_name)
{
	return Get_param(param_name,DB);
}
String	TAppManagment::Get_param    (String param_name, cSQL *DB)
{
	TADOQuery *rez=DB->SendSQL("Select Value from settings where param=\'"+param_name+"\'");
	String result;
	if (rez&&rez->RecordCount)
	{
		result=rez->FieldByName("Value")->Value.IsNull()?UnicodeString():rez->FieldByName("Value")->Value.operator UnicodeString();;
	}
	delete rez;
	return result;
}
void	TAppManagment::Set_Param	(String param_name,String value)
{
	String sql="update [settings] set [value]=\'"+value+"\' where [Param]=\'"+param_name+"\'";
	DB->SendCommand(sql);
}
void	TAppManagment::Set_Param	(String param_name,String value, cSQL *DB)
{
	String sql="update [settings] set [value]=\'"+value+"\' where [Param]=\'"+param_name+"\'";
	DB->SendCommand(sql);
}
void	TAppManagment::Get_Groups	(int Row)
{
	if (sgUsers->Row)
	{
		SGClear(sgGroups,0);
		String sql="SELECT c.Name FROM ";
		sql+="(UsersInGroups a ";
		sql+="INNER JOIN Logins b ON a.UserID = b.ID) ";
		sql+="INNER JOIN Groups c ON a.GroupID = c.ID ";
		sql+="Where b.Login=\'"+sgUsers->Cells[1][Row]+"\'";

		TADOQuery *rez=DB->SendSQL(sql);
		if (rez&&rez->RecordCount)
		{
			for (rez->First(); !rez->Eof; rez->Next())
			{
				sgGroups->Cells[0][sgGroups->RowCount-1]=rez->FieldByName("Name")->Value;
				sgGroups->RowCount++;
			}
			if (sgGroups->RowCount>1)
			{
				sgGroups->RowCount--;
			}
		}
		delete rez;
	}
}
//обработка событий
	//сетка пользователей
void __fastcall TAppManagment::sgUsersFixedCellClick(TObject *Sender, int ACol, int ARow)

{
	//сортировка
	String field="";
	switch (ACol)
	{
		case 1:{field="login";break;}
		case 2:{field="name";break;}
		case 3:{field="family";break;}
		default:return;
	}
	//определение пор€дка сортировки
	String order="desc",kor="";
	int pos=order_by.Pos(field);
	if (pos==10)
	{
		kor=" ";
		String o_order=order_by.SubString(pos+field.Length()+1,4);
		if (o_order=="desc")
		{
			order="asc ";
		}else
		{
			order="desc";
		}
	}
	//удаление старого вхождени€ строки
	order_by.Delete(pos,field.Length()+order.Length()+2);
	//вставка нового вхождени€
	order_by.Insert(kor+field+" "+order+",",10);
	order_by=order_by.Trim();
	if (order_by[order_by.Length()]==',')
	{
		order_by.Delete(order_by.Length(),1);
	}
	Get_Users();
}
void __fastcall TAppManagment::sgUsersSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
	Get_Groups(ARow);
}
//меню
void __fastcall TAppManagment::UserDelClick(TObject *Sender)
{
	if (sgUsers->Row)
	{
		//проверка наличи€ записи
		String sql="SELECT a.id FROM Logins a ";
		sql+="Where a.Login=\'"+sgUsers->Cells[1][sgUsers->Row]+"\'";
		TADOQuery *rez=DB->SendSQL(sql);
		if (rez)
		{
			if (rez->RecordCount)
			{//есть запись
				//удаление записи
				String sql="delete from Logins where ";
				sql+="Login=\'"+sgUsers->Cells[1][sgUsers->Row]+"\'";

				DB->SendCommand(sql);
				Get_Users();
			}else
			{//нет записи
				MessageBoxW(Handle,L"ѕользователь отсутствует",L"¬нимание!",MB_ICONWARNING|MB_OK);
			}
		}
		delete rez;
	}
}
void __fastcall TAppManagment::UserAddClick(TObject *Sender)
{
	TUserData *wnd=new TUserData(this);
	if (wnd->ShowModal()==mrOk)
	{
		//проверка наличи€ логина в базе
		String msg="";
		TADOQuery *rez=DB->SendSQL("Select login from logins where login=\'"+wnd->leLogin->Text.Trim()+"\'");
		if (rez)
		{
			if (rez->RecordCount)
			{//уже есть в базе
            	MessageBoxW(Handle,L"ѕользователь уже есть в базе",L"¬нимание!",MB_ICONWARNING|MB_OK);
			}else
			{
				//получение кеша парол€
				md5::Get_md5 cache;
				AnsiString pass=wnd->lePass->Text;
				char *Byte_cache=cache(pass.c_str(),pass.Length()); //байтовый кеш
				char *Str_cache=cache.ByteToCSTR(Byte_cache,strlen(Byte_cache)-1); //символьный кеш
				delete []Byte_cache;  //очистка байткеша
				Byte_cache=nullptr;
				//составление запроса
				String sql="insert into [Logins] ([Login],[Name],[Family],[Password]) ";
				sql+="Values (\'"+wnd->leLogin->Text.Trim()+"\',\'"+wnd->leName->Text.Trim()+"\',\'"+wnd->leFam->Text.Trim()+"\',\'"+String(Str_cache)+"\') ";
				delete []Str_cache;  //очистка стрингкеша
				Str_cache=nullptr;

				//добавление пользовател€
				DB->SendCommand(sql);
				Get_Users();
			}
		}
		delete rez;
	}
	delete wnd;
}
void __fastcall TAppManagment::UserUpdateClick(TObject *Sender)
{
	if (sgUsers->Row)
	{
		TUserData *wnd=new TUserData(this);
		wnd->leFam->Text=sgUsers->Cells[3][sgUsers->Row];
		wnd->leName->Text=sgUsers->Cells[2][sgUsers->Row];
		wnd->leLogin->Text=sgUsers->Cells[1][sgUsers->Row];
		if (wnd->ShowModal()==mrOk)
		{
			//проверка наличи€ логина в базе
			String msg="";
			TADOQuery *rez=DB->SendSQL("Select login from logins where login=\'"+sgUsers->Cells[1][sgUsers->Row]+"\'");
			if (rez)
			{
				if (rez->RecordCount)
				{//уже есть в базе
					//получение кеша парол€
					md5::Get_md5 cache;
					AnsiString pass=wnd->lePass->Text;
					char *Byte_cache=cache(pass.c_str(),pass.Length()); //байтовый кеш
					char *Str_cache=cache.ByteToCSTR(Byte_cache,strlen(Byte_cache)-1); //символьный кеш
					delete []Byte_cache;  //очистка байткеша
					Byte_cache=nullptr;
					//составление запроса
					String sql="update [Logins] set [Login]=\'"+wnd->leLogin->Text.Trim()+"\',";
					sql+="[Name]=\'"+wnd->leName->Text.Trim()+"\',";
					sql+="[Family]=\'"+wnd->leFam->Text.Trim()+"\',";
					sql+="[Password]=\'"+String(Str_cache)+"\' ";
					sql+="where [Login]=\'"+sgUsers->Cells[1][sgUsers->Row]+"\'";
					delete []Str_cache;  //очистка стрингкеша
					Str_cache=nullptr;

					//обновление данных пользовател€
					DB->SendCommand(sql);
					Get_Users();
				}else
				{//нет в базе
					MessageBoxW(Handle,L"ѕользовател€ уже нет в базе",L"¬нимание!",MB_ICONWARNING|MB_OK);
				}
			}
			delete rez;
		}
		delete wnd;
	}
}
void __fastcall TAppManagment::GroupDel2Click(TObject *Sender)
{
	if (sgUsers->Row)
	{
		//проверка наличи€ записис
		String sql="SELECT b.id,c.id FROM ";
		sql+="(UsersInGroups a ";
		sql+="INNER JOIN Logins b ON a.UserID = b.ID) ";
		sql+="INNER JOIN Groups c ON a.GroupID = c.ID ";
		sql+="Where b.Login=\'"+sgUsers->Cells[1][sgUsers->Row]+"\' and c.Name=\'"+sgGroups->Cells[0][sgGroups->Row]+"\'";
		TADOQuery *rez=DB->SendSQL(sql);
		if (rez)
		{
			if (rez->RecordCount)
			{//есть запись
				//удаление записи
				String sql="delete from UsersInGroups where ";
				sql+="UserID in (select ID from Logins where Login=\'"+sgUsers->Cells[1][sgUsers->Row]+"\') and ";
				sql+="GroupID in (select ID from Groups where Name=\'"+sgGroups->Cells[0][sgGroups->Row]+"\') ";

				DB->SendCommand(sql);
				Get_Groups(sgUsers->Row);
			}else
			{//нет записи
				MessageBoxW(Handle,L"ѕользователь отсутствует в этой группе",L"¬нимание!",MB_ICONWARNING|MB_OK);
			}
		}
		delete rez;
	}
}
void __fastcall TAppManagment::GroupDel1Click(TObject *Sender)
{
	//получить группу
	if (sgUsers->Row)
	{
		TfselGroup *wnd=new TfselGroup(this,DB);
		if (wnd->ShowModal()==mrOk)
		{
			//проверка наличи€ записис
			String sql="SELECT b.id,c.id FROM ";
			sql+="(UsersInGroups a ";
			sql+="INNER JOIN Logins b ON a.UserID = b.ID) ";
			sql+="INNER JOIN Groups c ON a.GroupID = c.ID ";
			sql+="Where b.Login=\'"+sgUsers->Cells[1][sgUsers->Row]+"\' and c.Name=\'"+wnd->cbGroups->Text+"\'";
			TADOQuery *rez=DB->SendSQL(sql);
			if (rez)
			{
				if (rez->RecordCount)
				{//есть запись
					//удаление записи
					String sql="delete from UsersInGroups where ";
					sql+="UserID in (select ID from Logins where Login=\'"+sgUsers->Cells[1][sgUsers->Row]+"\') and ";
					sql+="GroupID in (select ID from Groups where Name=\'"+wnd->cbGroups->Text+"\') ";

					DB->SendCommand(sql);
					Get_Groups(sgUsers->Row);
				}else
				{//нет записи
					MessageBoxW(Handle,L"ѕользователь отсутствует в этой группе",L"¬нимание!",MB_ICONWARNING|MB_OK);
				}
			}
			delete rez;
		}
		delete wnd;
	}
}
void __fastcall TAppManagment::AddGroupClick(TObject *Sender)
{
	//получить группу
	if (sgUsers->Row)
	{
		TfselGroup *wnd=new TfselGroup(this,DB);
		if (wnd->ShowModal()==mrOk)
		{
			//проверка наличи€ записи
			String sql="SELECT b.id,c.id FROM ";
			sql+="(UsersInGroups a ";
			sql+="INNER JOIN Logins b ON a.UserID = b.ID) ";
			sql+="INNER JOIN Groups c ON a.GroupID = c.ID ";
			sql+="Where b.Login=\'"+sgUsers->Cells[1][sgUsers->Row]+"\' and c.Name=\'"+wnd->cbGroups->Text+"\'";
			TADOQuery *rez=DB->SendSQL(sql);
			if (rez)
			{
				if (rez->RecordCount)
				{//есть запись
					MessageBoxW(Handle,L"ѕользователь уже находитс€ в этой группе",L"¬нимание!",MB_ICONWARNING|MB_OK);
				}else
				{//нет записи
					//добавление записи
					sql="insert into UsersInGroups (UserID,GroupID) ";
					sql+="select a.id,b.id from Logins a,  Groups b ";
					sql+="where a.Login=\'"+sgUsers->Cells[1][sgUsers->Row]+"\' and  b.Name=\'"+wnd->cbGroups->Text+"\'";

					DB->SendCommand(sql);
					Get_Groups(sgUsers->Row);
				}
			}
			delete rez;
		}
		delete wnd;
	}
}
//пути сохранени€
void __fastcall TAppManagment::bFindClick(TObject *Sender)
{
	TButton *t=(TButton *)Sender;
	TLabeledEdit *l=nullptr;
	switch (t->Tag)
	{
		case 0:{l=leDistProg; 		break;}
		case 1:{l=leTimeProg; 		break;}
		case 2:{l=leProtA; 			break;}
		case 3:{l=leProtB; 			break;}
		case 4:{l=leTitleProt;  	break;}
		case 5:{l=leLoadCalibrA; 	break;}
		case 6:{l=leLoadCalibrB; 	break;}
		case 7:{l=leTCalibrA; 		break;}
		case 8:{l=leTCalibrB; 		break;}
		case 9:{l=leRCalibrA;  		break;}
		case 10:{l=leRCalibrB; 		break;}
		case 11:{l=leSpdCalibr; 	break;}
		case 12:{l=leSertPrintProtA;break;}
		case 13:{l=leSertPrintProtB;break;}
		default:return;
	}
	sdPath->FileName="file";
	sdPath->InitialDir=l->Text.Trim();
	if (sdPath->Execute())
	{
		l->Text=ExtractFilePath(sdPath->FileName);
	}
}
void __fastcall TAppManagment::BitBtn1Click(TObject *Sender)
{
	//сохранение параметров
	Set_Param(L"File_Save_Mode",cbMode->Checked?L"Auto":L"Manual");
	Set_Param(L"Sprog",leDistProg->Text);
	Set_Param(L"Tprog",leTimeProg->Text);
	Set_Param(L"TestResPosA",leProtA->Text);
	Set_Param(L"TestResPosB",leProtB->Text);
	Set_Param(L"ProtTtl",leTitleProt->Text);

	Set_Param(L"SpdCalibrTable",leSpdCalibr->Text);
	Set_Param(L"LoadCalibrTableA",leLoadCalibrA->Text);
	Set_Param(L"LoadCalibrTableB",leLoadCalibrB->Text);
	Set_Param(L"TCalibrTableA",leTCalibrA->Text);
	Set_Param(L"TCalibrTableB",leTCalibrB->Text);
	Set_Param(L"RCalibrTableA",leRCalibrA->Text);
	Set_Param(L"RCalibrTableB",leRCalibrB->Text);

	Set_Param(L"LoadSertPrintProtA",leSertPrintProtA->Text);
	Set_Param(L"LoadSertPrintProtB",leSertPrintProtB->Text);
}
