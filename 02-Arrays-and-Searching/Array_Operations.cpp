#include <iostream>
using namespace std;

class Array
{
    int arr[100];
    int cap;
    int size;

public:
    Array(int cap)
    {
        this->cap = cap;
        size = 0;
    }

    // Insert at the end: O(1)
    void push_back(int val)
    {
        if (size == cap)
        {
            cout << "Array is Full" << endl;
            return;
        }
        arr[size] = val;
        size++;
    }

    // Insert at a given index: O(n)
    void insert_at(int val, int pos)
    {
        if (size == cap)
        {
            cout << "Array is Full" << endl;
            return;
        }
        if (pos < 0 || pos > size)
        {
            cout << "Invalid Position" << endl;
            return;
        }

        // Shift elements to the right
        for (int i = size; i > pos; i--)
        {
            arr[i] = arr[i - 1];
        }

        arr[pos] = val;
        size++;
    }

    // Delete element at a given index: O(n)
    void delete_at(int pos)
    {
        if (size == 0)
        {
            cout << "Array is Empty" << endl;
            return;
        }
        if (pos < 0 || pos >= size)
        {
            cout << "Invalid Position" << endl;
            return;
        }

        // Shift elements to the left
        for (int i = pos; i < size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

        size--;
    }

    // Reverse the array in-place: O(n) time, O(1) space
    void reverse_array()
    {
        int start = 0;
        int end = size - 1;

        while (start < end)
        {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;

            start++;
            end--;
        }
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Array a1(20);

    for (int i = 1; i <= 5; i++)
    {
        a1.push_back(i * 10);
    }

    cout << "Initial Array: ";
    a1.print();

    a1.insert_at(25, 2);
    cout << "After inserting 25 at index 2: ";
    a1.print();

    a1.delete_at(3);
    cout << "After deleting index 3: ";
    a1.print();

    a1.reverse_array();
    cout << "After reversing: ";
    a1.print();

    return 0;
}
