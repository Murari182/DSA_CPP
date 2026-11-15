# Quadratic Probing — Complete DSA Notes

## 1. Introduction to hashing

Hashing stores keys in a hash table by converting each key into an array index.

A hash function may be:

$$

h(k)=k\bmod M

$$

where $M$ is the table size.

A collision occurs when two different keys map to the same index. Quadratic Probing is an open-addressing technique used to resolve collisions.

## 2. What is Quadratic Probing?

**Quadratic Probing is an open-addressing collision-resolution technique in which the next positions are calculated using quadratic offsets from the original hash index.**

Instead of checking the next slot one by one, it uses a quadratic expression to calculate the probe positions.

A common formula is:

$$

\boxed{h(k,i)=(h(k)+i^2)\bmod M}

$$

where:

- $k$ = key
- $i$ = probe number, starting from 0
- $M$ = hash-table size
- $h(k)$ = original hash index

A more general formula is:

$$

\boxed{h(k,i)=(h(k)+c_1i+c_2i^2)\bmod M}

$$

where $c_1$ and $c_2$ are constants selected by the implementation.

In this guide, we use the simpler form:

$$

h(k,i)=(h(k)+i^2)\bmod M

$$

## 3. Why is it called Quadratic Probing?

The probe offset is based on the square of the probe number:

$$

0^2,\ 1^2,\ 2^2,\ 3^2,\ 4^2,\ldots

$$

So the offsets are:

$$

0,\ 1,\ 4,\ 9,\ 16,\ldots

$$

After applying modulo $M$, these offsets generate the positions to check.

For example, if $h(k)=3$ and $M=11$, the first positions are:

- $i=0$: $(3+0)\bmod11=3$
- $i=1$: $(3+1)\bmod11=4$
- $i=2$: $(3+4)\bmod11=7$
- $i=3$: $(3+9)\bmod11=1$
- $i=4$: $(3+16)\bmod11=8$

The sequence is 3, 4, 7, 1, 8, ...

## 4. Quadratic Probing versus Linear Probing

| Feature | Linear Probing | Quadratic Probing |
|---|---|---|
| Probe formula | $(h(k)+i)\bmod M$ | $(h(k)+i^2)\bmod M$ |
| Next position | Consecutive slot | Quadratic offset |
| Primary clustering | Suffers from it | Reduces primary clustering |
| Secondary clustering | Keys with same initial hash follow same sequence | Also occurs for keys with the same initial hash |
| Implementation | Very simple | Simple, but probe coverage needs care |

**Remember:** Linear Probing moves one slot at a time. Quadratic Probing moves by square-number offsets.

## 5. Worked example

Use:

$$

M=11

$$

$$

h(k)=k\bmod11

$$

$$

h(k,i)=(h(k)+i^2)\bmod11

$$

Insert these keys in order:

$$

22,\ 1,\ 13,\ 11,\ 24,\ 33,\ 44

$$

### Step 1 — Calculate the initial hash index

| Key | Calculation | Initial index |
|---:|---|---:|
| 22 | $22\bmod11$ | 0 |
| 1 | $1\bmod11$ | 1 |
| 13 | $13\bmod11$ | 2 |
| 11 | $11\bmod11$ | 0 |
| 24 | $24\bmod11$ | 2 |
| 33 | $33\bmod11$ | 0 |
| 44 | $44\bmod11$ | 0 |

### Step 2 — Insert each key

**Insert 22**

$$

h(22)=22\bmod11=0

$$

Index 0 is empty. Store 22 at index 0.

**Insert 1**

$$

h(1)=1

$$

Index 1 is empty. Store 1 at index 1.

**Insert 13**

$$

h(13)=2

$$

Index 2 is empty. Store 13 at index 2.

**Insert 11**

$$

h(11)=0

$$

Index 0 is occupied by 22.

Try $i=1$:

$$

h(11,1)=(0+1^2)\bmod11=1

$$

Index 1 is occupied by 1.

Try $i=2$:

$$

h(11,2)=(0+2^2)\bmod11=4

$$

Index 4 is empty. Store 11 at index 4.

**Insert 24**

$$

h(24)=2

$$

Index 2 is occupied by 13.

Try $i=1$:

$$

h(24,1)=(2+1)\bmod11=3

$$

Index 3 is empty. Store 24 at index 3.

**Insert 33**

$$

h(33)=0

$$

Index 0 is occupied.

- $i=1$: $(0+1)\bmod11=1$, occupied.
- $i=2$: $(0+4)\bmod11=4$, occupied.
- $i=3$: $(0+9)\bmod11=9$, empty.

Store 33 at index 9.

**Insert 44**

$$

h(44)=0

$$

Index 0 is occupied.

- $i=1$: index 1, occupied.
- $i=2$: index 4, occupied.
- $i=3$: index 9, occupied.
- $i=4$: $(0+16)\bmod11=5$, empty.

