# Backtracking and State-Space Trees: Subsets, Permutations & N-Queens

## Related Implementation

- `../Backtracking_Algorithms.cpp` *(Supplementary implementation created for this folder)*

---

## 1. Concept Introduction

### What is the Concept?
**Backtracking** is a systematic, depth-first algorithmic technique for solving constraint-satisfaction and combinatorial enumeration problems. It builds candidate solutions incrementally one decision at a time, and as soon as it determines that the current partial candidate cannot possibly lead to a valid complete solution (or after exploring a complete solution), it **undoes ("backtracks")** its last decision and tries the next alternative.

### Why is it Required?
Problems like generating all subsets (Power Set), generating all permutations, solving Sudoku, or placing $N$ non-attacking Queens on an $N \times N$ chessboard require exploring a tree of choices. Without undoing changes (`pop_back()`, `swap` back, or resetting `board[row][col] = '.'`) as we return up the recursion tree, we would have to clone the entire board or vector at every node, wasting massive amounts of memory and time.

---

## 2. Fundamental Theory

### The Universal Backtracking Template ("Choose – Explore – Unchoose")
Every backtracking algorithm follows a 3-step template at each decision level `idx`:
```cpp
void backtrack(State &state, int idx) {
    if (is_goal_reached(idx)) {
        record_or_print(state);
        return;
    }

    for (Choice c : available_choices(idx)) {
        if (is_valid(state, c)) {
            apply_choice(state, c);       // 1. CHOOSE (modify state in-place)
            backtrack(state, idx + 1);    // 2. EXPLORE (recurse to next level)
            undo_choice(state, c);        // 3. UNCHOOSE / BACKTRACK (restore exact state)
        }
    }
}
```

### Pruning (Bounding Function)
- **Exhaustive Recursion**: Explores every leaf of the state-space tree.
- **Backtracking with Pruning**: Checks a validity constraint (`is_safe_queen(board, row, col, n)`) **before** recursing. If a partial state already violates a constraint (e.g., two queens in the same column or diagonal), the entire subtree beneath that choice is **pruned (skipped)** immediately!

---

## 3. Mathematical Representation

### Combinatorial Sizes of State-Space Trees
1. **Subsets (Power Set) of an $n$-element set**:
   For each of the $n$ elements, we have $2$ independent choices (**Include** or **Exclude**):
   $$\text{Total Subsets} = \underbrace{2 \times 2 \times \dots \times 2}_{n \text{ times}} = 2^n$$
2. **Permutations of $n$ distinct elements**:
   Index $0$ has $n$ choices, index $1$ has $n - 1$ choices, ..., index $n - 1$ has $1$ choice:
   $$\text{Total Permutations} = n \times (n - 1) \times (n - 2) \times \dots \times 1 = n!$$
3. **N-Queens Attack Conditions**:
   Two queens at $(r_1, c_1)$ and $(r_2, c_2)$ attack each other if and only if:
   - **Same Row**: $r_1 == r_2$
   - **Same Column**: $c_1 == c_2$
   - **Same Diagonal**: $|r_1 - r_2| == |c_1 - c_2|$ (i.e., $r_1 - c_1 == r_2 - c_2$ for main diagonal, or $r_1 + c_1 == r_2 + c_2$ for anti-diagonal).

---

## 4. Working Mechanism

### 1. Subset Generation (`generate_subsets` in `../Backtracking_Algorithms.cpp`)
At index `idx`:
- **Base Case**: If `idx == nums.size()`, print the elements currently in `current` and return.
- **Branch 1 (Include `nums[idx]`)**:
  - `current.push_back(nums[idx]);`
  - `generate_subsets(nums, idx + 1, current);`
- **Branch 2 (Backtrack & Exclude `nums[idx]`)**:
  - `current.pop_back();` *(Undoes the `push_back`!)*
  - `generate_subsets(nums, idx + 1, current);`

### 2. String Permutations (`generate_permutations`)
At index `idx`:
- **Base Case**: If `idx == str.size()`, print `str` and return.
- Loop `i` from `idx` to `str.size() - 1`:
  - **Choose**: `swap(str[idx], str[i]);` (places character `str[i]` at position `idx`).
  - **Explore**: `generate_permutations(str, idx + 1);`
  - **Unchoose (Backtrack)**: `swap(str[idx], str[i]);` (restores `str` to its original order before the next loop iteration).

