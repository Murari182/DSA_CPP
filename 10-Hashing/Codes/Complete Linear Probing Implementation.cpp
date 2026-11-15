
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

/*
===========================================================
                    LINEAR PROBING
===========================================================

Linear Probing is a collision resolution technique used
in Open Addressing.

When a collision occurs, we sequentially search for the
next available slot in the hash table.

Hash Function:
    h(key) = key % capacity

Probing Function:
    h_i(key) = (h(key) + i) % capacity

Where:
    i = 0, 1, 2, 3, ...
    capacity = Total number of slots

Three possible states of every slot:

    EMPTY     = 0
    OCCUPIED  = 1
    DELETED   = 2

We use two vectors:

    arr[]    -> Stores actual keys.
    status[] -> Stores the state of every slot.

===========================================================
*/

class hashtable
{
private:

    vector<int> arr;
    vector<int> status;

    int cap;       // Total capacity of hash table
    int size;      // Number of currently stored elements

public:

    /*
    =======================================================
                    1. CONSTRUCTOR
    =======================================================

    Purpose:
        Initialize the hash table.

    Parameters:
        cap -> Capacity provided by the user.

    Working:
        1. Initialize capacity.
        2. Initialize size to zero.
        3. Create arr with cap elements.
        4. Create status with cap elements.
        5. Initialize every status as EMPTY (0).

    Time Complexity:
        O(cap)

    Space Complexity:
        O(cap)
    */

    hashtable(int cap)
    {
        this->cap = cap;

        size = 0;

        arr.resize(cap);
        status.resize(cap, 0);
    }


    /*
    =======================================================
                    2. HASH FUNCTION
    =======================================================

    Purpose:
        Convert a key into a valid array index.

    Formula:
        h(key) = key % cap

    Example:
        key = 24
        cap = 7

        h(24) = 24 % 7 = 3

    Note:
        The normalization below also handles negative keys.

    Time Complexity:
        O(1)

    Space Complexity:
        O(1)
    */

    int hashFunction(int key)
    {
        return ((key % cap) + cap) % cap;
    }


    /*
    =======================================================
                    3. INSERTION
    =======================================================

    Purpose:
        Insert a key using Linear Probing.

    Working:

        STEP 1:
            Calculate original hash index.

        STEP 2:
            Initialize firstDeleted = -1.

        STEP 3:
            Start probing from original index.

        STEP 4:
            Calculate current index:

            index = (oindex + i) % cap

        STEP 5:
            Check the slot status.

            CASE A: OCCUPIED

                If the key already exists:
                    Duplicate insertion is prevented.

                Otherwise:
                    Continue probing.

            CASE B: DELETED

                Remember the first deleted index.

                Do not insert immediately because the
                same key might exist later in the sequence.

            CASE C: EMPTY

                If a deleted slot was found:
                    Insert at firstDeleted.

                Otherwise:
                    Insert at current index.

        STEP 6:
            If all positions are checked:

                If firstDeleted exists:
                    Reuse that position.

                Otherwise:
                    Hash table is full.

    Time Complexity:

        Best Case: O(1)
        Average:   O(1) under suitable hashing and low load
        Worst:     O(cap) = O(n) when cap = O(n)

    Space Complexity:
        O(1) auxiliary space.

    =======================================================
    */

    void insert(int key)
    {
        int oindex = hashFunction(key);

        // Stores the first encountered deleted position.
        int firstDeleted = -1;

        for(int i = 0; i < cap; i++)
        {
            int index = (oindex + i) % cap;

            // CASE 1: OCCUPIED
            if(status[index] == 1)
            {
                // Check for duplicate key.
                if(arr[index] == key)
                {
                    cout << "Duplicate key!" << endl;
                    return;
                }
            }

            // CASE 2: DELETED
            else if(status[index] == 2)
            {
                // Remember the first deleted position.
                if(firstDeleted == -1)
                {
                    firstDeleted = index;
                }
            }

            // CASE 3: EMPTY
            else if(status[index] == 0)
            {
                // Reuse the first deleted position if available.
                int insertIndex;

                if(firstDeleted != -1)
                {
                    insertIndex = firstDeleted;
                }
                else
                {
                    insertIndex = index;
                }

                arr[insertIndex] = key;
                status[insertIndex] = 1;

                size++;

                cout << "Element inserted at index "
                     << insertIndex << endl;

                return;
            }
        }

        // Entire table was checked.
        // There might still be a reusable DELETED slot.

        if(firstDeleted != -1)
        {
            arr[firstDeleted] = key;
            status[firstDeleted] = 1;

            size++;

            cout << "Element inserted at index "
                 << firstDeleted << endl;

            return;
        }

        cout << "Hash table is full!" << endl;
    }


    /*
    =======================================================
                    4. SEARCHING
    =======================================================

    Purpose:
        Find the index of a given key.

    Working:

        STEP 1:
            Calculate original hash index.

        STEP 2:
            Start probing.

        STEP 3:
            Calculate current index.

        STEP 4:
            Check status.

            EMPTY:
                Key does not exist.
                Stop searching.

            OCCUPIED:
                Compare arr[index] with key.

                If equal:
                    Return index.

                Otherwise:
                    Continue probing.

            DELETED:
                Continue probing.

        STEP 5:
            If all positions are checked:
                Return -1.

    IMPORTANT:

        We stop at EMPTY because a valid insertion sequence
        cannot place the key beyond an EMPTY slot.

        We continue through DELETED because a key may
        exist further along the probe sequence.

    Time Complexity:

        Best Case: O(1)
        Average:   O(1) under suitable hashing and low load
        Worst:     O(cap) = O(n) when cap = O(n)

    Space Complexity:
        O(1)

    =======================================================
    */

