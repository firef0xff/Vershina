#ifndef log_implH
#define log_implH
#pragma once
#ifdef WINDOWS
#include <Comctrls.hpp>

void  LogPrint( String Mess, TColor wcl = clWhite);
void InitLogger( TRichEdit *pLog ); // указатель на компонент для вывода протокола

#endif
#endif // LOG_IMPL_H
