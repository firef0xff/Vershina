﻿#include "l_calibr.h"
#include <cstring>
#include <cstdio>
#include "src/def.h"
#include "../support_functions/str_convert.h"
#include "../support_functions/date_time.h"
#include "../log/log.h"

namespace sert
{
LCalibr::LCalibr(const std::string &pos):
   Index(0),
   loaded(false),
   mPos(pos)
{
   TargetLd[0] = 5;
   TargetLd[1] = 6;
   TargetLd[2] = 7;
   TargetLd[3] = 8;
   TargetLd[4] = 9;
   TargetLd[5] = 10;
   TargetLd[6] = 11;
   TargetLd[7] = 12;
   TargetLd[8] = 13;
   TargetLd[9] = 15;
   TargetLd[10] = 20;
   TargetLd[11] = 30;
   TargetLd[12] = 40;
   TargetLd[13] = 50;
   TargetLd[14] = 60;
   TargetLd[15] = 70;
   TargetLd[16] = 80;
   TargetLd[17] = 90;
   TargetLd[18] = 100;
   TargetLd[19] = 110;
   for (int i = 20, j = 2; i < ITEMS_COUNT; i++)
   { // столбец заданных нагрузок
      TargetLd[i] = TargetLd[20 - (j++)];
   }
   for (int i = 0; i < ITEMS_COUNT; i++)
   { // столбец заданных нагрузок
      sTLd[i] = "   " + FloatToStringF( TargetLd[i], 5, 2 );
   }

   Clear();
}
void LCalibr::Clear()
{
   Index = 0;
   for (int i = 0; i < ITEMS_COUNT; i++)
   {
      ReadoutLd[i] = MeasuredLd[i] = ReadKA[i] = 0.0;
      KA[i] = 1.0;
   }
   loaded = false;
}


void LCalibr::LKQInit( cpu::data::GR12& data)
{
   for (int i = 0; i < cpu::data::GR12::ITEMS_COUNT / 2; i++)
   {
      data.A[i] = data.A[i + cpu::data::GR12::ITEMS_COUNT / 2] = 1.0;
      data.Q[i] = TargetLd[i];
      data.Q[cpu::data::GR12::ITEMS_COUNT - i - 1] = TargetLd[ITEMS_COUNT - i - 1];
   }
}

void LCalibr::LKRead( cpu::data::GR12& data )
{
   for (int i = 0; i < cpu::data::GR12::ITEMS_COUNT / 2; i++)
   {
      KA[i] = data.A[i];
      KA[i + cpu::data::GR12::ITEMS_COUNT / 2 - 1] = data.A[i + cpu::data::GR12::ITEMS_COUNT / 2];
   }
   loaded = true;
}

void LCalibr::LKSetting( cpu::data::GR12& data )
{
   for (int i = 0; i < cpu::data::GR12::ITEMS_COUNT / 2; i++)
   {
      data.A[i] = KA[i];
      data.A[cpu::data::GR12::ITEMS_COUNT - i - 1] = KA[ITEMS_COUNT - i - 1];
   }
}

void LCalibr::PrintProtocol(std::string const& fn )
{
   FILE *fprint = fopen(fn.c_str(), "wt");
   if (fprint  == nullptr)
   {
      logger::LogPrint( "Can't open file \"" + fn + "\" for printing!", logger::lcRED );
      return;
   }
   fprintf(fprint, "%s  Стенд %s ПОЗ. %s\n\n",dt::ToString( dt::Now() ).c_str(), STAND_NO, mPos.c_str());
   fprintf(fprint, "%s","          ПРОТОКОЛ КАЛИБРОВКИ ТЕНЗОДАТЧИКА\n\n");
   fprintf(fprint, "%s","+----+---------+-----------+----------+-------------+\n");
   fprintf(fprint, "%s","| №  | задание | измерение | контроль | коэффициент |\n");
   fprintf(fprint, "%s","|    |   кН    |    кН     |    кН    |     %       |\n");
   fprintf(fprint, "%s","+----+---------+-----------+----------+-------------+\n");

   for (int i = 0; i < ITEMS_COUNT; i++)
   {
      fprintf(fprint, "| %2d |  %6.2f |   %6.2f  |  %6.2f  |  %9.6f  |\n",
         i + 1, TargetLd[i], ReadoutLd[i], MeasuredLd[i], KA[i]);
   }
   fprintf(fprint, "%s","+----+---------+-----------+----------+-------------+\n");
   fclose(fprint);
}
}