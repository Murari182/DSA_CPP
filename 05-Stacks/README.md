# Stacks: Principles, Implementations & Applications in C++17

A comprehensive module covering the Last-In-First-Out (LIFO) discipline, array-based and linked-list stack implementations, expression conversion (infix, postfix, prefix), operator precedence parsing, and monotonic stack patterns.

---

## Module Overview

| Document / Code | Description | Key Topics |
|---|---|---|
| [stack_array_and_linked_list.md](./Notes/stack_array_and_linked_list.md) | Architectural stack models | Dynamic array implementation, linked-list implementation, overflow/underflow, STL `std::stack` |
| [stack_applications_infix_postfix.md](./Notes/stack_applications_infix_postfix.md) | Expression parsing & compilers | Shunting-yard algorithm, infix-to-postfix conversion, postfix evaluation, bracket balancing |
| [Infix_to_Postfix_and_Evaluation.cpp](./Infix_to_Postfix_and_Evaluation.cpp) | Complete expression parser | Operator precedence, associativity, evaluation engine |
| [stack_01.cpp](./stack_01.cpp) & [stack_02.cpp](./stack_02.cpp) | Stack implementations | Array-based and linked-node implementations |
| [hello.cpp](./hello.cpp) | Character-based stack | Expression validation and matching |

---

## The LIFO Discipline & Operations

```text
       Push (Insert at Top)          Pop (Remove from Top)
              |                                 ^
              v                                 |
        +------------+                   +------------+
        |   Item 3   |  <--- TOP         |   Item 3   |
        +------------+                   +------------+
        |   Item 2   |                   |   Item 2   |
        +------------+                   +------------+
        |   Item 1   |                   |   Item 1   |
        +------------+                   +------------+
```

### Core Operations
- `push(x)`: Inserts element \( x \) on top of the stack. Time: \( O(1) \).
- `pop()`: Removes the topmost element. Time: \( O(1) \).
- `top()` / `peek()`: Returns the topmost element without removing it. Time: \( O(1) \).
- `empty()`: Returns true if stack contains 0 elements. Time: \( O(1) \).

---

## Monotonic Stack Pattern
A monotonic stack maintains elements in strictly increasing or decreasing order.
- **Key Applications:** Next Greater Element, Next Smaller Element, Largest Rectangle in Histogram, Daily Temperatures.
- **Complexity:** Amortized \( O(n) \) time because each element is pushed and popped at most once!
