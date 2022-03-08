#pragma once

#include "Node.h"
#include "UCT.h"

class MonteCarloTreeSearch {

private:
    static const int WIN_SCORE = 1;

    int level;
    int opponent;
    Node *root;

    Node *selectPromisingNode(Node *rootNode);

    static void expandNode(Node *node);

    void backPropagation(Node *nodeToExplore, int playerNo, Node *root);

    static int simulateRandomPlayout(Node *node);

public:
    MonteCarloTreeSearch(const Board &, int);

    Position findNextMove(int);

    void reRoot(const Board&, int);
};


