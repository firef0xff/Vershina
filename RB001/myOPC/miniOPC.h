//---------------------------------------------------------------------------
#pragma once
#ifndef miniOPCH
#define miniOPCH
#include "opc.h"
#include <list>
#include <Classes.hpp>
#include <thread>
#include <memory>
#include <vector>

//типы
class GroupPTRs                 //структура с данными по шруппе ОПС сервера
{
public:
	GroupPTRs():pItemMgt(nullptr),pSyncIO(nullptr),pItems(),pItemResult(nullptr){}
	~GroupPTRs()
	{
		if (pItemResult)
		{
			CoTaskMemFree(pItemResult);
		}
	}
IOPCItemMgt		*pItemMgt;		//указатель на Группу адресов с данными
IOPCSyncIO  	*pSyncIO;		//Указатель на ентерфейс для синхронизации данных
std::vector<OPCITEMDEF> pItems;	//массив с элементами группы
OPCITEMRESULT   *pItemResult;	//указатель на элемент
size_t			ItemsCount;		//количество элементов в группе
};
typedef std::list  <std::shared_ptr<GroupPTRs> >::const_iterator Item;
typedef unsigned __int64 GROUP_ID;
enum types{tBOOL,tINT,tFLOAT};

class myOPC
{
public:
	myOPC(wchar_t *ServerName=L"OPC.SimaticNET");//конструктор
	~myOPC(void);//деструктор

	GROUP_ID  AddGroup(wchar_t *pGroupName,wchar_t * Addresses[],size_t ItemsCount);
	OPCITEMSTATE*	Read 	(GROUP_ID _id); //вернуть минимально возможный набор который нужно будет распределить в массив
	HRESULT	WriteValue   (GROUP_ID _id,size_t pos,void *item,types type);
	HRESULT	WriteMass    (GROUP_ID _id,size_t pos,size_t mass_len,void *item,types type);
	void OpcMassFree(GROUP_ID _id,OPCITEMSTATE* mass);
private:
	//функции
	Item GetGroup(GROUP_ID _id);
	//данные
	IOPCServer 		*pIOPCServer;	//указатель на OPC сервер

    std::list  <std::shared_ptr<GroupPTRs> > Groups;//Данные по группам сервера
	OPCHANDLE		GrpSrvHandle;
	HRESULT		    *pErrors,*pRErrors,result;
	UINT			qnr;

	_GUID           clsid;		//идентификатор класса сервера
	long            TimeBias; 	//смещение времени
    float           PercentDeadband;
    DWORD           RevisedUpdateRate;


	//состояние сервера
	bool Connected;
	#ifdef _mDEBUG
public:
	static String log;
private:
	LPWSTR ErrorStr;
	#endif
};
#ifdef _mDEBUG
String myOPC::log="";
#endif
#endif
