#include "date_time.h"
#include "date/date.h"
namespace dt
{
std::string DEFAULT_DATE_TIME_FORMAT = "%d.%m.%Y %H:%M:%S";
std::string DEFAULT_DATE_FORMAT = "%d.%m.%Y";

typedef std::chrono::system_clock::duration SysDuration;
SysDuration GetUtcDiff()
{
   std::time_t t = std::time(nullptr);
   tm gm = *std::gmtime( &t );
   tm loc = *localtime(&t);

   DateTime gm_t = std::chrono::system_clock::from_time_t( std::mktime( &gm ) );
   DateTime loc_t = std::chrono::system_clock::from_time_t( std::mktime( &loc ) );

   return loc_t.time_since_epoch() - gm_t.time_since_epoch();
}
SysDuration UTC_DIFF = GetUtcDiff();

DateTime Now()
{

   auto t = Clock::now().time_since_epoch();
   t += UTC_DIFF;
   return DateTime( t );
}

std::string ToString( DateTime const& dt, std::string const& fmt )
{
   if ( dt == DateTime() )
   {
      return "";
   }
   std::string res = date::format( fmt, dt );
   return res;
}
DateTime FromString( std::string const& dt, std::string const& fmt )
{
   DateTime res;
   if (dt.empty())
      return res;

   std::istringstream s{dt};
   date::from_stream( s, fmt.c_str(), res );
   return res;
}

std::string mSecToHMSStr(int tm , bool show_sec) // перевод целого кол-ва мсек в строку чч:мм:сс
{
   int s = tm / 1000;
   int h = s / 3600;
   s -= h * 3600;
   int m = s / 60;
   s -= m * 60;
   std::string ws = "";

   // часы
   if ( h == 0 )
      ws = "00:";
   else if ( h < 10 )
      ws = "0" + std::to_string( h ) + ":";
   else
      ws = std::to_string( h ) + ":";

   // минуты
   if (m == 0)
      ws += "00";
   else if (m < 10)
      ws += "0" + std::to_string( m );
   else
      ws += std::to_string( m );

   if ( show_sec )
   {
      ws += ":";
      // секукны
      if ( s == 0 )
         ws += "00";
      else if ( s < 10 )
         ws += "0" + std::to_string( s );
      else
         ws += std::to_string( s );
   }

   return ws;
}


std::string ToWeekYYYY( DateTime const& dt )
{
   date::sys_days days( std::chrono::duration_cast<date::days>( dt.time_since_epoch() ) );
   date::year_month_day ymd( days );
   date::year_month_day _1_jan( ymd.year(), date::month(1), date::day(1) );

   date::weeks w = std::chrono::duration_cast<date::weeks>( date::sys_days(ymd) - date::sys_days(_1_jan) );

   int32_t year = static_cast<int>( ymd.year() );
   int week_num = w.count() + 1;
   return std::to_string( week_num ) + "." + std::to_string( year );
}
DateTime FromWeekYYYY( std::string const& dt )
{
   size_t delim = dt.find( "." );
   int week = 1;
   int year = 1970;
   try
   {
      auto w_str = dt.substr( 0, delim );
      auto y_str = dt.substr( delim + 1, dt.length() - delim );
      week = std::stoi( w_str );
      year = std::stoi( y_str );
   }
   catch(...)
   {}

   date::year_month_day ymd( date::year(year), date::month(1), date::day(1) );
   DateTime res = DateTime( std::chrono::duration_cast<SysDuration>( (static_cast<date::sys_days>(ymd) + std::chrono::duration_cast<date::days>( date::weeks(week-1) )).time_since_epoch() ) );
   return res;
}
}
