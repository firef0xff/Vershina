//---------------------------------------------------------------------------
#include <stdio.h>
#include <StrUtils.hpp>
#pragma hdrstop

#include "TyreProt.h"
#include "RBCommon.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
__fastcall Tyre::Tyre(void)       // конструктор
{
  ProtNo=0;                          // номер протокола
  Size=String(DupeString(' ',10));          // размер шины
  Model=String(DupeString(' ',10));         // модель шины
  TestProcedure=String(DupeString(' ',10)); // методика испытаний
  StandName="13";                   // наименование стенда
  Manufacturer=String(DupeString(' ',10));  // изготовитель шины
  DrumDiameter=1700;                 // диаметр барабана, мм
  TestCustomer=DupeString(' ',10);   // заказчик
  ManufactDate=Now();                // дата изготовления
  FormNo=0;                          // номер формы протокола
  OrderNo=0;                         // номер заказа
  PerfSpecNo=0;                      // номер ТЗ
  SerialNo=0;                        // порядковый номер шины
  LoadIndex=DupeString(' ',10);      // Индекс нагрузки шины
  MaxLoad=0.0;                       // максимальная нагрузка
  SpeedInd=DupeString(' ',10);       // Индекс скорости
  MaxSpeed=0.0;                      // Максимальная скорость
  StaticR=0.0;                       // статический радиус
  OuterD=0.0;                        // наружный диаметр
  WheelRim=DupeString(' ',10);       // обозначение обода
  MaxLoadPress=0.0;                  // давление при максимально нагрузке
  ProfileWide=0;                     // ширина профиля
  Type=1;                            // тип покрышки, 0-радиальная, 1-диагональная
  CurrentLoad=0.0;                   // нагрузка
  InitPressure=0.0;                  // начальное давление
  CurrentSpeed=0.0;                  // скорость
  TestMode=-1;                       // режим испытаний, 0-по времени, 1-по пути
  TotalTime=0;                       // общее время испытаний, мсек
  TotalS=0.0;                        // сумарный путь испытаний
  StepsNo=0;                         // количество шагов программы
  PollsNo=0;                         // количество опросов
  Clear();
}
void	Tyre::Clear	(void)
{
	for (int i = 0; i < 250; i++)
	{
		rT[i]=0;                         // массивы с результатами испытаний
		rV[i]=0;
		rS[i]=0;
		rL[i]=0;
		rR[i]=0;
		rTemp[i]=0;
	}
}
//---- End of Tyre(constructor) ---------------------------------------------

__fastcall Tyre::~Tyre(void)                      // деструктор
{
  Size=NULL;                         // размер шины
  Model=NULL;                        // модель шины
  TestProcedure=NULL;                // методика испытаний
  Manufacturer=NULL;                 // изготовитель шины
  TestCustomer=NULL;                 // заказчик
  LoadIndex=NULL;                    // Индекс нагрузки шины
  SpeedInd=NULL;                     // Индекс скорости
  WheelRim=NULL;                     // обозначение обода
}
//---- End of ~Tyre(destructor) ---------------------------------------------

Tyre __fastcall Tyre::operator=(Tyre op2) // переопределение присваивания
{
  ProtNo       =op2.ProtNo;        Size           =op2.Size;        Model=op2.Model;
  TestProcedure=op2.TestProcedure; StandName      =op2.StandName;
  Manufacturer =op2.Manufacturer;  DrumDiameter   =op2.DrumDiameter;
  TestCustomer =op2.TestCustomer;  ManufactDate   =op2.ManufactDate;
  FormNo       =op2.FormNo;        OrderNo        =op2.OrderNo;
  PerfSpecNo   =op2.PerfSpecNo;    SerialNo       =op2.SerialNo;
  LoadIndex    =op2.LoadIndex;     MaxLoad        =op2.MaxLoad;
  SpeedInd     =op2.SpeedInd;      MaxSpeed       =op2.MaxSpeed;
  StaticR      =op2.StaticR;       OuterD         =op2.OuterD;
  WheelRim     =op2.WheelRim;      MaxLoadPress   =op2.MaxLoadPress;
  ProfileWide  =op2.ProfileWide;   Type           =op2.Type;
  CurrentLoad  =op2.CurrentLoad;   InitPressure   =op2.InitPressure;
  CurrentSpeed =op2.CurrentSpeed;  TestMode       =op2.TestMode;
  TotalTime    =op2.TotalTime;     TotalS         =op2.TotalS;
  StepsNo      =op2.StepsNo;       PollsNo        =op2.PollsNo;
  for (int i = 0; i < 250; i++) {
    rT[i]=op2.rT[i];
    rV[i]=op2.rV[i];
    rS[i]=op2.rS[i];
    rL[i]=op2.rL[i];
    rR[i]=op2.rR[i];
    rTemp[i]=op2.rTemp[i];
  }
  return *this;
}
//---- End of Tyre::operator= -----------------------------------------------

