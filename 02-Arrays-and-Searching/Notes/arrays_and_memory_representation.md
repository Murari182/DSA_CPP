# Arrays and Contiguous Memory Representation

## Related Implementation

- `../Array_Operations.cpp` *(Supplementary implementation created for this folder)*
- Also used as the underlying storage in:
  - `../../05-Stacks/stack_01.cpp` (`int arr[100];`)
  - `../../06-Queues/queue_02.cpp` (`int arr[100];`)
  - `../../08-Trees/Binary_Tree_Array.cpp` (`int arr[100];`)
  - `../../08-Trees/Binary_Heap.cpp` (`int arr[100];`)

---

## 1. Concept Introduction

### What is the Concept?
An **Array** is a linear, homogeneous data structure that stores a fixed-size collection of elements of the **same data type** in **contiguous (adjacent) memory locations**.

### Why is it Required?
Because elements are stored contiguously without gaps, the memory address of any element at index $i$ can be computed in a single arithmetic operation from the base address. This provides **$O(1)$ Random Access**—the ability to read or write any element instantly regardless of the array size $n$.

### What Problem Does it Solve?
Without arrays, storing $n$ values would require either $n$ separate variables or a pointer-linked structure where reaching the $i$-th element requires traversing $i$ pointers in $O(i)$ time. Arrays serve as the foundational building block for stacks (`stack_01.cpp`), circular queues (`queue_02.cpp`), binary heaps (`Binary_Heap.cpp`), and hash tables.

---

## 2. Fundamental Theory

### Core Properties of an Array
1. **Contiguous Memory Allocation**: Every element `arr[i + 1]` resides immediately after `arr[i]` in RAM.
2. **Homogeneous Elements**: Every element has the exact same data type `T` and occupies the exact same size $w = \text{sizeof}(T)$ bytes.
3. **Zero-Based Indexing**: In C++, an array of size $n$ is indexed from $0$ to $n - 1$. The index represents the **offset** (number of elements) from the base address.
4. **Capacity vs. Logical Size**:
   - **Capacity (`cap`)**: The total number of slots allocated for the array (e.g., `int arr[100]` has capacity $100$).
   - **Logical Size (`size`)**: The number of valid elements currently stored in the array ($0 \le \text{size} \le \text{cap}$).

---

## 3. Mathematical Representation

### 1. 1D Array Address Calculation (Zero-Based Indexing)
Let:
- $B$ = Base address (memory address of `arr[0]`)
- $w$ = Size of each element in bytes ($\text{sizeof}(T)$, e.g., $4$ bytes for `int`)
- $i$ = Zero-based index ($0 \le i < n$)

$$\text{Address}(A[i]) = B + i \times w$$

*(If 1-based indexing or an arbitrary lower bound $L$ is used in examination problems: $\text{Address}(A[i]) = B + (i - L) \times w$.)*

### 2. 2D Array Address Calculation ($R \times C$ Matrix)
Even a 2D array `int mat[R][C]` is stored linearly in 1D physical RAM using one of two layouts:

- **Row-Major Order** *(Used by C and C++)*: Rows are stored one after another.
  $$\text{Address}(A[i][j]) = B + (i \times C + j) \times w$$
- **Column-Major Order** *(Used by Fortran and MATLAB)*: Columns are stored one after another.
  $$\text{Address}(A[i][j]) = B + (j \times R + i) \times w$$

---

## 4. Working Mechanism

### Core Array Operations
1. **Traversal (`print`)**:
   - Iterate `i` from `0` to `size - 1` and visit `arr[i]`.
2. **Insertion at End (`push_back(val)`)**:
   - Check if `size == cap` (overflow).
   - Write `arr[size] = val` and increment `size++`.
3. **Insertion at Arbitrary Position `pos` (`insert_at(val, pos)`)**:
   - Validate `size < cap` and `0 <= pos <= size`.
   - Shift all elements in `[pos .. size - 1]` **one position to the right**, starting from the **rightmost** element (`i = size` down to `pos + 1`): `arr[i] = arr[i - 1]`.
   - Place `arr[pos] = val` and increment `size++`.
4. **Deletion at Arbitrary Position `pos` (`delete_at(pos)`)**:
   - Validate `size > 0` and `0 <= pos < size`.
   - Shift all elements in `[pos + 1 .. size - 1]` **one position to the left**, starting from `i = pos` up to `size - 2`: `arr[i] = arr[i + 1]`.
   - Decrement `size--`.
5. **In-Place Reversal (`reverse_array()`)**:
   - Maintain two pointers/indices: `start = 0` and `end = size - 1`.
   - While `start < end`, swap `arr[start]` and `arr[end]`, then increment `start++` and decrement `end--`.

---

## 5. Visual Representation

### 1. Contiguous Memory Layout (`B = 1000`, `sizeof(int) = 4`)
```
Index:        0          1          2          3          4
         +----------+----------+----------+----------+----------+
Value:   |    10    |    20    |    30    |    40    |    50    |
         +----------+----------+----------+----------+----------+
Address:   1000       1004       1008       1012       1016
```

