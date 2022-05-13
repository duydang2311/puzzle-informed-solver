from typing import Any, Callable, TypeVar, cast
from time import time
from state import State
from direction import Direction
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


class AStarSolver(Solver):
    @_measure
    def solve(self, initial: State, heuristicFunction: Callable[[State, State], int]):
        increment = 0
        open_set: set[State] = set([initial])
        closed_set: set[State] = set()
        heap: list[tuple[int, int, State]] = [
            (0, (increment := increment + 1), initial)]
        while heap:  # or open_set
            _, _, state = Solver._pop(heap)
            if state == self.goal:
                print()
                print("found,", len(open_set), 'states expanded,', len(closed_set), 'states visited,',
                      state.depth, 'depths')
                break
            for i in Direction:
                moved = state.move(i)
                if moved is None:
                    continue
                moved.cost = moved.depth + heuristicFunction(moved, self.goal)
                if moved in open_set:
                    open_list = list(open_set)
                    old = open_list[open_list.index(moved)]
                    if old.cost > moved.cost:
                        open_set.remove(old)
                        heap.remove((old.cost, old.identity, old))
                elif moved in closed_set:
                    closed_list = list(closed_set)
                    old = closed_list[closed_list.index(moved)]
                    if old.cost > moved.cost:
                        closed_set.remove(old)
                if moved not in open_set:
                    moved.identity = (increment := increment + 1)
                    Solver._push(
                        heap, moved.cost, moved.identity, moved)
                    open_set.add(moved)
                    if moved in closed_set:
                        closed_set.remove(moved)
            open_set.remove(state)
            closed_set.add(state)
