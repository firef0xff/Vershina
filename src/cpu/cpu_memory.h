#pragma once
#ifndef cpu_memoryH
#define cpu_memoryH

#include "data/gr1.h"
#include "data/gr2.h"
#include "data/gr3.h"
#include "data/gr4.h"
#include "data/gr5.h"
#include "data/gr6.h"
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
    data::GR4 mGr4;
    data::GR5 mGr5;
    data::GR6 mGr6;
private:
    CpuMemory();
    CpuMemory( CpuMemory const& ) = delete;
    CpuMemory& operator = ( CpuMemory const& ) = delete;
};

}//namespace cpu
#endif
