#include <iostream>
using namespace std;

// Class demonstrating encapsulation, constructor, this pointer, and friend class
class Box
{
    int length;
    int width;

public:
    Box(int length, int width)
    {
        this->length = length;
        this->width = width;
    }

    friend class Inspector;
};

class Inspector
{
public:
    void print_area(Box &b)
    {
        cout << "Box Area: " << (b.length * b.width) << endl;
    }
};

// Pass by value: modifies a local copy
void increment_by_value(int x)
{
    x = x + 10;
}

// Pass by pointer: modifies original variable via address
void increment_by_pointer(int *x)
{
    if (x != NULL)
    {
        *x = *x + 10;
    }
}

// Pass by reference: modifies original variable directly
void increment_by_reference(int &x)
{
    x = x + 10;
}

int main()
{
    // 1. Pointers and Dereferencing
    int val = 42;
    int *ptr = &val;

    cout << "Value of val: " << val << endl;
    cout << "Dereferenced ptr: " << *ptr << endl;

    // 2. Pass by value vs pointer vs reference
    increment_by_value(val);
    cout << "After pass by value: " << val << endl;

    increment_by_pointer(&val);
    cout << "After pass by pointer: " << val << endl;

    increment_by_reference(val);
    cout << "After pass by reference: " << val << endl;

    // 3. Dynamic Memory Allocation (Heap memory)
    int *dyn_int = new int(100);
    cout << "Dynamically allocated int: " << *dyn_int << endl;
    delete dyn_int;
    dyn_int = NULL;

    // Dynamic Array Allocation
    int n = 5;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = (i + 1) * 10;
    }

    cout << "Dynamic array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;
    arr = NULL;

    // 4. Classes, this pointer, and friend class
    Box b1(10, 5);
    Inspector insp;
    insp.print_area(b1);

    return 0;
}
