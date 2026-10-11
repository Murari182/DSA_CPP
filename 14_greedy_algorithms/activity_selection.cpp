/*
Topic: Greedy Algorithms
Concept: Activity selection (maximum non-overlapping activities).
Time Complexity: O(n log n)
Space Complexity: O(n)
Example Input:
6
1 3
2 4
3 5
0 6
5 7
8 9
Example Output:
4
Practice Problems:
1) Fractional knapsack
2) Job sequencing with deadlines
3) Minimum platforms
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Activity {
    int start;
    int finish;
};

int main() {
    int n;
    cin >> n;
    vector<Activity> activities(n);

    for (int i = 0; i < n; i++) {
        cin >> activities[i].start >> activities[i].finish;
    }

    sort(activities.begin(), activities.end(), [](const Activity& a, const Activity& b) {
        return a.finish < b.finish;
    });

    int count = 0;
    int lastFinish = -1;

    for (const Activity& activity : activities) {
        if (activity.start >= lastFinish) {
            count++;
            lastFinish = activity.finish;
        }
    }

    cout << count << "\n";
    return 0;
}
