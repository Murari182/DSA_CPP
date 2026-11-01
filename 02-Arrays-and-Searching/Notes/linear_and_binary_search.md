# Linear Search and Binary Search

## Related Implementation

- `../Linear_and_Binary_Search.cpp` *(Supplementary implementation created for this folder)*
- `../../08-Trees/Recursive_Time_Complexity_Binary_Trees.cpp` *(Lines 323–336: Recursive Binary Search complexity analysis)*

---

## 1. Concept Introduction

### What is the Concept?
**Searching** is the algorithmic process of finding the index (or confirming the absence) of a target value (`key`) within a collection of elements:
1. **Linear Search (Sequential Search)**: Scans each element one by one from start to end without requiring any ordering of the data.
2. **Binary Search**: A **Divide-and-Conquer** search algorithm that repeatedly halves the search interval by comparing the target `key` against the middle element of a **sorted** array.

### Why is it Required?
In an unsorted collection of $n = 10^9$ elements, Linear Search requires up to $10^9$ comparisons in the worst case. If the array is sorted, Binary Search finds any element (or proves it does not exist) in at most $\lfloor \log_2(10^9) \rfloor + 1 = 30$ comparisons.

---

## 2. Fundamental Theory

### 1. Linear Search
- **Precondition**: None (works on both unsorted and sorted arrays/lists).
- **Mechanism**: Inspect `arr[0], arr[1], ..., arr[n - 1]`. As soon as `arr[i] == key`, return index `i`. If the loop finishes without a match, return `-1`.

### 2. Binary Search
- **Precondition (Crucial)**: The array **must be sorted** (monotonically non-decreasing or non-increasing).
- **Search Space Invariant**: Maintain two boundary indices `low` and `high` such that if `key` is present in the array, its index must lie within the closed interval $[\text{low}, \text{high}]$.
- **Decision at Midpoint**:
  Compute $\text{mid} = \lfloor (\text{low} + \text{high}) / 2 \rfloor$:
  1. If `arr[mid] == key`: Target found at `mid`.
  2. If `arr[mid] < key`: Because the array is sorted in ascending order, every element in `arr[low .. mid]` is strictly less than `key`. Discard the left half by setting `low = mid + 1`.
  3. If `arr[mid] > key`: Every element in `arr[mid .. high]` is strictly greater than `key`. Discard the right half by setting `high = mid - 1`.
- **Termination**: When `low > high`, the search interval $[\text{low}, \text{high}]$ is empty, proving `key` is not in the array.

---

## 3. Mathematical Representation

### Overflow-Safe Midpoint Formula
Writing `(low + high) / 2` can cause **32-bit signed integer overflow** if `low + high > INT_MAX` ($2^{31} - 1$). Always use the mathematically equivalent overflow-safe formula (also used in `08-Trees/Recursive_Time_Complexity_Binary_Trees.cpp` line 327):

$$\text{mid} = \text{low} + \left\lfloor \frac{\text{high} - \text{low}}{2} \right\rfloor$$

### Binary Search Recurrence Relation
At each step, the problem size $n = \text{high} - \text{low} + 1$ is reduced to at most $\lfloor n / 2 \rfloor$ with $O(1)$ comparison work:

$$T(n) = T\left(\lfloor n / 2 \rfloor\right) + c, \quad T(1) = c$$

Expanding the recurrence:
$$T(n) = T\left(\frac{n}{2^k}\right) + k \cdot c$$
Setting $\frac{n}{2^k} = 1 \implies k = \log_2 n$:
$$T(n) = c \cdot (\lfloor \log_2 n \rfloor + 1) = \Theta(\log n)$$

---

## 4. Working Mechanism

### Step-by-Step Iterative Binary Search
1. Initialize `low = 0` and `high = n - 1`.
2. Loop while `low <= high`:
   - Step 2a: Calculate `mid = low + (high - low) / 2`.
   - Step 2b: If `arr[mid] == key`, return `mid`.
   - Step 2c: Else if `arr[mid] < key`, update `low = mid + 1`.
   - Step 2d: Else (`arr[mid] > key`), update `high = mid - 1`.
3. If the loop exits (`low > high`), return `-1`.

---

## 5. Visual Representation

