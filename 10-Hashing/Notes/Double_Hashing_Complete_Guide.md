# Double Hashing — Complete DSA Notes

## 1. Introduction to hashing

Hashing stores keys in a hash table. A hash function converts a key into an array index.

For a table of size \(M=11\), a simple hash function is:

\[
h(k)=k\bmod 11
\]

A **collision** occurs when two different keys map to the same index. Double hashing is one method of resolving collisions in an open-addressing hash table.

## 2. What is Double Hashing?

**Double Hashing is an open-addressing collision-resolution technique that uses two hash functions to determine the sequence of positions to probe when a collision occurs.**

- The first hash function determines the key's initial index.
- The second hash function determines the step size between probes.
- If the initial position is occupied, the algorithm moves through the table using that step size.

The general probe formula is:

\[
\boxed{h(k,i)=(h_1(k)+i\cdot h_2(k))\bmod M}
\]

where:

- \(k\) = key
- \(i=0,1,2,\ldots\) = probe number
- \(M\) = table size
- \(h_1(k)\) = initial hash index
- \(h_2(k)\) = probe step size

At \(i=0\), the position is simply \(h_1(k)\).

## 3. Why do we need two hash functions?

Suppose many keys have the same initial hash index. Linear probing would check consecutive positions, which can create primary clustering.

Double hashing uses a key-dependent step size. Different keys can follow different probe sequences, reducing clustering.

It is still open addressing: every key is stored directly in the table, not in a linked list.

## 4. Hash functions used in this guide

We will use a table of prime size:

\[
M=11
\]

Choose:

\[
h_1(k)=k\bmod 11
\]

\[
h_2(k)=1+(k\bmod 10)
\]

The second function produces a step size from 1 through 10, so it is never zero.

**Important:** For a table size \(M\), the step size must be relatively prime to \(M\) so that the probe sequence can visit every table position. When \(M\) is prime, any step from 1 to \(M-1\) is relatively prime to \(M\).

## 5. Worked example

Insert the following keys in order:

\[
22,\ 1,\ 13,\ 11,\ 24,\ 33,\ 44
\]

with \(M=11\), \(h_1(k)=k\bmod11\), and \(h_2(k)=1+(k\bmod10)\).

### Step 1 — Calculate the two hash functions

| Key | \(h_1(k)\) | \(h_2(k)\) |
|---:|---:|---:|
| 22 | 0 | 3 |
| 1 | 1 | 2 |
| 13 | 2 | 4 |
| 11 | 0 | 2 |
| 24 | 2 | 5 |
| 33 | 0 | 4 |
| 44 | 0 | 5 |

### Step 2 — Insert each key

The probe formula is:

\[
h(k,i)=(h_1(k)+i\cdot h_2(k))\bmod11
\]

**Insert 22**

\[
h_1(22)=0
\]

Index 0 is empty. Store 22 at index 0.

**Insert 1**

\[
h_1(1)=1
\]

Index 1 is empty. Store 1 at index 1.

**Insert 13**

\[
h_1(13)=2
\]

Index 2 is empty. Store 13 at index 2.

**Insert 11**

\[
h_1(11)=0,\qquad h_2(11)=2
\]

Index 0 is occupied. Try the next probe:

\[
h(11,1)=(0+1\cdot2)\bmod11=2
\]

Index 2 is occupied. Try again:

\[
h(11,2)=(0+2\cdot2)\bmod11=4
\]

Index 4 is empty. Store 11 at index 4.

**Insert 24**

\[
h_1(24)=2,\qquad h_2(24)=5
\]

Index 2 is occupied:

\[
h(24,1)=(2+5)\bmod11=7
\]

Index 7 is empty. Store 24 at index 7.

**Insert 33**

\[
h_1(33)=0,\qquad h_2(33)=4
\]

Index 0 is occupied:

\[
h(33,1)=(0+4)\bmod11=4
\]

Index 4 is occupied:

\[
h(33,2)=(0+2\cdot4)\bmod11=8
\]

Index 8 is empty. Store 33 at index 8.

**Insert 44**

\[
h_1(44)=0,\qquad h_2(44)=5
\]

Index 0 is occupied:

\[
h(44,1)=(0+5)\bmod11=5
\]

