cmake_minimum_required(VERSION 3.0.0)
project(scratchy VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include_directories(./include)

set(
    SOURCE_FILES
    ./src/BitWriter.cpp ./src/BitReader.cpp
)

add_library(
    scratchy STATIC
    ${SOURCE_FILES}
)

target_include_directories(
    scratchy 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(CTest)
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/third_party/catch/contrib")

    add_subdirectory(third_party/catch)
    add_executable(test_main test/test.cpp)
    target_link_libraries(test_main Catch2::Catch2 scratchy)

    include(Catch)
    catch_discover_tests(test_main)
endif()