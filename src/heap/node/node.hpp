#ifndef PUZZLE_HEAP_NODE_NODE_H
#define PUZZLE_HEAP_NODE_NODE_H

#include "../../board/board.hpp"
#include <utility>

class Node {
  private:
    Node* _parent = nullptr;
    Node* _left = nullptr;
    Node* _right = nullptr;
    std::pair<Board*, unsigned int> _value;

  public:
    Node(std::pair<Board*, unsigned int>);

    Node* left(Node*);
    Node* left() const;
    Node* right(Node*);
    Node* right() const;
    Node* parent(Node*);
    Node* parent() const;
    Node* value(std::pair<Board*, unsigned int>);
    std::pair<Board*, unsigned int> value() const;
};

#endif
