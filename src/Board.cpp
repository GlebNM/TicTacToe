#include "Board.h"


bool Board::checkWin(int player, const std::vector<std::vector<signed char>> &field, int dX, int dY) const {
    if (field[0 + dX][0 + dY] == player && field[0 + dX][1 + dY] == player && field[0 + dX][2 + dY] == player ||
        field[1 + dX][0 + dY] == player && field[1 + dX][1 + dY] == player && field[1 + dX][2 + dY] == player ||
        field[2 + dX][0 + dY] == player && field[2 + dX][1 + dY] == player && field[2 + dX][2 + dY] == player ||
        field[0 + dX][0 + dY] == player && field[1 + dX][0 + dY] == player && field[2 + dX][0 + dY] == player ||
        field[0 + dX][1 + dY] == player && field[1 + dX][1 + dY] == player && field[2 + dX][1 + dY] == player ||
        field[0 + dX][2 + dY] == player && field[1 + dX][2 + dY] == player && field[2 + dX][2 + dY] == player ||
        field[0 + dX][0 + dY] == player && field[1 + dX][1 + dY] == player && field[2 + dX][2 + dY] == player ||
        field[0 + dX][2 + dY] == player && field[1 + dX][1 + dY] == player && field[2 + dX][0 + dY] == player) {
        return true;
    } else {
        return false;
    }
}

int Board::checkSmallFieldStatus(const Position &smallFieldPosition) {
    if (checkWin(COMP, smallField, smallFieldPosition.x * 3, smallFieldPosition.y * 3))return COMP_WIN;
    if (checkWin(OPPONENT, smallField, smallFieldPosition.x * 3, smallFieldPosition.y * 3))return OPPONENT_WIN;
    if (count(smallField, EMPTY, smallFieldPosition.x * 3, smallFieldPosition.y * 3) == 0)return DRAW;
    return IN_PROGRESS;
}

int Board::count(const std::vector<std::vector<signed char>> &field, int player, int deltaX, int deltaY) const {
    int res = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i + deltaX][j + deltaY] == player) {
                res++;
            }
        }
    }
    return res;
}

Board::Board() {
    smallField.assign(9, std::vector<signed char>(9, 5));//EMPTY
    bigField.assign(3, std::vector<signed char>(3, -1));//IN_PROGRESS
}

Board::~Board() {}

void Board::performMove(int player, Position pos) {
    smallField[pos.x][pos.y] = player;
    lastPosition = pos;
    Position smallFieldPosition = {pos.x / 3, pos.y / 3};
    bigField[smallFieldPosition.x][smallFieldPosition.y] = checkSmallFieldStatus(smallFieldPosition);
}

const Position &Board::getLastPosition() const {
    return lastPosition;
}

int Board::checkStatus() const {//general game status
    if (checkWin(COMP_WIN, bigField, 0, 0))return COMP_WIN;
    if (checkWin(OPPONENT_WIN, bigField, 0, 0))return OPPONENT_WIN;
    int numberOfCompWins = count(bigField, COMP_WIN, 0, 0);
    int numberOfOpponentWins = count(bigField, OPPONENT_WIN, 0, 0);
    int numberOfDraws = count(bigField, DRAW, 0, 0);
    if (numberOfDraws + numberOfCompWins + numberOfOpponentWins != 9)return IN_PROGRESS;
    if (numberOfCompWins > numberOfOpponentWins)return COMP_WIN;
    else if (numberOfCompWins < numberOfOpponentWins)return OPPONENT_WIN;
    else return DRAW;
}

void Board::getAvailableMoves(std::vector<Position> &res) const {//all available moves
    if (lastPosition.x == -1) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                res.emplace_back(Position{i, j});
            }
        }
        return;
    }
    Position nextBigBoardToMove = Position{lastPosition.x % 3, lastPosition.y % 3};
    if (bigField[nextBigBoardToMove.x][nextBigBoardToMove.y] == IN_PROGRESS) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (smallField[i + nextBigBoardToMove.x * 3][j + nextBigBoardToMove.y * 3] == EMPTY) {
                    res.emplace_back(Position{i + nextBigBoardToMove.x * 3, j + nextBigBoardToMove.y * 3});
                }
            }
        }
        return;
    } else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (bigField[i][j] != IN_PROGRESS)continue;
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        if (smallField[i * 3 + k][j * 3 + l] == EMPTY)res.emplace_back(Position{i * 3 + k, j * 3 + l});
                    }
                }
            }
        }
        return;
    }
}

const std::vector<std::vector<signed char>> &Board::getBigField() const {
    return bigField;
}

const std::vector<std::vector<signed char>> &Board::getSmallField() const {
    return smallField;
}

