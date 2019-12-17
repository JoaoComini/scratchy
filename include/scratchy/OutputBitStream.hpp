#pragma once
#include <cstdint>
#include <iostream>

class OutputBitStream {

    public:

        OutputBitStream(uint32_t size);
        ~OutputBitStream();

        bool writeBool(const bool input);
        bool writeByte(const uint8_t input);
        bool writeInt(const int32_t input);
        bool writeShort(const int16_t input);
        bool writeFloat(const float input);
        uint32_t *getBuffer();
        uint32_t getBufferSize();

        void flush();
    
    private:
        uint64_t scratching = 0x0;
        int scratching_bits = 0x0;
        int word_index = 0x0;
        uint32_t *buffer;
        uint32_t buffer_size;

        void scratch();

};