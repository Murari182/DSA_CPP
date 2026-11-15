/*
===============================================================================
SELECTION SORT — COMPLETE C++17 LEARNING FILE
===============================================================================

1. THE CENTRAL IDEA
-------------------
Selection Sort divides the array into:
  - a sorted section on the left;
  - an unsorted section on the right.

In every pass:
  1. Find the smallest element in the unsorted section.
  2. Swap it with the first element of the unsorted section.
  3. Expand the sorted section by one position.

Example:
  Initial: [64, 25, 12, 22, 11]

  Pass 1: minimum is 11. Swap with 64.
          [11, 25, 12, 22, 64]
           Sorted | Unsorted

  Pass 2: minimum of [25, 12, 22, 64] is 12.
          [11, 12, 25, 22, 64]

  Pass 3: minimum of [25, 22, 64] is 22.
          [11, 12, 22, 25, 64]

  Pass 4: minimum of [25, 64] is 25.
          [11, 12, 22, 25, 64]

  Sorted array: [11, 12, 22, 25, 64]

2. WHY DO WE USE minIndex?
--------------------------
We scan the unsorted section and remember the INDEX of the smallest value.
We do not swap every time we find a smaller value.
After completing the scan, we perform one swap.

This is important:
  - At most n-1 swaps are performed.
  - The algorithm still performs the same number of comparisons regardless
    of whether the input is sorted or reverse sorted.

3. LOOP LOGIC
-------------
For every position i from 0 to n-2:
  a. Assume i is the location of the minimum: minIndex = i.
  b. Search from i+1 to n-1.
  c. If arr[j] < arr[minIndex], update minIndex = j.
  d. After the scan, swap arr[i] and arr[minIndex].

At the end of each pass, arr[i] contains the smallest value from the
previously unsorted section.

4. COMPLEXITY
-------------
Best Case:    O(n^2)
Average Case: O(n^2)
Worst Case:   O(n^2)

Why is even the best case O(n^2)?
Because Selection Sort still scans the entire unsorted section to prove
which element is the minimum. A sorted input does not eliminate those scans.

Number of comparisons:
  (n-1) + (n-2) + ... + 1
  = n(n-1)/2
  = O(n^2)

Number of swaps:
  At most n-1 swaps, so O(n) swaps.

Auxiliary Space: O(1)
  The array is modified directly and only a few variables are used.

5. IMPORTANT PROPERTIES
-----------------------
Stable: NO, in its standard swap-based implementation.
  Example with labelled equal values:
      [4a, 4b, 1]
  The first minimum is 1. Swap it with 4a:
      [1, 4b, 4a]
  The two equal 4s have changed their relative order.
  Therefore, the standard algorithm is unstable.

In-place: YES
Adaptive: NO
  It performs quadratic comparisons even when the input is already sorted.

Comparison-based: YES

6. WHEN IS IT USEFUL?
---------------------
- When minimizing the number of swaps/writes matters.
- Small arrays where simplicity is more important than speed.
- Learning the difference between finding a minimum and inserting an item.

It is generally inefficient for large arrays due to O(n^2) comparisons.

7. COMMON MISTAKES
------------------
- Swapping inside the inner loop instead of after the scan.
- Storing the minimum VALUE when the later swap needs its INDEX.
- Starting the inner loop at i rather than i+1 (not always wrong, but
  unnecessary).
- Claiming best-case O(n) because the input is already sorted.
- Claiming standard Selection Sort is stable.

===============================================================================
*/

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

void selectionSort(vector<int>& arr)
{
    int n = static_cast<int>(arr.size());

    // i is the first position of the unsorted section.
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        // Find the index of the smallest value in the unsorted section.
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        // Place the smallest unsorted value at position i.
        if (minIndex != i)
            swap(arr[i], arr[minIndex]);
    }
}

void printArray(const vector<int>& arr)
{
    for (int value : arr)
        cout << value << " ";
    cout << '\n';
}

int main()
{
    vector<int> arr = {64, 25, 12, 22, 11};

    cout << "Before sorting: ";
    printArray(arr);

    selectionSort(arr);

    cout << "After Selection Sort: ";
    printArray(arr);

    return 0;
}
