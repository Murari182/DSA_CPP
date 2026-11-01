# Singly Linked List: Operations, Reversal, Merging & Element-Wise Sum

## Related Implementation

- `../linked_list-01.cpp` *(Original implementation: core operations + `reverse`)*
- `../Linked_List-02.cpp` *(Original implementation: core operations + `remove_cycle`, `Merge_SL`, `sum`)*

---

## 1. Concept Introduction

### What is the Concept?
A **Singly Linked List** is a dynamic, linear data structure composed of heap-allocated **nodes**, where each `Node` stores:
1. `int data` — the payload value.
2. `Node* next` — a pointer storing the memory address of the next node in the sequence (or `NULL` if it is the last node).

The `list` container class maintains two pointers:
- `Node* head` — points to the first node in the list (`NULL` when empty).
- `Node* tail` — points to the last node in the list (`NULL` when empty).

### Why is it Required?
Static arrays (`int arr[100]`) have a fixed capacity and require $O(n)$ element shifts when inserting or deleting at the front or middle. A Singly Linked List allocates nodes on demand from the heap and performs insertion at the front (`push_front`) or back (`pushb_back` with a `tail` pointer) in **$O(1)$ time** without shifting any elements.

---

## 2. Fundamental Theory

### Structural Invariants of Your `list` Class (`linked_list-01.cpp` & `Linked_List-02.cpp`)
1. **Empty List State**: `head == NULL` and `tail == NULL`.
2. **Single-Node List State**: `head == tail`, `head != NULL`, and `head->next == NULL`.
3. **Multi-Node List State**: Starting from `head` and following `next` pointers reaches `tail` after $n - 1$ hops, and `tail->next == NULL`.

---

## 3. Mathematical Representation

### Position Indexing from the End (`del_last(int pos)`)
In your `del_last(int pos)` implementation, `pos` is 0-indexed from the **end** of a list of `count` nodes:
- `pos = 0` refers to the last node (`tail`), which is at 0-based index $\text{count} - 1$ from the front.
- `pos = count - 1` refers to the first node (`head`), which is at 0-based index $0$ from the front.
- General conversion formula from 0-based end-position `pos` to 0-based front-index `idx_front`:
  $$\text{idx\_front} = \text{count} - 1 - \text{pos}$$
- The predecessor node `prev` (the node immediately before the target node) sits at 0-based front-index:
  $$\text{idx\_prev} = \text{count} - \text{pos} - 2$$
  which is why your loop runs `for(int i = 0; i < count - pos - 2; i++) prev = prev->next;`!

---

## 4. Working Mechanism

### 1. `push_front(int val)`
1. Allocate `Node* n1 = new Node(val)`.
2. If `head == NULL`, set both `head = n1` and `tail = n1`.
3. Otherwise, link `n1->next = head` and update `head = n1`.

### 2. `pushb_back(int val)`
1. Allocate `Node* n1 = new Node(val)`.
2. If `head == NULL`, set both `head = n1` and `tail = n1`.
3. Otherwise, attach `tail->next = n1` and advance `tail = n1`.

### 3. `insert(int val, int pos)` (0-Indexed Position from Front)
1. If `pos == 0`, delegate to `push_front(val)` and return.
2. Traverse `temp` from `head` for `pos - 1` steps (`for (int i = 0; i < pos - 1 && temp != NULL; i++)`) to reach the predecessor at index `pos - 1`.
3. If `temp == NULL`, `pos` is out of bounds: print `"Invalid position"`, `delete n1` (preventing a memory leak!), and return.
4. Wire `n1->next = temp->next` first, then `temp->next = n1`.
5. If `n1->next == NULL` (inserted at the end), update `tail = n1`.

### 4. Iterative List Reversal (`reverse()` in `linked_list-01.cpp`)
Uses the classic **Three-Pointer Technique** (`prev`, `curr`, `next`):
1. Initialize `prev = NULL`, `curr = head`.
2. While `curr != NULL`:
   - Save the rest of the list: `next = curr->next;`
   - Reverse the current link: `curr->next = prev;`
   - Advance `prev` forward: `prev = curr;`
   - Advance `curr` forward: `curr = next;`
