#include <scratchy/OutputBitStream.hpp>

OutputBitStream::OutputBitStream(uint32_t buffer_size)
{
    this->buffer_size = ((buffer_size + 3) & ~0x03);

    this->total_bits = buffer_size * 8;

    this->buffer = new uint32_t[this->buffer_size / 4];
}

OutputBitStream::~OutputBitStream()
{
    delete [] this->buffer;
}

template <class T> 
bool OutputBitStream::write(const T input)
{
    if (this->bits_written + BitMask<T>::type_size > this->total_bits) {
        throw "Writing out of buffer bounds";
    }

    this->scratching |= static_cast<uint64_t>(input & BitMask<T>::value) << this->scratching_bits;
    this->scratching_bits += BitMask<T>::type_size;
    this->bits_written += BitMask<T>::type_size;

    this->scratch();

    return true;
}

template <>
bool OutputBitStream::write(const bool input)
{
    if (this->bits_written + 1 > this->total_bits) {
        throw "Writing out of buffer bounds";
    }

    this->scratching |= static_cast<uint64_t>(input & 0b1) << this->scratching_bits;
    this->scratching_bits += 1;
    this->bits_written += 1;

    this->scratch();

    return true;
}

template <>
bool OutputBitStream::write(const float input) 
{
    union FloatInt
    {
        float float_value;
        int32_t int_value;
    };

    FloatInt tmp;

    tmp.float_value = input;

    return this->write<int32_t>(tmp.int_value);
}

template bool OutputBitStream::write(const int32_t input);
template bool OutputBitStream::write(const int16_t input);
template bool OutputBitStream::write(const uint8_t input);

void OutputBitStream::scratch() 
{
    if (this->scratching_bits < 32) {
        return;
    }

    this->buffer[this->word_index++] = this->scratching & 0xFFFFFFFF;
    this->scratching >>= 32;
    this->scratching_bits -= 32;
}

void OutputBitStream::flush() 
{
    this->buffer[this->word_index++] = this->scratching & 0xFFFFFFFF;
    this->scratching >>= this->scratching_bits;
    this->scratching_bits = 0;
}

uint32_t * OutputBitStream::getBuffer()
{
    return this->buffer;
}

uint32_t OutputBitStream::getBufferSize()
{
    return this->buffer_size;
}

