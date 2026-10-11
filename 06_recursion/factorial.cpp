/*
Topic: Recursion
Concept: Recursive factorial.
Time Complexity: O(n)
Space Complexity: O(n) recursion stack
Example Input:
5
Example Output:
120
Practice Problems:
1) Power using recursion
2) Fibonacci recursion
3) Sum of digits recursion
*/

#include <iostream>
using namespace std;

long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    int n;
    cin >> n;
    cout << factorial(n) << "\n";
    return 0;
}
