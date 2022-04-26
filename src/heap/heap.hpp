#ifndef PUZZLE_HEAP_HEAP_H
#define PUZZLE_HEAP_HEAP_H

#include "node/node.hpp"

class Heap {
  private:
    Node* _root;

  public:
    Heap(Node* = nullptr);
    Heap* push(Node* const);
    Heap* pop();
    Node* root() const;
    Heap* root(Node*);
};

#endif
