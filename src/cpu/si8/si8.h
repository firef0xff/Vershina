#pragma once
#ifndef si8H
#define si8H

#include <stdint.h>

namespace cpu
{
namespace data
{

class SI8
{
public:
   SI8( uint8_t endpoint );

   bool IsConnected();

   int32_t DCNT() const; //Считать показания счетчика импульсов
   float F_DCNT() const;
   int32_t DSPD() const; //Считать показания расходомера
   uint32_t DTMR() const; //Считать показания таймера (мсек)

private:
   uint8_t mEndpoint;
};

}
}

#endif // SI8_H
