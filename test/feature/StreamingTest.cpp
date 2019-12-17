#include <catch2/catch.hpp>
#include <scratchy/InputBitStream.hpp>
#include <scratchy/OutputBitStream.hpp>

TEST_CASE("InputBitStream can read a buffer written by an OutputBitStream", "[Streaming]") {
    
    OutputBitStream* outputBitStream = new OutputBitStream(256);

    outputBitStream->writeInt(1127310);
    outputBitStream->writeShort(7566);
    outputBitStream->writeBool(true); 
    outputBitStream->writeByte(152);
    outputBitStream->writeBool(false);
    outputBitStream->writeShort(1566);
    outputBitStream->writeFloat(3578.02f);

    outputBitStream->flush();

    uint32_t* buffer = outputBitStream->getBuffer();

    InputBitStream* inputBitStream = new InputBitStream(buffer, 256);

    CHECK(inputBitStream->readInt() == 1127310);
    CHECK(inputBitStream->readShort() == 7566);
    CHECK(inputBitStream->readBool());
    CHECK(inputBitStream->readByte() == 152);
    CHECK_FALSE(inputBitStream->readBool());
    CHECK(inputBitStream->readShort() == 1566);
    CHECK(inputBitStream->readFloat() == 3578.02f);

    delete outputBitStream;
    delete inputBitStream;
}