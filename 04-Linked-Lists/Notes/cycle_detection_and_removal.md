# Floyd's Cycle Detection (Tortoise & Hare) and Cycle Removal in Linked Lists

## Related Implementation

- `../linked_list-01.cpp` *(Lines 188–254: `Dect_cycle`, `make_cycle`, `cos_cycle`)*
- `../Linked_List-02.cpp` *(Lines 188–282: `Dect_cycle`, `make_cycle`, `cos_cycle`, `remove_cycle`)*

---

## 1. Concept Introduction

### What is the Concept?
A **cycle (or loop)** in a Singly Linked List occurs when the `next` pointer of the last node points back to an earlier node in the list (or to itself) instead of `NULL`.
**Floyd's Cycle-Finding Algorithm** (also known as the **Tortoise and Hare Algorithm**) uses two pointers moving at different speeds (`slow` moving 1 step per iteration and `fast` moving 2 steps per iteration) to:
1. Detect whether a cycle exists in **$O(n)$ time and $O(1)$ auxiliary space** (`Dect_cycle()`).
2. Locate the exact starting node of the cycle and break the cycle (`remove_cycle()`).

### Why is it Required?
If a linked list accidentally contains a cycle, any standard traversal (`print()`, `delete_all()`, `count` in `del_last()`) will enter an **infinite loop** because `temp != NULL` will remain true forever. Naive cycle detection using a hash set of visited `Node*` addresses requires $O(n)$ extra memory, whereas Floyd's algorithm requires **$O(1)$ memory**.

---

## 2. Fundamental Theory

### How Floyd's Tortoise and Hare Algorithm Works
- **Two Pointers**:
  - `Node* slow = head;` (moves 1 step: `slow = slow->next`)
  - `Node* fast = head;` (moves 2 steps: `fast = fast->next->next`)
- **Case 1: No Cycle Exists**:
  `fast` (or `fast->next`) eventually reaches `NULL` in $\lceil n / 2 \rceil$ steps. The function returns `false`.
- **Case 2: A Cycle Exists**:
  Once both `slow` and `fast` enter the cycle of length $C$, the relative speed between `fast` and `slow` is:
  $$v_{\text{relative}} = 2 - 1 = 1 \text{ step per iteration}$$
  Because `fast` closes the gap to `slow` by **exactly 1 node per step**, `fast` can never "jump over" `slow` without landing on the exact same node! Therefore, `slow == fast` is guaranteed to occur within at most $C$ steps after `slow` enters the cycle.

---

## 3. Mathematical Representation

### Mathematical Proof of Cycle Start Detection (`remove_cycle`)
Let:
- $L$ = Number of nodes from `head` to the **start of the cycle** (non-cyclic stem length).
- $C$ = Total number of nodes inside the cycle.
- $x$ = Distance (along the cycle direction) from the **start of the cycle** to the **meeting point** where `slow == fast`.

When `slow` and `fast` first meet:
1. Distance traveled by `slow`:
   $$d_{\text{slow}} = L + x$$
   *(Note: `slow` never completes a full lap before meeting `fast` because once `slow` enters the cycle, `fast` is at most $C - 1$ steps behind `slow` and closes the gap by 1 node per step.)*
2. Distance traveled by `fast` (which has completed $k \ge 1$ full laps around the cycle):
   $$d_{\text{fast}} = L + k \cdot C + x$$
3. Since `fast` moves twice as fast as `slow` ($d_{\text{fast}} = 2 \cdot d_{\text{slow}}$):
   $$2(L + x) = L + k \cdot C + x$$
   $$L + x = k \cdot C$$
   $$L = k \cdot C - x = (k - 1)C + (C - x)$$

### Geometric Interpretation of $L = (k - 1)C + (C - x)$
- The distance from `head` to the cycle start is $L$.
- The remaining distance forward along the cycle from the **meeting point** back to the **cycle start** is $C - x$ (plus $(k - 1)$ full laps around the cycle).
- **Therefore**: If we reset `slow = head`, keep `fast` at the meeting point, and advance **both** `slow` and `fast` by **1 step at a time** (`slow = slow->next; fast = fast->next;`), they will meet at the **exact starting node of the cycle** after $L$ steps!

---

## 4. Working Mechanism

### Step-by-Step Mechanism of Your Cycle Functions

1. **`make_cycle()`**:
   - Traverses `temp` to the last node (`while (temp->next != NULL) temp = temp->next;`).
   - Links `temp->next = head;` (creates a full-list cycle where $L = 0$).
2. **`cos_cycle(int val)`** *(Custom Cycle at Target Value)*:
   - Traverses `temp` to the last node (`tail`).
   - Traverses `req` from `head` until `req->data == val`.
   - Sets `temp->next = req;` so the last node loops back to the node containing `val`.
