#include "heap.hpp"
#include <iostream>

namespace {
void printTraversal(const Node* node) {
    if (node == nullptr) {
        return;
    }
    printTraversal(node->left());
    std::cout << node->value() << " ";
    printTraversal(node->right());
}

unsigned int findLeftMostOpenNodeHelper(Node* node, Node*& openNode,
                                        unsigned int depth = 1) {
    if (node->left() == nullptr || node->right() == nullptr) {
        openNode = node;
        return depth;
    }
    auto rightDepth =
        findLeftMostOpenNodeHelper(node->right(), openNode, depth + 1);
    Node* rightOpenNode = openNode;
    auto leftDepth =
        findLeftMostOpenNodeHelper(node->left(), openNode, depth + 1);
    if (rightDepth < leftDepth) {
        openNode = rightOpenNode;
        return rightDepth;
    }
    return leftDepth;
}

Node* findLeftMostOpenNode(const Heap* heap) {
    Node* openNode = nullptr;
    findLeftMostOpenNodeHelper(heap->root(), openNode);
    return openNode;
}

void ensureParent(Node* node) {
    if (node->left() != nullptr) {
        node->left()->parent(node);
    }
    if (node->right() != nullptr) {
        node->right()->parent(node);
    }
}

void ensureHeapPropertyUpward(Heap* heap, Node* node) {
    if (node->value() < node->parent()->value()) {
        auto parent = node->parent();
        auto leftTemp = node->left();
        auto rightTemp = node->right();
        if (parent->left() == node) {
            node->right(parent->right());
            node->left(parent);
        } else {
            node->left(parent->left());
            node->right(parent);
        }
        parent->left(leftTemp);
        parent->right(rightTemp);
        ensureParent(parent);

        node->parent(parent->parent());
        if (node->parent() != nullptr) {
            if (node->parent()->left() == parent) {
                node->parent()->left(node);
            } else {
                node->parent()->right(node);
            }
        }
        ensureParent(node);
        if (node->parent() != nullptr) {
            ensureHeapPropertyUpward(heap, node);
        } else {
            heap->root(node);
        }
    }
}

void ensureHeapPropertyDownward(Heap* heap, Node* node) {
    if (node->value() < node->parent()->value()) {
        auto parent = node->parent();
        auto leftTemp = node->left();
        auto rightTemp = node->right();
        if (parent->left() == node) {
            node->right(parent->right());
            node->left(parent);
        } else {
            node->left(parent->left());
            node->right(parent);
        }
        parent->left(leftTemp);
        parent->right(rightTemp);
        ensureParent(parent);

        node->parent(parent->parent());
        if (node->parent() != nullptr) {
            if (node->parent()->left() == parent) {
                node->parent()->left(node);
            } else {
                node->parent()->right(node);
            }
        }
        ensureParent(node);
        if (node->parent() == nullptr) {
            heap->root(node);
        }
        ensureHeapPropertyDownward(heap, parent);
    }
}

unsigned int findLastNodeHelper(Node* node, Node*& lastNode,
                                unsigned int depth = 1) {
    if (node == nullptr) {
        return depth - 1;
    }
    if (node->left() == nullptr && node->right() == nullptr) {
        lastNode = node;
        return depth - 1;
    }
    auto leftDepth = findLastNodeHelper(node->left(), lastNode, depth + 1);
    Node* leftOpenNode = lastNode;
    auto rightDepth = findLastNodeHelper(node->right(), lastNode, depth + 1);
    if (leftDepth > rightDepth) {
        lastNode = leftOpenNode;
        return leftDepth;
    }
    return rightDepth;
}

Node* findLastNode(Heap* heap) {
    Node* lastNode = nullptr;
    findLastNodeHelper(heap->root(), lastNode);
    return lastNode;
}
} // namespace

Heap::Heap(Node* root) : _root(root) {}

Node* Heap::root() const { return _root; }
Heap* Heap::root(Node* root) {
    _root = root;
    return this;
}

Heap* Heap::push(Node* const node) {
    if (_root == nullptr) {
        _root = node;
        return this;
    }
    Node* openNode = findLeftMostOpenNode(this);
    node->parent(openNode);
    if (openNode->left() == nullptr) {
        openNode->left(node);
    } else {
        openNode->right(node);
    }
    ensureHeapPropertyUpward(this, node);
    return this;
}

Heap* Heap::pop() {
    if (_root == nullptr) {
        return this;
    }
    auto lastNode = findLastNode(this);
    if (lastNode == _root) {
        delete _root;
        _root = nullptr;
        return this;
    }
    auto temp = _root;
    lastNode->left(_root->left());
    lastNode->right(_root->right());
    _root = lastNode;
    ensureParent(_root);
    if (lastNode->parent()->left() == lastNode) {
        lastNode->parent()->left(nullptr);
    } else if (lastNode->parent()->right() == lastNode) {
        lastNode->parent()->right(nullptr);
    }
    lastNode->parent(nullptr);
    if (_root->right() != nullptr) {
        ensureHeapPropertyDownward(this, _root->right());
    }
    if (_root->left() != nullptr) {
        ensureHeapPropertyDownward(this, _root->left());
    }
    return this;
}
