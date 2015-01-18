//---------------------------------------------------------------------------

#ifndef SertificationH
#define SertificationH
#include "def.h"
//---------------------------------------------------------------------------
class VSert                                  // ����� ���������� ��������
{ public:
    int    Index;                            // ������� ������ �������
    float  TargetV[VQTY];                    // ������� �������� ���������
    String sTV[VQTY];                        // ��������� ������������ �������� ���������
    float  ReadoutV[VQTY];                   // ������� ��������� ���������
    float  MeasuredV[VQTY];                  // ������� ���������� ���������
    float  RelError[VQTY];                   // ������� ������������� ������������

         __fastcall VSert(void);             // �����������
    void __fastcall Clear(void);             // �������� �������
    void __fastcall PrintProtocol(String fn);// ���������� �������� � ���� fn
  private:

};

class LSert                                  // ����� ���������� ��������
{ public:
    int    Index;                            // ������� ������ �������
    float  TargetLd[LDQTY];                     // ������� �������� ���������
    String sTLd[LDQTY];                         // ��������� ������������ �������� ���������
    float  ReadoutLd[LDQTY];                    // ������� ��������� ���������
    float  MeasuredLd[LDQTY];                   // ������� ���������� ���������
    float  RelError[LDQTY];                     // ������� ������������� ������������

         __fastcall LSert(void);             // �����������
    void __fastcall Clear(void);             // �������� �������
    void __fastcall PrintProtocol(// ���������� �������� � ���� fn
                                  String fn,
                                  String posname);
  private:

};

class TSert                                  // ����� ���������� �����������
{ public:
    int    Index;                            // ������� ������ �������
    float  ReadoutT[TQTY];                   // ������� ��������� ����������
    float  MeasuredT[TQTY];                  // ������� ���������� ����������
    float  RelError[TQTY];                   // ������� ������������� ������������

         __fastcall TSert(void);             // �����������
    void __fastcall Clear(void);             // �������� �������
    void __fastcall PrintProtocol(// ���������� �������� � ���� fn
                                  String fn,
                                  String posname);
  private:

};

class RSert                                  // ����� ���������� ��������
{ public:
    int    Index;                            // ������� ������ �������
    float  ReadoutR[RQTY];                   // ������� ��������� ��������
    float  MeasuredR[RQTY];                  // ������� ���������� ��������
    float  RelError[RQTY];                   // ������� ������������� ������������

         __fastcall RSert(void);             // �����������
    void __fastcall Clear(void);             // �������� �������
    void __fastcall PrintProtocol(// ���������� �������� � ���� fn
                                  String fn,
                                  String posname);
  private:

};

class LCalibr                                // ����� ���������� ��������
{ public:
    int    Index;                            // ������� ������ �������
    float  TargetLd[LDCQTY];                 // ������� �������� ��������
    String sTLd[LDCQTY];                     // ��������� ������������ �������� ��������
    float  ReadoutLd[LDCQTY];                // ������� ��������� ��������
    float  MeasuredLd[LDCQTY];               // ������� ���������� ��������
    float  KA[LDCQTY];                       // ������� �������������
    float  ReadKA[LDCQTY];                   // ������� �������������, ��������� �� �����������
	bool   loaded;							 //���� ��������� ������� �������� �� �����������
         __fastcall LCalibr(void);           // �����������
    void __fastcall LKQInit(                 // ������������� ������������� � ��������� �������� ��� ����������
                            float *Q[],      // ����� ���������� ������
                            float *A[]);     // ����� ���������� �������������
    void __fastcall LKRead(                  // ������ ������������� �� A (DB70,71) � Read��
                           float *A[]);      // ����� ���������� �������������
    void __fastcall LKMult(void);            // ������������ �� � ReadKA
    void __fastcall LKSetting(               // �������� ������������� ��� ����������
                              float *A[]);   // ����� ���������� �������������
    void __fastcall Clear(void);             // �������� �������
    void __fastcall PrintProtocol(// ���������� �������� � ���� fn
                                  String fn,
                                  String posname);
  private:

};

#endif

