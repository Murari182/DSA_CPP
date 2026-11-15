# C++ Fundamentals, OOP & Complexity for DSA

A comprehensive module covering essential C++ concepts, memory management, pointers, references, object-oriented design, and mathematical time/space complexity analysis required for data structures and algorithms.

---

## Module Overview

| Document / Code | Description | Key Topics |
|---|---|---|
| [cpp_fundamentals_and_oop_for_dsa.md](./Notes/cpp_fundamentals_and_oop_for_dsa.md) | Deep guide to C++ memory model & OOP | Stack vs Heap, pointers, references, dynamic memory (`new`/`delete`), classes, Rule of 3/5/0 |
| [time_and_space_complexity.md](./Notes/time_and_space_complexity.md) | Mathematical asymptotic analysis | Big-O, Big-Omega, Big-Theta, recurrence relations, Master Theorem, space complexity |
| [pointers_and_references.cpp](./pointers_and_references.cpp) | Practical C++17 pointers & references code | Pass by value vs reference, pointer arithmetic, memory addresses, const correctness |
| [time_and_space_complexity.cpp](./time_and_space_complexity.cpp) | Code examples demonstrating complexities | O(1), O(log n), O(n), O(n log n), O(n²), recursive stack profiling |

---

## 1. The C++ Memory Model in DSA

```text
+-------------------------------------------------------+
|  STACK MEMORY                                         |
|  - Fast allocation/deallocation via stack pointer     |
|  - Fixed size determined at compile-time / thread init|
|  - Stores: local variables, parameters, call frames   |
+-------------------------------------------------------+
                           |
                           v
+-------------------------------------------------------+
|  HEAP / FREE STORE MEMORY                             |
|  - Dynamic allocation at runtime (malloc, new)        |
|  - Flexible, resizable, manually managed              |
|  - Stores: dynamic arrays, linked list nodes, trees   |
|  - Requires: delete / delete[] or RAII containers     |
+-------------------------------------------------------+
```

### Pointers vs References
- **Pointer (`T*`):** A variable holding the memory address of another variable. Can be re-assigned, can be `nullptr`, supports pointer arithmetic.
- **Reference (`T&`):** An immutable alias for an existing variable. Cannot be null, cannot be re-seated to another object after initialization, behaves syntactically like a direct variable.
- **Rule of Thumb for DSA:** Pass read-only large containers by constant reference (`const std::vector<int>& arr`) to eliminate $ O(n) $ copying overhead!

---

## 2. Asymptotic Complexity Reference

```math
O(1) < O(\log n) < O(\sqrt{n}) < O(n) < O(n \log n) < O(n^2) < O(2^n) < O(n!)
```

### Distinguishing Asymptotic Notations
- **Big-O ($ O $):** Upper Bound. $ f(n) \le c \cdot g(n) $ for all $ n \ge n_0 $. Guarantees the algorithm will run no slower than this bound.
- **Big-Omega ($ \Omega $):** Lower Bound. $ f(n) \ge c \cdot g(n) $. Guarantees the algorithm will take at least this much time in the specified scenario.
- **Big-Theta ($ \Theta $):** Tight Bound. $ c_1 g(n) \le f(n) \le c_2 g(n) $. Captures both upper and lower behavior simultaneously.