void __fastcall Tyre::WriteTyreToFile(String fname)    // запись полей Tyre в файл с именем fname
{ FILE *fparam;
  if((fparam=fopen(AnsiString(fname).c_str(),"wb"))==NULL){
    LogPrint("Can't open file \""+fname+"\" for writing!",clRed);
    return;
  }
  WriteString(Size,fparam);
  WriteString(Model,fparam);
  WriteString(TestProcedure,fparam);
  WriteString(StandName,fparam);
  WriteString(Manufacturer,fparam);
  WriteString(TestCustomer,fparam);
  WriteString(LoadIndex,fparam);
  WriteString(SpeedInd,fparam);
  WriteString(WheelRim,fparam);
  fwrite(&ProtNo,sizeof(int),1,fparam);
  fwrite(&FormNo,sizeof(int),1,fparam);
  fwrite(&OrderNo,sizeof(int),1,fparam);
  fwrite(&PerfSpecNo,sizeof(int),1,fparam);
  fwrite(&SerialNo,sizeof(int),1,fparam);
  fwrite(&ProfileWide,sizeof(int),1,fparam);
  fwrite(&Type,sizeof(int),1,fparam);
  fwrite(&TestMode,sizeof(int),1,fparam);
  fwrite(&TotalTime,sizeof(int),1,fparam);
  fwrite(&StepsNo,sizeof(int),1,fparam);
  fwrite(&PollsNo,sizeof(int),1,fparam);
  fwrite(&DrumDiameter,sizeof(float),1,fparam);
  fwrite(&MaxLoad,sizeof(float),1,fparam);
  fwrite(&MaxSpeed,sizeof(float),1,fparam);
  fwrite(&StaticR,sizeof(float),1,fparam);
  fwrite(&OuterD,sizeof(float),1,fparam);
  fwrite(&MaxLoadPress,sizeof(float),1,fparam);
  fwrite(&CurrentLoad,sizeof(float),1,fparam);
  fwrite(&InitPressure,sizeof(float),1,fparam);
  fwrite(&CurrentSpeed,sizeof(float),1,fparam);
  fwrite(&TotalS,sizeof(float),1,fparam);
  fclose(fparam);
}
//---- End of WriteTyreToFile -----------------------------------------------

void __fastcall Tyre::ReadTyreFmFile(String fname)     // чтение полей Tyre из файла с именем fname
{ FILE *fparam;
  if((fparam=fopen(AnsiString(fname).c_str(),"rb"))==NULL){
    LogPrint("Can't open file \""+fname+"\" for writing!",clRed);
    return;
  }
  Size         =ReadString(fparam);
  Model        =ReadString(fparam);
  TestProcedure=ReadString(fparam);
  StandName    =ReadString(fparam);
  Manufacturer =ReadString(fparam);
  TestCustomer =ReadString(fparam);
  LoadIndex    =ReadString(fparam);
  SpeedInd     =ReadString(fparam);
  WheelRim     =ReadString(fparam);
  fread(&ProtNo,sizeof(int),1,fparam);
  fread(&FormNo,sizeof(int),1,fparam);
  fread(&OrderNo,sizeof(int),1,fparam);
  fread(&PerfSpecNo,sizeof(int),1,fparam);
  fread(&SerialNo,sizeof(int),1,fparam);
  fread(&ProfileWide,sizeof(int),1,fparam);
  fread(&Type,sizeof(int),1,fparam);
  fread(&TestMode,sizeof(int),1,fparam);
  fread(&TotalTime,sizeof(int),1,fparam);
  fread(&StepsNo,sizeof(int),1,fparam);
  fread(&PollsNo,sizeof(int),1,fparam);
  fread(&DrumDiameter,sizeof(float),1,fparam);
  fread(&MaxLoad,sizeof(float),1,fparam);
  fread(&MaxSpeed,sizeof(float),1,fparam);
  fread(&StaticR,sizeof(float),1,fparam);
  fread(&OuterD,sizeof(float),1,fparam);
  fread(&MaxLoadPress,sizeof(float),1,fparam);
  fread(&CurrentLoad,sizeof(float),1,fparam);
  fread(&InitPressure,sizeof(float),1,fparam);
  fread(&CurrentSpeed,sizeof(float),1,fparam);
  fread(&TotalS,sizeof(float),1,fparam);
  fclose(fparam);
}
//---- End of ReadTyreFmFile ------------------------------------------------

