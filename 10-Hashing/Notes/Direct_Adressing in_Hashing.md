# Hashing in DSA --- Direct Addressing

> Personal study notes: Direct Addressing using a fixed array and a
> dynamically resizable `vector` in C++.

------------------------------------------------------------------------

## 1. What is Direct Addressing?

Direct Addressing is a technique for storing, searching, and deleting
keys using an array called a **direct-address table**.

The key itself is used as the index of the array. We do not calculate a
separate hash value.

$$
h(key)=key
$$

For example, if the keys are `2, 4, 6, 8`, they are stored at indices
`2, 4, 6, 8`, respectively.

A simple table can use:

-   `0` to mean that a key is absent.
-   `1` to mean that a key is present.

Example, for a table of size 10:

| Index | Value | Meaning |
|---:|---:|---|
| 0 | 0 | Key 0 absent |
| 1 | 0 | Key 1 absent |
| 2 | 1 | Key 2 present |
| 3 | 0 | Key 3 absent |
| 4 | 1 | Key 4 present |
| 5 | 0 | Key 5 absent |
| 6 | 1 | Key 6 present |
| 7 | 0 | Key 7 absent |
| 8 | 1 | Key 8 present |
| 9 | 0 | Key 9 absent |

The table stores the *presence* of a key. It does not need to store the
key again because its index already identifies it.

## 2. Direct Addressing using a normal array

### C++ implementation

``` cpp
#include <iostream>
using namespace std;

class Direct_Addressing
{
public:
    int arr[10];

    Direct_Addressing()
    {
        for(int i = 0; i < 10; i++)
        {
            arr[i] = 0;
        }
    }

    // INSERTION
    void Insert(int key)
    {
        if(key < 0 || key >= 10)
        {
            cout << "Key is outside the array range\n";
            return;
        }

        arr[key] = 1;
        cout << "Key inserted successfully\n";
    }

    // SEARCHING
    void Search(int key)
    {
        if(key < 0 || key >= 10)
        {
            cout << "Key is outside the array range\n";
            return;
        }

        if(arr[key] == 1)
            cout << "Key Found\n";
        else
            cout << "Key Not Found\n";
    }

    // DELETION
    void Delete(int key)
    {
        if(key < 0 || key >= 10)
        {
            cout << "Key is outside the array range\n";
            return;
        }

        arr[key] = 0;
        cout << "Key Deleted Successfully\n";
    }

    // DISPLAY
    void Display()
    {
        cout << "\nIndex\tValue\n";

        for(int i = 0; i < 10; i++)
        {
            cout << i << "\t" << arr[i] << endl;
        }
    }
};

int main()
{
    Direct_Addressing obj;

    obj.Insert(2);
    obj.Insert(4);
    obj.Insert(6);
    obj.Insert(8);

    obj.Display();

    obj.Search(6);

    obj.Delete(6);

    obj.Display();

    return 0;
}
```

### Explanation of the code

#### A. Array initialization

``` cpp
int arr[10];
```

This creates an array with 10 elements. The constructor initializes
every element to zero:

``` cpp
for(int i = 0; i < 10; i++)
{
    arr[i] = 0;
}
```

Initially, no keys are present in the direct-address table.

#### B. Insertion

``` cpp
arr[key] = 1;
```

For example, `Insert(5)` executes:

``` cpp
arr[5] = 1;
```

The value at index 5 becomes 1, indicating that key 5 is present.

#### C. Searching

``` cpp
if(arr[key] == 1)
    cout << "Key Found";
else
    cout << "Key Not Found";
```

To search for key 5, directly inspect `arr[5]`. If it is 1, the key is
present; if it is 0, the key is absent.

#### D. Deletion

``` cpp
arr[key] = 0;
```

To delete key 5, set `arr[5]` back to zero. This marks the key as
absent.

### Complexity

| Operation | Time complexity |
|---|---:|
| Insertion | $O(1)$ |
| Searching | $O(1)$ |
| Deletion | $O(1)$ |
| Displaying the whole table | $O(M)$ |

Here, $M$ is the size of the direct-address table.

## 3. Limitation of a fixed-size array

Consider:

``` cpp
int arr[100] = {0};
int key = 150;

arr[key] = 1;
```

An array of size 100 has valid indices from 0 to 99. Accessing
`arr[150]` is out of bounds and causes **undefined behaviour** in C++.

The fundamental limitation is that the table must be large enough to
include every possible key.

| Key/index to be accessed | Minimum array size |
|---:|---:|
| 10 | 11 |
| 100 | 101 |
| 1,000 | 1,001 |
| 1,000,000 | 1,000,001 |
| 1,000,000,000 | 1,000,000,001 |

This can require a huge amount of memory, even if only a few keys are
actually stored.

## 4. Using a vector for dynamic Direct Addressing

A C++ `vector` can change its size while the program runs. This means we
can expand the table when a key is outside its current range.

For example:

