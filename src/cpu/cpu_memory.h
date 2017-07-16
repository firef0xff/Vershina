#pragma once
#ifndef cpu_memoryH
#define cpu_memoryH

#include "data/gr1.h"
#include "data/gr2.h"
#include "data/gr3.h"
#include "data/gr4.h"
#include "data/gr5.h"
#include "data/gr6.h"
#include "data/gr8.h"
#include "data/gr9.h"
#include "data/gr10.h"
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
    data::GR4 mGr4;
    data::GR5 mGr5;
    data::GR6 mGr6;
    data::GR12 mGr12;

    //B
    data::GR8 mGr8;
    data::GR9 mGr9;
    data::GR10 mGr10;
    data::GR13 mGr13;
private:
    CpuMemory();
    CpuMemory( CpuMemory const& ) = delete;
    CpuMemory& operator = ( CpuMemory const& ) = delete;
};

}//namespace cpu
#endif
