#pragma once

#include "Bot.h"
#include <string>
#include <vector>

class GameController {
private:
    Position inputMove(const std::vector<Position>&, const std::string&);

    void printStatus(BoardStatus);

public:
    void PlayGameEngineEngine(Bot*, Bot*, int, int);

    void PlayGameEngineHuman(Bot*, bool, int);

    void PlayGameHumanHuman();
};
