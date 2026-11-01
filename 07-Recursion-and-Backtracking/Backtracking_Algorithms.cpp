#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 1. Generate all subsets (Power Set): O(n * 2^n) Time, O(n) Auxiliary Stack Space
void generate_subsets(const vector<int> &nums, int idx, vector<int> &current)
{
    if (idx == nums.size())
    {
        cout << "{ ";
        for (int x : current)
        {
            cout << x << " ";
        }
        cout << "} ";
        return;
    }

    // Include nums[idx]
    current.push_back(nums[idx]);
    generate_subsets(nums, idx + 1, current);

    // Backtrack (exclude nums[idx])
    current.pop_back();
    generate_subsets(nums, idx + 1, current);
}

// 2. Generate all permutations of a string: O(n * n!) Time
void generate_permutations(string &str, int idx)
{
    if (idx == str.size())
    {
        cout << str << " ";
        return;
    }

    for (int i = idx; i < str.size(); i++)
    {
        swap(str[idx], str[i]);
        generate_permutations(str, idx + 1);
        swap(str[idx], str[i]); // Backtrack
    }
}

// 3. N-Queens Problem
bool is_safe_queen(const vector<string> &board, int row, int col, int n)
{
    // Check column above
    for (int i = 0; i < row; i++)
    {
        if (board[i][col] == 'Q')
        {
            return false;
        }
    }

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 'Q')
        {
            return false;
        }
    }

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
    {
        if (board[i][j] == 'Q')
        {
            return false;
        }
    }

    return true;
}

int count_n_queens(vector<string> &board, int row, int n)
{
    if (row == n)
    {
        return 1;
    }

    int ways = 0;
    for (int col = 0; col < n; col++)
    {
        if (is_safe_queen(board, row, col, n))
        {
            board[row][col] = 'Q';
            ways += count_n_queens(board, row + 1, n);
            board[row][col] = '.'; // Backtrack
        }
    }

    return ways;
}

int main()
{
    vector<int> nums = {1, 2, 3};
    vector<int> current;
    cout << "Subsets of {1, 2, 3}: ";
    generate_subsets(nums, 0, current);
    cout << endl;

    string s = "ABC";
    cout << "Permutations of ABC: ";
    generate_permutations(s, 0);
    cout << endl;

    int n = 4;
    vector<string> board(n, string(n, '.'));
    cout << "Total solutions for " << n << "-Queens: " << count_n_queens(board, 0, n) << endl;

    return 0;
}
