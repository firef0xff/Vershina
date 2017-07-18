#pragma once
#ifndef cpu_memoryH
#define cpu_memoryH

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

namespace cpu
{

class CpuMemory
{
public:
    ~CpuMemory();
    static CpuMemory& Instance();

    data::GR1 mGr1;
    data::GR2 mGr2;
    data::GR3 mGr3;

    //A
    data::GR4 mGr4Pos1;
    data::GR5 mGr5Pos1;
    data::GR6 mGr6Pos1;
    data::GR7 mGr7Pos1;
    data::GR12 mGr12Pos1;

    //B
    data::GR4 mGr4Pos2;
    data::GR5 mGr5Pos2;
    data::GR6 mGr6Pos2;
    data::GR7 mGr7Pos2;
    data::GR12 mGr12Pos2;

    int ReadCycleParameters(void);

private:
    CpuMemory();
    CpuMemory( CpuMemory const& ) = delete;
    CpuMemory& operator = ( CpuMemory const& ) = delete;
};

}//namespace cpu
#endif
