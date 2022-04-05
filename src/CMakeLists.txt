project(lib)

set(SOURCES State.cpp Other.cpp
        Node.cpp UCT.cpp MCTSAgent.cpp Bot.cpp MiniMax.cpp)

add_library(lib ${SOURCES})

if(TEST_COVERAGE)
        set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
        include(CodeCoverage)
        append_coverage_compiler_flags()
endif()