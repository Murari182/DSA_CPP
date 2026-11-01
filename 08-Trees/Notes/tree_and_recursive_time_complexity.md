# Recursive Time and Space Complexity of Binary Trees & Master Patterns

## Related Implementation

- `../Recursive_Time_Complexity_Binary_Trees.cpp` *(Original study reference file containing 25 complexity patterns)*
- `../Binary_Tree_01.cpp` and `../BST_01.cpp` *(Tree implementations analyzed by these recurrences)*

---

## 1. Concept Introduction

### What is the Concept?
Analyzing the **Time Complexity** and **Call Stack Space Complexity** of recursive functions—especially on Binary Trees and Divide-and-Conquer algorithms—requires writing a **Recurrence Relation** $T(n)$ and solving it using **Substitution (Expansion)**, **Recursion Trees**, or the **Master Theorem**.

### Why is This Document Important?
Your file `../Recursive_Time_Complexity_Binary_Trees.cpp` is a comprehensive 25-pattern study sheet covering binary tree recurrences, general recursive patterns, and mathematical series. This Markdown document preserves and formats all 25 patterns from `Recursive_Time_Complexity_Binary_Trees.cpp` with full LaTeX equations, recursion tree diagrams, and an important note about a C++ comment syntax detail in the original `.cpp` file.

---

## 2. Fundamental Theory

### The 5-Step Core Method (from `Recursive_Time_Complexity_Binary_Trees.cpp` lines 15–20)
1. **Identify the recursive call(s)** and the subproblem sizes ($n_L, n_R$, $n - 1$, $n / 2$, etc.).
2. **Count the work performed outside the recursive calls** in a single activation frame ($c$, $c \cdot n$, etc.).
3. **Write the recurrence relation $T(n)$**.
4. **Expand or solve the recurrence** (via summation, recursion tree, or Master Theorem).
5. **State Time Complexity separately from Auxiliary Stack Space** (Time $\propto$ total calls/work; Stack Space $\propto$ maximum call depth $h$).

---

## 3. Mathematical Representation

### 1. General Binary Tree Recurrence Relation
For a Binary Tree with $n$ total nodes, where the left subtree has $n_L$ nodes and the right subtree has $n_R$ nodes ($n_L + n_R = n - 1$), any function that visits the current node in $O(1)$ time ($c$) and recurses once on `root->left` and once on `root->right` satisfies:

$$T(n) = T(n_L) + T(n_R) + c, \quad T(0) = d$$

**Proof by Induction that $T(n) = \Theta(n)$ for ANY Tree Shape (Balanced or Skewed)**:
- Every one of the $n$ nodes is visited as `root` **exactly once** (doing $c$ work).
- Every one of the $n + 1$ `nullptr` child links is visited as a base case **exactly once** (doing $d$ work).
- Total work:
  $$T(n) = c \cdot n + d \cdot (n + 1) = (c + d)n + d = \Theta(n)$$

### 2. The Master Theorem for Divide-and-Conquer Recurrences
For a recurrence of the form:
$$T(n) = a \cdot T\left(\frac{n}{b}\right) + \Theta(n^d) \quad \text{where } a \ge 1, \; b > 1, \; d \ge 0$$

Compare $a$ (the branching factor / number of subproblems) with $b^d$ (the rate at per-level work shrinks):
1. **Case 1 ($a < b^d$ — Root work dominates)**:
   $$T(n) = \Theta(n^d)$$
2. **Case 2 ($a == b^d$ — Equal work at all $\log_b n$ levels)**:
   $$T(n) = \Theta(n^d \log n)$$
3. **Case 3 ($a > b^d$ — Leaf calls dominate)**:
   $$T(n) = \Theta\left(n^{\log_b a}\right)$$

---

## 4. Complete Breakdown of All 25 Patterns in `../Recursive_Time_Complexity_Binary_Trees.cpp`

### Part 1: Binary Tree Functions (Patterns 1–11)

