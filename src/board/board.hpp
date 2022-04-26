#ifndef PUZZLE_BOARD_BOARD_H
#define PUZZLE_BOARD_BOARD_H

#include "../direction/direction.hpp"
#include <optional>

class Board {
  private:
    int* matrix;
    unsigned int len;
    unsigned int zero_idx;
    const Board* parent;
    unsigned int _depth;

  public:
    Board(int*, unsigned int);
    Board(const Board*);
    std::optional<Board*> move(Direction);
    bool equals(const Board*) const;
    const Board* print() const;
    const Board* printTrace() const;
    unsigned int getManhattanDistance(const Board*) const;
    unsigned int depth() const { return _depth; }
    ~Board();
};

#endif
