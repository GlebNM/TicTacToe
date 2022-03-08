#include "State.h"
#include "Other.h"

void State::setBoard(const Board &newBoard) {
    State::board = newBoard;
}

std::vector<State *> State::getAllPossibleStates() const {
    std::vector<State *> res;
    std::vector<Position> possibleMoves;
    getBoard().getAvailableMoves(possibleMoves);
    for (Position move:possibleMoves) {
        State *newState = new State;
        Board newBoard = this->getBoard();
        newBoard.performMove(playerNo, move);
        newState->board = newBoard;
        newState->playerNo = changePlayer(playerNo);
        newState->visitCount = 0;
        newState->winScore = 0;
        res.emplace_back(newState);
    }
    return res;
}

void State::randomPlay() {             //makes a random move
    std::vector<Position>moves;
    this->board.getAvailableMoves(moves);
    int numberOfValidMoves = static_cast<int>(moves.size());
    int pos = rand() % numberOfValidMoves;
    this->board.performMove(this->playerNo, moves[pos]);
    this->playerNo = changePlayer(playerNo);
}

const Board& State::getBoard() const {
    return board;
}

int State::getPlayerNo() const {
    return playerNo;
}

int State::getOpponent() {
    if (playerNo == COMP)return OPPONENT;
    else return COMP;
}

long long State::getVisitCount() {
    return visitCount;
}

long double State::getWinScore() const {
    return winScore;
}

void State::setPlayerNo(int newPlayerNo) {
    State::playerNo = newPlayerNo;
}

void State::setVisitCount(int newVisitCount) {
    State::visitCount = newVisitCount;
}

void State::setWinScore(long double newWinScore) {
    State::winScore = newWinScore;
}

void State::addScore(long double add) {
    winScore += add;
}

void State::incrementVisit() {
    visitCount++;
}

void State::togglePlayer() {
    playerNo = getOpponent();
}

State::~State() {}
