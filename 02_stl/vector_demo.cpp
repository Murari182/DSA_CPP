/*
Topic: STL
Concept: Using vector, push_back, and iteration.
Time Complexity: O(n)
Space Complexity: O(n)
Example Input:
5
1 2 3 4 5
Example Output:
15
Practice Problems:
1) Reverse a vector
2) Find maximum in vector
3) Remove duplicates from sorted vector
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> values;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        values.push_back(x);
    }

    int sum = 0;
    for (int x : values) {
        sum += x;
    }

    cout << sum << "\n";
    return 0;
}
