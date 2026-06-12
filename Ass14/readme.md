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