3. Finally, set `head = prev;`.

---

## 5. Visual Representation

### 1. Inserting Node `25` at `pos = 2` (`insert(25, 2)`)
```
Before:
head (pos 0)     temp (pos 1)      pos 2
+----+----+      +----+----+      +----+----+
| 10 |  --|----->| 20 |  --|----->| 30 |NULL|
+----+----+      +----+----+      +----+----+

Step 1: n1->next = temp->next;
Step 2: temp->next = n1;

After:
+----+----+      +----+----+      +----+----+      +----+----+
| 10 |  --|----->| 20 |  --|----->| 25 |  --|----->| 30 |NULL|
+----+----+      +----+----+      +----+----+      +----+----+
```

### 2. Three-Pointer Reversal (`reverse()` in `linked_list-01.cpp`)
```
Initial:
prev = NULL     curr = [10] ---> [20] ---> [30] ---> NULL

Iteration 1:
                next = [20]
NULL <--- [10]  [20] ---> [30] ---> NULL
          prev  curr

Iteration 2:
                          next = [30]
NULL <--- [10] <--- [20]  [30] ---> NULL
                    prev  curr

Iteration 3:
                                    next = NULL
NULL <--- [10] <--- [20] <--- [30]  NULL
                              prev  curr
Final: head = prev ([30])
```

---

## 6. C++ Implementation & Code Review (`linked_list-01.cpp` & `Linked_List-02.cpp`)

### Difference Between `linked_list-01.cpp` and `Linked_List-02.cpp`
- Both files share the identical base `Node` and `list` class (`push_front`, `pushb_back`, `print`, `insert`, `delete_all`, `del_last`, `Dect_cycle`, `make_cycle`, `cos_cycle`).
- **`linked_list-01.cpp`** adds `reverse()` (lines 256–271) and demonstrates reversing `10-->20-->...-->100-->NULL` into `100-->90-->...-->10-->NULL`.
- **`Linked_List-02.cpp`** adds `remove_cycle()` (lines 256–282), `Merge_SL(list &l1, list &l2)` (lines 284–306), and `sum(list &l1, list &l2)` (lines 308–335).

### Important Code Review Observations & Edge Cases in Original Code
*(Documented here without modifying your original source files)*

1. **`Merge_SL(list &l1, list &l2)` in `Linked_List-02.cpp` (Lines 284–306) — Missing Remaining Elements**:
   - **What happens**: `Merge_SL` has the loop `while(temp1 != NULL && temp2 != NULL)` which compares `temp1->data <= temp2->data` and calls `pushb_back`. However, as soon as `temp1` reaches `NULL` (after `40` is merged from `l1 = {10, 20, 30, 40}`), the `while` loop terminates while `temp2` still points to `50` in `l2 = {15, 25, 35, 50}`!
   - **Actual Output in `Linked_List-02.cpp`**: `10-->15-->20-->25-->30-->35-->40-->NULL` (`50` is missing).
   - **Conceptual Fix**: Just like you wrote in `sum(list &l1, list &l2)` (lines 322–334), add two cleanup loops after the main `while` loop:
     ```cpp
     while (temp1 != NULL) {
         pushb_back(temp1->data);
         temp1 = temp1->next;
     }
     while (temp2 != NULL) {
         pushb_back(temp2->data);
         temp2 = temp2->next;
     }
     ```
2. **Reusing `l3` in `main()` of `Linked_List-02.cpp` (Lines 380–389)**:
   - In `main()`, `l3.Merge_SL(l1, l2)` appends the merged elements into `l3`, and then `l3.sum(l1, l2)` is called on the **same** `l3` object without calling `l3.delete_all()` first. As a result, `l3.sum(l1, l2)` appends the element-wise sums `25-->45-->65-->90` onto the end of the already-populated `l3`.
