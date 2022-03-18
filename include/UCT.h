#pragma once

#include "Node.h"
#include <cmath>

class UCT {
private:
    static long double uctValue(long long totalVisit, long double nodeWinScore, long long nodeVisit);

public:
    static Node *findBestMoveWithUct(Node *node);
};
