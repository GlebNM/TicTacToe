project(TicTacToe)

cmake_minimum_required(VERSION 3.21)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -Wextra -fsanitize=address -fsanitize=leak")

option(ENABLE_TESTING "enable google tests" ON)
option(ENABLE_BENCHMARK "enable google benchmark" OFF)

set(SOURCES main.cpp)

add_executable(main ${SOURCES})

include_directories(include)
add_subdirectory(src)

target_link_libraries(main lib)

if(ENABLE_TESTING)
    enable_testing()
    set(TestSources tests/main_test.cpp tests/board_tests.cpp)
    find_package(GTest CONFIG)
    if (GTest_FOUND)
        message("GTest found locally.")
        add_executable(CTest ${TestSources})
        target_link_libraries(CTest PUBLIC lib GTest::gtest GTest::gtest_main)
        target_link_libraries(CTest PUBLIC GTest::gmock GTest::gmock_main)
        include(GoogleTest)
        gtest_discover_tests(CTest)
    else()
        message("GTest not found locally. Downloading from repo ...")
        include(FetchContent)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        release-1.11.0
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)

        add_executable(CTest ${TestSources})
        target_link_libraries(CTest PUBLIC lib gtest gtest_main)
        target_link_libraries(CTest PUBLIC gmock gmock_main)
        include(GoogleTest)
        gtest_discover_tests(CTest)
    endif()
endif()

if(ENABLE_BENCHMARK)
    add_executable(bench ${CMAKE_SOURCE_DIR}/benchmark_files/main_bench.cpp)

    add_subdirectory(${CMAKE_SOURCE_DIR}/benchmark)

    target_link_libraries(bench lib)
    target_link_libraries(bench benchmark::benchmark)
endif()
