#pragma once
#include <cstdint>
#include <iostream>

class InputBitStream {

public:

    InputBitStream(const void *buffer, uint32_t buffer_size);

    bool readBool();
    uint8_t readByte();
    int16_t readShort();
    int32_t readInt();
    float readFloat();
    
private:
    uint64_t scratching = 0;
    int scratching_bits = 0;
    int word_index = 0;
    const uint32_t *buffer;
    int total_bits = 0;
    int num_bits_read = 0;
    uint32_t buffer_size;

    void scratch();    
};