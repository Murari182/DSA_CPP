
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
===============================================================================
                         BINARY HEAP - COMPLETE NOTES
===============================================================================

1. WHAT IS A BINARY HEAP?
-------------------------
A Binary Heap is a COMPLETE BINARY TREE that satisfies the HEAP PROPERTY.

Complete Binary Tree:
- Every level is completely filled except possibly the last level.
- The last level is filled from LEFT TO RIGHT.

A Binary Heap is commonly implemented using an ARRAY instead of pointers.

TYPES OF BINARY HEAP:
---------------------
1. MAX HEAP:
   Every parent is greater than or equal to its children.
   Parent >= Left Child
   Parent >= Right Child
   The ROOT contains the MAXIMUM element.

2. MIN HEAP:
   Every parent is less than or equal to its children.
   Parent <= Left Child
   Parent <= Right Child
   The ROOT contains the MINIMUM element.

This program implements a MAX HEAP.

IMPORTANT:
- A heap is NOT a completely sorted array.
- Only the parent-child relationship must satisfy the heap property.
- A heap is useful for Priority Queues, Heap Sort, and scheduling.

-------------------------------------------------------------------------------
2. ARRAY REPRESENTATION (ZERO-BASED INDEXING)
-------------------------------------------------------------------------------

For a node at index i:

    Parent index      = (i - 1) / 2       (if i > 0)
    Left child index  = 2 * i + 1
    Right child index = 2 * i + 2

Example:

                 100
                /   \
              50     70
             /  \   /
            20  40 60

Array = {100, 50, 70, 20, 40, 60}

Index =   0   1   2   3   4   5

For index 1:
    Parent = (1 - 1) / 2 = 0
    Left   = 2 * 1 + 1 = 3
    Right  = 2 * 1 + 2 = 4

For a heap containing n elements:
    Height = O(log n)

-------------------------------------------------------------------------------
3. TIME COMPLEXITY SUMMARY
-------------------------------------------------------------------------------

Operation                         Time Complexity
--------------------------------------------------
Get maximum (root)                 O(1)
Insert                             O(log n) worst case
Heapify Up                         O(log n) worst case
Heapify Down                       O(log n) worst case
Delete by index                    O(log n) worst case
Build Heap                         O(n)
Print Heap                         O(n)
Heap Sort                          O(n log n)

Auxiliary Space:
    Iterative heap operations      O(1)
    Heap Sort                      O(1)

The array in this program has a fixed capacity of 100 elements.

===============================================================================
*/

class Binary_Heap {

public:

    int arr[100];  // Stores heap elements
    int size;      // Number of elements currently in the heap

    /*
    ---------------------------------------------------------------------------
    CONSTRUCTOR
    ---------------------------------------------------------------------------

    Initializes an empty heap.

    Time Complexity:  O(1)
    Space Complexity: O(1)
    */
    Binary_Heap() {
        size = 0;
    }

    /*
    ---------------------------------------------------------------------------
    HEAPIFY UP
    ---------------------------------------------------------------------------

    THEORY:
    Heapify Up restores the Max Heap property by moving a node upward.

    LOGIC:
    1. Start from the inserted element's index.
    2. Find its parent using (i - 1) / 2.
    3. If the current element is greater than its parent, swap them.
    4. Continue until the parent is larger or the root is reached.

    WHY IS IT USED?
    After insertion, the new element is placed at the end to preserve the
    complete binary tree structure. Its value may violate the heap property,
    so we move it upward until the property is restored.

    Time Complexity:
        Worst case: O(log n)
        Best case:  O(1)
    Auxiliary Space: O(1)
    */
    void heapify_up(int index) {

        while (index > 0) {

            int parent = (index - 1) / 2;

            if (arr[index] > arr[parent]) {

                swap(arr[index], arr[parent]);

                // Continue from the parent's previous position.
                index = parent;
            }
            else {
                // The Max Heap property is satisfied.
                break;
            }
        }
    }

    /*
    ---------------------------------------------------------------------------
    INSERT
    ---------------------------------------------------------------------------

    THEORY:
    Insertion adds a new element while preserving the complete binary tree.

    LOGIC:
    1. Check whether the array is full.
    2. Insert the element at arr[size].
    3. Increase size.
    4. Call heapify_up() to restore the Max Heap property.

    Example:
        Heap = {100, 50, 70}
        Insert 90

        Initially: {100, 50, 70, 90}
        Compare 90 with parent 50 and swap.

        Result: {100, 90, 70, 50}

    Time Complexity:
        Worst case: O(log n)
        Best case:  O(1)
    Auxiliary Space: O(1)
    */
    void insert(int value) {

        if (size == 100) {
            cout << "Heap is full" << endl;
            return;
        }

        arr[size] = value;
        int index = size;
        size++;

        heapify_up(index);
    }