3. **`tail` Pointer After `reverse()` in `linked_list-01.cpp` (Lines 256–271)**:
   - `reverse()` updates `head = prev;`, so traversal from `head` works properly. However, `tail` is not updated to point to the old `head` (the new last node). If `pushb_back` is called after `reverse()`, `tail` would still point to the old last node (now the new `head`). Setting `tail = head;` at the start of `reverse()` before `head = prev;` keeps `tail` accurate.

---

## 7. Dry Runs

### Dry Run 1: `reverse()` on `10 --> 20 --> 30 --> NULL`
| Step | `prev` | `curr` | `next` | Rewired Link | List State |
| :---: | :---: | :---: | :---: | :--- | :--- |
| Init | `NULL` | `10` | — | — | `10 -> 20 -> 30 -> NULL` |
| Iter 1 | `10` | `20` | `20` | `10->next = NULL` | `NULL <- 10`, `20 -> 30 -> NULL` |
| Iter 2 | `20` | `30` | `30` | `20->next = 10` | `NULL <- 10 <- 20`, `30 -> NULL` |
| Iter 3 | `30` | `NULL` | `NULL` | `30->next = 20` | `NULL <- 10 <- 20 <- 30` |
| End | `30` | `NULL` | `NULL` | `head = prev` (`30`) | `30 -> 20 -> 10 -> NULL` |

### Dry Run 2: `Merge_SL(l1, l2)` and `sum(l1, l2)` on `l1 = {10, 20, 30, 40}`, `l2 = {15, 25, 35, 50}`
| Step | `temp1->data` | `temp2->data` | Comparison | Appended to `l3` (`Merge_SL`) | Element-Wise `sum(l1, l2)` |
| :---: | :---: | :---: | :---: | :--- | :--- |
| 1 | `10` | `15` | `10 <= 15` | `10` (`temp1` advances to `20`) | `10 + 15 = 25` |
| 2 | `20` | `15` | `20 > 15` | `15` (`temp2` advances to `25`) | `20 + 25 = 45` |
| 3 | `20` | `25` | `20 <= 25` | `20` (`temp1` advances to `30`) | `30 + 35 = 65` |
| 4 | `30` | `25` | `30 > 25` | `25` (`temp2` advances to `35`) | `40 + 50 = 90` |
| 5 | `30` | `35` | `30 <= 35` | `30` (`temp1` advances to `40`) | — |
| 6 | `40` | `35` | `40 > 35` | `35` (`temp2` advances to `50`) | — |
| 7 | `40` | `50` | `40 <= 50` | `40` (`temp1` becomes `NULL`) | — |

---

## 8. Time Complexity

| Function | Best Case | Average Case | Worst Case | Why? |
| :--- | :---: | :---: | :---: | :--- |
| `push_front(val)` | $O(1)$ | $O(1)$ | $O(1)$ | Direct pointer manipulation at `head` |
| `pushb_back(val)` | $O(1)$ | $O(1)$ | $O(1)$ | Direct pointer manipulation using `tail` pointer |
| `insert(val, pos)` | $O(1)$ (`pos=0`) | $O(n)$ | $O(n)$ | Traverses `pos - 1` nodes from `head` |
| `del_last(pos)` | $O(n)$ | $O(n)$ | $O(n)$ | Counts all $n$ nodes first, then traverses $n - \text{pos} - 2$ nodes |
| `delete_all()` | $O(n)$ | $O(n)$ | $O(n)$ | Visits and frees each of the $n$ nodes once |
| `reverse()` | $O(n)$ | $O(n)$ | $O(n)$ | Single pass over all $n$ nodes |
| `Merge_SL(l1, l2)` | $O(n + m)$ | $O(n + m)$ | $O(n + m)$ | Advances either `temp1` or `temp2` at every step |
| `sum(l1, l2)` | $O(n + m)$ | $O(n + m)$ | $O(n + m)$ | Single simultaneous pass over both lists |

---

## 9. Space Complexity

- **`reverse()`**: $O(1)$ auxiliary space (reverses links in-place using 3 pointers: `curr`, `prev`, `next`).
- **`del_last(pos)` / `insert(val, pos)`**: $O(1)$ auxiliary space.
- **`Merge_SL` / `sum`**: $O(n + m)$ new nodes allocated via `pushb_back` in `l3` (note: in-place merge without allocating new nodes can be done in $O(1)$ auxiliary space).

