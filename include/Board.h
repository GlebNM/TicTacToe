#pragma once

#include <vector>
#include "Other.h"

class Board {
private:
    std::vector<std::vector<signed char>> smallField;//81 cells (9x9)
    std::vector<std::vector<signed char>> bigField; //9 areas 3x3 each

    Position lastPosition{-1, -1};

    bool checkWin(int player, const std::vector<std::vector<signed char>> &field, int dX, int dY) const;

    int checkSmallFieldStatus(const Position&);

    int count(const std::vector<std::vector<signed char>> &field, int player, int deltaX, int deltaY) const;

public:

    static const int IN_PROGRESS = -1;
    static const int DRAW = 0;          //end of game description and big field description
//    static const int OPPONENT_WIN = 1;
//    static const int COMP_WIN = 2;

    //static int COMP;          // small field description
    //static int OPPONENT;
    static const int EMPTY = 5;

    Board();

    ~Board();

    void performMove(int player, Position pos);

    const Position &getLastPosition() const;

    int checkStatus() const;

    void getAvailableMoves(std::vector<Position> &res) const;

    const std::vector<std::vector<signed char>> &getBigField() const;

    const std::vector<std::vector<signed char>> &getSmallField() const;
};
