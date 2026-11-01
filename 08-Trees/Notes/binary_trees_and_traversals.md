# Binary Trees: Representations, Traversals, Structural Metrics & LCA

## Related Implementation

- `../Binary_Tree_01.cpp` *(Original pointer-based Binary Tree implementation)*
- `../Binary_Tree_01_Detailed.cpp` *(Original detailed commented Binary Tree implementation)*
- `../Binary_Tree_Array.cpp` *(Original array-based Binary Tree implementation)*
- `../Binary_Tree_Diameter_and_LCA.cpp` *(Supplementary implementation created for this folder)*

---

## 1. Concept Introduction

### What is the Concept?
A **Binary Tree** is a non-linear, hierarchical data structure in which each node contains a data value and has **at most two children**, referred to as the **left child** and the **right child**.

### Why is it Required?
Linear data structures (arrays, linked lists, stacks, queues) store one-dimensional sequences. Binary Trees represent hierarchical relationships, expression syntax trees, file systems, and decision trees, and serve as the foundation for **Binary Search Trees (`BST_01.cpp`)** and **Binary Heaps (`Binary_Heap.cpp`)**.

### How is it Implemented in Your Folder `08-Trees`?
You implemented **both** representations of a Binary Tree:
1. **Pointer-Based Dynamic Representation (`Binary_Tree_01.cpp` & `Binary_Tree_01_Detailed.cpp`)**: Each `Node` object on the heap has `Node *left`, `Node *right`, and `int data`. Constructed recursively from a preorder array using `-1` as a `NULL` marker.
2. **Array-Based Contiguous Representation (`Binary_Tree_Array.cpp`)**: Stores nodes in level order inside `int arr[100]` and computes parent/child relationships using index arithmetic (`left_child = 2 * index + 1`, `right_child = 2 * index + 2`).

---

## 2. Fundamental Theory

### Essential Binary Tree Terminology
- **Root**: The topmost node of the tree (has no parent).
- **Parent & Child**: If node $u$ has a link to node $v$ below it, $u$ is the parent of $v$, and $v$ is the left or right child of $u$.
- **Leaf Node (External Node)**: A node with **zero children** (`root->left == NULL && root->right == NULL`).
- **Internal Node (Non-Leaf Node)**: A node with **at least one child** (`root->left != NULL || root->right != NULL`).
- **Depth of a Node**: Number of edges on the unique path from the **root** down to that node (Root has depth $0$).
- **Height of a Tree**:
  - **Node-count convention** *(used in your `Height_Node(root)` in `Binary_Tree_01.cpp` and `Height_BST(root)` in `BST_01.cpp`)*: Number of **nodes** on the longest root-to-leaf path (`NULL` returns `0`; a single-node tree has height `1`).
  - **Edge-count convention** *(used in `Recursive_Time_Complexity_Binary_Trees.cpp` line 40)*: Number of **edges** on the longest root-to-leaf path (`NULL` returns `-1`; a single-node tree has height `0`).
- **Strict (Full / Proper) Binary Tree** *(implemented in `is_Strict_BT` in `BST_01.cpp`)*: Every node in the tree has **either $0$ or $2$ children** (never $1$ child).
- **Complete Binary Tree** *(used in `Binary_Tree_Array.cpp` and `Binary_Heap.cpp`)*: Every level is completely filled except possibly the last level, and all nodes in the last level are packed as far **left** as possible.
- **Perfect Binary Tree**: All internal nodes have $2$ children and all leaf nodes are at the exact same level.

---

## 3. Mathematical Representation

### Fundamental Binary Tree Theorems (Important for Examinations!)
1. **Maximum Nodes at Level $l$** (where Root is at level $l = 0$):
   $$N_{\max}(\text{level } l) = 2^l$$
2. **Maximum Total Nodes in a Binary Tree of Node-Height $H$** ($H \ge 1$ levels):
   $$N_{\max} = 2^0 + 2^1 + \dots + 2^{H-1} = 2^H - 1$$
3. **Minimum Height of a Binary Tree with $n$ Nodes**:
   $$H_{\min} = \lfloor \log_2 n \rfloor + 1 \text{ (in nodes)} \quad \text{or} \quad \lfloor \log_2 n \rfloor \text{ (in edges)}$$
