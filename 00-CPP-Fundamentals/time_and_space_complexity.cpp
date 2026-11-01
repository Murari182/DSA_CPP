#include <iostream>
#include <vector>
using namespace std;

// O(1) - Constant Time
int get_first_element(const vector<int> &arr)
{
    if (arr.empty())
    {
        return -1;
    }
    return arr[0];
}

// O(log n) - Logarithmic Time
int count_halving_steps(int n)
{
    int steps = 0;
    while (n > 1)
    {
        n = n / 2;
        steps++;
    }
    return steps;
}

// O(n) - Linear Time
int sum_elements(const vector<int> &arr)
{
    int sum = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    return sum;
}

// O(n log n) - Linearithmic Time
int linearithmic_operations(int n)
{
    int ops = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = n; j > 1; j = j / 2)
        {
            ops++;
        }
    }
    return ops;
}

// O(n^2) - Quadratic Time
int count_pairs(int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            count++;
        }
    }
    return count;
}

int main()
{
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80};
    int n = arr.size();

    cout << "O(1) First element: " << get_first_element(arr) << endl;
    cout << "O(log n) Steps for n=" << n << ": " << count_halving_steps(n) << endl;
    cout << "O(n) Sum of elements: " << sum_elements(arr) << endl;
    cout << "O(n log n) Operations for n=" << n << ": " << linearithmic_operations(n) << endl;
    cout << "O(n^2) Pair count for n=" << n << ": " << count_pairs(n) << endl;

    return 0;
}
