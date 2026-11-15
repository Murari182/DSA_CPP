/*
===============================================================================
INSERTION SORT — COMPLETE C++17 LEARNING FILE
===============================================================================

1. THE CENTRAL IDEA
-------------------
Insertion Sort builds a sorted portion of the array one element at a time.

It works just like sorting playing cards in your hand:
  1. Pick the next card.
  2. Compare it with cards already arranged.
  3. Shift larger cards one position to the right.
  4. Insert the picked card into the empty position.

At every stage:
  - Left side  = sorted portion
  - Right side = not-yet-processed portion

Example:
  Initial: [7, 4, 5, 2]

  Start:
  [7 | 4, 5, 2]
   Sorted | Unsorted

  Insert 4:
  7 is greater than 4, so shift 7 right.
  [4, 7 | 5, 2]

  Insert 5:
  7 is greater than 5, so shift 7 right.
  4 is not greater than 5, so stop.
  [4, 5, 7 | 2]

  Insert 2:
  Shift 7, then 5, then 4 to the right.
  Insert 2 at index 0.
  [2, 4, 5, 7]

2. THE KEY OPERATION: SHIFT, NOT REPEATED SWAPPING
--------------------------------------------------
Suppose the current element (called key) is 3:

  [2, 5, 7, 9, 3]
              ^
             key

Move larger elements one position to the right:

  [2, 5, 7, 9, 9]
  [2, 5, 7, 7, 9]
  [2, 5, 5, 7, 9]

Now index 1 contains 2, which is not greater than 3.
Place key at index 2:

  [2, 3, 5, 7, 9]

Why do we save key first?
Because shifting overwrites array positions. If we did not save the selected
value, we could lose it.

3. LOOP LOGIC
-------------
The first element by itself is considered sorted.
Therefore, begin with i = 1.

For every i:
  a. Store arr[i] in key.
  b. Set j = i - 1.
  c. While j >= 0 and arr[j] > key, shift arr[j] to arr[j+1].
  d. Decrease j.
  e. Put key at arr[j+1].

Why arr[j+1]?
The loop stops either:
  - when j becomes -1, meaning key belongs at index 0; or
  - when arr[j] <= key, meaning key belongs just after j.

4. COMPLEXITY
-------------
Best Case:    O(n)
  The array is already sorted. Each key is compared once and no shifts occur.

Average Case: O(n^2)
  On average, each key may need to move through a substantial part of the
  already-sorted section.

Worst Case:   O(n^2)
  Reverse-sorted input. For each new key, all earlier elements are shifted.
  The total number of shifts is:
      1 + 2 + 3 + ... + (n-1) = n(n-1)/2

Auxiliary Space: O(1)
  Only key, index variables, and a few temporary values are used.
  The original array is modified directly.

5. IMPORTANT PROPERTIES
-----------------------
Stable: YES
  The condition is arr[j] > key.
  Equal values are NOT shifted past one another, so their original relative
  order is preserved.
  If we used arr[j] >= key, equal elements could cross and stability would
  be lost.

In-place: YES
Adaptive: YES
  Nearly sorted input needs very few shifts, so Insertion Sort performs well.

Online: YES
  It can insert each newly arriving item into the sorted portion without
  needing the entire input in advance.

Comparison-based: YES

6. WHEN IS IT USEFUL?
---------------------
- Small arrays.
- Arrays that are already sorted or nearly sorted.
- As the small-partition sorting method inside more advanced algorithms.
- Situations where a simple, low-overhead, in-place stable sort is useful.

It is usually not a good choice for large random or reverse-sorted arrays
because its average and worst-case running time is O(n^2).

7. INSERTION SORT VS BUBBLE SORT
--------------------------------
Both have O(n^2) average and worst-case time and O(1) auxiliary space.
Both can be stable.
Insertion Sort is often faster in practice because it shifts elements and
usually performs fewer writes than Bubble Sort's repeated swaps.

8. COMMON MISTAKES
------------------
- Starting i at 0: the first item is already a sorted one-element section.
- Forgetting to save arr[i] in key before shifting.
- Writing arr[j] >= key and unintentionally losing stability.
- Inserting at arr[j] instead of arr[j+1].
- Using an unsigned index for j: j must be able to become -1.

===============================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

// Sorts the vector in ascending order using the insertion technique.
void insertionSort(vector<int>& arr)
{
    int n = static_cast<int>(arr.size());

    // The element at index 0 alone is already sorted.
    for (int i = 1; i < n; i++)
    {
        int key = arr[i]; // Value that must be inserted in the sorted section.
        int j = i - 1;

        // Shift every element greater than key one position to the right.
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        // j+1 is the correct insertion position for key.
        arr[j + 1] = key;
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
    vector<int> arr = {7, 4, 5, 2, 9, 1};

    cout << "Before sorting: ";
    printArray(arr);

    insertionSort(arr);

    cout << "After Insertion Sort: ";
    printArray(arr);

    return 0;
}
