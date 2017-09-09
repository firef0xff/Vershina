#pragma once
#ifndef data_updaterH
#define data_updaterH
#include <chrono>
#include <functional>
#include <thread>
#include <atomic>

namespace timer
{

class Timer
{
public:
   typedef std::function< void() > Action;
   typedef std::chrono::milliseconds TimeOut;
   Timer( TimeOut timeout, Action f );
   ~Timer();

   void Start();
   bool Started();
   void Stop();
   void Terminate();
   uint64_t Count();
private:
   void Run();
   TimeOut mTimeout;
   Action mAction;
   std::atomic< bool > mRunAction;
   std::atomic< bool > mTerminate;
   std::atomic< uint64_t > mCount;
   std::thread mThread;
};

}

#endif // DATAUPDATER_H