void __fastcall Tyre::PrintProtToFile(String fname,String side)    // печать протокола испытаний в файл fname
{ FILE *fprint;
  if((fprint=fopen(AnsiString(fname).c_str(),"wt"))==NULL){
    LogPrint("Can't open file \""+fname+"\" for printing!",clRed);
    return;
  }
  fprintf(fprint,"%s\n\n",AnsiString(Now().DateTimeString()).c_str());
  fprintf(fprint,"          ПРОТОКОЛ ИСПЫТАНИЙ № ______"/*%d*/" НА СТЕНДЕ %s\n"/*,ProtNo*/,AnsiString(StandName+side).c_str());
  fprintf(fprint,"     Изготовитель: %10s     Заказчик: %s  Заказ №: %5d\n",
				 AnsiString(Manufacturer).c_str(),AnsiString(TestCustomer).c_str(),OrderNo);
  fprintf(fprint,"           Модель: %10s            Размер: %10s\n",AnsiString(Model).c_str(),AnsiString(Size).c_str());
  fprintf(fprint,"Дата изготовления: %10s      Порядковый №: %5d\n",CustomDate().c_str(),SerialNo);
  fprintf(fprint,"     Тех. задание: %4d                Методика: %s\n",PerfSpecNo,AnsiString(TestProcedure).c_str());
  fprintf(fprint," Диаметр барабана,мм: %5.0f мм         Форма №: %5d\n\n",DrumDiameter,FormNo);
  if(Type==0)
	fprintf(fprint,"               ХАРАКТЕРИСТИКИ ИСПЫТЫВАЕМОЙ ШИНЫ\n"/*РАДИАЛЬНОЙ ШИНЫ\n"*/);
  else
	fprintf(fprint,"               ХАРАКТЕРИСТИКИ ИСПЫТЫВАЕМОЙ ШИНЫ\n"/*ДИАГОНАЛЬНОЙ ШИНЫ\n"*/);
  fprintf(fprint,"   Индекс нагрузки: %10s    Максимальная нагрузка: %6.2f кН \n",AnsiString(LoadIndex).c_str(),MaxLoad);
  fprintf(fprint,"Категория скорости: %10s    Максимальная скорость: %6.2f км/час \n",AnsiString(SpeedInd).c_str(),MaxSpeed);
  fprintf(fprint," Давление при Qmax: %4.2f кПа        Наружный диаметр: %6.2f мм \n",MaxLoadPress,OuterD);
  fprintf(fprint,"Статический радиус: %6.2f мм            Ширина профиля: %6d мм \n",StaticR,ProfileWide);
  fprintf(fprint,"   Давление в шине: %6.1f кПа                   Обод: %10s\n\n",InitPressure,AnsiString(WheelRim).c_str());
  fprintf(fprint,"                            РЕЗУЛЬТАТЫ ИСПЫТАНИЙ:\n");
  if(TestMode==0)
    fprintf(fprint,"      Режим обкатки: по времени\n");
  else
    fprintf(fprint,"      Режим обкатки: по пути\n");
  fprintf(fprint,"            Общее время испытаний: %10s\n",AnsiString(mSecToHMSStr(TotalTime)).c_str());
  fprintf(fprint,"            Общий путь: %8f км\n",TotalS);
  fprintf(fprint,"            Дата начала испытания: %s\n", AnsiString(Start.FormatString("dd.mm.yyyy hh:nn:ss")).c_str());
  fprintf(fprint,"            Дата окончания испытания: %s\n", AnsiString(Stop.FormatString("dd.mm.yyyy hh:nn:ss")).c_str());

  fprintf(fprint,"+-----+---------+--------+--------+--------+---------+-----------+\n");
  fprintf(fprint,"|Опрос|  время  |скорость|путь, км|нагрузка| радиус  |Температура|\n");
  fprintf(fprint,"|     |  чч:мм  | км/час |        |  кН    |   мм    |    С      |\n");
  fprintf(fprint,"+-----+---------+--------+--------+--------+---------+-----------+\n");
  for (int i = 0; i < PollsNo; i++) {
	if (rT[i]!=0&&rV[i]!=0&&rS[i]!=0&&rL[i]!=0&&rR[i]!=0&&rTemp[i]!=0)
	{ //это не даст печататься пустым строкам данных (пожелание заказчика)
		fprintf(fprint,"| %03d |%7s  | %6.2f | %6.0f | %6.2f | %5.2f |    %5.1f  |\n",
		i+1,AnsiString(mSecToHMSStr(rT[i])).c_str(),rV[i],rS[i],rL[i],rR[i],rTemp[i]);
	}
  }
  fprintf(fprint,"+-----+---------+--------+--------+--------+---------+-----------+\n");
  fclose(fprint);
}
//---- End of PrintProtToFile -----------------------------------------------

