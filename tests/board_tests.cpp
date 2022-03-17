#include "gtest/gtest.h"
#include "NewState.h"
#include <vector>

TEST(StateBasic, BigCellWin) {
    State st;
    EXPECT_EQ(st.checkBigCellStatus({0, 0}), BoardStatus::InProgress);
    st.performMove({0, 0});
    st.performMove({0, 1});
    st.performMove({1, 0});
    st.performMove({0, 2});
    st.performMove({2, 0});
    EXPECT_EQ(st.checkBigCellStatus({0, 0}), BoardStatus::XWin);
    st.performMove({8, 8});
    st.performMove({1, 4});
    st.performMove({0, 3});
    st.performMove({0, 5});
    st.performMove({8, 7});
    EXPECT_EQ(st.checkBigCellStatus({0, 1}), BoardStatus::InProgress);
    st.performMove({2, 3});
    EXPECT_EQ(st.checkBigCellStatus({0, 1}), BoardStatus::XWin);
    EXPECT_TRUE(st.checkBigCellStatus({0, 1}, PlayerSymbol::XMark));
    st.performMove({6, 6});
    st.performMove({1, 6});
    st.performMove({6, 7});
    st.performMove({1, 7});
    st.performMove({6, 8});
    EXPECT_EQ(st.checkOverallStatus(), BoardStatus::InProgress);
    st.performMove({1, 8});
    EXPECT_EQ(st.checkBigCellStatus({0, 2}), BoardStatus::XWin);
    EXPECT_EQ(st.checkOverallStatus(), BoardStatus::XWin);
    st.reset();
    std::vector<Position> correct;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            correct.push_back({i, j});
        }
    }
    std::vector<Position> res = st.getAvailableMoves();
    std::sort(res.begin(), res.end(), [](auto& l, auto& r) {
        if (l.x < r.x) return true;
        else return l.y < r.y;
    });
    EXPECT_TRUE(res == correct);
}
