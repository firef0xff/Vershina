#include "data_updater.h"

namespace timer
{

Timer::Timer(TimeOut timeout, Action f ):
   mTimeout( timeout ),
   mAction( f ),
   mRunAction( false ),
   mTerminate( false ),
   mThread( std::bind( &Timer::Run, this ) )
{
}
Timer::~Timer()
{
   Terminate();
   if ( mThread.joinable() )
   {
      mThread.join();
   }
}

void Timer::Terminate()
{
   mTerminate = true;
}

void Timer::Start()
{
   mRunAction = true;
}
bool Timer::Started()
{
   return mRunAction;
}
void Timer::Stop()
{
   mRunAction = false;
}

uint64_t Timer::Count()
{
   return mCount;
}

void Timer::Run()
{
   for(;!mTerminate;)
   {
      std::this_thread::sleep_for( mTimeout );
      if ( mTerminate )
         return;
      if ( !mRunAction )
         continue;

      ++mCount;
      mAction();
   }
}

}
