#pragma once

#include "State.h"
#include "Bot.h"

class MiniMaxAgent : public Bot {
private:
    State state;

    int calculate(const State&, int, int, int, int(const State&, BoardStatus, int depth), int);

    static int evaluate1(const State&, BoardStatus, int);

    static int evaluate2(const State&, BoardStatus, int);

    Position findNextMoveWithTimeLimit(int (* evaluation)(const State&, BoardStatus, int depth), int timeLimit);

public:
    static const int id = 1;

    int getId() {
        return id;
    }

    MiniMaxAgent() = default;

    void init(const State&) final;

    Position choseBestMove(int) final;

    void performMove(Position) final;

    void resetGame() final;

    void setState(const State&) final;

    void setAllPossibleMoves(const std::vector<Position>&) final;
};
