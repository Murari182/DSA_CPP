// ============================================================
// DOUBLE HASHING - OPEN ADDRESSING
// Table size M = 11
// h1(k) = k % M
// h2(k) = 1 + (k % (M - 1))
// Probe: (h1(k) + i * h2(k)) % M
// ============================================================

#include <iostream>
#include <vector>
using namespace std;

class DoubleHashing
{
private:
    static constexpr int M = 11;
    static constexpr int EMPTY = -1;
    static constexpr int DELETED = -2;

    vector<int> table;

    int h1(int key)
    {
        return key % M;
    }

    int h2(int key)
    {
        // Step is always between 1 and M - 1.
        // Since M is prime, every such step is coprime to M.
        return 1 + (key % (M - 1));
    }

    int probe(int key, int i)
    {
        return (h1(key) + i * h2(key)) % M;
    }

public:
    DoubleHashing()
    {
        table.assign(M, EMPTY);
    }

    bool search(int key)
    {
        for (int i = 0; i < M; i++)
        {
            int index = probe(key, i);

            if (table[index] == EMPTY)
                return false;

            if (table[index] == key)
                return true;

            // DELETED is not a stopping point. Continue probing.
        }

        return false;
    }

    bool insert(int key)
    {
        int firstDeleted = -1;

        for (int i = 0; i < M; i++)
        {
            int index = probe(key, i);

            if (table[index] == key)
            {
                cout << key << " already exists.\n";
                return false;
            }

            if (table[index] == DELETED && firstDeleted == -1)
            {
                firstDeleted = index;
            }

            if (table[index] == EMPTY)
            {
                // Reuse the earliest tombstone if one was seen.
                int target = (firstDeleted == -1) ? index : firstDeleted;
                table[target] = key;

                cout << "Inserted " << key
                     << " at index " << target << '\n';
                return true;
            }
        }

        // The probe sequence was exhausted. A tombstone can still
        // be reused, but only after checking the full sequence for
        // a duplicate key.
        if (firstDeleted != -1)
        {
            table[firstDeleted] = key;
            cout << "Inserted " << key
                 << " at deleted index " << firstDeleted << '\n';
            return true;
        }

        cout << "Hash table is full. Cannot insert " << key << ".\n";
        return false;
    }

    bool removeKey(int key)
    {
        for (int i = 0; i < M; i++)
        {
            int index = probe(key, i);

            if (table[index] == EMPTY)
                return false;

            if (table[index] == key)
            {
                table[index] = DELETED;
                return true;
            }
        }

        return false;
    }

    void display()
    {
        cout << "\nIndex : ";
        for (int i = 0; i < M; i++)
            cout << i << "\t";

        cout << "\nValue : ";
        for (int i = 0; i < M; i++)
        {
            if (table[i] == EMPTY)
                cout << "EMPTY\t";
            else if (table[i] == DELETED)
                cout << "DEL\t";
            else
                cout << table[i] << "\t";
        }
        cout << '\n';
    }
};

int main()
{
    DoubleHashing ht;

    int keys[] = {22, 1, 13, 11, 24, 33, 44};
    int n = sizeof(keys) / sizeof(keys[0]);

    cout << "DOUBLE HASHING\n";
    cout << "M = 11\n";
    cout << "h1(k) = k % 11\n";
    cout << "h2(k) = 1 + (k % 10)\n\n";

    for (int i = 0; i < n; i++)
        ht.insert(keys[i]);

    cout << "\nFinal table:\n";
    ht.display();

    cout << "\nSearch 33: "
         << (ht.search(33) ? "Found" : "Not found") << '\n';

    cout << "Delete 11: "
         << (ht.removeKey(11) ? "Deleted" : "Not found") << '\n';

    cout << "\nTable after deletion:\n";
    ht.display();

    return 0;
}

/*
EXPECTED TABLE BEFORE DELETION:

Index : 0  1  2  3      4   5   6      7   8   9      10
Value : 22 1  13 EMPTY  11  44  EMPTY  24  33  EMPTY  EMPTY

COMPLEXITY:
- Expected search/insert/delete: O(1), with suitable hashing
  and a controlled load factor.
- Worst-case search/insert/delete: O(M).
- Space: O(M).
*/
