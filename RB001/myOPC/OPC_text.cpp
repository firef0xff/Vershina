//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
 #include <windows.h>
#include <tchar.h>
#include <iostream.h>
#include "miniOPC.h"
#pragma argsused
/*
#define GR1BOOLITEMSNUM  33    // количество булевых переменных в группе 1
#define GR1INTITEMSNUM   11    // количество целых переменных в группе 1
#define GR1FLTITEMSNUM   1     // количество вещественных переменных в группе 1
#define GR1ITEMSNUM      GR1BOOLITEMSNUM+GR1INTITEMSNUM+GR1FLTITEMSNUM    // количество переменных в группе 1    */
#define GR1ITEMSNUM      1
myOPC *OPC;
GROUP_ID GroupID;
void PrintLog(void);
void AddGroups(void);
// адреса переменных в контроллере
wchar_t *Gr1ItemsNme[GR1ITEMSNUM]={	/*L"S7:[S7 connection_4]MX2.1",
									L"S7:[S7 connection_4]IX125.3", // заменить M125 на I125!!!!!
									L"S7:[S7 connection_4]MX50.1",
									L"S7:[S7 connection_4]MX3.1",
									L"S7:[S7 connection_4]IX125.7",
									L"S7:[S7 connection_4]MX50.2",  // заменить M125 на I125!!!!!
									L"S7:[S7 connection_4]MX50.3",
									L"S7:[S7 connection_4]MX50.4",
									L"S7:[S7 connection_4]MX50.5",
									L"S7:[S7 connection_4]MX50.6",
									L"S7:[S7 connection_4]MX2.2",
									L"S7:[S7 connection_4]MX3.2",
									L"S7:[S7 connection_4]MX34.0",
									L"S7:[S7 connection_4]MX34.2",
									L"S7:[S7 connection_4]MX34.1",
									L"S7:[S7 connection_4]MX34.3",
									L"S7:[S7 connection_4]MX34.4",
									L"S7:[S7 connection_4]MX34.5",
									L"S7:[S7 connection_4]MX34.6",
									L"S7:[S7 connection_4]DB10,X2.0",
									L"S7:[S7 connection_4]DB10,X2.1",
									L"S7:[S7 connection_4]DB10,X2.2",
									L"S7:[S7 connection_4]DB10,X2.3",
									L"S7:[S7 connection_4]DB10,X2.4",
									L"S7:[S7 connection_4]DB10,X2.5",
									L"S7:[S7 connection_4]DB10,X2.6",
									L"S7:[S7 connection_4]DB10,X3.0",
									L"S7:[S7 connection_4]DB10,X38.0",
									L"S7:[S7 connection_4]DB10,X38.1",
									L"S7:[S7 connection_4]DB10,X38.2",
									L"S7:[S7 connection_4]DB10,X38.3",
									L"S7:[S7 connection_4]DB10,X38.4",
									L"S7:[S7 connection_4]DB10,X39.0",
									L"S7:[S7 connection_4]DB20,DINT14",
									L"S7:[S7 connection_4]DB20,DINT26",
									L"S7:[S7 connection_4]DB20,DINT38",
									L"S7:[S7 connection_4]DB20,DINT42",
									L"S7:[S7 connection_4]DB20,DINT66",
									L"S7:[S7 connection_4]DB20,DINT78",
									L"S7:[S7 connection_4]DB20,DINT82",
									L"S7:[S7 connection_4]DB20,DINT148",
									L"S7:[S7 connection_4]DB20,DINT152",
									L"S7:[S7 connection_4]DB20,DINT180",
									L"S7:[S7 connection_4]DB20,DINT184",*/
									L"S7:[S7 connection_4]DB10,INT70"
								  };

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char q;
	do
	{
		OPC=new myOPC();
		AddGroups();
		int *t=new int(0);
		OPC->WriteValue(GroupID,0,(void *)t,tINT);
		delete t;
		OPCITEMSTATE* rez=OPC->Read(GroupID);
		for (int i= 0; i <GR1ITEMSNUM; i++)
		{
			cout<<rez->vDataValue.lVal<<endl;
		}
		delete OPC;
		#ifdef _mDEBUG
		PrintLog();
		#endif
		cin>>q;
	}while (q=='r');

	return 0;
}
void AddGroups(void)
{
	GroupID=OPC->AddGroup(L"Gr1Bool",Gr1ItemsNme,GR1ITEMSNUM);
}
void PrintLog(void)
{
	#ifdef _mDEBUG
	char* rus=new char[OPC->log.Length()+10];
	CharToOem(OPC->log.c_str(),rus);
	cout<<rus;
	delete []rus;
	#endif
}
//---------------------------------------------------------------------------
