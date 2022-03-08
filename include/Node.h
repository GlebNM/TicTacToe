#pragma once

#include <vector>
#include "State.h"

class Node {
private:
    State *state;
    Node *parent;
    std::vector<Node *> children;
public:
    Node(State *state);

    ~Node();

    State *getState() const;

    Node *getParent() const;

    const std::vector<Node *> &getChildren() const;

    void setParent(Node *newParent);

    void addChild(Node *child);

    Node *getRandomChildNode();

    Node *getChildWithMaxScore();


    static void deleteTree(Node *, Node *);
};

