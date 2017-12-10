#include "t_sert.h"
#include <cstring>
#include <cstdio>
#include "src/def.h"
#include "../support_functions/date_time.h"
#include "../log/log.h"

namespace sert
{
TSert::TSert(const std::string &pos):
   Index(0),
   mPos(pos)
{
   Clear();
}

void TSert::Clear(void) // очистить таблицу
{
   Index = 0;
   memset( ReadoutT, 0, sizeof(ReadoutT) );
   memset( MeasuredT, 0, sizeof(MeasuredT) );
   memset( RelError, 0, sizeof(RelError) );
}
void TSert::PrintProtocol(std::string const& fn)
{
   FILE *fprint = fopen(fn.c_str(), "wt");
   if( fprint == nullptr )
   {
      logger::LogPrint( "Can't open file \"" + fn + "\" for printing!", logger::lcRED );
      return;
   }
   fprintf(fprint, "%s  Стенд %s ПОЗ. %s\n\n", dt::ToString( dt::Now() ).c_str(), STAND_NO ,mPos.c_str());
   fprintf(fprint, "%s","Определение абсолютной погрешности измерения\n");
   fprintf(fprint, "%s","температуры окружающего воздуха\n\n");
   fprintf(fprint, "%s","+----+------------+-----------+-----------+\n");
   fprintf(fprint, "%s","| №  |температура,| показания |абсолютная |\n");
   fprintf(fprint, "%s","|    |измеренная  |на мониторе|погрешность|\n");
   fprintf(fprint, "%s","|    |термометром |     С     |    С      |\n");
   fprintf(fprint, "%s","+----+------------+-----------+-----------+\n");

   for (int i = 0; i < ITEMS_COUNT; i++)
   {
      if (ReadoutT[i] == 0.0)
         break;
      fprintf(fprint, "| %2d |   %6.2f   |   %6.2f  |  %7.2f  |\n", i + 1,
         ReadoutT[i], MeasuredT[i], RelError[i]);
   }
   fprintf(fprint, "%s","+----+------------+-----------+-----------+\n");
   fclose(fprint);
}
}
