
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {

    /*
        V = Number of vertices in the graph.

        adj = Adjacency List representation.

        vector<list<int>> means:
        - vector stores multiple lists.
        - Each list stores the neighbouring vertices.
        - Each index of the vector represents one vertex.

        Example:
        adj[0] stores all neighbours of vertex 0.
        adj[1] stores all neighbours of vertex 1.
    */

    int V;
    vector<list<int>> adj;

public:

    // --------------------------------------------------
    // 1. CONSTRUCTOR
    // --------------------------------------------------

    Graph(int vertices) {

        // Store the total number of vertices.
        V = vertices;

        /*
            resize(V) creates V empty lists inside the vector.

            If V = 5, the structure becomes:

            Index       Adjacency List
            --------------------------
              0         []
              1         []
              2         []
              3         []
              4         []

            Each index represents a vertex.

            Dynamic allocation:
            We do not need to declare a fixed-size array.
            The vector manages its memory dynamically.

            Time Complexity: O(V)
            Space Complexity: O(V) for the V list objects.
        */

        adj.resize(V);
    }


    // --------------------------------------------------
    // 2. ADD EDGE
    // --------------------------------------------------

    void addEdge(int u, int v) {

        /*
            Add an edge between vertices u and v.

            For an UNDIRECTED GRAPH:

            If there is an edge between 0 and 1,
            then both vertices are neighbours of each other.

            Therefore, we store:

            adj[0].push_back(1);
            adj[1].push_back(0);

            First statement:
            Adds v to the adjacency list of u.

            Second statement:
            Adds u to the adjacency list of v.
        */

        adj[u].push_back(v);
        adj[v].push_back(u);

        /*
            Why push_back()?

            list<int> is a doubly linked list.

            push_back() inserts an element at the end.

            Insertion at the end of a std::list is O(1).

            Time Complexity: O(1) per edge insertion.
            Space Complexity: O(1) auxiliary space per call.

            Note:
            For a directed graph, only use:

            adj[u].push_back(v);

            Do not insert the reverse edge.
        */
    }


    // --------------------------------------------------
    // 3. DISPLAY ADJACENCY LIST
    // --------------------------------------------------

    void display() {

        /*
            Traverse every vertex using the vector.

            i represents the current vertex.

            adj[i] contains all neighbours of vertex i.
        */

        for (int i = 0; i < V; i++) {

            cout << i << " -> ";

            /*
                Range-based for loop:

                int it : adj[i]

                It visits every element in the list
                corresponding to vertex i.

                Example:

                If adj[0] = {1, 2}

                First iteration: it = 1
                Second iteration: it = 2
            */

            for (int it : adj[i]) {

                cout << it << " ";
            }

            cout << endl;
        }

        /*
            Time Complexity: O(V + E)

            Explanation:

            Outer loop:
            Visits all V vertices -> O(V).

            Inner loops:
            Collectively visit all adjacency-list entries.

            In an undirected graph, every edge is stored twice.
            Therefore, the total number of entries is 2E.

            Total = O(V + 2E)
                 = O(V + E).

            Auxiliary Space Complexity: O(1)
            No additional data structure is created.
        */
    }


    // --------------------------------------------------
    // 4. GET NUMBER OF VERTICES
    // --------------------------------------------------

    int getVertices() {

        // Returns the total number of vertices.
        return V;

        // Time Complexity: O(1)
        // Auxiliary Space Complexity: O(1)
    }
};


// ======================================================
// MAIN FUNCTION
// ======================================================

int main() {

    /*
        Create a graph with 5 vertices.

        Vertices:
        0, 1, 2, 3, 4

        Initially, every adjacency list is empty.
    */

    Graph g(5);


    // --------------------------------------------------
    // INSERT EDGES
    // --------------------------------------------------

    g.addEdge(0, 1);
    g.addEdge(0, 2);

    g.addEdge(1, 3);
    g.addEdge(1, 4);

    g.addEdge(2, 4);


    /*
        The graph looks like:

                 0
                / \
               1   2
              / \   \
             3   4---+

        Edges:
        (0,1), (0,2), (1,3), (1,4), (2,4)
    */


    // --------------------------------------------------
    // DISPLAY GRAPH
    // --------------------------------------------------

    cout << "Adjacency List Representation:\n\n";

    g.display();


    return 0;
}


// ======================================================
// OVERALL COMPLEXITY ANALYSIS
// ======================================================

/*

    Let:
        V = Number of vertices
        E = Number of edges

    1. CONSTRUCTOR
       Time Complexity:  O(V)
       Space Complexity: O(V)

    2. ADD EDGE
       Time Complexity:  O(1) per edge
       Space Complexity: O(1) auxiliary

    3. DISPLAY
       Time Complexity:  O(V + E)
       Space Complexity: O(1) auxiliary

    4. COMPLETE GRAPH STORAGE

       Vector contains V adjacency lists.

       Each undirected edge is stored twice.

       Therefore:

       Space Complexity = O(V + 2E)
                        = O(V + E)

    5. COMPLETE GRAPH CONSTRUCTION

       Constructor: O(V)
       Adding E edges: O(E)

       Total: O(V + E)

    IMPORTANT:
    The graph's storage complexity is different from
    the auxiliary space complexity of display().

*/
