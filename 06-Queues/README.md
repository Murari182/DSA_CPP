# Queues, Deques & Circular Buffers in Modern C++17

A comprehensive module covering the First-In-First-Out (FIFO) discipline, array and linked-list implementations, circular queue index wrapping, double-ended queues (deques), and queue-stack simulations.

---

## Module Overview

| Document / Code | Description | Key Topics |
|---|---|---|
| [queues_linked_list_and_circular_array.md](./Notes/queues_linked_list_and_circular_array.md) | Queue architectures & modular arithmetic | Front/rear pointers, modulo index wrap, linked-list queues |
| [deque_and_queue_variations.md](./Notes/deque_and_queue_variations.md) | Advanced queues | Deque, priority queues, circular buffer, sliding window maximum |
| [Deque_and_Queue_Using_Stacks.cpp](./Deque_and_Queue_Using_Stacks.cpp) | Queue using two stacks & deque | Amortized \( O(1) \) queue operations using 2 LIFO stacks |
| [Queue_01.cpp](./Queue_01.cpp) & [queue_02.cpp](./queue_02.cpp) | Queue implementations | Array-based and linked-list queue implementations |

---

## Circular Queue Index Wrapping Mathematics
In a linear array queue, dequeuing causes the `front` pointer to advance, creating unfillable dead space at the beginning of the array. The **Circular Queue** solves this by using modular arithmetic:
```math
\text{Next Rear} = (\text{rear} + 1) \pmod{\text{Capacity}}
```
```math
\text{Next Front} = (\text{front} + 1) \pmod{\text{Capacity}}
```
- **Full Condition:** `(rear + 1) % Capacity == front`
- **Empty Condition:** `front == -1` (or `size == 0`)
- **Advantage:** Enables continuous reuse of buffer space in \( O(1) \) time with zero shifting!
