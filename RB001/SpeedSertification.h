//---------------------------------------------------------------------------

#ifndef SpeedSertificationH
#define SpeedSertificationH
//---------------------------------------------------------------------------
class VSert
{ public:
    int    Index;                            // ������� ������ �������
    float  TargetV[29];                      // ������� �������� ���������
    String sTV[29];                          // ��������� ������������ �������� ���������
    float  ReadoutV[29];                     // ������� ��������� ���������
    float  MeasuredV[29];                    // ������� ���������� ���������
    float  RelError[29];                     // ������� ������������� ������������

         __fastcall VSert(void);             // �����������
    void __fastcall Clear(void);             // �������� �������
    void __fastcall PrintProtocol(String fn);// ���������� �������� � ���� fn
  private:

};
#endif
