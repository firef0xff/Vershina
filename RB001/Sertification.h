//---------------------------------------------------------------------------

#ifndef SertificationH
#define SertificationH
#include "def.h"
//---------------------------------------------------------------------------
class VSert                                  // класс аттестации скорости
{ public:
    int    Index;                            // текущий индекс таблицы
    float  TargetV[VQTY];                    // столбец заданных скоростей
    String sTV[VQTY];                        // текстовое педставление заданных скоростей
    float  ReadoutV[VQTY];                   // столбец считанных скоростей
    float  MeasuredV[VQTY];                  // столбец измеренных скоростей
    float  RelError[VQTY];                   // столбец относительных погрешностей

         __fastcall VSert(void);             // конструктор
    void __fastcall Clear(void);             // очистить таблицу
    void __fastcall PrintProtocol(String fn);// распечатаь протокол в файл fn
  private:

};

class LSert                                  // класс аттестации нагрузки
{ public:
    int    Index;                            // текущий индекс таблицы
    float  TargetLd[LDQTY];                     // столбец заданных скоростей
    String sTLd[LDQTY];                         // текстовое педставление заданных скоростей
    float  ReadoutLd[LDQTY];                    // столбец считанных скоростей
    float  MeasuredLd[LDQTY];                   // столбец измеренных скоростей
    float  RelError[LDQTY];                     // столбец относительных погрешностей

         __fastcall LSert(void);             // конструктор
    void __fastcall Clear(void);             // очистить таблицу
    void __fastcall PrintProtocol(// распечатаь протокол в файл fn
                                  String fn,
                                  String posname);
  private:

};

class TSert                                  // класс аттестации температуры
{ public:
    int    Index;                            // текущий индекс таблицы
    float  ReadoutT[TQTY];                   // столбец считанных температур
    float  MeasuredT[TQTY];                  // столбец измеренных температур
    float  RelError[TQTY];                   // столбец относительных погрешностей

         __fastcall TSert(void);             // конструктор
    void __fastcall Clear(void);             // очистить таблицу
    void __fastcall PrintProtocol(// распечатаь протокол в файл fn
                                  String fn,
                                  String posname);
  private:

};

class RSert                                  // класс аттестации радиусов
{ public:
    int    Index;                            // текущий индекс таблицы
    float  ReadoutR[RQTY];                   // столбец считанных радиусов
    float  MeasuredR[RQTY];                  // столбец измеренных радиусов
    float  RelError[RQTY];                   // столбец относительных погрешностей

         __fastcall RSert(void);             // конструктор
    void __fastcall Clear(void);             // очистить таблицу
    void __fastcall PrintProtocol(// распечатаь протокол в файл fn
                                  String fn,
                                  String posname);
  private:

};

class LCalibr                                // класс калибровки нагрузки
{ public:
    int    Index;                            // текущий индекс таблицы
    float  TargetLd[LDCQTY];                 // столбец заданных нагрузок
    String sTLd[LDCQTY];                     // текстовое педставление заданных нагрузок
    float  ReadoutLd[LDCQTY];                // столбец считанных нагрузок
    float  MeasuredLd[LDCQTY];               // столбец измеренных нагрузок
    float  KA[LDCQTY];                       // столбец коэффициентов
    float  ReadKA[LDCQTY];                   // столбец коэффициентов, считанных из контроллера
	bool   loaded;							 //флаг индикатор события загрузки из контроллера
         __fastcall LCalibr(void);           // конструктор
    void __fastcall LKQInit(                 // инициализация коэффициентов и граничных нагрузок для калибровки
                            float *Q[],      // масив указателей границ
                            float *A[]);     // масив указателей коэффициентов
    void __fastcall LKRead(                  // чтение коэффициентов из A (DB70,71) в ReadКА
                           float *A[]);      // масив указателей коэффициентов
    void __fastcall LKMult(void);            // перемножение КА и ReadKA
    void __fastcall LKSetting(               // устанока коэффициентов для калибровки
                              float *A[]);   // масив указателей коэффициентов
    void __fastcall Clear(void);             // очистить таблицу
    void __fastcall PrintProtocol(// распечатаь протокол в файл fn
                                  String fn,
                                  String posname);
  private:

};

#endif

