//---------------------------------------------------------------------------

#ifndef opcrwH
#define opcrwH
#include "def.h"
#include "opc.h"
//---------------------------------------------------------------------------
class OPCRW
{ public:
        __fastcall OPCRW(void);              // �����������
    int __fastcall ReadGr1(void);            // ������ ���������� ������ 1
    int __fastcall ReadGr2(void);            // ������ ���������� ������ 2
    int __fastcall ReadGr3(void);            // ������ ���������� ������ 3
    int __fastcall ReadGr4(void);            // ������ ���������� ������ 4
    int __fastcall ReadGr5(void);            // ������ ���������� ������ 5
    int __fastcall ReadGr6(void);            // ������ ���������� ������ 6
    int __fastcall ReadGr7(void);            // ������ ���������� ������ 7
    int __fastcall ReadGr8(void);            // ������ ���������� ������ 8
    int __fastcall ReadGr9(void);            // ������ ���������� ������ 9
    int __fastcall ReadGr10(void);           // ������ ���������� ������ 10
    int __fastcall ReadGr11(void);           // ������ ���������� ������ 11
    int __fastcall ReadGr12(void);           // ������ ���������� ������ 12
    int __fastcall ReadGr13(void);           // ������ ���������� ������ 13
    int __fastcall WriteGr1(bool *);         // ������ ���������� ������ 1
	int __fastcall WriteGr1(int *);          // ������ ����� ���������� ������ 1
	int __fastcall WriteGr1(float *);        // ������ float ���������� ������ 1
	int __fastcall WriteGr2(float *);        // ������ ������������ ���������� ������ 2
	int __fastcall WriteGr3(int *);          // ������ ����� ���������� ������ 3
    int __fastcall WriteGr3(float *);        // ������ ������������ ���������� ������ 3
    int __fastcall WriteGr4(void);           // ������ ������������ �������� ������ 4
    int __fastcall WriteGr5(void);           // ������ ����� �������� ������ 5
	int __fastcall WriteGr6(void);           // ������ ������������� ������� ������ 6
    int __fastcall ResetGr7(void);			 // ����� �������� ��� ���������� ������� 7
	int __fastcall WriteGr8(void);           // ������ ������������ �������� ������ 8
    int __fastcall WriteGr9(void);           // ������ ����� �������� ������ 9
	int __fastcall WriteGr10(void);          // ������ ������������� ������� ������ 10
	int __fastcall ResetGr11(void);			 // ����� �������� ��� ���������� ������� 11
    int __fastcall WriteGr12(void);          // ������ ������������� ������� ������ 12
    int __fastcall WriteGr13(void);          // ������ ������������� ������� ������ 13
    int __fastcall BenchControl(             // ���������� �������
                                bool  *pbw1,       // ���������� ���� bool �� ������ 1
                                bool  *pbw2,       // ���������� ���� bool �� ������ 1
                                float *pfw=NULL);  // ���������� ���� float �� ������ 3
    int __fastcall TestParamWrite(           // ������ ���������� ����� ���������
                                  float *pS,       // ���������� ���� float �� ������ 3
                                  int   *piw1,     // ���������� ���� int �� ������ 3
                                  int   *piw2,     // ���������� ���� int �� ������ 3
                                  int   *piw3,     // ���������� ���� int �� ������ 3
                                  int   *piw4);    // ���������� ���� int �� ������ 3

    int __fastcall ReadCycleParameters(void);// ������ ����������� ����������
  private:
    IOPCServer     *pIOPCServer;             // ��������� �� OPC-������
    IOPCItemMgt	   *pIOPCItemMgt1,           // ��������� �� ������
                   *pIOPCItemMgt2,
                   *pIOPCItemMgt3,
                   *pIOPCItemMgt4,
                   *pIOPCItemMgt5,
                   *pIOPCItemMgt6,
                   *pIOPCItemMgt7,
                   *pIOPCItemMgt8,
                   *pIOPCItemMgt9,
                   *pIOPCItemMgt10,
                   *pIOPCItemMgt11,
                   *pIOPCItemMgt12,
                   *pIOPCItemMgt13;
    IOPCSyncIO	   *pIOPCSyncIO1,            // ��������� �� ���������� �����/������
                   *pIOPCSyncIO2,
                   *pIOPCSyncIO3,
                   *pIOPCSyncIO4,
                   *pIOPCSyncIO5,
                   *pIOPCSyncIO6,
                   *pIOPCSyncIO7,
                   *pIOPCSyncIO8,
                   *pIOPCSyncIO9,
                   *pIOPCSyncIO10,
                   *pIOPCSyncIO11,
                   *pIOPCSyncIO12,
                   *pIOPCSyncIO13;
    OPCITEMDEF		ItemsGr1[GR1ITEMSNUM],   // ��������� � �������
                    ItemsGr2[GR2ITEMSNUM],
                    ItemsGr3[GR3ITEMSNUM],
                    ItemsGr4[GR4ITEMSNUM],
                    ItemsGr5[GR5ITEMSNUM],
                    ItemsGr6[GR6ITEMSNUM],
                    ItemsGr7[GR7ARRAYSNUM],
                    ItemsGr8[GR8ITEMSNUM],
                    ItemsGr9[GR9ITEMSNUM],
                    ItemsGr10[GR10ITEMSNUM],
                    ItemsGr11[GR11ARRAYSNUM],
                    ItemsGr12[GR12ITEMSNUM],
                    ItemsGr13[GR13ITEMSNUM];
    OPCITEMRESULT  *pItemResult1,            // ��������� �� ��������
                   *pItemResult2,
                   *pItemResult3,
                   *pItemResult4,
                   *pItemResult5,
                   *pItemResult6,
                   *pItemResult7,
                   *pItemResult8,
                   *pItemResult9,
                   *pItemResult10,
                   *pItemResult11,
                   *pItemResult12,
                   *pItemResult13;
    OPCHANDLE		GrpSrvHandle;
    HRESULT		   *pErrors,*pRErrors,r1;
    UINT			qnr;

    wchar_t        *pServerName;
    wchar_t        *pGr1Name,*pGr2Name,*pGr3Name,*pGr4Name,*pGr5Name,*pGr6Name,
                   *pGr7Name,*pGr8Name,*pGr9Name,*pGr10Name,*pGr11Name,*pGr12Name,*pGr13Name;
    _GUID           clsid;
    long            TimeBias;
    float           PercentDeadband;
    DWORD           RevisedUpdateRate;
    LPWSTR          ErrorStr;
};
#endif
