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
	//������� �����
	const int CD9904GroupSize=5;
	const int ResetGroupSize=2;
	//�������� �����
	wchar_t *CD9904Group[CD9904GroupSize]={
											L"S7:[S7 connection_4]DB20,REAL204",    //��������
											L"S7:[S7 connection_4]DB20,REAL18",
											L"S7:[S7 connection_4]DB20,REAL58",
											L"S7:[S7 connection_4]DB20,DINT26",
											L"S7:[S7 connection_4]DB20,DINT66"
											};
	wchar_t *ResetGroup[ResetGroupSize]={
											L"S7:[S7 connection_4]IX124.0",
											L"S7:[S7 connection_4]IX124.3"
											};                          	//������� ������
	float values[CD9904GroupSize]={0.0};
	bool  resets[ResetGroupSize]={false};
	//�������������� �����
	GROUP_ID id=ThreadOPC->AddGroup(L"CD9904Group",CD9904Group,CD9904GroupSize);
	GROUP_ID reset_id=ThreadOPC->AddGroup(L"ResetGroup",ResetGroup,ResetGroupSize);

	if (cd_9904->Sensor())//�������� ����������� �������
	{
		CD_9904::Sensor *sensor =new CD_9904::Sensor(cd_9904->Sensor()->GetPort(),cd_9904->Sensor()->GetAddr());
	   //������� ����
	   while (1)
		{
           #ifdef _mDEBUG
			myOPC::log = "";
            #endif
			//������ ����������� ������
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
				speed=speed==350?*fakt_speed:speed; //������� ������ ������ ������ ���������� ����� �� ��������� ����� 350 �����-�� �����
				values[0]=speed<=10?0.0:speed;//������� 0 ��������       		fakt_speed
				values[1]=(float)data->Road_1();//������� 3 ��������� ���� 1    fakt_distance_1
				values[2]=(float)data->Road_2();//������� 9 ��������� ���� 2    fakt_distance_2
				values[3]=data->Time_1().Get_msek(); //DB20,DINT26 ����. ����� 1
				values[4]=data->Time_2().Get_msek(); //DB20,DINT66 ����. ����� 2
				static bool prevres=true; //����������� ���������� ��� ��������� ������� ������ ������
				bool res=false;    //���������� ��������� ���������� ������
				HRESULT RES=ThreadOPC->WriteMass(id,0,CD9904GroupSize,&values[0],tFLOAT);//������+ ��������� ����������
			   /*	if (RES==S_OK||RES==S_FALSE)  //���� ������ ������� �� ����
				{              //������� �� ��� ������ ��� �� ������ ����������
					res=true;
				}   */
				if (RES==0xC0048003)  //���� ������ ������� �� ����
				{              //������� �� ������� ������ ��� �� ������ ����������
					res=false;
				}else
				{
					res=true;
				}
				StendConnection=res+prevres;//�������������� bool ��� ����� �������� ���������� � �����������
											//��� ���� ����������� � false ������ ��� �������� false
				prevres=res;               //�������� ������� ���������
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
//����� �����������
}
