#pragma once

#include <chrono>

using milliseconds = std::chrono::duration<long long, std::milli>;

struct Position {
    int x;
    int y;

    Position(int _x, int _y) : x(_x), y(_y) {}

    Position getMoved(int changeX, int changeY) {
        return {x + changeX, y + changeY};
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

enum PlayerSymbol {
    XMark,
    OMark,
    Empty
};

enum BoardStatus {
    XWin,
    OWin,
    Draw,
    InProgress
};

int changePlayer(int player);

extern int COMP, OPPONENT, OPPONENT_WIN, COMP_WIN;

const int INF = 1e9 + 7;
const int MAX_DEPTH = 8;
