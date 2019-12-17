#include <catch2/catch.hpp>
#include <scratchy/InputBitStream.hpp>

TEST_CASE("InputBitStream can read 32-bit integers", "[InputBitStream]") {
    int32_t buffer[] = {10, -20};

    InputBitStream *stream = new InputBitStream(buffer, 8);

    REQUIRE(stream->readInt() == 10);
    REQUIRE(stream->readInt() == -20);
}

TEST_CASE("InputBitStream can read 16-bit integers", "[InputBitStream]") {
    int16_t buffer[] = {10, -20};

    InputBitStream *stream = new InputBitStream(buffer, 4);

    REQUIRE(stream->readShort() == 10);
    REQUIRE(stream->readShort() == -20);
}

TEST_CASE("InputBitStream can read bytes", "[InputBitStream]") {
    uint8_t buffer[] = {10, 20};

    InputBitStream *stream = new InputBitStream(buffer, 2);

    REQUIRE(stream->readByte() == 10);
    REQUIRE(stream->readByte() == 20);
}

TEST_CASE("InputBitStream can read 32-bit floats", "[InputBitStream]") {
    float buffer[] = {10.05f, 20.02f};

    InputBitStream *stream = new InputBitStream(buffer, 8);

    REQUIRE(stream->readFloat() == 10.05f);
    REQUIRE(stream->readFloat() == 20.02f);
}

TEST_CASE("InputBitStream can read bool values", "[InputBitStream]") {
    uint8_t buffer[] = {0b11001};

    InputBitStream *stream = new InputBitStream(buffer, 1);

    REQUIRE(stream->readBool());
    REQUIRE_FALSE(stream->readBool());
    REQUIRE_FALSE(stream->readBool());
    REQUIRE(stream->readBool());
    REQUIRE(stream->readBool());
}