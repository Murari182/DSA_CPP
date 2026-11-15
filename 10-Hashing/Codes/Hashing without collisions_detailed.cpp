
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*
====================================================================
                         HASHING IN DSA
====================================================================

1. WHAT IS HASHING?
-------------------
Hashing is a technique used to store, search, and retrieve data
quickly by converting a key into an index using a hash function.

Example:
    Key = 23
    Hash function = key % 10
    Index = 23 % 10 = 3

    Therefore, key 23 is stored at index 3.


2. WHAT IS A HASH TABLE?
------------------------
A hash table is a data structure that stores keys at positions
calculated by a hash function.

Here, we use an array of size 10.

    int arr[10];

Valid indices are:
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9

The hash table uses the calculated index to access a key directly.


3. WHAT IS A KEY?
-----------------
A key is the value that we want to insert or search.

Examples:
    20, 23, 45, 17


4. WHAT IS A HASH FUNCTION?
---------------------------
A hash function converts a key into an index.

In this program:

    h(key) = key % SIZE

Here, % is the modulo operator, which returns the remainder.

Examples:

    h(20) = 20 % 10 = 0
    h(23) = 23 % 10 = 3
    h(45) = 45 % 10 = 5
    h(17) = 17 % 10 = 7

IMPORTANT:
The hash function calculates the index.
The hash table stores the actual key at that index.


5. WHAT IS A COLLISION?
-----------------------
A collision occurs when two different keys produce the same index.

Example:

    h(20) = 20 % 10 = 0
    h(30) = 30 % 10 = 0

Both keys want index 0.

This program DOES NOT resolve collisions.
If an index is already occupied, insertion is rejected.

Collision-handling methods include:
    1. Separate Chaining
    2. Open Addressing
       a. Linear Probing
       b. Quadratic Probing
       c. Double Hashing


6. WHY DO WE NEED occupied[]?
-----------------------------
An ordinary local array such as int arr[10] is not automatically
initialized when an object is created.

Reading an uninitialized element can cause undefined behavior.

Therefore, we use:

    int arr[SIZE];
    bool occupied[SIZE];

occupied[i] == false means index i is empty.
occupied[i] == true  means index i contains a valid key.

The constructor initializes all occupancy flags to false.

This also lets us distinguish an empty slot from a slot that
contains the integer 0.


7. TIME AND SPACE COMPLEXITY
----------------------------

Let:
    m = hash table size
    n = number of stored keys

Hash function:
    TC = O(1)
    Auxiliary SC = O(1)

Insertion (this implementation):
    TC = O(1)
    Auxiliary SC = O(1)

Search (this implementation):
    TC = O(1)
    Auxiliary SC = O(1)

Display entire table:
    TC = O(m)
    Auxiliary SC = O(1)

Complete table storage:
    SC = O(m)

The table has fixed size 10 in this program, so its storage is
constant for this particular configuration.

NOTE:
O(1) insertion and search here apply to this simple implementation.
General collision-resolving hash tables can take O(n) in the
worst case, depending on the collision-handling method.

====================================================================
*/

class hash_table {

    // --------------------------------------------------------------
    // STEP 1: DECLARE THE HASH TABLE
    // --------------------------------------------------------------

    static const int SIZE = 10;

    // Stores the actual keys.
    int arr[SIZE];

    // Tracks whether each position contains a key.
    bool occupied[SIZE];

public:

    // --------------------------------------------------------------
    // STEP 2: CONSTRUCTOR
    // --------------------------------------------------------------
    //
    // A constructor runs automatically when an object is created.
    //
    // We mark every position as empty.
    //
    // TC: O(SIZE)
    // SC: O(1) auxiliary space
    // --------------------------------------------------------------

    hash_table() {

        for (int i = 0; i < SIZE; i++) {
            occupied[i] = false;
        }
    }


