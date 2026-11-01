# C++ Fundamentals, Pointers, Dynamic Memory & OOP for DSA

## Related Implementation

- `../pointers_and_references.cpp` *(Supplementary implementation created for this folder)*
- Used across the repository in:
  - `../../04-Linked-Lists/linked_list-01.cpp`
  - `../../04-Linked-Lists/DoubleLinkedList.cpp`
  - `../../05-Stacks/stack_01.cpp`
  - `../../05-Stacks/stack_02.cpp`
  - `../../06-Queues/Queue_01.cpp`
  - `../../08-Trees/BST_01.cpp`

---

## 1. Concept Introduction

### What is the Concept?
C++ provides low-level memory manipulation through **pointers**, **references**, and **dynamic memory allocation** (`new` and `delete`), combined with high-level **Object-Oriented Programming (OOP)** abstractions (`class`, constructors, `this` pointer, and `friend class`).

### Why is it Required?
In Data Structures and Algorithms (DSA), data structures fall into two primary physical storage models:
1. **Contiguous structures** (arrays, vectors, binary heaps) where elements live in adjacent memory addresses.
2. **Node-based dynamic structures** (linked lists, stacks, queues, binary trees, BSTs) where nodes are allocated at runtime on the heap and connected via memory addresses stored in pointers.

### What Problem Does it Solve?
Static arrays have a fixed size determined at compile time on the call stack. Dynamic memory allocation and pointers allow programs to request memory at runtime from the **free store (heap)**, link non-contiguous nodes together in $O(1)$ time, and pass large structures to functions without duplicating memory.

### How Does it Relate to Other Concepts in This Repository?
Throughout folders `04` through `08`, you consistently use two core design patterns:
- **Encapsulated `Node` + `friend class` Container Pattern**: Used in `04-Linked-Lists`, `05-Stacks/stack_02.cpp`, and `06-Queues/Queue_01.cpp`, where `Node` keeps `data` and `next` private and grants access to the container class (`friend class list;`, `friend class stack;`, `friend class que;`).
- **Public `Node` + Free Recursive Functions Pattern**: Used in `08-Trees/Binary_Tree_01.cpp` and `08-Trees/BST_01.cpp`, where `Node` members (`left`, `right`, `data`) are `public` and recursive functions take `Node* root`.

---

## 2. Fundamental Theory

### Memory Segments in a C++ Program
When a C++ program executes, its virtual memory is divided into four major segments:
1. **Code / Text Segment**: Stores compiled machine instructions (read-only).
2. **Data / BSS Segment**: Stores global and `static` variables (such as `static int idx = -1;` in `Binary_Tree_01.cpp` and `static int count = 0;` in `BST_01.cpp`).
3. **Stack Segment**: Stores function call frames, local variables, and function parameters. Memory is managed automatically in Last-In-First-Out (LIFO) order.
4. **Heap (Free Store) Segment**: Stores dynamically allocated objects created with `new`. Memory persists until explicitly freed using `delete` or `delete[]`.

### Key Definitions
- **Address-of Operator (`&`)**: Unary operator that returns the memory address of a variable.
- **Pointer (`T*`)**: A variable that stores the memory address of another variable of type `T`.
- **Dereference Operator (`*`)**: Unary operator that accesses the value stored at the memory address held by a pointer.
- **Null Pointer (`NULL` / `nullptr`)**: A pointer value indicating that the pointer does not refer to any valid memory object.
- **Reference (`T&`)**: An alias (alternative name) for an existing variable. Must be initialized when declared and cannot be reassigned to refer to a different object.
- **`this` Pointer**: An implicit constant pointer available inside non-static member functions of a class that points to the current object instance on which the member function was invoked.
- **Member Access Arrow Operator (`->`)**: Shorthand for dereferencing a pointer to an object and accessing its member: `ptr->member` is equivalent to `(*ptr).member`.

---

## 3. Mathematical Representation

### Pointer Address Arithmetic
If a pointer `ptr` points to element $0$ of an array of type `T` starting at base address $B$, then adding an integer offset $i$ to the pointer computes:

$$\text{Address}(\text{ptr} + i) = B + i \times \text{sizeof}(T)$$

