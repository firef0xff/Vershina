#include "str_convert.h"
#include <sstream>
#include <iomanip>

std::string FloatToStringF( float f, int digits, int precision )
{
   return FloatToStringF( static_cast<double>( f ), digits, precision );
}
std::string FloatToStringF( double f, int digits, int precision )
{
   std::stringstream buf;
   buf << std::fixed << std::setfill('0') << std::setw( digits ) << std::setprecision( precision ) << f;

   return buf.str();
}


std::string  IntToS( int i, int l)
{
   std::stringstream buf;
   buf << std::setfill(' ') << std::setw( l ) << i;
   return buf.str();
}
