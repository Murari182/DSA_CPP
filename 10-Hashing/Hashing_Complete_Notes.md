# Hashing in Data Structures & Algorithms (DSA)

## Hash Functions, Hashing Techniques and Table Size Optimization

A comprehensive guide to hashing, its mathematical foundations, hashing
methods, collisions, table-size selection, and C++ implementations.

## Table of Contents

1.  [Introduction](#1-introduction)
2.  [Hash Table Fundamentals](#2-hash-table-fundamentals)
3.  [Good Hash Functions](#3-good-hash-functions)
4.  [Division Method](#4-division-method)
5.  [Power-of-2 Table Sizes](#5-power-of-2-table-sizes)
6.  [LSB and MSB](#6-lsb-and-msb)
7.  [Drawback of Power-of-2 Sizes](#7-drawback-of-power-of-2-sizes)
8.  [Prime Table Sizes](#8-prime-table-sizes)
9.  [Digit Extraction](#9-digit-extraction)
10. [Mid-Square](#10-mid-square)
11. [Folding](#11-folding)
12. [Comparison](#12-comparison)
13. [Collisions](#13-collisions)
14. [C++ Implementations](#14-c-implementations)
15. [Complexity](#15-complexity)
16. [Common Mistakes](#16-common-mistakes)
17. [Practice Problems](#17-practice-problems)
18. [Quick Revision](#18-quick-revision)

------------------------------------------------------------------------

# 1. Introduction

Hashing is a technique for storing and retrieving data by transforming a
key into an index using a mathematical function called a **hash
function**.

The process is:

`Key → Hash Function → Hash Index → Hash Table`

For example, let:

\[ h(key)=key`\bmod10`{=tex} \]

    Key   Calculation   Index
  ----- ------------- -------
     10       10 % 10       0
     20       20 % 10       0
     30       30 % 10       0
     40       40 % 10       0

Different keys can map to the same index. This is called a
**collision**.

Hashing is used in databases, caches, password-verification systems,
compiler symbol tables, duplicate detection, and C++ `unordered_map` and
`unordered_set`.

# 2. Hash Table Fundamentals

A hash table is an array-like data structure in which positions are
calculated by a hash function.

If the table size is (m=10), valid indices are:

\[ 0,1,2,`\ldots`{=tex},9 \]

A hash function maps keys from a universe (U) into valid table
positions:

\[ h:U`\rightarrow`{=tex}{0,1,`\ldots`{=tex},m-1} \]

Therefore:

\[ `\boxed{0\leq h(key)<m}`{=tex} \]

  Term             Meaning
  ---------------- ---------------------------------------
  Key              Input value to be hashed
  Hash function    Calculates a table index
  Hash table       Stores keys or key-value entries
  Hash index       Position returned by the function
  Table size (m)   Number of available positions
  Collision        Different keys produce the same index
  LSB              Least Significant Bit
  MSB              Most Significant Bit

# 3. Good Hash Functions

A good hash function should distribute keys as uniformly as possible
across the table.

Important properties:

1.  **Deterministic:** The same key gives the same index for a fixed
    function and table configuration.
2.  **Uniform distribution:** Keys should be spread across the available
    positions.
3.  **Few collisions:** The function should minimize collisions for the
    expected input data.
4.  **Efficient computation:** Index calculation should be fast.
5.  **Good use of key information:** Relevant variation in the key
    should influence the result.

A good hash function reduces collisions; it cannot guarantee that
collisions never occur.

# 4. Division Method

The Division Method divides the key by the table size and uses the
remainder.

\[ `\boxed{h(key)=key\bmod m}`{=tex} \]

Example:

\[ key=12345,`\quad `{=tex}m=1000 \]

\[ h(12345)=12345`\bmod1000`{=tex}=`\boxed{345}`{=tex} \]

The modulo operation guarantees:

\[ 0`\leq `{=tex}key`\bmod `{=tex}m\<m \]

For (m=1000), the valid indices are 0 through 999.

# 5. Power-of-2 Table Sizes

A table size is a power of 2 when:

\[ `\boxed{m=2^k}`{=tex} \]

Examples:

    Table size    Power   Number of bits (k)
  ------------ -------- --------------------
             2   (2\^1)                    1
             4   (2\^2)                    2
             8   (2\^3)                    3
            16   (2\^4)                    4
            32   (2\^5)                    5
            64   (2\^6)                    6

For (m=8=2\^3), valid indices are 0 to 7:

    Decimal   Binary
  --------- --------
          0      000
          1      001
          2      010
          3      011
          4      100
          5      101
          6      110
          7      111

There are exactly (2\^3=8) possible three-bit combinations.

In general:

\[ `\boxed{k=\log_2m}`{=tex} \]

when (m) is a power of 2.

# 6. LSB and MSB

-   **LSB (Least Significant Bit):** Rightmost bit.
-   **MSB (Most Significant Bit):** Leftmost bit.

Consider:

\[ 169=(10101001)\_2 \]

The binary place values, from right to left, are:

\[ 1,2,4,8,16,32,64,128 \]

For (m=8=2\^3), the last three bits determine the remainder.

\[ 169=(10101`\underbrace{001}`{=tex}\_{`\text{last 3 bits}`{=tex}})\_2
\]

\[ (001)\_2=1 \]

Therefore:

\[ `\boxed{169\bmod8=1}`{=tex} \]

## Why does extracting the last k bits work?

If (m=2\^k), any non-negative integer (N) can be written as:

\[ N=q`\cdot2`{=tex}^k+r,`\qquad 0`{=tex}`\leq `{=tex}r\<2^k \]

In binary, the last (k) bits represent (r). Thus:

\[ `\boxed{N\bmod2^k=r}`{=tex} \]

## Bitwise AND equivalent

For a positive power-of-2 table size:

\[ `\boxed{h(key)=key\ \&\ (m-1)}`{=tex} \]

Example with (m=8):

``` text
  10101001   (169)
& 00000111   (m - 1)
-----------
  00000001   (1)
```

This is equivalent to `key % m` when `m` is a positive power of 2. In
C++, use suitable unsigned integer types for bitwise hashing.

# 7. Drawback of Power-of-2 Sizes

When (m=2\^k), the Division Method depends only on the last (k) bits.

Suppose (m=8=2\^3):

    Key Binary   Last 3 bits
  ----- -------- -------------
      9 1001     001
     17 10001    001
     25 11001    001
     33 100001   001

All have the same last three bits:

\[ 9`\bmod8`{=tex}=17`\bmod8`{=tex}=25`\bmod8`{=tex}=33`\bmod8`{=tex}=1
\]

They all map to index 1, causing collisions.

**Important:** Power-of-2 table sizes are not inherently bad. They can
expose repetitive patterns in the lower bits of poorly distributed keys.

# 8. Prime Table Sizes

A prime number is an integer greater than 1 with exactly two positive
factors: 1 and itself.

Examples: (2,3,5,7,11,13,17,19,`\ldots`{=tex})

A prime table size can reduce certain systematic collisions caused by
common factors or regular numerical patterns.

## Example: Keys ending in zero

Keys:

\[ 10,20,30,40,50,60 \]

### Table size 10

\[ h(key)=key`\bmod10`{=tex} \]

Every key maps to index 0 because every key is a multiple of 10.

### Table size 7

\[ h(key)=key`\bmod7`{=tex} \]

    Key   Calculation   Index
  ----- ------------- -------
     10        10 % 7       3
     20        20 % 7       6
     30        30 % 7       2
     40        40 % 7       5
     50        50 % 7       1
     60        60 % 7       4

All six keys now map to different positions.

Mathematically, if keys are (K=10n), then with (m=10):

\[ (10n)`\bmod10`{=tex}=0 \]

With (m=7), since (`\gcd`{=tex}(10,7)=1), the remainders cycle through
the table positions as (n) increases.

**Important:** Prime table sizes do not eliminate all collisions. They
can reduce particular regular patterns. Key distribution and
hash-function quality still matter.

# 9. Digit Extraction

The Digit Extraction Method selects particular digit positions from the
original key and combines them to form the index.

Example:

\[ m=1000,`\quad `{=tex}key=456378945 \]

Select the 3rd, 6th and 9th digits from the left:

``` text
4 5 6 3 7 8 9 4 5
    ↑     ↑     ↑
    6     8     5
```

The selected digits are 685:

\[ `\boxed{h(key)=685}`{=tex} \]

Digit positions should be selected so that they vary across the expected
keys.

### Advantages

-   Simple to implement.
-   Fast calculation.
-   Useful when selected positions have good variation.

### Disadvantages

-   Poor digit selection can create many collisions.
-   Effectiveness depends on the structure of the keys.
-   Uniform distribution is not guaranteed.

# 10. Mid-Square

The Mid-Square Method squares the key and extracts the required middle
digits.

## Procedure

1.  Take the original key.
2.  Square it.
3.  Extract the middle digits.
4.  Use them as the hash index.

Example:

\[ m=1000,`\quad `{=tex}key=12356 \]

Square the key:

\[ 12356\^2=152670736 \]

Extract the middle three digits:

``` text
152 | 670 | 736
        ↑
   Middle 3 digits
```

Therefore:

\[ `\boxed{h(12356)=670}`{=tex} \]

## Why square the key?

Squaring mixes information from different parts of the original key.

For example:

\[ 123\^2=15129 \]

\[ 124\^2=15376 \]

The middle three digits are 512 and 537 respectively. A small change in
the key can change the extracted middle portion.

### Advantages

-   Uses information from multiple portions of the key.
-   Can provide good distribution.
-   Uses a straightforward mathematical operation.

### Disadvantages

-   Large squares may overflow fixed-width integer types.
-   Middle-digit extraction needs careful handling.
-   Good distribution is not guaranteed.

**Implementation note:** Use sufficiently wide integer types or
arbitrary-precision arithmetic for large keys.

# 11. Folding

The Folding Method transforms a large key into a smaller value by
dividing it into groups and adding those groups.

General procedure:

1.  Divide the key into equal-sized groups.
2.  Perform the required folding operation.
3.  Add the groups.
4.  Apply modulo if necessary.

Two common variations are:

-   Fold-Shifting.
-   Fold-Boundary.

## 11.1 Fold-Shifting Method

In Fold-Shifting, divide the key into equal-sized groups and add them
directly without reversing any group.

Example:

\[ key=123456789,`\quad `{=tex}m=1000 \]

Divide into groups of three digits:

``` text
123 | 456 | 789
```

Keep the groups unchanged and add:

\[ 123+456+789=1368 \]

Apply modulo:

\[ h(key)=1368`\bmod1000`{=tex} \]

\[ `\boxed{h(key)=368}`{=tex} \]

For groups (G_1,G_2,`\ldots`{=tex},G_n):

\[ S=G_1+G_2+`\cdots`{=tex}+G_n \]

\[ `\boxed{h(key)=S\bmod m}`{=tex} \]

### Advantages

-   Simple addition operation.
-   Easy to implement.
-   Useful for large numerical keys.

### Disadvantages

-   Different keys can generate the same sum.
-   Similar group patterns may cause collisions.
-   Distribution depends on key structure.

## 11.2 Fold-Boundary Method

In Fold-Boundary, divide the key into equal-sized groups and reverse
alternate groups before adding them.

Example:

\[ key=123456789,`\quad `{=tex}m=1000 \]

Divide:

``` text
123 | 456 | 789
```

Reverse the second group, keeping the first and third unchanged:

``` text
123 | 654 | 789
```

Add:

\[ 123+654+789=1566 \]

Apply modulo:

\[ h(key)=1566`\bmod1000`{=tex} \]

\[ `\boxed{h(key)=566}`{=tex} \]

Let (G_i) be the original groups and (R(G_i)) be the reversal of a
group.

For the convention where alternate groups are reversed:

\[ S=G_1+R(G_2)+G_3+R(G_4)+`\cdots`{=tex} \]

\[ `\boxed{h(key)=S\bmod m}`{=tex} \]

### Advantages

-   Uses groups in different orientations.
-   Can reduce some repetitive group patterns.
-   Straightforward to perform manually.

### Disadvantages

-   Requires a reversal operation.
-   Different keys can still produce identical sums.
-   Does not guarantee collision-free hashing.

**Course note:** Folding conventions can vary between textbooks. Follow
the grouping direction and alternate-reversal convention specified by
your instructor.

## 11.3 Fold-Shifting vs Fold-Boundary

Use the same key:

\[ key=123456789,`\quad `{=tex}m=1000 \]

  Feature                     Fold-Shifting     Fold-Boundary
  --------------------------- ----------------- -----------------
  Groups                      123, 456, 789     123, 456, 789
  Reverse alternate groups?   No                Yes
  Groups added                123 + 456 + 789   123 + 654 + 789
  Sum                         1368              1566
  Modulo                      1368 % 1000       1566 % 1000
  Final index                 **368**           **566**

Visual flow:

``` text
              ORIGINAL KEY
              123456789
                   |
            DIVIDE INTO GROUPS
                   |
             123 | 456 | 789
                   |
          +--------+---------+
          |                  |
     FOLD-SHIFTING      FOLD-BOUNDARY
          |                  |
     123+456+789       123+654+789
          |                  |
        1368               1566
          |                  |
       % 1000              % 1000
          |                  |
        368                 566
```

# 12. Comparison of Hashing Methods

  -----------------------------------------------------------------------
  Method                  Main operation          Hash generation
  ----------------------- ----------------------- -----------------------
  Division                Modulo                  Remainder

  Digit Extraction        Digit selection         Selected digits

  Mid-Square              Squaring                Middle digits

  Fold-Shifting           Grouping and addition   Sum of original groups

  Fold-Boundary           Grouping, reversal and  Sum of alternate
                          addition                reversed groups
  -----------------------------------------------------------------------

No method guarantees perfect distribution for every dataset.

# 13. Collisions

A collision occurs when two different keys generate the same hash index.

Mathematically:

\[ K_1`\neq `{=tex}K_2 \]

but:

\[ `\boxed{h(K_1)=h(K_2)}`{=tex} \]

Example:

\[ h(key)=key`\bmod10`{=tex} \]

For keys 15 and 25:

\[ 15`\bmod10`{=tex}=5 \]

\[ 25`\bmod10`{=tex}=5 \]

Both map to index 5.

## Collision resolution techniques

### Separate Chaining

Each index stores a linked list or another collection of keys.

### Open Addressing

All keys are stored inside the hash table itself.

Common techniques:

1.  Linear Probing.
2.  Quadratic Probing.
3.  Double Hashing.

# 14. C++ Implementations

These examples demonstrate the mathematical methods. They are teaching
implementations, not complete production-grade hash tables.

## 14.1 Division Method

``` cpp
int divisionHash(int key, int m)
{
    return key % m;
}
```

Example:

``` cpp
cout << divisionHash(12345, 1000);
```

Output:

``` text
345
```

## 14.2 Power-of-2 Hashing Using Bitwise AND

``` cpp
int powerOfTwoHash(int key, int m)
{
    return key & (m - 1);
}
```

Requires a positive power-of-2 table size and a non-negative key.

Example:

``` cpp
cout << powerOfTwoHash(169, 8);
```

Output:

``` text
1
```

## 14.3 Digit Extraction

``` cpp
int digitExtraction(long long key)
{
    string s = to_string(key);

    return (s[2] - '0') * 100
         + (s[5] - '0') * 10
         + (s[8] - '0');
}
```

For `456378945`, output is `685`.

This example selects the 3rd, 6th and 9th digits from the left.

## 14.4 Mid-Square

``` cpp
int midSquareHash(long long key)
{
    long long sq = key * key;

    return (sq / 1000) % 1000;
}
```

Example:

``` cpp
cout << midSquareHash(12356);
```

Output:

``` text
670
```

This example assumes a nine-digit square and extracts its middle three
digits. A general implementation must determine the digit positions
based on the square length and desired index width. It must also guard
against overflow.

## 14.5 Fold-Shifting

``` cpp
int foldShifting(string key, int m)
{
    int sum = 0;

    for (int i = 0; i < key.size(); i += 3)
    {
        int group = stoi(key.substr(i, 3));
        sum += group;
    }

    return sum % m;
}
```

Example:

``` cpp
cout << foldShifting("123456789", 1000);
```

Output:

``` text
368
```

## 14.6 Fold-Boundary

``` cpp
int foldBoundary(string key, int m)
{
    int sum = 0;
    int groupNo = 0;

    for (int i = 0; i < key.size(); i += 3)
    {
        string group = key.substr(i, 3);

        if (groupNo % 2 == 1)
        {
            reverse(group.begin(), group.end());
        }

        sum += stoi(group);
        groupNo++;
    }

    return sum % m;
}
```

Example:

``` cpp
cout << foldBoundary("123456789", 1000);
```

Output:

``` text
566
```

These folding examples assume three-digit groups and non-negative
numerical keys represented as strings. A robust implementation should
handle partial groups, leading zeros, large sums and overflow.

# 15. Time and Space Complexity

Let:

-   \(n\) be the number of digits in the key.
-   \(g\) be the number of groups in folding.

  -----------------------------------------------------------------------
  Method                  Approximate time        Auxiliary space
                          complexity              
  ----------------------- ----------------------- -----------------------
  Division                (O(1)) for fixed-width  (O(1))
                          integers                

  Digit Extraction        (O(n)) for string-based (O(n))
                          extraction              

  Mid-Square              Depends on integer      Depends on
                          multiplication          representation

  Fold-Shifting           (O(n))                  (O(1)) with streaming
                                                  groups

  Fold-Boundary           (O(n))                  (O(1)) with fixed-size
                                                  group processing
  -----------------------------------------------------------------------

These complexities describe hash-index calculation, not complete
hash-table operations.

With good distribution and suitable collision handling, average lookup,
insertion and deletion can be (O(1)). Worst-case performance can be
(O(n)).

# 16. Common Mistakes and Important Observations

1.  Table size and maximum index are different. If (m=1000), valid
    indices are 0 through 999.
2.  Modulo returns the remainder, not the quotient.
3.  LSB is the rightmost bit.
4.  MSB is the leftmost bit.
5.  If (m=2\^k), the last (k) bits determine the modulo index.
6.  Different keys can have the same last (k) bits.
7.  Prime table sizes can reduce certain patterns but cannot eliminate
    all collisions.
8.  Digit Extraction depends on the positions selected.
9.  Mid-Square requires squaring before extracting middle digits.
10. Fold-Shifting adds groups without reversing them.
11. Fold-Boundary reverses alternate groups before adding them.
12. Apply modulo when the folded sum exceeds the table's valid index
    range.
13. A hash function should be deterministic and distribute keys
    uniformly.
14. Folding conventions can vary between textbooks; follow the
    convention taught in your course.

# 17. Practice Problems

Try solving these without looking at the notes.

## A. Division Method

1.  Calculate the hash index for key 4567 when (m=100).
2.  Calculate the hash index for key 12345 when (m=1000).
3.  What happens when all keys are multiples of the table size?

## B. Power-of-2 Table Size

4.  If (m=32), how many LSB bits are required?
5.  Find the hash index of 77 when (m=16).
6.  Do keys 9, 17, 25 and 33 collide when (m=8)? Explain.

## C. Digit Extraction

7.  For key 987654321, extract the 2nd, 5th and 8th digits from the
    left.
8.  Explain why selecting useful digit positions is important.

## D. Mid-Square

9.  Calculate the square of 123.
10. Extract the middle three digits from (123\^2).
11. Why can squaring large keys cause implementation problems?

## E. Folding

12. Apply Fold-Shifting to 987654321 with three-digit groups and
    (m=1000).
13. Apply Fold-Boundary to the same key.
14. Explain the difference between the two methods.
15. If the folded sum is 1912 and (m=1000), find the hash index.

# 18. Quick Revision

## Important formulas

**Division Method**

\[ `\boxed{h(key)=key\bmod m}`{=tex} \]

**Power-of-2 Table Size**

\[ `\boxed{m=2^k}`{=tex} \]

**Number of Bits**

\[ `\boxed{k=\log_2m}`{=tex} \]

**LSB-Based Hashing**

\[ `\boxed{h(key)=key\bmod2^k}`{=tex} \]

**Bitwise AND Equivalent**

\[ `\boxed{h(key)=key\ \&\ (m-1)}`{=tex} \]

**Digit Extraction**

\[ `\boxed{h(key)=\text{Selected Digits}}`{=tex} \]

**Mid-Square**

\[ `\boxed{h(key)=\text{Middle Digits of }key^2}`{=tex} \]

**Fold-Shifting**

\[ `\boxed{h(key)=\left(\sum G_i\right)\bmod m}`{=tex} \]

**Fold-Boundary**

\[ `\boxed{
h(key)=
\left(
G_1+R(G_2)+G_3+R(G_4)+\cdots
\right)\bmod m
}`{=tex} \]

Here, (R(G_i)) represents reversal of a group.

## Final Conceptual Summary

Hashing converts keys into hash table indices.

-   **Division:** Uses the remainder.
-   **Digit Extraction:** Selects specific digits.
-   **Mid-Square:** Squares the key and extracts middle digits.
-   **Fold-Shifting:** Divides the key into groups and adds them.
-   **Fold-Boundary:** Reverses alternate groups and adds them.

A good hash function should distribute keys uniformly and minimize
collisions. Power-of-2 sizes allow efficient bitwise indexing but can
expose lower-bit patterns. Prime table sizes can reduce certain
systematic modulo patterns.

**The ultimate objective of hashing is efficient insertion, searching
and deletion by distributing keys effectively across the hash table.**

------------------------------------------------------------------------

*End of Hashing Notes --- Hash Function Design and Hashing Methods.*
