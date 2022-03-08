#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "MCTS.h"
#include "Board.h"
#include "Other.h"
#include "MiniMax.h"


int main() {
    srand(time(0));

    COMP_WIN = 2;
    OPPONENT_WIN = 1;
    COMP = 4;
    OPPONENT = 3;
    Board *board = new Board();
    int a, b;
    std::cin >> a >> b;
    if (a != -1) {
        board->performMove(OPPONENT, {a, b});
    }
    auto *mcts = new MonteCarloTreeSearch(*board, COMP);
    bool ok = true;
    while (1) {
        if (ok) {
            Position pos2 = mcts->findNextMove(5000);
            board->performMove(COMP, {pos2.x, pos2.y});
            std::cout << pos2.x << ' ' << pos2.y << std::endl;
            ok = false;
        } else {
            Position pos2 = mcts->findNextMove(5000);
            board->performMove(COMP, {pos2.x, pos2.y});
            std::cout << pos2.x << ' ' << pos2.y << std::endl;
        }

        int a, b;
        std::cin >> a >> b;
        board->performMove(OPPONENT, {a, b});
        mcts->reRoot(*board, COMP);

    }
}