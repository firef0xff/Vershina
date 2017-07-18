#pragma once
#ifndef t_sertH
#define t_sertH
#include <string>

namespace sert
{
class TSert // класс аттестации температуры
{
public:
   enum
   {
      ITEMS_COUNT = 20
   };

   TSert(std::string const& pos);
   void Clear();
   void PrintProtocol( std::string const& fn );


   int Index; // текущий индекс таблицы
   float ReadoutT[ITEMS_COUNT]; // столбец считанных температур
   float MeasuredT[ITEMS_COUNT]; // столбец измеренных температур
   float RelError[ITEMS_COUNT]; // столбец относительных погрешностей


private:
   std::string mPos;
};
}

#endif // TSERT_H