``` cpp
vector<int> arr(100, 0);
```

Initially:

-   `arr.size()` is 100.
-   Valid indices are 0 through 99.
-   All 100 elements contain 0.

Suppose we want to insert key 150. We need index 150 to exist.

``` cpp
int key = 150;

if(key >= arr.size())
{
    arr.resize(key + 1, 0);
}

arr[key] = 1;
```

### Step-by-step dry run

**Step 1 --- Create the vector**

``` cpp
vector<int> arr(100, 0);
```

The vector contains 100 zero-initialized elements.

$$
\text{size}=100
$$

Valid indices: 0 to 99.

**Step 2 --- Set the key**

``` cpp
int key = 150;
```

Direct Addressing requires us to use index 150.

**Step 3 --- Check whether the index exists**

``` cpp
if(key >= arr.size())
```

Substituting the values:

$$
150 \geq 100
$$

The condition is true, so the vector must be expanded.

**Step 4 --- Resize the vector**

``` cpp
arr.resize(key + 1, 0);
```

Substitute:

$$
key+1=150+1=151
$$

This becomes:

``` cpp
arr.resize(151, 0);
```

The result:

-   The original 100 elements are preserved.
-   51 new elements are added and initialized to 0.
-   The new size is 151.
-   Valid indices are 0 through 150.

**Why `key + 1` and not just `key`?**

C++ vector indexing starts at zero. A vector of size 150 has valid
indices 0 through 149. To access index 150, it needs at least 151
elements.

In general:

$$
\boxed{\text{Minimum size required to access index } k=k+1}

$$

Examples:

| Required index | Minimum vector size |
|---:|---:|
| 5 | 6 |
| 10 | 11 |
| 75 | 76 |
| 150 | 151 |

**Step 5 --- Insert the key**

``` cpp
arr[key] = 1;
```

This executes:

``` cpp
arr[150] = 1;
```

It is now a valid access because the vector has indices 0 through 150.

> Important: `resize()` creates or removes elements to change the
> vector's size. It does not insert the key itself. The assignment
> `arr[key] = 1` marks the key as present.

## 5. Complete C++ implementation using vector

This implementation supports insertion, searching, deletion, and
displaying the present keys. It starts with a table of a chosen initial
size and expands it when necessary.

``` cpp
#include <iostream>
#include <vector>
using namespace std;

class Direct_Addressing
{
public:
    vector<int> arr;

    Direct_Addressing(int initial_size)
    {
        arr.resize(initial_size, 0);
    }

    // INSERTION
    void Insert(int key)
    {
        if(key < 0)
        {
            cout << "Negative keys are not supported\n";
            return;
        }

        // Check whether the required index exists
        if(key >= arr.size())
        {
            // Increase vector size dynamically
            arr.resize(key + 1, 0);
        }

        arr[key] = 1;
        cout << "Key inserted successfully\n";
    }

    // SEARCHING
    void Search(int key)
    {
        if(key < 0 || key >= arr.size())
        {
            cout << "Key Not Found\n";
            return;
        }

        if(arr[key] == 1)
            cout << "Key Found\n";
        else
            cout << "Key Not Found\n";
    }

    // DELETION
    void Delete(int key)
    {
        if(key < 0 || key >= arr.size())
        {
            cout << "Key Not Found\n";
            return;
        }

        if(arr[key] == 1)
        {
            arr[key] = 0;
            cout << "Key Deleted Successfully\n";
        }
        else
        {
            cout << "Key Not Found\n";
        }
    }

    // DISPLAY
    void Display()
    {
        cout << "\nPresent Keys: ";

        for(int i = 0; i < arr.size(); i++)
        {
            if(arr[i] == 1)
                cout << i << " ";
        }

        cout << "\nVector Size: " << arr.size() << endl;
    }
};

int main()
{
    Direct_Addressing obj(100);

    obj.Insert(2);
    obj.Insert(4);
    obj.Insert(6);
    obj.Insert(8);

    obj.Display();

    cout << "\nInserting a large key:\n";

    obj.Insert(150);

    obj.Display();

    cout << "\nSearching:\n";

    obj.Search(150);
    obj.Search(50);

    cout << "\nDeleting:\n";

    obj.Delete(150);

    obj.Display();

    return 0;
}
```

### Understanding the key condition

``` cpp
if(key >= arr.size())
{
    arr.resize(key + 1, 0);
}
```

This checks whether the required index is outside the current vector
size.

| Current size | Key | Condition | New size |
|---:|---:|:---:|---:|
| 100 | 50 | False | 100 |
| 100 | 99 | False | 100 |
| 100 | 100 | True | 101 |
| 100 | 150 | True | 151 |
| 100 | 200 | True | 201 |

If the index is already valid, no resizing is required.

## 6. Important distinction: `size()` vs `capacity()`

These two vector functions have different meanings.

