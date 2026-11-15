# Heaps & Priority Queues

A dedicated reference module for Min-Heaps, Max-Heaps, Binary Heaps, and the C++ Standard Template Library container adapter `std::priority_queue`.

---

## Architecture & Code Links

The core binary heap data structures and heap sorting implementations are detailed in the [08-Trees module](../08-Trees/):

- **Comprehensive Notes:** [binary_heaps_and_heap_sort.md](../08-Trees/Notes/binary_heaps_and_heap_sort.md)
- **Detailed Explanation Code:** [Binary_Heap_Detailed_Explanation.cpp](../08-Trees/Binary_Heap_Detailed_Explanation.cpp)
- **In-Place Heap Sort Code:** [06_heap_sort.cpp](../03-Sorting/06_heap_sort.cpp)
- **Tree Documentation:** [08-Trees/README.md](../08-Trees/README.md)

---

## STL `std::priority_queue` Quick Reference

In C++, `#include <queue>` provides `std::priority_queue`:

### 1. Max-Heap (Default)
```cpp
#include <queue>
#include <vector>

// Stores largest element on top
std::priority_queue<int> maxHeap;
maxHeap.push(10);
maxHeap.push(30);
maxHeap.push(20);

int topVal = maxHeap.top(); // 30
maxHeap.pop(); // Removes 30 in O(log n)
```

### 2. Min-Heap
```cpp
// Stores smallest element on top
std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
minHeap.push(10);
minHeap.push(30);
minHeap.push(20);

int topVal = minHeap.top(); // 10
minHeap.pop(); // Removes 10 in O(log n)
```

### 3. Top-K Pattern
- To find **K Largest Elements**: Maintain a Min-Heap of size \( K \). For each element, if greater than `minHeap.top()`, pop and push. Remaining heap contains the K largest elements in \( O(n \log K) \) time!
- To find **K Smallest Elements**: Maintain a Max-Heap of size \( K \).
