#include "NewState.h"
#include "NewOther.h"

int State::getSmallCellPosition(Position position) {
    return position.x * 9 + position.y;
}
    
int State::getBigCellPosition(Position position) {
    return position.x / 3 * 3 + position.y / 3;
}

bool State::isOccupied(Position position) const {
    return smallCellsX[getSmallCellPosition(position)] ||
           smallCellsO[getSmallCellPosition(position)];
}

State::State() : currentPlayer(XMark), lastPosition(-1, -1) {}

void State::performMove(Position position) {
    if (currentPlayer == XMark) {
        smallCellsX[getSmallCellPosition(position)] = true;
        currentPlayer = OMark;
    } else {
        smallCellsO[getSmallCellPosition(position)] = true;
        currentPlayer = XMark;
    }
    lastPosition = position;
    int bigCellPosition = getBigCellPosition(position);
    BoardStatus status = checkBigCellStatus({position.x / 3, position.y / 3});
    if (status == XWin)
        bigCellsX[bigCellPosition] = true;
    else if (status == OWin)
        bigCellsO[bigCellPosition] = true;
    else if (status == Draw)
        bigCellsDraw[bigCellPosition] = true;
}

BoardStatus State::checkOverallStatus() const {
    std::bitset<9> horizontal = 0b111000000;
    std::bitset<9> vertical = 0b100100100;
    std::bitset<9> diagonal1 = 0b100010001;
    std::bitset<9> diagonal2 = 0b001010100;
    bool winX = false;
    bool winO = false;
    for (int i = 0; i < 3; ++i) {
        winX |= (bigCellsX & (horizontal >> (i * 3))).count() == 3;
        winO |= (bigCellsO & (horizontal >> (i * 3))).count() == 3;
        winX |= (bigCellsX & (vertical >> i)).count() == 3;
        winO |= (bigCellsO & (vertical >> i)).count() == 3;
    }
    winX |= (bigCellsX & diagonal1).count() == 3;
    winX |= (bigCellsX & diagonal2).count() == 3;
    winO |= (bigCellsO & diagonal1).count() == 3;
    winO |= (bigCellsO & diagonal2).count() == 3;
    if (winX)
        return XWin;
    if (winO)
        return OWin;
    if (bigCellsX.count() + bigCellsO.count() + bigCellsDraw.count() == 9) {
        if (bigCellsX.count() > bigCellsO.count())
            return XWin;
        if (bigCellsX.count() < bigCellsO.count())
            return OWin;
        return Draw;
    }
    return InProgress;
}

bool State::checkOverallStatus(PlayerSymbol playerSymbol) const {
    BoardStatus status = checkOverallStatus();
    return (status == XWin && playerSymbol == XMark) ||
           (status == OWin && playerSymbol == OMark);
}

BoardStatus State::checkBigCellStatus(Position position) const {
    Position BigCellCenter = {position.x * 3 + 1, position.y * 3 + 1};
    bool diagonal1X = true;
    bool diagonal2X = true;
    bool diagonal1O = true;
    bool diagonal2O = true;
    for (int i = -1; i <= 1; ++i) {
        Position movedPosition1 = BigCellCenter.getMoved(i, -i);
        Position movedPosition2 = BigCellCenter.getMoved(-i, i);
        diagonal1X &= smallCellsX[getSmallCellPosition(movedPosition1)];
        diagonal2X &= smallCellsX[getSmallCellPosition(movedPosition2)];
        diagonal1O &= smallCellsO[getSmallCellPosition(movedPosition1)];
        diagonal2O &= smallCellsO[getSmallCellPosition(movedPosition2)];
    }
    if (diagonal1X || diagonal2X)
        return XWin;
    if (diagonal1O || diagonal2O)
        return OWin;
    for (int i = -1; i <= 1; ++i) {
        bool horizontalX = true;
        bool horizontalO = true;
        bool verticalX = true;
        bool verticalO = true;
        for (int j = -1; j <= 1; ++j) {
            int movedPosition1 = getSmallCellPosition(BigCellCenter.getMoved(i, j));
            int movedPosition2 = getSmallCellPosition(BigCellCenter.getMoved(j, i));
            horizontalX &= smallCellsX[movedPosition1];
            horizontalO &= smallCellsO[movedPosition1];
            verticalX &= smallCellsX[movedPosition2];
            verticalO &= smallCellsO[movedPosition2];
        }
        if (horizontalX || verticalX)
            return XWin;
        if (horizontalO || verticalO)
            return OWin;
    }
    int countCells = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int movedPosition = getSmallCellPosition(BigCellCenter.getMoved(i, j));
            countCells += smallCellsX[movedPosition] | smallCellsX[movedPosition];
        }
    }
    return countCells == 9 ? Draw : InProgress;
}

bool State::checkBigCellStatus(Position position, PlayerSymbol playerSymbol) const {
    BoardStatus status = checkBigCellStatus(position);
    return (status == XWin && playerSymbol == XMark) ||
           (status == OWin && playerSymbol == OMark);
}

std::vector<Position> State::getAvailableMoves() const {
    Position nextBigCell = {lastPosition.x % 3, lastPosition.y % 3};
    BoardStatus status = checkBigCellStatus(nextBigCell);
    std::vector<Position> positions;
    if ((lastPosition.x == -1 && lastPosition.y == -1) || status != InProgress) {
        for (int i = 0; i < 81; ++i) {
            if (!isOccupied({i / 9, i % 9}))
                positions.emplace_back(i / 9, i % 9);
        }
    } else {
        Position BigCellCorner = {nextBigCell.x * 3, nextBigCell.y * 3};
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (!isOccupied(BigCellCorner.getMoved(i, j)))
                    positions.emplace_back(BigCellCorner.getMoved(i, j));
            }
        }
    }
    return positions;
}