3. **`Dect_cycle()`**:
   - Initializes `slow = head, fast = head`.
   - Loops `while (fast != NULL && fast->next != NULL)`:
     - `slow = slow->next;`
     - `fast = fast->next->next;`
     - If `slow == fast`, prints `slow->data << " = " << fast->data` and returns `true`.
   - Returns `false` if loop ends.
4. **`remove_cycle()`** (in `Linked_List-02.cpp`):
   - Phase 1: Detects the meeting point where `slow == fast`.
   - Phase 2: Resets `slow = head` and advances both `slow` and `fast` by 1 step (`while (slow != fast)`) until they meet at the cycle start node.
   - Phase 3: Walks `temp` around the cycle (`while (temp->next != slow)`) to find the last node of the cycle, and breaks the cycle by setting `temp->next = NULL;`.

---

## 5. Visual Representation

### Diagram of Cycle Parameters ($L = 3, C = 5, x = 2$)
```
                       L = 3 steps                   CycleStart (val = 40)
head                                                       |
 |                                                         v
[10] ---> [20] ---> [30] ------------------------------> [40] ---> [50]
                                                           ^         |
                                                           |         v
                                                         [80] <--- [60] <--- [70]
                                                                               ^
                                                                               |
                                                                    Meeting Point (x = 2)
```
Here:
- $L = 3$ (`10 -> 20 -> 30 -> 40`)
- $C = 5$ (`40 -> 50 -> 70 -> 60 -> 80 -> 40`)
- Meeting point is `70` ($x = 2$ steps past `40`, since $L + x = 3 + 2 = 5 = 1 \cdot C$).
- Remaining distance from `70` to `40` is $C - x = 5 - 2 = 3 = L$.

---

## 6. C++ Implementation & Code Review (`Linked_List-02.cpp`)

### Important Code Review Observations in `remove_cycle()` (Lines 256–282 of `Linked_List-02.cpp`)
*(Documented here without modifying your original file)*

```cpp
    void remove_cycle(){

        Node *slow = head;
        Node *fast = head;

        while(fast!=NULL || fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;

            if(slow == fast){
                cout << "Cycle found" << endl;
                break;
            }
        }
```
1. **Logical OR (`||`) vs. Logical AND (`&&`) on Line 261**:
   - In `Dect_cycle()` (line 194), you wrote the correct condition: `while(fast != NULL && fast->next != NULL)`.
   - In `remove_cycle()` (line 261), `||` was written instead of `&&`: `while(fast != NULL || fast->next != NULL)`.
   - **Why `&&` is required**: If `remove_cycle()` is called on a list **without** a cycle, when `fast` reaches the last node (`fast != NULL` is true, `fast->next == NULL`), `fast = fast->next->next` sets `fast = NULL`. On the next iteration, `fast != NULL` is false, so `||` evaluates the right-hand side `fast->next != NULL` on a `NULL` pointer, causing a Segmentation Fault! Furthermore, if no cycle is found after the loop exits, `remove_cycle()` should return immediately (`if (fast == NULL || fast->next == NULL) return;`).
2. **Efficiency Note on Phase 3 (Lines 277–281)**:
   - Your code finds the node before the cycle start by running `Node *temp = slow; while(temp->next != slow) temp = temp->next; temp->next = NULL;`. This works accurately for all cycles (including full-list cycles created by `make_cycle()` where `slow == head`)!

---

## 7. Dry Runs

### Dry Run of `cos_cycle(30)`, `Dect_cycle()`, and `remove_cycle()`
Suppose list is `10 --> 20 --> 30 --> 40 --> 50 --> NULL`, and we call `cos_cycle(30)` so `50->next` points to `30` ($L = 2, C = 3$):

| Phase / Step | `slow` Node | `fast` Node | Explanation |
| :--- | :---: | :---: | :--- |
| **Phase 1: Init** | `10` | `10` | Both start at `head` |
| **Phase 1: Step 1** | `20` | `30` | `slow` moves 1, `fast` moves 2 |
| **Phase 1: Step 2** | `30` | `50` | Both are now inside the cycle `{30, 40, 50}` |
| **Phase 1: Step 3** | `40` | `40` | `fast` moves `50 -> 30 -> 40`; **`slow == fast` at `40`!** |
| **Phase 2: Reset** | `10` | `40` | `slow` reset to `head` (`10`); `fast` stays at `40` |
| **Phase 2: Step 1** | `20` | `50` | Both move **1 step** |
| **Phase 2: Step 2** | `30` | `30` | **`slow == fast` at `30` (the exact start of the cycle!)** |
| **Phase 3: Unlink** | `30` | `30` | `temp` walks `30 -> 40 -> 50` (`temp->next == 30`) and sets `50->next = NULL` |

---

## 8. Time Complexity

