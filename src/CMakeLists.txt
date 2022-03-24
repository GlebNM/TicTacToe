project(lib)

set(SOURCES State.cpp Other.cpp
        Node.cpp UCT.cpp MCTSAgent.cpp Bot.cpp)

add_library(lib ${SOURCES})