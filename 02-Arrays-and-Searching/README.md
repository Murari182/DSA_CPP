# Arrays, Memory Layout & Searching Algorithms in C++17

A comprehensive module covering array memory representation, row-major vs column-major indexing, pointer arithmetic, linear search, binary search, and search space reduction patterns.

---

## Module Overview

| Document / Code | Description | Key Topics |
|---|---|---|
| [arrays_and_memory_representation.md](./Notes/arrays_and_memory_representation.md) | Contiguous memory, indexing math, static vs dynamic | Byte offsets, 1D/2D memory mapping, cache locality, CPU prefetching |
| [linear_and_binary_search.md](./Notes/linear_and_binary_search.md) | Algorithmic searching & bounds | Linear search, iterative/recursive binary search, search on answer space |
| [Array_Operations.cpp](./Array_Operations.cpp) | Core array operations in C++17 | Insert, delete, rotate, reverse, prefix sums, sliding window |
| [Linear_and_Binary_Search.cpp](./Linear_and_Binary_Search.cpp) | Search implementations & benchmarks | `binary_search`, `lower_bound`, `upper_bound`, edge case handling |

---

## Memory Offset Derivation
In a 1D array of elements of type `T` located at base address `Base`:
```math
\text{Address}(\text{arr}[i]) = \text{Base} + i \times \text{sizeof}(T)
```
In a 2D array of dimensions `R × C` in **Row-Major Order** (standard in C and C++):
```math
\text{Address}(\text{arr}[i][j]) = \text{Base} + (i \times C + j) \times \text{sizeof}(T)
```

## Binary Search Template (Overflow-Safe)
```cpp
int binarySearch(const std::vector<int>& arr, int target) {
    int low = 0, high = static_cast<int>(arr.size()) - 1;
    while (low <= high) {
        // Safe midpoint calculation avoiding integer overflow
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1; // Target not found
}
```
- **Time Complexity:** Best: \( O(1) \), Worst/Average: \( O(\log n) \).
- **Space Complexity:** Iterative: \( O(1) \), Recursive: \( O(\log n) \) call stack.
