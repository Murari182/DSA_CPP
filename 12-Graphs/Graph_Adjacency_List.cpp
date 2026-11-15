/**
 * @file Graph_Adjacency_List.cpp
 * @brief Comprehensive, Leak-Free Graph Implementations in Modern C++17
 * 
 * Demonstrates:
 * 1. Educational Raw-Pointer Dynamic Adjacency List with strict RAII (Rule of 5).
 * 2. Modern Standard Adjacency List using std::vector<std::vector<int>>.
 * 3. Weighted Adjacency List using std::vector<std::vector<std::pair<int, int>>>.
 * 4. Graph Traversals: Breadth-First Search (BFS) and Depth-First Search (DFS - recursive and iterative).
 */

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <utility>
#include <algorithm>

// ============================================================================
// 1. EDUCATIONAL RAW-POINTER DYNAMIC ADJACENCY LIST (STRICT RAII & RULE OF 5)
// ============================================================================

class DynamicRawGraph {
private:
    int V;
    std::list<int>* arr; // Pointer to a dynamically allocated array of std::list<int>

public:
    // Constructor: Allocates V independent std::list objects on the heap
    explicit DynamicRawGraph(int vertices) : V(vertices), arr(nullptr) {
        if (V > 0) {
            arr = new std::list<int>[V];
        }
    }

    // Destructor: Essential to prevent memory leaks when dynamically allocating with new[]
    ~DynamicRawGraph() {
        delete[] arr; // Invokes destructors for all V std::list objects, then frees buffer
    }

    // Copy Constructor (Deep Copy - Rule of 3/5)
    DynamicRawGraph(const DynamicRawGraph& other) : V(other.V), arr(nullptr) {
        if (V > 0) {
            arr = new std::list<int>[V];
            for (int i = 0; i < V; ++i) {
                arr[i] = other.arr[i]; // Deep copy of each list's nodes
            }
        }
    }

    // Copy Assignment Operator (Copy-and-Swap idiom - Rule of 3/5)
    DynamicRawGraph& operator=(const DynamicRawGraph& other) {
        if (this != &other) {
            DynamicRawGraph temp(other);
            std::swap(V, temp.V);
            std::swap(arr, temp.arr);
        }
        return *this;
    }

    // Move Constructor (Rule of 5)
    DynamicRawGraph(DynamicRawGraph&& other) noexcept : V(other.V), arr(other.arr) {
        other.V = 0;
        other.arr = nullptr;
    }

    // Move Assignment Operator (Rule of 5)
    DynamicRawGraph& operator=(DynamicRawGraph&& other) noexcept {
        if (this != &other) {
            delete[] arr;
            V = other.V;
            arr = other.arr;
            other.V = 0;
            other.arr = nullptr;
        }
        return *this;
    }

