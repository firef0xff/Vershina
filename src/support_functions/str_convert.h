#ifndef str_convertH
#define str_convertH
#pragma once

#include <string>

std::string FloatToStringF( float f, int digits , int precision);
std::string FloatToStringF( double f, int digits , int precision);

// Преобразование целого в строку длиной l
// i - преобразуемое число
// l - длина строки
std::string  IntToS( int i, int l);


#endif // STR_CONVERT_H
