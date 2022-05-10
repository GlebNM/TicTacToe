#pragma once

#include "Bot.h"
#include <string>
#include <vector>

class GameController {
private:
    virtual Position inputMove(const std::vector<Position>&, const std::string&);

    void printStatus(BoardStatus);

public:
    void playGameEngineEngine(Bot*, Bot*, int, int);

    void playGameEngineHuman(Bot*, bool, int);

    void playGameHumanHuman();
};
