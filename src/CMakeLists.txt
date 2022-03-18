project(lib)

set(SOURCES State.cpp Other.cpp
        Node.cpp UCT.cpp MCTS.cpp)

add_library(lib ${SOURCES})