| Function | Best Case | Average Case | Worst Case | Explanation |
| :--- | :---: | :---: | :---: | :--- |
| `Dect_cycle()` | $O(1)$ | $O(n)$ | $O(n)$ | `slow` takes at most $L + C \le n$ steps before meeting `fast` or `fast` hitting `NULL` |
| `remove_cycle()` | $O(n)$ | $O(n)$ | $O(n)$ | Phase 1: $\le n$ steps; Phase 2: $L$ steps; Phase 3: $C$ steps $\implies O(n)$ total |
| `make_cycle()` | $O(n)$ | $O(n)$ | $O(n)$ | Traverses from `head` to the last node |
| `cos_cycle(val)` | $O(n)$ | $O(n)$ | $O(n)$ | Traverses $n$ steps to last node + up to $n$ steps to find `val` |

---

## 9. Space Complexity

- **Auxiliary Space**: $O(1)$ for `Dect_cycle()`, `remove_cycle()`, `make_cycle()`, and `cos_cycle(val)`—only 2 or 3 `Node*` pointers (`slow`, `fast`, `temp`) are used regardless of how large $n$ is.

---

## 10. Important Properties and Observations

1. **Why Does `fast` Move 2 Steps Instead of 3 or 4 Steps?**
   If `fast` moved 3 steps per iteration (`v_rel = 2`), and the gap between `fast` and `slow` was an odd number in an even-length cycle, `fast` could jump right over `slow` repeatedly, Or take extra laps. Moving 2 steps (`v_rel = 1`) guarantees the gap decreases by 1 at every step and minimizes total pointer hops.
2. **Finding the Length of the Cycle ($C$)**:
   Once `slow == fast` at the meeting point, keep `slow` fixed and advance `temp = slow->next` one step at a time while counting steps until `temp == slow`. That count is the exact cycle length $C$.

---

## 11. Advantages and Disadvantages

### Advantages of Floyd's Algorithm vs. Hashing (`unordered_set<Node*>`)
- Uses **$O(1)$ space** instead of $O(n)$ hash table memory.
- No dynamic memory allocation or pointer hashing overhead.

### Disadvantages
- Slightly more pointer dereferences than a single traversal if the cycle is entered after a long stem.

---

## 12. Comparison with Related Concepts

| Method | Time Complexity | Auxiliary Space | Modifies Node Structure? |
| :--- | :---: | :---: | :---: |
| **Floyd's Tortoise & Hare (`Dect_cycle`)** | $O(n)$ | **$O(1)$** | No |
| **Hash Set of Visited `Node*` Addresses** | $O(n)$ | $O(n)$ | No |
| **Adding `bool visited` Field to `Node`** | $O(n)$ | $O(1)$ per call ($O(n)$ in struct) | Yes (requires altering `Node` class) |

---

## 13. Common Mistakes

1. **Using `||` Instead of `&&` in `while (fast != NULL && fast->next != NULL)`**:
   Always use `&&` so `fast->next` is never evaluated when `fast == NULL`.
2. **Checking `if (slow == fast)` Before Moving the Pointers**:
   Since both `slow` and `fast` start at `head`, checking `if (slow == fast)` at the top of the `while` loop before advancing them will falsely report a cycle on step 0! Your code correctly advances `slow` and `fast` first and checks `if (slow == fast)` afterward.

---

## 14. Applications

1. **Memory Corruption & Infinite Loop Prevention** in linked data structures.
2. **Find the Duplicate Number in an Array of $n+1$ Integers in $[1..n]$ (LeetCode 287)** in $O(n)$ time and $O(1)$ space by treating array values as `next` indices (`slow = nums[slow]`).
3. **Happy Number Detection** and **Pollard's Rho Algorithm** for integer factorization and cryptographic hash collision detection.

---

## 15. Practice Questions

1. **Basic Understanding**: Why is it impossible for `fast` (moving 2 steps) to skip over `slow` (moving 1 step) inside a cycle without landing on the same node?
2. **Implementation**: Write a function `int cycle_length()` that returns the exact number of nodes inside the cycle (or `0` if no cycle exists) in $O(n)$ time and $O(1)$ space.
3. **Dry-Run Problem**: Suppose a list has 8 nodes `1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8` and `8->next` points back to `4`. Trace the exact node values of `slow` and `fast` at each iteration until they meet, then trace Phase 2 to verify they meet at `4`.
4. **Complexity Analysis**: Prove that in Phase 1 of Floyd's algorithm, `slow` takes at most $L + C \le n$ steps before meeting `fast`.
5. **Interview Question**: How can you use Floyd's Cycle Detection algorithm on an read-only array `nums` of length $n + 1$ containing integers in the range $[1, n]$ to find the duplicate number in $O(n)$ time and $O(1)$ extra space?

---

## 16. Quick Revision

- **Loop Condition**: `while (fast != NULL && fast->next != NULL)`
- **Step Sizes**: `slow = slow->next;` (1 step), `fast = fast->next->next;` (2 steps).
- **Cycle Start Formula**: $L + x = k \cdot C \implies L = (k - 1)C + (C - x)$. Reset `slow = head`, move both 1 step at a time until `slow == fast`.
- **Complexity**: $O(n)$ time, $O(1)$ auxiliary space.
