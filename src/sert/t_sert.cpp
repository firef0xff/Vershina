#include "t_sert.h"
#include <cstring>
#include <cstdio>
#include "src/Common.h"
#include "src/def.h"

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
      LogPrint("Can't open file \"" + AnsiString(fn.c_str()) + "\" for printing!", clRed);
      return;
   }
   fprintf(fprint, "%s  Стенд %d ПОЗ. %s\n\n",
      AnsiString(Now().DateTimeString()).c_str(), STAND_NO ,mPos.c_str());
   fprintf(fprint, "Определение абсолютной погрешности измерения\n");
   fprintf(fprint, "температуры окружающего воздуха\n\n");
   fprintf(fprint, "+----+------------+-----------+-----------+\n");
   fprintf(fprint, "| №  |температура,| показания |абсолютная |\n");
   fprintf(fprint, "|    |измеренная  |на мониторе|погрешность|\n");
   fprintf(fprint, "|    |термометром |     С     |    С      |\n");
   fprintf(fprint, "+----+------------+-----------+-----------+\n");

   for (int i = 0; i < ITEMS_COUNT; i++)
   {
      if (ReadoutT[i] == 0.0)
         break;
      fprintf(fprint, "| %2d |   %6.2f   |   %6.2f  |  %7.2f  |\n", i + 1,
         ReadoutT[i], MeasuredT[i], RelError[i]);
   }
   fprintf(fprint, "+----+------------+-----------+-----------+\n");
   fclose(fprint);
}
}
