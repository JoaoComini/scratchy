#include <catch2/catch.hpp>
#include <scratchy/InputBitStream.hpp>

TEST_CASE("InputBitStream can read 32-bit integers", "[InputBitStream]") {
    int32_t buffer[] = {10, -20};

    InputBitStream *stream = new InputBitStream(buffer, 8);

    REQUIRE(stream->read<int>() == 10);
    REQUIRE(stream->read<int>() == -20);
}

TEST_CASE("InputBitStream can read 16-bit integers", "[InputBitStream]") {
    int16_t buffer[] = {10, -20};

    InputBitStream *stream = new InputBitStream(buffer, 4);

    REQUIRE(stream->read<short>() == 10);
    REQUIRE(stream->read<short>() == -20);
}

TEST_CASE("InputBitStream can read bytes", "[InputBitStream]") {
    uint8_t buffer[] = {10, 20};

    InputBitStream *stream = new InputBitStream(buffer, 2);

    REQUIRE(stream->read<uint8_t>() == 10);
    REQUIRE(stream->read<uint8_t>() == 20);
}

TEST_CASE("InputBitStream can read 32-bit floats", "[InputBitStream]") {
    float buffer[] = {10.05f, 20.02f};

    InputBitStream *stream = new InputBitStream(buffer, 8);

    REQUIRE(stream->read<float>() == 10.05f);
    REQUIRE(stream->read<float>() == 20.02f);
}

TEST_CASE("InputBitStream can read bool values", "[InputBitStream]") {
    uint8_t buffer[] = {0b11001};

    InputBitStream *stream = new InputBitStream(buffer, 1);

    REQUIRE(stream->read<bool>());
    REQUIRE_FALSE(stream->read<bool>());
    REQUIRE_FALSE(stream->read<bool>());
    REQUIRE(stream->read<bool>());
    REQUIRE(stream->read<bool>());
}

TEST_CASE("Cannot read out of InputBitStream buffer bounds", "[InputBitStream]") {
    int32_t buffer[] = {10, -20};

    InputBitStream *stream = new InputBitStream(buffer, 8);

    REQUIRE(stream->read<int>() == 10);
    REQUIRE(stream->read<int>() == -20);

    CHECK_THROWS(stream->read<int>());
    CHECK_THROWS(stream->read<bool>());
}