    int search(int key)
    {
        int oindex = hashFunction(key);

        for(int i = 0; i < cap; i++)
        {
            int index = (oindex + i) % cap;

            // EMPTY means key cannot exist further.
            if(status[index] == 0)
            {
                return -1;
            }

            // Compare only OCCUPIED slots.
            if(status[index] == 1 && arr[index] == key)
            {
                return index;
            }

            // If DELETED, continue probing.
        }

        return -1;
    }


    /*
    =======================================================
                    5. DELETION
    =======================================================

    Purpose:
        Delete an existing key.

    Working:

        STEP 1:
            Calculate original hash index.

        STEP 2:
            Start probing.

        STEP 3:
            Calculate current index.

        STEP 4:
            Check status.

            EMPTY:
                Key does not exist.
                Stop.

            OCCUPIED:
                Compare key.

                If matched:
                    Mark status as DELETED (2).
                    Decrease size.
                    Return.

            DELETED:
                Continue probing.

        WHY NOT MARK AS EMPTY?

            Suppose:

            Index 3 -> 10
            Index 4 -> 17
            Index 5 -> 24

            If we delete 17 and mark index 4 EMPTY,
            searching for 24 stops at index 4.

            Therefore, we use DELETED (tombstone).

    Time Complexity:

        Best Case: O(1)
        Average:   O(1) under suitable hashing and low load
        Worst:     O(cap) = O(n) when cap = O(n)

    Space Complexity:
        O(1)

    =======================================================
    */

    void remove(int key)
    {
        int oindex = hashFunction(key);

        for(int i = 0; i < cap; i++)
        {
            int index = (oindex + i) % cap;

            // Empty slot means key doesn't exist.
            if(status[index] == 0)
            {
                cout << "Key does not exist!" << endl;
                return;
            }

            // Key found.
            if(status[index] == 1 && arr[index] == key)
            {
                // Mark slot as DELETED.
                status[index] = 2;

                size--;

                cout << "Key deleted from index "
                     << index << endl;

                return;
            }

            // If DELETED, continue probing.
        }

        cout << "Key does not exist!" << endl;
    }


    /*
    =======================================================
                    6. DISPLAY
    =======================================================

    Purpose:
        Display the complete hash table.

    Working:
        Traverse every index and display:

            Index
            Value
            Status

    Time Complexity:
        O(cap)

    Space Complexity:
        O(1)
    */

    void display()
    {
        cout << "\n========== HASH TABLE ==========\n";

        cout << left
             << setw(12) << "Index"
             << setw(12) << "Value"
             << "Status" << endl;

        cout << "--------------------------------\n";

        for(int i = 0; i < cap; i++)
        {
            cout << left << setw(12) << i;

            if(status[i] == 0)
            {
                cout << setw(12) << "-"
                     << "EMPTY" << endl;
            }

            else if(status[i] == 1)
            {
                cout << setw(12) << arr[i]
                     << "OCCUPIED" << endl;
            }

            else
            {
                cout << setw(12) << "-"
                     << "DELETED" << endl;
            }
        }

        cout << "================================\n";
    }


    /*
    =======================================================
                    7. LOAD FACTOR
    =======================================================

    Definition:

        Load Factor is the ratio of the number of currently
        stored elements to the total number of slots.

    Formula:

                  Number of elements
        alpha = ----------------------
                   Table capacity

                  size
        alpha = -------
                   cap

    Example:

        size = 4
        cap  = 7

        alpha = 4 / 7

        alpha = 0.5714

    Interpretation:

        Lower load factor:
            More free slots.
            Usually fewer probes.

        Higher load factor:
            Fewer free slots.
            Usually more probes.

    IMPORTANT:

        For Open Addressing:

            0 <= alpha <= 1

        For Separate Chaining:

            alpha can be greater than 1.

    Time Complexity:
        O(1)

    Space Complexity:
        O(1)

    =======================================================
    */

    double loadFactor()
    {
        return (double)size / cap;
    }

};


/*
===========================================================
                        MAIN FUNCTION
===========================================================

Testing all basic operations.

===========================================================
*/

int main()
{
    hashtable h(7);

    // INSERTION
    h.insert(10);
    h.insert(17);
    h.insert(24);
    h.insert(31);

    // DISPLAY
    h.display();

    // SEARCHING
    cout << "\nSearch 24: "
         << h.search(24) << endl;

    cout << "Search 50: "
         << h.search(50) << endl;

    // DELETION
    h.remove(17);

    // SEARCH AFTER DELETION
    cout << "\nSearch 17: "
         << h.search(17) << endl;

    cout << "Search 24: "
         << h.search(24) << endl;

    // LOAD FACTOR
    cout << "\nLoad Factor: "
         << h.loadFactor() << endl;

    // FINAL DISPLAY
    h.display();

    return 0;
}
