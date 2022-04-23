#ifndef PUZZLE_BOARD_BOARD_H
#define PUZZLE_BOARD_BOARD_H

class Board {
  private:
    unsigned char* matrix;
    unsigned int len;

  public:
    Board(unsigned char* matrix, unsigned int len) : matrix(matrix), len(len) {}
    const bool operator==(const Board* board) {
        if (len != board->len) {
            return false;
        }
        for (unsigned int i = 0; i != len; ++i) {
            if (*(matrix + i) != *(board->matrix + i)) {
                return false;
            }
        }
        return true;
    }
};

#endif
