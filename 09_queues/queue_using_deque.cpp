/*
Topic: Queues
Concept: Queue using deque (FIFO).
Time Complexity: O(1) amortized enqueue/dequeue
Space Complexity: O(n)
Example Input:
5
10 20 30 40 50
Example Output:
10 20 30 40 50
Practice Problems:
1) Circular queue
2) Queue using stacks
3) First non-repeating character in stream
*/

#include <deque>
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    deque<int> q;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        q.push_back(x);
    }

    while (!q.empty()) {
        cout << q.front();
        q.pop_front();
        cout << (q.empty() ? '\n' : ' ');
    }

    return 0;
}
