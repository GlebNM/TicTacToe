#pragma once

#include "State.h"
#include "Bot.h"

class MiniMaxAgent : public Bot {
private:
    State state;
public:

    MiniMaxAgent() = default;

    int calculate(const State&, int, int, int, int, int(const State&, int, int, int), int);

    int evaluate1(const State&, BoardStatus, int, int);

    int evaluate2(const State&, BoardStatus, int, int);

    Position
    findNextMoveWithTimeLimit(int (* evaluation)(const State&, int, int, int), int timeLimit);

    void init(const State&) final;

    Position choseBestMove(int) final;

    void performMove(Position) final;

    void resetGame() final;

    void setState(const State&) final;

    void setAllPossibleMoves(const std::vector<Position>&) final;
};
