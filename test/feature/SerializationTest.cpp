#include <catch2/catch.hpp>
#include <scratchy/scratchy.h>

TEST_CASE("InputBitStream can read a buffer written by an OutputBitStream", "[Serialization]") {
    
    OutputBitStream* outputBitStream = new OutputBitStream(256);

    outputBitStream->write<int>(1127310);
    outputBitStream->write<short>(7566);
    outputBitStream->write<bool>(true); 
    outputBitStream->write<unsigned char>(152);
    outputBitStream->write<bool>(false);
    outputBitStream->write<short>(1566);
    outputBitStream->write<float>(3578.02f);

    outputBitStream->flush();

    uint32_t* buffer = outputBitStream->getBuffer();

    InputBitStream* inputBitStream = new InputBitStream(buffer, 256);

    CHECK(inputBitStream->read<int>() == 1127310);
    CHECK(inputBitStream->read<short>() == 7566);
    CHECK(inputBitStream->read<bool>());
    CHECK(inputBitStream->read<uint8_t>() == 152);
    CHECK_FALSE(inputBitStream->read<bool>());
    CHECK(inputBitStream->read<short>() == 1566);
    CHECK(inputBitStream->read<float>() == 3578.02f);

    delete outputBitStream;
    delete inputBitStream;
}