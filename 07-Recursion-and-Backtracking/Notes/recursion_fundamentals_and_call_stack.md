# Recursion Fundamentals, Call Stack & Recurrence Relations

## Related Implementation

- `../rec.cpp` *(Original recursive countdown implementation)*
- `../Recursion_Fundamentals.cpp` *(Supplementary implementation created for this folder)*
- `../../08-Trees/Recursive_Time_Complexity_Binary_Trees.cpp` *(Existing reference sheet on recursive recurrences)*

---

## 1. Concept Introduction

### What is the Concept?
**Recursion** is a problem-solving technique in which a function calls **itself** directly or indirectly on a smaller instance of the same problem until it reaches a terminating condition known as the **Base Case**.

### Why is it Required?
Inductive and hierarchical structures—such as Binary Trees (`08-Trees`), Divide-and-Conquer sorting (`03-Sorting/Merge_and_Quick_Sort.cpp`), and Backtracking state spaces—are defined recursively (a Binary Tree is either `NULL` or a root node connected to two smaller Binary Trees). Recursion mirrors this mathematical structure directly in code.

---

## 2. Fundamental Theory

### The Three Laws of Recursion
1. **Base Case (Stopping Condition)**: The smallest subproblem whose answer is known directly without further recursion (e.g., `if (n == 1) return 1;` in `../rec.cpp`, or `if (root == NULL) return 0;` in `08-Trees`). Without a valid base case, recursion continues until the call stack overflows (**Stack Overflow / `SIGSEGV`**).
2. **Recursive Step (Progress Toward Base Case)**: Every recursive call must strictly reduce the problem size (e.g., `n - 1`, `n / 2`, `root->left`) so that it is guaranteed to reach the base case in a finite number of steps.
3. **Combine / Return**: Combine the result(s) of the recursive call(s) with local work to form the answer for the current call frame.

### Types of Recursion
1. **Tail Recursion** *(e.g., `print(int n)` in `../rec.cpp`)*: The recursive call `return print(n - 1);` is the **very last operation** in the function; no computation is performed after the recursive call returns.
2. **Head / Non-Tail Linear Recursion** *(e.g., `factorial(n)`)*: Work is performed **after** the recursive call returns (`return n * factorial(n - 1);`).
3. **Binary / Tree Recursion** *(e.g., `fibonacci(n)`, `tower_of_hanoi(n, ...)`, and all Binary Tree traversals in `08-Trees`)*: A function makes **two or more** recursive calls per activation frame, forming a **Recursion Tree**.

---

## 3. Mathematical Representation

### Recurrence Relations in `../rec.cpp` and `../Recursion_Fundamentals.cpp`

1. **Countdown (`print(n)` in `../rec.cpp`) & Factorial (`factorial(n)`)**:
   $$T(n) = T(n - 1) + c, \quad T(1) = c \implies T(n) = c \cdot n = \Theta(n)$$
2. **Fast Exponentiation (`fast_power(a, b)`)**:
   $$a^b = \begin{cases} 1 & \text{if } b = 0 \\ \left(a^{\lfloor b/2 \rfloor}\right)^2 & \text{if } b \text{ is even} \\ a \cdot \left(a^{\lfloor b/2 \rfloor}\right)^2 & \text{if } b \text{ is odd} \end{cases}$$
   Recurrence:
   $$T(b) = T(\lfloor b / 2 \rfloor) + c \implies T(b) = \Theta(\log_2 b)$$
3. **Naive Fibonacci (`fibonacci(n)`)**:
   $$F(n) = F(n - 1) + F(n - 2), \quad F(0) = 0, \; F(1) = 1$$
   $$T(n) = T(n - 1) + T(n - 2) + c \implies T(n) = \Theta(\phi^n) \subseteq O(2^n), \text{ where } \phi = \frac{1 + \sqrt{5}}{2} \approx 1.618$$
4. **Tower of Hanoi (`tower_of_hanoi(n, src, helper, dest)`)**:
   $$T(n) = 2T(n - 1) + 1, \quad T(0) = 0 \implies T(n) = 2^n - 1 = \Theta(2^n)$$

---

## 4. Working Mechanism

### How the CPU Call Stack Executes Recursion
Every time a function is called:
1. **Push Activation Frame (Winding Phase)**: A new **Stack Frame** containing the function's parameters (`n`), local variables, and return address is pushed onto the **System Call Stack**.
2. **Base Case Reached**: The deepest call hits the base case and returns a value without pushing any further frames.
3. **Pop Activation Frame (Unwinding Phase)**: Each waiting stack frame resumes at its return address, completes any post-call work, and pops off the stack in **LIFO** order.

---

## 5. Visual Representation

### 1. Call Stack Winding & Unwinding for `print(3)` in `../rec.cpp`
```
WINDING PHASE (Pushing Stack Frames)            UNWINDING PHASE (Returning 1)
------------------------------------            -----------------------------
Call print(3) -> prints 3                       Frame print(1) returns 1
  |                                               |
  v                                               v
Call print(2) -> prints 2                       Frame print(2) returns 1
  |                                               |
  v                                               v
Call print(1) -> prints 1, hits (n == 1)!       Frame print(3) returns 1 to main()
```

