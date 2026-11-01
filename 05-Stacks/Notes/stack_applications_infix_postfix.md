# Stack Applications: Infix-to-Postfix Conversion, Postfix Evaluation & Balanced Parentheses

## Related Implementation

- `../hello.cpp` *(Original work-in-progress Infix-to-Postfix implementation)*
- `../Infix_to_Postfix_and_Evaluation.cpp` *(Supplementary complete implementation created for this folder)*

---

## 1. Concept Introduction

### What is the Concept?
Humans write arithmetic expressions in **Infix Notation**, where binary operators appear **between** their operands (e.g., `a + b * c`). However, computers cannot evaluate infix expressions directly in a single left-to-right scan because of **operator precedence** (`*` before `+`), **associativity** (`+` is left-to-right; `^` is right-to-left), and **parentheses** `( ... )`.

**Postfix Notation (Reverse Polish Notation / RPN)** places each operator **immediately after** its operands (e.g., `a b c * +`). Postfix expressions require **zero parentheses** and can be evaluated in a single left-to-right pass using a **Stack**!

---

## 2. Fundamental Theory

### Three Expression Notations
| Notation | Operator Position | Example 1 | Example 2 | Needs Parentheses? |
| :--- | :--- | :---: | :---: | :---: |
| **Infix** | `Operand1 op Operand2` | `a + b * c` | `(a + b) * c` | Yes |
| **Prefix (Polish)** | `op Operand1 Operand2` | `+ a * b c` | `* + a b c` | No |
| **Postfix (RPN)** | `Operand1 Operand2 op` | `a b c * +` | `a b + c *` | No |

### Operator Precedence & Associativity Table (as modeled in `prece(char op)` in `../hello.cpp`)
| Operator | Precedence Value (`prece`) | Associativity | Meaning |
| :---: | :---: | :---: | :--- |
| `^` | `3` (Highest) | **Right-to-Left** (`a^b^c` = `a^(b^c)`) | Exponentiation |
| `*`, `/`, `%` | `2` (Medium) | **Left-to-Right** (`a*b/c` = `(a*b)/c`) | Multiplication, Division, Modulo |
| `+`, `-` | `1` (Lowest) | **Left-to-Right** (`a-b+c` = `(a-b)+c`) | Addition, Subtraction |

---

## 3. Mathematical Representation

### Shunting-Yard Stacking Condition for an Incoming Operator `ch`
When scanning an infix expression from left to right and encountering an operator `ch`, we must pop operators from the stack and append them to `postfix` as long as the stack is non-empty, `peek() != '('`, and:

$$\text{prece}(\text{peek}()) > \text{prece}(\text{ch}) \quad \lor \quad \Big(\text{prece}(\text{peek}()) == \text{prece}(\text{ch}) \land \text{ch is Left-Associative}\Big)$$

After popping all higher-or-equal precedence operators, we `push(ch)` onto the stack.

---

## 4. Working Mechanism

### 1. Dijkstra's Shunting-Yard Algorithm (Infix $\to$ Postfix)
Scan each character `ch` of the infix string from left to right:
1. **If `ch` is an Operand** (`A–Z`, `a–z`, `0–9`):
   Append `ch` directly to the `postfix` output string.
2. **If `ch == '('`**:
   `push('(')` onto the operator stack.
3. **If `ch == ')'`**:
   While the stack is not empty and `peek() != '('`, `pop()` from the stack and append to `postfix`. Then `pop()` and discard the matching `'('`.
4. **If `ch` is an Operator (`+`, `-`, `*`, `/`, `%`, `^`)**:
   While `!isempty()` and `peek() != '('` and `(prece(peek()) > prece(ch) || (prece(peek()) == prece(ch) && ch != '^'))`, `pop()` from the stack and append to `postfix`.
   Then `push(ch)` onto the stack.
5. **End of Input**:
   While `!isempty()`, `pop()` all remaining operators from the stack and append them to `postfix`. Return `postfix`.

### 2. Postfix Expression Evaluation (`evaluate_postfix`)
Scan each character `ch` of the postfix string from left to right:
1. **If `ch` is a Digit (`'0'`–`'9'`)**: Convert `ch - '0'` to an `int` and `push` onto the operand stack.
2. **If `ch` is an Operator**:
   - Pop the top element as the **right** operand: `right = pop()`.
   - Pop the next element as the **left** operand: `left = pop()`. *(Order matters for `-` and `/`!)*
   - Compute `res = left op right` and `push(res)` back onto the stack.
3. At the end of the string, the single value at the top of the stack is the final answer.

---

## 5. Visual Representation

