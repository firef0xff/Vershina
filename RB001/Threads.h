//---------------------------------------------------------------------------

#ifndef ThreadsH
#define ThreadsH
#include <Windows.h>
//---------------------------------------------------------------------------
extern bool CD_reset1;
extern bool CD_reset2;
unsigned long __stdcall ListenCD9904(void *msg);
#endif
