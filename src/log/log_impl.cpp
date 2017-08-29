#include "log_impl.h"
#include <string>
#include <mutex>
#include "../support_functions/date_time.h"
#include "log.h"
namespace logger
{

namespace
{
std::string LogFName() // Генерация имени файла журнала
{
   std::string wfname = "RBLogFile";
   wfname += dt::ToString( dt::Now(), "%Y%m%d" );
   wfname += ".log";
   return wfname;
}
#ifdef WINDOWS
TColor lcTocl( logger::LineColor cl )
{
   switch ( cl )
   {
   case lcWHITE:
      return clWhite;
   case lcRED:
      return clRed;
   case lcLIME:
      return clLime;
   case lcMONEYGREEN:
      return clMoneyGreen;
   case lcAQUA:
      return clAqua;
   case lcSKYBLUE:
      return clSkyBlue;
   case lcGREEN:
      return clGreen;
   case lcYELLOW:
      return clYellow;
   case lcOLIVE:
      return clOlive;
   default:
      return clWhite;
   }
   return clWhite;
}

logger::LineColor clTolc( TColor cl )
{
   switch ( cl )
   {
   case clWhite:
      return lcWHITE;
   case clRed:
      return lcRED;
   case clLime:
      return lcLIME;
   case clMoneyGreen:
      return lcMONEYGREEN;
   case clAqua:
      return lcAQUA;
   case clSkyBlue:
      return lcSKYBLUE;
   case clGreen:
      return lcGREEN;
   case clYellow:
      return lcYELLOW;
   case clOlive:
      return lcOLIVE;
   default:
      return lcWHITE;
   }
   return lcWHITE;
}
#endif

class FileLogger : public Logger
{
public:
   void AddRecord( std::string msg, LineColor c )
   {
      std::lock_guard<std::recursive_mutex> lock(mMutex);
      std::string fname = LogFName();
      FILE *fparam = fopen(fname.c_str(), "at+");
      if ( fparam == nullptr )
         return;
      fprintf(fparam, "%8s: %s\n", dt::ToString( dt::Now() ).c_str(), msg.c_str() );
      fclose(fparam);
   }
protected:
   std::recursive_mutex mMutex;
};

#ifdef WINDOWS
class WidgetLogger : public FileLogger
{
public:
   WidgetLogger( TRichEdit *ptr ):
      pLog( ptr )
   {}
   void AddRecord( std::string msg, LineColor c )
   {
      std::lock_guard<std::recursive_mutex> lock(mMutex);
      FileLogger::AddRecord( msg, c );
      pLog->SelAttributes->Color = lcTocl( c );
      pLog->Lines->Add( AnsiString( msg.c_str() ) );
   }
private:
   TRichEdit *pLog;
};
#endif
}
}

#ifdef WINDOWS
void  LogPrint( String Str, TColor CClr )
{
   logger::LogPrint( AnsiString( Str ).c_str(), logger::clTolc( CClr ) );
}
void InitLogger( TRichEdit *pLog )
{
   logger::Logger::SetLogger( std::unique_ptr<logger::Logger>( new logger::WidgetLogger( pLog ) ) );
}
#endif
