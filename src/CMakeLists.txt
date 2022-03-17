project(lib)

set(SOURCES NewState.cpp NewOther.cpp
        NewNode.cpp NewUCT.cpp NewMCTS.cpp)

add_library(lib ${SOURCES})