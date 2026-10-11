/*
Topic: Hashing
Concept: Frequency counting with unordered_map.
Time Complexity: O(n) average
Space Complexity: O(n)
Example Input:
6
1 2 2 3 1 2
Example Output:
1:2 2:3 3:1
Practice Problems:
1) Two sum
2) First unique character
3) Count distinct elements
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    unordered_map<int, int> freq;
    vector<int> keys;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (freq.find(x) == freq.end()) {
            keys.push_back(x);
        }
        freq[x]++;
    }

    sort(keys.begin(), keys.end());

    for (int i = 0; i < (int)keys.size(); i++) {
        int key = keys[i];
        cout << key << ':' << freq[key] << (i + 1 == (int)keys.size() ? '\n' : ' ');
    }

    return 0;
}
