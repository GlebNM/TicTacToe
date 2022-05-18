#include "gtest/gtest.h"
#include "Interface.h"
#include "GameController.h"
#include "MiniMax.h"
#include <gmock/gmock.h>
#include <vector>


class GameControllerMock : public GameController {
public:
	MOCK_METHOD(Position, inputMove, (const std::vector<Position>& availableMoves, const std::string& name), (override));
};

TEST(GameController, HumanHuman) {
	testing::internal::CaptureStdout();
	GameControllerMock game;
	std::vector <Position> positions = {
		{4, 4},
		{3, 5},
		{0, 6},
		{1, 1},
		{5, 4},
		{7, 4},
		{3, 4},
		{2, 3},
		{7, 1},
		{6, 2},
		{1, 7},
		{6, 8},
		{2, 8},
		{8, 6},
		{6, 1},
		{1, 4},
		{8, 1}
	};
	EXPECT_CALL(game, inputMove(testing::_, testing::_))
     		.Times(testing::AtLeast(17))
     		.WillOnce(testing::Return(positions[0]))
     		.WillOnce(testing::Return(positions[1]))
     		.WillOnce(testing::Return(positions[2]))
     		.WillOnce(testing::Return(positions[3]))
     		.WillOnce(testing::Return(positions[4]))
     		.WillOnce(testing::Return(positions[5]))
     		.WillOnce(testing::Return(positions[6]))
     		.WillOnce(testing::Return(positions[7]))
     		.WillOnce(testing::Return(positions[8]))
     		.WillOnce(testing::Return(positions[9]))
     		.WillOnce(testing::Return(positions[10]))
     		.WillOnce(testing::Return(positions[11]))
     		.WillOnce(testing::Return(positions[12]))
     		.WillOnce(testing::Return(positions[13]))
     		.WillOnce(testing::Return(positions[14]))
     		.WillOnce(testing::Return(positions[15]))
     		.WillOnce(testing::Return(positions[16]));
    game.playGameHumanHuman();
    std::string ans = "";
	for (auto str : testing::internal::GetCapturedStdout())
		ans += str;
	EXPECT_TRUE(ans.find("XWin") != ans.size());
}

TEST(GameController, EngineHuman) {
	testing::internal::CaptureStdout();
	GameControllerMock game;
	EXPECT_CALL(game, inputMove(testing::_, testing::_))
     		.WillRepeatedly(testing::Invoke([&](const std::vector<Position>& availableMoves, const std::string& name) -> Position { return availableMoves[0]; }));
    Bot* bot = new MiniMaxAgent();
    game.playGameEngineHuman(bot, true, 10);
    std::string ans = "";
	for (auto str : testing::internal::GetCapturedStdout())
		ans += str;
	EXPECT_TRUE(ans.find("OWin") != ans.size());
    delete bot;
}