    /*
    ---------------------------------------------------------------------------
    HEAPIFY DOWN
    ---------------------------------------------------------------------------

    THEORY:
    Heapify Down restores the Max Heap property by moving a node downward.

    LOGIC:
    1. Assume the current node is the largest.
    2. Calculate the left and right child indices.
    3. Compare the current node with its existing children.
    4. Identify the largest among the three.
    5. If a child is larger, swap with that child.
    6. Continue downward until no violation remains.

    WHY COMPARE THE RIGHT CHILD WITH arr[largest]?
    The left child may already be larger than the current node.
    Therefore, the right child must be compared with the largest candidate
    found so far, not necessarily with the original parent.

    Time Complexity:
        Worst case: O(log n)
        Best case:  O(1)
    Auxiliary Space: O(1)

    Used in:
        - Deletion
        - Build Heap
        - Heap Sort
    */
    void heapify_down(int index) {

        while (true) {

            int largest = index;

            int left = 2 * index + 1;
            int right = 2 * index + 2;

            // Check whether the left child exists and is larger.
            if (left < size && arr[left] > arr[largest]) {
                largest = left;
            }

            // Check whether the right child exists and is larger.
            if (right < size && arr[right] > arr[largest]) {
                largest = right;
            }

            // If the current node is largest, the heap property is satisfied.
            if (largest == index) {
                break;
            }

            // Move the largest child upward.
            swap(arr[index], arr[largest]);

            // Continue from the child's previous position.
            index = largest;
        }
    }

    /*
    ---------------------------------------------------------------------------
    GET MAXIMUM / PEEK
    ---------------------------------------------------------------------------

    THEORY:
    In a Max Heap, the root contains the maximum element.

    LOGIC:
    Return arr[0] without removing it.

    Time Complexity:  O(1)
    Space Complexity: O(1)
    */
    int peek() {

        if (size == 0) {
            cout << "Heap is empty" << endl;
            return -1;
        }

        return arr[0];
    }

    /*
    ---------------------------------------------------------------------------
    EXTRACT MAXIMUM
    ---------------------------------------------------------------------------

    THEORY:
    Extract Maximum returns the root and removes it from the heap.

    LOGIC:
    1. Save the root value.
    2. Replace the root with the last element.
    3. Decrease size.
    4. Call heapify_down() to restore the heap.
    5. Return the saved maximum.

    Time Complexity:  O(log n) worst case
    Auxiliary Space: O(1)

    NOTE:
    This method assumes -1 is used as an error value. If -1 is a valid
    heap element, use a different error-handling approach.
    */
    int extract_max() {

        if (size == 0) {
            cout << "Heap is empty" << endl;
            return -1;
        }

        int maximum = arr[0];

        arr[0] = arr[size - 1];
        size--;

        if (size > 0) {
            heapify_down(0);
        }

        return maximum;
    }

    /*
    ---------------------------------------------------------------------------
    DELETE NODE BY INDEX
    ---------------------------------------------------------------------------

    THEORY:
    Deletion removes an element from a specified array index.

    LOGIC:
    1. Check whether the heap is empty.
    2. Validate the index.
    3. Replace the target element with the last element.
    4. Decrease size.
    5. If the replacement is greater than its parent, heapify upward.
    6. Otherwise, heapify downward.

    WHY ARE BOTH DIRECTIONS POSSIBLE?
    The last element may be greater or smaller than the deleted element.
    The replacement may violate the heap property with its parent or children.

    Time Complexity:  O(log n) worst case
    Auxiliary Space: O(1)

    IMPORTANT:
    This function deletes by index, NOT by value.
    */
    void delete_node(int index) {

        if (size == 0) {
            cout << "Heap is empty" << endl;
            return;
        }

        if (index < 0 || index >= size) {
            cout << "Invalid index" << endl;
            return;
        }

        // Replace the target with the last element.
        arr[index] = arr[size - 1];

        // Remove the last position from the logical heap.
        size--;

        // If the deleted element was the last element, we are done.
        if (index >= size) {
            return;
        }

        // If the replacement violates the parent relationship, move upward.
        if (index > 0 && arr[index] > arr[(index - 1) / 2]) {

            heapify_up(index);
        }
        else {
            // Otherwise, repair a possible child relationship violation.
            heapify_down(index);
        }
    }

