#include "Node.h"

long long Node::getVisitCount() const {
    return visitCount;
}

long double Node::getWinScore() const {
    return winScore;
}

Node* Node::getChildWithMaxScore() {
    long long mx = -INF;
    Node* res = nullptr;
    for (Node* child: children) {
        long long totalVisit = child->getVisitCount();
        if (totalVisit > mx) {
            mx = totalVisit;
            res = child;
        }
    }
    return res;
}

State* Node::getState() const {
    return state;
}

Node::~Node() {
    children.clear();
}

Node::Node(State* nstate) {
    state = new State(*nstate);
}

const std::vector<Node*>& Node::getChildren() const {
    return children;
}

void Node::setParent(Node* newParent) {
    Node::parent = newParent;
}

void Node::addChild(Node* child) {
    children.emplace_back(child);
}

Node* Node::getRandomChildNode() {
    int numberOfChildren = static_cast<int>(children.size());
    int pos = rand() % numberOfChildren;
    return children[pos];
}

void Node::deleteTree(Node* node, Node* prohibited) {
    if (node == prohibited)return;
    std::vector<Node*> children = node->getChildren();
    for (Node* child: children) {
        if (child != nullptr)deleteTree(child, prohibited);
    }
    delete node->getState();
    delete node;
}

Node* Node::getParent() const {
    return parent;
}

void Node::setWinScore(long double value) {
    winScore = value;
}

void Node::incrementVisit() {
    ++visitCount;
}

void Node::addScore(long double value) {
    winScore += value;
}