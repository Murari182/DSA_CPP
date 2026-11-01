# Double-Ended Queue (Deque) and Queue Using Stacks

## Related Implementation

- `../Deque_and_Queue_Using_Stacks.cpp` *(Supplementary implementation created for this folder)*
- Related files in this repository:
  - `../queue_02.cpp` *(Circular Array Queue)*
  - `../../04-Linked-Lists/DoubleLinkedList.cpp` *(Doubly Linked List)*

---

## 1. Concept Introduction

### What is the Concept?
1. **Double-Ended Queue (Deque, pronounced "deck")**:
   A generalized queue that supports $O(1)$ insertion and deletion at **both** the `front` and the `rear` (`push_front`, `push_back`, `pop_front`, `pop_back`).
2. **Queue Using Two Stacks (`QueueUsingStacks`)**:
   A classic data structure transformation that simulates **FIFO (Queue)** behavior using two **LIFO (Stack)** instances (`s_in` and `s_out`) in **$O(1)$ amortized time** per operation.

### Why are They Required?
- A **Deque** combines the capabilities of both a Stack and a Queue into a single structure and is required for **Sliding Window Maximum/Minimum** ($O(n)$ monotonic deque) and **0-1 BFS**.
- Implementing a **Queue Using Two Stacks** demonstrates how two LIFO reversals cancel each other out to produce FIFO order ($(\text{Reverse}(\text{Reverse}(\text{Sequence}))) = \text{Sequence}$) and is one of the most frequently asked technical interview problems.

---

## 2. Fundamental Theory

### 1. Circular Array Deque Arithmetic
In `../queue_02.cpp`, `front` and `rare` only move **forward** (`(index + 1) % cap`).
In a **Circular Array Deque**, pointers must be able to move both **forward** and **backward** around the circle:
- **Move Forward (Clockwise)**:
  $$\text{index} = (\text{index} + 1) \bmod \text{cap}$$
- **Move Backward (Counter-Clockwise)**:
  In C++, `(-1) % cap` evaluates to `-1` (negative!). To wrap `-1` safely to `cap - 1`, always add `cap` before taking modulo:
  $$\text{index} = (\text{index} - 1 + \text{cap}) \bmod \text{cap}$$

### 2. How Two LIFO Stacks Produce a FIFO Queue
- **`s_in` (Input Stack)**: Receives all newly enqueued elements via `s_in.push(val)` in $O(1)$ time. The newest element sits at the top of `s_in`, and the oldest element sits at the bottom.
- **`s_out` (Output Stack)**: Serves `dequeue()` and `peek()` requests from its top.
- **Lazy Transfer (`transfer_if_needed()`)**:
  Whenever `dequeue()` or `peek()` is called:
  - If `s_out` is **not empty**, its top element is already the oldest element in the queue—pop or read `s_out.top()` in $O(1)$ time!
  - Only when `s_out` is **completely empty**, pop every element from `s_in` and push it onto `s_out`. This reverses the LIFO order of `s_in`, bringing the oldest element to the top of `s_out`!

---

## 3. Mathematical Representation

### Amortized $O(1)$ Analysis of `QueueUsingStacks`
Suppose we perform a sequence of $m$ operations (`enqueue`, `dequeue`, `peek`) starting from an empty queue.
Track the lifecycle of any single element $x$:
1. $x$ is pushed onto `s_in` **once** ($1$ operation).
2. $x$ is popped from `s_in` **at most once** ($1$ operation).
3. $x$ is pushed onto `s_out` **at most once** ($1$ operation).
4. $x$ is popped from `s_out` **at most once** ($1$ operation).

Thus, across the entire history of $m$ operations, each element undergoes at most $4$ elementary stack operations:
$$\text{Total Cost of } m \text{ Operations} \le 4m = O(m)$$
$$\text{Amortized Cost per Operation} = \frac{O(m)}{m} = O(1)$$

---

## 4. Working Mechanism

### Circular Deque Operations (`Deque` in `../Deque_and_Queue_Using_Stacks.cpp`)
1. **`push_front(val)`**:
   - Check `if (size == cap)` (overflow).
   - Step `front` backward: `front = (front - 1 + cap) % cap`.
   - Store `arr[front] = val`. If `size == 0`, set `rear = front`. Increment `size++`.
