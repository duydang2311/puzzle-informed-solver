#include "solver.hpp"
#include "../board/board.hpp"

Solver::Solver(const Board* goal) : goal(goal) {}

Solver::~Solver() { delete goal; }
