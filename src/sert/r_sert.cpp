#include "r_sert.h"
#include <cstring>
#include <cstdio>
#include "src/def.h"
#include "../support_functions/date_time.h"
#include "../log/log.h"

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
      logger::LogPrint( "Can't open file \"" + fn + "\" for printing!", logger::lcRED );
      return;
   }
   fprintf(fprint, "%s  Стенд %s ПОЗ. %s\n\n",dt::ToString( dt::Now() ).c_str(), STAND_NO, mPos.c_str());
   fprintf(fprint, "%s","Определение абсолютной погрешности измерения\n");
   fprintf(fprint, "%s","динамического радиуса\n\n");
   fprintf(fprint, "%s","+----+-------------+-------------+-------------+\n");
   fprintf(fprint, "%s","| №  |   значение  |   значение  |относительная|\n");
   fprintf(fprint, "%s","|    |динамического|динамического|погрешность  |\n");
   fprintf(fprint, "%s","|    |  радиуса на |радиуса, из- |     %       |\n");
   fprintf(fprint, "%s","|    |   мониторе  |меренное нут-|             |\n");
   fprintf(fprint, "%s","|    |  стенда, мм |ромером, мм  |             |\n");
   fprintf(fprint, "%s","+----+-------------+-------------+-------------+\n");

   for (int i = 0; i < ITEMS_COUNT; i++)
   {
      fprintf(fprint, "| %2d |   %6.2f    |    %6.2f   |   %7.2f   |\n", i + 1,
         ReadoutR[i], MeasuredR[i], RelError[i]);
   }
   fprintf(fprint, "%s","+----+-------------+-------------+-------------+\n");
   fclose(fprint);
}

}
