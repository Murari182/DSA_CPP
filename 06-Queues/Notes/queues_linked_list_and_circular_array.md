# Queues: Linked-List Queue and Circular Array Queue

## Related Implementation

- `../Queue_01.cpp` *(Original Linked-List Queue implementation)*
- `../queue_02.cpp` *(Original Circular Array Queue implementation)*

---

## 1. Concept Introduction

### What is the Concept?
A **Queue** is a linear Abstract Data Type (ADT) that follows the **FIFO (First-In, First-Out)** principle: elements are inserted at the back (**`rear`** / `rare`) and removed from the front (**`front`**). The first element that enters the queue is the first element to leave.

### Why is it Required?
Whenever tasks, requests, or tree/graph nodes must be processed in the exact chronological order of their arrival—such as **Level-Order Traversal (BFS)** in `08-Trees/Binary_Tree_01.cpp` (`queue<Node*> q;`), printer spoolers, or CPU scheduling—a FIFO Queue is required.

### How is it Implemented in Your Folder `06-Queues`?
You implemented both foundational representations of a Queue:
1. **Dynamic Linked-List Queue (`../Queue_01.cpp`)**: Uses `Node` objects and two pointers `Node *front` and `Node *rear`.
2. **Circular Array Queue (`../queue_02.cpp`)**: Uses `int arr[100]`, capacity `cap`, `front`, `rare`, and `size` with **modulo wrap-around arithmetic** (`(rare + 1) % cap` and `(front + 1) % cap`).

---

## 2. Fundamental Theory

### Why a Simple Linear Array Queue Fails ("False Overflow")
Suppose we implement a queue of capacity `cap = 5` in an array without modulo arithmetic by incrementing `rear++` on `enqueue` and `front++` on `dequeue`.
After 5 `enqueue` operations (`rear = 4`) and 3 `dequeue` operations (`front = 3`), only 2 elements remain in the queue, and slots `0, 1, 2` at the beginning of the array are completely empty. Yet `rear == cap - 1` (`4`), so we cannot insert a new element at `rear + 1`!
If we shifted all elements left on every `dequeue`, `dequeue` would degrade from $O(1)$ to $O(n)$.

### The Circular Array Solution (`../queue_02.cpp`)
By treating the array indices `0 .. cap - 1` as a **circle** using the modulo operator `% cap`:
- Advancing `rare` wraps around from `cap - 1` back to `0`:
  $$\text{rare} = (\text{rare} + 1) \bmod \text{cap}$$
- Advancing `front` wraps around from `cap - 1` back to `0`:
  $$\text{front} = (\text{front} + 1) \bmod \text{cap}$$
This reuses vacated slots at the front of the array while keeping both `enqueue` and `pop` (dequeue) strictly **$O(1)$**!

---

## 3. Mathematical Representation

### 1. Circular Array Queue Equations (`queue_02.cpp`)
Given capacity $\text{cap} > 0$, current element count $\text{size} \in [0, \text{cap}]$, initial $\text{front} = 0$, and initial $\text{rare} = -1$:
- **Empty Condition**:
  $$\text{size} == 0$$
- **Full Condition**:
  $$\text{size} == \text{cap}$$
- **Enqueue Index Update**:
  $$\text{rare} \leftarrow (\text{rare} + 1) \bmod \text{cap}, \quad \text{size} \leftarrow \text{size} + 1$$
- **Dequeue (`pop`) Index Update**:
  $$\text{front} \leftarrow (\text{front} + 1) \bmod \text{cap}, \quad \text{size} \leftarrow \text{size} - 1$$

### 2. Linked-List Queue Pointer Assignments (`Queue_01.cpp`)
- **Empty State**: `front == NULL` and `rear == NULL`.
- **Single-Element State**: `front == rear` and `front->next == NULL`.

---

## 4. Working Mechanism

### 1. Linked-List Queue (`../Queue_01.cpp`)
- **`enque(int val)`** (Inserts at `rear` — tail of linked list):
  1. Allocates `Node *n1 = new Node(val);`.
  2. If `rear == NULL` (queue is empty), sets both `front = n1` and `rear = n1`.
  3. Otherwise, links `rear->next = n1` and updates `rear = n1`.
- **`dequeue()`** (Removes from `front` — head of linked list):
  1. If only 1 node remains (`front->next == NULL`), deletes `front` and resets both `front = NULL` and `rear = NULL`.
  2. Otherwise, saves `Node *temp = front`, advances `front = front->next`, and calls `delete temp`.
- **`peek()`**:
  Checks `if (front == NULL)` and prints `front->data`.

### 2. Circular Array Queue (`../queue_02.cpp`)
- **`enqueue(int val)`**:
  1. Checks `if (size == cap)` $\to$ prints `"Queue is Full"` and returns.
  2. Computes `rare = (rare + 1) % cap;`, stores `arr[rare] = val;`, and increments `size++`.