4. **Full (Strict) Binary Tree Leaf-to-Internal Node Theorem**:
   In any non-empty Strict (Full) Binary Tree where every node has $0$ or $2$ children, the number of leaf nodes ($L$) and the number of internal nodes with 2 children ($I_2$) always satisfy:
   $$L = I_2 + 1$$
5. **Array Representation Index Formulas (Zero-Based, `Binary_Tree_Array.cpp`)**:
   For a node at index $i$ ($0 \le i < \text{size}$):
   $$\text{Parent}(i) = \left\lfloor \frac{i - 1}{2} \right\rfloor \quad (i > 0)$$
   $$\text{LeftChild}(i) = 2i + 1, \qquad \text{RightChild}(i) = 2i + 2$$

---

## 4. Working Mechanism

### 1. Preorder Tree Construction (`build_tree(vector<int> &Nodes)` in `Binary_Tree_01.cpp`)
Given `arr = {50, 30, -1, -1, 70, 60, -1, -1, 80, -1, -1}` and `static int idx = -1;`:
1. Increment `idx++`.
2. If `Nodes[idx] == -1`, return `NULL` (base case: empty child).
3. Allocate `Node *n1 = new Node(Nodes[idx]);`.
4. Recursively build left subtree: `n1->left = build_tree(Nodes);`.
5. Recursively build right subtree: `n1->right = build_tree(Nodes);`.
6. Return `n1`.

### 2. The Four Standard Tree Traversals (`Binary_Tree_01.cpp`)
- **Depth-First Search (DFS) Traversals (Recursive)**:
  1. **`Preorder(root)`** (**Root $\to$ Left $\to$ Right**): Visits `root->data` *before* subtrees.
  2. **`Inorder(root)`** (**Left $\to$ Root $\to$ Right**): Visits `root->data` *between* subtrees.
  3. **`Postorder(root)`** (**Left $\to$ Right $\to$ Root**): Visits `root->data` *after* subtrees.
- **Breadth-First Search (BFS) Traversals (Iterative with `std::queue<Node*>`)**:
  4. **`Level_Order(root)`**: Pushes `root` to `q`. While `!q.empty()`, pops `curr`, prints `curr->data`, and pushes `curr->left` and `curr->right` if non-`NULL`.
  5. **`level_Wise_Traversal(root)`**: Pushes `root` followed by a `NULL` level-delimiter marker into `q`. Whenever `curr == NULL` is popped, prints `endl` (a newline) and, if `!q.empty()`, pushes a new `NULL` marker for the end of the next level!

---

## 5. Visual Representation

### 1. Tree Constructed in `Binary_Tree_01.cpp` (`{50, 30, -1, -1, 70, 60, -1, -1, 80, -1, -1}`)
```
                 50              <-- Level 0 (Root)
               /    \
             30      70          <-- Level 1
            /  \    /  \
          -1   -1  60   80       <-- Level 2
                  / \   / \
                -1  -1 -1  -1

Traversals of this Tree:
- Preorder   (Root -> Left -> Right): 50 30 70 60 80
- Inorder    (Left -> Root -> Right): 30 50 60 70 80
- Postorder  (Left -> Right -> Root): 30 60 80 70 50
- Level Order (BFS):                  50 30 70 60 80
- Level Wise:
  50
  30 70
  60 80
```

### 2. Array-Based Tree in `Binary_Tree_Array.cpp` (`{10, 20, 30, 40, 50, 60, 70}`)
```
Tree View:                               Array View (arr[0..6]):
                 10 (idx 0)              Idx:  0   1   2   3   4   5   6
               /            \                 +---+---+---+---+---+---+---+
         20 (idx 1)       30 (idx 2)          |10 |20 |30 |40 |50 |60 |70 |
         /       \         /       \          +---+---+---+---+---+---+---+
    40(idx 3) 50(idx 4) 60(idx 5) 70(idx 6)
```

---

## 6. C++ Implementation & Code Review

### Comparison of `Binary_Tree_01.cpp` and `Binary_Tree_01_Detailed.cpp`
- Both files implement `build_tree`, `Inorder`, `Preorder`, `Postorder`, `Level_Order`, `level_Wise_Traversal`, `Height_Node`, `Node_count`, `sum_Nodes`, `search_BST`, `search`, and `check_BST`.
- **Difference in `check_BST`**:
  - In `../Binary_Tree_01.cpp` (lines 282–288), `check_BST(Node* root)` was left as a stub (`if(root == NULL) return false;`, with no return statement for non-NULL `root`).
  - In `../Binary_Tree_01_Detailed.cpp` (lines 514–544), you completed `check_BST(Node* root, long long minVal = LLONG_MIN, long long maxVal = LLONG_MAX)` using the range-validation method `(minVal, maxVal)` in $O(n)$ time!
