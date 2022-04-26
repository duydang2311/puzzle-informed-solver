#include "node.hpp"
#include "../../board/board.hpp"
#include <iostream>
#include <utility>

Node::Node(std::pair<Board*, unsigned int> value) : _value(value) {}

Node* Node::left() const { return _left; }
Node* Node::left(Node* left) {
    _left = left;
    return this;
}

Node* Node::right() const { return _right; }
Node* Node::right(Node* right) {
    _right = right;
    return this;
}

Node* Node::parent() const { return _parent; }
Node* Node::parent(Node* parent) {
    _parent = parent;
    return this;
}

std::pair<Board*, unsigned int> Node::value() const { return _value; }
Node* Node::value(std::pair<Board*, unsigned int> value) {
    _value = value;
    return this;
}
