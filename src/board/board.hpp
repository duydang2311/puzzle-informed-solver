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
    unsigned int depth;

  public:
    Board(int*, unsigned int);
    Board(const Board*);
    std::optional<Board*> move(Direction) const;
    bool equals(const Board*) const;
    const Board* print() const;
    ~Board();
};

#endif
