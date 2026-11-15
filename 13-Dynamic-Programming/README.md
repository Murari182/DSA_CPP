# Dynamic Programming (DP) in Modern C++17

A reference guide to optimal substructure, overlapping subproblems, top-down memoization, bottom-up tabulation, state transition design, and space optimization patterns.

---

## 1. What is Dynamic Programming?

**Dynamic Programming (DP)** is an algorithmic optimization technique that solves complex problems by breaking them down into simpler, overlapping subproblems, solving each subproblem once, and storing their solutions to avoid redundant computations.

### Two Necessary Preconditions for DP
1. **Overlapping Subproblems:** The problem can be broken down into subproblems which are reused several times (unlike Divide & Conquer like Merge Sort, where subproblems are completely independent).
2. **Optimal Substructure:** An optimal solution to the problem can be constructed from optimal solutions to its subproblems.

---

## 2. Top-Down (Memoization) vs Bottom-Up (Tabulation)

| Feature | Top-Down (Memoization) | Bottom-Up (Tabulation) |
|---|---|---|
| **Mechanism** | Recursive with cache table | Iterative loop filling table from base cases |
| **Call Stack** | Uses recursion stack memory (\( O(n) \)) | Zero recursion stack; \( O(1) \) function call overhead |
| **Subproblem Evaluation** | Solves only subproblems that are actually needed | Solves all subproblems in topological order |
| **Space Optimization** | Difficult to optimize space | Often straightforward (e.g. keeping only last 2 rows) |
| **Ease of Transition** | Direct translation from naive recurrence | Requires understanding iteration order dependencies |

---

## 3. Canonical DP Problem Archetypes

| Pattern | Classic Problem | State Definition | Transition Recurrence | Complexity |
|---|---|---|---|---|
| **1D Linear DP** | Climbing Stairs / House Robber | `dp[i]`: Max value up to index `i` | `dp[i] = max(dp[i-1], dp[i-2] + val[i])` | Time: \( O(n) \), Space: \( O(1) \) |
| **0/1 Knapsack** | 0/1 Knapsack Problem | `dp[i][w]`: Max value using first `i` items with weight `w` | `dp[i][w] = max(dp[i-1][w], dp[i-1][w - wt[i]] + val[i])` | Time: \( O(n \cdot W) \), Space: \( O(W) \) |
| **Longest Common Subsequence** | LCS | `dp[i][j]`: LCS of `s1[0..i-1]` and `s2[0..j-1]` | `s1[i-1] == s2[j-1] ? 1 + dp[i-1][j-1] : max(dp[i-1][j], dp[i][j-1])` | Time: \( O(m \cdot n) \), Space: \( O(\min(m, n)) \) |
| **Longest Increasing Subsequence** | LIS | `dp[i]`: Length of LIS ending at index `i` | `dp[i] = 1 + max({dp[j] : j < i && arr[j] < arr[i]})` | Time: \( O(n^2) \) / \( O(n \log n) \) with binary search |
| **Interval DP** | Matrix Chain Multiplication | `dp[i][j]`: Min scalar multiplications for chain `i..j` | `dp[i][j] = min_{k} (dp[i][k] + dp[k+1][j] + d_{i-1} d_k d_j)` | Time: \( O(n^3) \), Space: \( O(n^2) \) |
| **Grid DP** | Unique Paths / Minimum Path Sum | `dp[i][j]`: Min cost from `(0,0)` to `(i,j)` | `dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])` | Time: \( O(m \cdot n) \), Space: \( O(n) \) |