| # | Function / Pattern | Recurrence Relation | Time Complexity | Stack Space | Key Insight |
| :---: | :--- | :--- | :---: | :---: | :--- |
| **1** | `countNodes(root)` | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ | $O(h)$ | Every node visited once |
| **2** | `height(root)` | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ | $O(h)$ | Height *value* is $O(\log n)$ if balanced, but *computing* it visits all $n$ nodes ($O(n)$) |
| **3** | `countLeafNodes(root)` | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ | $O(h)$ | Must traverse internal nodes to reach leaves |
| **4** | `countInternalNodes(root)` | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ | $O(h)$ | Visits every node once |
| **5** | `preorder` / `inorder` / `postorder` | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ | $O(h)$ | Prints each node once |
| **6** | `searchBT(root, key)` (General BT) | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ worst, $O(1)$ best | $O(h)$ | Cannot eliminate a subtree without BST ordering |
| **7** | `isBST(root, low, high)` | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ | $O(h)$ | Passes range bounds `(low, high)` in $O(1)$ per node |
| **8** | `isFull(root)` (`is_Strict_BT`) | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ | $O(h)$ | Checks $0$ or $2$ children at each node |
| **9** | `searchBST(root, key)` | $T(h) = T(h - 1) + c$ | $O(h)$ ($O(\log n)$ bal, $O(n)$ skewed) | $O(h)$ | Only 1 recursive call per level! |
| **10** | `preorderArray(arr, n, i)` | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ | $O(\log n)$ | Complete binary tree has height $h = \lfloor \log_2 n \rfloor$ |
| **11** | `sumSubtreeHeights(root)` *(calling `height(root)` at each node)* | Skewed: $T(n) = T(n-1) + cn$<br>Balanced: $T(n) = 2T(n/2) + cn$ | $O(n^2)$ skewed<br>$O(n \log n)$ balanced | $O(h)$ | Recomputing height top-down is slow; computing bottom-up is $O(n)$ |

---

### Part 2: General Recursive & Loop Patterns (Patterns 12–25)

| # | Code Pattern | Recurrence / Summation | Time Complexity | Stack Space | Mathematical Derivation |
| :---: | :--- | :--- | :---: | :---: | :--- |
| **12** | 1 call on `n - 1`, $O(1)$ work | $T(n) = T(n - 1) + c$ | $O(n)$ | $O(n)$ | $\sum_{i=1}^{n} c = c \cdot n$ |
| **13** | 1 call on `n - 1`, loop of size `n` | $T(n) = T(n - 1) + c \cdot n$ | $O(n^2)$ | $O(n)$ | $c \sum_{i=1}^{n} i = \frac{c n(n+1)}{2}$ |
| **14** | 1 call on `n / 2`, $O(1)$ work | $T(n) = T(n/2) + c$ | $O(\log n)$ | $O(\log n)$ | $n / 2^k = 1 \implies k = \log_2 n$ |
| **15** | 2 calls on `n / 2`, $O(1)$ work | $T(n) = 2T(n/2) + c$ | $O(n)$ | $O(\log n)$ | $1 + 2 + 4 + \dots + n = 2n - 1$ calls |
| **16** | 2 calls on `n / 2`, loop of size `n` | $T(n) = 2T(n/2) + c \cdot n$ | $O(n \log n)$ | $O(\log n)$ | $\log_2 n$ levels $\times c \cdot n$ work per level |
| **17** | 3 calls on `n / 2`, $O(1)$ work | $T(n) = 3T(n/2) + c$ | $O(n^{\log_2 3}) \approx O(n^{1.585})$ | $O(\log n)$ | Leaves: $3^{\log_2 n} = n^{\log_2 3}$ |
| **18** | 2 calls on `n / 3`, $O(1)$ work | $T(n) = 2T(n/3) + c$ | $O(n^{\log_3 2}) \approx O(n^{0.631})$ | $O(\log_3 n)$ | Leaves: $2^{\log_3 n} = n^{\log_3 2}$ |
| **19** | 1 call on `n / 2`, loop of size `n` | $T(n) = T(n/2) + c \cdot n$ | **$O(n)$** *(not $O(n \log n)$!)* | $O(\log n)$ | $cn + \frac{cn}{2} + \frac{cn}{4} + \dots < 2cn$ |
| **20** | 2 calls on `n - 1`, $O(1)$ work | $T(n) = 2T(n - 1) + c$ | $O(2^n)$ | $O(n)$ | $1 + 2 + 4 + \dots + 2^n = 2^{n+1} - 1$ |
| **21** | Naive `fib(n - 1) + fib(n - 2)` | $T(n) = T(n-1) + T(n-2) + c$ | $O(2^n)$ ($\Theta(\phi^n)$) | $O(n)$ | Memoization reduces this to $O(n)$ |
| **22** | `binarySearch` | $T(n) = T(n/2) + c$ | $O(\log n)$ | $O(\log n)$ | Halves interval each call |
| **23** | Merge Sort | $T(n) = 2T(n/2) + c \cdot n$ | $O(n \log n)$ | $O(\log n)$ stack + $O(n)$ aux | Master Theorem Case 2 ($a = 2, b = 2, d = 1$) |
| **24** | Nested Loops $n \times n$ | $\sum_{i=0}^{n-1} \sum_{j=0}^{n-1} c$ | $O(n^2)$ | $O(1)$ | $n \times n = n^2$ |
| **25** | Outer loop $n$, Inner loop halves | $\sum_{i=0}^{n-1} \log_2 n$ | $O(n \log n)$ | $O(1)$ | $n \times \log_2 n$ |

