#pragma once

#include "State.h"
#include<vector>

class Bot {
public:
    virtual void init(const State&) = 0;

    virtual Position choseBestMove(int) = 0;

    virtual void performMove(Position) = 0;

    virtual void resetGame() = 0;

    virtual void setState(const State&) = 0;

    virtual void setAllPossibleMoves(const std::vector<Position>&) = 0;

    virtual int getId() = 0;
};
