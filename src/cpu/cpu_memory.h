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
#include "data/common_params.h"

namespace cpu
{

class Position
{
public:
   Position( data::GR1& gr1,
             data::GR2& gr2,
             data::GR3& gr3,
             data::GR4& gr4,
             data::GR5& gr5,
             data::GR6& gr6,
             data::GR7& gr7,
             data::GR12& gr12 );

   data::GR1& mGr1;
   data::GR2& mGr2;
   data::GR3& mGr3;
   data::GR4& mGr4;
   data::GR5& mGr5;
   data::GR6& mGr6;
   data::GR7& mGr7;
   data::GR12& mGr12;
};

class CpuMemory
{
public:
    ~CpuMemory();
    static CpuMemory& Instance();

    data::CommonParams mCommonParams;

    Position mPos1;
    Position mPos2;

    std::vector<Position*> mPos;
    int ReadCycleParameters();

private:
    CpuMemory();
    CpuMemory( CpuMemory const& ) = delete;
    CpuMemory& operator = ( CpuMemory const& ) = delete;
};

}//namespace cpu
#endif
