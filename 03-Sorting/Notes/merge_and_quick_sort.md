# Divide and Conquer Sorting: Merge Sort & Quick Sort

## Related Implementation

- `../Merge_and_Quick_Sort.cpp` *(Supplementary implementation created for this folder)*
- Related sorting and recurrence files in this repository:
  - `../../04-Linked-Lists/Linked_List-02.cpp` (`Merge_SL` — merging two sorted linked lists)
  - `../../08-Trees/Binary_Heap.cpp` and `../../08-Trees/Binary_Heap_Detailed_Explanation.cpp` (`heap_sort` — $O(n \log n)$ in-place sorting)
  - `../../08-Trees/Recursive_Time_Complexity_Binary_Trees.cpp` (Lines 337–342: Merge Sort recurrence $T(n) = 2T(n/2) + cn$)

---

## 1. Concept Introduction

### What is the Concept?
Elementary sorting algorithms require $O(n^2)$ time in the average and worst cases because each comparison eliminates at most one inversion between adjacent elements. **Divide-and-Conquer Sorting Algorithms** break the array into smaller subproblems, sort them recursively, and combine the results to achieve **$O(n \log n)$** time complexity:
1. **Merge Sort**: Divides the array into two equal halves, recursively sorts both halves, and merges the two sorted halves in $O(n)$ time.
2. **Quick Sort**: Selects a **pivot** element, partitions the array in $O(n)$ time so that all elements $\le \text{pivot}$ are on its left and all elements $> \text{pivot}$ are on its right (placing the pivot at its exact final sorted index), and recursively sorts the left and right partitions.

---

## 2. Fundamental Theory

### The Divide-and-Conquer Paradigm
Every Divide-and-Conquer algorithm consists of three stages:
1. **Divide**: Split the problem of size $n$ into smaller subproblems.
2. **Conquer**: Solve the subproblems recursively (stopping at base case $n \le 1$, where a 0- or 1-element subarray is already sorted).
3. **Combine**: Merge the subproblem solutions into the solution for the original problem.

### How Merge Sort vs. Quick Sort Divide Work
- **Merge Sort ("Easy Divide, Hard Combine")**:
  - **Divide**: Compute `mid = left + (right - left) / 2` in $O(1)$ time.
  - **Conquer**: Recursively sort `arr[left .. mid]` and `arr[mid + 1 .. right]`.
  - **Combine**: Merge the two sorted subarrays into a single sorted subarray using a two-pointer merge in $O(n)$ time.
- **Quick Sort ("Hard Divide, No Combine")**:
  - **Divide**: Rearrange (partition) the subarray around a `pivot` in $O(n)$ time so that `arr[left .. p - 1] <= arr[p] < arr[p + 1 .. right]`.
  - **Conquer**: Recursively sort `arr[left .. p - 1]` and `arr[p + 1 .. right]`.
  - **Combine**: Nothing to do ($O(1)$)—the array is already sorted in-place!

---

## 3. Mathematical Representation

### 1. Merge Sort Recurrence Relation (All Cases)
Whether the input is sorted, reversed, or random, Merge Sort always splits $n$ into two halves of size $\approx n/2$ and performs $c \cdot n$ work during `merge`:

$$T(n) = 2T\left(\frac{n}{2}\right) + c \cdot n, \quad T(1) = c$$

By the Master Theorem ($a = 2, b = 2, d = 1 \implies a = b^d$) or recursion tree expansion across $\log_2 n$ levels with $c \cdot n$ total work per level:

$$T(n) = \Theta(n \log n)$$

### 2. Quick Sort Recurrence Relations
- **Best Case** (Pivot always lands at the exact median, splitting into $\approx n/2$ and $n/2$):
  $$T(n) = 2T\left(\frac{n}{2}\right) + c \cdot n = \Theta(n \log n)$$
