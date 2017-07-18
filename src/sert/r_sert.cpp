#include "r_sert.h"
#include <cstring>
#include <cstdio>
#include "src/Common.h"
#include "src/def.h"

namespace sert
{
RSert::RSert(const std::string &pos):
   Index(0),
   mPos(pos)
{
   Clear();
}

void RSert::Clear(void)
{
   Index = 0;
   memset( ReadoutR, 0, sizeof(ReadoutR) );
   memset( MeasuredR, 0, sizeof(MeasuredR) );
   memset( RelError, 0, sizeof(RelError) );
}

void RSert::PrintProtocol( std::string const& fn)
{
   FILE *fprint = fopen(fn.c_str(), "wt");
   if ( fprint == nullptr )
   {
      LogPrint("Can't open file \"" + AnsiString(fn.c_str()) + "\" for printing!", clRed);
      return;
   }
   fprintf(fprint, "%s  Стенд %13 ПОЗ. %s\n\n",
      AnsiString(Now().DateTimeString()).c_str(), STAND_NO, mPos.c_str());
   fprintf(fprint, "Определение абсолютной погрешности измерения\n");
   fprintf(fprint, "динамического радиуса\n\n");
   fprintf(fprint, "+----+-------------+-------------+-----------+\n");
   fprintf(fprint, "| №  |   значение  |   значение  |абсолютная |\n");
   fprintf(fprint, "|    |динамического|динамического|погрешность|\n");
   fprintf(fprint, "|    |  радиуса на |радиуса, из- |     мм    |\n");
   fprintf(fprint, "|    |   мониторе  |меренное нут-|           |\n");
   fprintf(fprint, "|    |  стенда, мм |ромером, мм  |           |\n");
   fprintf(fprint, "+----+-------------+-------------+-----------+\n");

   for (int i = 0; i < ITEMS_COUNT; i++)
   {
      fprintf(fprint, "| %2d |   %6.2f    |    %6.2f   |  %7.2f  |\n", i + 1,
         ReadoutR[i], MeasuredR[i], RelError[i]);
   }
   fprintf(fprint, "+----+-------------+-------------+-----------+\n");
   fclose(fprint);
}

}
