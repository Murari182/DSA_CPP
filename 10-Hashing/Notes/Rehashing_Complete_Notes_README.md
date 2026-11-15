# Rehashing in Hash Tables — Complete DSA Notes

> A detailed, exam-ready and interview-oriented guide to rehashing, with worked examples, collision handling, load factor, C++ implementation logic, and time/space complexity.

This note is a deep-dive companion for the hashing section in this repository. It focuses on when and why rehashing is needed, how it affects the load factor, and how it fits into common collision-resolution techniques.

## Related Hashing Notes

- [Hashing_Complete_Notes.md](./Hashing_Complete_Notes.md)
- [Hash_Functions_and_Hashing_Techniques.md](./Hash_Functions_and_Hashing_Techniques.md)
- [Direct_Adressing in_Hashing.md](./Direct_Adressing%20in_Hashing.md)
- [Double_Hashing_Complete_Guide.md](./Double_Hashing_Complete_Guide.md)
- [Quadratic_Probing_Complete_Guide.md](./Quadratic_Probing_Complete_Guide.md)
- [Cuckoo_Hashing_Complete_Guide.md](./Cuckoo_Hashing_Complete_Guide.md)

------------------------------------------------------------------------

## Table of Contents

1.  [What Is Rehashing?](#1-what-is-rehashing)
2.  [Why Do We Need Rehashing?](#2-why-do-we-need-rehashing)
3.  [Hash Table Terminology](#3-hash-table-terminology)
4.  [Load Factor](#4-load-factor)
5.  [When Is Rehashing Triggered?](#5-when-is-rehashing-triggered)
6.  [Rehashing: Step-by-Step Working](#6-rehashing-step-by-step-working)
7.  [Complete Worked Example](#7-complete-worked-example)
8.  [Rehashing With Collision-Resolution
    Techniques](#8-rehashing-with-collision-resolution-techniques)
9.  [Rehashing Algorithm and
    Pseudocode](#9-rehashing-algorithm-and-pseudocode)
10. [C++ Implementation Example](#10-c-implementation-example)
11. [Time Complexity --- Detailed
    Analysis](#11-time-complexity--detailed-analysis)
12. [Space Complexity --- Detailed
    Analysis](#12-space-complexity--detailed-analysis)
13. [Amortized Analysis of
    Insertion](#13-amortized-analysis-of-insertion)
14. [Rehashing vs. Resizing vs. Collision
    Resolution](#14-rehashing-vs-resizing-vs-collision-resolution)
15. [Important Edge Cases and Implementation
    Notes](#15-important-edge-cases-and-implementation-notes)
16. [Advantages and Disadvantages](#16-advantages-and-disadvantages)
17. [Exam and Interview Points](#17-exam-and-interview-points)
18. [Practice Questions](#18-practice-questions)
19. [Quick Revision Sheet](#19-quick-revision-sheet)

------------------------------------------------------------------------

## 1. What Is Rehashing?

**Rehashing is the process of creating a new hash table (usually with a
larger capacity) and inserting all existing keys into that new table
again by recalculating their hash-table positions.**

The key idea is:

-   The table's capacity changes.
-   The hash index of an existing key may change.
-   Every existing key must be placed again according to the new table's
    indexing rule.
-   The collision-resolution method must be applied again if a collision
    occurs.

### A simple analogy

Imagine a car park with 5 parking spaces. As more cars arrive, the
parking area becomes crowded. You expand it to 11 spaces.

You cannot assume that every car should remain in the same numbered
space. The parking allocation rule may depend on the total number of
spaces. Therefore, you assign every car a valid position again.

That is the basic idea of rehashing.

### Important distinction

Rehashing is **not itself a collision-resolution technique**.

-   Linear probing, quadratic probing, double hashing and separate
    chaining are collision-handling approaches.
-   Rehashing is a table-maintenance strategy that rebuilds the table,
    commonly to reduce the load factor and improve performance.

------------------------------------------------------------------------

## 2. Why Do We Need Rehashing?

A hash table is designed to provide fast operations.

With a well-distributed hash function and a controlled load factor,
search, insertion and deletion are typically expected to take $O(1)$
time.

However, as more keys are inserted into a fixed-capacity table:

1.  The load factor increases.
2.  More positions become occupied.
3.  Collisions may become more frequent.
4.  Open-addressing methods may need to probe many positions.
5.  Search and insertion can become slower.

Rehashing helps by increasing the table capacity and redistributing the
existing keys.

### What happens without rehashing?

Suppose a table has capacity 5 and uses:

$$
h(k) = k \bmod 5
$$

Insert the keys:

`10, 15, 20, 25`

All four keys have the same initial hash index:

| Key | Calculation | Initial index |
|---:|---|---:|
| 10 | $10 \bmod 5$ | 0 |
| 15 | $15 \bmod 5$ | 0 |
| 20 | $20 \bmod 5$ | 0 |
| 25 | $25 \bmod 5$ | 0 |

With linear probing, they occupy positions 0, 1, 2 and 3.

The table is already 80% full:

$$
\alpha = \frac{4}{5} = 0.8
$$

A high load factor can make open-addressed operations expensive.

**Rehashing does not guarantee that every collision disappears.** It
gives the table more room and may distribute the keys better when the
new capacity changes the hash indices.

------------------------------------------------------------------------

## 3. Hash Table Terminology

Before studying rehashing, understand these terms.

| Symbol / term | Meaning |
|---|---|
| $n$ | Number of stored keys/elements |
| $m$ | Current capacity of the hash table |
| $m'$ | New capacity after resizing |
| $h(k)$ | Hash function for key $k$ |
| $\alpha$ | Load factor |
| Collision | Two or more keys map to the same initial index |

For a basic hash table:

$$
\alpha = \frac{n}{m}
$$

For example, if 6 keys are stored in a table of capacity 10:

$$
\alpha = \frac{6}{10} = 0.6
$$

So the table is 60% full.

> For open addressing, the load factor is usually the fraction of slots
> occupied. For separate chaining, it is the average number of keys per
> bucket and can be greater than 1.

------------------------------------------------------------------------

## 4. Load Factor

The **load factor** measures how full a hash table is.

$$
\boxed{\alpha = \frac{\text{Number of stored elements}}{\text{Hash table capacity}}}
$$

### Example

Capacity = 10

Number of stored elements = 7

$$
\alpha = \frac{7}{10} = 0.7
$$

The load factor is 0.7, or 70%.

### Why does load factor matter?

For open addressing, as the load factor approaches 1, fewer empty slots
remain. A probe sequence may have to inspect more positions before
finding an empty slot or a key.

For separate chaining, a higher load factor means more keys on average
in each bucket, so bucket searches can become longer.

### Maximum load-factor threshold

A hash table implementation can define a threshold called the **maximum
load factor**.

For example:

$$
\alpha_{\max} = 0.75
$$

A common policy is to rehash when the projected load factor after an
insertion exceeds this threshold.

Suppose:

-   Current capacity = 10
-   Current number of elements = 7
-   Maximum load factor = 0.75

Before insertion:

$$
\alpha = \frac{7}{10} = 0.7
$$

After inserting one more key:

$$
\alpha_{\text{new}} = \frac{8}{10} = 0.8
$$

Since:

$$
0.8 > 0.75
$$

the implementation triggers rehashing.

**Important:** 0.75 is an example, not a universal rule. The threshold
depends on the implementation and collision-resolution strategy.

------------------------------------------------------------------------

## 5. When Is Rehashing Triggered?

A common policy is:

1.  Calculate the projected number of elements after insertion.
2.  Calculate the projected load factor.
3.  Compare it with the maximum allowed load factor.
4.  If it exceeds the threshold, grow and rebuild the table.
5.  Insert the new key into the rebuilt table.

The condition can be written as:

$$
\frac{n+1}{m} > \alpha_{\max}
$$

where $n$ is the current number of elements and $m$ is the current
capacity.

Some implementations check the threshold at a slightly different point,
but the principle is the same.

### Example

| Current elements | Capacity | Projected elements | Projected load factor | Action (threshold = 0.75) |
|---:|---:|---:|---:|---|
| 3 | 10 | 4 | 0.4 | No rehash |
| 5 | 10 | 6 | 0.6 | No rehash |
| 7 | 10 | 8 | 0.8 | Rehash |
| 8 | 10 | 9 | 0.9 | Rehash should already have happened |

------------------------------------------------------------------------

## 6. Rehashing: Step-by-Step Working

Suppose the old table has capacity $m=5$, and the new table has capacity
$m'=11$.

Old hash function:

$$
h_{\text{old}}(k) = k \bmod 5
$$

New hash function:

$$
h_{\text{new}}(k) = k \bmod 11
$$

The rehashing procedure is:

1.  Allocate a new table with capacity 11.
2.  Initialize every new slot as empty.
3.  Traverse the old table.
4.  For each stored key, calculate its new index using the new capacity.
5.  Insert the key into the new table.
6.  If the new index is already occupied, use the chosen
    collision-resolution method.
7.  Once all keys have been moved, replace the old table with the new
    table.

### The most important rule

**Never simply copy keys into their old indices. Recalculate their
positions.**

The hash index depends on the capacity in this example:

$$
h(k) = k \bmod m
$$

When $m$ changes, the result can change.

------------------------------------------------------------------------

## 7. Complete Worked Example

Consider a hash table with:

-   Old capacity = 5
-   New capacity = 11
-   Collision resolution = Linear probing
-   Keys = `10, 15, 20, 25`

### 7.1 Before rehashing

Hash function:

$$
h(k) = k \bmod 5
$$

Insert the keys one by one.

**Insert 10**

$$
10 \bmod 5 = 0
$$

Place 10 at index 0.

**Insert 15**

$$
15 \bmod 5 = 0
$$

Index 0 is occupied. Linear probing checks index 1. Place 15 at index 1.

**Insert 20**

$$
20 \bmod 5 = 0
$$

Index 0 is occupied; index 1 is occupied; index 2 is empty. Place 20 at
index 2.

**Insert 25**

$$
25 \bmod 5 = 0
$$

Indices 0, 1 and 2 are occupied. Place 25 at index 3.

Old table:

| Index | Stored value |
|---:|---:|
| 0 | 10 |
| 1 | 15 |
| 2 | 20 |
| 3 | 25 |
| 4 | EMPTY |

Load factor:

$$
\alpha = \frac{4}{5} = 0.8
$$

### 7.2 Start rehashing

Create a new table of capacity 11.

New hash function:

$$
h_{\text{new}}(k) = k \bmod 11
$$

All new slots initially contain EMPTY.

### 7.3 Reinsert each old key

| Key | New hash calculation | New index |
|---:|---|---:|
| 10 | $10 \bmod 11$ | 10 |
| 15 | $15 \bmod 11$ | 4 |
| 20 | $20 \bmod 11$ | 9 |
| 25 | $25 \bmod 11$ | 3 |

None of these new indices collide, so all keys can be placed directly.

### 7.4 New table after rehashing

| Index | Stored value |
|---:|---:|
| 0 | EMPTY |
| 1 | EMPTY |
| 2 | EMPTY |
| 3 | 25 |
| 4 | 15 |
| 5 | EMPTY |
| 6 | EMPTY |
| 7 | EMPTY |
| 8 | EMPTY |
| 9 | 20 |
| 10 | 10 |

New load factor:

$$
\alpha = \frac{4}{11} \approx 0.364
$$

The load factor has reduced from 0.8 to approximately 0.364.

### 7.5 What did we learn?

-   The keys were not deleted.
-   Every key was inserted again.
-   Their positions were recalculated.
-   The capacity increased from 5 to 11.
-   The load factor decreased.
-   In this particular example, the new positions had no collisions.

A new table can still contain collisions. Rehashing reduces the pressure
caused by a high load factor; it does not promise collision-free
storage.

------------------------------------------------------------------------

## 8. Rehashing With Collision-Resolution Techniques

Rehashing is compatible with different collision-resolution techniques.
During rebuilding, the table must use the same intended
collision-handling policy (or a deliberately chosen replacement policy).

### 8.1 Separate Chaining

Each table index stores a bucket, often implemented as a linked list or
another container.

During rehashing:

1.  Create a larger bucket array.
2.  Visit every key in every old bucket.
3.  Compute its new bucket index.
4.  Insert it into the corresponding new bucket.

For separate chaining, the load factor may be greater than 1.

### 8.2 Linear Probing

A typical probe formula is:

$$
h(k,i) = (h(k)+i)\bmod m
$$

During rehashing:

-   Calculate the new initial hash index using the new capacity.
-   If it is occupied, try the next position.
-   Continue until an available slot is found.

### 8.3 Quadratic Probing

A typical formula is:

$$
h(k,i) = (h(k)+c_1i+c_2i^2)\bmod m
$$

During rehashing:

-   Recalculate the initial index with the new capacity.
-   Apply the quadratic probe sequence in the new table.
-   Place the key in the first valid available position.

### 8.4 Double Hashing

A typical formula is:

$$
h(k,i) = (h_1(k)+i\cdot h_2(k))\bmod m
$$

During rehashing:

-   Recalculate the first hash using the new table configuration.
-   Recalculate the step size as required.
-   Probe using the double-hashing formula until an available slot is
    found.

The second hash function and capacity must be designed so that the probe
sequence can reach the required slots. In particular, the step size
should be relatively prime to the table capacity for full coverage.

### 8.5 Cuckoo Hashing

Cuckoo hashing uses multiple hash functions and multiple candidate
tables/locations.

During a rebuild:

-   Allocate the new table or tables.
-   Recalculate candidate positions for every key.
-   Reinsert keys according to the cuckoo insertion procedure.
-   If insertion cycles or exceeds its displacement limit, the
    implementation may need another resize or a new hash-function seed.

**Do not confuse cuckoo hashing with ordinary open addressing:** cuckoo
hashing uses a different placement and displacement strategy.

------------------------------------------------------------------------

## 9. Rehashing Algorithm and Pseudocode

### High-level pseudocode

``` text
REHASH(new_capacity):

    old_table = current_table

    create new_table with new_capacity
    initialize all new_table slots as EMPTY

    for each slot in old_table:
        if slot contains a valid key:
            key = slot.key
            new_index = hash(key, new_capacity)

            insert key into new_table
            using the collision-resolution method

    current_table = new_table
    capacity = new_capacity
```

### Important implementation detail

If the old table uses open addressing and supports deletion with
tombstones:

-   Reinsert only genuinely occupied entries.
-   Do not reinsert EMPTY slots.
-   Do not reinsert DELETED/tombstone markers.
-   Reset the new table's occupied count and deleted count
    appropriately.

A tombstone is a marker used to preserve probe-chain correctness after
deletion. It is not a stored key and should not survive as a tombstone
in the rebuilt table.

------------------------------------------------------------------------

## 10. C++ Implementation Example

The following is a simplified educational implementation using linear
probing and `vector<int>`. It uses `-1` as the EMPTY marker, so it
assumes `-1` is not a valid key. A production implementation should use
a separate occupancy state or an optional value instead.

``` cpp
#include <iostream>
#include <vector>
using namespace std;

class HashTable
{
private:
    vector<int> table;
    int capacity;
    int size;
    double maxLoadFactor;

    int hashFunction(int key) const
    {
        // Handles negative keys as well.
        return ((key % capacity) + capacity) % capacity;
    }

    void insertWithoutRehash(int key)
    {
        int index = hashFunction(key);

        // Linear probing
        while (table[index] != -1)
        {
            index = (index + 1) % capacity;
        }

        table[index] = key;
        size++;
    }

    void rehash()
    {
        vector<int> oldTable = table;

        capacity = capacity * 2 + 1;
        table.assign(capacity, -1);
        size = 0;

        for (int key : oldTable)
        {
            if (key != -1)
            {
                insertWithoutRehash(key);
            }
        }
    }

public:
    HashTable(int cap = 5, double threshold = 0.75)
    {
        capacity = cap;
        size = 0;
        maxLoadFactor = threshold;
        table.assign(capacity, -1);
    }

    void insert(int key)
    {
        // Check whether the next insertion would exceed the threshold.
        if (static_cast<double>(size + 1) / capacity > maxLoadFactor)
        {
            rehash();
        }

        insertWithoutRehash(key);
    }

    void display() const
    {
        for (int i = 0; i < capacity; i++)
        {
            cout << i << " : ";

            if (table[i] == -1)
                cout << "EMPTY";
            else
                cout << table[i];

            cout << '\n';
        }
    }
};

int main()
{
    HashTable ht(5, 0.75);

    ht.insert(10);
    ht.insert(15);
    ht.insert(20);
    ht.insert(25);

    cout << "Hash table after insertions:\n";
    ht.display();

    return 0;
}
```

### Understanding the important functions

**`insert()`**

-   Checks the projected load factor.
-   Calls `rehash()` if the threshold would be exceeded.
-   Inserts the new key.

**`rehash()`**

-   Saves the old table.
-   Increases capacity.
-   Creates a fresh empty table.
-   Resets the element count.
-   Reinserts every valid old key.

**`insertWithoutRehash()`**

-   Calculates the index using the current capacity.
-   Uses linear probing if the position is occupied.
-   Does not call `rehash()` itself.

Why have a separate `insertWithoutRehash()`?

Because rehashing already knows it is rebuilding the table. If
reinsertion called the public `insert()` method, it could trigger
another rehash in the middle of rebuilding. Separating the internal
insertion routine makes the process easier to control.

> This example is intentionally minimal. It does not implement search,
> deletion, duplicate-key handling, tombstones, or a full-table failure
> policy. Those details must be added for a complete general-purpose
> hash table.

------------------------------------------------------------------------

## 11. Time Complexity --- Detailed Analysis

Let:

-   $m$ = old capacity
-   $m'$ = new capacity
-   $n$ = number of stored keys

Rehashing consists of multiple operations.

### 11.1 Creating the new table

If the new table has $m'$ slots and every slot is initialized:

$$
T_{\text{allocation and initialization}} = O(m')
$$

The exact allocation cost depends on the language and container, but
initializing all slots is linear in the new capacity.

### 11.2 Traversing the old table

If the old table has $m$ slots, every slot is checked:

$$
T_{\text{traversal}} = O(m)
$$

This is true even if only a few slots contain keys, because a basic
array-based implementation scans the entire table.

### 11.3 Reinserting the keys

There are $n$ valid keys.

With a good hash distribution and a controlled load factor, reinsertion
is expected to take:

$$
T_{\text{reinsertion}} = O(n)
$$

However, this is an expected/average-case statement, not a guarantee for
every input.

With severe clustering or pathological collisions, an individual
insertion can take $O(n)$, and reinserting all $n$ keys can take
$O(n^2)$ in the worst case.

### 11.4 Total time complexity

Combining the operations:

$$
T(n,m,m') = O(m') + O(m) + O(n)
$$

Therefore:

$$
\boxed{T_{\text{rehash}} = O(m+m'+n)}
$$

If the old and new capacities are both proportional to the number of
stored elements, this is commonly simplified to:

$$
\boxed{O(n)}
$$

Expected time is linear in the number of stored elements under normal
hashing assumptions and bounded load factor. Worst-case time can be
quadratic with poor collision behavior.

### Complexity summary

| Operation | Time complexity |
|---|---:|
| Allocate and initialize new table | $O(m')$ |
| Scan old table | $O(m)$ |
| Reinsert all keys - expected | $O(n)$ |
| Reinsert all keys - worst case | $O(n^2)$ |
| Complete rehash - expected with typical resizing | $O(n)$ |
| Complete rehash - possible worst case | $O(n^2)$ |

### Important exam trap

It is incomplete to say that rehashing is always $O(1)$.

-   One rehash operation is typically $O(n)$ expected time.
-   Ordinary insertion is expected $O(1)$ when no rehash is triggered.
-   Insertion that triggers a rehash can take $O(n)$.
-   Across many insertions, the amortized insertion time can still be
    $O(1)$ under geometric growth and suitable hashing assumptions.

------------------------------------------------------------------------

## 12. Space Complexity --- Detailed Analysis

Space complexity should distinguish the new table from temporary
storage.

### 12.1 New table

A new table with capacity $m'$ is allocated:

$$
O(m')
$$

### 12.2 Old table

The old table remains available while its keys are being moved:

$$
O(m)
$$

### 12.3 Temporary storage

The exact extra storage depends on the implementation.

-   If the old table itself is retained and the new table is allocated
    separately, both arrays coexist during rebuilding.
-   A copied `oldTable` vector, as in the simple C++ example, adds
    another $O(m)$ temporary array.
-   A carefully designed implementation may move or swap storage to
    avoid an unnecessary extra copy, but the old and new table storage
    still need to coexist during a conventional rebuild.

### 12.4 Total space

For a conventional implementation that keeps the old and new tables at
the same time:

$$
\boxed{O(m+m')}
$$

If the new capacity is proportional to the old capacity, this is often
written as:

$$
\boxed{O(m)}
$$

or, when capacity is proportional to the number of stored keys:

$$
\boxed{O(n)}
$$

### Space complexity summary

| Space used | Complexity |
|---|---:|
| New table | $O(m')$ |
| Old table retained during rebuild | $O(m)$ |
| Extra copied old table in the sample code | $O(m)$ |
| Conventional total peak table storage | $O(m+m')$ |

**Do not say that rehashing uses $O(1)$ extra space** for the standard
new-table approach. It needs storage for the rebuilt table.

------------------------------------------------------------------------

## 13. Amortized Analysis of Insertion

This is one of the most important interview concepts connected to
rehashing.

A single rehash can be expensive:

$$
O(n)
$$

Does that mean every insertion is $O(n)$?

**No.**

If the table grows geometrically (for example, doubles its capacity),
rehashing does not happen on every insertion. It happens only
occasionally.

### Example: doubling capacity

Suppose the table grows approximately as:

$$
1, 2, 4, 8, 16, 32,\ldots
$$

When capacity grows from 1 to 2, the existing keys are moved.

Later, when capacity grows from 2 to 4, the keys are moved again.

Then capacity grows from 4 to 8, and so on.

Across $N$ insertions, the total number of keys moved by all rebuilds is
bounded by a geometric sum:

$$
1+2+4+8+\cdots+2^k
$$

For the final capacity scale $2^k$:

$$
1+2+4+\cdots+2^k < 2^{k+1}
$$

This total is proportional to $N$, so the total rebuilding work across
$N$ insertions is $O(N)$.

The ordinary insertion work is also $O(N)$ in total under expected
constant-time hashing assumptions.

Therefore:

$$
\frac{O(N)}{N} = O(1)
$$

$$
\boxed{\text{Amortized insertion time} = O(1)}
$$

### Three different complexity statements

| Situation | Complexity |
|---|---|
| One insertion without rehash | Expected $O(1)$ |
| One insertion that triggers rehash | Expected $O(n)$ |
| A sequence of $N$ insertions with geometric growth | Amortized expected $O(1)$ per insertion |

Amortized analysis is about the total cost over a sequence of
operations. It does not mean every individual insertion is constant
time.

------------------------------------------------------------------------

## 14. Rehashing vs. Resizing vs. Collision Resolution

These terms are related but not identical.

| Concept | Meaning |
|---|---|
| Resizing | Changing the capacity of the hash table |
| Rehashing | Rebuilding the table and reinserting keys using recalculated positions |
| Collision resolution | Deciding where to place or search for a key when its initial index is occupied |

### Examples of collision-resolution techniques

-   Separate chaining
-   Linear probing
-   Quadratic probing
-   Double hashing
-   Cuckoo hashing (a distinct placement strategy)

### Key relationship

In many hash-table implementations, resizing is followed by rehashing.
In casual explanations, the terms are sometimes used interchangeably,
but technically resizing changes capacity while rehashing performs the
rebuild and redistribution.

------------------------------------------------------------------------

## 15. Important Edge Cases and Implementation Notes

### 15.1 Rehashing can still produce collisions

Changing capacity does not guarantee unique hash indices. The
collision-resolution method must still work.

### 15.2 Every valid key must be reinserted

Do not reinsert only the keys that previously collided. The hash
calculation may change for every key.

### 15.3 Deleted markers should not be copied as keys

In open addressing with tombstones, reinsert only occupied entries. A
rebuild naturally removes old tombstones.

### 15.4 Duplicate keys

If the table is a set/map, the implementation must preserve its
duplicate-key policy. Rehashing should not accidentally create duplicate
entries.

### 15.5 Negative keys

In C++, the `%` operator can produce a negative remainder. A
non-negative index can be calculated as:

``` cpp
int index = ((key % capacity) + capacity) % capacity;
```

### 15.6 Choosing the new capacity

Common strategies include:

-   Doubling the capacity.
-   Growing to a suitable larger prime number.
-   Using a growth policy selected by the hash-table implementation.

The best policy depends on the hash function and collision-resolution
strategy.

### 15.7 Hash functions with extra parameters

If the hash function depends on capacity, a seed, or other table
parameters, recalculate the index using the new configuration. For
double hashing, recalculate the step size too.

### 15.8 Allocation failure

A robust implementation should avoid losing the old table if allocation
of the new table fails. A safe approach is to build the new table
separately and replace the old table only after successful completion.

------------------------------------------------------------------------

## 16. Advantages and Disadvantages

### Advantages

1.  Reduces the load factor after growth.
2.  Helps control collision frequency.
3.  Improves expected search and insertion performance.
4.  Removes obsolete tombstones in many open-addressing implementations.
5.  Allows a hash table to grow dynamically.

### Disadvantages

1.  A single rehash can take linear expected time.
2.  It temporarily requires additional memory.
3.  All existing keys must be processed again.
4.  A poor hash function can still cause many collisions after
    rehashing.
5.  Frequent resizing can cause unnecessary overhead if the growth
    policy is poorly chosen.

------------------------------------------------------------------------

## 17. Exam and Interview Points

1.  Rehashing usually occurs when the load factor exceeds a chosen
    threshold.
2.  Rehashing commonly increases the table capacity.
3.  All existing valid keys are reinserted.
4.  New indices must be recalculated using the new
    capacity/configuration.
5.  Rehashing is not the same as linear probing or quadratic probing.
6.  Rehashing does not guarantee zero collisions.
7.  Expected time for one rehash is $O(n)$ when the table is scanned and
    keys are reinserted under normal hashing assumptions.
8.  A pathological collision pattern can make rebuilding $O(n^2)$.
9.  Conventional peak storage is $O(m+m')$.
10. Geometric growth gives amortized expected $O(1)$ insertion time.
11. In open addressing, deleted markers are not reinserted as keys.
12. In separate chaining, the load factor can be greater than 1.

------------------------------------------------------------------------

## 18. Practice Questions

Try answering before checking the solutions.

### Q1. Definition

What is rehashing?

**Answer:** Rehashing is rebuilding a hash table, usually with a larger
capacity, and reinserting all valid existing keys using recalculated
hash positions.

### Q2. New index

Old capacity = 7, new capacity = 13, key = 29.

Using $h(k)=k\bmod m$, calculate the new index.

**Solution:**

$$
29\bmod 13 = 3
$$

Answer: index 3.

### Q3. Load factor

A table contains 9 elements and has capacity 12. Calculate the load
factor.

**Solution:**

$$
\alpha = \frac{9}{12}=0.75
$$

Answer: 0.75 (75%).

### Q4. Rehash trigger

A table has 7 elements, capacity 10 and maximum load factor 0.75. A new
key is about to be inserted. Should the table rehash first if the policy
checks the projected load factor?

**Solution:**

$$
\alpha_{\text{projected}} =
\frac{7+1}{10}=0.8
$$

Since $0.8 > 0.75$, yes.

### Q5. Complexity

What is the expected time complexity of a complete rehash when the old
table is scanned and all $n$ keys are reinserted into a suitably sized
table?

**Answer:** $O(m+m'+n)$, commonly $O(n)$ when the capacities are
proportional to the number of stored keys.

### Q6. Worst case

Can rehashing take $O(n^2)$ time?

**Answer:** Yes. With pathological collisions, reinserting each key may
require scanning many positions, leading to quadratic total work in an
open-addressed table.

### Q7. Amortized complexity

If one insertion triggers an $O(n)$ rehash, why is insertion still
amortized $O(1)$ under geometric growth?

**Answer:** Rehashes are infrequent. The total rebuilding work across
$N$ insertions is $O(N)$, so the average cost per insertion over the
sequence is $O(1)$, under expected constant-time hashing assumptions.

### Q8. True or False

"During rehashing, only collided keys are inserted again."

**Answer:** False. Every valid stored key must be reinserted because its
new index may differ.

### Q9. True or False

"Rehashing always removes all collisions."

**Answer:** False. It may reduce collisions, but collisions can still
occur.

### Q10. Distinguish

Is quadratic probing rehashing?

**Answer:** No. Quadratic probing is a collision-resolution technique.
Rehashing rebuilds the table and uses the configured
collision-resolution technique when reinserting keys.

------------------------------------------------------------------------

## 19. Quick Revision Sheet

### Definition

Rehashing = create a new table + recalculate indices + reinsert all
valid keys.

### Load factor

$$
\boxed{\alpha = \frac{n}{m}}
$$

### Typical trigger

$$
\boxed{\frac{n+1}{m} > \alpha_{\max}}
$$

### Time complexity

$$
\boxed{O(m+m'+n)\text{ expected under normal hashing assumptions}}
$$

Commonly:

$$
\boxed{O(n)\text{ expected for one rehash}}
$$

Possible pathological worst case:

$$
\boxed{O(n^2)}
$$

### Space complexity

$$
\boxed{O(m+m')\text{ peak table storage}}
$$

Commonly $O(n)$ when capacities are proportional to the number of keys.

### Insertion complexity

-   No rehash: expected $O(1)$
-   Insertion triggering rehash: expected $O(n)$
-   Amortized over many insertions with geometric growth: expected
    $O(1)$ per insertion

### Remember these five points

1.  Rehashing is generally triggered by a high load factor.
2.  The capacity is usually increased.
3.  All valid keys are reinserted.
4.  Hash indices are recalculated.
5.  Rehashing is expensive once, but geometric growth makes insertion
    efficient amortized.

------------------------------------------------------------------------

**Final takeaway:** Rehashing keeps a dynamically growing hash table
efficient by rebuilding it at a larger capacity and redistributing its
keys. Understand the difference between the cost of one rehash ($O(n)$
expected in a typical rebuild) and the amortized cost of many insertions
($O(1)$ expected per insertion under geometric growth).
