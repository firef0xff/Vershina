#include "log.h"
#include <mutex>

namespace logger
{

namespace
{
std::unique_ptr< Logger > LOGGER;
}
void LogPrint( std::string msg, LineColor c )
{
   if ( LOGGER )
      LOGGER->AddRecord( msg, c );
}

Logger::Logger()
{}
Logger::~Logger()
{}
void Logger::SetLogger( std::unique_ptr< Logger > l )
{
   static std::mutex m;
   std::lock_guard<std::mutex> lock( m );
   LOGGER = std::move( l );
}

}