### Memory Overhead of Pointer-Based Nodes
For a 64-bit architecture where `sizeof(int) = 4` bytes and `sizeof(void*) = 8` bytes:
- Singly Linked List `Node` (`int data`, `Node* next`):
  $$\text{Logical Size} = 4 + 8 = 12 \text{ bytes} \xrightarrow{\text{8-byte alignment padding}} 16 \text{ bytes}$$
- Doubly Linked List or Binary Tree `Node` (`int data`, two pointers):
  $$\text{Logical Size} = 4 + 8 + 8 = 20 \text{ bytes} \xrightarrow{\text{8-byte alignment padding}} 24 \text{ bytes}$$

---

## 4. Working Mechanism

### Parameter Passing Modes in C++
1. **Pass by Value (`void func(int x)`)**:
   - Copies the value of the argument into the formal parameter `x` on the stack.
   - Changes made to `x` inside `func` do not affect the caller's variable.
   - Cost: $O(\text{sizeof}(T))$ copy time and space.
2. **Pass by Pointer (`void func(int *x)`)**:
   - Copies the memory address ($8$ bytes on 64-bit systems) of the argument.
   - Dereferencing `*x` reads or modifies the original variable in the caller's scope.
   - Can accept `NULL` / `nullptr`.
3. **Pass by Reference (`void func(int &x)` or `void func(const vector<int> &arr)`)**:
   - Binds `x` directly as an alias to the caller's variable without copying the object.
   - Adding `const` prevents modification while still avoiding an $O(n)$ copy (used in `08-Trees/Binary_Tree_Array.cpp`: `void Build_BT(const vector<int>& arr)`).

### Dynamic Memory Lifecycle (`new` and `delete`)
1. `Node *n1 = new Node(val);`
   - Step 1: Requests `sizeof(Node)` bytes from the heap allocator.
   - Step 2: Invokes the constructor `Node::Node(val)` to initialize `this->data = val` and pointers to `NULL`.
   - Step 3: Returns the starting heap address and stores it in local stack pointer `n1`.
2. `delete temp;`
   - Step 1: Calls the destructor of the object pointed to by `temp`.
   - Step 2: Releases the heap memory block back to the free store.
   - Step 3: Note that `temp` itself still holds the old address (now a **dangling pointer**) unless reassigned or out of scope.

---

## 5. Visual Representation

### Stack vs. Heap Memory Layout When Creating a Node
```
STACK MEMORY (Automatic)                 HEAP MEMORY (Dynamic / Free Store)
+------------------------+               +--------------------------------+
| main() / push_front()  |               | Node Object at 0x7fff5000      |
|                        |               | +----------------------------+ |
| Node *n1 = 0x7fff5000 -|-------------->| | data: 10                   | |
+------------------------+               | | next: NULL (0x0)           | |
                                         | +----------------------------+ |
                                         +--------------------------------+
```

### Disambiguating Shadowed Names with `this->`
In your constructors across `04-Linked-Lists`, `05-Stacks`, `06-Queues`, and `08-Trees`:
```cpp
Node(int data) {
    this->data = data; // this->data is the member variable; data is the parameter
    next = NULL;
}
```
```
+--------------------------------------------+
| Parameter on Stack:  int data = 25         |
|                          |                 |
|                          v                 |
| Object on Heap (this):   this->data = 25   |
+--------------------------------------------+
```

---

## 6. C++ Implementation Analysis

### File: `../pointers_and_references.cpp`

#### 1. `Box` and `Inspector` Classes (`friend class` Pattern)
- **Purpose**: Demonstrates how private data members (`length`, `width`) are hidden from outside functions but accessible to a designated `friend class Inspector`—the exact pattern used in `Node` and `list`/`stack`/`que` in your repository.
- **Constructor `Box(int length, int width)`**: Uses `this->length = length;` to resolve variable shadowing between the constructor parameter and class member.

#### 2. `increment_by_value`, `increment_by_pointer`, `increment_by_reference`
- **Purpose**: Contrasts the three parameter-passing mechanisms.
- **Parameters**:
  - `int x`: Local copy.
  - `int *x`: Pointer checked against `NULL` before dereferencing `*x`.
  - `int &x`: Reference alias modifying the caller's variable directly.
