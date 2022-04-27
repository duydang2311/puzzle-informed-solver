from solver import Solver
from state import State
from solver import GreedySolver, AStarSolver


goal = State([1, 2, 3, 4, 5, 6, 7, 8, 0])
initial = State([2, 6, 5, 0, 8, 7, 4, 3, 1])
print('initial state is', initial.matrix)
print('goal state is', goal.matrix)

print('greedy misplaced: ', end='')
GreedySolver(goal).solve(initial, Solver.misplaced)
print('greedy manhattan: ', end='')
GreedySolver(goal).solve(initial, Solver.manhattan)

print('A* misplaced: ', end='')
AStarSolver(goal).solve(initial, Solver.misplaced)
print('A* manhattan: ', end='')
AStarSolver(goal).solve(initial, Solver.manhattan)