### 2. Right-Shift During `insert_at(val = 25, pos = 2)`
```
Before (size = 5):
Index:     0     1     2     3     4     5
        +-----+-----+-----+-----+-----+-----+
        |  10 |  20 |  30 |  40 |  50 |     |
        +-----+-----+-----+-----+-----+-----+
                        \     \     \
                         v     v     v   (Shift right from back: i = 5 down to 3)
After Shift & Insert (size = 6):
Index:     0     1     2     3     4     5
        +-----+-----+-----+-----+-----+-----+
        |  10 |  20 |  25 |  30 |  40 |  50 |
        +-----+-----+-----+-----+-----+-----+
```

### 3. Left-Shift During `delete_at(pos = 3)`
```
Before (size = 6):
Index:     0     1     2     3     4     5
        +-----+-----+-----+-----+-----+-----+
        |  10 |  20 |  25 |  30 |  40 |  50 |
        +-----+-----+-----+-----+-----+-----+
                             ^     ^
                            /     /      (Shift left from pos: i = 3 up to 4)
After Shift (size = 5):
Index:     0     1     2     3     4
        +-----+-----+-----+-----+-----+
        |  10 |  20 |  25 |  40 |  50 |
        +-----+-----+-----+-----+-----+
```

---

## 6. C++ Implementation Analysis

### File: `../Array_Operations.cpp`

- **`class Array`**: Encapsulates `int arr[100]`, `int cap`, and `int size`, matching your class design in `05-Stacks/stack_01.cpp` and `08-Trees/Binary_Tree_Array.cpp`.
- **`push_back(int val)`**: Appends at `arr[size]` in $O(1)$ time after checking `if (size == cap)`.
- **`insert_at(int val, int pos)`**: Shifts `[pos .. size - 1]` right in $O(n - \text{pos})$ time so no existing element is overwritten, then writes `arr[pos] = val`.
- **`delete_at(int pos)`**: Shifts `[pos + 1 .. size - 1]` left in $O(n - \text{pos})$ time and decrements `size`.
- **`reverse_array()`**: Uses two indices (`start` and `end`) to reverse the array in-place in $\lfloor n/2 \rfloor$ swaps ($O(n)$ time, $O(1)$ space).

---

## 7. Dry Runs

### Dry Run of `main()` in `../Array_Operations.cpp`

| Step | Operation | Array State (`arr[0 .. size-1]`) | `size` | Output / Action |
| :---: | :--- | :--- | :---: | :--- |
| 1 | `Array a1(20);` | `[]` | `0` | Initialized empty array |
| 2 | Loop `i = 1..5`: `push_back(i * 10)` | `[10, 20, 30, 40, 50]` | `5` | Prints `10 20 30 40 50` |
| 3 | `a1.insert_at(25, 2);` | `[10, 20, 25, 30, 40, 50]` | `6` | Shifts `30, 40, 50` right; inserts `25` at index `2` |
| 4 | `a1.delete_at(3);` | `[10, 20, 25, 40, 50]` | `5` | Deletes `30` at index `3`; shifts `40, 50` left |
| 5 | `a1.reverse_array();` | `[50, 40, 25, 20, 10]` | `5` | Swaps `(10, 50)` and `(20, 40)` |

---

## 8. Time Complexity

| Operation | Best Case | Average Case | Worst Case | Why? |
| :--- | :---: | :---: | :---: | :--- |
| **Access / Update `arr[i]`** | $O(1)$ | $O(1)$ | $O(1)$ | Direct formula $B + i \times w$ |
| **Insert at End (`push_back`)** | $O(1)$ | $O(1)$ | $O(1)$ | Writes directly to `arr[size]` |
| **Insert at Position `pos`** | $O(1)$ (`pos == size`) | $O(n)$ | $O(n)$ (`pos == 0`) | Shifts $n - \text{pos}$ elements right |
| **Delete at End** | $O(1)$ | $O(1)$ | $O(1)$ | Only decrements `size--` |
| **Delete at Position `pos`** | $O(1)$ (`pos == size-1`) | $O(n)$ | $O(n)$ (`pos == 0`) | Shifts $n - 1 - \text{pos}$ elements left |
| **Reverse / Traverse** | $O(n)$ | $O(n)$ | $O(n)$ | Visits each element a constant number of times |

---

## 9. Space Complexity

- **Storage Space**: $O(\text{cap})$ for static array `int arr[100]`, or $O(n)$ for a dynamically sized array.
- **Auxiliary Space for `insert_at`, `delete_at`, `reverse_array`**: $O(1)$, since all shifts and swaps happen in-place using a constant number of index variables.

---

## 10. Important Properties and Observations

