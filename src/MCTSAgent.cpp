#include "MCTSAgent.h"
#include <iostream>

Node* MCTSAgent::selectPromisingNode(Node* rootNode) {
    Node* node = rootNode;
    while (!node->getChildren().empty()) {
        node = UCT::findBestMoveWithUct(node);
    }
    return node;
}

void MCTSAgent::expandNode(Node* node) {
    std::vector<State*> possibleStates = node->getState()->getAllPossibleStates();
    for (State* state: possibleStates) {
        Node* newNode = new Node(state);
        newNode->setParent(node);
        node->addChild(newNode);
        delete state;
    }
}

void MCTSAgent::backPropagation(Node* nodeToExplore, BoardStatus status, Node* rootNode) {
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

BoardStatus MCTSAgent::simulateRandomPlayout(Node* node) {
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

Position MCTSAgent::findNextMove(int time) {
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
    return result;
}

MCTSAgent::MCTSAgent() = default;

MCTSAgent::~MCTSAgent() {
    Node::deleteTree(root, nullptr);
}

void MCTSAgent::reRoot(const State& nState) {
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
    delete state;
    root = rootNode;
}

void MCTSAgent::init(const State& nState) {
    State* state = new State(nState);
    Node* rootNode = new Node(state);
    delete state;
    root = rootNode;
}

void MCTSAgent::resetGame() {
    Node::deleteTree(root, nullptr);
    State* initialState = new State();
    Node* rootNode = new Node(initialState);
    root = rootNode;
}

Position MCTSAgent::choseBestMove(int timeLimit) {
    return findNextMove(timeLimit);
}

void MCTSAgent::performMove(Position move) {
    State newState = *root->getState();
    newState.performMove(move);
    reRoot(newState);
}

void MCTSAgent::setState(const State& newState) {
    reRoot(newState);
}

void MCTSAgent::setAllPossibleMoves(const std::vector<Position>&) {

}

