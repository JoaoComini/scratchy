cmake_minimum_required(VERSION 3.0.0)
project(scratchy VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/third_party/cotire/CMake")

include(cotire)
include(GNUInstallDirs)

include_directories("./include")

set(
    SOURCE_FILES
    "./src/OutputBitStream.cpp"
    "./src/InputBitStream.cpp"
)

set(
    HEADER_FILES
    "./include/scratchy/OutputBitStream.hpp"
    "./include/scratchy/InputBitStream.hpp"
    "./include/scratchy/BitMask.hpp"
)

add_library(
    scratchy 
    STATIC
    "${SOURCE_FILES}"
)

target_compile_options(scratchy PRIVATE -Werror)
target_compile_features(scratchy PRIVATE cxx_std_11)

target_include_directories(
    scratchy PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(
    TARGETS scratchy
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

install(
    DIRECTORY "include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

cotire(scratchy)

option(ENABLE_COVERAGE "Enables gcov code coverage" OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)

    if (ENABLE_COVERAGE)
        SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
        SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

        SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
        SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
    endif()

    add_subdirectory(third_party/catch)

    set(
        TEST_SOURCE_FILES
        "test/test_main.cpp"
        "test/unit/InputBitStreamTest.cpp"
        "test/unit/OutputBitStreamTest.cpp"
        "test/feature/SerializationTest.cpp"
    )

    add_executable(
        test_main
        "${TEST_SOURCE_FILES}"
    )

    target_link_libraries(test_main PRIVATE Catch2::Catch2 scratchy)
endif()
