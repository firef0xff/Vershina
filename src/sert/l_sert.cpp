#include "l_sert.h"
#include <cstring>
#include <cstdio>
#include "src/def.h"
#include "../support_functions/str_convert.h"
#include "../support_functions/date_time.h"
#include "../log/log.h"
namespace sert
{
LSert::LSert(const std::string &pos):
   Index(0),
   mPos(pos)
{
   TargetLd[0] = 0.5;
   for ( int i = 1; i <= ((ITEMS_COUNT-1)/2); ++i )
   {
      TargetLd[i] = TargetLd[i-1] + 1.65;
   }
   TargetLd[(ITEMS_COUNT-1)/2] = TargetLd[(ITEMS_COUNT-1)/2-1] + 1.35;

   for (int i = 13, j = 2; i < ITEMS_COUNT; i++)
   { // столбец заданных нагрузок
      TargetLd[i] = TargetLd[13 - (j++)];
   }


   for (int i = 0; i < ITEMS_COUNT; i++)
   {
      if (i == 0 || i == ITEMS_COUNT - 1)
         sTLd[i] = "   " + FloatToStringF( TargetLd[i], 5, 2 );
      else
         sTLd[i] = FloatToStringF( TargetLd[i], 5, 2 );
   }
   Clear();
}

void LSert::Clear() // очистить таблицу
{
   Index = 0;
   memset( ReadoutLd, 0, sizeof(ReadoutLd) );
   memset( MeasuredLd, 0, sizeof(MeasuredLd) );
   memset( RelError, 0, sizeof(RelError) );
}

void LSert::PrintProtocol(std::string const& fn)
{
   FILE *fprint = fopen(fn.c_str(), "wt");
   if (fprint == nullptr)
   {
      logger::LogPrint( "Can't open file \"" + fn + "\" for printing!", logger::lcRED );
      return;
   }
   fprintf(fprint, "%s  Стенд %s ПОЗ. %s\n\n", dt::ToString( dt::Now() ).c_str(), STAND_NO, mPos.c_str());
   fprintf(fprint, "%s","Определение относительной погрешности задания и \n");
   fprintf(fprint, "%s","и поддержания силы прижатия шины к барабану\n\n");
   fprintf(fprint, "%s","+----+---------+-----------+----------+-------------+\n");
   fprintf(fprint, "%s","| №  |заданное | нагрузка, | значение |относительная|\n");
   fprintf(fprint, "%s","|    |значение |измеренная | нагрузки,|погрешность  |\n");
   fprintf(fprint, "%s","|    |нагрузки,|динамомет- |показанное|задания силы |\n");
   fprintf(fprint, "%s","|    |   кН    |ром, кН    |на монито-|     %       |\n");
   fprintf(fprint, "%s","|    |         |           |ре стенда,|             |\n");
   fprintf(fprint, "%s","|    |         |           |    кН    |             |\n");
   fprintf(fprint, "%s","+----+---------+-----------+----------+-------------+\n");

   for (int i = 0; i < ITEMS_COUNT; i++)
   {
      fprintf(fprint, "| %2d |  %6.2f |   %6.2f  |  %6.2f  |   %7.2f   |\n",
         i + 1, TargetLd[i], MeasuredLd[i], ReadoutLd[i], RelError[i]);
   }
   fprintf(fprint, "%s","+----+---------+-----------+----------+-------------+\n");
   fclose(fprint);
}

}
