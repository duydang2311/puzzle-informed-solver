#ifndef PUZZLE_HEAP_NODE_NODE_H
#define PUZZLE_HEAP_NODE_NODE_H

class Node {
  private:
    Node* _parent = nullptr;
    Node* _left = nullptr;
    Node* _right = nullptr;
    int _value;

  public:
    Node(int);

    Node* left(Node*);
    Node* left() const;
    Node* right(Node*);
    Node* right() const;
    Node* parent(Node*);
    Node* parent() const;
    Node* value(int value);
    const int& value() const;
};

#endif
