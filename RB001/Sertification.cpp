//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "def.h"
#include "Sertification.h"
#include "RBCommon.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
__fastcall VSert::VSert(void)                  // конструктор
{
  Index=0;                            // текущий индекс таблицы
  for (int i=0,j=16;i<VQTY;i++) {     // столбец заданных скоростей
    if(i<17) {
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
  Index=0;
  for (int i=0;i<VQTY;i++) {
    ReadoutV[i]=MeasuredV[i]=RelError[i]=0.0;
  }
}
//---- End of Clear ---------------------------------------------------------

void __fastcall VSert::PrintProtocol(String fn)// распечатать протокол в файл fn
{ FILE *fprint;
  if((fprint=fopen(AnsiString(fn).c_str(),"wt"))==NULL){
    LogPrint("Can't open file \""+fn+"\" for printing!",clRed);
    return;
  }
  fprintf(fprint,"%s                                    Стенд 13\n\n",AnsiString(Now().DateTimeString()).c_str());
  fprintf(fprint,"Определение относительной погрешности задания и \n");
  fprintf(fprint,"поддержания линейной скорости барабана \n\n");
  fprintf(fprint,"+----+---------+-----------+----------+-------------+\n");
  fprintf(fprint,"| №  |заданное | скорость, |скорость, |относительная|\n");
  fprintf(fprint,"|    |значение | измеренная|показанная| погрешность |\n");
  fprintf(fprint,"|    |скорости | тахометром|на монито-| задания ско-|\n");
  fprintf(fprint,"|    |  км/час |  км/час   |ре, км/час| рости, %    |\n");
  fprintf(fprint,"+----+---------+-----------+----------+-------------+\n");

  for (int i = 0; i < VQTY; i++) {
    fprintf(fprint,"| %2d |  %6.2f |   %6.2f  |  %6.2f  |   %7.2f   |\n",
    i+1,TargetV[i],MeasuredV[i],ReadoutV[i],RelError[i]);
  }
  fprintf(fprint,"+----+---------+-----------+----------+-------------+\n");
  fclose(fprint);
}
//---- End of PrintProtocol -------------------------------------------------

__fastcall LSert::LSert(void)                  // конструктор
{
  Index=0;                            // текущий индекс таблицы
  for (int i=0,j=11;i<LDQTY;i++) {       // столбец заданных скоростей
    if(i<12) {
      TargetLd[i]=(i)*10;
    }
    else if(i==12) TargetLd[i]=115;
    else {
      TargetLd[i]=(j--)*10;
    }
  }
  TargetLd[0]=TargetLd[LDQTY-1]=5;
  for (int i=0;i<LDQTY;i++) {       // столбец заданных скоростей
    if(i==0 || i==LDQTY-1)
	  sTLd[i]="   "+FloatToStrF(TargetLd[i],ffFixed,5,2);
    else
	  sTLd[i]="  "+FloatToStrF(TargetLd[i],ffFixed,5,2);
    ReadoutLd[i]=MeasuredLd[i]=RelError[i]=0.0;
  }
}
//---- End of Constructor LSert ---------------------------------------------

void __fastcall LSert::Clear(void)    // очистить таблицу
{
  Index=0;
  for (int i=0;i<LDQTY;i++) {
    ReadoutLd[i]=MeasuredLd[i]=RelError[i]=0.0;
  }
}
//---- End of Clear ---------------------------------------------------------

void __fastcall LSert::PrintProtocol(// распечатать протокол в файл fn
                                     String fn,
                                     String posname)
{ FILE *fprint;
  if((fprint=fopen(AnsiString(fn).c_str(),"wt"))==NULL){
    LogPrint("Can't open file \""+fn+"\" for printing!",clRed);
    return;
  }
  fprintf(fprint,"%s  Стенд 13 ПОЗ. %s\n\n",AnsiString(Now().DateTimeString()).c_str(),AnsiString(posname).c_str());
  fprintf(fprint,"Определение относительной погрешности задания и \n");
  fprintf(fprint,"и поддержания силы прижатия шины к барабану\n\n");
  fprintf(fprint,"+----+---------+-----------+----------+-------------+\n");
  fprintf(fprint,"| №  |заданное | нагрузка, | значение |относительная|\n");
  fprintf(fprint,"|    |значение |измеренная | нагрузки,|погрешность  |\n");
  fprintf(fprint,"|    |нагрузки,|динамомет- |показанное|задания силы |\n");
  fprintf(fprint,"|    |   кН    |ром, кН    |на монито-|     %       |\n");
  fprintf(fprint,"|    |         |           |ре стенда,|             |\n");
  fprintf(fprint,"|    |         |           |    кН    |             |\n");
  fprintf(fprint,"+----+---------+-----------+----------+-------------+\n");

  for (int i = 0; i < LDQTY; i++) {
    fprintf(fprint,"| %2d |  %6.2f |   %6.2f  |  %6.2f  |   %7.2f   |\n",
	i+1,TargetLd[i],MeasuredLd[i],ReadoutLd[i],RelError[i]);
  }
  fprintf(fprint,"+----+---------+-----------+----------+-------------+\n");
  fclose(fprint);
}
//---- End of PrintProtocol -------------------------------------------------

__fastcall TSert::TSert(void)                  // конструктор
{
  Index=0;                            // текущий индекс таблицы
  for (int i=0;i<TQTY;i++) {          // столбец заданных скоростей
    ReadoutT[i]=MeasuredT[i]=RelError[i]=0.0;
  }
}
//---- End of Constructor TSert ---------------------------------------------

void __fastcall TSert::Clear(void)    // очистить таблицу
{
  Index=0;
  for (int i=0;i<TQTY;i++) {
    ReadoutT[i]=MeasuredT[i]=RelError[i]=0.0;
  }
}
//---- End of Clear ---------------------------------------------------------

void __fastcall TSert::PrintProtocol(// распечатать протокол в файл fn
                                     String fn,
                                     String posname)
{ FILE *fprint;
  if((fprint=fopen(AnsiString(fn).c_str(),"wt"))==NULL){
    LogPrint("Can't open file \""+fn+"\" for printing!",clRed);
    return;
  }
  fprintf(fprint,"%s  Стенд 13 ПОЗ. %s\n\n",AnsiString(Now().DateTimeString()).c_str(),AnsiString(posname).c_str());
  fprintf(fprint,"Определение абсолютной погрешности измерения\n");
  fprintf(fprint,"температуры окружающего воздуха\n\n");
  fprintf(fprint,"+----+------------+-----------+-----------+\n");
  fprintf(fprint,"| №  |температура,| показания |абсолютная |\n");
  fprintf(fprint,"|    |измеренная  |на мониторе|погрешность|\n");
  fprintf(fprint,"|    |термометром |     С     |    С      |\n");
  fprintf(fprint,"+----+------------+-----------+-----------+\n");

  for (int i = 0; i < TQTY; i++) {
    if(ReadoutT[i]==0.0)break;
    fprintf(fprint,"| %2d |   %6.2f   |   %6.2f  |  %7.2f  |\n",
    i+1,ReadoutT[i],MeasuredT[i],RelError[i]);
  }
  fprintf(fprint,"+----+------------+-----------+-----------+\n");
  fclose(fprint);
}
//---- End of PrintProtocol -------------------------------------------------

__fastcall RSert::RSert(void)                  // конструктор
{
  Index=0;                            // текущий индекс таблицы
  for (int i=0;i<TQTY;i++) {          // столбец заданных скоростей
    ReadoutR[i]=MeasuredR[i]=RelError[i]=0.0;
  }
}
//---- End of Constructor RSert ---------------------------------------------

void __fastcall RSert::Clear(void)    // очистить таблицу
{
  Index=0;
  for (int i=0;i<TQTY;i++) {
    ReadoutR[i]=MeasuredR[i]=RelError[i]=0.0;
  }
}
//---- End of Clear ---------------------------------------------------------

void __fastcall RSert::PrintProtocol(// распечатать протокол в файл fn
                                     String fn,
                                     String posname)
{ FILE *fprint;
  if((fprint=fopen(AnsiString(fn).c_str(),"wt"))==NULL){
    LogPrint("Can't open file \""+fn+"\" for printing!",clRed);
    return;
  }
  fprintf(fprint,"%s  Стенд 13 ПОЗ. %s\n\n",AnsiString(Now().DateTimeString()).c_str(),AnsiString(posname).c_str());
  fprintf(fprint,"Определение абсолютной погрешности измерения\n");
  fprintf(fprint,"динамического радиуса\n\n");
  fprintf(fprint,"+----+-------------+-------------+-----------+\n");
  fprintf(fprint,"| №  |   значение  |   значение  |абсолютная |\n");
  fprintf(fprint,"|    |динамического|динамического|погрешность|\n");
  fprintf(fprint,"|    |  радиуса на |радиуса, из- |     мм    |\n");
  fprintf(fprint,"|    |   мониторе  |меренное нут-|           |\n");
  fprintf(fprint,"|    |  стенда, мм |ромером, мм  |           |\n");
  fprintf(fprint,"+----+-------------+-------------+-----------+\n");

  for (int i = 0; i < TQTY; i++) {
    fprintf(fprint,"| %2d |   %6.2f    |    %6.2f   |  %7.2f  |\n",
    i+1,ReadoutR[i],MeasuredR[i],RelError[i]);
  }
  fprintf(fprint,"+----+-------------+-------------+-----------+\n");
  fclose(fprint);
}
//---- End of PrintProtocol -------------------------------------------------

__fastcall LCalibr::LCalibr(void)                  // конструктор
{
  loaded=false;
  Index=0;                            // текущий индекс таблицы
  TargetLd[0]=5;
  TargetLd[1]=6;
  TargetLd[2]=7;
  TargetLd[3]=8;
  TargetLd[4]=9;
  TargetLd[5]=10;
  TargetLd[6]=11;
  TargetLd[7]=12;
  TargetLd[8]=13;
  TargetLd[9]=15;
  TargetLd[10]=20;
  TargetLd[11]=30;
  TargetLd[12]=40;
  TargetLd[13]=50;
  TargetLd[14]=60;
  TargetLd[15]=70;
  TargetLd[16]=80;
  TargetLd[17]=90;
  TargetLd[18]=100;
  TargetLd[19]=110;
  for (int i=20,j=2;i<LDCQTY;i++) {    // столбец заданных нагрузок
    TargetLd[i]=TargetLd[20-(j++)];
  }
  for (int i=0;i<LDCQTY;i++) {    // столбец заданных нагрузок
    sTLd[i]="   "+FloatToStrF(TargetLd[i],ffFixed,5,2);
    ReadoutLd[i]=MeasuredLd[i]=ReadKA[i]=0.0;
    KA[i]=1.0;
  }
}
//---- End of Constructor LCalibr -------------------------------------------

void __fastcall LCalibr::LKQInit(                 // инициализация коэффициентов и граничных нагрузок для калибровки
                                 float *Q[],      // масив указателей границ
                                 float *A[])      // масив указателей коэффициентов
{
  for(int i=0; i<GR12ARRAYSIZE/2; i++) {
    *A[i]=*A[i+GR12ARRAYSIZE/2]=1.0;
    *Q[i]=TargetLd[i];
    *Q[GR12ARRAYSIZE-i-1]=TargetLd[LDCQTY-i-1];
  }
}
//---- End of LKQInit -------------------------------------------------------

void __fastcall LCalibr::LKRead(                  // чтение коэффициентов из A (DB70,71) в ReadКА
                                float *A[])       // масив указателей коэффициентов
{
  for(int i=0; i<GR12ARRAYSIZE/2; i++) {
	/*Read*/KA[i]=*A[i];
    /*Read*/KA[i+GR12ARRAYSIZE/2-1]=*A[i+GR12ARRAYSIZE/2];
  }
  loaded=true;
}
//---- End of LKRead --------------------------------------------------------

void __fastcall LCalibr::LKMult(void)             // перемножение КА и ReadKA
{
  for (int i=0;i<LDCQTY;i++) {
    KA[i]*=ReadKA[i];
  }
}
//---- End of LKMult --------------------------------------------------------

void __fastcall LCalibr::LKSetting(               // устанока коэффициентов для калибровки
                                   float *A[])    // масив указателей коэффициентов
{
  for(int i=0; i<GR12ARRAYSIZE/2; i++) {
    *A[i]=KA[i];
    *A[GR12ARRAYSIZE-i-1]=KA[LDCQTY-i-1];
  }
}
//---- End of LKSetting -----------------------------------------------------

void __fastcall LCalibr::Clear(void)    // очистить таблицу
{
  Index=0;
  for (int i=0;i<LDCQTY;i++) {
    ReadoutLd[i]=MeasuredLd[i]=ReadKA[i]=0.0;
    KA[i]=1.0;
  }
  loaded=false;
}
//---- End of Clear ---------------------------------------------------------

void __fastcall LCalibr::PrintProtocol(// распечатать протокол в файл fn
                                       String fn,
                                       String posname)
{ FILE *fprint;
  if((fprint=fopen(AnsiString(fn).c_str(),"wt"))==NULL){
    LogPrint("Can't open file \""+fn+"\" for printing!",clRed);
    return;
  }
  fprintf(fprint,"%s  Стенд 13 ПОЗ. %s\n\n",AnsiString(Now().DateTimeString()).c_str(),AnsiString(posname).c_str());
  fprintf(fprint,"          ПРОТОКОЛ КАЛИБРОВКИ ТЕНЗОДАТЧИКА\n\n");
  fprintf(fprint,"+----+---------+-----------+----------+-------------+\n");
  fprintf(fprint,"| №  | задание | измерение | контроль | коэффициент |\n");
  fprintf(fprint,"|    |   кН    |    кН     |    кН    |     %       |\n");
  fprintf(fprint,"+----+---------+-----------+----------+-------------+\n");

  for (int i = 0; i < LDCQTY; i++) {
    fprintf(fprint,"| %2d |  %6.2f |   %6.2f  |  %6.2f  |  %9.6f  |\n",
    i+1,TargetLd[i],ReadoutLd[i],MeasuredLd[i],KA[i]);
  }
  fprintf(fprint,"+----+---------+-----------+----------+-------------+\n");
  fclose(fprint);
}
//---- End of PrintProtocol -------------------------------------------------

