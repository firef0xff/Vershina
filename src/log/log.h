#ifndef logH
#define logH
#include <string>
#include <memory>

namespace logger
{

enum LineColor
{
   lcWHITE,
   lcRED,
   lcLIME,
};

void LogPrint( std::string msg, LineColor c = lcWHITE );

class Logger
{
public:
   Logger();
   virtual ~Logger();
   virtual void AddRecord( std::string msg, LineColor c ) = 0;
   static void SetLogger( std::unique_ptr< Logger > l );
};

}

#endif // LOG_H
