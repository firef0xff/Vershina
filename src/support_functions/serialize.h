#ifndef serializeH
#define serializeH
#pragma once
#include <stdio.h>
#include <string>

namespace serialize
{

void Write(FILE *fp, uint8_t const* data, size_t size );
void Read(FILE *fp, uint8_t* data, size_t size );

template<class T>
void Write(FILE *fp, T const& data)
{
   Write( fp, reinterpret_cast<uint8_t const* >( &data ), sizeof(T) );
}

template<class T>
void Read(FILE *fp, T& data)
{
   Read( fp, reinterpret_cast<uint8_t* >( &data ), sizeof(T) );
}

template<>
void Write(FILE *fp, std::string const& data);
template<>
void Read(FILE *fp, std::string& data);

}

#endif // SERIALISE_H
