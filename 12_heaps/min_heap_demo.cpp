/*
Topic: Heaps
Concept: Min heap using priority_queue.
Time Complexity: O(log n) insertion/extraction
Space Complexity: O(n)
Example Input:
5
7 2 9 1 6
Example Output:
1 2 6 7 9
Practice Problems:
1) Kth largest element
2) Merge k sorted arrays
3) Top k frequent elements
*/

#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        minHeap.push(x);
    }

    while (!minHeap.empty()) {
        cout << minHeap.top();
        minHeap.pop();
        cout << (minHeap.empty() ? '\n' : ' ');
    }

    return 0;
}
