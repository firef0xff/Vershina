#define ADDRLEN         100    // ������������ ����� ������ ��� ������ ������ ��������

#define GR1BOOLITEMSNUM  41    // ���������� ������� ���������� � ������ 1
#define GR1INTITEMSNUM   11    // ���������� ����� ���������� � ������ 1
#define GR1FLTITEMSNUM   13     // ���������� ������������ ���������� � ������ 1
#define GR1ITEMSNUM      GR1BOOLITEMSNUM+GR1INTITEMSNUM+GR1FLTITEMSNUM    // ���������� ���������� � ������ 1

#define GR2FLOATITEMSNUM 23    //���������� ������������ ���������� ������ 2
#define GR2INTITEMSNUM	 2     // ���������� ����� ���������� � ������ 2
#define GR2ITEMSNUM      GR2FLOATITEMSNUM+GR2INTITEMSNUM    // ���������� ���������� � ������ 2

#define GR3INTITEMSNUM    8    // ���������� ����� ���������� � ������ 3
#define GR3FLTITEMSNUM   23    // ���������� ������������ ���������� � ������ 3
#define GR3ITEMSNUM      GR3INTITEMSNUM+GR3FLTITEMSNUM    // ���������� ���������� � ������ 3


#define GR41ITEMSNUM    250    // ���������� ���������� � ������� 1 ������ 4
#define GR42ITEMSNUM    100    // ���������� ���������� � ������� 2 ������ 4
#define GR4ITEMSNUM     GR41ITEMSNUM+GR42ITEMSNUM    // ���������� ���������� � ������ 4


#define GR51ITEMSNUM    250    // ���������� ���������� � ������� 1 ������ 5
#define GR52ITEMSNUM    100    // ���������� ���������� � ������� 2 ������ 5
#define GR5ITEMSNUM     GR51ITEMSNUM+GR52ITEMSNUM    // ���������� ���������� � ������ 5


#define GR6ITEMSNUM     200    // ���������� ���������� � ������ 6
#define GR7ARRAYSNUM      6    // ���������� �������� � ������ 7
#define GR7ARRAYSIZE    250    // ������ �������� � ������ 7

#define GR81ITEMSNUM    250    // ���������� ���������� � ������� 1 ������ 8
#define GR82ITEMSNUM    100    // ���������� ���������� � ������� 2 ������ 8
#define GR8ITEMSNUM     GR81ITEMSNUM+GR82ITEMSNUM    // ���������� ���������� � ������ 8

#define GR91ITEMSNUM    250    // ���������� ���������� � ������� 1 ������ 9
#define GR92ITEMSNUM    100    // ���������� ���������� � ������� 2 ������ 9
#define GR9ITEMSNUM     GR91ITEMSNUM+GR92ITEMSNUM    // ���������� ���������� � ������ 9

#define GR10ITEMSNUM    200    // ���������� ���������� � ������ 10

#define GR11ARRAYSNUM     6    // ���������� �������� � ������ 11
#define GR11ARRAYSIZE   250    // ������ �������� � ������ 11

#define GR12ITEMSNUM     26     //80    // ���������� ���������� � ������ 12
#define GR12ARRAYSIZE    10     //40    // ���������� ���������� � ������� ������ 12
#define GR13ITEMSNUM     26     //80    // ���������� ���������� � ������ 13
#define GR13ARRAYSIZE    10     //40    // ���������� ���������� � ������� ������ 13

#define MAXNUMOFSTEPS   100    // ������������ ���������� ����� ��������� ���������
#define MAXNUMOFPOLLS   250    // ������������ ���������� �������
// ����������� ����������� ���������
#define WM_LogPrint  WM_USER
#define WM_DataShow  WM_USER+1
#define WM_OPCCmd    WM_USER+2
// ����� ���������� �� ���������� OPCCtrlStat
#define IDDLESTAT      0
#define READGR1        1
#define WRITEGR1ITEM   2
// ����� ���������� ��� ������� OnDataShow
#define COMMONPRMSHOW  0
// ������� ������ ��� ����������
#define VQTY          33
#define LDQTY         10
#define TQTY          20
#define RQTY          20
#define LDCQTY		  13   //20
#define LOWTLIM      -50
#define UPPERTLIM    150

//��������� ������
#define MIN_SPEED 10
#define MAX_SPEED 150
#define MIN_LOAD  10
#define MAX_LOAD  70
//�����
#ifdef _DEBUG
	  //#define  _mDEBUG
	  //#define    _NO_Write
#endif

//���������
#define _NOS_SHOW_SEK   //�������� ����� ��� ������� ��� ������� �� �������

#define DELAY_TIME 5000  //5 ���
#define USEPROCESSDELAY /*�������� �������� �� ������� ��� ������������
						  //�������� ��� ���������� � ���������� ������������*/

// ������������ �����������
#define LOWTEMP   37
#define HIGHTTEMP 55
