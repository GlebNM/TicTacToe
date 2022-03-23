#include "gtest/gtest.h"
#include "MCTSAgent.h"
#include "State.h"
#include <vector>


TEST(MCTS, Test1) {
    State st;
    st.performMove({0, 0});
    st.performMove({1, 0});
    st.performMove({0, 1});
    st.performMove({1, 1});
    st.performMove({0, 2});
    st.performMove({3, 3});

    st.performMove({0, 4});
    st.performMove({0, 3});
    st.performMove({1, 4});
    st.performMove({1, 3});
    st.performMove({2, 4});
    st.performMove({5, 5});

    st.performMove({2, 6});
    st.performMove({8, 8});
    st.performMove({1, 7});
    st.performMove({0, 6});

    MCTSAgent mcts;
    mcts.init(st);
    Position move = mcts.choseBestMove(100);
    ASSERT_EQ(move, Position(0, 8));
}

TEST(MCTS, againstRandom) {
    srand(time(0));
    int numGames = 10;
    for (int i = 0; i < numGames; i++) {
        State st;
        while (st.checkOverallStatus() == InProgress) {
            MCTSAgent mcts;
            mcts.init(st);
            Position move = mcts.findNextMove(50);
            st.performMove(move);
            if (st.checkOverallStatus() != InProgress)break;
            std::vector<Position> moves = st.getAvailableMoves();
            int pos = rand() % moves.size();
            st.performMove(moves[pos]);
        }
        int status = st.checkOverallStatus();
        EXPECT_EQ(status, XWin);
    }
}