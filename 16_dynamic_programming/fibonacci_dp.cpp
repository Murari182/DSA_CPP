/*
Topic: Dynamic Programming
Concept: Fibonacci using tabulation.
Time Complexity: O(n)
Space Complexity: O(n)
Example Input:
7
Example Output:
13
Practice Problems:
1) Climbing stairs
2) 0/1 knapsack
3) Longest common subsequence
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    if (n == 0) {
        cout << 0 << "\n";
        return 0;
    }

    vector<long long> dp(n + 1, 0);
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    cout << dp[n] << "\n";
    return 0;
}
