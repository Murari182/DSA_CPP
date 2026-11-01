# Stacks: Array-Based and Linked-List-Based Implementations

## Related Implementation

- `../stack_01.cpp` *(Original Array-Based Stack implementation)*
- `../stack_02.cpp` *(Original Linked-List-Based Stack implementation)*

---

## 1. Concept Introduction

### What is the Concept?
A **Stack** is a linear Abstract Data Type (ADT) that restricts insertions and deletions to a **single end** called the **`top`**. It operates strictly on the **LIFO (Last-In, First-Out)** principle: the last element pushed onto the stack is the first element popped off.

### Why is it Required?
Many computational processes naturally require reversing order or remembering the most recent state and returning to it once nested work finishes—such as function call frames on the CPU call stack, undo history, expression parsing, and Depth-First Search (DFS) / recursion.

### How is it Implemented in Your Folder `05-Stacks`?
You implemented both classic physical representations of a Stack:
1. **Contiguous Array Representation (`../stack_01.cpp`)**: Uses `int arr[100]`, capacity `cap`, and an integer index `int top` initialized to `-1`.
2. **Dynamic Linked List Representation (`../stack_02.cpp`)**: Uses dynamically allocated `Node` objects and a single pointer `Node *top` initialized to `NULL`.

---

## 2. Fundamental Theory

### Core Stack Operations
1. **`push(val)`**: Inserts `val` at the `top` of the stack.
   - If an array-based stack is already at maximum capacity (`top == cap - 1`), a **Stack Overflow** occurs.
2. **`pop()`**: Removes the element currently at the `top` of the stack.
   - If the stack is empty (`top == -1` in array stack, or `top == NULL` in linked stack), a **Stack Underflow** occurs.
3. **`peek()` (or `top()`)**: Reads and displays the element at `top` without removing it.
4. **`empty()`**: Checks whether the stack contains zero elements.
5. **`size()`**: Returns the number of elements currently in the stack (`top + 1` in array-based stack).

---

## 3. Mathematical Representation

### Array-Based Stack State Equations (`stack_01.cpp`)
Let `cap` be the capacity of the stack and `top` be the 0-based index of the current top element:
- **Empty Stack Invariant**:
  $$\text{top} = -1$$
- **Current Number of Elements (`size`)**:
  $$\text{size} = \text{top} + 1$$
- **Full Stack (Overflow) Condition**:
  $$\text{top} == \text{cap} - 1 \iff \text{size} == \text{cap}$$
- **Push State Transition** (when $\text{top} < \text{cap} - 1$):
  $$\text{top} \leftarrow \text{top} + 1, \quad \text{arr}[\text{top}] \leftarrow \text{val}$$
- **Pop State Transition** (when $\text{top} \ge 0$):
  $$\text{top} \leftarrow \text{top} - 1$$

---

## 4. Working Mechanism

### 1. Array-Based Stack (`../stack_01.cpp`)
- **Initialization (`stack(int cap)`)**: Sets `this->cap = cap` and `top = -1`.
- **`push(int val)`**:
  1. Checks `if (top == cap - 1)` $\to$ prints `"StackOverFlow"` and returns.
  2. Increments `top++` and assigns `arr[top] = val;`.
- **`pop()`**:
  1. Checks `if (top == -1)` $\to$ prints `"The Stack is Empty"` and returns.
  2. Decrements `top--;` (logically removing `arr[top]` in $O(1)$ without needing to zero out the memory cell).
- **`Display()`**:
  Iterates `for (int i = top; i >= 0; i--)` so elements are printed from **top to bottom** in LIFO order.

### 2. Linked-List-Based Stack (`../stack_02.cpp`)
- **Why `top` is Placed at the `head` of the Singly Linked List**:
  In a Singly Linked List, both inserting at the head (`push_front`) and deleting from the head (`pop_front`) take **$O(1)$ time**. (If `top` were placed at the `tail`, `pop()` would require $O(n)$ time to find the node before `tail`!)
- **`push(int val)`**:
  1. Allocates `Node *n1 = new Node(val);`.
  2. Links `n1->next = top;` and updates `top = n1;`.
- **`pop()`**:
  1. Checks `if (top == NULL)` $\to$ prints `"The Stack is Empty"` and returns.
  2. Saves `Node *temp = top;`, advances `top = top->next;`, and frees memory with `delete temp;`.

---

## 5. Visual Representation

### 1. Array-Based Stack (`stack_01.cpp`) vs. Linked-List Stack (`stack_02.cpp`)
```
ARRAY-BASED STACK (stack_01.cpp)            LINKED-LIST STACK (stack_02.cpp)
cap = 20, after pushing 10, 20, 30:         After pushing 10, 20, 30:

Index   arr[]                               top
        +----+                               |
  3     |    |                               v
        +----+                             +----+----+
  2     | 30 | <-- top = 2                 | 30 |  --|----+
        +----+                             +----+----+    |
  1     | 20 |                                            v
        +----+                                          +----+----+
  0     | 10 |                                          | 20 |  --|----+
        +----+                                          +----+----+    |
 -1     (empty when top == -1)                                         v
                                                                     +----+----+
                                                                     | 10 |NULL|
                                                                     +----+----+
```

