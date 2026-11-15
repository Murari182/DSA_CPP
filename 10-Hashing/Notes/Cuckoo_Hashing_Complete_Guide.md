# Cuckoo Hashing — Complete DSA Notes

## 1. Introduction to hashing

Hashing is a technique used to store keys in a hash table so that they can be inserted, searched, and deleted efficiently.

A **hash function** converts a key into an array index.

For example, if the table size is $M=7$, a simple hash function is:

$$

h(k)=k\bmod 7

$$

For key $23$:

$$

h(23)=23\bmod 7=2

$$

So key 23 is assigned to index 2.

### What is a collision?

A collision occurs when two different keys produce the same hash-table index.

For example:

$$

h(23)=23\bmod7=2

$$

$$

h(30)=30\bmod7=2

$$

Both keys want index 2. A collision-resolution technique is needed to store both keys.

Common collision-resolution techniques include:

- Separate chaining
- Linear probing
- Quadratic probing
- Double hashing
- Cuckoo hashing

---

## 2. What is Cuckoo Hashing?

**Cuckoo Hashing is an open-addressing collision-resolution technique that uses two or more hash functions and multiple hash tables (or candidate positions) to store keys.**

In the basic two-table version:

- There are two hash tables, usually called $T_1$ and $T_2$.
- Each table has the same size $M$.
- Hash function $h_1$ gives the only permitted position for a key in $T_1$.
- Hash function $h_2$ gives the only permitted position for that key in $T_2$.

Therefore, a key $k$ can be stored only at:

$$

T_1[h_1(k)] \quad \text{or} \quad T_2[h_2(k)]

$$

A key is not allowed to occupy an arbitrary empty position.

### Why is it called Cuckoo Hashing?

The name is inspired by the cuckoo bird. Some cuckoo birds lay eggs in another bird's nest and may push an existing egg out.

Similarly, when a new key wants an occupied position, Cuckoo Hashing can put the new key there and **kick out (evict) the existing key**. The displaced key must move to its alternative permitted position.

---

## 3. Cuckoo Hashing versus Linear Probing

Both are open-addressing techniques, but their collision-handling methods are different.

| Feature | Linear Probing | Cuckoo Hashing |
|---|---|---|
| Candidate positions | Usually one hash function followed by a sequence of slots | One position per hash function |
| Collision handling | Checks the next slot, then the next | Displaces the occupant to its alternative position |
| Search | May inspect a sequence of slots | Checks the key's candidate positions |
| Clustering | Can suffer from primary clustering | Avoids linear-probing-style primary clustering |
| Insertion | Usually straightforward | Can cause a chain of displacements or a cycle |

**Remember:**

- Linear Probing: “The desired slot is occupied, so check the next slot.”
- Cuckoo Hashing: “The desired slot is occupied, so move its occupant to its other permitted slot.”

---

## 4. Two hash functions and two tables

For the example in this guide, the table size is:

$$

M=7

$$

The hash functions are:

$$

h_1(k)=k\bmod M

$$

$$

h_2(k)=[(k\bmod M)+3]\bmod M

$$

Interpretation:

- Calculate $h_1(k)$ to find the candidate position in $T_1$.
- Calculate $h_2(k)$ to find the candidate position in $T_2$.

For key $23$:

$$

h_1(23)=23\bmod7=2

$$

$$

h_2(23)=[(23\bmod7)+3]\bmod7=(2+3)\bmod7=5

$$

So key 23 can be stored at either:

- $T_1[2]$, or
- $T_2[5]$.

It cannot be stored at any other position.

---

## 5. Insertion algorithm: the kick-out mechanism

The following is the alternating insertion convention used in the worked example and C++ program.

1. Start by trying to insert the new key into $T_1$ at $h_1(k)$.
2. If that position is empty, place the key there and finish.
3. If it is occupied, swap the new key with the key already there. The displaced key becomes the key that still needs to be inserted.
4. Try that displaced key in $T_2$, at its $h_2$ position.
5. If the position is occupied, swap again. The newly displaced key is sent back to $T_1$.
6. Continue alternating between the tables until an empty candidate position is found.
7. In a real implementation, limit the number of displacements. If the limit is exceeded, rebuild the table using new hash functions and/or a larger table.

### Important terms

- **Displacement / eviction:** Removing an existing key from its current slot to make room for another key.
- **Alternative position:** The key's candidate position in the other table.
- **Cycle:** A repeated displacement pattern that does not reach an empty position.
- **Rehashing:** Rebuilding the table, usually with new hash functions and sometimes a larger capacity, to resolve an insertion failure or cycle.

