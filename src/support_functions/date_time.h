#ifndef date_timeH
#define date_timeH
#pragma once
#include <chrono>
#include "date/date.h"
#include <string>
namespace dt
{
typedef std::chrono::system_clock::time_point DateTime;
typedef std::chrono::system_clock Clock;

extern std::string DEFAULT_DATE_TIME_FORMAT;

DateTime Now();
std::string ToString( DateTime const& dt, std::string const& fmt = DEFAULT_DATE_TIME_FORMAT );

std::string mSecToHMSStr( int tm, bool show_sec = false ); // перевод целого кол-ва мсек в строку чч:мм:сс

std::string ToWeekYYYY( DateTime const& dt );
std::string ToWeekYY( DateTime const& dt );
DateTime FromWeekYYYY( std::string const& dt );
DateTime FromWeekYY( std::string const& dt );

}

#endif // DATE_TIME_H
