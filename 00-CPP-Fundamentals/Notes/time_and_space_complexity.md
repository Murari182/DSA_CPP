# Time and Space Complexity Analysis

## Related Implementation

- `../time_and_space_complexity.cpp` *(Supplementary implementation created for this folder)*
- `../../08-Trees/Recursive_Time_Complexity_Binary_Trees.cpp` *(Existing reference sheet on recursive and iterative complexity)*

---

## 1. Concept Introduction

### What is the Concept?
**Time Complexity** and **Space Complexity** are mathematical measures of how the execution time and memory consumption of an algorithm scale as the input size $n$ grows toward infinity ($n \to \infty$).

### Why is it Required?
Wall-clock execution time (in milliseconds) depends on hardware factors such as CPU clock speed, compiler optimizations, operating system scheduling, and cache size. **Asymptotic Analysis** abstracts away machine-dependent constants and measures the intrinsic efficiency of an algorithm in terms of elementary operations as a function of input size $n$.

### What Problem Does it Solve?
It allows an engineer to predict whether an algorithm will finish in milliseconds or take years when $n = 10^6$, and to compare competing algorithms (e.g., Linear Search $O(n)$ vs. Binary Search $O(\log n)$, or Bubble Sort $O(n^2)$ vs. Merge Sort $O(n \log n)$) objectively before writing code.

---

## 2. Fundamental Theory

### Elementary Operation
An operation whose execution time is bounded by a constant independent of $n$ (e.g., arithmetic addition `+`, comparison `<`, variable assignment `=`, array indexing `arr[i]`, or pointer dereference `temp->next`).

### Cases of Analysis
1. **Best Case**: The minimum number of operations performed over all possible inputs of size $n$ (e.g., finding the target at index `0` in Linear Search: $1$ comparison).
2. **Worst Case**: The maximum number of operations performed over all possible inputs of size $n$ (e.g., target is absent in Linear Search: $n$ comparisons). **DSA and competitive programming primarily focus on worst-case guarantees.**
3. **Average Case**: The expected number of operations averaged over a probability distribution of all inputs of size $n$.

---

## 3. Mathematical Representation

### Asymptotic Notations

#### 1. Big-O Notation ($O$) — Asymptotic Upper Bound
A function $f(n)$ is in $O(g(n))$ if there exist positive constants $c > 0$ and $n_0 \ge 1$ such that:

$$0 \le f(n) \le c \cdot g(n) \quad \forall n \ge n_0$$

#### 2. Big-Omega Notation ($\Omega$) — Asymptotic Lower Bound
A function $f(n)$ is in $\Omega(g(n))$ if there exist positive constants $c > 0$ and $n_0 \ge 1$ such that:

$$0 \le c \cdot g(n) \le f(n) \quad \forall n \ge n_0$$

#### 3. Big-Theta Notation ($\Theta$) — Asymptotic Tight Bound
A function $f(n)$ is in $\Theta(g(n))$ if and only if $f(n) \in O(g(n))$ and $f(n) \in \Omega(g(n))$, i.e., there exist constants $c_1, c_2 > 0$ and $n_0 \ge 1$ such that:

$$0 \le c_1 \cdot g(n) \le f(n) \le c_2 \cdot g(n) \quad \forall n \ge n_0$$

### Essential Summations for Loop & Recurrence Analysis
1. **Arithmetic Series**:
   $$\sum_{i=1}^{n} i = 1 + 2 + 3 + \dots + n = \frac{n(n + 1)}{2} = \Theta(n^2)$$
2. **Geometric Series (Increasing)**:
   $$\sum_{i=0}^{k} 2^i = 1 + 2 + 4 + \dots + 2^k = 2^{k+1} - 1 = \Theta(2^k)$$
3. **Geometric Series (Decreasing Halves)**:
   $$\sum_{i=0}^{\infty} \frac{n}{2^i} = n + \frac{n}{2} + \frac{n}{4} + \frac{n}{8} + \dots = 2n = \Theta(n)$$
4. **Harmonic Series**:
   $$\sum_{i=1}^{n} \frac{n}{i} = n \left(1 + \frac{1}{2} + \frac{1}{3} + \dots + \frac{1}{n}\right) = \Theta(n \log n)$$

---

## 4. Working Mechanism

### Rules for Computing Time Complexity from Code
1. **Drop Multiplicative Constants**: $5n^2 \to O(n^2)$.
2. **Drop Lower-Order Terms**: $n^2 + 100n + 500 \to O(n^2)$.
3. **Sequential Statements Add**: If Block A takes $O(f(n))$ and Block B takes $O(g(n))$, then executing A followed by B takes:
   $$O(f(n) + g(n)) = O(\max(f(n), g(n)))$$
4. **Nested Loops Multiply**: If an outer loop runs $f(n)$ times and an independent inner loop runs $g(n)$ times per outer iteration, total work is:
   $$O(f(n) \times g(n))$$