- **Complexity**: $O(1)$ time and $O(1)$ space for all three.

---

## 7. Dry Runs

### Tracing `pointers_and_references.cpp`

| Step | Statement Executed | `val` (at `0x100`) | `*ptr` (`ptr = 0x100`) | Explanation |
| :--- | :--- | :---: | :---: | :--- |
| 1 | `int val = 42;` | `42` | — | `val` initialized on stack at `0x100` |
| 2 | `int *ptr = &val;` | `42` | `42` | `ptr` stores `0x100`; `*ptr` reads `42` |
| 3 | `increment_by_value(val);` | `42` | `42` | Local copy `x` becomes `52` and is destroyed |
| 4 | `increment_by_pointer(&val);` | `52` | `52` | `*x = *x + 10` writes `52` to address `0x100` |
| 5 | `increment_by_reference(val);` | `62` | `62` | Alias `x` directly increments `val` to `62` |

---

## 8. Time Complexity

| Operation | Best Case | Average Case | Worst Case | Explanation |
| :--- | :---: | :---: | :---: | :--- |
| Pointer Assignment / Dereference | $O(1)$ | $O(1)$ | $O(1)$ | Single CPU register load/store instruction |
| Pass by Pointer / Reference | $O(1)$ | $O(1)$ | $O(1)$ | Passes a single memory address regardless of object size |
| Pass `vector<int>` by Value | $O(n)$ | $O(n)$ | $O(n)$ | Allocates and copies all $n$ elements |
| Single `new Node(val)` / `delete` | $O(1)$ | $O(1)$ | $O(1)$ | Allocates/frees fixed-size block on the heap |
| Dynamic Array `new int[n]` | $O(n)$ / $O(1)$ | $O(n)$ / $O(1)$ | $O(n)$ | $O(1)$ raw allocation for primitives, $O(n)$ if initialized |

---

## 9. Space Complexity

- **Pointer Variable**: $O(1)$ auxiliary space ($8$ bytes on 64-bit architectures, $4$ bytes on 32-bit architectures).
- **Pass by Reference (`vector<int> &arr`)**: $O(1)$ auxiliary space because no copy of the container is created.
- **Dynamic Array (`new int[n]`)**: $O(n)$ heap space.

---

## 10. Important Properties and Observations

1. **Why `Build_BST(Node* root, int data)` returns `Node*` in `08-Trees/BST_01.cpp`**:
   Because `root` is passed **by value** (`Node* root`, a copy of the pointer), assigning `root = new Node(data)` inside the function only modifies the local pointer copy unless the new address is returned and assigned back by the caller (`root->left = Build_BST(root->left, data);`).
2. **Static Local/Global Variables in Recursion**:
   In `08-Trees/Binary_Tree_01.cpp` (`static int idx = -1;`) and `08-Trees/BST_01.cpp` (`static int count = 0;`), `static` variables persist in the Data segment across all recursive calls. If you call the function a second time in `main()`, you must manually reset the `static` variable (as done in `Binary_Tree_01_Detailed.cpp` with `idx = -1;`).
3. **`NULL` vs `nullptr`**:
   In your code, `clinked.cpp` and `Recursive_Time_Complexity_Binary_Trees.cpp` use C++11 `nullptr` (type-safe pointer literal of type `std::nullptr_t`), while the other files use `NULL` (macro expanding to integer `0`). Both work identically in pointer comparisons, though `nullptr` avoids overload ambiguity with `int`.

---

## 11. Advantages and Disadvantages

### Advantages of Pointers & Dynamic Allocation
- Allows data structures to grow and shrink dynamically at runtime up to available system RAM.
- Enables $O(1)$ insertion and deletion in linked structures via pointer rewiring without shifting elements.
- Allows sharing and mutating state across functions without copying large objects.

### Disadvantages
- **Manual Memory Management**: Forgetting `delete` causes **memory leaks**; accessing memory after `delete` causes **use-after-free** undefined behavior.
- **Null Pointer Dereferencing**: Accessing `temp->next` when `temp == NULL` immediately crashes the program with a Segmentation Fault (`SIGSEGV`).
- **Cache Locality**: Heap-allocated nodes may be scattered in memory, leading to more CPU cache misses compared to contiguous arrays.

