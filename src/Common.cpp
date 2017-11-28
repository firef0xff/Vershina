// ---------------------------------------------------------------------------
#include <stdio.h>
#include <process.h>
#include <DateUtils.hpp>
#include <StrUtils.hpp>
#pragma hdrstop
#include "def.h"
#include "Common.h"
#include "log/log_impl.h"
#include <System.SysUtils.hpp>
#include "support_functions/functions.h"
// ---------------------------------------------------------------------------

#pragma package(smart_init)

char MakeSeparator()
{
   TFormatSettings s = TFormatSettings::Create();
   return s.DecimalSeparator;
}
char DecimalSeparator = MakeSeparator();

float  StrToFlt(String ws)
   // Преобразование строки в значение типа float
{
   String s;
   s = Trim(ws);
   if (s == "")
      return 0.0;

   if (DecimalSeparator == '.')
   {
      s = Replace(s, ",", String(DecimalSeparator));
   }
   else
   {
      s = Replace(s, ".", String(DecimalSeparator));
   }
   return StrToFloat(s);
}
// ---- End of StrToFlt ------------------------------------------------------

int  StrToI(String ws) // ПРеобразование строки в значение типа int
{
   String s;
   s = Trim(ws);
   if (s == "")
      return 0;
   else
      return StrToInt(s);
}
// ---- End of StrToI --------------------------------------------------------

String  FileNameParse
   ( // Функция выделения имени файла из полного пути
   String SFN) // Полное имя файла
{
   String wfname = SFN;
   if (wfname.Length() > 0)
   {
      int slPos = wfname.Pos("\\");
      while (slPos)
      {
         wfname = wfname.SubString(slPos + 1, 1000);
         slPos = wfname.Pos("\\");
      }
   }
   return wfname;
}
// ---- End of FileNameParse -------------------------------------------------

// ---- End of NextCycleCount ------------------------------------------------

void  LeastSquares
   ( // расчет коэффициентов A и B методом наименьших квадратов
   float X[], // массив X
   float Y[], // массив Y
   int N, // количество элементов в массивах
   float &A, // коэффициент A
   float &B) // коэффициент B
{
   int i;
   double SXi, SYi, SXiYi, SXi2, Ndbl;
   SXi = 0;
   SYi = 0;
   SXiYi = 0;
   SXi2 = 0;
   Ndbl = N;
   for (i = 0; i < N; i++)
   {
      SXi += X[i];
      SYi += Y[i];
      SXiYi += X[i] * Y[i];
      SXi2 += X[i] * X[i];
   }
   A = (Ndbl * SXiYi - SXi * SYi) / (Ndbl * SXi2 - SXi * SXi);
   B = (SYi - A * SXi) / Ndbl;
}
// ---- End of LeastSquares --------------------------------------------------


int  BUnion(bool b1, bool b2)
   // объединение занчений аргументов в целое значение
{
   return (int(b1) << 1)+int(b2);
}
// ---- End of BUnion --------------------------------------------------------

String  FltToStr( // Преобразование числа в строку длиной l
   float f, // преобразуемое число
   TFloatFormat ff, // формат
   int l, // длина строки
   int r) // длина дробной части
{
   String ws;
   ws = FloatToStrF(f, ff, l, r);
   int wl = ws.Length();
   if (wl < l)
   {
      ws = String(DupeString(' ', l - wl)) + ws;
   }
   return ws;
}
// ---- End of FltToStr -----------------------------------------------------
