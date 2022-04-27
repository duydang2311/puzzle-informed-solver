from __future__ import annotations
from state.state import State
import heapq
import abc


class Solver():
    __metaclass__ = abc.ABCMeta

    def __init__(self, goal: State):
        self.goal = goal

    @staticmethod
    def _heuristics(state1: State, state2: State):
        diff = 0
        for i, _ in enumerate(state1.matrix):
            if state1.matrix[i] != state2.matrix[i]:
                diff += 1
        return diff

    @staticmethod
    def _push(heap: list[tuple[int, int, State]], cost: int, identity: int, state: State):
        heapq.heappush(heap, (cost, identity, state))

    @staticmethod
    def _pop(heap: list[tuple[int, int, State]]):
        return heapq.heappop(heap)

    @staticmethod
    def _visit(visitedSet: set[tuple[int, ...]], matrix: list[int]):
        visitedSet.add(tuple(matrix))

    @abc.abstractmethod
    def solve(self, initial: State):
        pass
