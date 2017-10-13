#pragma once
#ifndef data_updaterH
#define data_updaterH
#include <chrono>
#include <functional>
#include <atomic>
#include <windows.h>
#include <mutex>

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
   void Stop();
   void Terminate();
   uint64_t Count();

   void Run();
private:
   TimeOut mTimeout;
   Action mAction;
   std::atomic< uint64_t > mCount;
   std::mutex mMutex;
   HANDLE mThread;
};

}

#endif // DATAUPDATER_H
