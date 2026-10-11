/*
Topic: Sorting
Concept: Bubble sort.
Time Complexity: O(n^2)
Space Complexity: O(1)
Example Input:
5
5 1 4 2 3
Example Output:
1 2 3 4 5
Practice Problems:
1) Selection sort
2) Insertion sort
3) Merge sort
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << (i + 1 == n ? '\n' : ' ');
    }
    return 0;
}
