from state import State
from solver import GreedySolver, AStarSolver


goal = State([1, 2, 3, 4, 5, 6, 7, 8, 0])
initial = State([2, 6, 5, 0, 8, 7, 4, 3, 1])

print('greedy: ', end='')
GreedySolver(goal).solve(initial)

print('a*: ', end='')
AStarSolver(goal).solve(initial)
