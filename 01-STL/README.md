# C++ Standard Template Library (STL) for DSA

A comprehensive module covering STL containers, iterators, function objects, and algorithms essential for high-performance competitive programming and technical interviews.

---

## Module Overview

| Document / Code | Description | Key Topics |
|---|---|---|
| [stl_list_iterators_and_containers.md](./Notes/stl_list_iterators_and_containers.md) | Deep guide to STL containers & mechanics | Sequence containers, associative containers, unordered containers, iterators |
| [STL.cpp](./STL.cpp) | Hands-on STL fundamentals | Vector basics, iterators, common operations |
| [STL_Containers_and_Algorithms.cpp](./STL_Containers_and_Algorithms.cpp) | Comprehensive STL algorithms suite | `std::sort`, `std::binary_search`, `std::lower_bound`, `std::upper_bound`, `std::transform` |

---

## STL Container Complexity Reference

| Container | Underlying Structure | Access | Insert/Delete (Front) | Insert/Delete (Back) | Search |
|---|---|---|---|---|---|
| `std::vector` | Dynamic contiguous array | \( O(1) \) | \( O(n) \) | \( O(1) \) amortized | \( O(n) \) / \( O(\log n) \) (sorted) |
| `std::deque` | Array of fixed-size chunks | \( O(1) \) | \( O(1) \) | \( O(1) \) | \( O(n) \) |
| `std::list` | Doubly linked list | \( O(n) \) | \( O(1) \) | \( O(1) \) | \( O(n) \) |
| `std::set` / `std::map` | Red-Black Tree (Self-balancing BST) | — | \( O(\log n) \) | \( O(\log n) \) | \( O(\log n) \) |
| `std::unordered_set` / `std::unordered_map` | Hash Table with Separate Chaining | — | Avg: \( O(1) \), Worst: \( O(n) \) | Avg: \( O(1) \), Worst: \( O(n) \) | Avg: \( O(1) \), Worst: \( O(n) \) |
| `std::priority_queue` | Binary Heap | Top: \( O(1) \) | — | Push/Pop: \( O(\log n) \) | — |