void __fastcall Tyre::PrintProtocol(TPrinter *pprt,String side)    // печать протокола на принтер pprt
{
  String wstr[60]={""};
  int left[60];
  float pWidthM=210,pHeightM=297;            // ширина и высота страницы в мм
  float LeftMargM=15, RightMargM=15;         // поля слева и справа в мм
  float UpperMargM=15, LowMargM=15;          // поля сверху и снизу в мм
  int lineX,lineY;
  int pWidth=pprt->PageWidth;                // ширина страницы в пикселях
  int pHeight=pprt->PageHeight;              // высота страницы в пикселях
  int fHeight=pprt->Canvas->TextHeight("A"); // высота строки в пикселях
  int LeftMarg, RightMarg;                   // поля слева и справа в пикселях
  int UpperMarg, LowMarg;                    // поля сверху и снизу в пикселях
  LeftMarg=LeftMargM/pWidthM*pWidth;
  RightMarg=RightMargM/pWidthM*pWidth+850;
  UpperMarg=UpperMargM/pHeightM*pHeight;
  LowMarg=LowMargM/pHeightM*pHeight;
  int prtWidth=pWidth-LeftMarg-RightMarg;    // ширина печатаемой области в пикселях
  int prtHeight=pHeight-UpperMarg-LowMarg;   // высота печатаемой области в пикселях
  int LinesPP=50;                            // количество строк на странице
  int LSp=(prtHeight-fHeight)/(LinesPP-1);   // расстояние между строками в пикселях
//  lineX=LeftMarg;
  lineY=UpperMarg+fHeight;
  int LineCnt=0;
//  wstr[LineCnt]="Font is: \""+pprt->Canvas->Font->Name+"\"";
//  left[LineCnt++]=LeftMarg;
//  left[LineCnt]=abs( prtWidth - pprt->Canvas->TextWidth(wstr[LineCnt++]) )/2+LeftMarg;
//  wstr[1]="Высота страницы: "+String(pHeight);
//  wstr[2]="Font height: "+String(fHeight);
//  wstr[3]="Line spacing: "+String(LSp);
  wstr[LineCnt]="ПРОТОКОЛ ИСПЫТАНИЙ № ______"/*String(ProtNo)+*/" НА СТЕНДЕ "+StandName+side;
  left[LineCnt]=abs( prtWidth - pprt->Canvas->TextWidth(wstr[LineCnt]) )/2+LeftMarg;
  wstr[++LineCnt]="     Изготовитель: "+Manufacturer+"     Заказчик: "+TestCustomer+"  Заказ №: "+String(OrderNo);
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="           Модель: "+Model+"            Размер: "+Size;
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="Дата изготовления: "+CustomDate()+"     Порядковый №: "+String(SerialNo);
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="     Тех. задание: "+String(PerfSpecNo)+"   Методика: "+TestProcedure;
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]=" Диаметр барабана: "+String(DrumDiameter)+"мм       Форма №: "+String(FormNo);
  left[LineCnt]=LeftMarg;
  if(Type==0)
	wstr[++LineCnt]="ХАРАКТЕРИСТИКИ ИСПЫТАННОЙ ШИНЫ"/*РАДИАЛЬНОЙ ШИНЫ"*/;
  else
	wstr[++LineCnt]="ХАРАКТЕРИСТИКИ ИСПЫТАННОЙ ШИНЫ"/*ДИАГОНАЛЬНОЙ ШИНЫ"*/;
  left[LineCnt]=abs(prtWidth-pprt->Canvas->TextWidth(wstr[LineCnt]))/2+LeftMarg;
  wstr[++LineCnt]="   Индекс нагрузки: "+LoadIndex+"   Максимальная нагрузка: "+FloatToStrF(MaxLoad,ffFixed,6,2)+"кН";
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="Категория скорости: "+SpeedInd+"   Максимальная скорость: "+FloatToStrF(MaxSpeed,ffFixed,6,2)+"км/час";
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]=" Давление при Qmax: "+FloatToStrF(MaxLoadPress,ffFixed,6,2)+"кПа        Наружный диаметр: "+FloatToStrF(OuterD,ffFixed,6,2)+"мм";
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="Статический радиус: "+FloatToStrF(StaticR,ffFixed,6,2)+"мм            Ширина профиля: "+String(ProfileWide)+"мм";
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="   Давление в шине: "+FloatToStrF(InitPressure,ffFixed,6,1)+"кПа                   Обод: "+WheelRim;
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="РЕЗУЛЬТАТЫ ИСПЫТАНИЙ:";
  left[LineCnt]=abs(prtWidth-pprt->Canvas->TextWidth(wstr[LineCnt]))/2+LeftMarg;
  if(TestMode==0)
    wstr[++LineCnt]="    Режим обкатки: по времени";
  else
    wstr[++LineCnt]="    Режим обкатки: по пути";
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="        Общее время испытаний: "+mSecToHMSStr(TotalTime);
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="        Общий путь: "+FloatToStrF(TotalS,ffFixed,7,0) +"км";
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="        Дата начала испытания: " + Start.FormatString("dd.mm.yyyy hh:nn:ss");
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="        Дата окончания испытания: " + Stop.FormatString("dd.mm.yyyy hh:nn:ss");
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="+-----+---------+--------+--------+--------+---------+-----------+";
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="|Опрос|  время  |скорость|путь, км|нагрузка| радиус  |Температура|";
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="|     | чч:мм   | км/час |        |  кН    |   мм    |    С      |";
  left[LineCnt]=LeftMarg;
  wstr[++LineCnt]="+-----+---------+--------+--------+--------+---------+-----------+";
  left[LineCnt]=LeftMarg;
  int LinePrinted=-1;

  for (int i = 0; i < PollsNo; i++) {
	if (rT[i]!=0&&rV[i]!=0&&rS[i]!=0&&rL[i]!=0&&rR[i]!=0&&rTemp[i]!=0)
	{//это не даст печататься пустым строкам данных (пожелание заказчика)
		wstr[++LineCnt]="| "+IntToS(i+1,3)+" | "+mSecToHMSStr(rT[i])+"   | "+
		  FltToStr(rV[i],ffFixed,6,2)+" | "+
		  FltToStr(rS[i],ffFixed,6,0)+" | "+
		  FltToStr(rL[i],ffFixed,6,2)+" | "+
		  FltToStr(rR[i],ffFixed,5,2)+" |    "+
		  FltToStr(rTemp[i],ffFixed,5,1)+"  |";
		left[LineCnt]=LeftMarg;
	}

	if(LineCnt==LinesPP-1){
      LinePrinted=i;
      break;
    }
  }
  wstr[++LineCnt]="+-----+---------+--------+--------+--------+---------+-----------+";
  left[LineCnt]=LeftMarg;
  pprt->BeginDoc();
  for (int i = 0; i <= LineCnt; i++,lineY+=LSp) {
    pprt->Canvas->TextOutA(left[i],lineY,wstr[i]);
  }
  pprt->EndDoc();
  if(LinePrinted>=0) {
    int NotPrintedLines=PollsNo-LinePrinted;
    LogPrint("NotPrintedLines="+String(NotPrintedLines));
    int PNum=NotPrintedLines/LinesPP;
    if(NotPrintedLines%LinesPP !=0 ) {
      PNum++;
    }
    LogPrint("NumberOfPages="+String(PNum));
    for(int PNo = 0; PNo < PNum; PNo++) {
      for (int i = 0; i < 60; i++) {
        wstr[i]=""; left[i]=0;
      }
      LineCnt=-1;
      for (int i = LinePrinted; i < PollsNo; i++) {
        wstr[++LineCnt]="| "+IntToS(i+1,3)+" | "+mSecToHMSStr(rT[i])+"| "+
          FltToStr(rV[i],ffFixed,6,2)+" | "+
          FltToStr(rS[i],ffFixed,6,2)+" | "+
          FltToStr(rL[i],ffFixed,6,2)+" | "+
          FltToStr(rR[i],ffFixed,5,0)+" |    "+
          FltToStr(rTemp[i],ffFixed,5,1)+"  |";
        left[LineCnt]=LeftMarg;
        if(LineCnt == LinesPP-1){
          LinePrinted+=i;
          break;
        }
      }
      lineY=UpperMarg+fHeight;
      pprt->BeginDoc();
      for (int i = 0; i <= LineCnt; i++,lineY+=LSp) {
        pprt->Canvas->TextOutA(left[i],lineY,wstr[i]);
      }
      pprt->EndDoc();
    }
  }
}
//---- End of PrintProtocol -------------------------------------------------