1. **Direction of Shifting Matters**:
   - When **inserting** at `pos`, you **must** shift from **right to left** (`for (int i = size; i > pos; i--) arr[i] = arr[i - 1];`). If you shifted left to right (`arr[i + 1] = arr[i]`), you would overwrite `arr[pos + 1]` with `arr[pos]` and duplicate the same value across the array!
   - When **deleting** at `pos`, you **must** shift from **left to right** (`for (int i = pos; i < size - 1; i++) arr[i] = arr[i + 1];`).
2. **CPU Cache Locality**:
   When `arr[0]` is accessed, the CPU loads an entire cache line (typically 64 bytes = 16 `int`s) into L1 cache. Subsequent accesses `arr[1]..arr[15]` are instantaneous L1 cache hits.

---

## 11. Advantages and Disadvantages

### Advantages
- $O(1)$ random access to any index.
- Zero per-element memory overhead (no pointers stored per element).
- Superior CPU cache locality.

### Disadvantages
- Fixed capacity in static arrays (can cause overflow if `size == cap`, or wasted memory if `size << cap`).
- $O(n)$ time required for insertions and deletions at the beginning or middle due to element shifting.

---

## 12. Comparison with Related Concepts

### Array vs. Singly Linked List (`04-Linked-Lists`)

| Feature | Array (`Array_Operations.cpp`) | Singly Linked List (`linked_list-01.cpp`) |
| :--- | :--- | :--- |
| **Memory Layout** | Contiguous block in memory | Non-contiguous nodes scattered on heap |
| **Access $i$-th Element** | $O(1)$ via `arr[i]` | $O(i)$ (must traverse from `head`) |
| **Insert at Front (`pos = 0`)** | $O(n)$ (must shift all $n$ elements) | $O(1)$ via `push_front` |
| **Insert at End (with `tail`)** | $O(1)$ (if `size < cap`) | $O(1)$ via `pushb_back` |
| **Memory Overhead per Element** | $0$ extra bytes | $8$ bytes (`Node* next`) + alignment padding |
| **Binary Search Support** | Yes ($O(\log n)$) | No ($O(n)$ because mid cannot be reached in $O(1)$) |

---

## 13. Common Mistakes

1. **Off-by-One Out-of-Bounds Access**:
   Accessing `arr[size]` instead of `arr[size - 1]` (as you carefully noted in your comments in `08-Trees/Binary_Tree_Array.cpp` line 137: `index == size is INVALID because indexing starts from 0`).
2. **Shifting in the Wrong Direction During Insertion**:
   Overwriting adjacent elements by shifting forward instead of backward from `size` down to `pos + 1`.
3. **Forgetting Capacity Checks**:
   Inserting when `size == cap` writes past the end of the array buffer (buffer overflow).

---

## 14. Applications

1. **Array-Based Binary Trees & Binary Heaps**: Implemented in `08-Trees/Binary_Tree_Array.cpp` and `08-Trees/Binary_Heap.cpp` using `left = 2*i + 1` and `right = 2*i + 2`.
2. **Array-Based Stacks & Circular Queues**: Implemented in `05-Stacks/stack_01.cpp` and `06-Queues/queue_02.cpp`.
3. **Lookup Tables, Matrices, and Dynamic Programming Tables**.

---

## 15. Practice Questions

1. **Basic Understanding**: An integer array `int A[15][20]` is stored in **Row-Major Order** starting at base address $B = 2000$, with $\text{sizeof}(\text{int}) = 4$ bytes. Calculate the exact memory address of `A[6][8]`. What would its address be in **Column-Major Order**?
2. **Implementation**: Write a function `void rotate_left_by_one(int arr[], int size)` that shifts all elements left by one position and moves `arr[0]` to `arr[size - 1]` in $O(n)$ time and $O(1)$ space.
3. **Dry-Run Problem**: Trace the exact array contents after each step: start with `[5, 10, 15, 20]`, call `insert_at(12, 2)`, `insert_at(2, 0)`, and `delete_at(4)`.
4. **Complexity Analysis**: If you want to delete an element at index `i` from an **unsorted** array where element order does **not** matter, how can you do it in $O(1)$ time instead of $O(n)$ time? *(Hint: Look at how `delete_node` in `08-Trees/Binary_Heap.cpp` removes an element before heapifying!)*
5. **Interview Question**: Given an array of size $n$, how can you rotate the array to the right by $k$ steps in $O(n)$ time and $O(1)$ auxiliary space using `reverse_array`?

---

## 16. Quick Revision

- **1D Address Formula**: $\text{Addr}(A[i]) = B + i \times w$.
- **2D Row-Major Formula ($R \times C$)**: $\text{Addr}(A[i][j]) = B + (i \cdot C + j) \times w$.
- **2D Column-Major Formula ($R \times C$)**: $\text{Addr}(A[i][j]) = B + (j \cdot R + i) \times w$.
- **Insertion Shift**: Right-shift backward (`for (i = size; i > pos; i--) arr[i] = arr[i-1]`).
- **Deletion Shift**: Left-shift forward (`for (i = pos; i < size - 1; i++) arr[i] = arr[i+1]`).
