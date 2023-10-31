//---------------------------------------------------------------------------

#ifndef TyreProtH
#define TyreProtH
#include <SysUtils.hpp>
#include <Printers.hpp>
#include "def.h"
//---------------------------------------------------------------------------
class Tyre
{ public:

// ���������� ���������
    int       ProtNo;            // ����� ���������
    String    Size;              // ������ ����
    String    Model;             // ������ ����
    String    TestProcedure;     // �������� ���������
    String    StandName;         // ������������ ������
    String    Manufacturer;      // ������������ ����
    float     DrumDiameter;      // ������� ��������
    String    TestCustomer;      // ��������
    TDateTime ManufactDate;      // ���� ������������
    TDateTime Start;             // ���� ������ ���������
    TDateTime Stop;              // ���� ��������� ���������
    int       FormNo;            // ����� ����� ���������
    int       OrderNo;           // ����� ������
    int       PerfSpecNo;        // ����� ��
    int       SerialNo;          // ���������� ����� ����
    String    LoadIndex;         // ������ �������� ����
    float     MaxLoad;           // ������������ ��������
    String    SpeedInd;          // ������ ��������
    float     MaxSpeed;          // ������������ ��������
    float     StaticR;           // ����������� ������
    float     OuterD;            // �������� �������
    String    WheelRim;          // ����������� �����
    float     MaxLoadPress;      // �������� ��� ����������� ��������
    int       ProfileWide;       // ������ �������
    int       Type;              // ��� ��������, 0-����������, 1-������������
    float     CurrentLoad;       // ��������
    float     InitPressure;      // ��������� ��������
    float     CurrentSpeed;      // ��������
    int       TestMode;          // ����� ���������, 0-�� �������, 1-�� ����
    int       TotalTime;         // ����� ����� ���������, ����
    float     TotalS;            // �������� ���� ���������
    int       StepsNo;           // ���������� ����� ���������
	int       PollsNo;           // ���������� �������
    int       rT[250]; // ������� � ������������ ���������
    float     rV[250];
    float     rS[250];
    float     rL[250];
    float     rR[250];
	float     rTemp[250];
    float     Mass;               //�����

              __fastcall Tyre(void);                       // �����������
              __fastcall ~Tyre(void);                      // ����������
    Tyre      __fastcall operator=(Tyre op2);              // ��������������� ������������
    void      __fastcall WriteTyreToFile(String fname);    // ������ ����� Tyre � ���� � ������ fname
    void      __fastcall ReadTyreFmFile(String fname);     // ������ ����� Tyre �� ����� � ������ fname
	void      __fastcall PrintProtToFile(String fname,String side);    // ������ ��������� ��������� � ���� fname
	void      __fastcall PrintProtocol(TPrinter *pprt,String side);    // ������ ��������� �� ������� pprt
	void	Clear	(void);//������� �������� (��� ���������� �������� �� ��������, ������ �������� �������� �� ������ �������)

	AnsiString CustomDate (void)
	{
		int week_num;
		Word year, month, day;
		ManufactDate.DecodeDate(&year,&month,&day);	// ������������ ���� ���� �� ������������
		TDateTime _1_jan(year,1,1);		// 1-� ������ ���� ����, �������� ������������� ����
		int _1_jan_day_of_week = (_1_jan.DayOfWeek()+5)%7; // ���� ������ 1-�� ������
		week_num = (int)(ManufactDate-TDateTime(year,1,1)+_1_jan_day_of_week)/7; // ������� ����� ������(� 0)
		return AnsiString(week_num)+":"+AnsiString(year).SubString(3,2);
	}
	void  	CustomDate  (AnsiString dt)
	{
		int delim = dt.Pos(".");
		int week=dt.SubString(1,delim-1).ToIntDef(0);
		short year=dt.SubString(delim+1,dt.Length()-delim).ToIntDef(0);
	   	ManufactDate=TDateTime(year,1,1)+7*(week);
		return;
	}
  private:
};
#endif
