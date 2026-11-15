/*
===============================================================================
BUBBLE SORT — COMPLETE C++17 LEARNING FILE
===============================================================================

1. THE BASIC IDEA
-----------------
Bubble Sort repeatedly compares TWO ADJACENT elements.

If the left element is greater than the right element, swap them.
After one complete pass, the largest element among the unsorted elements
has "bubbled" to the last position.

Think of:
    [5,  1,  4,  2,  8]
     ^  ^
Compare adjacent values and move the larger value to the right.

2. COMPLETE DRY RUN
-------------------
Initial array: [5, 1, 4, 2, 8]

Pass 1:
  Compare 5 and 1 -> swap: [1, 5, 4, 2, 8]
  Compare 5 and 4 -> swap: [1, 4, 5, 2, 8]
  Compare 5 and 2 -> swap: [1, 4, 2, 5, 8]
  Compare 5 and 8 -> no swap: [1, 4, 2, 5, 8]
  Largest value (8) is already at the end.

Pass 2:
  Compare 1 and 4 -> no swap
  Compare 4 and 2 -> swap: [1, 2, 4, 5, 8]
  Compare 4 and 5 -> no swap
  The next-largest unsorted value is now in its correct position.

Pass 3:
  No swaps are needed. The array is sorted.
  The optimized algorithm stops early.

3. WHY DOES THE OUTER LOOP SHRINK?
----------------------------------
After pass 1, the final position is correct.
After pass 2, the final two positions are correct.
After pass 3, the final three positions are correct.

Therefore, for pass i, we only need to compare up to n-i-1.

4. COMPLEXITY
-------------
Let n be the number of elements.

Best Case:    O(n)
  This occurs when the input is already sorted AND we use the swapped flag.
  One pass checks all adjacent pairs and performs zero swaps.

Average Case: O(n^2)
Worst Case:   O(n^2)
  Reverse-sorted input causes many comparisons and swaps.

Auxiliary Space: O(1)
  Only a few variables are used. The array is sorted in-place.

5. IMPORTANT PROPERTIES
-----------------------
Stable: YES
  We swap only when arr[j] > arr[j+1], not when they are equal.
  Equal elements therefore do not cross each other.

In-place: YES
Adaptive: YES, with the swapped-flag optimization.
  It detects an already-sorted array in one pass.

Comparison-based: YES
Internal sorting: YES (the data is assumed to fit in main memory).

6. WHEN IS IT USEFUL?
---------------------
Bubble Sort is easy to understand and useful for learning sorting mechanics.
It is generally unsuitable for large inputs because its average and worst
time complexities are quadratic.

7. COMMON MISTAKES
------------------
- Using j < n instead of j < n-i-1 causes an out-of-bounds access.
- Forgetting the swapped flag means the best case remains O(n^2).
- Swapping equal elements with >= can make the algorithm unstable.
- Confusing the number of passes with the number of comparisons.

===============================================================================
*/

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Sorts the vector in ascending order.
void bubbleSort(vector<int>& arr)
{
    int n = static_cast<int>(arr.size());

    // Each pass places one maximum unsorted element at the end.
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;

        // The last i positions are already in their final positions.
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // No swap means the entire array is already sorted.
        if (!swapped)
            break;
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
    vector<int> arr = {5, 1, 4, 2, 8};

    cout << "Before sorting: ";
    printArray(arr);

    bubbleSort(arr);

    cout << "After Bubble Sort: ";
    printArray(arr);

    return 0;
}
