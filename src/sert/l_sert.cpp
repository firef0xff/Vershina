#include "l_sert.h"
#include <cstring>
#include <cstdio>
#include "src/Common.h"
#include "src/def.h"

namespace sert
{
LSert::LSert(const std::string &pos):
   Index(0),
   mPos(pos)
{
   for ( int i = 0, j = ITEMS_COUNT/2-1; i < ITEMS_COUNT; i++)
   {
      if (i < ITEMS_COUNT/2)
      {
         TargetLd[i] = i * 10;
      }
      else if (i == ITEMS_COUNT/2)
         TargetLd[i] = 115;
      else
      {
         TargetLd[i] = (j--) * 10;
      }
   }
   TargetLd[0] = TargetLd[ITEMS_COUNT - 1] = 5;

   for (int i = 0; i < ITEMS_COUNT; i++)
   {
      if (i == 0 || i == ITEMS_COUNT - 1)
         sTLd[i] = std::string( AnsiString( "   " + FloatToStrF(TargetLd[i], ffFixed, 5, 2) ).c_str() );
      else
         sTLd[i] = std::string( AnsiString("  " + FloatToStrF(TargetLd[i], ffFixed, 5, 2) ).c_str() );
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
      LogPrint("Can't open file \"" + AnsiString(fn.c_str()) + "\" for printing!", clRed);
      return;
   }
   fprintf(fprint, "%s  Стенд %d ПОЗ. %s\n\n",
      AnsiString(Now().DateTimeString()).c_str(), STAND_NO, mPos.c_str());
   fprintf(fprint, "Определение относительной погрешности задания и \n");
   fprintf(fprint, "и поддержания силы прижатия шины к барабану\n\n");
   fprintf(fprint, "+----+---------+-----------+----------+-------------+\n");
   fprintf(fprint, "| №  |заданное | нагрузка, | значение |относительная|\n");
   fprintf(fprint, "|    |значение |измеренная | нагрузки,|погрешность  |\n");
   fprintf(fprint, "|    |нагрузки,|динамомет- |показанное|задания силы |\n");
   fprintf(fprint, "|    |   кН    |ром, кН    |на монито-|     %       |\n");
   fprintf(fprint, "|    |         |           |ре стенда,|             |\n");
   fprintf(fprint, "|    |         |           |    кН    |             |\n");
   fprintf(fprint, "+----+---------+-----------+----------+-------------+\n");

   for (int i = 0; i < ITEMS_COUNT; i++)
   {
      fprintf(fprint, "| %2d |  %6.2f |   %6.2f  |  %6.2f  |   %7.2f   |\n",
         i + 1, TargetLd[i], MeasuredLd[i], ReadoutLd[i], RelError[i]);
   }
   fprintf(fprint, "+----+---------+-----------+----------+-------------+\n");
   fclose(fprint);
}

}