2. **`push_back(val)`**:
   - Check `if (size == cap)` (overflow).
   - Step `rear` forward: `rear = (rear + 1) % cap`.
   - Store `arr[rear] = val`. If `size == 0`, set `front = rear`. Increment `size++`.
3. **`pop_front()`**:
   - Check `if (size == 0)` (underflow).
   - Step `front` forward: `front = (front + 1) % cap`. Decrement `size--`.
4. **`pop_back()`**:
   - Check `if (size == 0)` (underflow).
   - Step `rear` backward: `rear = (rear - 1 + cap) % cap`. Decrement `size--`.

---

## 5. Visual Representation

### 1. Circular Deque Pointer Movements
```
push_front(val):  front = (front - 1 + cap) % cap   <-- Moves Left (with wrap-around)
pop_front():      front = (front + 1) % cap         --> Moves Right (with wrap-around)

push_back(val):   rear  = (rear + 1) % cap          --> Moves Right (with wrap-around)
pop_back():       rear  = (rear - 1 + cap) % cap    <-- Moves Left (with wrap-around)
```

### 2. `QueueUsingStacks` Lazy Transfer (`enqueue(100), enqueue(200), enqueue(300), dequeue()`)
```
Before dequeue():                   During transfer_if_needed():
    s_in            s_out               s_in            s_out
  +-------+       +-------+           +-------+       +-------+
  |  300  |       |       |           |       |       |  100  | <-- Oldest is now on top!
  +-------+       +-------+           +-------+       +-------+
  |  200  |       |       |    ===>   |       |       |  200  |
  +-------+       +-------+           +-------+       +-------+
  |  100  |       |       |           |       |       |  300  |
  +-------+       +-------+           +-------+       +-------+
```

---

## 6. C++ Implementation Analysis

### File: `../Deque_and_Queue_Using_Stacks.cpp`

1. **`class Deque`**:
   - Extends your `queue` class from `../queue_02.cpp` by adding counter-clockwise index arithmetic `(idx - 1 + cap) % cap` to support `push_front` and `pop_back` alongside `push_back` and `pop_front`.
   - All four operations execute in strict **$O(1)$ worst-case time** and **$O(1)$ auxiliary space**.
2. **`class QueueUsingStacks`**:
   - Uses two stacks `s_in` and `s_out`.
   - `enqueue(int val)` pushes to `s_in` in $O(1)$ worst-case time.
   - `dequeue()` and `peek()` call `transfer_if_needed()`, running in **$O(1)$ amortized time** ($O(n)$ worst-case only when `s_out` is empty and a batch transfer occurs).

---

## 7. Dry Runs

### Dry Run 1: `Deque dq(10)` in `main()`
| Step | Operation | `front` | `rear` | `size` | Active Deque Sequence (Front $\to$ Rear) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 1 | `Deque dq(10);` | `0` | `-1` | `0` | `[]` |
| 2 | `dq.push_back(10);` | `0` | `0` | `1` | `[10]` (`arr[0] = 10`) |
| 3 | `dq.push_back(20);` | `0` | `1` | `2` | `[10, 20]` (`arr[1] = 20`) |
| 4 | `dq.push_front(5);` | `9` (`(0-1+10)%10`) | `1` | `3` | `[5, 10, 20]` (`arr[9] = 5`) |
| 5 | `dq.pop_front();` | `0` (`(9+1)%10`) | `1` | `2` | `[10, 20]` |

---

## 8. Time Complexity

| Structure & Operation | Best Case | Average / Amortized | Worst Case |
| :--- | :---: | :---: | :---: |
| **`Deque::push_front` / `push_back`** | $O(1)$ | $O(1)$ | $O(1)$ |
| **`Deque::pop_front` / `pop_back`** | $O(1)$ | $O(1)$ | $O(1)$ |
| **`Deque::get_front` / `get_rear`** | $O(1)$ | $O(1)$ | $O(1)$ |
| **`QueueUsingStacks::enqueue`** | $O(1)$ | $O(1)$ | $O(1)$ |
| **`QueueUsingStacks::dequeue` / `peek`** | $O(1)$ | **$O(1)$ amortized** | $O(n)$ (when `s_out` empty) |

---

## 9. Space Complexity

- **Circular Array `Deque`**: $O(\text{cap})$ array storage, $O(1)$ auxiliary space.
- **`QueueUsingStacks`**: $O(n)$ total space across `s_in` and `s_out` (each of the $n$ elements resides in either `s_in` or `s_out`, never both simultaneously).

---