- **`pop()`**:
  1. Checks `if (size == 0)` $\to$ prints `"Queue Underflow"` and returns.
  2. Advances `front = (front + 1) % cap;` and decrements `size--`.
- **`peek()`**:
  Checks `if (size == 0)` and prints `arr[front]`.

---

## 5. Visual Representation

### Circular Wrap-Around in `queue_02.cpp` (`cap = 5`)
```
Step 1: After 5 enqueues (0, 10, 20, 30, 40) -> size = 5 (FULL)
Index:     0      1      2      3      4
        +------+------+------+------+------+
        |   0  |  10  |  20  |  30  |  40  |
        +------+------+------+------+------+
            ^                           ^
          front = 0                   rare = 4

Step 2: After q.pop() -> front = (0 + 1) % 5 = 1, size = 4
Index:     0      1      2      3      4
        +------+------+------+------+------+
        |  (0) |  10  |  20  |  30  |  40  |
        +------+------+------+------+------+
                   ^                    ^
                 front = 1            rare = 4

Step 3: After q.enqueue(60) -> rare = (4 + 1) % 5 = 0 (WRAPS AROUND!), size = 5
Index:     0      1      2      3      4
        +------+------+------+------+------+
        |  60  |  10  |  20  |  30  |  40  |
        +------+------+------+------+------+
            ^      ^
        rare=0   front=1
```

---

## 6. C++ Implementation & Code Review (`Queue_01.cpp` & `queue_02.cpp`)

### 1. File: `../Queue_01.cpp` (Linked-List Queue)
- **Why `enque` is at `rear` (Tail) and `dequeue` is at `front` (Head)**:
  In a Singly Linked List with `front` (head) and `rear` (tail), inserting at the tail (`rear->next = n1; rear = n1;`) is $O(1)$, and deleting from the head (`front = front->next;`) is $O(1)$. If you reversed the roles and tried to dequeue from the tail, it would take $O(n)$ time!
- **Important Edge Case Observation in `dequeue()` (Lines 50–62 of `Queue_01.cpp`)**:
  *(Documented here without modifying `Queue_01.cpp`)*
  ```cpp
    void dequeue(){

        if(front->next == NULL){
            delete front;
            front = NULL;
            rear = NULL;
            return;
        }
  ```
  - **What happens when the queue is already empty (`front == NULL`)**:
    If `dequeue()` is called when `front == NULL`, evaluating `if (front->next == NULL)` on line 52 dereferences a `NULL` pointer!
  - **Conceptual Guard**: Add an empty-queue check right before line 52:
    ```cpp
    if (front == NULL) {
        cout << "The que is Empty" << endl;
        return;
    }
    ```
  - Also notice how well your code handles the **single-element deletion case** (`if (front->next == NULL)`): it resets **both** `front = NULL` and `rear = NULL`. Forgetting to reset `rear = NULL` when the last element is dequeued is one of the most common linked-queue bugs, and your code handled it properly!

### 2. File: `../queue_02.cpp` (Circular Array Queue)
- Clean, bug-free circular buffer design using `int size` to distinguish between a full queue (`size == cap`) and an empty queue (`size == 0`) without wasting a slot in the array.

---

## 7. Dry Runs

### Dry Run 1: `main()` in `../Queue_01.cpp`
| Step | Operation | `front` | `rear` | Queue State | Console Output |
| :---: | :--- | :---: | :---: | :--- | :--- |
| 1 | `que q1;` | `NULL` | `NULL` | Empty | — |
| 2 | `q1.enque(10);` | `[10]` | `[10]` | `10 -> NULL` | — |
| 3 | `q1.dequeue();` | `NULL` | `NULL` | Empty (`front->next == NULL` branch) | — |
| 4 | `q1.peek();` | `NULL` | `NULL` | Empty | `The que is Empty` |

### Dry Run 2: `main()` in `../queue_02.cpp` (`cap = 5`)
| Step | Operation | `front` | `rare` | `size` | Array `arr[0..4]` | Output |
| :---: | :--- | :---: | :---: | :---: | :--- | :--- |
| 1 | `queue q(5);` | `0` | `-1` | `0` | `[_, _, _, _, _]` | — |
| 2 | Loop `i=0..4`: `enqueue(i*10)` | `0` | `4` | `5` | `[0, 10, 20, 30, 40]` | — |
| 3 | `q.peek();` | `0` | `4` | `5` | `[0, 10, 20, 30, 40]` | `0` |
| 4 | `q.pop();` | `1` | `4` | `4` | `[0, 10, 20, 30, 40]` | — |
| 5 | `q.enqueue(60);` | `1` | `0` (`(4+1)%5`) | `5` | `[60, 10, 20, 30, 40]` | — |
| 6 | `q.peek();` | `1` | `0` | `5` | `[60, 10, 20, 30, 40]` | `10` |

---

## 8. Time Complexity