- **Supplementary File `../Binary_Tree_Diameter_and_LCA.cpp`**:
  - Adds **`Diameter_BT(Node* root)`**: Computes the longest path between any two nodes in $O(n)$ time by updating `max_diameter = max(max_diameter, left_h + right_h)` during a single bottom-up height calculation.
  - Adds **`is_Balanced_BT(Node* root)`**: Checks whether $|h_{\text{left}} - h_{\text{right}}| \le 1$ for every node in $O(n)$ time using `-1` as an early-unbalanced signal.
  - Adds **`LCA_BST(Node* root, int n1, int n2)`**: Finds the Lowest Common Ancestor in $O(h)$ time.
  - Adds **`IS_STRICT_BST(Node* root)`**: Completes the strict BST validator from `BST_01.cpp`.

---

## 7. Dry Runs

### Dry Run of `level_Wise_Traversal(root)` on `{50, 30, 70, 60, 80}`
| Step | Popped `curr` | Queue State `q` (Front $\to$ Back) | Console Output |
| :---: | :---: | :--- | :--- |
| Init | — | `[50, NULL]` | — |
| 1 | `50` | `[NULL, 30, 70]` | `50 ` |
| 2 | `NULL` | `[30, 70, NULL]` | `\n` (Newline after Level 0) |
| 3 | `30` | `[70, NULL]` (`30` has no children) | `30 ` |
| 4 | `70` | `[NULL, 60, 80]` | `70 ` |
| 5 | `NULL` | `[60, 80, NULL]` | `\n` (Newline after Level 1) |
| 6 | `60` | `[80, NULL]` | `60 ` |
| 7 | `80` | `[NULL]` | `80 ` |
| 8 | `NULL` | `[]` (`q.empty()` is true $\to$ `break`) | `\n` (Newline after Level 2) |

---

## 8. Time Complexity

| Function | Recurrence | Time Complexity | Why? |
| :--- | :--- | :---: | :--- |
| `build_tree(Nodes)` | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ | Processes each element of the preorder array once |
| `Inorder` / `Preorder` / `Postorder` | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ | Visits each of the $n$ nodes exactly once |
| `Level_Order` / `level_Wise_Traversal` | — | $O(n)$ | Enqueues and dequeues each node once |
| `Height_Node` / `Node_count` / `sum_Nodes` | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ | Combines left and right results in $O(1)$ per node |
| `search(root, target)` (General BT) | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ worst, $O(1)$ best | Must check both subtrees if not found on left |
| `Diameter_BT` / `is_Balanced_BT` | $T(n) = T(n_L) + T(n_R) + c$ | $O(n)$ | Single bottom-up postorder pass |

---

## 9. Space Complexity

- **Recursive DFS Functions (`Inorder`, `Preorder`, `Postorder`, `Height_Node`, `Node_count`, `sum_Nodes`, `search`)**:
  - **Auxiliary Call Stack Space**: $O(h)$, where $h$ is the height of the tree.
  - **Balanced Tree**: $h = O(\log n)$.
  - **Skewed Tree (Worst Case)**: $h = O(n)$.
- **Iterative BFS Functions (`Level_Order`, `level_Wise_Traversal`)**:
  - **Auxiliary Queue Space**: $O(w)$, where $w$ is the maximum width of the tree (in a perfect binary tree, the last level has $\lceil n/2 \rceil$ nodes, so worst-case queue space is $O(n)$).

---

## 10. Important Properties and Observations

1. **Uniquely Reconstructing a Binary Tree from Traversals**:
   - **Preorder + Inorder** or **Postorder + Inorder** uniquely determines any Binary Tree! (InPre or InPost).
   - **Preorder + Postorder** alone **cannot** uniquely reconstruct a general binary tree (unless the tree is known to be Strict/Full, or `NULL` markers `-1` are included as in `build_tree`!).
2. **Why `Diameter_BT` Uses a Single Pass Instead of Calling `Height_Node` at Every Node**:
   As explained in your `Recursive_Time_Complexity_Binary_Trees.cpp` (Pattern 11, lines 162–181), recalculating `Height_Node(root)` separately at every node takes $O(n^2)$ time on a skewed tree and $O(n \log n)$ on a balanced tree. Computing height and updating `max_diameter` simultaneously bottom-up reduces the time complexity to **$O(n)$**!

