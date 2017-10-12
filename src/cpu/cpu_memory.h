#pragma once
#ifndef cpu_memoryH
#define cpu_memoryH

#include <vector>
#include "data/gr1.h"
#include "data/gr2.h"
#include "data/gr3.h"
#include "data/gr4.h"
#include "data/gr5.h"
#include "data/gr6.h"
#include "data/gr7.h"
#include "data/gr8.h"
#include "data/gr9.h"
#include "data/gr10.h"
#include "data/gr11.h"
#include "data/gr12.h"
#include "data/gr13.h"
#include "si8/si8.h"
#include "data/common_params.h"
#include <memory>
#include <functional>

namespace cpu
{

class Position
{
public:
   Position( std::unique_ptr<data::GR1> gr1,
             std::unique_ptr<data::GR2> gr2,
             std::unique_ptr<data::GR3> gr3,
             std::unique_ptr<data::GR4> gr4,
             std::unique_ptr<data::GR5> gr5,
             std::unique_ptr<data::GR6> gr6,
             std::unique_ptr<data::GR7> gr7,
             std::unique_ptr<data::GR12> gr12,
             std::unique_ptr<data::SI8> si8);

   std::unique_ptr<data::GR1> mGr1;
   std::unique_ptr<data::GR2> mGr2;
   std::unique_ptr<data::GR3> mGr3;
   std::unique_ptr<data::GR4> mGr4;
   std::unique_ptr<data::GR5> mGr5;
   std::unique_ptr<data::GR6> mGr6;
   std::unique_ptr<data::GR7> mGr7;
   std::unique_ptr<data::GR12> mGr12;

   std::unique_ptr<data::SI8> mTimeSensor;
};

class CpuMemory
{
public:
    ~CpuMemory();
    static CpuMemory& Instance();

    data::CommonParams mCommonParams;
    data::SI8 mSpeedSensor;

    std::unique_ptr<Position> mPos1;

    std::vector<Position*> mPos;
    int ReadCycleParameters();
    void UpdateCpuData();
    bool IsConnected();

    typedef std::function< void() > CallBack;
    void OnConnected( CallBack f );
private:
    CpuMemory();
    CpuMemory( CpuMemory const& ) = delete;
    CpuMemory& operator = ( CpuMemory const& ) = delete;
    std::vector< CpuMemory::CallBack > CALLBACKS;
};


}//namespace cpu
#endif