## 10. Important Properties and Observations

1. **Never Transfer into a Non-Empty `s_out`**:
   In `QueueUsingStacks`, `transfer_if_needed()` **must** check `if (s_out.empty())` before transferring elements from `s_in`. If you transferred elements from `s_in` while `s_out` still contained older elements, the newer elements from `s_in` would be placed on top of the older elements in `s_out`, violating FIFO order!
2. **Doubly Linked List vs. Circular Array for Deque**:
   Note that your `DoublyList` in `04-Linked-Lists/Circular_and_Doubly_Linked_List_Complete.cpp` (`push_front`, `push_back`, `pop_front`, `pop_back`) also implements a dynamic Deque in $O(1)$ time per operation!

---

## 11. Advantages and Disadvantages

### Deque
- **Advantages**: Supports both LIFO and FIFO operations at either end in $O(1)$ time.
- **Disadvantages**: Slightly more complex index management than a simple stack or standard queue.

---

## 12. Comparison with Related Concepts

| Operation | Stack | Standard Queue | Deque (Double-Ended Queue) |
| :--- | :---: | :---: | :---: |
| **Insert at Front (`push_front`)** | — | — | **$O(1)$** |
| **Insert at Back (`push_back`)** | $O(1)$ (`push`) | $O(1)$ (`enqueue`) | **$O(1)$** |
| **Remove from Front (`pop_front`)** | — | $O(1)$ (`dequeue`) | **$O(1)$** |
| **Remove from Back (`pop_back`)** | $O(1)$ (`pop`) | — | **$O(1)$** |

---

## 13. Common Mistakes

1. **Writing `(front - 1) % cap` Instead of `(front - 1 + cap) % cap` in C++**:
   When `front == 0`, `(0 - 1) % cap` evaluates to `-1`, causing an out-of-bounds memory access `arr[-1]`. Always add `+ cap` before `% cap`.
2. **Forgetting to Initialize Both `front` and `rear` on the First Insertion (`size == 0`)**:
   When inserting into an empty `Deque`, `front` and `rear` must point to the same single element (`if (size == 0) rear = front;`).

---

## 14. Applications

1. **Sliding Window Maximum (LeetCode 239)**: Using a Monotonic Deque of indices to find the maximum in every window of size $k$ in $O(n)$ total time.
2. **Work-Stealing Thread Schedulers**: Each worker thread pushes/pops its own tasks at the front of its Deque (LIFO for cache locality), while idle threads "steal" tasks from the back (FIFO) of busy threads' Deques.
3. **Palindrome Checker**: Pushing characters into a Deque and comparing `pop_front()` with `pop_back()`.

---

## 15. Practice Questions

1. **Basic Understanding**: Why does `(-1) % 5` evaluate to `-1` in C++, and how does `(-1 + 5) % 5` fix this for circular array backward movement?
2. **Implementation**: Implement the reverse problem: a **Stack Using Queues (`StackUsingQueues`)** where `push`, `pop`, and `top` work using a single `std::queue<int>` by rotating the existing $n - 1$ elements after each `push`.
3. **Dry-Run Problem**: Trace `QueueUsingStacks` on the sequence: `enqueue(1)`, `enqueue(2)`, `dequeue()`, `enqueue(3)`, `enqueue(4)`, `dequeue()`, `peek()`. Show the exact contents of `s_in` and `s_out` after each operation.
4. **Complexity Analysis**: Compare the time complexity of `push` and `pop` in `StackUsingQueues` (which takes $O(n)$ per `push` and $O(1)$ per `pop`) vs. `QueueUsingStacks` (which takes $O(1)$ amortized for both `enqueue` and `dequeue`). Why can two Stacks achieve $O(1)$ amortized Queue operations, whereas two Queues cannot achieve $O(1)$ amortized Stack operations?
5. **Interview Question**: Explain how a **Monotonic Decreasing Deque** solves the **Sliding Window Maximum** problem on an array of size $n$ and window size $k$ in $O(n)$ time and $O(k)$ auxiliary space.

---

## 16. Quick Revision

- **Circular Backward Step**: `index = (index - 1 + cap) % cap;`
- **Circular Forward Step**: `index = (index + 1) % cap;`
- **`QueueUsingStacks`**: Push to `s_in`; pop/peek from `s_out`; transfer all elements from `s_in` to `s_out` **only when `s_out` is empty** $\implies O(1)$ amortized time.