---

## 6. C++ Implementation Analysis

### 1. File: `../stack_01.cpp` (Array Implementation)
- **Data Members**: `int arr[100]; int cap; int top;` (private by default in `class stack`).
- **Constructor `stack(int cap)`**: Sets user-defined logical capacity `cap` (up to physical array size `100`) and `top = -1`.
- **Methods**:
  - `push(int val)`: $O(1)$ time. Checks overflow `top == cap - 1`.
  - `pop()`: $O(1)$ time. Checks underflow `top == -1`.
  - `peek()`: $O(1)$ time. Prints `arr[top]`.
  - `empty()`: $O(1)$ time. Prints whether `top == -1`.
  - `Display()`: $O(n)$ time. Prints from `top` down to `0`.
  - `size()`: $O(1)$ time. Prints `top + 1`.

### 2. File: `../stack_02.cpp` (Linked List Implementation)
- **Classes**: `Node` (`int data; Node *next; friend class stack;`) and `stack` (`Node *top;`).
- **Constructor `stack()`**: Initializes `top = NULL`.
- **Methods**:
  - `push(int val)`: Allocates node on heap and prepends to `top` in $O(1)$ time.
  - `peek()`: Prints `top->data` in $O(1)$ time.
  - `pop()`: Unlinks `top` and calls `delete temp;` in $O(1)$ time (no memory leak!).

---

## 7. Dry Runs

### Dry Run 1: `main()` in `../stack_01.cpp`
| Step | Function Call | `top` | Stack Contents (`arr[0..top]`) | Console Output |
| :---: | :--- | :---: | :--- | :--- |
| 1 | `stack s(20); s.empty();` | `-1` | `[]` | `The Stack is Empty` |
| 2 | `s.push(10);` + loop `i=2..10` | `9` | `[10, 20, 30, 40, 50, 60, 70, 80, 90, 100]` | — |
| 3 | `s.empty();` | `9` | `[10 .. 100]` | `The Stack is Not Empty` |
| 4 | `s.peek();` | `9` | `[10 .. 100]` | `100` |
| 5 | `s.Display();` | `9` | `[10 .. 100]` | `100 90 80 70 60 50 40 30 20 10 ` |
| 6 | `s.pop();` | `8` | `[10 .. 90]` | — |
| 7 | `s.Display();` | `8` | `[10 .. 90]` | `90 80 70 60 50 40 30 20 10 ` |
| 8 | `s.size();` | `8` | `[10 .. 90]` | `Size of stack: 9` |

### Dry Run 2: `main()` in `../stack_02.cpp`
| Step | Operations | `top->data` | Linked Chain from `top` | Console Output |
| :---: | :--- | :---: | :--- | :--- |
| 1 | `s1.push(10); s1.peek();` | `10` | `10 -> NULL` | `10` |
| 2 | `s1.push(20); s1.push(30); s1.peek();` | `30` | `30 -> 20 -> 10 -> NULL` | `30` |
| 3 | Push `40, 50, 60, 70, 80`; `s1.peek();` | `80` | `80 -> 70 -> ... -> 10 -> NULL` | `80` |
| 4 | `s1.pop(); s1.peek();` | `70` | `70 -> 60 -> ... -> 10 -> NULL` | `70` |

---

## 8. Time Complexity

| Operation | Array Stack (`stack_01.cpp`) | Linked List Stack (`stack_02.cpp`) | Explanation |
| :--- | :---: | :---: | :--- |
| **`push(val)`** | $O(1)$ | $O(1)$ | Increments `top` index or updates `top` head pointer |
| **`pop()`** | $O(1)$ | $O(1)$ | Decrements `top` index or deletes `top` head node |
| **`peek()`** | $O(1)$ | $O(1)$ | Reads `arr[top]` or `top->data` |
| **`empty()` / `size()`** | $O(1)$ | $O(1)$ | Checks `top == -1` / `top == NULL` |
| **`Display()`** | $O(n)$ | $O(n)$ | Visits all $n$ elements from `top` down |

---

## 9. Space Complexity

- **Array-Based Stack (`stack_01.cpp`)**:
  - Static buffer `int arr[100]` uses $O(\text{cap})$ memory regardless of current number of elements.
  - Zero pointer overhead per element.
- **Linked-List Stack (`stack_02.cpp`)**:
  - Uses $O(n)$ dynamic heap memory proportional to the exact number of elements currently in the stack, plus 1 pointer (`Node* next`) per node.

---

