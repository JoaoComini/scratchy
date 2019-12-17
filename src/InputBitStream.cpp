#include <scratchy/InputBitStream.hpp>

InputBitStream::InputBitStream(const void *buffer, uint32_t buffer_size): 
        buffer(reinterpret_cast<const uint32_t *>(buffer)), 
        buffer_size(buffer_size) {
            
        this->total_bits = buffer_size * 8;
}

bool InputBitStream::readBool()
{
    if (this->scratching_bits < 1) {
        this->scratch();
    }
    
    int value = this->scratching & 0x1;
    
    this->scratching >>= 1;
    this->scratching_bits -= 1;

    return value;
}

uint8_t InputBitStream::readByte()
{
     if (this->scratching_bits < 8) {
        this->scratch();
     }

    uint8_t value = this->scratching & 0xFF;

    this->scratching >>= 8;
    this->scratching_bits -= 8;

    return value;
}

int32_t InputBitStream::readInt()
{
    if (this->scratching_bits < 32) {
        this->scratch();
    }

    int32_t value = this->scratching & 0xFFFFFFFF;

    this->scratching >>= 32;
    this->scratching_bits -= 32;

    return value;
}

int16_t InputBitStream::readShort()
{
    if (this->scratching_bits < 16) {
        this->scratch();
    }

    int16_t value = this->scratching & 0xFFFF;

    this->scratching >>= 16;
    this->scratching_bits -= 16;

    return value;
}

float InputBitStream::readFloat()
{
    union FloatInt
    {
        float float_value;
        uint32_t int_value;
    };

    FloatInt tmp;

    tmp.int_value = (uint32_t) this->readInt();

    return tmp.float_value;
}

void InputBitStream::scratch()
{
    #ifdef LITTLE_ENDIAN
    this->scratching |= static_cast<uint64_t>(this->buffer[word_index++]) << this->scratching_bits; 
    #else
    this->scratching |= static_cast<uint64_t>(__bswap_32(this->buffer[word_index++])) << this->scratching_bits; 
    #endif

    this->scratching_bits += 32;
}
