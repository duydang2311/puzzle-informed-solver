#include "board.hpp"

Board::Board(unsigned char* matrix, unsigned int len)
    : matrix(matrix), len(len) {
    for (unsigned int i = 0; i != len; ++i) {
        if (*(matrix + i) == 0) {
            this->zero_idx = i;
            break;
        }
    }
}

bool Board::equals(const Board* board) const {
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

Board::~Board() { delete[] this->matrix; }