### Insertion pseudocode

```text
INSERT(key):
    currentKey = key
    currentTable = T1

    repeat, up to MAX_KICKS:
        if currentTable is T1:
            position = h1(currentKey)
        else:
            position = h2(currentKey)

        swap(currentKey, currentTable[position])

        if currentKey is EMPTY:
            return SUCCESS

        switch currentTable to the other table

    return REHASH_REQUIRED
```

The `swap` is the central operation. After the swap, `currentKey` contains the key that was occupying that slot.

---

## 6. Worked examination question

**Question**

Two hash tables of equal size have $M=7$. Their hash functions are:

$$

h_1(k)=k\bmod M

$$

$$

h_2(k)=[(k\bmod M)+3]\bmod M

$$

Insert the following sequence using Cuckoo Hashing:

$$

23,\ 74,\ 73,\ 76,\ 28,\ 25,\ 35,\ 17

$$

Find the final contents of both hash tables.

### Step 1 — Calculate both candidate positions

| Key | $h_1(k)=k\bmod7$ | $h_2(k)=[(k\bmod7)+3]\bmod7$ |
|---:|---:|---:|
| 23 | 2 | 5 |
| 74 | 4 | 0 |
| 73 | 3 | 6 |
| 76 | 6 | 2 |
| 28 | 0 | 3 |
| 25 | 4 | 0 |
| 35 | 0 | 3 |
| 17 | 3 | 6 |

Each row tells us the only two permitted locations for that key.

### Step 2 — Insert the keys in the given order

Initially, every slot in both tables is empty.

#### Insert 23

$$

h_1(23)=2

$$

$T_1[2]$ is empty, so place 23 there.

#### Insert 74

$$

h_1(74)=4

$$

$T_1[4]$ is empty, so place 74 there.

#### Insert 73

$$

h_1(73)=3

$$

$T_1[3]$ is empty, so place 73 there.

#### Insert 76

$$

h_1(76)=6

$$

$T_1[6]$ is empty, so place 76 there.

#### Insert 28

$$

h_1(28)=0

$$

$T_1[0]$ is empty, so place 28 there.

#### Insert 25 — First displacement

$$

h_1(25)=4

$$

But $T_1[4]$ already contains 74.

- Put 25 into $T_1[4]$.
- The displaced key is 74.
- Move 74 to its alternative position in $T_2$.

$$

h_2(74)=[(74\bmod7)+3]\bmod7=(4+3)\bmod7=0

$$

$T_2[0]$ is empty, so place 74 there.

#### Insert 35 — Second displacement

$$

h_1(35)=0

$$

But $T_1[0]$ contains 28.

- Put 35 into $T_1[0]$.
- The displaced key is 28.
- Move 28 to its alternative position in $T_2$.

$$

h_2(28)=[(28\bmod7)+3]\bmod7=(0+3)\bmod7=3

$$

$T_2[3]$ is empty, so place 28 there.

#### Insert 17 — Third displacement

$$

h_1(17)=3

$$

But $T_1[3]$ contains 73.

- Put 17 into $T_1[3]$.
- The displaced key is 73.
- Move 73 to its alternative position in $T_2$.

$$

h_2(73)=[(73\bmod7)+3]\bmod7=(3+3)\bmod7=6

$$

$T_2[6]$ is empty, so place 73 there.

No cycle occurs in this sequence. All eight keys are inserted successfully.

### Step 3 — Final hash tables

**Hash Table 1**

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---:|---:|---:|---:|---:|---:|---:|
| Key | 35 | EMPTY | 23 | 17 | 25 | EMPTY | 76 |

**Hash Table 2**

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---:|---:|---:|---:|---:|---:|---:|
| Key | 74 | EMPTY | EMPTY | 28 | EMPTY | EMPTY | 73 |

Therefore:

$$

\boxed{T_1=[35,-,23,17,25,-,76]}

$$

$$

\boxed{T_2=[74,-,-,28,-,-,73]}

$$

Here, `-` represents an empty slot.

---

## 7. Searching in Cuckoo Hashing

Searching is simple because a key has only two possible positions in the two-table version.

To search for key $k$:

1. Calculate $h_1(k)$ and check $T_1[h_1(k)]$.
2. If the key is not there, calculate/check $T_2[h_2(k)]$.
3. If neither location contains the key, the key is absent.

Example: Search for 28.

$$

