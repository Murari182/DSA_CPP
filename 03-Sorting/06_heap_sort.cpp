/**
 * @file 06_heap_sort.cpp
 * @brief In-Place Heap Sort Algorithm in Modern C++17
 * 
 * Features:
 * 1. Bottom-up max-heap construction in O(n) time.
 * 2. In-place extraction loop with heapify-down in O(log n).
 * 3. Total guaranteed time: O(n log n).
 * 4. Auxiliary space: O(1).
 */

#include <iostream>
#include <vector>
#include <utility>

// Heapify a subtree rooted at index i in an array of size n
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main Heap Sort routine
void heapSort(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());

    // Phase 1: Build Max-Heap (start from lowest non-leaf node down to 0)
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }

    // Phase 2: Extract elements one by one from max-heap
    for (int i = n - 1; i > 0; --i) {
        // Move current root (maximum element) to the end
        std::swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap of size i
        heapify(arr, i, 0);
    }
}

int main() {
    std::vector<int> arr = {5, 1, 4, 2, 8};
    std::cout << "Original array: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";

    heapSort(arr);

    std::cout << "Sorted with Heap Sort: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
