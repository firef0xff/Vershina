#include "serialize.h"

namespace serialize
{
void Write(FILE *fp, uint8_t const* data, size_t size )
{
   fwrite(data, sizeof(uint8_t), size, fp);
}
void Read(FILE *fp, uint8_t* data, size_t size )
{
   fread(data, sizeof(uint8_t), size, fp);
}

template<>
void Write(FILE *fp, std::string const& data)
{
   uint16_t size = static_cast<uint16_t>( data.size() );
   fwrite(&size, sizeof(uint16_t), 1, fp);
   fwrite( data.c_str(), sizeof(std::string::value_type), size, fp );
}

template<>
void Read(FILE *fp, std::string& data)
{
   uint16_t size = 0;
   fread(&size, sizeof(uint16_t), 1, fp);
   data.resize(size);
   fread(const_cast<char*>( data.data() ), sizeof(std::string::value_type), size, fp);
}

}