h_1(28)=0,\qquad h_2(28)=3

$$

Check:

- $T_1[0]=35$, so 28 is not there.
- $T_2[3]=28$, so the key is found.

With two tables and two hash functions, lookup checks at most **two slots**.

---

## 8. Deletion in Cuckoo Hashing

Deletion is also straightforward.

To delete key $k$:

1. Check $T_1[h_1(k)]$.
2. If it contains $k$, mark that slot empty.
3. Otherwise, check $T_2[h_2(k)]$.
4. If it contains $k$, mark that slot empty.
5. If neither contains it, the key is not present.

For a fixed number of hash functions, deletion takes $O(1)$ time.

---

## 9. Time and space complexity

Let:

- $n$ = number of stored keys.
- $M$ = number of slots in each table.
- $d$ = number of hash functions / candidate positions per key.

For the basic version here, $d=2$, and there are two tables of $M$ slots each.

| Operation / property | Complexity | Explanation |
|---|---|---|
| Calculate a hash position | $O(1)$ | A fixed hash function is evaluated |
| Search / lookup | $O(1)$ | At most two candidate slots are checked |
| Delete | $O(1)$ | At most two candidate slots are checked |
| Insert | Expected $O(1)$ under suitable hashing and load assumptions | Usually a short displacement chain |
| Insert, worst case | $O(n)$ or more including rebuilding | A long chain or cycle can trigger rehashing |
| Space | $O(M)$ | Two arrays of $M$ slots each; total capacity is $2M$ |

### Important complexity clarification

- Lookup is worst-case $O(1)$ for a fixed number of hash functions, assuming the hash functions and candidate positions are directly computable.
- Insertion is **not guaranteed worst-case $O(1)$**. A displacement chain may be long, and rehashing can take $O(n)$ time.
- The commonly quoted expected $O(1)$ insertion bound relies on suitable hash functions and keeping the table load below an appropriate threshold. It is not guaranteed for every hash-function choice or every input.
- If the two tables each have $M$ slots, the total allocated table space is $2M$, which is $O(M)$.

### Load factor

For two tables of size $M$, the total number of available slots is $2M$.

$$

\alpha=\frac{n}{2M}

$$

For this question:

$$

n=8,\qquad M=7

$$

$$

\alpha=\frac{8}{2\times7}=\frac{8}{14}\approx0.5714

$$

So the combined load factor is approximately $57.14\%$.

---

## 10. Advantages of Cuckoo Hashing

1. **Fast lookup:** Only the candidate positions need to be checked.
2. **Predictable search:** The number of checks is bounded by the number of hash functions.
3. **No linear-probing primary clustering:** Keys do not occupy arbitrary consecutive slots.
4. **Simple deletion:** Check the candidate positions and clear the matching slot.
5. **Array-based storage:** The basic implementation does not need linked lists.

## 11. Disadvantages of Cuckoo Hashing

1. **Displacement chains:** One insertion may move several existing keys.
2. **Cycles:** Displacements may repeat without finding an empty slot.
3. **Rehashing:** A cycle or excessive number of displacements may require new hash functions or a larger table.
4. **Insertion complexity:** Insertion is more complicated than linear probing.
5. **Hash-function sensitivity:** Poor hash functions or an unsuitable load factor can cause frequent insertion failures.

---

## 12. Important examination points

- Cuckoo Hashing is an **open-addressing** collision-resolution method.
- The basic version uses two hash tables and two hash functions.
- Each key has two permitted positions: $T_1[h_1(k)]$ and $T_2[h_2(k)]$.
- If the chosen position is occupied, the existing key is displaced to its alternative position.
- The displacement process is also called **eviction** or **kicking out**.
- A repeated displacement cycle may require rehashing.
- Search checks at most two positions in the basic two-hash-function version.
- Lookup and deletion are worst-case $O(1)$ for a fixed number of candidate positions.
- Insertion is expected $O(1)$ under suitable assumptions, but can take longer and may require rehashing.
- Two tables of size $M$ provide $2M$ total slots.

### Quick memory trick

| Technique | What happens after a collision? |
|---|---|
| Linear Probing | Check the next slot |
| Quadratic Probing | Check slots using quadratic offsets |
| Double Hashing | Use a second hash function as the probe step |
| Cuckoo Hashing | Kick out the existing key and move it to its alternative position |

**One-line definition for exams:**

Cuckoo Hashing is an open-addressing collision-resolution technique that uses multiple hash functions and resolves collisions by displacing existing keys to their alternative hash locations.
