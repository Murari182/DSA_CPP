/*
BINARY TREE + RECURSIVE TIME COMPLEXITY — C++ STUDY NOTES
=========================================================

This is a comment-based reference file. The snippets are examples for study;
they are not all compiled together because some use the same function names
or assume a Node structure.

Notation:
  n       = number of input items / tree nodes
  nL, nR  = left and right subtree node counts; nL + nR = n - 1
  c       = constant work per call
  h       = tree height

CORE METHOD:
  1. Identify the recursive call(s).
  2. Count work outside recursive calls.
  3. Write T(n).
  4. Expand or solve the recurrence.
  5. State time complexity separately from stack space.

---------------------------------------------------------
PART 1: BINARY TREE FUNCTIONS
---------------------------------------------------------

1) COUNT ALL NODES

int countNodes(Node* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left)
             + countNodes(root->right);
}

Recurrence: T(n) = T(nL) + T(nR) + c
Time:       O(n) — each node is visited once.
Stack:      O(h).

2) HEIGHT OF A TREE

int height(Node* root) {
    if (root == nullptr) return -1;
    int lh = height(root->left);
    int rh = height(root->right);
    return 1 + max(lh, rh);
}

Recurrence: T(n) = T(nL) + T(nR) + c
Time:       O(n).
Stack:      O(h).
Important: a balanced tree's height value is O(log n), but computing
           that height by visiting all nodes takes O(n) time.

3) COUNT LEAF NODES

int countLeafNodes(Node* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    return countLeafNodes(root->left)
         + countLeafNodes(root->right);
}

Recurrence: T(n) = T(nL) + T(nR) + c
Time:       O(n) — internal nodes must be visited too.
Stack:      O(h).

4) COUNT INTERNAL NODES

int countInternalNodes(Node* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 0;
    return 1 + countInternalNodes(root->left)
             + countInternalNodes(root->right);
}

Recurrence: T(n) = T(nL) + T(nR) + c
Time:       O(n)
Stack:      O(h)

5) PREORDER / INORDER / POSTORDER TRAVERSAL

void preorder(Node* root) {
    if (root == nullptr) return;
    cout << root->data << ' ';
    preorder(root->left);
    preorder(root->right);
}

Recurrence: T(n) = T(nL) + T(nR) + c
Time:       O(n), because each node is processed once.
Stack:      O(h). Inorder and postorder have the same bounds.

6) SEARCH IN AN ORDINARY BINARY TREE

bool searchBT(Node* root, int key) {
    if (root == nullptr) return false;
    if (root->data == key) return true;
    if (searchBT(root->left, key)) return true;
    return searchBT(root->right, key);
}

Worst-case recurrence (key absent):
  T(n) = T(nL) + T(nR) + c
Worst-case time: O(n)
Best case:       O(1), if root matches.
Stack:           O(h)

7) VALIDATE BST USING BOUNDS

bool isBST(Node* root, long long low, long long high) {
    if (root == nullptr) return true;
    if (root->data <= low || root->data >= high) return false;
    return isBST(root->left, low, root->data) &&
           isBST(root->right, root->data, high);
}

Worst-case recurrence: T(n) = T(nL) + T(nR) + c
Worst-case time: O(n). Early return can reduce some executions.

8) CHECK WHETHER A TREE IS FULL
A full binary tree has either zero or two children at each node.

bool isFull(Node* root) {
    if (root == nullptr) return true;
    if (root->left == nullptr && root->right == nullptr) return true;
    if (root->left != nullptr && root->right != nullptr)
        return isFull(root->left) && isFull(root->right);
    return false;
}

Worst-case recurrence: T(n) = T(nL) + T(nR) + c
Worst-case time: O(n).

9) SEARCH IN A BST

bool searchBST(Node* root, int key) {
    if (root == nullptr) return false;
    if (root->data == key) return true;
    if (key < root->data)
        return searchBST(root->left, key);
    return searchBST(root->right, key);
}

Recurrence in terms of height: T(h) = T(h - 1) + c
Time: O(h)
Balanced BST: O(log n)
Worst-case skewed BST: O(n)
Do not say O(log n) for every BST; it must be balanced.

10) ARRAY-REPRESENTED COMPLETE BINARY TREE TRAVERSAL

void preorderArray(const int arr[], int n, int i) {
    if (i >= n) return;
    cout << arr[i] << ' ';
    preorderArray(arr, n, 2 * i + 1);
    preorderArray(arr, n, 2 * i + 2);
}

Assumption: the complete tree is densely stored at indices 0 ... n-1.
Recurrence: T(n) = T(nL) + T(nR) + c
Time: O(n), because each valid node is visited once.

11) RECALCULATE SUBTREE HEIGHT AT EVERY NODE

int height(Node* root) {
    if (root == nullptr) return -1;
    return 1 + max(height(root->left), height(root->right));
}

int sumSubtreeHeights(Node* root) {
    if (root == nullptr) return 0;
    int h = height(root);
    return h + sumSubtreeHeights(root->left)
             + sumSubtreeHeights(root->right);
}

Skewed-tree recurrence: T(n) = T(n - 1) + c*n
Expansion: T(n) = c*n + c*(n-1) + ... + c
          = c*n*(n+1)/2
Worst-case time: O(n^2).
For a balanced tree, this implementation is O(n log n).
Better approach: calculate information bottom-up once per node => O(n).

---------------------------------------------------------
PART 2: GENERAL RECURSIVE PATTERNS
---------------------------------------------------------

12) ONE CALL ON n-1, CONSTANT WORK

void f(int n) {
    if (n <= 0) return;
    f(n - 1);
}

T(n) = T(n - 1) + c
      = T(n - 2) + 2c
      = T(n - k) + kc
Stop at k = n.
Time: O(n).

13) ONE CALL ON n-1, LOOP OF SIZE n

void f(int n) {
    if (n <= 0) return;
    for (int i = 0; i < n; ++i) { /* constant work */ }
    f(n - 1);
}
*/


