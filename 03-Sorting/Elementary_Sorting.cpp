#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Bubble Sort: O(n^2) worst/average, O(n) best case with swapped flag
void bubble_sort(vector<int> &arr)
{
    int n = arr.size();

    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped, array is already sorted
        if (!swapped)
        {
            break;
        }
    }
}

// Selection Sort: O(n^2) in all cases, O(1) auxiliary space
void selection_sort(vector<int> &arr)
{
    int n = arr.size();

    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }

        if (min_idx != i)
        {
            swap(arr[i], arr[min_idx]);
        }
    }
}

// Insertion Sort: O(n^2) worst/average, O(n) best case
void insertion_sort(vector<int> &arr)
{
    int n = arr.size();

    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void print_array(const vector<int> &arr)
{
    for (int x : arr)
    {
        cout << x << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> a1 = {64, 34, 25, 12, 22, 11, 90};
    bubble_sort(a1);
    cout << "Bubble Sort: ";
    print_array(a1);

    vector<int> a2 = {64, 25, 12, 22, 11};
    selection_sort(a2);
    cout << "Selection Sort: ";
    print_array(a2);

    vector<int> a3 = {12, 11, 13, 5, 6};
    insertion_sort(a3);
    cout << "Insertion Sort: ";
    print_array(a3);

    return 0;
}
