#ifndef r_sertH
#define r_sertH
#include <string>

namespace sert
{
class RSert // класс аттестации радиусов
{
public:
   enum
   {
      ITEMS_COUNT = 20
   };
   RSert( std::string const& pos );
   void Clear();
   void PrintProtocol(const std::string &fn);

   int Index; // текущий индекс таблицы
   float ReadoutR[ITEMS_COUNT]; // столбец считанных радиусов
   float MeasuredR[ITEMS_COUNT]; // столбец измеренных радиусов
   float RelError[ITEMS_COUNT]; // столбец относительных погрешностей


private:
    std::string mPos;
};
}

#endif // RSERT_H