## 10. Important Properties and Observations

1. **Notice `push(int val)` Simplification in `stack_02.cpp` (Lines 27–37)**:
   In `stack_02.cpp`, you wrote:
   ```cpp
   if (top == NULL) {
       top = n1;
       return;
   }
   n1->next = top;
   top = n1;
   ```
   Observe that even when `top == NULL`, executing `n1->next = top;` sets `n1->next = NULL` and `top = n1;` sets `top` to `n1`! Both the explicit `if (top == NULL)` branch and the general branch perform the exact same logic.
2. **Lifespan of Popped Elements in `stack_01.cpp`**:
   When `pop()` executes `top--;` in `stack_01.cpp`, the old value at `arr[top + 1]` still physically sits in the array until overwritten by a future `push()`, which is why `top` alone defines the logical boundary of the stack.

---

## 11. Advantages and Disadvantages

### Array-Based Stack (`stack_01.cpp`)
- **Advantages**: Fast (no `new`/`delete` heap calls), cache-friendly, no pointer memory overhead.
- **Disadvantages**: Fixed maximum capacity (`StackOverFlow` when `top == cap - 1`).

### Linked-List Stack (`stack_02.cpp`)
- **Advantages**: Grows and shrinks dynamically at runtime; never overflows unless system RAM is exhausted.
- **Disadvantages**: Extra memory for `next` pointer in every node; slightly slower due to heap allocation (`new`/`delete`) on every `push`/`pop`.

---

## 12. Comparison with Related Concepts

### Stack (`05-Stacks`) vs. Queue (`06-Queues`)

| Feature | Stack (`stack_01.cpp`, `stack_02.cpp`) | Queue (`Queue_01.cpp`, `queue_02.cpp`) |
| :--- | :--- | :--- |
| **Ordering Principle** | **LIFO** (Last-In, First-Out) | **FIFO** (First-In, First-Out) |
| **Active Ends** | Single end (`top` for both `push` & `pop`) | Two ends (`rear` for `enqueue`, `front` for `dequeue`) |
| **Linked List Pointers Needed** | 1 (`Node *top`) | 2 (`Node *front` and `Node *rear`) |
| **Tree/Graph Traversal Use** | Depth-First Search (DFS) / Recursion | Breadth-First Search (BFS) / `Level_Order` |

---

## 13. Common Mistakes

1. **Initializing `top = 0` Instead of `top = -1` Without Adjusting `push`/`pop`**:
   When `top = -1` (as in `stack_01.cpp`), `push` increments **first** (`top++; arr[top] = val;`) and `pop` decrements **after** reading (`val = arr[top]; top--;`). Mixing up pre-increment and post-increment causes off-by-one bugs.
2. **Placing Linked Stack `top` at the Tail Instead of the Head**:
   Always push and pop at the **head** of a singly linked list ($O(1)$), never the tail ($O(n)$ for `pop`).

---

## 14. Applications

1. **Function Call Stack** in C++ recursion (`07-Recursion-and-Backtracking`).
2. **Infix-to-Postfix Conversion & Expression Evaluation** (`hello.cpp` and `Infix_to_Postfix_and_Evaluation.cpp`).
3. **Balanced Parentheses / Syntax Checking** in compilers.
4. **Monotonic Stack Problems** (Next Greater Element, Largest Rectangle in Histogram, Stock Span).

---

## 15. Practice Questions

1. **Basic Understanding**: If elements `1, 2, 3, 4, 5` are pushed onto a stack in that order (with `pop` operations allowed at any time), why is the pop sequence `3, 5, 4, 1, 2` impossible, while `3, 5, 4, 2, 1` is possible?
2. **Implementation**: Implement **Two Stacks in a Single Array** `int arr[100]` (`class TwoStacks`) so that neither stack overflows until the sum of both stacks' sizes reaches `100`. *(Hint: Grow `top1` upward from `-1` and `top2` downward from `100`!)*
3. **Dry-Run Problem**: Trace `stack_01.cpp` with `cap = 3` on the sequence: `push(10)`, `push(20)`, `push(30)`, `push(40)`, `pop()`, `pop()`, `peek()`, `size()`.
4. **Complexity Analysis**: How can you design a `MinStack` class that supports `push(val)`, `pop()`, `peek()`, and `getMin()` (returning the minimum element in the stack) all in **$O(1)$ worst-case time**?
5. **Interview Question**: How do you reverse a Stack using only recursion and stack operations (`push`, `pop`, `empty`) without using any other data structure?

---

## 16. Quick Revision

- **LIFO**: Last-In, First-Out.
- **Array Stack (`stack_01.cpp`)**: `top = -1` (empty); `top == cap - 1` (full); `size = top + 1`.
- **Linked Stack (`stack_02.cpp`)**: `top = NULL` (empty); `push` and `pop` operate at the linked list head in $O(1)$ time.
