#pragma once

#include "Node.h"
#include "UCT.h"
#include "Bot.h"

class MCTSAgent : public Bot {

private:
    Node* root;

    Node* selectPromisingNode(Node* rootNode);

    static void expandNode(Node* node);

    void backPropagation(Node*, BoardStatus, Node*);

    static BoardStatus simulateRandomPlayout(Node* node);

public:
    MCTSAgent();

    ~MCTSAgent();

    Position findNextMove(int);

    void reRoot(const State&);

    void init(const State&) final;

    Position choseBestMove(int) final;

    void performMove(Position) final;

    void setState(const State&) final;

    void setAllPossibleMoves(const std::vector<Position>&) final;

    void resetGame() final;
};



