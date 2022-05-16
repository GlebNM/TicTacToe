#include "gtest/gtest.h"
#include "Interface.h"
#include "GameController.h"
#include "RandomAgent.h"
#include "MiniMax.h"
#include <algorithm>

TEST(MinimaxTest, AllWins) {
    for (int i = 0; i < 5; ++i) {
        GameController game;
        Bot* bot1 = new RandomAgent();
        Bot* bot2 = new MiniMaxAgent();
        testing::internal::CaptureStdout();
        game.playGameEngineEngine(bot1, bot2, 10, 10);
        std::string ans = "";
        for (auto str: testing::internal::GetCapturedStdout())
            ans += str;
        EXPECT_TRUE(ans.find("OWin") != ans.size());
        delete bot1;
        delete bot2;
    }
}
