#pragma once
#ifndef cpu_memoryH
#define cpu_memoryH

#include "data/gr1.h"
#include "data/gr2.h"
namespace cpu
{

class CpuMemory
{
public:
    ~CpuMemory();
    static CpuMemory& Instance();

    data::GR1 mGr1;
    data::GR2 mGr2;
private:
    CpuMemory();
    CpuMemory( CpuMemory const& ) = delete;
    CpuMemory& operator = ( CpuMemory const& ) = delete;
};

}//namespace cpu
#endif
