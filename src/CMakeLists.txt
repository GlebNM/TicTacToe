project(lib)

set(SOURCES NewState.cpp NewOther.cpp Board.cpp MCTS.cpp MiniMax.cpp Node.cpp Other.cpp State.cpp UCT.cpp)

add_library(lib ${SOURCES})