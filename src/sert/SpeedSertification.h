// ---------------------------------------------------------------------------

#ifndef SpeedSertificationH
#define SpeedSertificationH

// ---------------------------------------------------------------------------
class VSert
{
public:
   int Index; // текущий индекс таблицы
   float TargetV[29]; // столбец заданных скоростей
   String sTV[29]; // текстовое педставление заданных скоростей
   float ReadoutV[29]; // столбец считанных скоростей
   float MeasuredV[29]; // столбец измеренных скоростей
   float RelError[29]; // столбец относительных  погрешностей

   __fastcall VSert(void); // конструктор
   void __fastcall Clear(void); // очистить таблицу
   void __fastcall PrintProtocol(AnsiString fn); // распечатаь протокол в файл fn

private:

};
#endif