### 2. Recursion Tree for `fibonacci(4)` (Showing Overlapping Subproblems)
```
                        fib(4)
                       /      \
                  fib(3)      fib(2)
                 /      \     /    \
             fib(2)   fib(1) fib(1) fib(0)
             /    \
         fib(1)  fib(0)
```
Notice that `fib(2)` is computed twice and `fib(1)` is computed three times—this exponential branching is why naive Fibonacci takes $O(2^n)$ time!

---

## 6. C++ Implementation Analysis

### 1. Original File: `../rec.cpp`
```cpp
#include<iostream>
using namespace std;

int print(int n){

    cout << n << endl;
    if(n==1){
        return 1;
    }

    return print(n - 1);
}

int main(){

    print(1000);

    return 0;
}
```
- **Purpose**: Prints numbers from `n` (`1000`) down to `1` in descending order and returns `1`.
- **Order of Execution**: Because `cout << n << endl;` appears **before** `return print(n - 1);`, the numbers are printed during the **winding phase** (`1000, 999, 998, ..., 1`). *(If `cout << n << endl;` were placed **after** `print(n - 1);`, it would print during the **unwinding phase** in ascending order: `1, 2, 3, ..., 1000`!)*
- **Edge Case Note**: If `print(0)` or `print(-5)` were called, `n == 1` would be bypassed and `n - 1` would decrease forever until Stack Overflow. Writing `if (n <= 1)` protects against non-positive inputs.

### 2. Supplementary File: `../Recursion_Fundamentals.cpp`
- **`factorial(int n)`**: Linear recursion $O(n)$ time, $O(n)$ stack space.
- **`fibonacci(int n)`**: Tree recursion $O(2^n)$ time, $O(n)$ stack space.
- **`sum_of_digits(int n)`**: Extracts last digit `n % 10` and recurses on `n / 10` in $O(\log_{10} n)$ time.
- **`fast_power(long long a, int b)`**: Computes `half = fast_power(a, b / 2)` **once** and squares `half * half`, reducing time from $O(b)$ to $O(\log_2 b)$.
- **`tower_of_hanoi(int n, char src, char helper, char dest)`**: Moves $n - 1$ disks from `src` to `helper`, moves disk $n$ from `src` to `dest`, and moves $n - 1$ disks from `helper` to `dest` in $2^n - 1$ moves.

---

## 7. Dry Runs

### Dry Run 1: `fast_power(2, 10)`
| Call Depth | Function Call | `b` | Recursive Call Made | Returned `half` | Parity of `b` | Return Value |
| :---: | :--- | :---: | :--- | :---: | :---: | :---: |
| 1 | `fast_power(2, 10)` | `10` | `fast_power(2, 5)` | `32` | Even | `32 * 32 = 1024` |
| 2 | `fast_power(2, 5)` | `5` | `fast_power(2, 2)` | `4` | Odd | `2 * 4 * 4 = 32` |
| 3 | `fast_power(2, 2)` | `2` | `fast_power(2, 1)` | `2` | Even | `2 * 2 = 4` |
| 4 | `fast_power(2, 1)` | `1` | `fast_power(2, 0)` | `1` | Odd | `2 * 1 * 1 = 2` |
| 5 | `fast_power(2, 0)` | `0` | Base Case (`b == 0`) | — | — | `1` |

### Dry Run 2: `tower_of_hanoi(3, 'A', 'B', 'C')` ($2^3 - 1 = 7$ Moves)
1. Move disk 1 from `A` to `C`
2. Move disk 2 from `A` to `B`
3. Move disk 1 from `C` to `B` *(Top 2 disks are now on helper rod `B`!)*
4. **Move disk 3 from `A` to `C`** *(Largest disk placed on destination `C`!)*
5. Move disk 1 from `B` to `A`
6. Move disk 2 from `B` to `C`
7. Move disk 1 from `A` to `C` *(All 3 disks are now on destination `C`!)*

---

## 8. Time Complexity

| Function | Recurrence Relation | Best / Avg / Worst Time | Why? |
| :--- | :--- | :---: | :--- |
| **`print(n)` (`rec.cpp`)** | $T(n) = T(n-1) + c$ | $O(n)$ | Makes $n$ sequential calls |
| **`factorial(n)`** | $T(n) = T(n-1) + c$ | $O(n)$ | $n$ multiplications |
| **`sum_of_digits(n)`** | $T(n) = T(n/10) + c$ | $O(\log_{10} n)$ | One call per decimal digit of $n$ |
| **`fast_power(a, b)`** | $T(b) = T(b/2) + c$ | $O(\log_2 b)$ | Halves exponent $b$ at each step |
| **`fibonacci(n)`** | $T(n) = T(n-1) + T(n-2) + c$ | $O(2^n)$ ($\Theta(\phi^n)$) | Binary recursion tree of height $n$ |
| **`tower_of_hanoi(n)`** | $T(n) = 2T(n-1) + c$ | $O(2^n)$ | Exactly $2^n - 1$ disk moves |