### Stack State Transitions During Infix $\to$ Postfix of `a+b*(c^d-e)`
```
Token   Operator Stack (Bottom -> Top)     Postfix Output
-----   ------------------------------     --------------
 'a'    [ ]                                "a"
 '+'    [ + ]                              "a"
 'b'    [ + ]                              "ab"
 '*'    [ + * ]                            "ab"
 '('    [ + * ( ]                          "ab"
 'c'    [ + * ( ]                          "abc"
 '^'    [ + * ( ^ ]                        "abc"
 'd'    [ + * ( ^ ]                        "abcd"
 '-'    [ + * ( - ]   (^ popped!)          "abcd^"
 'e'    [ + * ( - ]                        "abcd^e"
 ')'    [ + * ]       (- and ( popped!)    "abcd^e-"
 END    [ ]           (* then + popped!)   "abcd^e-*+"
```

---

## 6. C++ Implementation & Code Review (`../hello.cpp` & `../Infix_to_Postfix_and_Evaluation.cpp`)

### Detailed Review of Original File `../hello.cpp`
*(Documented here without modifying `../hello.cpp`; the completed version is in `../Infix_to_Postfix_and_Evaluation.cpp`)*

In `../hello.cpp`, you built a character-based `stack` (`char arr[100]; int cap; int top;`) with `push`, `isempty`, `pop`, `peek`, `isoperator`, `prece`, and started `infix_postfix(string infinix)`:
1. **Typo in `isoperator(char ch)` (Line 73 of `hello.cpp`)**:
   - Line 73 reads:
     ```cpp
     if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'b') || (ch >= '0' && ch <= '9'))
     ```
   - Notice two things:
     1. Functionally, this checks if `ch` is an **alphanumeric operand** (used on line 104: `if(isoperator(ch)) postfix = postfix + ch;`).
     2. The lowercase range check says `ch <= 'b'` instead of `ch <= 'z'`, which causes lowercase variables `'c'`, `'d'`, `'e'`, etc., to be rejected as operands!
2. **Incomplete `infix_postfix` Function (Lines 98–122 of `hello.cpp`)**:
   - Lines 104–119 correctly handle:
     - Operands (`if (isoperator(ch))`)
     - Opening parenthesis (`else if (ch == '(')`)
     - Closing parenthesis (`else if (ch == ')')`)
   - **What was left unfinished in `hello.cpp`**:
     1. The `else` branch for operators (`+`, `-`, `*`, `/`, `^`) comparing `prece(peek())` with `prece(ch)`.
     2. The final `while (!isempty()) { postfix = postfix + pop(); }` loop after the `for` loop finishes.
     3. The `return postfix;` statement at the end of `infix_postfix` and a `main()` driver function.
   - All of these are completed in your exact coding style in `../Infix_to_Postfix_and_Evaluation.cpp`!

---

## 7. Dry Runs

### Dry Run 1: Postfix Evaluation of `"231*+9-"` (`evaluate_postfix("231*+9-")`)
*(Infix equivalent: $2 + (3 \times 1) - 9 = -4$)*

| Step | Token `ch` | Type | Action | Operand Stack (`bottom .. top`) |
| :---: | :---: | :--- | :--- | :--- |
| 1 | `'2'` | Operand | Push `2` | `[2]` |
| 2 | `'3'` | Operand | Push `3` | `[2, 3]` |
| 3 | `'1'` | Operand | Push `1` | `[2, 3, 1]` |
| 4 | `'*'` | Operator | Pop `right=1, left=3`; Push `3 * 1 = 3` | `[2, 3]` |
| 5 | `'+'` | Operator | Pop `right=3, left=2`; Push `2 + 3 = 5` | `[5]` |
| 6 | `'9'` | Operand | Push `9` | `[5, 9]` |
| 7 | `'-'` | Operator | Pop `right=9, left=5`; Push `5 - 9 = -4` | `[-4]` (Returns `-4`) |

### Dry Run 2: Balanced Parentheses Check on `"{[(])}"` (`is_balanced("{[(])}")`)
| Step | `ch` | Stack State | Action | Result |
| :---: | :---: | :--- | :--- | :--- |
| 1 | `'{'` | `['{']` | Push `'{'` | Continue |
| 2 | `'['` | `['{', '[']` | Push `'['` | Continue |
| 3 | `'('` | `['{', '[', '(']` | Push `'('` | Continue |
| 4 | `']'` | `['{', '[']` | Popped `'('` does not match `']'`! | **Returns `false` immediately** |

---

## 8. Time Complexity

