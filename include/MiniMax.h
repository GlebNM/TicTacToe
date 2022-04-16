#pragma once

#include "Node.h"

class minimax {
public:
    static Position findNextMove(const Board &, int (const Board &, int, int, int), int);

    static int calculate(Board, int, int, int, int, int(const Board &, int, int, int), int);

    static int evaluate1(const Board &, int, int, int);

    static int evaluate2(const Board &, int, int, int);

    static Position
    findNextMoveWithTimeLimit(const Board &board, int (*evaluation)(const Board &, int, int, int), int timeLimit);
};
