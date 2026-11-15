# Greedy Algorithms in Modern C++17

A reference guide to the greedy paradigm, optimal substructure, greedy-choice property, interval scheduling, knapsack variations, and graph optimization routines.

---

## 1. The Greedy Choice Paradigm

A **Greedy Algorithm** builds up a solution piece by piece, always choosing the next piece that offers the most immediate, local benefit (**greedy choice**), without ever reconsidering past choices.

### When Does a Greedy Strategy Yield a Globally Optimal Solution?
A problem is solvable by a greedy algorithm if and only if it satisfies two strict mathematical properties:
1. **Greedy-Choice Property:** A globally optimal solution can be arrived at by making locally optimal (greedy) choices without looking ahead or backtracking.
2. **Optimal Substructure:** An optimal solution to the overall problem contains within it optimal solutions to its subproblems.

---

## 2. Canonical Greedy Algorithms & Paradigms

| Problem / Algorithm | Greedy Metric / Choice | Optimal? | Contrast with Dynamic Programming |
|---|---|---|---|
| **Activity Selection / Interval Scheduling** | Earliest finishing time $ f_i $ | **Yes** | Sort by end time; non-overlapping greedy pick |
| **Fractional Knapsack** | Highest value-to-weight ratio $ v_i / w_i $ | **Yes** | Can take fractional parts (0/1 Knapsack requires DP!) |
| **Huffman Coding** | Combine two lowest frequency trees | **Yes** | Optimal prefix-free compression tree |
| **Dijkstra's Shortest Path** | Extract vertex with minimum tentative distance | **Yes** (non-negative weights) | Greedy relaxation fails on negative edges |
| **Kruskal's MST** | Add cheapest edge that does not form a cycle | **Yes** | Cut and cycle properties guarantee optimality |
| **Prim's MST** | Add cheapest edge crossing the current tree cut | **Yes** | Cut property guarantees global minimum weight |
| **Coin Change (Standard Currency)** | Highest denomination first | **Yes** (canonical systems) | Arbitrary coin denominations require DP! |
