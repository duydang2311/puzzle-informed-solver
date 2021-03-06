from time import time
from typing import Any, Callable, TypeVar, cast
from state.state import State
from direction.direction import Direction
from solver.solver import Solver


F = TypeVar('F', bound=Callable[..., Any])


def _measure(func: F) -> F:
    def wrapped(self: Solver, *args: Any, **kwargs: Any):
        start = time()
        try:
            return func(self, *args, **kwargs)
        finally:
            end_ = time() - start
            print(f"\t> {end_} seconds")
    return cast(F, wrapped)


class GreedySolver(Solver):
    @_measure
    def solve(self, initial: State, heuristicFunction: Callable[[State, State], int]):
        super().solve(initial, heuristicFunction)
        increment = 1
        visited: set[State] = set()
        heap: list[tuple[int, int, State]] = []
        Solver._push(heap, 0, (increment := increment + 1), initial)
        while len(heap) != 0:
            _, _, state = Solver._pop(heap)
            if state == self.goal:
                print("found,", len(visited), 'states expanded,',
                      state.depth, 'depths')
                # state.print_trace()
                break
            for i in Direction:
                moved = state.move(i)
                if moved is None or moved in visited:
                    continue
                Solver._push(heap, heuristicFunction(
                    moved, self.goal), (increment := increment + 1), moved)
                visited.add(moved)
        print("could not find goal")
