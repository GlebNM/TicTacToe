#include "NewUCT.h"

long double UCT::uctValue(int totalVisit, long double nodeWinScore, int nodeVisit) {
    if (nodeVisit == 0) {
        return INF;
    }
    return ((long double) nodeWinScore / (long double) nodeVisit) +
           1.414213 * sqrtl(logl(totalVisit) / (long double) nodeVisit);
}

Node* UCT::findBestMoveWithUct(Node* node) {
    int parentVisit = node->getVisitCount();
    long double mx = -INF;
    Node* result = node;
    for (Node* child: node->getChildren()) {
        long double curUctValue = uctValue(parentVisit, child->getWinScore(),
                                           child->getVisitCount());
        if (curUctValue > mx) {
            mx = curUctValue;
            result = child;
        }
    }
    return result;
}