### Binary Search for `key = 60` in `arr = {10, 20, 30, 40, 50, 60, 70, 80}`
```
Iteration 1: low = 0, high = 7, mid = 0 + (7 - 0)/2 = 3 (arr[3] = 40 < 60 -> go right: low = 4)
Index:    0     1     2     3     4     5     6     7
       +-----+-----+-----+-----+-----+-----+-----+-----+
       |  10 |  20 |  30 |  40 |  50 |  60 |  70 |  80 |
       +-----+-----+-----+-----+-----+-----+-----+-----+
         ^                 ^                       ^
        low               mid                     high

Iteration 2: low = 4, high = 7, mid = 4 + (7 - 4)/2 = 5 (arr[5] = 60 == 60 -> FOUND at index 5!)
Index:    0     1     2     3     4     5     6     7
       +-----+-----+-----+-----+-----+-----+-----+-----+
       |  10 |  20 |  30 |  40 |  50 |  60 |  70 |  80 |
       +-----+-----+-----+-----+-----+-----+-----+-----+
                                 ^     ^           ^
                                low   mid         high
```

---

## 6. C++ Implementation Analysis

### File: `../Linear_and_Binary_Search.cpp`

1. **`linear_search(const vector<int> &arr, int key)`**:
   - Loops `i` from `0` to `arr.size() - 1`.
   - Returns `i` on the first match, or `-1` if not found.
   - **Time**: $O(n)$ worst/average, $O(1)$ best. **Space**: $O(1)$.
2. **`binary_search_iterative(const vector<int> &arr, int key)`**:
   - Uses a `while (low <= high)` loop and `mid = low + (high - low) / 2`.
   - Adjusts `low = mid + 1` or `high = mid - 1`.
   - **Time**: $O(\log n)$ worst/average, $O(1)$ best. **Auxiliary Space**: $O(1)$.
3. **`binary_search_recursive(const vector<int> &arr, int low, int high, int key)`**:
   - Base case: `if (low > high) return -1;`.
   - Recursively searches either `[low, mid - 1]` or `[mid + 1, high]`.
   - **Time**: $O(\log n)$. **Auxiliary Stack Space**: $O(\log n)$.

---

## 7. Dry Runs

### Dry Run 1: Successful Search (`key = 20`) on `{10, 20, 30, 40, 50, 60, 70, 80}`

| Iteration | `low` | `high` | `mid` | `arr[mid]` | Comparison (`key = 20`) | Action |
| :---: | :---: | :---: | :---: | :---: | :---: | :--- |
| 1 | `0` | `7` | `3` | `40` | `20 < 40` | Search left half: `high = mid - 1 = 2` |
| 2 | `0` | `2` | `1` | `20` | `20 == 20` | Match found! Return `1` |

### Dry Run 2: Unsuccessful Search (`key = 99`) on `{10, 20, 30, 40, 50, 60, 70, 80}`

| Iteration | `low` | `high` | `mid` | `arr[mid]` | Comparison (`key = 99`) | Action |
| :---: | :---: | :---: | :---: | :---: | :---: | :--- |
| 1 | `0` | `7` | `3` | `40` | `99 > 40` | `low = mid + 1 = 4` |
| 2 | `4` | `7` | `5` | `60` | `99 > 60` | `low = mid + 1 = 6` |
| 3 | `6` | `7` | `6` | `70` | `99 > 70` | `low = mid + 1 = 7` |
| 4 | `7` | `7` | `7` | `80` | `99 > 80` | `low = mid + 1 = 8` |
| 5 | `8` | `7` | — | — | `low > high` (`8 > 7`) | Loop terminates; return `-1` |

---

## 8. Time Complexity

| Algorithm | Best Case | Average Case | Worst Case | Explanation |
| :--- | :---: | :---: | :---: | :--- |
| **Linear Search** | $O(1)$ | $O(n)$ | $O(n)$ | Best: `arr[0] == key`; Average: $\frac{n+1}{2}$ checks; Worst: $n$ checks |
| **Binary Search (Iterative)** | $O(1)$ | $O(\log n)$ | $O(\log n)$ | Best: `arr[mid] == key` on step 1; Worst: $\lfloor \log_2 n \rfloor + 1$ steps |
| **Binary Search (Recursive)** | $O(1)$ | $O(\log n)$ | $O(\log n)$ | Halves interval `[low, high]` at each recursive call |

---

## 9. Space Complexity

- **Linear Search**: $O(1)$ auxiliary space.
- **Iterative Binary Search**: $O(1)$ auxiliary space (`low`, `high`, `mid`).
- **Recursive Binary Search**: $O(\log n)$ auxiliary call stack space (at most $\lfloor \log_2 n \rfloor + 1$ stack frames).

---

## 10. Important Properties and Observations

1. **Iterative vs. Recursive Binary Search**:
   Iterative Binary Search is preferred in production code because it achieves the same $O(\log n)$ time complexity with **$O(1)$ auxiliary space**, avoiding function call overhead and stack allocation.
