#include "MCTS.h"
#include <iostream>

Node* MonteCarloTreeSearch::selectPromisingNode(Node* rootNode) {
    Node* node = rootNode;
    while (!node->getChildren().empty()) {
        node = UCT::findBestMoveWithUct(node);
    }
    return node;
}

void MonteCarloTreeSearch::expandNode(Node* node) {
    std::vector<State*> possibleStates = node->getState()->getAllPossibleStates();
    for (auto state: possibleStates) {
        Node* newNode = new Node(state);
        newNode->setParent(node);
        node->addChild(newNode);
    }
}

void MonteCarloTreeSearch::backPropagation(Node* nodeToExplore, BoardStatus status, Node* rootNode) {
    rootNode->incrementVisit();
    Node* tempNode = nodeToExplore;
    while (tempNode != rootNode) {
        tempNode->incrementVisit();
        if (status == BoardStatus::Draw) {
            tempNode->addScore(0.5);
        } else {
            PlayerSymbol curPlayer = tempNode->getState()->getCurrentPlayer();
            if ((curPlayer == OMark && status == XWin) || (curPlayer == XMark && status == OWin)) {
                tempNode->addScore(1);
            }
        }
        tempNode = tempNode->getParent();
    }
}

BoardStatus MonteCarloTreeSearch::simulateRandomPlayout(Node* node) {
    State* tempState = new State(*node->getState());
    BoardStatus boardStatus = tempState->checkOverallStatus();
    if (boardStatus == BoardStatus::Draw) {
        delete tempState;
        return boardStatus;
    }
    if (boardStatus == XWin || boardStatus == OWin) {
        node->getParent()->setWinScore(-INF);
        node->setWinScore(INF);
        delete tempState;
        return boardStatus;
    }
    while (boardStatus == BoardStatus::InProgress) {
        //make random move
        std::vector<Position> moves = tempState->getAvailableMoves();
        int numberOfValidMoves = static_cast<int>(moves.size());
        int pos = rand() % numberOfValidMoves;
        tempState->performMove(moves[pos]);

        boardStatus = tempState->checkOverallStatus();
    }
    delete tempState;
    return boardStatus;
}

Position MonteCarloTreeSearch::findNextMove(int time) {
    const milliseconds TIME_LIMIT{time};
    Node* rootNode = root;
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(end - start) < TIME_LIMIT) {
        Node* promisingNode = selectPromisingNode(rootNode);
        if (promisingNode->getState()->checkOverallStatus() == BoardStatus::InProgress &&
            promisingNode->getVisitCount() != 0) {
            expandNode(promisingNode);
        }
        Node* nodeToExplore = promisingNode;
        if (!promisingNode->getChildren().empty()) {
            nodeToExplore = promisingNode->getRandomChildNode();
        }
        BoardStatus playoutResult = simulateRandomPlayout(nodeToExplore);
        backPropagation(nodeToExplore, playoutResult, rootNode);
        end = std::chrono::steady_clock::now();
    }
    Node* winnerNode = rootNode->getChildWithMaxScore();
    std::clog << rootNode->getVisitCount() << ' ';
    std::clog << winnerNode->getWinScore() / winnerNode->getVisitCount() << ' ';

    auto result = winnerNode->getState()->getLastPosition();
    Node::deleteTree(root, winnerNode);
    root = winnerNode;
    return result;
}

MonteCarloTreeSearch::MonteCarloTreeSearch(const State& nState) {
    State* state = new State(nState);
    Node* rootNode = new Node(state);
    root = rootNode;
}

void MonteCarloTreeSearch::reRoot(const State& nState) {
    std::vector<Node*> children = root->getChildren();
    for (auto child: children) {
        auto smallF = child->getState();
        if (*smallF == nState) {
            Node::deleteTree(root, child);
            root = child;
            return;
        }
    }

    Node::deleteTree(root, nullptr);
    State* state = new State(nState);
    Node* rootNode = new Node(state);
    root = rootNode;
}

