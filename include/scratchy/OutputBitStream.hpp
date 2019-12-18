#pragma once
#include <cstdint>
#include <iostream>

#include <scratchy/BitMask.hpp>

class OutputBitStream {

    public:

        OutputBitStream(uint32_t size);
        ~OutputBitStream();

        template <class T> 
        bool write(const T input);

        uint32_t *getBuffer();
        uint32_t getBufferSize();

        void flush();
    
    private:
        uint64_t scratching = 0;
        int scratching_bits = 0;
        int word_index = 0;
        uint32_t *buffer;
        uint32_t buffer_size;
        uint32_t bits_written = 0;
        uint32_t total_bits;

        void scratch();

};