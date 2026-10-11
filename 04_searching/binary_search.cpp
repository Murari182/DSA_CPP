/*
Topic: Searching
Concept: Binary search on sorted array.
Time Complexity: O(log n)
Space Complexity: O(1)
Example Input:
6
1 3 5 7 9 11
7
Example Output:
3
Practice Problems:
1) First occurrence
2) Last occurrence
3) Lower/upper bound
*/

#include <iostream>
#include <vector>
using namespace std;

int binarySearch(const vector<int>& a, int target) {
    int low = 0, high = (int)a.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int target;
    cin >> target;
    cout << binarySearch(a, target) << "\n";
    return 0;
}
