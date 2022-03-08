#include "gtest/gtest.h"
#include "Board.h"
#include "Other.h"
#include<vector>

TEST(BoardBasic, Test1)
{
    Board *b = new Board();
    std::vector<Position> res;
    b->getAvailableMoves(res);
    EXPECT_EQ(res.size(), 81);
    res.clear();
    b->performMove(0, {0, 0});
    b->getAvailableMoves(res);
    EXPECT_EQ(res.size(), 8);
}