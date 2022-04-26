#include "greedy.hpp"
#include "../../direction/direction.hpp"
#include "../../heap/heap.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <list>
#include <thread>
#include <unordered_set>

namespace {
struct BoardEqual {
    bool operator()(const Board* a, const Board* b) const {
        return a->equals(b);
    }
};
} // namespace

using namespace std::chrono_literals;
const Solver* GreedySolver::solve(const Board* initial) const {
    auto heap = new Heap();
    std::unordered_set<const Board*, std::hash<const Board*>, BoardEqual>
        visited;
    heap->push(new Node(
        std::make_pair((Board*)initial, initial->getManhattanDistance(goal))));
    while (heap->length()) {
        auto node = heap->pop();
        auto board = node->value().first;
        visited.emplace(board);
        if (board->equals(goal)) {
            board->printTrace();
            std::cout << "Found, " << visited.size() << " states explored."
                      << std::endl;
            break;
        }
        for (int i = 0; i != 4; ++i) {
            auto moved = board->move((Direction)(i)).value_or(nullptr);
            if (moved == nullptr || visited.count(moved)) {
                continue;
            }
            heap->push(new Node(
                std::make_pair(moved, node->value().second +
                                          moved->getManhattanDistance(goal))));
            visited.emplace(moved);
        }
    }
    return this;
}