| Operation | Linked Queue (`Queue_01.cpp`) | Circular Array Queue (`queue_02.cpp`) | Naive Linear Array Queue (with shift) |
| :--- | :---: | :---: | :---: |
| **Enqueue (`enque` / `enqueue`)** | $O(1)$ | $O(1)$ | $O(1)$ |
| **Dequeue (`dequeue` / `pop`)** | $O(1)$ | **$O(1)$** | $O(n)$ (shifts all elements left) |
| **Peek (`peek`)** | $O(1)$ | $O(1)$ | $O(1)$ |

---

## 9. Space Complexity

- **Linked Queue (`Queue_01.cpp`)**: $O(n)$ dynamic heap memory ($1$ `Node* next` pointer per element), $O(1)$ auxiliary space per operation.
- **Circular Array Queue (`queue_02.cpp`)**: $O(\text{cap})$ static array memory, $O(1)$ auxiliary space per operation.

---

## 10. Important Properties and Observations

1. **Why Tracking `int size` in `queue_02.cpp` Simplifies Circular Queue Logic**:
   When a circular queue does **not** store `int size`, both the empty state and the full state have `front == (rare + 1) % cap`! Without `size`, you must either waste 1 array slot (`cap - 1` max elements) or set `front = rare = -1` on empty. By maintaining `int size` in `queue_02.cpp`, `size == 0` (empty) and `size == cap` (full) are completely unambiguous and all `cap` slots can be used!

---

## 11. Advantages and Disadvantages

### Linked-List Queue (`Queue_01.cpp`)
- **Advantages**: No fixed capacity limit; allocates only as many nodes as currently needed.
- **Disadvantages**: Pointer memory overhead and heap allocation cost per node.

### Circular Array Queue (`queue_02.cpp`)
- **Advantages**: Zero dynamic allocation overhead, cache-friendly, reuses array slots in $O(1)$ via modulo arithmetic.
- **Disadvantages**: Fixed maximum capacity `cap`.

---

## 12. Comparison with Related Concepts

| Feature | Linked-List Queue (`Queue_01.cpp`) | Circular Array Queue (`queue_02.cpp`) |
| :--- | :--- | :--- |
| **Storage Type** | Non-contiguous heap nodes | Contiguous circular buffer |
| **Overflow Condition** | Only if system RAM is full | `size == cap` |
| **Underflow Condition** | `front == NULL` | `size == 0` |
| **Wrap-Around Mechanism** | Not needed (nodes freed via `delete`) | `(index + 1) % cap` |

---

## 13. Common Mistakes

1. **Forgetting to Set `rear = NULL` When Dequeuing the Last Node in a Linked Queue**:
   If `front` becomes `NULL` after `dequeue()` but `rear` still points to the deleted node, `rear` becomes a **dangling pointer**, and the next `enque()` (`if (rear == NULL)`) will fail to recognize that the queue is empty! (Your `if (front->next == NULL)` block in `Queue_01.cpp` properly sets both `front = NULL` and `rear = NULL`.)
2. **Using `rare++` Instead of `rare = (rare + 1) % cap` in an Array Queue**:
   Causes out-of-bounds array access or false overflow once `rare` reaches `cap - 1`.

---

## 14. Applications

1. **Tree Level-Order Traversal (`08-Trees/Binary_Tree_01.cpp`)** and **Graph Breadth-First Search (BFS)** for shortest paths in unweighted graphs.
2. **Operating System Ready Queue & I/O Buffers**.
3. **Producer-Consumer Ring Buffers** in networking and audio/video streaming.

---

## 15. Practice Questions

1. **Basic Understanding**: In a Circular Array Queue of capacity `cap = 8` with `front = 5` and `size = 6`, what is the current index of `rare`?
2. **Implementation**: Write a `display()` method for `queue_02.cpp` that prints all `size` elements in FIFO order from `front` to `rare` even when `rare < front` (wrapped around). *(Hint: Loop `i` from `0` to `size - 1` and access `arr[(front + i) % cap]`!)*
3. **Dry-Run Problem**: Trace `queue_02.cpp` with `cap = 4` for: `enqueue(10)`, `enqueue(20)`, `enqueue(30)`, `pop()`, `pop()`, `enqueue(40)`, `enqueue(50)`, `peek()`. Show `front`, `rare`, and `size` at every step.
4. **Complexity Analysis**: Without using `int size`, how can you distinguish between an empty circular queue and a full circular queue using only `front`, `rare`, and `cap`?
5. **Interview Question**: How do you reverse the first $k$ elements of a Queue in $O(n)$ time using an auxiliary Stack?

---

## 16. Quick Revision

- **FIFO**: First-In, First-Out (`enqueue` at `rear`/`rare`, `dequeue`/`pop` at `front`).
- **Circular Array Formulas**:
  - `rare = (rare + 1) % cap;`
  - `front = (front + 1) % cap;`
  - Empty: `size == 0`; Full: `size == cap`.
- **Linked Queue**: `enque` at `rear` (tail), `dequeue` at `front` (head) — both $O(1)$.
