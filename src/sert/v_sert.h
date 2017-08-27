#pragma once
#ifndef v_sertH
#define v_sertH

#include <string>
namespace sert
{

class VSert // класс аттестации скорости
{
public:
   enum
   {
      ITEMS_COUNT = 33 //размер таблицы аттестации скорости
   };

   VSert();
   void Clear();

   void PrintProtocol( std::string const& file );

   int Index; // текущий индекс таблицы
   float TargetV[ITEMS_COUNT]; // столбец заданных скоростей
   std::string sTV[ITEMS_COUNT]; // текстовое педставление заданных скоростей
   float ReadoutV[ITEMS_COUNT]; // столбец считанных скоростей
   float MeasuredV[ITEMS_COUNT]; // столбец измеренных скоростей
   float RelError[ITEMS_COUNT]; // столбец относительных погрешностей


private:
   VSert( VSert const& ) = delete;
   void operator = ( VSert const& ) = delete;
};
}

#endif // VSERT_H
