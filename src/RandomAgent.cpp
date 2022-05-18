#include "RandomAgent.h"
#include <iostream>
#include <random>
#include <cassert>
#include <algorithm>

void RandomAgent::init(const State& nState) {
    state = nState;
}

void RandomAgent::resetGame() {
    state.reset();
}

Position RandomAgent::choseBestMove(int) {
    std::vector<Position> allMoves = state.getAvailableMoves();
    std::random_device rd;
    std::mt19937 g(rd());
    assert(!allMoves.empty());
    std::shuffle(allMoves.begin(), allMoves.end(), g);
    return allMoves[0];
}

void RandomAgent::performMove(Position move) {
    state.performMove(move);
}

void RandomAgent::setState(const State& newState) {
    state = newState;
}

void RandomAgent::setAllPossibleMoves(const std::vector<Position>&) {

}