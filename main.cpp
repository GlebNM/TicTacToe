#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "NewMCTS.h"
#include "NewOther.h"


int main() {
    srand(time(0));

//    COMP_WIN = 2;
//    OPPONENT_WIN = 1;
//    COMP = 4;
//    OPPONENT = 3;
//    Board *board = new Board();
//    int a, b;
//    std::cin >> a >> b;
//    if (a != -1) {
//        board->performMove(OPPONENT, {a, b});
//    }
//    auto *mcts = new MonteCarloTreeSearch(*board, COMP);
//    bool ok = true;
//    while (1) {
//        if (ok) {
//            Position pos2 = mcts->findNextMove(5000);
//            board->performMove(COMP, {pos2.x, pos2.y});
//            std::cout << pos2.x << ' ' << pos2.y << std::endl;
//            ok = false;
//        } else {
//            Position pos2 = mcts->findNextMove(5000);
//            board->performMove(COMP, {pos2.x, pos2.y});
//            std::cout << pos2.x << ' ' << pos2.y << std::endl;
//        }
//
//        int a, b;
//        std::cin >> a >> b;
//        board->performMove(OPPONENT, {a, b});
//        mcts->reRoot(*board, COMP);
//    }
    State st;
    while (st.checkOverallStatus() == InProgress) {
        std::cout << "MCTS" << std::endl;
        MonteCarloTreeSearch mcts(st, PlayerSymbol::XMark);
        Position move = mcts.findNextMove(5000);
        std::cout << move.x << ' ' << move.y << std::endl;
        int x, y;
        st.performMove(move);
        st.print();
        if (st.checkOverallStatus() != InProgress)break;
        std::cout << "RAND" << std::endl;
        std::vector<Position> moves = st.getAvailableMoves();
        int pos = rand() % moves.size();
        std::cout << moves[pos].x << ' ' << moves[pos].y << std::endl;
        st.performMove(moves[pos]);
        st.print();
    }
    int status = st.checkOverallStatus();
    if (status == XWin)std::cout << "XWin"<<std::endl;
    if (status == OWin)std::cout << "OWin" << std::endl;
    if (status == Draw)std::cout << "Draw"<<std::endl;
}
