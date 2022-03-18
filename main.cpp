#include <iostream>
#include <algorithm>
#include <ctime>
#include "MCTS.h"
#include "Other.h"


int main() {
    srand(time(0));
    State st;
    while (st.checkOverallStatus() == InProgress) {
        std::cout << "MCTS" << std::endl;
        MonteCarloTreeSearch mcts(st);
        Position move = mcts.findNextMove(5000);
        std::cout << move.x << ' ' << move.y << std::endl;
        int x, y;
        st.performMove(move);
        st.print();
        if (st.checkOverallStatus() != InProgress)break;
        std::cin >> x >> y;
        st.performMove({x, y});
        st.print();
    }
    int status = st.checkOverallStatus();
    if (status == XWin) {
        std::cout << "XWin" << std::endl;
    }
    if (status == OWin)std::cout << "OWin" << std::endl;
    if (status == Draw)std::cout << "Draw" << std::endl;
}
