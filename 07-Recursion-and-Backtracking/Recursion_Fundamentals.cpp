#include <iostream>
#include <vector>
using namespace std;

// 1. Factorial: T(n) = T(n-1) + O(1) -> O(n) Time, O(n) Stack Space
long long factorial(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

// 2. Fibonacci: T(n) = T(n-1) + T(n-2) + O(1) -> O(2^n) Time, O(n) Stack Space
int fibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 3. Sum of Digits: O(log10(n)) Time
int sum_of_digits(int n)
{
    if (n == 0)
    {
        return 0;
    }
    return (n % 10) + sum_of_digits(n / 10);
}

// 4. Fast Exponentiation (a^b): T(b) = T(b/2) + O(1) -> O(log b) Time
long long fast_power(long long a, int b)
{
    if (b == 0)
    {
        return 1;
    }

    long long half = fast_power(a, b / 2);

    if (b % 2 == 0)
    {
        return half * half;
    }
    else
    {
        return a * half * half;
    }
}

// 5. Check if Array is Sorted: O(n) Time
bool is_sorted_recursive(const vector<int> &arr, int idx)
{
    if (idx >= (int)arr.size() - 1)
    {
        return true;
    }
    if (arr[idx] > arr[idx + 1])
    {
        return false;
    }
    return is_sorted_recursive(arr, idx + 1);
}

// 6. Tower of Hanoi: T(n) = 2T(n-1) + 1 -> O(2^n) Time
void tower_of_hanoi(int n, char src, char helper, char dest)
{
    if (n == 0)
    {
        return;
    }

    tower_of_hanoi(n - 1, src, dest, helper);
    cout << "Move disk " << n << " from " << src << " to " << dest << endl;
    tower_of_hanoi(n - 1, helper, src, dest);
}

int main()
{
    cout << "Factorial of 5: " << factorial(5) << endl;
    cout << "Fibonacci of 6: " << fibonacci(6) << endl;
    cout << "Sum of digits (1234): " << sum_of_digits(1234) << endl;
    cout << "Fast Power (2^10): " << fast_power(2, 10) << endl;

    vector<int> arr = {10, 20, 30, 40, 50};
    cout << "Is array sorted: " << is_sorted_recursive(arr, 0) << endl;

    cout << "Tower of Hanoi (3 disks):" << endl;
    tower_of_hanoi(3, 'A', 'B', 'C');

    return 0;
}
