#include <iostream>
#include <vector>
using namespace std;

// Linear Search: O(n) Time, O(1) Space
int linear_search(const vector<int> &arr, int key)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == key)
        {
            return i;
        }
    }
    return -1;
}

// Iterative Binary Search: O(log n) Time, O(1) Space
int binary_search_iterative(const vector<int> &arr, int key)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

// Recursive Binary Search: O(log n) Time, O(log n) Stack Space
int binary_search_recursive(const vector<int> &arr, int low, int high, int key)
{
    if (low > high)
    {
        return -1;
    }

    int mid = low + (high - low) / 2;

    if (arr[mid] == key)
    {
        return mid;
    }
    else if (key < arr[mid])
    {
        return binary_search_recursive(arr, low, mid - 1, key);
    }
    else
    {
        return binary_search_recursive(arr, mid + 1, high, key);
    }
}

int main()
{
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80};

    cout << "Linear Search (50): Index " << linear_search(arr, 50) << endl;
    cout << "Iterative Binary Search (60): Index " << binary_search_iterative(arr, 60) << endl;
    cout << "Recursive Binary Search (20): Index " << binary_search_recursive(arr, 0, arr.size() - 1, 20) << endl;
    cout << "Binary Search (99): Index " << binary_search_iterative(arr, 99) << endl;

    return 0;
}