T(n) = T(n - 1) + c*n
      = c*n + c*(n-1) + ... + c
      = c*n*(n+1)/2
Time: O(n^2).

14) ONE CALL ON n/2, CONSTANT WORK

void f(int n) {
    if (n <= 1) return;
    f(n / 2);
}

T(n) = T(n/2) + c
Stop when n / 2^k <= 1 => k = Theta(log n).
Time: O(log n).

15) TWO CALLS ON n/2, CONSTANT WORK

void f(int n) {
    if (n <= 1) return;
    f(n / 2);
    f(n / 2);
}

T(n) = 2T(n/2) + c
Depth is log n, but calls double by level: 1, 2, 4, ..., n.
Total calls are proportional to n.
Time: O(n).

16) TWO CALLS ON n/2, LINEAR LOOP

void f(int n) {
    if (n <= 1) return;
    for (int i = 0; i < n; ++i) { /* constant work */ }
    f(n / 2);
    f(n / 2);
}

T(n) = 2T(n/2) + c*n
Expansion:
  T(n) = 2T(n/2) + cn
       = 4T(n/4) + 2cn
       = 8T(n/8) + 3cn
After k expansions:
  T(n) = 2^k T(n/2^k) + kcn
Stop at n/2^k = 1 => k = log2(n).
Time: O(n log n).

IMPORTANT: The coefficient of cn is k, NOT 2^k - 1.
The geometric expression 2^k - 1 counts nodes/calls in certain
recursion-tree levels; it is not the accumulated loop work here.

17) THREE CALLS ON n/2, CONSTANT WORK

void f(int n) {
    if (n <= 1) return;
    f(n / 2);
    f(n / 2);
    f(n / 2);
}