---

## 5. Visual Representation

### Contrast Between Pattern 15 ($2T(n/2) + c$), Pattern 16 ($2T(n/2) + cn$), and Pattern 19 ($T(n/2) + cn$)
```
PATTERN 15: T(n) = 2T(n/2) + c           PATTERN 16: T(n) = 2T(n/2) + cn          PATTERN 19: T(n) = T(n/2) + cn
Level 0: 1 call   * c   = c              Level 0: 1 * cn     = cn                 Level 0: cn
Level 1: 2 calls  * c   = 2c             Level 1: 2 * c(n/2) = cn                 Level 1: cn / 2
Level 2: 4 calls  * c   = 4c             Level 2: 4 * c(n/4) = cn                 Level 2: cn / 4
...                                      ...                                      ...
Level k: n calls  * c   = nc             Level k (k=log2 n)  = cn                 Level k: c
----------------------------------       ----------------------------------       ----------------------------------
Total = c(1 + 2 + ... + n) = O(n)        Total = cn * log2(n) = O(n log n)        Total = cn(1 + 1/2 + 1/4...) = O(n)
```

---

## 6. C++ Implementation & Code Review Note on `../Recursive_Time_Complexity_Binary_Trees.cpp`

### Important Observation in `../Recursive_Time_Complexity_Binary_Trees.cpp` (Line 204)
*(Documented here without modifying your original file)*
- Line 1 of `Recursive_Time_Complexity_Binary_Trees.cpp` starts a multi-line comment `/*` intended to wrap lines 1 through 400.
- However, on **line 204** (inside Pattern 13):
  ```cpp
  for (int i = 0; i < n; ++i) { /* constant work */ }
  ```
  In C++, multi-line comments `/* ... */` **do not nest**! The `*/` at the end of `/* constant work */` on line 204 (and line 207) closes the outer `/*` that began on line 1, leaving lines 210–400 outside the comment block if compiled directly with `g++`.
- All 25 patterns and mathematical formulas from that file are preserved in clean, renderable form in this Markdown reference!

---

## 7. Dry Runs

### Expanding Pattern 16: $T(n) = 2T(n/2) + c \cdot n$ (Lines 248–260 of `Recursive_Time_Complexity_Binary_Trees.cpp`)
Let $n = 8$:
1. **Expansion 1 ($k = 1$)**:
   $$T(8) = 2T(4) + 8c$$
2. **Expansion 2 ($k = 2$)**:
   $$T(8) = 2\big(2T(2) + 4c\big) + 8c = 4T(2) + 8c + 8c = 4T(2) + 2 \cdot (8c)$$
3. **Expansion 3 ($k = 3 = \log_2 8$)**:
   $$T(8) = 4\big(2T(1) + 2c\big) + 2 \cdot (8c) = 8T(1) + 3 \cdot (8c)$$
Notice your important note on lines 258–260 of `Recursive_Time_Complexity_Binary_Trees.cpp`:
> *"IMPORTANT: The coefficient of $cn$ is $k$, NOT $2^k - 1$. The geometric expression $2^k - 1$ counts nodes/calls in certain recursion-tree levels; it is not the accumulated loop work here."*

Because each of the $2^i$ subproblems at level $i$ has size $n / 2^i$, their combined loop work at level $i$ is $2^i \cdot c(n / 2^i) = c \cdot n$, and summing $c \cdot n$ across $k = \log_2 n$ levels gives $k \cdot c \cdot n = c \cdot n \log_2 n$!

---

## 8. Time Complexity Summary

See the complete 25-pattern tables in Section 4 above.

---

## 9. Space Complexity Summary

- **Binary Tree Traversals & Queries**: $O(h)$ stack space ($O(\log n)$ balanced, $O(n)$ skewed).
- **Halving Recurrences ($T(n/2)$ or $2T(n/2)$)**: $O(\log n)$ stack space.
- **Decrementing Recurrences ($T(n-1)$ or $2T(n-1)$)**: $O(n)$ stack space.

---

## 10. Important Properties and Observations

1. **Why $T(n) = 2T(n/2) + c$ is $O(n)$ and NOT $O(\log n)$**:
   Even though the recursion depth is $\log_2 n$, the number of calls doubles at every level ($1, 2, 4, 8, \dots, 2^{\log_2 n} = n$). Thus total calls equal $2n - 1 = \Theta(n)$.
