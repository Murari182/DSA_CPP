/*
===============================================================================
MERGE SORT — COMPLETE C++17 LEARNING FILE
===============================================================================

1. THE CENTRAL IDEA: DIVIDE AND CONQUER
---------------------------------------
Merge Sort follows the Divide and Conquer strategy.

DIVIDE:
  Split the array into two smaller halves.

CONQUER:
  Recursively sort the left half and the right half.

COMBINE:
  Merge the two sorted halves into one sorted section.

Example:
  [38, 27, 43, 3, 9, 82, 10]

  Divide:
             [38, 27, 43, 3, 9, 82, 10]
                  /                 \\
          [38, 27, 43]           [3, 9, 82, 10]
            /      \\              /       \\
        [38]     [27,43]        [3,9]    [82,10]
                  / \\            / \\      / \\
                [27][43]        [3][9]   [82][10]

  Conquer:
    Single-element arrays are already sorted.
    Merge [27] and [43] -> [27,43]
    Merge [38] and [27,43] -> [27,38,43]
    Similarly sort the right side -> [3,9,10,82]

  Combine:
    Merge [27,38,43] and [3,9,10,82]
    Result -> [3,9,10,27,38,43,82]

2. WHY DOES MERGING WORK?
-------------------------
The merge function receives TWO ALREADY-SORTED ranges:
  Left:  [2, 8, 15]
  Right: [3, 9, 12]

Compare the first unused values:
  2 vs 3 -> take 2
  8 vs 3 -> take 3
  8 vs 9 -> take 8
  15 vs 9 -> take 9
  15 vs 12 -> take 12
  Copy remaining 15

Merged result:
  [2, 3, 8, 9, 12, 15]

The key fact is that the smallest remaining value must be at the front of
one of the two sorted ranges. Therefore, choosing the smaller front value
at every step produces a sorted result.

3. RECURSION AND BASE CASE
--------------------------
mergeSort(arr, left, right)

If left >= right:
  The range has zero or one element.
  It is already sorted, so return.

Otherwise:
  mid = left + (right-left)/2
  Sort left..mid
  Sort mid+1..right
  Merge both sorted ranges

The base case is essential. Without it, recursion would never stop.

4. COMPLEXITY
-------------
Best Case:    O(n log n)
Average Case: O(n log n)
Worst Case:   O(n log n)

Why?
  - Each level of recursion processes a total of n elements during merging.
  - The array is divided approximately in half at every level.
  - The number of levels is approximately log2(n).
  - Total work = n * log2(n) = O(n log n).

Auxiliary Space: O(n)
  Temporary arrays are used during merging.
  The recursion stack additionally uses O(log n) space.
  The O(n) temporary storage dominates.

5. IMPORTANT PROPERTIES
-----------------------
Stable: YES, in this implementation.
  During merging, when left and right values are equal, we take from the
  LEFT range first (arr[i] <= arr[j]).
  This preserves the original relative order of equal elements.

In-place: NO, in this standard array implementation.
  It needs temporary storage proportional to n.

Adaptive: NO, not in this standard implementation.
  It performs the divide-and-merge work even if the input is already sorted.

Comparison-based: YES

6. WHEN IS IT USEFUL?
---------------------
- Large datasets where predictable O(n log n) time is important.
- Linked-list sorting (merging linked lists can be done with little extra
  storage).
- Stable sorting requirements.
- External sorting, where data is too large to fit into memory at once.

7. RECURRENCE RELATION
----------------------
T(n) = 2T(n/2) + O(n)

Meaning:
  2T(n/2): recursively sort two halves.
  O(n):     merge the two sorted halves.

Solving this recurrence gives:
  T(n) = O(n log n)

8. COMMON MISTAKES
------------------
- Forgetting the base case left >= right.
- Calculating mid as (left + right)/2 in code where integer overflow is
  possible. Use left + (right-left)/2.
- Using incorrect range boundaries.
- Forgetting to copy remaining elements from either half.
- Using < instead of <= when choosing from the left on equal values,
  which can destroy stability.
- Forgetting that the standard implementation needs O(n) extra space.

===============================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

// Merge two sorted ranges:
// first range  = arr[left ... mid]
// second range = arr[mid+1 ... right]
void merge(vector<int>& arr, int left, int mid, int right)
{
    vector<int> temp;

    int i = left;       // Current index in the left range.
    int j = mid + 1;    // Current index in the right range.

    // Pick the smaller front element from the two sorted ranges.
    while (i <= mid && j <= right)
    {
        // <= is intentional: it preserves stability for equal values.
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

    // Copy any remaining elements from the left range.
    while (i <= mid)
    {
        temp.push_back(arr[i]);
        i++;
    }

    // Copy any remaining elements from the right range.
    while (j <= right)
    {
        temp.push_back(arr[j]);
        j++;
    }

    // Copy the merged sorted values back into the original array.
    for (int k = 0; k < static_cast<int>(temp.size()); k++)
        arr[left + k] = temp[k];
}

void mergeSort(vector<int>& arr, int left, int right)
{
    // Base case: a range of zero or one element is already sorted.
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    // Divide and sort the left half.
    mergeSort(arr, left, mid);

    // Divide and sort the right half.
    mergeSort(arr, mid + 1, right);

    // Combine the two sorted halves.
    merge(arr, left, mid, right);
}

void printArray(const vector<int>& arr)
{
    for (int value : arr)
        cout << value << " ";
    cout << '\n';
}

int main()
{
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    cout << "Before sorting: ";
    printArray(arr);

    if (!arr.empty())
        mergeSort(arr, 0, static_cast<int>(arr.size()) - 1);

    cout << "After Merge Sort: ";
    printArray(arr);

    return 0;
}
