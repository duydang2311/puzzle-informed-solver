#ifndef PUZZLE_SOLVER_GREEDY_GREEDY_H
#define PUZZLE_SOLVER_GREEDY_GREEDY_H

#include "../solver.hpp"

class GreedySolver : public Solver {
  public:
    explicit GreedySolver(const Board* goal) : Solver(goal) {}
    const Solver* solve(const Board* initial) const;
};

#endif
