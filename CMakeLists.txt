project(TicTacToe)

cmake_minimum_required(VERSION 3.21)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES main.cpp)

add_executable(main ${SOURCES})

include_directories(include)
add_subdirectory(src)

target_link_libraries(main lib)

find_package(GTest REQUIRED CONFIG)

#include_directories("/usr/local/include/")
set(TestSources tests/main_test.cpp tests/board_tests.cpp)

add_executable(CTest ${TestSources})
target_link_libraries(CTest PUBLIC lib GTest::gtest GTest::gtest_main)
target_link_libraries(CTest PUBLIC GTest::gmock GTest::gmock_main)
include(GoogleTest)
gtest_discover_tests(CTest)