### 3. N-Queens (`count_n_queens`)
- Places **one queen per row** (`row = 0` to `n - 1`).
- In row `row`, tries every column `col = 0` to `n - 1`:
  - Calls `is_safe_queen(board, row, col, n)` to check the column above (`[0 .. row-1][col]`), the upper-left diagonal, and the upper-right diagonal. *(Why don't we need to check rows below `row`? Because no queens have been placed in rows `> row` yet!)*
  - If safe: sets `board[row][col] = 'Q'`, recurses to `row + 1`, and then **backtracks** by resetting `board[row][col] = '.'`.

---

## 5. Visual Representation

### 1. State-Space Tree for `generate_subsets({1, 2})`
```
                           idx = 0: current = {}
                          /                     \
               Include 1 /                       \ Exclude 1 (pop_back)
                        /                         \
             idx = 1: {1}                         idx = 1: {}
             /          \                         /         \
  Include 2 /            \ Exclude 2   Include 2 /           \ Exclude 2
           /              \                     /             \
     idx=2: {1, 2}    idx=2: {1}           idx=2: {2}     idx=2: {}
```

### 2. The Two Valid $4 \times 4$ N-Queens Boards (`n = 4`)
```
Solution 1:                 Solution 2:
. Q . .   (row 0, col 1)    . . Q .   (row 0, col 2)
. . . Q   (row 1, col 3)    Q . . .   (row 1, col 0)
Q . . .   (row 2, col 0)    . . . Q   (row 2, col 3)
. . Q .   (row 3, col 2)    . Q . .   (row 3, col 1)
```

---

## 6. C++ Implementation Analysis

### File: `../Backtracking_Algorithms.cpp`

1. **`generate_subsets(const vector<int> &nums, int idx, vector<int> &current)`**:
   - Passes `current` **by reference** (`vector<int> &current`) so only **one** vector exists in memory across all $2^n$ recursive calls.
   - `current.pop_back()` restores `current` before exploring the exclusion branch.
2. **`generate_permutations(string &str, int idx)`**:
   - Modifies `str` in-place via `swap(str[idx], str[i])` and restores it immediately after returning.
3. **`is_safe_queen` & `count_n_queens`**:
   - Returns the total number of valid $N$-Queens configurations (`2` for $n = 4$, `92` for $n = 8$).

---

## 7. Dry Runs

### Dry Run of `generate_permutations("ABC", 0)`
| Call Level `idx` | Loop `i` | Swap Applied | `str` State | Action / Output | Backtrack Swap |
| :---: | :---: | :--- | :---: | :--- | :--- |
| `idx = 0` | `i = 0` | `swap(0, 0)` | `"ABC"` | Recurse `idx = 1` | — |
| `idx = 1` | `i = 1` | `swap(1, 1)` | `"ABC"` | Recurse `idx = 2` $\to$ **Prints `ABC`** | `swap(1, 1)` |
| `idx = 1` | `i = 2` | `swap(1, 2)` | `"ACB"` | Recurse `idx = 2` $\to$ **Prints `ACB`** | `swap(1, 2)` $\to$ `"ABC"` |
| `idx = 0` | `i = 1` | `swap(0, 1)` | `"BAC"` | Recurse `idx = 1` $\to$ **Prints `BAC`, `BCA`** | `swap(0, 1)` $\to$ `"ABC"` |
| `idx = 0` | `i = 2` | `swap(0, 2)` | `"CBA"` | Recurse `idx = 1` $\to$ **Prints `CBA`, `CAB`** | `swap(0, 2)` $\to$ `"ABC"` |

---

## 8. Time Complexity

| Algorithm | Time Complexity | Explanation |
| :--- | :---: | :--- |
| **Subset Generation (`generate_subsets`)** | $O(n \cdot 2^n)$ | $2^n$ subsets generated; printing each subset takes up to $O(n)$ work |
| **Permutations (`generate_permutations`)** | $O(n \cdot n!)$ | $n!$ leaf permutations; printing each string of length $n$ takes $O(n)$ |
| **N-Queens (`count_n_queens`)** | $O(n!)$ (Tighter than $O(n^n)$) | Pruning ensures at most $n$ choices in row 0, $n-1$ in row 1, $n-2$ in row 2, etc.; each `is_safe_queen` check takes $O(n)$ |

---

## 9. Space Complexity

- **`generate_subsets`**: $O(n)$ auxiliary space ($O(n)$ recursion stack depth + $O(n)$ for `vector<int> &current`).
- **`generate_permutations`**: $O(n)$ auxiliary stack space (in-place swapping on `str`).
- **`count_n_queens`**: $O(n^2)$ for the $n \times n$ board + $O(n)$ recursion stack depth.

---

## 10. Important Properties and Observations

1. **Why Passing `current` by Reference (`vector<int> &current`) + `pop_back()` is Faster Than Passing by Value**:
   If `current` were passed by value (`vector<int> current`), you wouldn't need `pop_back()`, **but** every single node in the $2^n$-node recursion tree would allocate and copy a new `vector` on the heap! Passing by reference and calling `pop_back()` performs $O(1)$ work per step and allocates only a single vector for the entire traversal.

---

## 11. Advantages and Disadvantages

### Advantages
- Finds **all** exact solutions (or proves no solution exists).
- Pruning drastically reduces the search space compared to brute-force generation of all configurations.

### Disadvantages
- Worst-case time complexity remains exponential ($O(2^n)$ or $O(n!)$), making it suitable only for small $n$ (typically $n \le 20$ for subsets, $n \le 12$ for permutations/N-Queens).

---

## 12. Comparison with Related Concepts

### Backtracking vs. Brute Force vs. Dynamic Programming

| Feature | Brute Force | Backtracking | Dynamic Programming |
| :--- | :--- | :--- | :--- |
| **Search Strategy** | Generates all full candidates, tests at the end | Builds partial candidates, **prunes invalid branches early** | Caches overlapping subproblems to avoid recomputation |
| **Typical Goal** | Simple verification | Enumerate all valid configurations (`Subsets`, `N-Queens`) | Count/optimize without listing every configuration |

---

## 13. Common Mistakes

1. **Forgetting the Undo Step (`pop_back()`, `swap` back, or `board[r][c] = '.'`)**:
   If you forget to undo a choice after the recursive call returns, the mutated state leaks into sibling branches of the recursion tree, producing corrupted results!
2. **Checking All 8 Directions in `is_safe_queen`**:
   Since queens are placed strictly top-to-bottom row by row (`row = 0, 1, ..., n-1`), only rows `0 .. row - 1` above the current row can contain queens. You only need to check 3 upward directions: straight up, upper-left diagonal, and upper-right diagonal.

---

## 14. Applications

1. **Constraint Satisfaction Puzzles**: Sudoku solver, Crossword filler, N-Queens, Knight's Tour.
2. **Combinatorial Optimization**: Subset Sum, Combination Sum, Palindrome Partitioning, Word Search in a 2D Grid.
3. **SAT Solvers (DPLL Algorithm)** and automated theorem proving.

---

## 15. Practice Questions

1. **Basic Understanding**: In `generate_subsets({1, 2, 3})`, how many total calls are made to `generate_subsets` (including both internal nodes and base-case leaves of the recursion tree)?
2. **Implementation**: Given an array of positive integers `candidates` and a `target` sum, write a backtracking function `combination_sum(candidates, idx, current, current_sum, target)` that prints all subsets whose sum equals `target` (pruning whenever `current_sum > target`).
3. **Dry-Run Problem**: Trace `count_n_queens` on $n = 3$ and show why every branch gets pruned and the function returns `0` valid solutions.
4. **Complexity Analysis**: How can you optimize `is_safe_queen` from $O(n)$ time to **$O(1)$ time** using three boolean arrays: `col_used[n]`, `diag1_used[2*n]`, and `diag2_used[2*n]`?
5. **Interview Question**: If the input string `str` in `generate_permutations` contains duplicate characters (e.g., `"AAB"`), how do you modify the backtracking loop to avoid printing duplicate permutations?

---

## 16. Quick Revision

- **Backtracking Mantra**: **Choose $\to$ Explore $\to$ Unchoose (Backtrack)**.
- **Subsets**: 2 branches per element (Include / Exclude) $\implies 2^n$ subsets, $O(n \cdot 2^n)$ time, $O(n)$ space.
- **Permutations**: Swap `str[idx]` with `str[i]` for $i \in [\text{idx}, n-1]$, recurse, swap back $\implies n!$ permutations, $O(n \cdot n!)$ time.
- **N-Queens**: Place 1 queen per row; prune invalid columns/diagonals using `is_safe_queen` before recursing.
