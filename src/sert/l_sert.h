#pragma once
#ifndef l_sertH
#define l_sertH
#include <string>
namespace sert
{

class LSert // класс аттестации нагрузки
{
public:

   enum
   {
//      ITEMS_COUNT = 25
//      ITEMS_COUNT = 13
        ITEMS_COUNT = 9
   };

   LSert(  std::string const& pos ); // конструктор
   void Clear(); // очистить таблицу
   void PrintProtocol( std::string const& file);

   int Index; // текущий индекс таблицы
   float TargetLd[ITEMS_COUNT]; // столбец заданных скоростей
   std::string sTLd[ITEMS_COUNT]; // текстовое педставление заданных скоростей
   float ReadoutLd[ITEMS_COUNT]; // столбец считанных скоростей
   float MeasuredLd[ITEMS_COUNT]; // столбец измеренных скоростей
   float RelError[ITEMS_COUNT]; // столбец относительных погрешностей


private:
    std::string mPos;
};


}

#endif // LSERT_H
