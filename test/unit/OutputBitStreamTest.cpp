#include <catch2/catch.hpp>
#include <scratchy/OutputBitStream.hpp>

TEST_CASE("OutputBitStream buffer size is always set to a mutiple of sizeof(uint32_t)", "[OutputBitStream]") {

    OutputBitStream *stream = new OutputBitStream(2);

    REQUIRE(! (stream->getBufferSize() % sizeof(uint32_t)));

    delete stream;

    stream = new OutputBitStream(13);

    REQUIRE(! (stream->getBufferSize() % sizeof(uint32_t)));

    delete stream;

    stream = new OutputBitStream(243);

    REQUIRE(! (stream->getBufferSize() % sizeof(uint32_t)));

    delete stream;
}

TEST_CASE("OutputBitStream can write 32-bit integers", "[OutputBitStream]") {

    OutputBitStream *stream = new OutputBitStream(sizeof(int32_t) * 2);

    REQUIRE(stream->writeInt(10));
    REQUIRE(stream->writeInt(-20));

    uint32_t* buffer = stream->getBuffer();

    REQUIRE(buffer[0] == 10);
    REQUIRE(buffer[1] == -20);

    delete stream;
}

TEST_CASE("OutputBitStream can write 16-bit integers", "[OutputBitStream]") {

    OutputBitStream *stream = new OutputBitStream(sizeof(int16_t) * 2);

    REQUIRE(stream->writeShort(10));
    REQUIRE(stream->writeShort(-20));

    uint32_t* buffer = stream->getBuffer();

    REQUIRE((short)(buffer[0] & 0x0000ffff) == 10);
    REQUIRE((short)(buffer[0] >> 16) == -20);

    delete stream;
}

TEST_CASE("OutputBitStream can write bytes", "[OutputBitStream]") {

    OutputBitStream *stream = new OutputBitStream(sizeof(uint8_t) * 2);

    REQUIRE(stream->writeByte(10));
    REQUIRE(stream->writeByte(30));
    
    stream->flush();

    uint32_t* buffer = stream->getBuffer();

    REQUIRE((uint8_t)(buffer[0] & 0x000000ff) == 10);
    REQUIRE((uint8_t)(buffer[0] >> 8) == 30);

    delete stream;
}

TEST_CASE("OutputBitStream can write boolean values", "[OutputBitStream]") {

    OutputBitStream *stream = new OutputBitStream(sizeof(bool) * 2);

    REQUIRE(stream->writeBool(true));
    REQUIRE(stream->writeBool(false));
    REQUIRE(stream->writeBool(false));
    REQUIRE(stream->writeBool(true));
    
    stream->flush();

    uint32_t* buffer = stream->getBuffer();

    REQUIRE((buffer[0] & 0b1));
    REQUIRE(! ((buffer[0] >> 1) & 0b1));
    REQUIRE(! ((buffer[0] >> 2) & 0b1));
    REQUIRE(((buffer[0] >> 3) & 0b1));

    delete stream;
}

TEST_CASE("OutputBitStream can write 32-bit floats", "[OutputBitStream]") {

    OutputBitStream *stream = new OutputBitStream(sizeof(float) * 2);

    REQUIRE(stream->writeFloat(10.05f));
    REQUIRE(stream->writeFloat(-20.02f));

    uint32_t* buffer = stream->getBuffer();

    union FloatInt
    {
        float float_value;
        uint32_t int_value;
    };

    FloatInt tmp;

    tmp.int_value = buffer[0];
    REQUIRE(tmp.float_value == 10.05f);

    tmp.int_value = buffer[1];
    REQUIRE(tmp.float_value == -20.02f);

    delete stream;
}