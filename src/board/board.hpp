#ifndef PUZZLE_BOARD_BOARD_H
#define PUZZLE_BOARD_BOARD_H

#include "../direction/direction.hpp"

class Board {
  private:
    unsigned char* matrix;
    unsigned int len;

  public:
    Board(unsigned char*, unsigned int);
    Board* move(Direction) const;
    bool equals(const Board*) const;
    ~Board();
};

#endif