---

## 11. Advantages and Disadvantages

### Pointer-Based Binary Tree (`Binary_Tree_01.cpp`) vs. Array-Based Binary Tree (`Binary_Tree_Array.cpp`)
- **Pointer-Based**: Works efficiently for any tree shape (even skewed trees) without wasting memory on missing nodes, but uses 2 pointers (`16` bytes) per node.
- **Array-Based**: Zero pointer overhead and $O(1)$ parent/child navigation via `2*i + 1` and `2*i + 2`, making it ideal for **Complete Binary Trees and Binary Heaps (`Binary_Heap.cpp`)**, but wastes $O(2^h)$ array slots if used on a sparse or skewed tree.

---

## 12. Comparison with Related Concepts

### DFS (`Inorder`/`Preorder`/`Postorder`) vs. BFS (`Level_Order`)

| Feature | DFS Traversals | BFS (`Level_Order`) |
| :--- | :--- | :--- |
| **Underlying Data Structure** | Call Stack (LIFO) | `std::queue<Node*>` (FIFO) |
| **Time Complexity** | $O(n)$ | $O(n)$ |
| **Auxiliary Space** | $O(h)$ (Max depth) | $O(w)$ (Max level width) |
| **Space on Balanced Tree** | $O(\log n)$ | $O(n)$ (last level has $\approx n/2$ nodes) |
| **Space on Skewed Tree** | $O(n)$ | **$O(1)$** ($1$ node per level) |

---

## 13. Common Mistakes

1. **Forgetting to Reset `static int idx = -1;` Before Calling `build_tree` a Second Time**:
   Because `idx` is `static`, building a second tree without resetting `idx = -1;` (as noted in `Binary_Tree_01_Detailed.cpp` line 560) reads past the end of the vector!
2. **Pushing `NULL` endlessly in `level_Wise_Traversal`**:
   When `curr == NULL` is popped in `level_Wise_Traversal` (line 163), you **must** check `if (q.empty()) break;` **before** pushing the next `NULL` marker. Otherwise, an empty queue will push and pop `NULL` in an infinite loop! Your implementation in `Binary_Tree_01.cpp` (lines 168–174) handles this accurately.

---

## 14. Applications

- **Abstract Syntax Trees (AST)** in compilers (Postorder evaluates expressions; Inorder reconstructs infix expressions).
- **File System Directories** and **HTML/XML DOM Trees**.
- **Huffman Coding Trees** for lossless data compression.

---

## 15. Practice Questions

1. **Basic Understanding**: A Strict (Full) Binary Tree has $15$ internal nodes (each having $2$ children). Without drawing the tree, how many leaf nodes and how many total nodes does it have?
2. **Implementation**: Write a function `bool is_identical(Node* r1, Node* r2)` that returns `true` if two binary trees have the exact same structure and node values.
3. **Dry-Run Problem**: Given **Inorder** = `[40, 20, 50, 10, 60, 30, 70]` and **Preorder** = `[10, 20, 40, 50, 30, 60, 70]`, reconstruct the Binary Tree and write its **Postorder** traversal.
4. **Complexity Analysis**: Compare the auxiliary memory used by `Inorder(root)` vs. `Level_Order(root)` on (a) a Perfect Binary Tree of $1023$ nodes, and (b) a Right-Skewed Binary Tree of $1023$ nodes.
5. **Interview Question**: How do you find the **Lowest Common Ancestor (LCA)** of two nodes `p` and `q` in a **General Binary Tree** (not necessarily a BST) in a single $O(n)$ recursive traversal?

---

## 16. Quick Revision

- **Preorder**: Root $\to$ Left $\to$ Right
- **Inorder**: Left $\to$ Root $\to$ Right *(Sorted for a BST!)*
- **Postorder**: Left $\to$ Right $\to$ Root *(Bottom-up: Height, Node count, Sum, Diameter, Delete tree)*
- **Level Order**: Queue-based BFS ($O(n)$ time, $O(w)$ space).
- **Array Child Indices (0-based)**: $\text{Left} = 2i + 1$, $\text{Right} = 2i + 2$, $\text{Parent} = (i - 1) / 2$.