| Function | Meaning |
|---|---|
| `arr.size()` | Number of elements currently in the vector |
| `arr.capacity()` | Number of elements the vector can hold in its currently allocated storage without another allocation |

Example:

``` cpp
vector<int> arr(100, 0);

cout << arr.size() << endl;
cout << arr.capacity() << endl;
```

The size is 100. The capacity is at least 100, but its exact value is
implementation-dependent.

After:

``` cpp
arr.resize(151, 0);
```

The size becomes 151, and capacity must be at least 151.

Remember:

-   `resize()` changes the number of elements.
-   `reserve()` changes the capacity when necessary, but does not change
    the number of elements.

For example:

``` cpp
vector<int> arr;
arr.reserve(100);

cout << arr.size();     // 0
cout << arr.capacity(); // At least 100
```

Even though storage has been reserved, `arr[50]` is not valid because
the vector still has zero elements.

## 7. Time and space complexity

Let:

-   $M$ be the fixed size of the normal array.
-   $K$ be the vector's size after expansion.

| Operation | Fixed array | Vector |
|---|---:|---:|
| Insertion when index exists | $O(1)$ | $O(1)$ |
| Insertion requiring expansion | Not possible | $O(K)$ worst case |
| Searching | $O(1)$ | $O(1)$ |
| Deletion | $O(1)$ | $O(1)$ |
| Displaying all indices | $O(M)$ | $O(K)$ |

A vector resize that requires a new allocation may move or copy the
existing elements. Therefore, resizing can take linear time in the
resulting vector size.

The vector implementation above resizes to exactly `key + 1` when
needed. If keys arrive in increasing order, repeated expansions may be
expensive. A production implementation could grow geometrically or
reserve a suitable range in advance.

Space complexity:

- Fixed array: $O(M)$.
- Vector: $O(K)$, where $K$ is the largest allocated index plus one.

## 8. Direct Addressing vs ordinary hashing

This is the important connection between Direct Addressing and hashing.

Suppose:

$$
key=150
$$

### Direct Addressing

The key itself is the index:

$$
h(150)=150
$$

So the key is represented at index 150.

### Hashing

Suppose we use this hash function:

$$
h(key)=key \bmod 10
$$

Then:

$$
h(150)=150 \bmod 10=0
$$

The key maps to index 0 in a table of size 10.

| Property | Direct Addressing | Hashing |
|---|---|---|
| Index calculation | Key itself | Hash function |
| Large keys | Requires a table covering the key range | Maps keys into a smaller table |
| Collisions | No collisions for distinct keys | Collisions are possible |
| Memory requirement | Depends on the key universe | Depends mainly on table capacity |
| Search | $O(1)$ | Average $O(1)$ under suitable assumptions |

Hashing can produce collisions because different keys may map to the
same index. Collision resolution techniques include:

1.  Separate Chaining
2.  Linear Probing
3.  Quadratic Probing
4.  Double Hashing

### Important conclusion about vectors

Using a vector solves the *fixed-size limitation* of a normal array
because it can grow dynamically.

However, it does not solve the fundamental memory limitation of Direct
Addressing.

For example, if the key is:

$$
10^9
$$

The vector still needs at least:

$$
10^9+1
$$

elements to access that key directly.

Therefore:

-   A vector provides dynamic sizing.
-   A hash function provides a way to map a large key universe into a
    smaller table.

These are two different solutions to two different problems.

## 9. Practice questions

Try these without looking at the explanations above.

1.  Create a Direct Address Table of size 20 and insert keys 3, 5, 7,
    10, and 15.
2.  Search for keys 7 and 12.
3.  Delete key 10 and display the remaining keys.
4.  Initialize a vector with size 25. Insert key 50. What is the new
    vector size?
5.  Initialize a vector with size 100. Insert keys 25, 150, 75, and 200.
    Track the vector size after each insertion.
6.  Explain why using a vector does not make Direct Addressing
    memory-efficient for very large keys.
7.  Explain the difference between `resize()` and `reserve()`.

## 10. Quick revision sheet

| Concept | Key point |
|---|---|
| Direct Addressing | The key itself is the array index |
| Direct-address function | $h(key)=key$ |
| Insertion | `arr[key] = 1` |
| Searching | Check `arr[key] == 1` |
| Deletion | `arr[key] = 0` |
| Fixed array limitation | Cannot safely access an index outside its bounds |
| Vector | Can dynamically increase its size |
| `resize()` | Changes the number of elements |
| `size()` | Number of current elements |
| `capacity()` | Allocated storage available before another allocation |
| Minimum size for index $k$ | $k+1$ |
| Vector memory limitation | Still depends on the largest key |
| Hashing | Maps keys to table indices using a hash function |

### What to study next

After Direct Addressing, study **collision handling in hashing**:

1.  Separate Chaining
2.  Open Addressing
3.  Linear Probing
4.  Quadratic Probing
5.  Double Hashing

These concepts explain how practical hash tables handle multiple keys
mapping to the same table index.
