#include "MCTS.h"

Node *MonteCarloTreeSearch::selectPromisingNode(Node *rootNode) {
    Node *node = rootNode;
    while (!node->getChildren().empty()) {
        node = UCT::findBestMoveWithUct(node);
    }
    return node;
}

void MonteCarloTreeSearch::expandNode(Node *node) {
    std::vector<State *> possibleStates = node->getState()->getAllPossibleStates();
    for (auto state:possibleStates) {
        State *nstate = new State(*state);
        Node *newNode = new Node(nstate);
        newNode->setParent(node);
        newNode->getState()->setPlayerNo(node->getState()->getOpponent());
        newNode->getState()->setVisitCount(0);
        newNode->getState()->setWinScore(0);
        node->addChild(newNode);
    }
    for (auto state:possibleStates)delete state;
}

void MonteCarloTreeSearch::backPropagation(Node *nodeToExplore, int playerNo, Node *root) {
    int player = Board::DRAW;
    if (playerNo == COMP_WIN)player = COMP;
    else if (playerNo == OPPONENT_WIN)player = OPPONENT;
    root->getState()->incrementVisit();
    Node *tempNode = nodeToExplore;
    while (tempNode != root) {
        tempNode->getState()->incrementVisit();
        if (player == Board::DRAW) {
            tempNode->getState()->addScore(0.5);
        } else if (tempNode->getState()->getPlayerNo() != player) {
            tempNode->getState()->addScore(WIN_SCORE);
        }
        tempNode = tempNode->getParent();
    }
}

int MonteCarloTreeSearch::simulateRandomPlayout(Node *node) {
    Node *tempNode = new Node(*node);
    State *tempState = new State();
    tempState->setBoard(tempNode->getState()->getBoard());
    tempState->setPlayerNo(tempNode->getState()->getPlayerNo());
    int boardStatus = tempState->getBoard().checkStatus();
    if (boardStatus == Board::DRAW) {
        delete tempNode;
        delete tempState;
        return boardStatus;
    }
    if (boardStatus == OPPONENT_WIN || boardStatus == COMP_WIN) {
        node->getParent()->getState()->setWinScore(-INF);
        node->getState()->setWinScore(INF);
        delete tempNode;
        delete tempState;
        return boardStatus;
    }
    while (boardStatus == Board::IN_PROGRESS) {
        tempState->randomPlay();
        boardStatus = tempState->getBoard().checkStatus();
    }
    delete tempNode;
    delete tempState;
    return boardStatus;
}

Position MonteCarloTreeSearch::findNextMove(int time) {
    const milliseconds TIME_LIMIT{time};
    Node *rootNode = root;
    //rootNode->setParent(nullptr);
    int cnt = 10000;
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(end - start) < TIME_LIMIT) {
        Node *promisingNode = selectPromisingNode(rootNode);
        if (promisingNode->getState()->getBoard().checkStatus() == Board::IN_PROGRESS &&
            promisingNode->getState()->getVisitCount()) {
            expandNode(promisingNode);
        }
        Node *nodeToExplore = promisingNode;
        if (!promisingNode->getChildren().empty()) {
            nodeToExplore = promisingNode->getRandomChildNode();
        }
        int playoutResult = simulateRandomPlayout(nodeToExplore);
        backPropagation(nodeToExplore, playoutResult, rootNode);
        end = std::chrono::steady_clock::now();
    }
    Node *winnerNode = rootNode->getChildWithMaxScore();
    //tree->setRoot(&winnerNode);
    std::clog << rootNode->getState()->getVisitCount() << ' ';
    std::clog << winnerNode->getState()->getWinScore() / winnerNode->getState()->getVisitCount() << ' ';

    auto result = winnerNode->getState()->getBoard().getLastPosition();
    Node::deleteTree(root, winnerNode);
    root = winnerNode;
    return result;
}

MonteCarloTreeSearch::MonteCarloTreeSearch(const Board &board, int player) {
    State *state = new State();
    state->setBoard(board);
    state->setPlayerNo(player);
    state->setVisitCount(0);
    state->setWinScore(0);
    Node *rootNode = new Node(state);
    root = rootNode;
}

void MonteCarloTreeSearch::reRoot(const Board &board, int player) {
    std::vector<Node *> children = root->getChildren();
    for (auto child: children) {
        auto smallF = child->getState()->getBoard().getSmallField();
        if (smallF == board.getSmallField()) {
            Node::deleteTree(root, child);
            root = child;
            return;
        }
    }

    Node::deleteTree(root, nullptr);
    State *state = new State();
    state->setBoard(board);
    state->setPlayerNo(player);
    state->setVisitCount(0);
    state->setWinScore(0);
    Node *rootNode = new Node(state);
    root = rootNode;
}

