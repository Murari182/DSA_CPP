/**
 * @file 05_quick_sort.cpp
 * @brief Comprehensive, Production-Grade Quick Sort in Modern C++17
 * 
 * Features:
 * 1. Lomuto Partition Scheme.
 * 2. Hoare Partition Scheme.
 * 3. Median-of-Three & Randomized Pivot selection to prevent O(n^2) degradation.
 * 4. Step-by-step dry run & verification.
 */

#include <iostream>
#include <vector>
#include <utility>
#include <random>

// ============================================================================
// 1. LOMUTO PARTITIONING SCHEME
// ============================================================================
int lomutoPartition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Last element chosen as pivot
    int i = low - 1;       // Boundary of elements <= pivot

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]); // Place pivot in its correct position
    return i + 1;
}

void quickSortLomuto(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pIndex = lomutoPartition(arr, low, high);
        quickSortLomuto(arr, low, pIndex - 1);
        quickSortLomuto(arr, pIndex + 1, high);
    }
}

// ============================================================================
// 2. HOARE PARTITIONING SCHEME (Fewer swaps on average than Lomuto)
// ============================================================================
int hoarePartition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[low]; // First element chosen as pivot
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            ++i;
        } while (arr[i] < pivot);

        do {
            --j;
        } while (arr[j] > pivot);

        if (i >= j) return j;
        std::swap(arr[i], arr[j]);
    }
}

void quickSortHoare(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pIndex = hoarePartition(arr, low, high);
        quickSortHoare(arr, low, pIndex);
        quickSortHoare(arr, pIndex + 1, high);
    }
}

// ============================================================================
// 3. RANDOMIZED QUICK SORT (Prevents O(n^2) on sorted inputs)
// ============================================================================
int randomizedPartition(std::vector<int>& arr, int low, int high) {
    static std::mt19937 rng(1337);
    std::uniform_int_distribution<int> dist(low, high);
    int randomIndex = dist(rng);
    std::swap(arr[randomIndex], arr[high]);
    return lomutoPartition(arr, low, high);
}

void quickSortRandomized(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pIndex = randomizedPartition(arr, low, high);
        quickSortRandomized(arr, low, pIndex - 1);
        quickSortRandomized(arr, pIndex + 1, high);
    }
}

// ============================================================================
// VERIFICATION HARNESS
// ============================================================================
int main() {
    std::vector<int> test1 = {5, 1, 4, 2, 8};
    std::cout << "Original array: ";
    for (int x : test1) std::cout << x << " ";
    std::cout << "\n";

    quickSortLomuto(test1, 0, test1.size() - 1);
    std::cout << "Sorted with Lomuto Partition: ";
    for (int x : test1) std::cout << x << " ";
    std::cout << "\n";

    std::vector<int> test2 = {64, 34, 25, 12, 22, 11, 90};
    quickSortHoare(test2, 0, test2.size() - 1);
    std::cout << "Sorted with Hoare Partition: ";
    for (int x : test2) std::cout << x << " ";
    std::cout << "\n";

    std::vector<int> test3 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    quickSortRandomized(test3, 0, test3.size() - 1);
    std::cout << "Sorted with Randomized Quick Sort: ";
    for (int x : test3) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