    /*
    ---------------------------------------------------------------------------
    BUILD HEAP
    ---------------------------------------------------------------------------

    THEORY:
    Build Heap converts an arbitrary array into a valid Max Heap.

    LOGIC:
    1. Find the last non-leaf node: (size / 2) - 1.
    2. Start at that node and move backward to index 0.
    3. Call heapify_down() for every internal node.

    WHY DO WE START FROM THE LAST NON-LEAF NODE?
    Leaf nodes have no children and automatically satisfy the heap property.
    Processing bottom-up ensures the children are heaps before their parents
    are processed.

    Time Complexity: O(n)

    IMPORTANT:
    Although heapify_down() can take O(log n), Build Heap takes O(n),
    because most nodes are near the bottom and require little work.

    Auxiliary Space: O(1)
    */
    void build_heap() {

        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify_down(i);
        }
    }

    /*
    ---------------------------------------------------------------------------
    PRINT HEAP
    ---------------------------------------------------------------------------

    THEORY:
    The array stores the heap in level order.

    Printing the array does NOT produce sorted order.
    It displays the internal heap representation.

    Time Complexity:  O(n)
    Auxiliary Space: O(1)
    */
    void print_BH() {

        if (size == 0) {
            cout << "Heap is empty" << endl;
            return;
        }

        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }

        cout << endl;
    }

    /*
    ---------------------------------------------------------------------------
    HEAP SORT
    ---------------------------------------------------------------------------

    THEORY:
    Heap Sort sorts an array using the Binary Heap data structure.

    A Max Heap produces ASCENDING ORDER.

    LOGIC:
    1. The root contains the maximum element.
    2. Swap the root with the last element of the active heap.
    3. Reduce the heap size by one.
    4. Heapify down from the root.
    5. Repeat until only one active element remains.

    WHY DOES IT SORT IN ASCENDING ORDER?
    Each maximum element is placed at the end of the active heap.
    The active heap becomes smaller after every iteration.

    Time Complexity:
        Best case:    O(n log n)
        Average case: O(n log n)
        Worst case:   O(n log n)

    Auxiliary Space: O(1)

    Properties:
        - In-place sorting algorithm
        - Not stable
        - Does not require an additional array

    IMPORTANT:
    After sorting, the array is sorted, but it is no longer necessarily
    a valid Max Heap. Restoring size does not rebuild the heap.
    */
    void heap_sort() {

        int originalSize = size;

        while (size > 1) {

            // Move the maximum element to the end.
            swap(arr[0], arr[size - 1]);

            // Exclude the sorted element from the active heap.
            size--;

            // Restore the heap property in the remaining elements.
            heapify_down(0);
        }

        // Restore the logical element count after sorting.
        size = originalSize;
    }
};


/*
===============================================================================
                                  MAIN
===============================================================================

This demonstrates:
1. Insertion
2. Printing a Max Heap
3. Getting the maximum element
4. Extracting the maximum
5. Building a heap from an array
6. Heap Sort

===============================================================================
*/

int main() {

    Binary_Heap b1;

    vector<int> values = {100, 50, 70, 20, 40, 60};

    // Insert each value individually.
    // Total worst-case time: O(n log n)
    for (int value : values) {
        b1.insert(value);
    }

    cout << "Max Heap: ";
    b1.print_BH();

    cout << "Maximum element: " << b1.peek() << endl;

    cout << "Extracted maximum: " << b1.extract_max() << endl;

    cout << "Heap after extracting maximum: ";
    b1.print_BH();

    // Demonstrate deletion by index.
    // Index 2 means the third element in the current heap array.
    b1.delete_node(2);

    cout << "Heap after deleting index 2: ";
    b1.print_BH();

    // Heap sort is performed on the current heap elements.
    b1.heap_sort();

    cout << "Sorted array: ";
    b1.print_BH();

    // Demonstrate bottom-up Build Heap on a fresh heap.
    Binary_Heap b2;

    for (int value : values) {
        b2.arr[b2.size] = value;
        b2.size++;
    }

    // Converts the existing array into a Max Heap in O(n).
    b2.build_heap();

    cout << "Heap built using Build Heap: ";
    b2.print_BH();

    return 0;
}

/*
===============================================================================
                         FINAL COMPLEXITY SUMMARY
===============================================================================

Operation                    Time Complexity    Auxiliary Space
----------------------------------------------------------------
Constructor                  O(1)                O(1)
Peek / Get Maximum           O(1)                O(1)
Insert                       O(log n) worst      O(1)
Heapify Up                   O(log n) worst      O(1)
Heapify Down                 O(log n) worst      O(1)
Extract Maximum              O(log n) worst      O(1)
Delete by Index              O(log n) worst      O(1)
Build Heap                   O(n)                O(1)
Print Heap                   O(n)                O(1)
Heap Sort                    O(n log n)          O(1)

For insertion of n elements one by one:
    Total worst-case time = O(n log n)

For bottom-up Build Heap:
    Total time = O(n)

For Heap Sort:
    Total time = O(n log n)

===============================================================================
*/