Store 44 at index 5.

### Step 3 — Final hash table

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Key | 22 | 1 | 13 | 24 | 11 | 44 | EMPTY | EMPTY | EMPTY | 33 | EMPTY |

$$

\boxed{[22,\ 1,\ 13,\ 24,\ 11,\ 44,\ -,\ -,\ -,\ 33,\ -]}

$$

Here `-` represents an empty slot.

## 6. Searching in Quadratic Probing

Searching follows the same quadratic probe sequence used during insertion:

$$

h(k,i)=(h(k)+i^2)\bmod M

$$

Example: Search for 33.

$$

h(33)=0

$$

Check the sequence:

- $i=0$: index 0 contains 22.
- $i=1$: index 1 contains 1.
- $i=2$: index 4 contains 11.
- $i=3$: index 9 contains 33.

The key is found at index 9.

If an EMPTY slot is reached, the key is not present. A DELETED slot does not stop the search.

## 7. Deletion and tombstones

As with other open-addressing techniques, deletion must preserve the probe sequence.

Use three slot states:

- EMPTY: the slot has never been occupied; search may stop.
- OCCUPIED: the slot contains a key.
- DELETED: a key was removed; search must continue.

If a deleted slot were changed directly to EMPTY, a search for a key placed farther along the probe sequence could stop too early.

During insertion, remember the first DELETED slot, but continue probing to check for a duplicate before reusing it.

## 8. Primary and secondary clustering

### Primary clustering

Primary clustering occurs when long groups of occupied consecutive slots form. Linear Probing is particularly vulnerable because keys that collide tend to extend the same cluster.

Quadratic Probing reduces primary clustering because it does not move through consecutive positions.

### Secondary clustering

Quadratic Probing still has secondary clustering.

Keys with the same initial hash value follow the same quadratic probe sequence. Therefore, they can still compete for the same positions.

Double Hashing reduces this effect because the step size depends on the key.

## 9. Important limitation: probe coverage

Quadratic Probing does **not necessarily visit every table position**.

For example, with $M=11$ and the simple formula $h(k,i)=(h(k)+i^2)\bmod11$, the offsets repeat after a limited number of distinct positions.

Therefore, even if some slots in the table are empty, a particular probe sequence may fail to reach them.

Common textbook approaches use a prime table size and keep the load factor at or below about 0.5 for the simple $i^2$ method. The exact guarantee depends on the chosen formula and table-size assumptions.

A failed probe sequence may require resizing or rehashing.

## 10. Time and space complexity

Let $n$ be the number of stored keys and $M$ the table size.

| Operation | Expected time | Worst case |
|---|---:|---:|
| Hash calculation | $O(1)$ | $O(1)$ |
| Search | $O(1)$ under suitable load assumptions | $O(M)$ |
| Insert | $O(1)$ under suitable load assumptions | $O(M)$ |
| Delete | $O(1)$ under suitable load assumptions | $O(M)$ |

- **Space complexity:** $O(M)$ for the table.
- Expected performance depends on the load factor and the probe formula.
- A probe sequence may not cover all slots, so insertion can fail even while some table slots are empty.

### Load factor

$$

\alpha=\frac{n}{M}

$$

For the simple quadratic probing method, keeping the load factor low helps reduce insertion failures and long probe sequences.

## 11. Advantages

1. Reduces primary clustering compared with linear probing.
2. Does not require linked lists.
3. Stores keys directly in the hash table.
4. Uses a simple mathematical probe formula.
5. Can provide expected constant-time operations at a suitable load factor.

## 12. Disadvantages

1. Secondary clustering still occurs.
2. The probe sequence may not visit every table position.
3. Performance degrades as the table becomes full.
4. Deletion requires tombstones.
5. Table size and probe constants must be selected carefully.

## 13. Comparison of collision-resolution techniques

| Technique | How it resolves collision |
|---|---|
| Linear Probing | Checks the next slot sequentially |
| Quadratic Probing | Checks positions using quadratic offsets |
| Double Hashing | Uses a second hash function as the step size |
| Cuckoo Hashing | Displaces an existing key to its alternative hash position |
| Separate Chaining | Stores colliding keys in a linked structure or bucket |

## 14. Important examination points

- Quadratic Probing is an open-addressing technique.
- It resolves collisions using quadratic offsets.
- The common formula is $(h(k)+i^2)\bmod M$.
- The general formula is $(h(k)+c_1i+c_2i^2)\bmod M$.
- It reduces primary clustering.
- It still suffers from secondary clustering.
- Its probe sequence may not cover the entire table.
- Deletion should use a tombstone.
- Expected operations can be $O(1)$ under suitable assumptions; worst case is $O(M)$.
- Space complexity is $O(M)$.

**One-line exam definition:** Quadratic Probing is an open-addressing collision-resolution technique that uses quadratic functions of the probe number to generate alternative positions in a hash table.
