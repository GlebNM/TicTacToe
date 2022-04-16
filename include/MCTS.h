#pragma once

#include "Node.h"
#include "UCT.h"

class MonteCarloTreeSearch {

private:
    Node* root;

    Node* selectPromisingNode(Node* rootNode);

    static void expandNode(Node* node);

    void backPropagation(Node*, BoardStatus, Node*);

    static BoardStatus simulateRandomPlayout(Node* node);

public:
    MonteCarloTreeSearch(const State&);

    Position findNextMove(int);

    void reRoot(const State&);
};



