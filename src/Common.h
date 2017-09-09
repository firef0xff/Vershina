#ifndef CommonH
#define CommonH
// ---------------------------------------------------------------------------
#include <stdio.h>
#include <Comctrls.hpp>
#include "def.h"
#include <string>

// объявление общих функций -------------------------------------------------

String  FileNameParse
   ( // Функция выделения имени файла из полного пути
   String SFN);
float  StrToFlt(String);
// Преобразование строки в значение типа float
int  StrToI(String); // ПРеобразование строки в значение типа int
String  FltToStr( // Преобразование числа в строку длиной l
   float f, // преобразуемое число
   TFloatFormat ff, // формат
   int l, // длина строки
   int r); // длина дробной части
void  LeastSquares
   ( // расчет коэффициентов A и B методом наименьших квадратов
   float X[], // массив X
   float Y[], // массив Y
   int N, // размерность массива
   float &A, //
   float &B); //
int  BUnion(bool b1, bool b2);
// объединение занчений аргументов в целое значение

// индикаторы автосохранения протоколов за испытание

#endif
