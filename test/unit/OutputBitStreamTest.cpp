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

    REQUIRE(stream->write<int>(10));
    REQUIRE(stream->write<int>(-20));

    uint32_t* buffer = stream->getBuffer();

    REQUIRE(buffer[0] == 10);
    REQUIRE(buffer[1] == -20);

    delete stream;
}

TEST_CASE("OutputBitStream can write 16-bit integers", "[OutputBitStream]") {

    OutputBitStream *stream = new OutputBitStream(sizeof(int16_t) * 2);

    REQUIRE(stream->write<short>(10));
    REQUIRE(stream->write<short>(-20));

    uint32_t* buffer = stream->getBuffer();

    REQUIRE((short)(buffer[0] & 0x0000ffff) == 10);
    REQUIRE((short)(buffer[0] >> 16) == -20);

    delete stream;
}

TEST_CASE("OutputBitStream can write bytes", "[OutputBitStream]") {

    OutputBitStream *stream = new OutputBitStream(sizeof(uint8_t) * 2);

    REQUIRE(stream->write<unsigned char>(10));
    REQUIRE(stream->write<unsigned char>(30));
    
    stream->flush();

    uint32_t* buffer = stream->getBuffer();

    REQUIRE((uint8_t)(buffer[0] & 0x000000ff) == 10);
    REQUIRE((uint8_t)(buffer[0] >> 8) == 30);

    delete stream;
}

TEST_CASE("OutputBitStream can write boolean values", "[OutputBitStream]") {

    OutputBitStream *stream = new OutputBitStream(sizeof(bool) * 2);

    REQUIRE(stream->write<bool>(true));
    REQUIRE(stream->write<bool>(false));
    REQUIRE(stream->write<bool>(false));
    REQUIRE(stream->write<bool>(true));
    
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

    REQUIRE(stream->write<float>(10.05f));
    REQUIRE(stream->write<float>(-20.02f));

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

TEST_CASE("Cannot write out of OutputBitStream buffer bounds", "[InputBitStream]") {
    int32_t buffer[] = {10, -20};

    OutputBitStream *stream = new OutputBitStream(8);

    REQUIRE(stream->write<int>(10));
    REQUIRE(stream->write<int>(-20));

    CHECK_THROWS(stream->write<int>(12312));
    CHECK_THROWS(stream->write<bool>(true));
}