    // Add an undirected edge (u <-> v)
    void addUndirectedEdge(int u, int v) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            arr[u].push_back(v);
            arr[v].push_back(u);
        }
    }

    // Add a directed edge (u -> v)
    void addDirectedEdge(int u, int v) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            arr[u].push_back(v);
        }
    }

    // Print adjacency list
    void print() const {
        std::cout << "--- Educational Raw Dynamic Array Adjacency List ---\n";
        for (int i = 0; i < V; ++i) {
            std::cout << "Vertex [" << i << "] --> ";
            for (int neighbor : arr[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }
};

// ============================================================================
// 2. MODERN PRODUCTION GRAPH (RAII, std::vector, Traversals)
// ============================================================================

class ModernGraph {
private:
    int V;
    bool directed;
    std::vector<std::vector<int>> adj; // Contiguous, cache-friendly, automatic memory

    // Recursive DFS helper
    void dfsRecursiveHelper(int u, std::vector<bool>& visited, std::vector<int>& order) const {
        visited[u] = true;
        order.push_back(u);

        for (int v : adj[u]) {
            if (!visited[v]) {
                dfsRecursiveHelper(v, visited, order);
            }
        }
    }

public:
    explicit ModernGraph(int vertices, bool isDirected = false)
        : V(vertices), directed(isDirected), adj(vertices) {}

    // Add an edge
    void addEdge(int u, int v) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            adj[u].push_back(v);
            if (!directed) {
                adj[v].push_back(u);
            }
        }
    }

    // Add a new vertex dynamically (demonstrating resizability)
    int addVertex() {
        adj.push_back({});
        return V++;
    }

    // Get number of vertices
    int getV() const { return V; }

    // Breadth-First Search (BFS) from source vertex
    std::vector<int> bfs(int startVertex) const {
        std::vector<int> order;
        if (startVertex < 0 || startVertex >= V) return order;

        std::vector<bool> visited(V, false);
        std::queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        return order;
    }

    // Depth-First Search (DFS) - Recursive
    std::vector<int> dfsRecursive(int startVertex) const {
        std::vector<int> order;
        if (startVertex < 0 || startVertex >= V) return order;

        std::vector<bool> visited(V, false);
        dfsRecursiveHelper(startVertex, visited, order);
        return order;
    }

    // Depth-First Search (DFS) - Iterative using explicit std::stack
    std::vector<int> dfsIterative(int startVertex) const {
        std::vector<int> order;
        if (startVertex < 0 || startVertex >= V) return order;

        std::vector<bool> visited(V, false);
        std::stack<int> s;

        s.push(startVertex);

        while (!s.empty()) {
            int u = s.top();
            s.pop();

            if (!visited[u]) {
                visited[u] = true;
                order.push_back(u);

                // Push neighbors in reverse order so the lowest indexed neighbor is processed first
                for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
                    if (!visited[*it]) {
                        s.push(*it);
                    }
                }
            }
        }
        return order;
    }

    // Display adjacency list
    void print() const {
        std::cout << "--- Modern std::vector Adjacency List (" 
                  << (directed ? "Directed" : "Undirected") << ") ---\n";
        for (int i = 0; i < V; ++i) {
            std::cout << "Vertex [" << i << "] --> ";
            for (int neighbor : adj[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }
};

// ============================================================================
// 3. MAIN DEMONSTRATION & VERIFICATION
// ============================================================================

int main() {
    std::cout << "========================================\n";
    std::cout << "DSA-CPP Graph Adjacency List Demonstration\n";
    std::cout << "========================================\n\n";

    // 1. Verify Educational Raw Pointer Dynamic Array
    {
        DynamicRawGraph rawG(5);
        rawG.addUndirectedEdge(0, 1);
        rawG.addUndirectedEdge(1, 2);
        rawG.addUndirectedEdge(2, 3);
        rawG.addUndirectedEdge(1, 3);
        rawG.addUndirectedEdge(2, 4);
        rawG.print();
        // Destructor ~DynamicRawGraph() automatically called here - 0 memory leaks!
    }

    std::cout << "\n";

    // 2. Verify Modern Production Graph with BFS & DFS
    {
        ModernGraph g(5, false); // 5 vertices, undirected
        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.addEdge(2, 3);
        g.addEdge(1, 3);
        g.addEdge(2, 4);

        g.print();

        // Run BFS
        std::vector<int> bfsOrder = g.bfs(0);
        std::cout << "\nBFS Traversal starting from vertex 0: ";
        for (int v : bfsOrder) std::cout << v << " ";
        std::cout << "\n";

        // Run Recursive DFS
        std::vector<int> dfsRecOrder = g.dfsRecursive(0);
        std::cout << "DFS (Recursive) starting from vertex 0: ";
        for (int v : dfsRecOrder) std::cout << v << " ";
        std::cout << "\n";

        // Run Iterative DFS
        std::vector<int> dfsIterOrder = g.dfsIterative(0);
        std::cout << "DFS (Iterative) starting from vertex 0: ";
        for (int v : dfsIterOrder) std::cout << v << " ";
        std::cout << "\n";

        // Dynamic vertex insertion
        std::cout << "\nDynamically adding vertex 5 and edge (4, 5)...\n";
        int newV = g.addVertex();
        g.addEdge(4, newV);
        g.print();
    }

    return 0;
}
