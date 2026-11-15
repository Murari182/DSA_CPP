#include <iostream>
#include <algorithm>
using namespace std;

void bubble_sort(int arr[]) {

    int n = 5;

    for(int i = 0; i < n-1; i++) {

        for(int j = 0; j < n-i-1; j++) {

            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void optimized_bubble_sort(int arr[]) {

    int n = 5;

    for(int i = 0; i < n-1; i++) {

        bool swapped = false;

        for(int j = 0; j < n-i-1; j++) {

            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }

        if(swapped == false) {
            break;
        }
    }
}

void selection_sort(int arr[]) {

    int n = 5;

    for(int i = 0; i < n-1; i++) {

        int min_index = i;

        for(int j = i+1; j < n; j++) {

            if(arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        swap(arr[i], arr[min_index]);
    }
}

int main() {

    int arr1[] = {4, 1, 5, 2, 3};
    int arr2[] = {4, 1, 5, 2, 3};
    int arr3[] = {4, 1, 5, 2, 3};

    bubble_sort(arr1);
    optimized_bubble_sort(arr2);
    selection_sort(arr3);

    cout << "Bubble Sort: ";
    for(int i = 0; i < 5; i++) {
        cout << arr1[i] << " ";
    }

    cout << "\nOptimized Bubble Sort: ";
    for(int i = 0; i < 5; i++) {
        cout << arr2[i] << " ";
    }

    cout << "\nSelection Sort: ";
    for(int i = 0; i < 5; i++) {
        cout << arr3[i] << " ";
    }

    return 0;
}