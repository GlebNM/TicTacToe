#pragma once

#include "NewNode.h"
#include <cmath>

class UCT {
private:
    static long double uctValue(int totalVisit, long double nodeWinScore, int nodeVisit);

public:
    static Node *findBestMoveWithUct(Node *node);
};
