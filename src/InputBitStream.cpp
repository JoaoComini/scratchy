#include <scratchy/InputBitStream.hpp>

InputBitStream::InputBitStream(const void *buffer, uint32_t buffer_size): 
        buffer(reinterpret_cast<const uint32_t *>(buffer)), 
        buffer_size(buffer_size) {
            
        this->total_bits = buffer_size * 8;
}

template <class T> 
T InputBitStream::read()
{
    if (this->num_bits_read + BitMask<T>::type_size > this->total_bits) {
        throw "Reading out of buffer bounds";
    }

    this->scratch(BitMask<T>::type_size);

    T value = this->scratching & BitMask<T>::value;

    this->scratching >>= BitMask<T>::type_size;
    this->scratching_bits -= BitMask<T>::type_size;
    
    this->num_bits_read += BitMask<T>::type_size;

    return value;
}

template <> 
float InputBitStream::read()
{
    union FloatInt
    {
        float float_value;
        int32_t int_value;
    };

    FloatInt tmp;

    tmp.int_value = (int32_t) this->read<int>();

    return tmp.float_value;
}


template <> 
bool InputBitStream::read()
{
    if (this->num_bits_read + 1 > this->total_bits) {
        throw "Reading out of buffer bounds";
    }

    this->scratch(1);
    
    bool value = this->scratching & 0x1;
    
    this->scratching >>= 1;
    this->scratching_bits -= 1;
    this->num_bits_read += 1;

    return value;
}

template int32_t InputBitStream::read();
template uint32_t InputBitStream::read();
template int16_t InputBitStream::read();
template uint16_t InputBitStream::read();
template int8_t InputBitStream::read();
template uint8_t InputBitStream::read();

void InputBitStream::scratch(uint32_t bits)
{
    if (this->scratching_bits >= bits) {
        return;
    }

    this->scratching |= static_cast<uint64_t>(this->buffer[word_index++]) << this->scratching_bits; 
    this->scratching_bits += 32;
}
