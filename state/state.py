from __future__ import annotations
from direction.direction import Direction


class State:
    def __init__(self, matrix: tuple[int, ...], parent: State | None = None):
        self.parent = parent
        self.matrix = matrix
        self.depth = 1 if parent is None else parent.depth + 1
        self.zero = self.matrix.index(0)

    def __eq__(self, other: object) -> bool:
        return isinstance(other, State) and self.matrix == other.matrix

    def __hash__(self):
        return hash(self.matrix)

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
        return State(tuple(mtx), self)

    def print_trace(self):
        state = self
        while state is not None:
            print(state.matrix)
            state = state.parent
