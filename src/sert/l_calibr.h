#pragma once
#ifndef l_calibrH
#define l_calibrH
#include <string>
#include "../cpu/data/gr12.h"

namespace sert
{
class LCalibr // класс калибровки нагрузки
{
public:
enum
{
   ITEMS_COUNT = 39
};

   LCalibr( std::string const& pos );

   // инициализация коэффициентов и граничных нагрузок для калибровки
   void LKQInit( cpu::data::GR12& data ); // масив коэффициентов

   // чтение коэффициентов из A (DB70,71) в ReadКА
   void LKRead(cpu::data::GR12 &data ); // масив коэффициентов

   // устанока коэффициентов для калибровки
   void LKSetting(cpu::data::GR12 &data); // масив коэффициентов

   void Clear(); // очистить таблицу
   void PrintProtocol(std::string const& fn);


   int Index; // текущий индекс таблицы
   float TargetLd[ITEMS_COUNT]; // столбец заданных нагрузок
   std::string sTLd[ITEMS_COUNT]; // текстовое педставление заданных нагрузок
   float ReadoutLd[ITEMS_COUNT]; // столбец считанных нагрузок
   float MeasuredLd[ITEMS_COUNT]; // столбец измеренных нагрузок
   float KA[ITEMS_COUNT]; // столбец коэффициентов
   float ReadKA[ITEMS_COUNT]; // столбец коэффициентов, считанных из контроллера
   bool loaded; // флаг индикатор события загрузки из контроллера

private:
   std::string mPos;

};

}
#endif // LCALIBR_H
