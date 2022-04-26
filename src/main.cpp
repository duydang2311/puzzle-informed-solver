#include "board/board.hpp"
#include "direction/direction.hpp"
#include "heap/heap.hpp"
#include "heap/node/node.hpp"
#include "solver/greedy/greedy.hpp"
#include <iostream>
#include <utility>

int main() {
    auto solver =
        new GreedySolver(new Board(new int[]{1, 2, 3, 4, 5, 6, 7, 8, 0}, 9));
    solver->solve(new Board(new int[]{2, 0, 3, 1, 5, 6, 4, 7, 8}, 9));
    delete solver;
}