    // --------------------------------------------------------------
    // STEP 3: HASH FUNCTION
    // --------------------------------------------------------------
    //
    // Purpose:
    // Calculate the index at which a key should be stored.
    //
    // Formula:
    //     h(key) = key % SIZE
    //
    // Example:
    //     key = 23
    //     h(23) = 23 % 10 = 3
    //
    // Returns:
    // The calculated index.
    //
    // TC: O(1)
    // Auxiliary SC: O(1)
    //
    // Assumption: keys are non-negative integers.
    // --------------------------------------------------------------

    int hash_function(int value) {

        int h = value % SIZE;

        return h;
    }


    // --------------------------------------------------------------
    // STEP 4: INSERTION
    // --------------------------------------------------------------
    //
    // Purpose:
    // Store a key at its calculated index.
    //
    // Algorithm:
    // 1. Calculate the hash index.
    // 2. Check whether the position is empty.
    // 3. If empty, store the key.
    // 4. If occupied, report a collision.
    //
    // This version does not resolve collisions.
    //
    // Example:
    //     insert(23)
    //     h(23) = 3
    //     arr[3] = 23
    //
    // TC: O(1)
    // Auxiliary SC: O(1)
    // --------------------------------------------------------------

    void insert(int value) {

        // Calculate the index.
        int h = hash_function(value);

        cout << "\nInserting key: " << value << endl;

        cout << "Hash calculation: "
             << value << " % " << SIZE
             << " = " << h << endl;

        // Check whether this position is occupied.
        if (occupied[h] == true) {

            cout << "COLLISION DETECTED!" << endl;

            cout << "Index " << h
                 << " already contains key "
                 << arr[h] << "." << endl;

            cout << "Key " << value
                 << " was NOT inserted because "
                 << "collision resolution is not implemented."
                 << endl;

            return;
        }

        // Store the key at the calculated index.
        arr[h] = value;

        // Mark the position as occupied.
        occupied[h] = true;

        cout << "Key " << value
             << " successfully stored at index "
             << h << "." << endl;
    }


    // --------------------------------------------------------------
    // STEP 5: SEARCH
    // --------------------------------------------------------------
    //
    // Purpose:
    // Find a key in the hash table.
    //
    // Algorithm:
    // 1. Calculate the index using the hash function.
    // 2. Check whether that position is occupied.
    // 3. If occupied, compare the stored key with the search key.
    // 4. Report whether the key was found.
    //
    // Example:
    //     search(23)
    //     h(23) = 3
    //     Check arr[3].
    //
    // TC: O(1)
    // Auxiliary SC: O(1)
    // --------------------------------------------------------------

    void search(int key) {

        int h = hash_function(key);

        cout << "\nSearching for key: " << key << endl;

        cout << "Hash calculation: "
             << key << " % " << SIZE
             << " = " << h << endl;

        // First check whether the position contains a key.
        if (occupied[h] == false) {

            cout << "Key " << key
                 << " NOT FOUND. Index "
                 << h << " is empty." << endl;

            return;
        }

        // Verify the key itself.
        if (arr[h] == key) {

            cout << "Key " << key
                 << " FOUND at index "
                 << h << "." << endl;

            return;
        }

        // Another key occupies the calculated index.
        cout << "Key " << key
             << " NOT FOUND." << endl;

        cout << "Index " << h
             << " contains " << arr[h]
             << ", not " << key << "." << endl;
    }


    // --------------------------------------------------------------
    // STEP 6: DISPLAY THE HASH TABLE
    // --------------------------------------------------------------
    //
    // Displays every index and its current contents.
    //
    // TC: O(SIZE)
    // Auxiliary SC: O(1)
    // --------------------------------------------------------------

    void display() {

        cout << "\n";
        cout << "======================================" << endl;
        cout << "           HASH TABLE                 " << endl;
        cout << "======================================" << endl;

        cout << "Index\tValue" << endl;
        cout << "--------------------------------------" << endl;

        for (int i = 0; i < SIZE; i++) {

            cout << i << "\t";

            if (occupied[i] == true) {
                cout << arr[i];
            }
            else {
                cout << "EMPTY";
            }

            cout << endl;
        }

        cout << "======================================" << endl;
    }


