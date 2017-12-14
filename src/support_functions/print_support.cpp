#include "print_support.h"
#include "../sert/TyreProt.h"
#include "str_convert.h"
#include "date_time.h"
#include "../log/log.h"

namespace printing
{
void Print(TPrinter *pprt, Tyre const& data) // печать протокола на принтер pprt
{
   std::string wstr[60] = {""};
   int left[60];
   float pWidthM = 210, pHeightM = 297; // ширина и высота страницы в мм
   float LeftMargM = 15, RightMargM = 15; // поля слева и справа в мм
   float UpperMargM = 15, LowMargM = 15; // поля сверху и снизу в мм
   int pWidth = pprt->PageWidth; // ширина страницы в пикселях
   int pHeight = pprt->PageHeight; // высота страницы в пикселях
   int fHeight = pprt->Canvas->TextHeight("A"); // высота строки в пикселях
   int LeftMarg = LeftMargM / pWidthM * pWidth;
   int RightMarg = RightMargM / pWidthM * pWidth + 850; // поля слева и справа в пикселях
   int UpperMarg = UpperMargM / pHeightM * pHeight;
   int LowMarg = LowMargM / pHeightM * pHeight; // поля сверху и снизу в пикселях
   int prtWidth = pWidth - LeftMarg - RightMarg;
   // ширина печатаемой области в пикселях
   int prtHeight = pHeight - UpperMarg - LowMarg;
   // высота печатаемой области в пикселях
   int LinesPP = 50; // количество строк на странице
   int LSp = (prtHeight - fHeight) / (LinesPP - 1);
   // расстояние между строками в пикселях
   int lineX = LeftMarg;
   int lineY = UpperMarg + fHeight;
   int LineCnt = 0;

   wstr[LineCnt] = "ПРОТОКОЛ ИСПЫТАНИЙ № ______" /* std::string(ProtNo)+ */ " НА СТЕНДЕ " + data.StandName + data.mSide;
   left[LineCnt] = abs(prtWidth - pprt->Canvas->TextWidth(AnsiString(wstr[LineCnt].c_str()))) / 2 + LeftMarg;
   wstr[++LineCnt] = "     Изготовитель: " + data.Manufacturer + "     Заказчик: " + data.TestCustomer + "  Заказ №: " + std::to_string(data.OrderNo);
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = "           Размер: " + data.Size         + "       Модель: " + data.Model + "  Маркировка: ______";
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = "Дата изготовления: " + dt::ToString(data.ManufactDate, dt::DEFAULT_DATE_FORMAT) +"     Порядковый №: " + std::to_string(data.SerialNo) + "    Форма №: " + data.FormNo;
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = "Диаметр барабана, мм: " + FloatToStringF( data.DrumDiameter, 6,2 ) +"   Методика: " + data.TestProcedure;
   left[LineCnt] = LeftMarg;
   if (data.Type == 0)
      wstr[++LineCnt] = "ХАРАКТЕРИСТИКИ ИСПЫТАННОЙ ШИНЫ" /* РАДИАЛЬНОЙ ШИНЫ" */ ;
   else
      wstr[++LineCnt] = "ХАРАКТЕРИСТИКИ ИСПЫТАННОЙ ШИНЫ" /* ДИАГОНАЛЬНОЙ ШИНЫ" */ ;
   left[LineCnt] = abs(prtWidth - pprt->Canvas->TextWidth(AnsiString(wstr[LineCnt].c_str()))) / 2 + LeftMarg;
   wstr[++LineCnt] = "   Индекс нагрузки: " + data.LoadIndex + "        Наружный диаметр, мм: " + FloatToStringF(data.OuterD, 6,2);
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = "Категория скорости: " + data.SpeedInd +  + "          Ширина профиля, мм: " + std::to_string( data.ProfileWide);
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = " Давление, кПа: " + FloatToStringF(data.InitPressure, 6, 2) + "               Обод: " + data.WheelRim;
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = "РЕЗУЛЬТАТЫ ИСПЫТАНИЙ:";
   left[LineCnt] = abs(prtWidth - pprt->Canvas->TextWidth(AnsiString(wstr[LineCnt].c_str()))) / 2 + LeftMarg;
   if (data.TestMode == 0)
      wstr[++LineCnt] = "    Режим обкатки: по времени";
   else
      wstr[++LineCnt] = "    Режим обкатки: по пути";
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = "        Общее время испытаний: " + dt::mSecToHMSStr(data.TotalTime);
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = "        Общий путь: " + FloatToStringF(data.TotalS, 7,0) + "км";
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = "        Дата начала испытания: " + dt::ToString(data.Start);
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = "        Дата окончания испытания: " + dt::ToString(data.Stop);
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] ="+-----+---------+--------+--------+--------+--------+-----------+";
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = "|Опрос|  время  |скорость|путь, км|нагрузка| радиус |Температура|";
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = "|     | чч:мм   | км/час |        |  кН    |   мм   |    С      |";
   left[LineCnt] = LeftMarg;
   wstr[++LineCnt] = "+-----+---------+--------+--------+--------+--------+-----------+";
   left[LineCnt] = LeftMarg;
   int LinePrinted = -1;

