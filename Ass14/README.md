# Garbage Collection Demo with Cyclic References

This assignment demonstrates how Python's garbage collector handles objects that are part of a reference cycle.

## Scenario
We create two `Node` objects that reference each other, forming a cycle. Even after deleting the variables, the objects remain alive because their reference count stays above zero due to the cycle.

## Implementation Steps
1. **Create a `Node` class** with a `name` and a `link` attribute.
2. **Create a cycle** by instantiating Node A and Node B and setting `A.link = B` and `B.link = A`.
3. **Check references** using `sys.getrefcount()` to show that both objects have multiple references.
4. **Deletion**: use `del A` and `del B` to remove the external references.
5. **Investigation**: use the `gc` module to show that these objects are still present in memory because of the cycle.
6. **Cleanup**: call `gc.collect()` and print the number of *unreachable* objects collected.

## Example Code
```python
import sys
import gc

class Node:
    def __init__(self, name):
        self.name = name
        self.link = None

    def __repr__(self):
        return f"Node({self.name})"

# Step 1 & 2: Create nodes and a cycle
A = Node('A')
B = Node('B')
A.link = B
B.link = A

# Step 3: Check reference counts
print('Refcount A before del:', sys.getrefcount(A))
print('Refcount B before del:', sys.getrefcount(B))

# Step 4: Delete external references
del A
del B

# Step 5: Objects are still tracked by gc because of the cycle
print('Objects tracked by gc before collect:', len(gc.get_objects()))

# Step 6: Force garbage collection
collected = gc.collect()
print('Unreachable objects collected:', collected)
print('Objects tracked by gc after collect:', len(gc.get_objects()))
```

Running this script will illustrate that reference counts stay > 1 due to the cycle, `del` removes external names but the objects persist, and `gc.collect()` reclaims them.
