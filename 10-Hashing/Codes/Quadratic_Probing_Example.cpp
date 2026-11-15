// ============================================================
// QUADRATIC PROBING - OPEN ADDRESSING
// Table size M = 11
// h(k) = k % M
// Probe: (h(k) + i * i) % M
// ============================================================

#include <iostream>
#include <vector>
using namespace std;

class QuadraticProbing
{
private:
    static constexpr int M = 11;
    static constexpr int EMPTY = -1;
    static constexpr int DELETED = -2;

    vector<int> table;

    int hashFunction(int key)
    {
        return key % M;
    }

    int probe(int key, int i)
    {
        return (hashFunction(key) + i * i) % M;
    }

public:
    QuadraticProbing()
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

            // If DELETED, continue the probe sequence.
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
                int target = (firstDeleted == -1) ? index : firstDeleted;
                table[target] = key;

                cout << "Inserted " << key
                     << " at index " << target << '\n';
                return true;
            }
        }

        // Reuse a tombstone only after checking the full
        // probe sequence for an existing copy of the key.
        if (firstDeleted != -1)
        {
            table[firstDeleted] = key;
            cout << "Inserted " << key
                 << " at deleted index " << firstDeleted << '\n';
            return true;
        }

        cout << "Probe sequence exhausted. Could not insert "
             << key << ".\n";
        cout << "The table may still have empty slots that this\n";
        cout << "quadratic probe sequence does not visit.\n";
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
    QuadraticProbing ht;

    int keys[] = {22, 1, 13, 11, 24, 33, 44};
    int n = sizeof(keys) / sizeof(keys[0]);

    cout << "QUADRATIC PROBING\n";
    cout << "M = 11\n";
    cout << "h(k) = k % 11\n";
    cout << "h(k, i) = (h(k) + i * i) % 11\n\n";

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

Index : 0  1  2   3   4   5   6      7      8      9   10
Value : 22 1  13  24  11  44  EMPTY  EMPTY  EMPTY  33  EMPTY

COMPLEXITY:
- Expected search/insert/delete: O(1) under suitable load
  and probe-coverage assumptions.
- Worst case: O(M) probes.
- Space: O(M).

IMPORTANT:
The simple i*i probe sequence does not necessarily visit
every slot. Do not assume that an empty slot must be found
just because the table has unused positions.
*/
