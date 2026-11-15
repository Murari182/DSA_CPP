# Recursion, Call Stack Mechanics & Backtracking

A comprehensive module covering base cases, recurrence relations, stack frame anatomy, recursion trees, state-space exploration, pruning, and backtracking algorithms in C++17.

---

## Module Overview

| Document / Code | Description | Key Topics |
|---|---|---|
| [recursion_fundamentals_and_call_stack.md](./Notes/recursion_fundamentals_and_call_stack.md) | Mechanics of recursion & OS stack | Base cases, recursive cases, stack frame push/pop, stack overflow |
| [backtracking_and_state_space_trees.md](./Notes/backtracking_and_state_space_trees.md) | Backtracking & search space exploration | N-Queens, Sudoku solver, subsets, permutations, pruning |
| [Recursion_Fundamentals.cpp](./Recursion_Fundamentals.cpp) | Core recursive patterns in C++17 | Factorial, Fibonacci, power, tower of Hanoi |
| [Backtracking_Algorithms.cpp](./Backtracking_Algorithms.cpp) | Full backtracking implementations | State-space tree search with undo-choice mechanics |
| [rec.cpp](./rec.cpp) | Recursion utilities & testing | Additional recursive examples |

---

## The General Backtracking Paradigm

Backtracking systematically searches for solutions by constructing candidate states incrementally and abandoning ("backtracking" from) a candidate as soon as it determines that the candidate cannot lead to a valid solution.

### Universal Backtracking Pseudocode Template
```text
void backtrack(State& state, Choices& choices) {
    if (isGoal(state)) {
        recordSolution(state);
        return;
    }

    for (const auto& choice : choices) {
        if (isValid(choice, state)) {
            applyChoice(choice, state);       // 1. Choose
            backtrack(state, choices);        // 2. Explore
            undoChoice(choice, state);         // 3. Backtrack (Undo choice)
        }
    }
}
```
- **Pruning:** By checking `isValid(choice, state)` before recursing, backtracking cuts off entire branches of the exponential search space tree, transforming infeasible $ O(n!) $ searches into tractable algorithms.
