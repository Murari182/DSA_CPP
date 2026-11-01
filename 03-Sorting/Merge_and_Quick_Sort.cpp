#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Merge two sorted subarrays arr[left..mid] and arr[mid+1..right]
void merge(vector<int> &arr, int left, int mid, int right)
{
    vector<int> temp;
    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp.push_back(arr[i]);
            i++;
        }
        else
        {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while (i <= mid)
    {
        temp.push_back(arr[i]);
        i++;
    }

    while (j <= right)
    {
        temp.push_back(arr[j]);
        j++;
    }

    for (int k = 0; k < temp.size(); k++)
    {
        arr[left + k] = temp[k];
    }
}

// Merge Sort: O(n log n) Time in all cases, O(n) Auxiliary Space
void merge_sort(vector<int> &arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid = left + (right - left) / 2;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Lomuto Partition Scheme
int partition_array(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort: O(n log n) Average Time, O(n^2) Worst Time, O(log n) Stack Space
void quick_sort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int p = partition_array(arr, low, high);

        quick_sort(arr, low, p - 1);
        quick_sort(arr, p + 1, high);
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
    vector<int> arr1 = {38, 27, 43, 3, 9, 82, 10};
    merge_sort(arr1, 0, arr1.size() - 1);
    cout << "Merge Sort: ";
    print_array(arr1);

    vector<int> arr2 = {10, 80, 30, 90, 40, 50, 70};
    quick_sort(arr2, 0, arr2.size() - 1);
    cout << "Quick Sort: ";
    print_array(arr2);

    return 0;
}
