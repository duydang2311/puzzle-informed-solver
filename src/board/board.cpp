#include "board.hpp"
#include <algorithm>
#include <iostream>
#include <optional>

Board::Board(int* matrix, unsigned int len)
    : matrix(matrix), len(len), _depth(1) {
    for (unsigned int i = 0; i != len; ++i) {
        if (*(matrix + i) == 0) {
            zero_idx = i;
            break;
        }
    }
}

Board::Board(const Board* board)
    : parent(board), _depth(board->_depth + 1), len(board->len),
      zero_idx(board->zero_idx) {
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

std::optional<Board*> Board::move(Direction direction) {
    std::optional<Board*> board = std::nullopt;
    if (direction == Direction::Up) {
        if (zero_idx >= 3) {
            board = new Board(this);
            std::swap(*(board.value()->matrix + zero_idx),
                      *(board.value()->matrix + zero_idx - 3));
            board.value()->zero_idx -= 3;
        }
    } else if (direction == Direction::Down) {
        if (zero_idx < 6) {
            board = new Board(this);
            std::swap(*(board.value()->matrix + zero_idx),
                      *(board.value()->matrix + zero_idx + 3));
            board.value()->zero_idx += 3;
        }
    } else if (direction == Direction::Left) {
        if (zero_idx % 3 != 0) {
            board = new Board(this);
            std::swap(*(board.value()->matrix + zero_idx),
                      *(board.value()->matrix + zero_idx - 1));
            board.value()->zero_idx -= 1;
        }
    } else if (direction == Direction::Right) {
        if ((zero_idx + 1) % 3 != 0) {
            board = new Board(this);
            std::swap(*(board.value()->matrix + zero_idx),
                      *(board.value()->matrix + zero_idx + 1));
            board.value()->zero_idx += 1;
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

const Board* Board::printTrace() const {
    auto node = this;
    while (node != nullptr) {
        node->print();
        node = node->parent;
    }
    return this;
}

unsigned int Board::getManhattanDistance(const Board* board) const {
    unsigned int distance = 0;
    unsigned int len = (this->len < board->len) ? this->len : board->len;
    for (unsigned int i = 0; i != len; ++i) {
        if (*(this->matrix + i) != *(board->matrix + i)) {
            ++distance;
        }
    }
    return distance;
}

Board::~Board() { delete[] matrix; }
