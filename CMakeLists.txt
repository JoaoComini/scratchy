cmake_minimum_required(VERSION 3.0.0)
project(scratchy VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

include(cotire)

include_directories(include)

set(
    SOURCE_FILES
    ./src/OutputBitStream.cpp ./src/InputBitStream.cpp
)

add_library(
    scratchy STATIC
    ${SOURCE_FILES}
)

target_include_directories(
    scratchy 
    PUBLIC 
    include
)

cotire(scratchy)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)

    SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
    SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
    SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

    add_subdirectory(third_party/catch)

    add_executable(
        test_main
        test/test_main.cpp
        test/unit/InputBitStreamTest.cpp
        test/unit/OutputBitStreamTest.cpp
        test/feature/StreamingTest.cpp
    )

    target_link_libraries(test_main Catch2::Catch2 scratchy)
endif()