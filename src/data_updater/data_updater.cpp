#include "data_updater.h"
#include <thread>

namespace timer
{

namespace
{
DWORD WINAPI ThreadFunk(
  _In_ LPVOID lpParameter
)
{
   Timer *self = static_cast<Timer*>(lpParameter);
   self->Run();
}

}

Timer::Timer(TimeOut timeout, Action f ):
   mTimeout( timeout ),
   mAction( f ),
   mThread( CreateThread(NULL,0, &ThreadFunk, this, CREATE_SUSPENDED, NULL) )
{
}
Timer::~Timer()
{
   Terminate();
}

void Timer::Terminate()
{
   TerminateThread( mThread, 0 );
}

void Timer::Start()
{
   ResumeThread( mThread );
}

void Timer::Stop()
{
   SuspendThread( mThread );
}

uint64_t Timer::Count()
{
   return mCount;
}

void Timer::Run()
{
   for(;;)
   {
      std::this_thread::sleep_for( mTimeout );
      ++mCount;
      mAction();
   }
}

}
