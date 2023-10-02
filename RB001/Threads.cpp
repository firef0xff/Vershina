//---------------------------------------------------------------------------


#pragma hdrstop

#include "Threads.h"
#include "def.h"
#include "RBCommon.h"
#include "opcrw.h"
#include "miniOPC.h"


#pragma package(smart_init)
bool CD_reset1=false;
bool CD_reset2=false;
unsigned long __stdcall ListenCD9904(void *msg)
{
    std::shared_ptr<myOPC> ThreadOPC(new myOPC());
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

//											db10.dbx38.5  � db10.dbx38.6
	float values[CD9904GroupSize]={0.0};
	bool  resets[ResetGroupSize]={false};
	//�������������� �����
	GROUP_ID id=ThreadOPC->AddGroup(L"CD9904Group",CD9904Group,CD9904GroupSize);

	if (cd_9904->Sensor())//�������� ����������� �������
	{
		std::shared_ptr<CD_9904::Sensor> sensor(new CD_9904::Sensor(cd_9904->Sensor()->GetPort(),cd_9904->Sensor()->GetAddr()));
	   //������� ����
	   while (1)
		{
           #ifdef _mDEBUG
			myOPC::log = "";
            #endif
			//������ ����������� ������
			if (CD_reset1/**Reset1*/)
			{
				cd_9904->ResetBus_1();
				CD_reset1 = false;
			}
			if (CD_reset2/**Reset2*/)
			{
				cd_9904->ResetBus_2();
				CD_reset2 = false;
			}
			std::shared_ptr<CD_9904::Data> data;
			CD_9904::ErrCode err=sensor->Tansl_Speed(data);
			//CD_9904::ErrCode err=CD_9904::ErrCode::Sucsess;
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
				prevres=res;               //�������� ������� ���������  */
				#ifdef _DEBUG
				ThreadCounter++;
				#endif
				//StendConnection = true;
			}else
			{
				StendConnection=false;
			}
			Application->ProcessMessages();
		}
	}
	CD_9904Thread=0;
    ThreadOPC.reset();
	return 0;
//����� �����������
}