- **Worst Case** (Pivot is always the smallest or largest element, e.g., picking `arr[high]` on an already-sorted or reverse-sorted array, splitting into $n - 1$ and $0$):
  $$T(n) = T(n - 1) + T(0) + c \cdot n = T(n - 1) + c \cdot n = \frac{c \cdot n(n + 1)}{2} = \Theta(n^2)$$
- **Average Case** (Even a 9-to-1 split $T(n) = T(9n/10) + T(n/10) + cn$ has recursion tree depth $\log_{10/9} n = O(\log n)$):
  $$T_{\text{avg}}(n) = \Theta(n \log n)$$

---

## 4. Working Mechanism

### Two-Pointer `merge(arr, left, mid, right)`
*(Note: This is the array counterpart to your `Merge_SL(list &l1, list &l2)` in `04-Linked-Lists/Linked_List-02.cpp`!)*
1. Create temporary vector `temp`. Set `i = left` (start of left sorted half) and `j = mid + 1` (start of right sorted half).
2. **Main Loop (`while (i <= mid && j <= right)`)**:
   - Compare `arr[i]` and `arr[j]`.
   - If `arr[i] <= arr[j]`, push `arr[i]` to `temp` and increment `i++` (using `<=` preserves **stability**!).
   - Otherwise, push `arr[j]` to `temp` and increment `j++`.
3. **Remaining Left Elements (`while (i <= mid)`)**: Append any leftover elements from the left half.
4. **Remaining Right Elements (`while (j <= right)`)**: Append any leftover elements from the right half.
5. Copy all elements from `temp` back into `arr[left .. right]`.

### Lomuto Partition (`partition_array(arr, low, high)`)
1. Choose `pivot = arr[high]`.
2. Maintain boundary index `i = low - 1` (representing the end of the region of elements $\le \text{pivot}$).
3. Loop `j` from `low` to `high - 1`:
   - If `arr[j] <= pivot`: increment `i++` and `swap(arr[i], arr[j])`.
4. Finally, place the pivot immediately after the $\le \text{pivot}$ region by calling `swap(arr[i + 1], arr[high])` and return `i + 1`.

---

## 5. Visual Representation

### 1. Merge Sort Divide & Combine Tree on `{38, 27, 43, 3}`
```
                  [38, 27, 43, 3]
                 /               \          <-- DIVIDE
          [38, 27]               [43, 3]
          /      \               /     \
       [38]      [27]         [43]     [3]
          \      /               \     /    <-- MERGE (Combine)
          [27, 38]               [3, 43]
                 \               /
                  [3, 27, 38, 43]
```

### 2. Lomuto Partition Invariant
```
Index:   low           i                 j          high
        +---------------+---------------+----------+-------+
        |  <= pivot     |   > pivot     | Unseen   | pivot |
        +---------------+---------------+----------+-------+
```

---

## 6. C++ Implementation Analysis

### File: `../Merge_and_Quick_Sort.cpp`

1. **`merge(vector<int> &arr, int left, int mid, int right)`**:
   - Merges two sorted ranges `[left .. mid]` and `[mid + 1 .. right]` in $O(n)$ time and $O(n)$ auxiliary space.
   - Crucial completeness detail: Includes both `while (i <= mid)` and `while (j <= right)` cleanup loops so no trailing elements are lost when one half finishes early.
2. **`merge_sort(vector<int> &arr, int left, int right)`**:
   - Base case: `if (left >= right) return;`.
   - Recursively sorts `[left, mid]` and `[mid + 1, right]`, then calls `merge`.
3. **`partition_array(vector<int> &arr, int low, int high)`**:
   - Partitions `[low .. high]` around `pivot = arr[high]` in $O(\text{high} - \text{low} + 1)$ time and $O(1)$ space, returning the pivot's final sorted index `i + 1`.
4. **`quick_sort(vector<int> &arr, int low, int high)`**:
   - Base case: `if (low < high)`.
   - Partitions around `p`, then recursively sorts `[low, p - 1]` and `[p + 1, high]`.

---

## 7. Dry Runs

