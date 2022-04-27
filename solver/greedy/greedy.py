from state.state import State
from direction.direction import Direction
from solver.solver import Solver


class GreedySolver(Solver):
    def solve(self, initial: State):
        increment = 1
        visited: set[tuple[int, ...]] = set()
        heap: list[tuple[int, int, State]] = []
        Solver._push(heap, 0, (increment := increment + 1), initial)
        while len(heap) != 0:
            _, _, state = Solver._pop(heap)
            if state.matrix == self.goal.matrix:
                print("found,", len(visited), 'states expanded,',
                      state.depth, 'depths')
                state.print_trace()
                break
            for i in Direction:
                moved = state.move(i)
                if moved is None or tuple(moved.matrix) in visited:
                    continue
                Solver._push(heap, Solver._heuristics(
                    moved, self.goal), (increment := increment + 1), moved)
                Solver._visit(visited, moved.matrix)
