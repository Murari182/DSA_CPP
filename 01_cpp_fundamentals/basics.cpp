/*
Topic: C++ Fundamentals
Concept: Variables, loops, conditionals, and functions.
Time Complexity: O(n)
Space Complexity: O(1)
Example Input:
5
Example Output:
15
Practice Problems:
1) Sum of first N natural numbers
2) Count digits in a number
3) Check even/odd
*/

#include <iostream>
using namespace std;

int sumFirstN(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int main() {
    int n;
    cin >> n;
    cout << sumFirstN(n) << "\n";
    return 0;
}