2. **Relationship to Binary Search Trees (`08-Trees/BST_01.cpp`)**:
   Searching a perfectly balanced BST (`search(root, key)` in `BST_01.cpp`) performs the exact same sequence of comparisons as Binary Search on a sorted array! The root of the BST corresponds to `arr[mid]`, the left subtree to `arr[low .. mid-1]`, and the right subtree to `arr[mid+1 .. high]`.

---

## 11. Advantages and Disadvantages

### Linear Search
- **Advantages**: Works on unsorted arrays and linked lists; zero preprocessing required.
- **Disadvantages**: Slow ($O(n)$) for large datasets.

### Binary Search
- **Advantages**: Extremely fast ($O(\log n)$); ideal when many queries are performed on static or rarely modified sorted data.
- **Disadvantages**: Requires sorted data (sorting an unsorted array takes $O(n \log n)$ time first) and requires $O(1)$ random access (cannot be used efficiently on a linked list).

---

## 12. Comparison with Related Concepts

### Linear Search vs. Binary Search

| Feature | Linear Search | Binary Search |
| :--- | :--- | :--- |
| **Sorting Prerequisite** | Not required (works on any order) | **Mandatory** (must be sorted) |
| **Data Structure Requirement** | Any iterable structure (Array, Linked List) | Random-access structure (Array, `std::vector`) |
| **Worst-Case Time Complexity** | $O(n)$ | $O(\log n)$ |
| **Best-Case Time Complexity** | $O(1)$ (first element) | $O(1)$ (middle element) |
| **Max Comparisons for $n = 10^6$** | $1,000,000$ | $20$ |

---

## 13. Common Mistakes

1. **Applying Binary Search on an Unsorted Array**:
   If the array is not sorted, discarding half of the array based on `arr[mid] < key` is invalid and will miss elements.
2. **Writing `while (low < high)` Instead of `while (low <= high)`**:
   When `low == high`, there is still $1$ candidate element remaining in the interval `[low, high]`. Using `low < high` skips checking that final single-element interval (as seen in Dry Run 2, Iteration 4 where `low = 7, high = 7`).
3. **Writing `low = mid` or `high = mid` Without Adjusting by $\pm 1$**:
   Since `arr[mid]` has already been checked and is not equal to `key`, keeping `mid` in the range can cause an **infinite loop** when `low == high`.
4. **Integer Overflow in `(low + high) / 2`**:
   Always write `low + (high - low) / 2`.

---

## 14. Applications

1. **Database Indexing & Dictionary Lookups**.
2. **STL `std::lower_bound` and `std::upper_bound`**: Finding the first element $\ge x$ or $> x$ in a sorted array.
3. **Binary Search on Answer**: Finding the minimum/maximum feasible parameter in optimization problems where the feasibility predicate is monotonic.
4. **Git Bisect**: Finding the exact commit that introduced a bug in $O(\log n)$ tests.

---

## 15. Practice Questions

1. **Basic Understanding**: Why is Binary Search not suitable for a Singly Linked List (`04-Linked-Lists/linked_list-01.cpp`) even if the linked list is sorted in ascending order?
2. **Implementation**: Given a sorted array with duplicate elements (e.g., `{10, 20, 20, 20, 30, 40}`), write a modified Binary Search function `first_occurrence(arr, key)` that returns the **smallest** index of `key` in $O(\log n)$ time.
3. **Dry-Run Problem**: Trace `binary_search_iterative` step-by-step on `arr = {5, 12, 18, 24, 31, 39, 45, 52, 60}` for (a) `key = 39` and (b) `key = 25`. Show `low`, `high`, `mid`, and `arr[mid]` at each step.
4. **Complexity Analysis**: Suppose you have an unsorted array of size $n$ and need to perform $k$ search queries. For what value of $k$ (in terms of $n$) does sorting the array first ($O(n \log n)$) and running $k$ Binary Searches ($O(k \log n)$) become faster than running $k$ Linear Searches ($O(k \cdot n)$)?
5. **Interview Question**: How do you search for a target `key` in a **Rotated Sorted Array** (e.g., `{40, 50, 60, 70, 10, 20, 30}`) in $O(\log n)$ time?

---

## 16. Quick Revision

- **Linear Search**: $O(n)$ time, $O(1)$ space; works on unsorted data.
- **Binary Search**: $O(\log n)$ time, $O(1)$ iterative space ($O(\log n)$ recursive stack space); **requires sorted data and $O(1)$ random access**.
- **Midpoint Formula**: `int mid = low + (high - low) / 2;`
- **Maximum Comparisons in Binary Search**: $\lfloor \log_2 n \rfloor + 1$.
