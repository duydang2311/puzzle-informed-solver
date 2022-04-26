#ifndef PUZZLE_HEAP_HEAP_H
#define PUZZLE_HEAP_HEAP_H

#include "node/node.hpp"

class Heap {
  private:
    Node* _root;
    unsigned int _length = 0;

  public:
    Heap(Node* = nullptr);
    Heap* push(Node* const);
    Node* pop();
    Node* root() const;
    Heap* root(Node*);
    unsigned int length() const;
    ~Heap();
};

#endif
