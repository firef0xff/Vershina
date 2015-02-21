//---------------------------------------------------------------------------


#pragma hdrstop

#include "Threads.h"
#include "def.h"
#include "RBCommon.h"
#include "opcrw.h"
#include "miniOPC.h"


#pragma package(smart_init)
unsigned long __stdcall ListenCD9904(void *msg)
{
	myOPC *ThreadOPC=new myOPC();
	//размеры групп
	const int CD9904GroupSize=5;
	const int ResetGroupSize=2;
	//описание групп
	wchar_t *CD9904Group[CD9904GroupSize]={
											L"S7:[S7 connection_4]DB20,REAL204",    //скорость
											L"S7:[S7 connection_4]DB20,REAL18",
											L"S7:[S7 connection_4]DB20,REAL58",
											L"S7:[S7 connection_4]DB20,DINT26",
											L"S7:[S7 connection_4]DB20,DINT66"
											};
	wchar_t *ResetGroup[ResetGroupSize]={
											L"S7:[S7 connection_4]IX124.0",
											L"S7:[S7 connection_4]IX124.3"
											};                          	//массивы данных
	float values[CD9904GroupSize]={0.0};
	bool  resets[ResetGroupSize]={false};
	//идентификаторы групп
	GROUP_ID id=ThreadOPC->AddGroup(L"CD9904Group",CD9904Group,CD9904GroupSize);
	GROUP_ID reset_id=ThreadOPC->AddGroup(L"ResetGroup",ResetGroup,ResetGroupSize);

	if (cd_9904->Sensor())//проверка подключения датчика
	{
		CD_9904::Sensor *sensor =new CD_9904::Sensor(cd_9904->Sensor()->GetPort(),cd_9904->Sensor()->GetAddr());
	   //рабочий цикл
	   while (1)
		{
           #ifdef _mDEBUG
			myOPC::log = "";
            #endif
			//чтение индикаторов ресета
			OPCITEMSTATE* rez=ThreadOPC->Read(reset_id);
			if (!rez)
			{
				Application->ProcessMessages();
				continue;
			}
			for (size_t i = 0; i<ResetGroupSize; i++)
			{
				resets[i]=rez[i].vDataValue.boolVal;
			}
			ThreadOPC->OpcMassFree(reset_id,rez);
			if (resets[0]/**Reset1*/)
			{
				cd_9904->ResetBus_1();
			}
			if (resets[1]/**Reset2*/)
			{
				cd_9904->ResetBus_2();
			}
			CD_9904::Data *data=0;
			CD_9904::ErrCode err=sensor->Tansl_Speed(&data);
			if (err==CD_9904::ErrCode::Sucsess)
			{
				float speed=(float)data->Speed();
				speed=speed==350?*fakt_speed:speed; //попытка обхода ошибки работы спидометра когда он спонтанно кажет 350 какое-то время
				values[0]=speed<=10?0.0:speed;//позиция 0 скорость       		fakt_speed
				values[1]=(float)data->Road_1();//позиция 3 дистанция шины 1    fakt_distance_1
				values[2]=(float)data->Road_2();//позиция 9 дистанция шины 2    fakt_distance_2
				values[3]=data->Time_1().Get_msek(); //DB20,DINT26 факт. время 1
				values[4]=data->Time_2().Get_msek(); //DB20,DINT66 факт. время 2
				static bool prevres=true; //статическая переменная для отсечения разовых ошибок записи
				bool res=false;    //переменная индикаотр успешности записи
				HRESULT RES=ThreadOPC->WriteMass(id,0,CD9904GroupSize,&values[0],tFLOAT);//запись+ получение результата
			   /*	if (RES==S_OK||RES==S_FALSE)  //если запись успешна то норм
				{              //реакция на все ощибки как на разрыв соединения
					res=true;
				}   */
				if (RES==0xC0048003)  //если запись успешна то норм
				{              //реакция на таймаут ощибки как на разрыв соединения
					res=false;
				}else
				{
					res=true;
				}
				StendConnection=res+prevres;//результирующий bool это сумма текущего результата и предыдущего
											//что дает сбрасывание в false только при обоюдном false
				prevres=res;               //сохраним текущий результат
				#ifdef _DEBUG
				ThreadCounter++;
				#endif
			}else
			{
				StendConnection=false;
			}
			if (data)
			{
				delete data;
				data=nullptr;
			}
			Application->ProcessMessages();
		}
	}else
	{
		CD_9904Thread=0;
		delete ThreadOPC;
		TerminateThread(CD_9904Thread,0);
	}
	return 0;
//конец встраивания
}
