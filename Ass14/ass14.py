import sys
import gc

class Node:
    def __init__(self, name):
        self.name = name
        self.link = None

A = Node("A")
B = Node("B")

A.link = B
B.link = A

print("Refcount A:", sys.getrefcount(A))
print("Refcount B:", sys.getrefcount(B))

del A
del B

unreachable = gc.collect()
print("Unreachable objects collected:", unreachable)
