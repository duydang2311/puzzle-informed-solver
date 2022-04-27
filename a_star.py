from __future__ import annotations
import heapq
from enum import Enum


class Direction(Enum):
    Up = 1
    Down = 2
    Left = 3
    Right = 4


class State:
    def __init__(self, matrix: list[int], parent: State | None = None):
        self.parent = parent
        self.matrix = matrix
        self.depth = 1 if parent is None else parent.depth + 1
        self.zero = self.matrix.index(0)

    def move(self, direction: Direction) -> State | None:
        mtx: list[int] | None = None
        if direction == Direction.Up:
            if self.zero > 2:
                mtx = [i for i in self.matrix]
                (mtx[self.zero], mtx[self.zero - 3]
                 ) = (mtx[self.zero - 3], mtx[self.zero])
        elif direction == Direction.Down:
            if self.zero < 6:
                mtx = [i for i in self.matrix]
                (mtx[self.zero], mtx[self.zero + 3]
                 ) = (mtx[self.zero + 3], mtx[self.zero])
        elif direction == Direction.Left:
            if self.zero % 3 != 0:
                mtx = [i for i in self.matrix]
                (mtx[self.zero], mtx[self.zero - 1]
                 ) = (mtx[self.zero - 1], mtx[self.zero])
        elif direction == Direction.Right:
            if (self.zero + 1) % 3 != 0:
                mtx = [i for i in self.matrix]
                (mtx[self.zero], mtx[self.zero + 1]
                 ) = (mtx[self.zero + 1], mtx[self.zero])
        if mtx is None:
            return None
        return State(mtx, self)

    def print_trace(self):
        state = self
        while state is not None:
            print(state.matrix)
            state = state.parent


goal = State([1, 2, 3, 4, 5, 6, 7, 8, 0])
initial = State([2, 6, 5, 0, 8, 7, 4, 3, 1])
heap: list[tuple[int, int, State]] = []
visited: set[tuple[int, ...]] = set()
increment = 0


def heuristics(state1: State, state2: State):
    diff = 0
    for i, _ in enumerate(state1.matrix):
        if state1.matrix[i] != state2.matrix[i]:
            diff += 1
    return diff


def push(cost: int, state: State):
    global increment
    heapq.heappush(heap, (cost, increment, state))
    increment += 1


def pop():
    return heapq.heappop(heap)


def visit(matrix: list[int]):
    visited.add(tuple(matrix))


push(0, initial)
while len(heap) != 0:
    cost, _, state = pop()
    if state.matrix == goal.matrix:
        print("found,", len(visited), 'states expanded,',
              state.depth, 'depths')
        state.print_trace()
        break
    for i in Direction:
        moved = state.move(i)
        if moved is None or tuple(moved.matrix) in visited:
            continue
        push(moved.depth + heuristics(moved, goal), moved)
        visit(moved.matrix)
