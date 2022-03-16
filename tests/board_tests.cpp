#include "gtest/gtest.h"
#include "NewState.h"
#include <vector>

TEST(BoardBasic, Test1)
{
    State st;
    EXPECT_EQ(st.checkBigCellStatus({0,0}), BoardStatus::InProgress);
    st.performMove({0,0});
    st.performMove({0,1});
    st.performMove({1,0});
    st.performMove({0,2});
    st.performMove({2,0});
    EXPECT_EQ(st.checkBigCellStatus({0, 0}), BoardStatus::InProgress);
}