### Dry Run of `partition_array` on `arr = {10, 80, 30, 90, 40, 50, 70}` (`low = 0, high = 6, pivot = 70`)

| Step (`j`) | `arr[j]` | Condition `arr[j] <= 70` | `i` | Action | Array State |
| :---: | :---: | :---: | :---: | :--- | :--- |
| Initial | — | — | `-1` | `pivot = 70` | `[10, 80, 30, 90, 40, 50, 70]` |
| `j = 0` | `10` | `10 <= 70` (True) | `0` | `swap(arr[0], arr[0])` | `[10, 80, 30, 90, 40, 50, 70]` |
| `j = 1` | `80` | `80 <= 70` (False) | `0` | No swap | `[10, 80, 30, 90, 40, 50, 70]` |
| `j = 2` | `30` | `30 <= 70` (True) | `1` | `swap(arr[1], arr[2])` | `[10, 30, 80, 90, 40, 50, 70]` |
| `j = 3` | `90` | `90 <= 70` (False) | `1` | No swap | `[10, 30, 80, 90, 40, 50, 70]` |
| `j = 4` | `40` | `40 <= 70` (True) | `2` | `swap(arr[2], arr[4])` | `[10, 30, 40, 90, 80, 50, 70]` |
| `j = 5` | `50` | `50 <= 70` (True) | `3` | `swap(arr[3], arr[5])` | `[10, 30, 40, 50, 80, 90, 70]` |
| Final | — | Place Pivot | `3` | `swap(arr[4], arr[6])` | `[10, 30, 40, 50, 70, 90, 80]` (Returns `p = 4`) |

Notice that after partitioning:
- Left side `[10, 30, 40, 50]` has all elements $\le 70$.
- Pivot `70` is at index `4` (its exact final sorted position!).
- Right side `[90, 80]` has all elements $> 70$.

---

## 8. Time Complexity

| Algorithm | Best Case | Average Case | Worst Case | Explanation |
| :--- | :---: | :---: | :---: | :--- |
| **Merge Sort** | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $\log_2 n$ levels $\times O(n)$ merge work per level in all cases |
| **Quick Sort** | $O(n \log n)$ | $O(n \log n)$ | $O(n^2)$ | $O(n \log n)$ when balanced; $O(n^2)$ when pivot is always min/max |

---

## 9. Space Complexity

- **Merge Sort**:
  - Temporary merge buffer `temp`: $O(n)$ auxiliary heap space.
  - Recursion call stack: $O(\log n)$ stack space.
  - **Total Auxiliary Space**: $O(n)$ (not in-place for arrays).
- **Quick Sort**:
  - Partitioning is performed in-place ($O(1)$ extra variables).
  - Recursion call stack: $O(\log n)$ in best/average case; $O(n)$ in worst case (skewed recursion tree).

---

## 10. Important Properties and Observations

1. **Why Quick Sort is Often Faster Than Merge Sort in Practice for Arrays**:
   Even though both are $O(n \log n)$ on average, Quick Sort operates in-place with excellent cache locality and avoids allocating/copying a temporary $O(n)$ buffer at every level.
2. **Why Merge Sort is Preferred for Linked Lists**:
   In a Linked List (`04-Linked-Lists`), two sorted lists can be merged in $O(1)$ auxiliary space by rewiring `next` pointers without allocating new nodes, whereas Quick Sort performs poorly on linked lists due to lack of random access.
3. **Avoiding Quick Sort's $O(n^2)$ Worst Case**:
   Choosing a **random pivot** (`swap(arr[low + rand() % (high - low + 1)], arr[high])`) or **median-of-three** (`low`, `mid`, `high`) makes the $O(n^2)$ worst case astronomically unlikely regardless of input order.

---

## 11. Advantages and Disadvantages

### Merge Sort
- **Advantages**: Guaranteed $O(n \log n)$ worst-case time; **Stable**; ideal for external sorting (large files on disk) and linked lists.
- **Disadvantages**: Requires $O(n)$ auxiliary memory for arrays.

