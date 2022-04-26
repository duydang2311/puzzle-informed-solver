#ifndef PUZZLE_SOLVER_SOLVER_H
#define PUZZLE_SOLVER_SOLVER_H

#include "../board/board.hpp"

class Solver {
  public:
    explicit Solver(const Board* goal);
    virtual const Solver* solve(const Board* initial) const = 0;
    ~Solver();

  protected:
    const Board* goal;
};

#endif