---

## 10. Important Properties and Observations

1. **Why Maintaining a `tail` Pointer Matters**:
   Without `Node* tail`, inserting at the end (`pushb_back`) requires traversing from `head` to the last node in $O(n)$ time. By maintaining `tail`, your `list` class achieves $O(1)$ insertion at both ends!
2. **One-Pass $n$-th Node from End (Two-Pointer Trick)**:
   In `del_last(int pos)`, your code uses a clean two-pass approach (Pass 1 counts `count`, Pass 2 walks `count - pos - 2` steps). In interviews, you can also do this in a **single pass** by advancing a `fast` pointer `pos + 1` steps ahead of `slow`, then moving both `slow` and `fast` one step at a time until `fast->next == NULL`.

---

## 11. Advantages and Disadvantages

### Advantages
- Dynamic size without reallocation or copying.
- $O(1)$ `push_front` and $O(1)$ `pushb_back` (with `tail`).

### Disadvantages
- No $O(1)$ random access; cannot move backward from a node (`prev` pointer is absent).
- Extra memory for the `next` pointer in every node.

---

## 12. Comparison with Related Concepts

| Operation | Singly Linked List (with `tail`) | Dynamic Array (`std::vector`) |
| :--- | :---: | :---: |
| **`push_front`** | $O(1)$ | $O(n)$ |
| **`push_back`** | $O(1)$ | $O(1)$ amortized |
| **Delete Last Node (`tail`)** | $O(n)$ (must find predecessor of `tail`) | $O(1)$ |
| **Access $i$-th Node** | $O(i)$ | $O(1)$ |

*(Notice that even with a `tail` pointer, deleting the last node in a Singly Linked List takes $O(n)$ time because there is no `prev` pointer to step backward from `tail`!)*

---

## 13. Common Mistakes

1. **Losing the Rest of the List During `insert` or `reverse`**:
   In `insert`, always set `n1->next = temp->next;` **before** `temp->next = n1;`. If you set `temp->next = n1;` first, you overwrite the address of the rest of the list!
2. **Forgetting to `delete` Unlinked Nodes**:
   Notice how in `insert` (line 101 of `linked_list-01.cpp`), when `temp == NULL`, you properly wrote `delete n1;` before returning so the unused node does not leak.

---

## 14. Applications

- Implementing Stacks (`05-Stacks/stack_02.cpp`) and Queues (`06-Queues/Queue_01.cpp`).
- Hash table separate chaining collision lists.
- Graph adjacency lists and polynomial arithmetic.

---

## 15. Practice Questions

1. **Basic Understanding**: Why does deleting the `tail` node take $O(n)$ time in a Singly Linked List even when we maintain a `Node* tail` pointer, whereas `pushb_back` takes $O(1)$ time?
2. **Implementation**: Write a recursive function `Node* reverse_recursive(Node* head)` to reverse a singly linked list, and compare its auxiliary space complexity with your iterative `reverse()` in `linked_list-01.cpp`.
3. **Dry-Run Problem**: Trace `del_last(2)` on the list `10 --> 20 --> 30 --> 40 --> 50 --> NULL` (`count = 5`). What value is deleted, and how many times does the `prev` loop execute?
4. **Complexity Analysis**: What is the time complexity of building a list of $n$ elements by calling `pushb_back` $n$ times (a) with a `tail` pointer vs. (b) without a `tail` pointer?
5. **Interview Question**: How can you find the **middle node** of a Singly Linked List in a single pass without counting the total number of nodes first?

---

## 16. Quick Revision

- **`push_front` / `pushb_back`**: $O(1)$ time.
- **`reverse()`**: Uses `prev = NULL`, `curr = head`, `next`; runs in $O(n)$ time and $O(1)$ auxiliary space.
- **`del_last(pos)`**: Deletes the node at 0-based position `pos` from the end (`count - pos - 1` from the front) in $O(n)$ time.