   for (int i = 0; i < data.PollsNo; i++)
   {
      if (data.rT[i] != 0 && data.rV[i] != 0 && data.rS[i] != 0 && data.rL[i] != 0 && data.rR[i] != 0 && data.rTemp[i] != 0)
      { // это не даст печататься пустым строкам данных (пожелание заказчика)
         wstr[++LineCnt] = "| " + IntToS(i + 1, 3) + " | " + dt::mSecToHMSStr(data.rT[i]) +
               "   | " + FloatToStringF(data.rV[i], 6, 2) + " | " + FloatToStringF(data.rS[i],6, 0) +
               " | " + FloatToStringF(data.rL[i], 6, 2) + " | " + FloatToStringF(data.rR[i], 5, 2) +
               " |    " + FloatToStringF(data.rTemp[i], 5, 1) + "  |";
         left[LineCnt] = LeftMarg;
      }

      if (LineCnt == LinesPP - 1)
      {
         LinePrinted = i;
         break;
      }
   }
   wstr[++LineCnt] = "+-----+---------+--------+--------+--------+--------+-----------+";
   left[LineCnt] = LeftMarg;
   pprt->BeginDoc();
   for (int i = 0; i <= LineCnt; i++, lineY += LSp)
   {
      pprt->Canvas->TextOutA(left[i], lineY, AnsiString(wstr[i].c_str()));
   }
   pprt->EndDoc();
   if (LinePrinted >= 0)
   {
      int NotPrintedLines = data.PollsNo - LinePrinted;
      logger::LogPrint("NotPrintedLines=" + std::to_string(NotPrintedLines));
      int PNum = NotPrintedLines / LinesPP;
      if (NotPrintedLines % LinesPP != 0)
      {
         PNum++;
      }
      logger::LogPrint("NumberOfPages=" + std::to_string(PNum));
      for (int PNo = 0; PNo < PNum; PNo++)
      {
         for (int i = 0; i < 60; i++)
         {
            wstr[i] = "";
            left[i] = 0;
         }
         LineCnt = -1;
         for (int i = LinePrinted; i < data.PollsNo; i++)
         {
            wstr[++LineCnt] = "| " + IntToS(i + 1, 3) + " | " + dt::mSecToHMSStr(data.rT[i]) +
                  "| " + FloatToStringF(data.rV[i], 6, 2) + " | " + FloatToStringF(data.rS[i], 6, 2) +
                  " | " + FloatToStringF(data.rL[i],6, 2) + " | " + FloatToStringF(data.rR[i], 5, 0) +
                  " |    " + FloatToStringF(data.rTemp[i], 5, 1) + "  |";
            left[LineCnt] = LeftMarg;
            if (LineCnt == LinesPP - 1)
            {
               LinePrinted += i;
               break;
            }
         }
         lineY = UpperMarg + fHeight;
         pprt->BeginDoc();
         for (int i = 0; i <= LineCnt; i++, lineY += LSp)
         {
            pprt->Canvas->TextOutA(left[i], lineY, AnsiString(wstr[i].c_str()));
         }
         pprt->EndDoc();
      }
   }
}


}
