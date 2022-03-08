project(lib)

set(SOURCES Board.cpp MCTS.cpp MiniMax.cpp Node.cpp Other.cpp State.cpp UCT.cpp)

add_library(lib ${SOURCES})