5. **Dependent Nested Loops Sum**: When the inner loop bound depends on the outer loop variable (e.g., `for (int j = 0; j < i; j++)`), write out the summation across all values of `i`.

---

## 5. Visual Representation

### Growth Rate Hierarchy
$$O(1) \prec O(\log n) \prec O(\sqrt{n}) \prec O(n) \prec O(n \log n) \prec O(n^2) \prec O(n^3) \prec O(2^n) \prec O(n!)$$

### Operation Counts as $n$ Grows
| Input Size $n$ | $O(1)$ | $O(\log_2 n)$ | $O(n)$ | $O(n \log_2 n)$ | $O(n^2)$ | $O(2^n)$ |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| $8$ | $1$ | $3$ | $8$ | $24$ | $64$ | $256$ |
| $64$ | $1$ | $6$ | $64$ | $384$ | $4,096$ | $1.84 \times 10^{19}$ |
| $1,024$ | $1$ | $10$ | $1,024$ | $10,240$ | $1,048,576$ | $\approx 10^{308}$ |
| $10^6$ | $1$ | $20$ | $10^6$ | $2 \times 10^7$ | $10^{12}$ (TLE) | $\infty$ |

---

## 6. C++ Implementation Analysis

### File: `../time_and_space_complexity.cpp`

1. **`get_first_element(const vector<int> &arr)`**:
   - Accesses `arr[0]` directly via contiguous base address offset.
   - **Time Complexity**: $O(1)$, **Auxiliary Space**: $O(1)$.
2. **`count_halving_steps(int n)`**:
   - Divides $n$ by $2$ each iteration (`n = n / 2`) until $n \le 1$.
   - After $k$ iterations, $n / 2^k = 1 \implies k = \lfloor \log_2 n \rfloor$.
   - **Time Complexity**: $O(\log n)$, **Auxiliary Space**: $O(1)$.
3. **`sum_elements(const vector<int> &arr)`**:
   - Single loop from `0` to `arr.size() - 1`.
   - **Time Complexity**: $O(n)$, **Auxiliary Space**: $O(1)$.
4. **`linearithmic_operations(int n)`**:
   - Outer loop runs $n$ times; inner loop halves `j` from `n` down to `1` in $\lfloor \log_2 n \rfloor$ steps.
   - **Time Complexity**: $O(n \log n)$, **Auxiliary Space**: $O(1)$.
5. **`count_pairs(int n)`**:
   - Two nested loops each running $n$ times: $n \times n = n^2$.
   - **Time Complexity**: $O(n^2)$, **Auxiliary Space**: $O(1)$.

---

## 7. Dry Runs

### Dry Run of `count_halving_steps(8)` and `linearithmic_operations(8)`
For $n = 8$:
- In `count_halving_steps(8)`:
  - Initial: `n = 8, steps = 0`
  - Iteration 1: `n = 4, steps = 1`
  - Iteration 2: `n = 2, steps = 2`
  - Iteration 3: `n = 1, steps = 3` (Loop terminates since `n > 1` is false)
  - Returns `3` ($\log_2 8 = 3$).
- In `linearithmic_operations(8)`:
  - Outer loop runs for `i = 0, 1, 2, 3, 4, 5, 6, 7` ($8$ iterations).
  - For each `i`, inner loop runs for `j = 8, 4, 2` ($3$ iterations).
  - Total `ops = 8 * 3 = 24` ($n \log_2 n = 8 \times 3 = 24$).

---

## 8. Time Complexity

### Common Loop Patterns Summary

| Loop Pattern | Mathematical Work | Time Complexity |
| :--- | :--- | :---: |
| `for(i = 0; i < n; i += c)` | $n / c$ | $O(n)$ |
| `for(i = 1; i < n; i *= 2)` | $2^k = n \implies k = \log_2 n$ | $O(\log n)$ |
| `for(i = n; i > 1; i /= 2)` | $n / 2^k = 1 \implies k = \log_2 n$ | $O(\log n)$ |
| `for(i = 0; i < n; i++) for(j = 0; j < i; j++)` | $0 + 1 + 2 + \dots + (n-1) = \frac{n(n-1)}{2}$ | $O(n^2)$ |
| `for(i = 1; i <= n; i *= 2) for(j = 0; j < i; j++)` | $1 + 2 + 4 + \dots + n = 2n - 1$ | $O(n)$ |

---

## 9. Space Complexity

### Total Space vs. Auxiliary Space
- **Input Space**: Memory occupied by the problem inputs themselves (e.g., an input array of size $n$ takes $O(n)$ input space).
- **Auxiliary Space**: Extra temporary memory allocated by the algorithm beyond the input data (including dynamic allocations and recursion call stack frames).
  - Example 1: Iterative Binary Search uses `low`, `high`, `mid` $\implies O(1)$ auxiliary space.
  - Example 2: Recursive Binary Search creates $\log_2 n$ stack frames $\implies O(\log n)$ auxiliary stack space.
  - Example 3: Merge Sort allocates a temporary vector `temp` of size $n$ $\implies O(n)$ auxiliary space.

---

