/*
Topic: Stacks
Concept: Stack using vector (LIFO).
Time Complexity: O(1) for push/pop/top
Space Complexity: O(n)
Example Input:
5
1 2 3 4 5
Example Output:
5 4 3 2 1
Practice Problems:
1) Balanced parentheses
2) Next greater element
3) Implement min stack
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> st;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        st.push_back(x);
    }

    while (!st.empty()) {
        cout << st.back();
        st.pop_back();
        cout << (st.empty() ? '\n' : ' ');
    }

    return 0;
}
