#include "v_sert.h"
#include <cstring>
#include <cstdio>
#include "src/Common.h"
#include "src/def.h"
namespace sert
{

VSert::VSert():
   Index(0)
{
   for ( int i = 0, j = ITEMS_COUNT/2; i < ITEMS_COUNT; i++ ) // столбец заданных скоростей
   {
      //инициализация массива скоростей
      if ( i <= ITEMS_COUNT/2 )
         TargetV[i] = (i + 1) * 10;
      else
         TargetV[i] = (j--) * 10;

      //инициализация строковых представлений


      if (TargetV[i] < 100.0)
         sTV[i] = std::string( AnsiString( "      " + FloatToStrF(TargetV[i], ffFixed, 5, 2) ).c_str() );
      else
         sTV[i] = std::string( AnsiString( "    " + FloatToStrF(TargetV[i], ffFixed, 6, 2) ).c_str() );
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
      LogPrint("Can't open file \"" + AnsiString(fn.c_str()) + "\" for printing!", clRed);
      return;
   }

   fprintf(fprint, "%s                                    Стенд %d\n\n", AnsiString(Now().DateTimeString()).c_str(), STAND_NO );
   fprintf(fprint, "Определение относительной погрешности задания и \n");
   fprintf(fprint, "поддержания линейной скорости барабана \n\n");
   fprintf(fprint, "+----+---------+-----------+----------+-------------+\n");
   fprintf(fprint, "| №  |заданное | скорость, |скорость, |относительная|\n");
   fprintf(fprint, "|    |значение | измеренная|показанная| погрешность |\n");
   fprintf(fprint, "|    |скорости | тахометром|на монито-| задания ско-|\n");
   fprintf(fprint, "|    |  км/час |  км/час   |ре, км/час| рости, %    |\n");
   fprintf(fprint, "+----+---------+-----------+----------+-------------+\n");

   for (int i = 0; i < ITEMS_COUNT; i++)
   {
      fprintf(fprint, "| %2d |  %6.2f |   %6.2f  |  %6.2f  |   %7.2f   |\n",
                       i + 1, TargetV[i], MeasuredV[i], ReadoutV[i], RelError[i]);
   }
   fprintf(fprint, "+----+---------+-----------+----------+-------------+\n");
   fclose(fprint);
}

}
