#include <scratchy/OutputBitStream.hpp>

OutputBitStream::OutputBitStream(uint32_t buffer_size)
{
    this->buffer_size = ((buffer_size + 3) & ~0x03);

    this->buffer = new uint32_t[this->buffer_size / 4];
}

OutputBitStream::~OutputBitStream()
{
    delete [] this->buffer;
}

bool OutputBitStream::writeBool(const bool input)
{
    this->scratching |= static_cast<uint64_t>(input & 0b1) << this->scratching_bits;
    this->scratching_bits += 1;
    
    this->scratch();

    return true;
}

bool OutputBitStream::writeByte(const uint8_t input)
{
    this->scratching |= static_cast<uint64_t>(input & 0xFF) << this->scratching_bits;
    this->scratching_bits += 8;
    
    this->scratch();

    return true;
}

bool OutputBitStream::writeInt(const int32_t input)
{
    this->scratching |= static_cast<uint64_t>(input & 0xFFFFFFFF) << this->scratching_bits;
    this->scratching_bits += 32;
    
    this->scratch();

    return true;
}


bool OutputBitStream::writeShort(const int16_t input)
{
    this->scratching |= static_cast<uint64_t>(input & 0xFFFF) << this->scratching_bits;
    this->scratching_bits += 16;
    
    this->scratch();

    return true;
}


bool OutputBitStream::writeFloat(float input) 
{

    union FloatInt
    {
        float float_value;
        uint32_t int_value;
    };

    FloatInt tmp;

    tmp.float_value = input;

    return this->writeInt(tmp.int_value);
}

uint32_t * OutputBitStream::getBuffer()
{
    return this->buffer;
}

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

uint32_t OutputBitStream::getBufferSize()
{
    return this->buffer_size;
}