| Algorithm | Best Case | Average Case | Worst Case | Why? (Amortized Analysis) |
| :--- | :---: | :---: | :---: | :--- |
| **Infix to Postfix** | $O(n)$ | $O(n)$ | $O(n)$ | Even with nested `while` inside `for`, each character is pushed at most once and popped at most once ($\le 2n$ stack ops) |
| **Postfix Evaluation** | $O(n)$ | $O(n)$ | $O(n)$ | Single scan of $n$ characters with $O(1)$ stack ops per token |
| **Balanced Parentheses** | $O(1)$ | $O(n)$ | $O(n)$ | Scans at most $n$ brackets; $O(1)$ if first char is `')'` |

---

## 9. Space Complexity

- **Infix to Postfix**: $O(n)$ auxiliary stack space for operators + $O(n)$ space for the output `postfix` string.
- **Postfix Evaluation**: $O(n)$ auxiliary stack space for operands.
- **Balanced Parentheses**: $O(n)$ auxiliary stack space in the worst case (e.g., `"(((((("`).

---

## 10. Important Properties and Observations

1. **Order of Operands Never Changes Between Infix and Postfix**:
   In `a + b * (c ^ d - e)` and `abcd^e-*+`, the operands appear in the exact same left-to-right relative order (`a, b, c, d, e`)! Only the operators change position and parentheses disappear.
2. **Why `right` is Popped Before `left` in `evaluate_postfix`**:
   Because `left` was pushed first and `right` was pushed second, LIFO order means the first `pop()` returns `right` and the second `pop()` returns `left`. For non-commutative operators (`left - right` and `left / right`), reversing them produces the wrong sign or quotient!

---

## 11. Advantages and Disadvantages

### Advantages of Postfix Representation
- Completely eliminates parentheses and precedence rules during evaluation.
- Evaluates in a single $O(n)$ left-to-right pass using a simple operand stack.

### Disadvantages
- Less intuitive for humans to read compared to infix notation.

---

## 12. Comparison with Related Concepts

| Feature | Infix Evaluation | Postfix (RPN) Evaluation |
| :--- | :--- | :--- |
| **Parentheses Needed?** | Yes | **No** |
| **Precedence Rules Needed at Eval Time?** | Yes | **No** (baked into token order) |
| **Stacks Needed for Direct Evaluation** | 2 (Operand stack + Operator stack) | **1** (Operand stack only) |

---

## 13. Common Mistakes

1. **Popping `'('` Without Stopping at `'('` During Operator Precedence Loop**:
   An `'('` on the stack should only be popped when a matching `')'` arrives. Always include `peek() != '('` (or give `'('` precedence `0`, as your `prece` function does by returning `0` for non-operators!).
2. **Swapping `left` and `right` Operands in Postfix Subtraction/Division**:
   Doing `right - left` instead of `left - right`.
3. **Returning `true` at the End of `is_balanced` Without Checking `s.isempty()`**:
   For an input like `"((()"`, the loop finishes without a mismatch, but two `'('` remain unclosed on the stack. Always `return s.isempty();` at the end.

---

## 14. Applications

- **Compiler Expression Parsers** and **Bytecode Virtual Machines** (JVM and Python bytecode are stack-based machines that evaluate expressions in postfix order).
- **Scientific Calculators** (HP RPN calculators).
- **Linter & IDE Bracket Matching** (`is_balanced`).

---

## 15. Practice Questions

1. **Basic Understanding**: Convert the infix expression `A * (B + C * D) + E` into Postfix and Prefix notations by hand.
2. **Implementation**: How do you convert an **Infix** expression into **Prefix** notation using a Stack?
3. **Dry-Run Problem**: Trace `infix_to_postfix` step-by-step on `"a^b^c"` and explain why right-associativity of `^` produces `"abc^^"` instead of `"ab^c^"`.
4. **Complexity Analysis**: Prove why the inner `while (!isempty() ...)` loop inside the `for (char ch : infix)` loop of `infix_to_postfix` does **not** make the time complexity $O(n^2)$.
5. **Interview Question**: Given a postfix expression containing multi-digit numbers separated by spaces (e.g., `"100 200 + 2 / 5 * 7 +"`), how would you modify `evaluate_postfix` to parse and evaluate it?

---

## 16. Quick Revision

- **Precedence (`prece`)**: `^` ($3$) > `*`, `/`, `%` ($2$) > `+`, `-` ($1$).
- **Shunting-Yard Rule**: Operands go straight to output; `'('` pushes to stack; `')'` pops until `'('`; operators pop higher-or-equal precedence operators before pushing.
- **Postfix Evaluation**: Push numbers; on operator `op`, `right = pop()`, `left = pop()`, push `left op right`.
