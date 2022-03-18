#pragma once

#include "NewOther.h"
#include <bitset>
#include <vector>

class State {
private:
    std::bitset<81> smallCellsX;
    std::bitset<81> smallCellsO;

    std::bitset<9> bigCellsX;
    std::bitset<9> bigCellsO;
    std::bitset<9> bigCellsDraw;

    PlayerSymbol currentPlayer;
    Position lastPosition;

    static int getSmallCellPosition(Position position);

    static int getBigCellPosition(Position position);

    bool isOccupied(Position position) const;

    bool isBigCellInProgress(Position position) const;

public:
    State();

    void performMove(Position position);

    BoardStatus checkOverallStatus() const;

    bool checkOverallStatus(PlayerSymbol playerSymbol) const;

    BoardStatus checkBigCellStatus(Position position) const;

    bool checkBigCellStatus(Position position, PlayerSymbol playerSymbol) const;

    std::vector<Position> getAvailableMoves() const;

    void reset();

    std::vector<State*> getAllPossibleStates() const;

    Position getLastPosition() const;

    bool operator==(const State& other) const;

    PlayerSymbol getCurrentPlayer() const;

    void print() const;
};
