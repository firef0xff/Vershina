#include "v_sert.h"
#include <cstring>
#include <cstdio>
#include "src/def.h"
#include "../support_functions/date_time.h"
#include "../support_functions/str_convert.h"
#include "../log/log.h"

namespace sert
{

VSert::VSert():
   Index(0)
{
   TargetV[0] = 10.0;
   for ( int i = 1; i <= ITEMS_COUNT-2; ++i )
   {
      TargetV[i] = TargetV[i-1] + 18.0;
   }
   TargetV[ITEMS_COUNT-1] = TargetV[ITEMS_COUNT-2] + 20.0;

//   for (int i = 17, j = 2; i < ITEMS_COUNT; i++)
//   { // столбец заданных нагрузок
//      TargetV[i] = 0;// TargetV[17 - (j++)];
//   }

   for ( int i = 0; i < ITEMS_COUNT; i++ ) // столбец заданных скоростей
   {
      if (TargetV[i] < 100.0)
         sTV[i] = "      " + FloatToStringF(TargetV[i], 5, 2);
      else
         sTV[i] = "    " + FloatToStringF(TargetV[i], 6, 2);
   }
   Clear();
}
void VSert::Clear()
{
   Index = 0;
   memset( ReadoutV, 0, sizeof(ReadoutV) );
   memset( MeasuredV, 0, sizeof(MeasuredV) );
   memset( RelError, 0, sizeof(RelError) );
}

void VSert::PrintProtocol( std::string const& fn)
{
   FILE *fprint = std::fopen(fn.c_str(), "wt");
   if (fprint == nullptr )
   {
      logger::LogPrint( "Can't open file \"" + fn + "\" for printing!", logger::lcRED );
      return;
   }

   fprintf(fprint, "%s                                    Стенд %s\n\n", dt::ToString( dt::Now() ).c_str(), STAND_NO );
   fprintf(fprint, "%s","Определение относительной погрешности задания и \n");
   fprintf(fprint, "%s","поддержания линейной скорости барабана \n\n");
   fprintf(fprint, "%s","+----+---------+-----------+----------+-------------+\n");
   fprintf(fprint, "%s","| №  |заданное | скорость, |скорость, |относительная|\n");
   fprintf(fprint, "%s","|    |значение | измеренная|показанная| погрешность |\n");
   fprintf(fprint, "%s","|    |скорости | тахометром|на монито-| задания ско-|\n");
   fprintf(fprint, "%s","|    |  км/час |  км/час   |ре, км/час| рости, %    |\n");
   fprintf(fprint, "%s","+----+---------+-----------+----------+-------------+\n");

   for (int i = 0; i < ITEMS_COUNT; i++)
   {
      fprintf(fprint, "| %2d |  %6.2f |   %6.2f  |  %6.2f  |   %7.2f   |\n",
                       i + 1, TargetV[i], MeasuredV[i], ReadoutV[i], RelError[i]);
   }
   fprintf(fprint, "%s","+----+---------+-----------+----------+-------------+\n");
   fclose(fprint);
}

}
