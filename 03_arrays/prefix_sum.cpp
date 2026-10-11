/*
Topic: Arrays
Concept: Prefix sum for range sum queries.
Time Complexity: O(n) preprocessing, O(1) query
Space Complexity: O(n)
Example Input:
5
2 4 1 6 3
1 3
Example Output:
11
Practice Problems:
1) Range sum query
2) Equilibrium index
3) Maximum subarray sum
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), pref(n + 1, 0);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }

    int l, r;
    cin >> l >> r;
    cout << pref[r + 1] - pref[l] << "\n";
    return 0;
}
