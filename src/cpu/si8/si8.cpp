#include "si8.h"
#include "funcs/owen_read.h"
#include "types/owen_int_types.h"
#include "types/owen_time.h"
#include "owen_paskage.h"
#include "COMPort/ComPort.h"

#include <mutex>
#include <chrono>
#include <thread>
#include <cmath>

#include "../../def.h"

namespace cpu
{
namespace data
{

namespace
{

static std::recursive_mutex MUTEX;
class Connection
{
public:
   ~Connection()
   {}

   static Connection& Instance()
   {
	  static Connection c;
      return c;
   }

   COMPort* GetPort()
   {
      if ( !mPort )
         Connect();
      return mPort.get();
   }

private:
   Connection()
   {
      mAddr = SI8_PORT;
   }
   Connection( Connection const& ) = delete;
   Connection& operator = ( Connection const& ) = delete;

   void Connect()
   {
      std::lock_guard< std::recursive_mutex > lock( MUTEX );
      try
      {
         mPort.reset();
         //подготовка  таймаутов
         std::unique_ptr< COMMTIMEOUTS > TimeOuts ( new COMMTIMEOUTS() );
         TimeOuts->ReadIntervalTimeout = 20;
         TimeOuts->ReadTotalTimeoutMultiplier = 1;
         TimeOuts->ReadTotalTimeoutConstant = 315;
         TimeOuts->WriteTotalTimeoutMultiplier = 1;
         TimeOuts->WriteTotalTimeoutConstant =315;

         mPort.reset(new COMPort( mAddr, std::move( TimeOuts ), COMPort::CommMasks::ev_rxchar, 4096, 2048 )  );

         //корректировка настроек порта DCB

         std::unique_ptr< DCB> settings = mPort->Get_port_Settings();
         settings->BaudRate =COMPort::BaudRates::BR_9600;
         settings->ByteSize = 7;
         settings->Parity = COMPort::Paritys::NOparity;
         settings->StopBits = COMPort::StopBits::TWO;
         settings->fAbortOnError = FALSE;
         settings->fDtrControl = DTR_CONTROL_DISABLE;
         settings->fRtsControl = RTS_CONTROL_ENABLE;
         settings->fBinary = TRUE;
         settings->fParity = COMPort::fParitys::OFF;
         settings->fInX = FALSE;
         settings->fOutX = FALSE;
         settings->XonChar = (BYTE)0x11;
         settings->XoffChar = (BYTE)0x13;
         settings->fErrorChar = FALSE;
         settings->fNull = FALSE;
         settings->fOutxCtsFlow = FALSE;
         settings->fOutxDsrFlow = FALSE;
         settings->XonLim = 1024;
         settings->XoffLim = 1024;
         settings->fDsrSensitivity=FALSE;
         mPort->Set_DCB_Settings( std::move( settings ) );
      }
      catch(...)
      {
      }
   }

   std::unique_ptr<COMPort> mPort;
   std::string mAddr;
};

bool SendCommand( owen::Command& cmd, uint8_t endpoint )
{
   std::lock_guard< std::recursive_mutex > lock( MUTEX );
   COMPort* port = Connection::Instance().GetPort();
   if ( !port )
      return false;

   owen::Paskage pkg( endpoint, cmd );
   port->Clear_Com_Buff(	COMPort::Purge_flags::TXABORT|
                           COMPort::Purge_flags::RXABORT|
                           COMPort::Purge_flags::TXCLEAR|
                           COMPort::Purge_flags::RXCLEAR);

   port->RTS_On(0,20);
   port->RTS_oFF();
   port->Write( pkg.Data(), pkg.Size() );

   const int len = 1096;
   char buff[len] = {0};
   char* p_buff = &buff[0];
   size_t remain_len = len;
   size_t total_readed = 0;
   bool done = false;
   std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
   do
   {
       size_t readed = port->Read( reinterpret_cast<BYTE*>( p_buff ), remain_len );
       total_readed += readed;
       remain_len -= readed;
       for( size_t i = 0; i < readed; ++i )
          if ( p_buff[i] == 0x0d )
            done = true;
       p_buff += readed;
       std::this_thread::sleep_for( std::chrono::milliseconds(20) );
       std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
       if ( (now - std::chrono::seconds(1)) > start )
          break;
   }
   while( !done && remain_len );
   if (done)
   {
      pkg.SetResponce( reinterpret_cast<uint8_t*>( buff ), len - remain_len );
   }
   return done;
}

}

SI8::SI8( uint8_t endpoint ):
   mEndpoint( endpoint )
{}

bool SI8::IsConnected()
{
   return Connection::Instance().GetPort() != nullptr;
}

int32_t SI8::DCNT() const
{
   owen::SI8BCD res;
   owen::Read cmd( "DCNT", res );
   SendCommand( cmd, mEndpoint );
   return res.Data();
}
float SI8::F_DCNT() const
{
    int res = DCNT();
	if (!res)
	{
		return 0.0;
	}

	int pos = res; //число символов после запятой
	int num = 0; //количество символов значащей части
	while ( pos > 10 )
	{
		pos /= 10;
		++num;
	}

	res -= pos * pow( 10, num );
	int c = res /pow(10, pos);
	res -= c * pow(10, pos);
	float result = c + static_cast<float>( res )/pow(10, pos);
    return result;
}
int32_t SI8::DSPD() const
{
   owen::SI8BCD res;
   owen::Read cmd( "DSPD", res );
   SendCommand( cmd, mEndpoint );
   return res.Data();
}
uint32_t SI8::DTMR() const
{
   owen::DTMR res;
   owen::Read cmd( "DTMR", res );
   SendCommand( cmd, mEndpoint );

   uint32_t to_ret = res.MSec();
   to_ret += res.Sec() * 1000;
   to_ret += res.Min() * 60 * 1000;
   to_ret += res.Hour() * 60 * 60 * 1000;

   return to_ret;
}

}
}
