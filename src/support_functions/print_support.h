#ifndef print_supportH
#define print_supportH
#pragma once
#include <Printers.hpp>
#include <string>

class Tyre;

namespace printing
{
   // печать протокола на принтер pprt
   void Print(TPrinter *pprt, Tyre const & data );
}

#endif // PRINTSUPPORT_H
