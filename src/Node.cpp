#include "Node.h"

Node *Node::getChildWithMaxScore() {
    int mx = -INF;
    Node *res;
    for (Node *child:children) {
        int totalVisit = child->getState()->getVisitCount();
        if (totalVisit > mx) {
            mx = totalVisit;
            res = child;
        }
    }
    return res;
}

State *Node::getState() const {
    return state;
}

Node::~Node() {
    children.clear();
}

Node::Node(State *state) : state(state) {}

const std::vector<Node *> &Node::getChildren() const {
    return children;
}

void Node::setParent(Node *newParent) {
    Node::parent = newParent;
}

void Node::addChild(Node *child) {
    children.emplace_back(child);
}

Node *Node::getRandomChildNode() {
    int numberOfChildren = static_cast<int>(children.size());
    int pos = rand() % numberOfChildren;
    return children[pos];
}

void Node::deleteTree(Node *node, Node *prohibited) {
    if (node == prohibited)return;
    std::vector<Node *> children = node->getChildren();
    for (Node *child: children) {
        if (child != nullptr)deleteTree(child, prohibited);
    }
    delete node->getState();
    delete node;
}

Node *Node::getParent() const {
    return parent;
}