### Quick Sort
- **Advantages**: In-place ($O(\log n)$ stack space); small constant factors and superior cache performance.
- **Disadvantages**: $O(n^2)$ worst-case time if pivot selection is naive; **Unstable**.

---

## 12. Comparison with Related Concepts

### Master Comparison Table of All Sorting Algorithms in This Repository

| Algorithm | Best Time | Average Time | Worst Time | Auxiliary Space | Stable? | In-Place? |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| **Bubble Sort** (`03-Sorting`) | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Yes | Yes |
| **Selection Sort** (`03-Sorting`) | $O(n^2)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | No | Yes |
| **Insertion Sort** (`03-Sorting`) | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Yes | Yes |
| **Merge Sort** (`03-Sorting`) | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ | Yes | No |
| **Quick Sort** (`03-Sorting`) | $O(n \log n)$ | $O(n \log n)$ | $O(n^2)$ | $O(\log n)$ | No | Yes |
| **Heap Sort** (`08-Trees/Binary_Heap.cpp`) | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(1)$ | No | Yes |

---

## 13. Common Mistakes

1. **Forgetting the Remaining-Element Loops in `merge`**:
   When one half finishes (`i > mid` or `j > right`), the other half still has unmerged elements. Forgetting the two cleanup `while` loops truncates the largest elements (this exact issue occurs in `Merge_SL` in `04-Linked-Lists/Linked_List-02.cpp`, documented in `04-Linked-Lists/Notes/singly_linked_list_and_operations.md`).
2. **Including the Pivot Index `p` in Recursive Quick Sort Calls**:
   In `quick_sort`, the recursive calls must be `quick_sort(arr, low, p - 1)` and `quick_sort(arr, p + 1, high)`. Since `arr[p]` is already in its final sorted position, including `p` can cause infinite recursion.

---

## 14. Applications

1. **Counting Inversions in an Array in $O(n \log n)$**: Modifying `merge` by adding `(mid - i + 1)` to an inversion counter whenever `arr[i] > arr[j]`.
2. **QuickSelect ($k$-th Smallest Element in $O(n)$ Average Time)**: Using `partition_array` and recursing only on the side containing index $k$.
3. **External Merge Sort**: Sorting multi-terabyte datasets stored on disk that cannot fit in RAM.

---

## 15. Practice Questions

1. **Basic Understanding**: Why does picking `pivot = arr[high]` in Quick Sort yield $O(n^2)$ time complexity when the input array is already sorted in ascending order?
2. **Implementation**: Modify `merge` and `merge_sort` to count the total number of **inversions** ($i < j$ and `arr[i] > arr[j]`) in an array in $O(n \log n)$ time.
3. **Dry-Run Problem**: Trace `merge_sort` completely on `arr = {30, 10, 40, 20, 50}`, showing every recursive call range `[left, right]` and the result of each `merge` call.
4. **Complexity Analysis**: What happens to the time complexity of Lomuto Quick Sort when all $n$ elements in the input array are identical (e.g., `{5, 5, 5, 5, 5}`)? How does **3-Way Dutch National Flag Partitioning** fix this?
5. **Interview Question**: Compare Merge Sort, Quick Sort, and Heap Sort (`08-Trees/Binary_Heap.cpp`). Why does C++ `std::sort` combine Quick Sort, Heap Sort, and Insertion Sort (IntroSort) instead of using just one of them?

---

## 16. Quick Revision

- **Merge Sort**: $T(n) = 2T(n/2) + O(n) \implies O(n \log n)$ in all cases; $O(n)$ auxiliary space; **Stable**.
- **Quick Sort**: $O(n \log n)$ best/average, $O(n^2)$ worst case; $O(\log n)$ auxiliary stack space; **In-Place, Unstable**.
- **Key Partition Property**: After `p = partition_array(arr, low, high)`, `arr[p]` is at its final sorted index.