Index 5 is empty. Store 44 at index 5.

### Step 3 — Final hash table

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Key | 22 | 1 | 13 | EMPTY | 11 | 44 | EMPTY | 24 | 33 | EMPTY | EMPTY |

\[
\boxed{[22,\ 1,\ 13,\ -,\ 11,\ 44,\ -,\ 24,\ 33,\ -,\ -]}
\]

Here `-` means an empty slot.

## 6. Searching in Double Hashing

To search for key \(k\), follow exactly the same probe sequence used during insertion:

\[
(h_1(k)+i\cdot h_2(k))\bmod M
\]

At each position:

1. If the key is found, report success.
2. If the slot is EMPTY, the key is not present; stop.
3. If the slot is OCCUPIED by another key or is DELETED, continue probing.

Example: Search for 33.

\[
h_1(33)=0,\qquad h_2(33)=4
\]

Probe sequence:

- \(i=0\): index 0 contains 22.
- \(i=1\): index 4 contains 11.
- \(i=2\): index 8 contains 33.

The key is found at index 8.

## 7. Deletion and tombstones

In open addressing, simply making a deleted slot EMPTY can break a later search.

Example: suppose a key was inserted after probing past an occupied slot. If that earlier slot is changed to EMPTY, a search may stop there and incorrectly conclude that the later key does not exist.

Therefore, deletion uses a special marker called a **tombstone** or DELETED state.

A slot has three possible states:

- EMPTY: never occupied; search can stop here.
- OCCUPIED: contains a key.
- DELETED: previously contained a key; search must continue through it.

During insertion, a tombstone may be reused, but the implementation must continue probing far enough to ensure the same key is not already stored later in the sequence.

## 8. Time and space complexity

Let \(n\) be the number of stored keys and \(M\) the table capacity.

| Operation | Expected time | Worst case |
|---|---:|---:|
| Hash calculation | \(O(1)\) | \(O(1)\) |
| Search | \(O(1)\) under a suitable load factor and hashing | \(O(M)\) |
| Insert | \(O(1)\) under a suitable load factor and hashing | \(O(M)\) |
| Delete | \(O(1)\) under a suitable load factor and hashing | \(O(M)\) |

- **Space complexity:** \(O(M)\) for the table.
- Each operation may examine many positions when the table is nearly full.
- Expected constant time depends on a suitable hash design and a controlled load factor; it is not guaranteed for every input.

### Load factor

\[
\alpha=\frac{n}{M}
\]

It measures how full the table is. As the load factor approaches 1, finding an empty slot generally becomes harder.

## 9. Advantages

1. Reduces primary clustering compared with linear probing.
2. Uses the key-dependent second hash function to generate probe sequences.
3. Stores keys directly in the array.
4. Does not require linked lists.
5. Can provide expected \(O(1)\) operations when the load factor is controlled.

## 10. Disadvantages

1. More computation than linear probing because two hash functions are evaluated.
2. Poor hash functions can produce poor probe sequences.
3. Deletion requires tombstones to preserve search correctness.
4. Performance degrades as the table becomes full.
5. The step size must be chosen carefully; otherwise, the probe sequence may not reach every slot.

## 11. Double Hashing versus other techniques

| Technique | Probe sequence |
|---|---|
| Linear probing | \((h(k)+i)\bmod M\) |
| Quadratic probing | \((h(k)+c_1i+c_2i^2)\bmod M\) |
| Double hashing | \((h_1(k)+i\cdot h_2(k))\bmod M\) |

## 12. Important examination points

- Double Hashing is an open-addressing technique.
- It uses two hash functions.
- \(h_1(k)\) gives the initial index.
- \(h_2(k)\) gives the probe step size.
- The probe formula is \((h_1(k)+i\cdot h_2(k))\bmod M\).
- The second hash function must not produce zero.
- Ideally, the step size is relatively prime to the table size.
- Choosing a prime table size and a step in \(1,\ldots,M-1\) guarantees a full probe cycle.
- Deletion should use a tombstone, not simply mark the slot EMPTY.
- Expected search and insertion can be \(O(1)\); worst case is \(O(M)\).

**One-line exam definition:** Double Hashing is an open-addressing collision-resolution technique in which a second hash function determines the step size used to probe for another available position.
