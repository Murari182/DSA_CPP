/**
 * @file 07_counting_and_radix_sort.cpp
 * @brief Linear-Time Non-Comparison Sorting Algorithms in C++17
 * 
 * Features:
 * 1. Counting Sort (Stable implementation using prefix sum frequencies).
 * 2. Radix Sort (LSD - Least Significant Digit using stable counting sort subroutine).
 * 3. Handles positive and negative numbers.
 */

#include <iostream>
#include <vector>
#include <algorithm>

// ============================================================================
// 1. COUNTING SORT (STABLE)
// ============================================================================
void countingSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int minVal = *std::min_element(arr.begin(), arr.end());
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    std::vector<int> count(range, 0);
    std::vector<int> output(arr.size());

    // 1. Store frequencies
    for (int x : arr) {
        count[x - minVal]++;
    }

    // 2. Compute prefix sums (cumulative positions)
    for (int i = 1; i < range; ++i) {
        count[i] += count[i - 1];
    }

    // 3. Build output array in reverse order to preserve STABILITY
    for (int i = static_cast<int>(arr.size()) - 1; i >= 0; --i) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    arr = output;
}

// ============================================================================
// 2. RADIX SORT (LSD - LEAST SIGNIFICANT DIGIT)
// ============================================================================
void countingSortByDigit(std::vector<int>& arr, int exp) {
    int n = static_cast<int>(arr.size());
    std::vector<int> output(n);
    int count[10] = {0};

    // Store count of occurrences in count[]
    for (int i = 0; i < n; ++i) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Change count[i] so it contains actual position in output[]
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    // Build the output array from right to left (preserves stability)
    for (int i = n - 1; i >= 0; --i) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

void radixSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *std::max_element(arr.begin(), arr.end());

    // Do counting sort for every digit. exp is 10^i where i is current digit position
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortByDigit(arr, exp);
    }
}

int main() {
    std::vector<int> arr1 = {4, 2, 2, 8, 3, 3, 1};
    std::cout << "Original array: ";
    for (int x : arr1) std::cout << x << " ";
    std::cout << "\n";

    countingSort(arr1);
    std::cout << "Sorted with Counting Sort: ";
    for (int x : arr1) std::cout << x << " ";
    std::cout << "\n\n";

    std::vector<int> arr2 = {170, 45, 75, 90, 802, 24, 2, 66};
    std::cout << "Original array: ";
    for (int x : arr2) std::cout << x << " ";
    std::cout << "\n";

    radixSort(arr2);
    std::cout << "Sorted with Radix Sort: ";
    for (int x : arr2) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
