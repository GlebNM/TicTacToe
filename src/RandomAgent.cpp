#include "RandomAgent.h"
#include <iostream>
#include <random>

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
    return allMoves[static_cast<int>(g()) % static_cast<int>(allMoves.size())];
}

void RandomAgent::performMove(Position move) {
    state.performMove(move);
}

void RandomAgent::setState(const State& newState) {
    state = newState;
}

void RandomAgent::setAllPossibleMoves(const std::vector<Position>&) {

}
