#pragma once

#include "NewNode.h"
#include "NewUCT.h"

class MonteCarloTreeSearch {

private:
    static const int WIN_SCORE = 1;

    int level;
    int opponent;
    Node* root;
    PlayerSymbol agentSymbol;

    Node* selectPromisingNode(Node* rootNode);

    static void expandNode(Node* node);

    void backPropagation(Node*, BoardStatus, Node*);

    static BoardStatus simulateRandomPlayout(Node* node);

public:
    MonteCarloTreeSearch(const State&, PlayerSymbol);

    Position findNextMove(int);

    void reRoot(const State&);
};