    // --------------------------------------------------------------
    // STEP 7: DISPLAY THE COMPLEXITY SUMMARY
    // --------------------------------------------------------------
    //
    // Hash function       : O(1) time
    // Insertion           : O(1) time
    // Search              : O(1) time
    // Display             : O(SIZE) time
    // Complete storage    : O(SIZE) space
    // --------------------------------------------------------------

    void complexity() {

        cout << "\n";
        cout << "======================================" << endl;
        cout << "       COMPLEXITY SUMMARY             " << endl;
        cout << "======================================" << endl;

        cout << "Hash function       : O(1) TC" << endl;
        cout << "Insertion           : O(1) TC" << endl;
        cout << "Search              : O(1) TC" << endl;
        cout << "Display             : O(SIZE) TC" << endl;
        cout << "Table storage       : O(SIZE) SC" << endl;
        cout << "======================================" << endl;
    }
};


// ==================================================================
//                              MAIN
// ==================================================================

int main() {

    // Create an object of the hash_table class.
    hash_table h1;

    // --------------------------------------------------------------
    // INSERTION EXAMPLES
    // --------------------------------------------------------------

    // 20 % 10 = 0
    h1.insert(20);

    // 23 % 10 = 3
    h1.insert(23);

    // 45 % 10 = 5
    h1.insert(45);

    // 17 % 10 = 7
    h1.insert(17);

    // --------------------------------------------------------------
    // SEARCH EXAMPLES
    // --------------------------------------------------------------

    h1.search(20);  // Found at index 0
    h1.search(23);  // Found at index 3
    h1.search(99);  // Index 9 is empty

    // --------------------------------------------------------------
    // COLLISION EXAMPLE
    // --------------------------------------------------------------

    // 30 % 10 = 0
    // Index 0 already contains 20.
    // Insertion of 30 will be rejected.
    h1.insert(30);

    // --------------------------------------------------------------
    // DISPLAY THE COMPLETE HASH TABLE
    // --------------------------------------------------------------

    h1.display();

    // Display time and space complexity.
    h1.complexity();

    return 0;
}

