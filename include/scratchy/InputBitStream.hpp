#pragma once
#include <cstdint>
#include <limits>

#include <scratchy/BitMask.hpp>

class InputBitStream {

public:

    InputBitStream(const void *buffer, uint32_t buffer_size);

    template <class T> 
    T read();
    
private:
    uint64_t scratching = 0;
    int scratching_bits = 0;
    int word_index = 0;
    const uint32_t *buffer;
    int total_bits;
    int num_bits_read = 0;
    uint32_t buffer_size;

    void scratch(uint32_t bits);    
};