---

## 12. Comparison with Related Concepts

### Pointer vs. Reference in C++

| Feature | Pointer (`T*`) | Reference (`T&`) |
| :--- | :--- | :--- |
| **Can be `NULL` / `nullptr`?** | Yes | No (must refer to a valid object) |
| **Can be reassigned to another object?** | Yes (`ptr = &other;`) | No (bound for its entire lifetime) |
| **Syntax to access value** | Requires dereferencing `*ptr` or `ptr->` | Direct variable syntax `ref` or `ref.` |
| **Primary DSA Use Case** | Node links (`next`, `prev`, `left`, `right`) | Passing `vector<int>&` or `list&` to functions |

### Stack Memory vs. Heap Memory

| Feature | Stack Memory | Heap Memory (Free Store) |
| :--- | :--- | :--- |
| **Allocation Mechanism** | Automatic on function/block entry | Explicit via `new` / `new[]` |
| **Deallocation Mechanism** | Automatic when variable goes out of scope | Explicit via `delete` / `delete[]` |
| **Allocation Speed** | Extremely fast (single stack pointer shift) | Slower (heap allocator bookkeeping) |
| **Size Limit** | Small (typically 1 MB – 8 MB; overflows on deep recursion) | Large (bounded by system RAM) |

---

## 13. Common Mistakes

1. **Dereferencing a `NULL` Pointer**:
   Writing `temp->next` or `front->next` before checking `if (temp != NULL)`. Always check `fast != NULL && fast->next != NULL` using short-circuit `&&` (never `||`).
2. **Memory Leaks When Overwriting Pointers**:
   If `head = head->next;` is executed without saving the old `head` in a `Node* temp` and calling `delete temp;`, the old node remains allocated on the heap forever with no pointer pointing to it.
3. **Mismatched `new[]` and `delete`**:
   Memory allocated with `new int[n]` must be freed with `delete[] arr`, not `delete arr`.
4. **Dangling Pointers**:
   Continuing to dereference a pointer after `delete ptr;` has been called.

---

## 14. Applications

1. **Dynamic Data Structures**: Linked Lists (`04-Linked-Lists`), Dynamic Stacks (`05-Stacks/stack_02.cpp`), Linked Queues (`06-Queues/Queue_01.cpp`), and Binary Trees (`08-Trees`).
2. **Zero-Copy Function Arguments**: Passing large `vector<int>&` or custom `list&` objects (`Merge_SL(list &l1, list &l2)` in `Linked_List-02.cpp`).
3. **Out-Parameters in Recursive Tree Algorithms**: Passing `int &max_diameter` by reference to accumulate state across recursive tree calls without global variables.

---

## 15. Practice Questions

1. **Basic Understanding**: What is the difference between `void insert(Node* head)` and `void insert(Node*& head)` when inserting a new node at the beginning of a linked list?
2. **Implementation**: Write a C++ function `void swap_pointers(Node* &a, Node* &b)` that swaps two `Node` pointers without copying the `Node` objects.
3. **Dry-Run Problem**: Given `int a = 10, b = 20; int *p = &a; int *q = &b; *p = *q + 5; p = q; *p = 100;`, what are the final values of `a` and `b`?
4. **Complexity Analysis**: Suppose a function `int sum(vector<int> v, int i)` recursively computes the sum of a vector of size $n$, but passes `vector<int> v` **by value** instead of `const vector<int>& v`. What do the time complexity and space complexity become?
5. **Interview Question**: Why does `sizeof(Node)` in a 64-bit C++ compiler equal `16` bytes instead of `12` bytes when `Node` contains one `int` (4 bytes) and one `Node*` (8 bytes)?

---

## 16. Quick Revision

- **`&x`**: Address of `x`.
- **`*ptr`**: Value at address stored in `ptr`.
- **`ptr->data`**: Equivalent to `(*ptr).data`.
- **`this`**: Pointer to the current object instance inside a class method.
- **`friend class B`**: Grants class `B` access to `private` and `protected` members of class `A`.
- **Short-Circuit Guard**: Always write `while (fast != NULL && fast->next != NULL)`—if the left condition is false, C++ guarantees the right condition is not evaluated.
