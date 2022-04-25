#include "board.hpp"
#include <algorithm>
#include <iostream>
#include <optional>

Board::Board(int* matrix, unsigned int len) : matrix(matrix), len(len) {
    for (unsigned int i = 0; i != len; ++i) {
        if (*(matrix + i) == 0) {
            zero_idx = i;
            break;
        }
    }
}

Board::Board(const Board* board) : len(board->len), zero_idx(board->zero_idx) {
    matrix = new int[len];
    for (unsigned int i = 0; i != len; ++i) {
        (*(matrix + i) = *(board->matrix + i));
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

std::optional<Board*> Board::move(Direction direction) const {
    std::optional<Board*> board = std::nullopt;
    if (direction == Direction::Up) {
        if (zero_idx >= 3) {
            board = new Board(this);
            std::swap(*(board.value()->matrix + zero_idx),
                      *(board.value()->matrix + zero_idx - 3));
        }
    } else if (direction == Direction::Down) {
        if (zero_idx < 6) {
            board = new Board(this);
            std::swap(*(board.value()->matrix + zero_idx),
                      *(board.value()->matrix + zero_idx + 3));
        }
    } else if (direction == Direction::Left) {
        if (zero_idx % 3 != 0) {
            board = new Board(this);
            std::swap(*(board.value()->matrix + zero_idx),
                      *(board.value()->matrix + zero_idx - 1));
        }
    } else if (direction == Direction::Right) {
        if ((zero_idx + 1) % 3 != 0) {
            board = new Board(this);
            std::swap(*(board.value()->matrix + zero_idx),
                      *(board.value()->matrix + zero_idx + 1));
        }
    }
    return board;
}

const Board* Board::print() const {
    for (unsigned int i = 0; i != len; ++i) {
        std::cout << *(matrix + i) << " ";
    }
    std::cout << std::endl;
    return this;
}

Board::~Board() { delete[] matrix; }
