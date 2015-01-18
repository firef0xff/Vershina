//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "SpeedSertification.h"
#include "RBCommon.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
__fastcall VSert::VSert(void)                  // конструктор
{
  Index=0;                            // текущий индекс таблицы
  for (int i=0,j=14;i<29;i++) {       // столбец заданных скоростей
    if(i<15) {
      TargetV[i]=(i+1)*10;
    }
    else {
      TargetV[i]=(j--)*10;
    }
    if(TargetV[i]<100.0)
      sTV[i]="      "+FloatToStrF(TargetV[i],ffFixed,5,2);
    else
      sTV[i]="    "+FloatToStrF(TargetV[i],ffFixed,6,2);
    ReadoutV[i]=MeasuredV[i]=RelError[i]=0.0;
  }
}
//---- End of Constructor VSert ---------------------------------------------

void __fastcall VSert::Clear(void)    // очистить таблицу
{
  for (int i=0;i<29;i++) {
    ReadoutV[i]=MeasuredV[i]=RelError[i]=0.0;
  }
}
//---- End of Clear ---------------------------------------------------------

void __fastcall VSert::PrintProtocol(String fn)// распечатать протокол в файл fn
{ FILE *fprint;
  if((fprint=fopen(fn.c_str(),"wt"))==NULL){
    LogPrint("Can't open file \""+fn+"\" for printing!",clRed);
    return;
  }
  fprintf(fprint,"%s\n\n",Now().DateTimeString().c_str());
  fprintf(fprint,"                ПРОТОКОЛ АТТЕСТАЦИИ БАРАБАНА\n\n");
  fprintf(fprint,"+----+---------+-----------+----------+-------------+\n");
  fprintf(fprint,"| №  | задание | измерение | контроль | погрешность |\n");
  fprintf(fprint,"|    |  км/час |  км/час   |  км/час  |     %       |\n");
  fprintf(fprint,"+----+---------+-----------+----------+-------------+\n");

  for (int i = 0; i < 29; i++) {
    fprintf(fprint,"| %2d |  %6.2f |   %6.2f  |  %6.2f  |   %7.2f   |\n",
    i+1,TargetV[i],ReadoutV[i],MeasuredV[i],RelError[i]);
  }
  fprintf(fprint,"+----+---------+-----------+----------+-------------+\n");
  fclose(fprint);
}
//---- End of PrintProtocol -------------------------------------------------
//│┤╡╢╖╕╣║╗╝╜╛┐└└┴┬├─┼╞╟╚╔╩╦╠═╬╧╨╤╥╙╘╒╓╫╪┘┌
