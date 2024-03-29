#pragma once

#include "Other.h"
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
    
    template<size_t N>
	std::vector<std::bitset<N> > getCells(const std::bitset<N * N>&) const; 

public:
    State();
	
	void performMove(Position position);
	
	std::vector<std::bitset<9> > getSmallCellsX() const;
	
	std::vector<std::bitset<9> > getSmallCellsO() const;
	
	std::vector<std::bitset<3> > getBigCellsX() const;
	
	std::vector<std::bitset<3> > getBigCellsO() const;
	
	std::vector<std::bitset<3> > getBigCellsDraw() const;
	
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