2. **Why $T(n) = T(n/2) + c \cdot n$ is $O(n)$ and NOT $O(n \log n)$**:
   Because there is only **1** recursive call on $n/2$, the work halves at every level: $cn + cn/2 + cn/4 + \dots < 2cn = \Theta(n)$.

---

## 11. Advantages and Disadvantages of Master Theorem vs. Expansion

- **Master Theorem**: Instantaneous for standard polynomial divide-and-conquer recurrences $T(n) = aT(n/b) + \Theta(n^d)$.
- **Substitution / Expansion**: Required when subproblems shrink subtractively ($T(n - 1)$) or unequally ($T(n_L) + T(n_R)$).

---

## 12. Comparison with Related Concepts

| Recurrence | Branching Factor | Subproblem Size | Local Work | Final Time Complexity |
| :--- | :---: | :---: | :---: | :---: |
| $T(n) = T(n - 1) + c$ | $1$ | $n - 1$ | $O(1)$ | $O(n)$ |
| $T(n) = T(n - 1) + cn$ | $1$ | $n - 1$ | $O(n)$ | $O(n^2)$ |
| $T(n) = 2T(n - 1) + c$ | $2$ | $n - 1$ | $O(1)$ | $O(2^n)$ |
| $T(n) = T(n / 2) + c$ | $1$ | $n / 2$ | $O(1)$ | $O(\log n)$ |
| $T(n) = T(n / 2) + cn$ | $1$ | $n / 2$ | $O(n)$ | $O(n)$ |
| $T(n) = 2T(n / 2) + c$ | $2$ | $n / 2$ | $O(1)$ | $O(n)$ |
| $T(n) = 2T(n / 2) + cn$ | $2$ | $n / 2$ | $O(n)$ | $O(n \log n)$ |

---

## 13. Common Mistakes

1. **Confusing the Value of `height(root)` with the Time to Compute `height(root)`**:
   Computing the height of a balanced tree takes $O(n)$ time (not $O(\log n)$ time) because every node must be inspected to confirm which path is longest.
2. **Applying the Master Theorem to $T(n) = 2T(n - 1) + c$**:
   The Master Theorem only applies to **divisive** recurrences $T(n/b)$, never subtractive recurrences $T(n - 1)$.

---

## 14. Applications

- Analyzing every tree, divide-and-conquer, and backtracking algorithm in examinations and interviews.
- Identifying $O(n^2)$ top-down tree bottlenecks (like Pattern 11 `sumSubtreeHeights` or naive `Diameter`) and refactoring them into $O(n)$ bottom-up passes.

---

## 15. Practice Questions

1. **Basic Understanding**: Explain in your own words why $T(n) = T(n/2) + c \cdot n$ has time complexity $O(n)$ while $T(n) = 2T(n/2) + c \cdot n$ has time complexity $O(n \log n)$.
2. **Recurrence Expansion**: Expand $T(n) = 2T(n - 1) + c$ for $k$ steps and prove that $T(n) = (2^{n-1})T(1) + c(2^{n-1} - 1) = \Theta(2^n)$.
3. **Master Theorem**: Solve (a) $T(n) = 4T(n/2) + n$, (b) $T(n) = 4T(n/2) + n^2$, and (c) $T(n) = 4T(n/2) + n^3$.
4. **Tree Complexity Analysis**: Look at `Delete_Node(Node* root, int node)` in `08-Trees/BST_01.cpp`. Write its recurrence relation in terms of tree height $h$ and state its best-case, balanced average-case, and skewed worst-case time and space complexities.
5. **Interview Question**: In `Binary_Tree_Diameter_and_LCA.cpp`, how does passing `int &max_diameter` by reference inside `height_for_diameter` change the recurrence relation of computing the diameter of a binary tree from Pattern 11 ($O(n^2)$ worst case) to Pattern 2 ($O(n)$ worst case)?

---

## 16. Quick Revision

- **Tree Traversals / Counts / Height**: $T(n) = T(n_L) + T(n_R) + c \implies \mathbf{O(n)}$ time, $\mathbf{O(h)}$ stack space.
- **BST Search / Insert / Delete**: $T(h) = T(h - 1) + c \implies \mathbf{O(h)}$ time ($O(\log n)$ balanced, $O(n)$ skewed).
- **Master Theorem ($T(n) = aT(n/b) + \Theta(n^d)$)**:
  - $a < b^d \implies \Theta(n^d)$
  - $a == b^d \implies \Theta(n^d \log n)$
  - $a > b^d \implies \Theta(n^{\log_b a})$