---

## 9. Space Complexity

**Key Rule**: The auxiliary stack space of a recursive function equals the **maximum depth of the recursion tree** (the longest root-to-leaf path active on the call stack at any single moment), **not** the total number of calls!
- `print(n)` and `factorial(n)`: $O(n)$ stack space.
- `fast_power(a, b)`: $O(\log_2 b)$ stack space.
- `fibonacci(n)` and `tower_of_hanoi(n)`: **$O(n)$ stack space** (even though total calls are $O(2^n)$, the left branch finishes and pops its stack frames before the right branch is entered).

---

## 10. Important Properties and Observations

1. **Why `fast_power` Stores `long long half = fast_power(a, b / 2)` Instead of Calling `fast_power(a, b / 2) * fast_power(a, b / 2)`**:
   - Calling `fast_power(a, b / 2)` **once** and squaring `half * half` gives $T(b) = T(b/2) + c \implies \mathbf{O(\log b)}$.
   - Calling `fast_power(a, b / 2) * fast_power(a, b / 2)` **twice** gives $T(b) = 2T(b/2) + c \implies \mathbf{O(b)}$, completely destroying the logarithmic speedup! (See Pattern 14 vs. Pattern 15 in your `08-Trees/Recursive_Time_Complexity_Binary_Trees.cpp` lines 215–238!)

---

## 11. Advantages and Disadvantages

### Advantages
- Expresses tree, divide-and-conquer, and combinatorial algorithms cleanly and concisely.
- Eliminates the need to manage an explicit stack manually.

### Disadvantages
- Each recursive call incurs stack-frame push/pop overhead and consumes call stack memory ($O(\text{depth})$).
- Deep linear recursion (e.g., $n = 10^6$) can exhaust the OS call stack limit and crash, whereas an iterative loop uses $O(1)$ stack space.

---

## 12. Comparison with Related Concepts

### Recursion vs. Iteration

| Feature | Recursion (`rec.cpp`) | Iteration (`while` / `for` loop) |
| :--- | :--- | :--- |
| **State Storage** | Implicit OS Call Stack frames | Explicit local loop variables |
| **Termination** | Base case (`if (n == 1) return 1;`) | Loop condition (`while (n >= 1)`) |
| **Auxiliary Space for $n$ steps** | $O(n)$ stack frames | $O(1)$ |
| **Best Suited For** | Trees, Divide & Conquer, Backtracking | Simple linear scans and counting |

---

## 13. Common Mistakes

1. **Missing or Unreachable Base Case**:
   Causes infinite recursion and Stack Overflow.
2. **Recomputing Identical Subproblems Twice in Divide-and-Conquer**:
   Writing `return fast_power(a, b/2) * fast_power(a, b/2)` ($O(b)$) instead of saving `long long half = fast_power(a, b/2); return half * half;` ($O(\log b)$).
3. **Pass-by-Value of Large Containers (`vector<int> v`)**:
   Passing `vector<int> arr` without `&` copies all $n$ elements at every recursive step, multiplying time and space complexity by $O(n)$.

---

## 14. Applications

- All Binary Tree and BST algorithms (`08-Trees`).
- Merge Sort and Quick Sort (`03-Sorting/Merge_and_Quick_Sort.cpp`).
- Backtracking and Combinatorial Search (`../Backtracking_Algorithms.cpp`).

---

## 15. Practice Questions

1. **Basic Understanding**: In `../rec.cpp`, if you swap line 6 (`cout << n << endl;`) so that it appears **after** `print(n - 1);`, what will the output be for `print(5)`?
2. **Implementation**: Write a recursive function `bool is_palindrome(const string &s, int left, int right)` that checks if a string is a palindrome in $O(n)$ time.
3. **Dry-Run Problem**: Draw the complete recursion tree for `tower_of_hanoi(3, 'A', 'B', 'C')` and label the exact order (1 to 7) in which the `cout` statements execute.
4. **Complexity Analysis**: Solve the recurrence $T(n) = 3T(n/2) + c$ and $T(n) = T(n/2) + c \cdot n$ (verify your answer against Patterns 17 and 19 in `08-Trees/Recursive_Time_Complexity_Binary_Trees.cpp`).
5. **Interview Question**: How does **Tail Call Optimization (TCO)** allow a compiler to execute a tail-recursive function like `print(n)` in `rec.cpp` using $O(1)$ stack space instead of $O(n)$ stack space?

---

## 16. Quick Revision

- **Base Case**: Stops recursion; **Recursive Step**: Shrinks problem toward base case.
- **Time Complexity** $\propto$ Total nodes in the Recursion Tree.
- **Auxiliary Stack Space** $\propto$ Maximum height (depth) of the Recursion Tree.
