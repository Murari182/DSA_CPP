// ============================================================
// CUCKOO HASHING - TWO TABLE IMPLEMENTATION
// Example based on the given examination question.
//
// M = 7
// h1(k) = k % M
// h2(k) = ((k % M) + 3) % M
//
// Keys: 23, 74, 73, 76, 28, 25, 35, 17
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class CuckooHashing
{
private:
    static const int M = 7;
    static constexpr int EMPTY = -1;
    static const int MAX_KICKS = 2 * M + 1;

    vector<int> table1;
    vector<int> table2;

    // First hash function: position in Table 1
    int h1(int key)
    {
        return key % M;
    }

    // Second hash function: position in Table 2
    int h2(int key)
    {
        return ((key % M) + 3) % M;
    }

public:
    // Constructor: initially every slot is empty
    CuckooHashing()
    {
        table1.assign(M, EMPTY);
        table2.assign(M, EMPTY);
    }

    // Insert a key using alternating displacement
    bool insert(int key)
    {
        int currentKey = key;

        // Start with Table 1.
        bool useTable1 = true;

        for (int kick = 0; kick < MAX_KICKS; kick++)
        {
            int position;

            if (useTable1)
            {
                position = h1(currentKey);

                cout << "Trying " << currentKey
                     << " in Table 1, index " << position << '\n';

                // Put currentKey in its permitted position.
                // The old occupant, if any, is moved into currentKey.
                swap(currentKey, table1[position]);
            }
            else
            {
                position = h2(currentKey);

                cout << "Trying " << currentKey
                     << " in Table 2, index " << position << '\n';

                swap(currentKey, table2[position]);
            }

            // If currentKey is EMPTY, the slot was empty.
            // The key has been inserted successfully.
            if (currentKey == EMPTY)
            {
                cout << "Insertion successful.\n\n";
                return true;
            }

            // Otherwise, currentKey is the displaced key.
            cout << "Displaced key: " << currentKey << '\n';

            // Next try the other table.
            useTable1 = !useTable1;
        }

        // Too many displacements: a cycle or difficult placement
        // may exist. A production implementation should rebuild
        // both tables with new hash functions and/or larger capacity.
        cout << "Insertion could not finish within the kick limit.\n";
        cout << "Rehashing or a larger table is required.\n\n";

        return false;
    }

    // Search checks only the two permitted positions.
    bool search(int key)
    {
        int pos1 = h1(key);
        int pos2 = h2(key);

        if (table1[pos1] == key)
        {
            cout << key << " found in Table 1 at index "
                 << pos1 << '\n';
            return true;
        }

        if (table2[pos2] == key)
        {
            cout << key << " found in Table 2 at index "
                 << pos2 << '\n';
            return true;
        }

        cout << key << " not found.\n";
        return false;
    }

    // Delete checks the two permitted positions.
    bool removeKey(int key)
    {
        int pos1 = h1(key);

        if (table1[pos1] == key)
        {
            table1[pos1] = EMPTY;
            return true;
        }

        int pos2 = h2(key);

        if (table2[pos2] == key)
        {
            table2[pos2] = EMPTY;
            return true;
        }

        return false;
    }

    void display()
    {
        cout << "\n========== FINAL HASH TABLES ==========\n";

        cout << "\nTable 1 (using h1):\n";
        cout << "Index : ";
        for (int i = 0; i < M; i++)
            cout << i << "\t";

        cout << "\nValue : ";
        for (int i = 0; i < M; i++)
        {
            if (table1[i] == EMPTY)
                cout << "-\t";
            else
                cout << table1[i] << "\t";
        }

        cout << "\n\nTable 2 (using h2):\n";
        cout << "Index : ";
        for (int i = 0; i < M; i++)
            cout << i << "\t";

        cout << "\nValue : ";
        for (int i = 0; i < M; i++)
        {
            if (table2[i] == EMPTY)
                cout << "-\t";
            else
                cout << table2[i] << "\t";
        }

        cout << "\n=======================================\n";
    }
};

int main()
{
    CuckooHashing hashTable;

    int keys[] = {23, 74, 73, 76, 28, 25, 35, 17};
    int n = sizeof(keys) / sizeof(keys[0]);

    cout << "CUCKOO HASHING\n";
    cout << "M = 7\n";
    cout << "h1(k) = k % 7\n";
    cout << "h2(k) = ((k % 7) + 3) % 7\n\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Inserting key: " << keys[i] << '\n';

        if (!hashTable.insert(keys[i]))
        {
            cout << "Stop: a rehash is required for this input.\n";
            return 0;
        }
    }

    hashTable.display();

    cout << "\nSearching examples:\n";
    hashTable.search(28);
    hashTable.search(100);

    cout << "\nDeleting key 28:\n";
    if (hashTable.removeKey(28))
        cout << "28 deleted successfully.\n";
    else
        cout << "28 was not present.\n";

    cout << "\nTables after deletion:\n";
    hashTable.display();

    return 0;
}

/*
EXPECTED FINAL TABLES BEFORE THE DEMONSTRATION DELETION:

Table 1:
Index : 0  1  2   3   4   5  6
Value : 35 -  23  17  25  -  76

Table 2:
Index : 0   1  2  3   4  5  6
Value : 74  -  -  28  -  -  73

TIME COMPLEXITY:
- Hash calculation: O(1)
- Search: O(1) worst case for two candidate positions
- Delete: O(1) worst case for two candidate positions
- Insert: expected O(1) under suitable hashing/load assumptions;
  worst case can be longer and rehashing can take O(n).

SPACE COMPLEXITY:
- Two tables, each of size M: O(2M) = O(M)
- Auxiliary insertion variables: O(1)
*/
