/*
Topic: Graphs
Concept: BFS traversal from source node 0.
Time Complexity: O(V + E)
Space Complexity: O(V)
Example Input:
5 4
0 1
0 2
1 3
2 4
Example Output:
0 1 2 3 4
Practice Problems:
1) DFS traversal
2) Cycle detection
3) Shortest path in unweighted graph
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> visited(n, false);
    queue<int> q;

    visited[0] = true;
    q.push(0);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << ' ';

        for (int next : graph[node]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }

    cout << "\n";
    return 0;
}