/*
====================================================================
                   HASHING AND HASH TABLE - DSA NOTES
====================================================================

1. WHAT IS HASHING?
-------------------
Hashing is a technique used to store, search, and retrieve data
quickly by converting a key into an index using a hash function.

Example:
    Key = 23
    Hash function = key % 10
    Index = 23 % 10 = 3

    Therefore, key 23 is stored at index 3.


2. WHAT IS A HASH TABLE?
------------------------
A hash table is a data structure that stores keys or key-value
pairs at positions calculated by a hash function.

Example:
    int arr[10];

    This array has 10 positions with indices from 0 to 9.

    arr[3] = 23;

    Here, key 23 is stored at index 3.

A hash table uses hashing to find the position where data should
be stored or searched for.


3. WHAT IS A KEY?
-----------------
A key is the value used to identify, insert, or search for data.

Examples:
    10, 20, 23, 45

In a key-value hash table, a key can be associated with a value.
Example:
    Roll number -> Student name


4. WHAT IS A HASH FUNCTION?
---------------------------
A hash function converts a key into an index in the hash table.

General notation:
    h(key) = calculated index

Example hash function:
    h(key) = key % SIZE

If SIZE = 10:

    h(20) = 20 % 10 = 0
    h(23) = 23 % 10 = 3
    h(45) = 45 % 10 = 5
    h(17) = 17 % 10 = 7

The hash function should produce a valid table index.

For a table of size SIZE:
    0 <= index < SIZE

IMPORTANT:
    Hash function -> Calculates the index.
    Hash table    -> Stores the data.


5. WHAT IS MODULO (%)?
----------------------
The modulo operator returns the remainder after division.

Examples:
    23 % 10 = 3
    45 % 10 = 5
    30 % 10 = 0
    17 % 10 = 7

We use modulo in a simple hash function to map integer keys
to valid indices.


6. HOW DOES HASHING WORK?
-------------------------
Suppose we want to insert these keys:

    20, 23, 45, 17

Hash function:
    h(key) = key % 10

Insertion:

    Key 20 -> Index 0
    Key 23 -> Index 3
    Key 45 -> Index 5
    Key 17 -> Index 7

The table becomes:

    Index       Value
    -----------------
      0           20
      1          EMPTY
      2          EMPTY
      3           23
      4          EMPTY
      5           45
      6          EMPTY
      7           17
      8          EMPTY
      9          EMPTY

To search for 23:
    1. Calculate 23 % 10 = 3.
    2. Access index 3.
    3. Check whether the stored key is 23.
    4. If it matches, the key is found.

This avoids checking every array element.


7. WHAT IS A COLLISION?
-----------------------
A collision occurs when two different keys produce the same
hash table index.

Example:
    h(20) = 20 % 10 = 0
    h(30) = 30 % 10 = 0

Both keys map to index 0.

Therefore, a collision occurs.

Collisions are common in hashing because many possible keys
must map to a limited number of table positions.


8. COLLISION-HANDLING TECHNIQUES
--------------------------------

A. SEPARATE CHAINING
--------------------
Each hash table index stores a collection of keys, commonly
implemented using a linked list or another container.

Example:
    h(23) = 3
    h(43) = 3
    h(13) = 3

Index 3 contains:
    23 -> 43 -> 13

In C++, a simple learning implementation is:

    vector<int> table[10];

Insertion:
    table[23 % 10].push_back(23);
    table[43 % 10].push_back(43);
    table[13 % 10].push_back(13);

All three keys are stored in the vector at index 3.

B. OPEN ADDRESSING
------------------
Every occupied table slot stores one key.

When a collision occurs, another available position is found.

Common methods:

    1. Linear Probing
       Check the next position.

       index = (index + 1) % SIZE;

    2. Quadratic Probing
       Check positions using quadratic offsets.

    3. Double Hashing
       Use a second hash function to determine the step size.


9. LINEAR PROBING
-----------------
Suppose:
    h(key) = key % 10

Insert 23:
    23 % 10 = 3
    Store 23 at index 3.

Insert 43:
    43 % 10 = 3
    Index 3 is occupied.
    Check index 4.
    If index 4 is empty, store 43 there.

Linear probing checks subsequent positions until an empty
position is found, wrapping around to index 0 when necessary.

A table can become full, so insertion must check for that case.


10. INSERTION OPERATION
-----------------------
Steps:
    1. Receive the key.
    2. Calculate its index using the hash function.
    3. Check whether the index is available.
    4. Store the key or handle the collision.

Without collision handling:
    An occupied index prevents insertion of another key
    that maps to the same index.

With collision handling:
    Use chaining or open addressing.


11. SEARCH OPERATION
--------------------
Steps:
    1. Receive the key to search for.
    2. Calculate its hash index.
    3. Check the corresponding table position.
    4. Compare the stored key with the requested key.
    5. Report whether the key exists.

With separate chaining:
    Search through the collection at the calculated index.

With open addressing:
    Follow the same probing sequence used during insertion.

IMPORTANT:
    A search must follow the collision-handling method.
    Checking only the initial index is not sufficient when
    collisions are handled by chaining or probing.


12. DELETION OPERATION
----------------------
Deletion removes a key from the hash table.

With separate chaining:
    Find the key in the chain and remove it.

With open addressing:
    Deletion requires care. Simply marking a slot as empty
    can break searches for keys inserted later in the probing
    sequence. A special DELETED marker is commonly used.


13. WHY USE HASHING?
--------------------
Advantages:
    1. Fast average-case searching.
    2. Fast average-case insertion and deletion.
    3. Useful for frequency counting.
    4. Useful for duplicate detection.
    5. Useful for key-value storage.
    6. Widely used in dictionaries, caches, and sets.

Limitations:
    1. Collisions must be handled.
    2. Worst-case operations can be slower.
    3. A hash table does not generally keep keys sorted.
    4. Performance depends on the hash function and table design.


14. TIME COMPLEXITY
-------------------

Let:
    n = number of stored keys
    m = number of table positions

Operation                 Average TC       Worst-case TC
---------------------------------------------------------
Hash calculation             O(1)               O(1)
Search                       O(1)               O(n)
Insertion                    O(1)               O(n)
Deletion                     O(1)               O(n)
Display entire table         O(m)               O(m)

These are typical complexities for a properly implemented,
collision-resolving hash table under the usual assumptions.

For the simple fixed-size table WITHOUT collision handling,
a single insertion or search checks only one index and takes
O(1) time. However, it cannot correctly store or find every
key when collisions occur.

For separate chaining, worst-case search can be O(n).
For open addressing, performance deteriorates as the table
becomes full.


15. SPACE COMPLEXITY
--------------------

Hash table storage:
    O(m)

Separate chaining:
    O(m + n) total storage, including stored keys and chains.

Open addressing:
    O(m) total table storage, with keys stored in the table.

Auxiliary space for a single hash calculation:
    O(1)

Auxiliary space for a single search:
    O(1), excluding any existing table storage.


16. LOAD FACTOR
---------------
The load factor measures how full a hash table is.

Formula:
    Load Factor = Number of Stored Keys / Table Size

Mathematically:
    alpha = n / m

Example:
    Number of keys = 5
    Table size = 10

    alpha = 5 / 10 = 0.5

A higher load factor generally increases collision frequency
or probing effort. The exact effect depends on the method used.


17. HASHING IN C++ STL
----------------------

A. unordered_map
----------------
Stores key-value pairs.

Example:
    unordered_map<int, string> student;

    student[101] = "Ravi";
    student[102] = "Raju";

    cout << student[101];

Average-case insertion, search, and deletion:
    O(1)

Worst-case operations:
    O(n)


B. unordered_set
----------------
Stores unique keys.

Example:
    unordered_set<int> s;

    s.insert(10);
    s.insert(20);
    s.insert(10);

The value 10 is stored only once because unordered_set
contains unique elements.

Average-case insertion, search, and deletion:
    O(1)

Worst-case operations:
    O(n)


18. HASH TABLE VS NORMAL ARRAY
------------------------------

Normal array:
    Access by a known index.
    arr[3] accesses index 3 directly.

Hash table:
    Calculate an index from a key using a hash function.
    h(23) = 3, then access the corresponding position.

An array does not automatically calculate an index from
the value being searched for. Hashing adds that mapping.


19. IMPORTANT INTERVIEW POINTS
------------------------------
1. A hash function maps keys to table indices.
2. A hash table stores data using those calculated indices.
3. A collision occurs when different keys map to the same index.
4. Separate chaining stores multiple keys in a collection per index.
5. Linear probing searches for another available table slot.
6. Average-case hash table operations are often O(1).
7. Worst-case operations can be O(n).
8. Hash tables do not generally maintain sorted order.
9. unordered_map stores key-value pairs.
10. unordered_set stores unique keys.

/*
==================== HASH TABLE ====================

A hash table is a data structure that stores keys at
indices calculated using a hash function.

Example:
    Hash function: h(key) = key % 10

    Key       Hash Calculation       Index
    ------------------------------------------------
    20        20 % 10 = 0              0
    23        23 % 10 = 3              3
    45        45 % 10 = 5              5
    17        17 % 10 = 7              7

    Hash Table:

    Index          Value
    ---------------------
      0              20
      1            EMPTY
      2            EMPTY
      3              23
      4            EMPTY
      5              45
      6            EMPTY
      7              17
      8            EMPTY
      9            EMPTY
    ---------------------

COLLISION EXAMPLE:
    h(20) = 20 % 10 = 0
    h(30) = 30 % 10 = 0

    Both keys map to index 0.
    This is called a HASH COLLISION.

TIME COMPLEXITY:
    Hash calculation : O(1)
    Search            : O(1) average
    Insertion         : O(1) average
    Worst-case search : O(n) for a general hash table

SPACE COMPLEXITY:
    Hash table        : O(m)

    n = number of keys
    m = size of hash table
====================================================


====================================================================
                        END OF HASHING NOTES
====================================================================
*/