T(n) = 3T(n/2) + c
Stop depth k = log2(n).
Leaves: 3^k = 3^(log2 n) = n^(log2 3).
Time: O(n^(log2 3)) ≈ O(n^1.585).

18) TWO CALLS ON n/3, CONSTANT WORK

void f(int n) {
    if (n <= 1) return;
    f(n / 3);
    f(n / 3);
}

T(n) = 2T(n/3) + c
Depth: log3(n)
Leaves: 2^(log3 n) = n^(log3 2)
Time: O(n^(log3 2)) ≈ O(n^0.631).

19) ONE CALL ON n/2, LOOP OF SIZE n

void f(int n) {
    if (n <= 1) return;
    for (int i = 0; i < n; ++i) { /* constant work */ }
    f(n / 2);
}

T(n) = T(n/2) + c*n
Expansion: cn + cn/2 + cn/4 + ... < 2cn
Time: O(n), not O(n log n).

20) TWO CALLS ON n-1, CONSTANT WORK

void f(int n) {
    if (n <= 0) return;
    f(n - 1);
    f(n - 1);
}

T(n) = 2T(n - 1) + c
Time: O(2^n) — exponential.

21) NAIVE FIBONACCI

long long fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

T(n) = T(n - 1) + T(n - 2) + c
Time: O(2^n) as a simple upper bound; tightly Theta(phi^n).
With memoization: O(n) time and O(n) memory.

22) BINARY SEARCH

int binarySearch(const int arr[], int low, int high, int key) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (arr[mid] == key) return mid;
    if (key < arr[mid])
        return binarySearch(arr, low, mid - 1, key);
    return binarySearch(arr, mid + 1, high, key);
}

T(n) = T(n/2) + c
Time: O(log n).

23) MERGE-SORT PATTERN

Two recursive halves plus O(n) merging:
T(n) = 2T(n/2) + cn
Time: O(n log n).

24) NESTED LOOPS

for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
        /* constant work */;

Work: n*n
Time: O(n^2).

25) OUTER LOOP n TIMES, INNER LOOP HALVES

for (int i = 0; i < n; ++i)
    for (int j = n; j > 1; j /= 2)
        /* constant work */;

Time: O(n log n).

---------------------------------------------------------
PART 3: MATHEMATICAL FORMULAS
---------------------------------------------------------

Arithmetic series:
  1 + 2 + ... + n = n(n+1)/2 = Theta(n^2)
Use for T(n) = T(n-1) + cn.

Geometric series:
  1 + 2 + 4 + ... + 2^k = 2^(k+1) - 1
Use to count calls at levels of a recursion tree.

Decreasing work:
  n + n/2 + n/4 + ... < 2n
Thus T(n) = T(n/2) + cn is O(n).

General divide-and-conquer:
  T(n) = aT(n/b) + Theta(n^d)
Compare a with b^d:
  - a < b^d: Theta(n^d)
  - a = b^d: Theta(n^d log n)
  - a > b^d: Theta(n^(log_b a))
These are the standard Master Theorem cases for regular polynomial-size
subproblems and the usual conditions.

Tree time vs stack:
  Time: often O(n) when every node is visited once.
  Stack: O(h), where h is tree height.
  Balanced tree: h = O(log n); skewed tree: h = O(n).

QUICK TABLE:
  T(n) = T(n-1) + c        => O(n)
  T(n) = T(n-1) + cn       => O(n^2)
  T(n) = T(n/2) + c        => O(log n)
  T(n) = T(n/2) + cn       => O(n)
  T(n) = 2T(n/2) + c       => O(n)
  T(n) = 2T(n/2) + cn      => O(n log n)
  T(n) = 3T(n/2) + c       => O(n^(log2 3))
  T(n) = 2T(n/3) + c       => O(n^(log3 2))
  T(n) = 2T(n-1) + c       => O(2^n)
*/
int main() {
    // This file is a reference sheet. See the comments above.
    return 0;
}