## 10. Important Properties and Observations

1. **Why Nested Halving Loops Can Be $O(n)$ Instead of $O(n \log n)$**:
   If the outer loop halves (`for (int m = n; m >= 1; m /= 2)`) and the inner loop runs `m` times (`for (int j = 0; j < m; j++)`), the total work is $n + n/2 + n/4 + \dots + 1 < 2n = O(n)$, **not** $O(n \log n)$.
2. **Why `Build Heap` in `08-Trees/Binary_Heap_Detailed_Explanation.cpp` is $O(n)$**:
   Even though `heapify_down` takes $O(\log n)$ in the worst case, most nodes in a complete binary tree are near the bottom (height $0$ or $1$), yielding $\sum_{h=0}^{\lfloor \log n \rfloor} \lceil \frac{n}{2^{h+1}} \rceil O(h) = O(n)$.
3. **Tree Height Value vs. Tree Height Computation**:
   As noted in your `08-Trees/Recursive_Time_Complexity_Binary_Trees.cpp` (line 50): the *value* of a balanced binary tree's height is $O(\log n)$, but *computing* that height via `Height_Node(root)` visits all $n$ nodes and therefore takes $O(n)$ time and $O(h)$ stack space.

---

## 11. Advantages and Disadvantages

### Advantages of Asymptotic Complexity
- Hardware-independent and programming-language-independent.
- Predicts scalability bottlenecks for large datasets.

### Disadvantages
- Ignores constant factors and cache locality for small $n$ (e.g., Insertion Sort $O(n^2)$ can beat Merge Sort $O(n \log n)$ for $n \le 16$ due to lower overhead and in-place cache locality).

---

## 12. Comparison with Related Concepts

| Metric | Time Complexity | Auxiliary Space Complexity |
| :--- | :--- | :--- |
| **What it measures** | Number of elementary CPU operations | Peak extra memory used at any point in time |
| **Can it be reused?** | No — time spent cannot be reclaimed | Yes — memory freed or popped off the call stack is reused |
| **Recursive Tree Traversal (`Inorder`)** | $O(n)$ (visits every node once) | $O(h)$ (maximum active call stack depth equals tree height $h$) |

---

## 13. Common Mistakes

1. **Assuming Two Nested Loops Always Mean $O(n^2)$**:
   Two-pointer algorithms or outer-halving/inner-linear loops often run in $O(n)$ time. Always trace how the loop variables change.
2. **Confusing Total Recursive Calls with Maximum Stack Depth**:
   In `fibonacci(n)`, total recursive calls are $O(2^n)$ (time complexity), but only one branch is active on the call stack at any instant, so space complexity is $O(n)$, not $O(2^n)$.
3. **Hidden String/Vector Copies in Loops**:
   Writing `postfix = postfix + ch` or passing a `vector` by value inside a recursive call can turn an $O(n)$ algorithm into $O(n^2)$.

---

## 14. Applications

- Selecting data structures for system design (e.g., choosing a Balanced BST / Heap $O(\log n)$ vs. Unsorted Array $O(n)$).
- Estimating whether a solution will pass within a $1$-second time limit ($\approx 10^8$ elementary operations in C++).

---

## 15. Practice Questions

1. **Basic Understanding**: Arrange the following functions in increasing asymptotic order: $n^{1.5}$, $n \log_2 n$, $2^{\log_2 n}$, $n!$, $(\log_2 n)^2$, $2^n$.
2. **Dry-Run / Loop Analysis**: Find the tight $\Theta$ time complexity of:
   ```cpp
   for (int i = 1; i <= n; i++) {
       for (int j = 1; j <= n; j += i) {
           // O(1) work
       }
   }
   ```
3. **Complexity Analysis**: What is the time and auxiliary space complexity of `Count_leaf_Nodes_02(Node* root)` in `08-Trees/BST_01.cpp` for (a) a balanced BST of $n$ nodes, and (b) a skewed BST of $n$ nodes?
4. **Interview Question**: Explain why dynamic array (`std::vector`) `push_back` takes $O(n)$ worst-case time on a resize, yet has $O(1)$ **amortized** time complexity per insertion.

---

## 16. Quick Revision

- **$O(1)$**: Array index lookup, stack `push`/`pop`, queue `enqueue`/`dequeue`, heap `peek`.
- **$O(\log n)$**: Binary search, balanced BST `search`/`insert`/`delete`, binary heap `insert`/`extract_max`, fast exponentiation.
- **$O(n)$**: Linear search, linked list traversal/reversal, tree traversals (`Inorder`, `Preorder`, `Postorder`, `Level_Order`), bottom-up `build_heap`.
- **$O(n \log n)$**: Merge Sort, Heap Sort, Quick Sort (average), sorting `std::vector`.
- **$O(n^2)$**: Bubble Sort, Selection Sort, Insertion Sort (worst/average), Quick Sort (worst case).
- **$O(2^n)$**: Naive Fibonacci, Tower of Hanoi, Generating all subsets of $n$ elements.
