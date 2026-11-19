
/*
===============================================================================
                    GRAPH DATA STRUCTURE IN C++
                  ADJACENCY LIST + BFS + DFS
===============================================================================

TOPICS COVERED:
1. Graph Fundamentals
2. Undirected Graph
3. Adjacency List Representation
4. vector<list<int>>
5. Dynamic Memory and resize()
6. Edge Insertion
7. Graph Display
8. BFS (Breadth First Search)
9. DFS (Depth First Search - Recursive)
10. DFS (Iterative using Stack)
11. Disconnected Graph Traversal
12. Time and Space Complexity
13. Important C++ Concepts

===============================================================================
                        1. GRAPH FUNDAMENTALS
===============================================================================

A GRAPH is a non-linear data structure consisting of:

    1. Vertices (V): Nodes of the graph.
    2. Edges (E): Connections between vertices.

Example:

             0
            / \
           1   2
          / \
         3   4

Vertices = {0, 1, 2, 3, 4}

Edges = {(0,1), (0,2), (1,3), (1,4)}

Types of Graphs:

1. Undirected Graph:
   Edges have no direction.
   If 0 is connected to 1, then 1 is also connected to 0.

   0 -------- 1

2. Directed Graph:
   Edges have directions.

   0 -------> 1

3. Weighted Graph:
   Edges have associated weights or costs.

4. Unweighted Graph:
   Edges do not have weights.

===============================================================================
                    2. HEADER FILES
===============================================================================
*/

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;

/*
iostream:
    Provides input/output operations.
    Used for cout, cin and endl.

vector:
    Provides the dynamic array container.
    Used for storing adjacency lists and visited arrays.

list:
    Provides the doubly linked list container.
    Used for storing neighbours of each vertex.

queue:
    Provides the FIFO (First In First Out) data structure.
    Used in BFS.

stack:
    Provides the LIFO (Last In First Out) data structure.
    Used in iterative DFS.

===============================================================================
                    3. GRAPH CLASS
===============================================================================

WHY USE A CLASS?

A graph contains related data and operations:

    - Number of vertices.
    - Adjacency list.
    - Add edges.
    - Display graph.
    - BFS.
    - DFS.

A class groups these properties and functions together.

This is called ENCAPSULATION.

*/

class Graph
{
private:

    /*
    ---------------------------------------------------------------------------
    VARIABLE 1: NUMBER OF VERTICES
    ---------------------------------------------------------------------------

    int V;

    V stores the total number of vertices in the graph.

    Example:
        Graph g(5);

        V = 5

    Vertices are numbered:
        0, 1, 2, 3, 4

    We use integer indices to identify vertices.
    */


    int V;


    /*
    ---------------------------------------------------------------------------
    VARIABLE 2: ADJACENCY LIST
    ---------------------------------------------------------------------------

    vector<list<int>> adj;

    Let's understand this declaration.

    vector:
        Dynamic array.

    list<int>:
        Doubly linked list storing integer values.

    vector<list<int>>:
        A vector in which every element is a linked list.

    WHY DO WE USE VECTOR?

        Suppose we have 5 vertices.

        We need 5 separate adjacency lists.

        We can access them using:

            adj[0]
            adj[1]
            adj[2]
            adj[3]
            adj[4]

        Each index represents a vertex.

    WHY DO WE USE LIST?

        A vertex can have multiple neighbours.

        Example:

                1
               /
              0
             / \
            2   3

        Vertex 0 has three neighbours:
            1, 2, 3

        list<int> allows us to store a variable number
        of neighbours.

    HOW DOES IT WORK?

        adj[0] = {1}
        adj[1] = {2, 3, 0}
        adj[2] = {1, 4}
        adj[3] = {1}
        adj[4] = {2}

    MEMORY REPRESENTATION (CONCEPTUAL):

        Vector
          |
          |---- Index 0 --> List: 1
          |
          |---- Index 1 --> List: 2 -> 3 -> 0
          |
          |---- Index 2 --> List: 1 -> 4
          |
          |---- Index 3 --> List: 1
          |
          |---- Index 4 --> List: 2

    IMPORTANT:

        The vector stores list objects.

        Each list manages its own linked nodes.

    WHY NOT USE AN ADJACENCY MATRIX?

        Adjacency Matrix:
            Space Complexity = O(V * V)

        Adjacency List:
            Space Complexity = O(V + E)

        Adjacency lists are generally more memory-efficient
        for sparse graphs.

    */

    vector<list<int>> adj;


    /*
    ===========================================================================
                    4. RECURSIVE DFS HELPER FUNCTION
    ===========================================================================

    This function is private because users should normally
    call the public DFS() function.

    It performs the actual recursive traversal.

    PARAMETERS:

        int u:
            Current vertex being processed.

        vector<bool>& visited:
            Visited array passed by reference.

    WHY USE vector<bool>?

        We only need to store two states:

            false = Vertex not visited.
            true  = Vertex already visited.

        A Boolean container is suitable because we do not
        need to store any other information.

    WHY USE & (REFERENCE)?

        We need every recursive call to share the same
        visited array.

        Passing by value would create a copy.

        Passing by reference allows all recursive calls
        to update the same original array.

    */

    void DFS_helper(int u, vector<bool>& visited)
    {
        /*
        STEP 1: MARK CURRENT VERTEX AS VISITED.

        Why?

        To prevent visiting the same vertex repeatedly.

        It also prevents infinite recursion in cyclic graphs.
        */

        visited[u] = true;


        /*
        STEP 2: PROCESS THE CURRENT VERTEX.

        Here, we print the vertex.

        In other problems, we may store it, calculate something,
        or perform another operation.
        */

        cout << u << " ";


        /*
        STEP 3: EXPLORE ALL NEIGHBOURS.

        adj[u] contains all neighbours of vertex u.

        Range-based for loop:

            for (int v : adj[u])

        It visits every neighbour one by one.
        */

        for (int v : adj[u])
        {
            /*
            STEP 4: CHECK WHETHER THE NEIGHBOUR IS VISITED.

            !visited[v] means:

                The neighbour is NOT visited.

            Only unvisited neighbours should be explored.
            */

            if (!visited[v])
            {
                /*
                STEP 5: RECURSIVE CALL.

                We move deeper into the graph.

                The function calls itself with the new vertex.

                When the current vertex has no unvisited
                neighbours, the function automatically returns.

                This automatic return is called BACKTRACKING.

                Recursion internally uses the FUNCTION CALL STACK.
                */

                DFS_helper(v, visited);
            }
        }

        /*
        BACKTRACKING:

        Once all neighbours are explored, this function returns
        to the previous recursive call.

        We do not need to write a separate backtracking statement.
        The function call stack handles it automatically.
        */
    }


public:

    /*
    ===========================================================================
                            5. CONSTRUCTOR
    ===========================================================================

    Constructor:

        Graph(int vertices)

    It initializes the graph when an object is created.

    Example:

        Graph g(5);

    Here:

        vertices = 5
        V = 5

    WHY adj.resize(V)?

        Initially, the vector is empty.

            adj.size() = 0

        After:

            adj.resize(5);

        It contains five list<int> objects.

        Conceptually:

            Index 0 --> Empty List
            Index 1 --> Empty List
            Index 2 --> Empty List
            Index 3 --> Empty List
            Index 4 --> Empty List

        Later, edges will be inserted into these lists.

    IMPORTANT DIFFERENCE:

        resize():
            Changes the number of elements.

        reserve():
            Allocates capacity but does not create elements.

        We use resize() because we need V actual adjacency lists.

    */

    Graph(int vertices)
    {
        V = vertices;

        // Create V empty adjacency lists.
        adj.resize(V);
    }


    /*
    ===========================================================================
                            6. ADD EDGE FUNCTION
    ===========================================================================

    Function:

        addEdge(int u, int v)

    Parameters:

        u = First vertex.
        v = Second vertex.

    Example:

        addEdge(0, 1);

    It connects vertex 0 with vertex 1.

    WHY TWO PUSH_BACK OPERATIONS?

        We are implementing an UNDIRECTED GRAPH.

        An undirected edge means:

            0 <------> 1

        Therefore, both vertices are neighbours of each other.

        First operation:

            adj[u].push_back(v);

            Inserts v into the adjacency list of u.

        Second operation:

            adj[v].push_back(u);

            Inserts u into the adjacency list of v.

    push_back():

        Inserts an element at the end of the list.

        For a linked list, this operation is O(1).

    FOR DIRECTED GRAPH:

        We would only need:

            adj[u].push_back(v);

    */

    void addEdge(int u, int v)
    {
        // Validate vertex indices before accessing the vector.

        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            cout << "Invalid vertex!" << endl;
            return;
        }

        // Insert v into the adjacency list of u.
        adj[u].push_back(v);

        // Insert u into the adjacency list of v.
        // Required because this is an undirected graph.
        adj[v].push_back(u);
    }


    /*
    ===========================================================================
                        7. DISPLAY ADJACENCY LIST
    ===========================================================================

    WHY DO WE NEED THIS FUNCTION?

        To display the graph representation.

    OUTER LOOP:

        for (int i = 0; i < V; i++)

        Visits every vertex.

    INNER LOOP:

        for (int neighbour : adj[i])

        Visits every neighbour of vertex i.

    WHY USE RANGE-BASED FOR LOOP?

        It directly iterates through every element.

        We do not need to manage indices or iterators manually.

    */

    void display()
    {
        cout << "\nAdjacency List:" << endl;

        for (int i = 0; i < V; i++)
        {
            cout << i << " --> ";

            for (int neighbour : adj[i])
            {
                cout << neighbour << " ";
            }

            cout << endl;
        }
    }


    /*
    ===========================================================================
                    8. BREADTH FIRST SEARCH (BFS)
    ===========================================================================

    FULL FORM:
        Breadth First Search.

    DEFINITION:

        BFS is a graph traversal algorithm that explores
        vertices level by level.

    DATA STRUCTURE:
        QUEUE.

    WHY QUEUE?

        Queue follows FIFO:

            First In, First Out.

        The vertex inserted first is processed first.

        This naturally allows BFS to explore one level
        before moving to the next level.

    IMPORTANT VARIABLES:

        vector<bool> visited(V, false);

            Tracks whether a vertex has already been visited.

            Initially every vertex is unvisited.

        queue<int> q;

            Stores vertices waiting to be explored.

            We store integer vertex numbers, not Boolean values.

        int src:

            Starting vertex.

    */

    void BFS(int src)
    {
        // Check whether the source vertex is valid.

        if (src < 0 || src >= V)
        {
            cout << "Invalid source vertex!" << endl;
            return;
        }


        /*
        STEP 1: CREATE VISITED ARRAY.

        vector<bool> visited(V, false);

        Example when V = 5:

            Index:    0      1      2      3      4
            Value:  false  false  false  false  false

        Every vertex is initially unvisited.
        */

        vector<bool> visited(V, false);


        /*
        STEP 2: CREATE QUEUE.

        queue<int> q;

        Queue stores vertices waiting for processing.

        FIFO = First In, First Out.
        */

        queue<int> q;


        /*
        STEP 3: INSERT STARTING VERTEX.

        Push the source vertex into the queue.
        */

        q.push(src);


        /*
        STEP 4: MARK SOURCE AS VISITED.

        WHY MARK IT IMMEDIATELY?

        If we mark it only after removing it from the queue,
        another vertex might insert it again.

        Therefore, we mark a vertex visited when it is enqueued.

        Each vertex is enqueued at most once.
        */

        visited[src] = true;


        cout << "\nBFS Traversal: ";


        /*
        STEP 5: PROCESS WHILE QUEUE IS NOT EMPTY.

        q.empty():

            Returns true when the queue contains no elements.

        !q.empty():

            Means the queue still contains elements.

        */

        while (!q.empty())
        {
            /*
            STEP 6: ACCESS FRONT ELEMENT.

            q.front():

                Returns the first element without removing it.

            We store it in u because we need to process
            the adjacency list of this vertex.
            */

            int u = q.front();


            /*
            STEP 7: REMOVE FRONT ELEMENT.

            q.pop():

                Removes the front element.

            IMPORTANT:

                pop() does not return the removed element.

                That is why we use front() before pop().
            */

            q.pop();


            // Process current vertex.
            cout << u << " ";


            /*
            STEP 8: EXPLORE ALL NEIGHBOURS.

            adj[u] contains all neighbours of current vertex u.
            */

            for (int v : adj[u])
            {
                /*
                STEP 9: CHECK VISITED STATUS.

                If neighbour v is unvisited, we need to explore it.
                */

                if (!visited[v])
                {
                    /*
                    STEP 10: INSERT INTO QUEUE.

                    This vertex will be explored later.
                    */

                    q.push(v);


                    /*
                    STEP 11: MARK IT VISITED.

                    We mark it immediately after insertion.

                    This avoids duplicate insertions.
                    */

                    visited[v] = true;
                }
            }
        }

        // Queue empty means all reachable vertices are explored.

        cout << endl;
    }


    /*
    ===========================================================================
                    9. RECURSIVE DEPTH FIRST SEARCH
    ===========================================================================

    FULL FORM:
        Depth First Search.

    DEFINITION:

        DFS explores a path as deeply as possible before
        backtracking to explore another path.

    DATA STRUCTURE:

        Recursion uses the FUNCTION CALL STACK internally.

    IMPORTANT VARIABLES:

        vector<bool> visited:

            Tracks already visited vertices.

        int src:

            Starting vertex.

    */

    void DFS(int src)
    {
        // Validate source vertex.

        if (src < 0 || src >= V)
        {
            cout << "Invalid source vertex!" << endl;
            return;
        }


        /*
        STEP 1: CREATE VISITED ARRAY.

        Initially, all vertices are unvisited.

        This array is shared among all recursive calls.
        */

        vector<bool> visited(V, false);


        cout << "\nRecursive DFS Traversal: ";


        /*
        STEP 2: CALL RECURSIVE HELPER FUNCTION.

        DFS_helper() handles:

            1. Marking visited.
            2. Printing current vertex.
            3. Exploring neighbours.
            4. Recursive calls.
            5. Backtracking.

        */

        DFS_helper(src, visited);


        cout << endl;
    }


    /*
    ===========================================================================
                    10. ITERATIVE DEPTH FIRST SEARCH
                            DFS USING STACK
    ===========================================================================

    Recursive DFS uses the system call stack.

    Iterative DFS uses an explicitly created stack.

    WHY STACK?

        Stack follows LIFO:

            Last In, First Out.

        The most recently inserted vertex is processed first.

    IMPORTANT OPERATIONS:

        st.push(x):
            Inserts x at the top.

        st.top():
            Returns the top element.

        st.pop():
            Removes the top element.

        st.empty():
            Checks whether the stack is empty.

    WHY REVERSE ITERATION?

        Suppose adjacency list is:

            1 -> 2, 3

        If we push 2 first and 3 second:

            Stack top = 3

        So 3 will be processed first.

        To preserve recursive DFS neighbour order,
        we push neighbours in reverse order.

    NOTE:

        This implementation marks vertices visited when popped.

        A vertex can be pushed more than once before its first
        pop. The visited check skips duplicate entries.

    */

    void DFS_Iterative(int src)
    {
        if (src < 0 || src >= V)
        {
            cout << "Invalid source vertex!" << endl;
            return;
        }

        // Create visited array.
        vector<bool> visited(V, false);

        // Create explicit stack.
        stack<int> st;

        // Insert starting vertex.
        st.push(src);

        cout << "\nIterative DFS Traversal: ";

        // Continue until stack becomes empty.
        while (!st.empty())
        {
            // Access top element.
            int u = st.top();

            // Remove top element.
            st.pop();

            // Skip if already processed.
            if (visited[u])
            {
                continue;
            }

            // Mark current vertex as visited.
            visited[u] = true;

            // Process current vertex.
            cout << u << " ";

            /*
            Explore neighbours in reverse order.

            rbegin():
                Iterator pointing to the last element.

            rend():
                Iterator pointing beyond the first element
                in reverse traversal.

            This makes the first adjacency-list neighbour
            get processed first.
            */

            for (auto it = adj[u].rbegin();
                 it != adj[u].rend(); ++it)
            {
                if (!visited[*it])
                {
                    st.push(*it);
                }
            }
        }

        cout << endl;
    }


    /*
    ===========================================================================
                    11. BFS FOR DISCONNECTED GRAPHS
    ===========================================================================

    PROBLEM:

        Normal BFS starting from vertex 0 only explores
        vertices reachable from vertex 0.

        What if the graph has multiple connected components?

        Example:

            0 ---- 1 ---- 2

            3 ---- 4

            5

        Starting BFS from 0 only explores 0, 1 and 2.

    SOLUTION:

        Run BFS from every unvisited vertex.

        This explores every connected component.

    */

    void BFS_All()
    {
        vector<bool> visited(V, false);

        queue<int> q;

        cout << "\nBFS of Entire Graph: ";

        // Check every vertex.
        for (int i = 0; i < V; i++)
        {
            // Start BFS if vertex is unvisited.
            if (!visited[i])
            {
                q.push(i);
                visited[i] = true;

                // Explore this connected component.
                while (!q.empty())
                {
                    int u = q.front();
                    q.pop();

                    cout << u << " ";

                    for (int v : adj[u])
                    {
                        if (!visited[v])
                        {
                            q.push(v);
                            visited[v] = true;
                        }
                    }
                }
            }
        }

        cout << endl;
    }


    /*
    ===========================================================================
                    12. DFS FOR DISCONNECTED GRAPHS
    ===========================================================================

    Same concept as BFS_All().

    We check every vertex.

    If a vertex is unvisited, we start a new DFS.

    Each new DFS call explores one connected component.

    */

    void DFS_All()
    {
        vector<bool> visited(V, false);

        cout << "\nDFS of Entire Graph: ";

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                DFS_helper(i, visited);
            }
        }

        cout << endl;
    }


};


/*
===============================================================================
                            13. MAIN FUNCTION
===============================================================================

The main function is the entry point of the C++ program.

We create a Graph object and call its functions.

*/

int main()
{
    /*
    STEP 1: CREATE GRAPH.

    Graph g(5);

    Creates a graph with 5 vertices:

        0, 1, 2, 3, 4

    Constructor initializes the adjacency list.
    */

    Graph g(5);


    /*
    STEP 2: INSERT EDGES.

    Each addEdge() call connects two vertices.

    We are creating an undirected graph.

            0
            |
            1
           / \
          2   3
          |
          4

    */

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 4);
    g.addEdge(1, 3);


    /*
    STEP 3: DISPLAY ADJACENCY LIST.
    */

    g.display();


    /*
    STEP 4: EXECUTE BFS.

    Starting vertex = 0.

    Expected output:

        0 1 2 3 4
    */

    g.BFS(0);


    /*
    STEP 5: EXECUTE RECURSIVE DFS.

    Starting vertex = 0.

    Expected output:

        0 1 2 4 3
    */

    g.DFS(0);


    /*
    STEP 6: EXECUTE ITERATIVE DFS.

    Starting vertex = 0.

    Expected output:

        0 1 2 4 3

    */

    g.DFS_Iterative(0);


    /*
    STEP 7: TRAVERSE ENTIRE GRAPH.

    These functions also work when the graph is disconnected.

    */

    g.BFS_All();

    g.DFS_All();


    return 0;
}


/*
===============================================================================
                    14. EXPECTED OUTPUT
===============================================================================

Adjacency List:
0 --> 1
1 --> 2 3 0
2 --> 1 4
3 --> 1
4 --> 2

BFS Traversal: 0 1 2 3 4

Recursive DFS Traversal: 0 1 2 4 3

Iterative DFS Traversal: 0 1 2 4 3

BFS of Entire Graph: 0 1 2 3 4

DFS of Entire Graph: 0 1 2 4 3


===============================================================================
                    15. TIME COMPLEXITY
===============================================================================

Let:

    V = Number of vertices.
    E = Number of edges.

1. GRAPH CONSTRUCTION:

    Creating V empty adjacency lists:

        O(V)

2. ADD EDGE:

    Each edge insertion uses push_back() on a list.

        O(1) per edge

3. DISPLAY ADJACENCY LIST:

    Every vertex and every adjacency entry is processed.

        O(V + E)

4. BFS:

    Every vertex is visited at most once.

    Every adjacency entry is examined.

        O(V + E)

5. RECURSIVE DFS:

    Every vertex is visited at most once.

    Every adjacency entry is examined.

        O(V + E)

6. ITERATIVE DFS:

    Every vertex and adjacency entry is processed a
    constant number of times.

        O(V + E)


===============================================================================
                    16. SPACE COMPLEXITY
===============================================================================

1. ADJACENCY LIST:

        O(V + E)

    Every vertex has an adjacency list.
    Every undirected edge is stored twice.

2. VISITED ARRAY:

        O(V)

3. BFS QUEUE:

        O(V) auxiliary space.

4. RECURSIVE DFS:

        O(V) worst-case function call stack.

5. ITERATIVE DFS:

        O(V) worst-case auxiliary stack space,
        excluding graph storage.

TOTAL GRAPH STORAGE:

        O(V + E)

AUXILIARY SPACE FOR BFS / DFS:

        O(V)


===============================================================================
                    17. IMPORTANT INTERVIEW POINTS
===============================================================================

Q1. Why use an adjacency list?

    It stores only existing edges and is memory-efficient
    for sparse graphs.

Q2. Why use vector<list<int>>?

    Vector stores adjacency lists by vertex index.
    Each list stores that vertex's neighbours.

Q3. Why use a visited array?

    To avoid revisiting vertices and infinite traversal
    in cyclic graphs.

Q4. Why use a Boolean visited array?

    We only need two states: visited and unvisited.

Q5. Why use a queue in BFS?

    FIFO order helps explore vertices level by level.

Q6. Why use a stack in DFS?

    LIFO order helps explore the latest discovered
    vertex first.

Q7. Why pass visited by reference in recursive DFS?

    All recursive calls must share the same visited array.
    Reference avoids creating copies.

Q8. Why mark BFS vertices visited when inserting them?

    To prevent duplicate insertions into the queue.

Q9. Why does recursive DFS backtrack automatically?

    Because the function call stack stores the previous
    execution state.

Q10. Does DFS guarantee the shortest path?

    No. BFS guarantees shortest paths in unweighted graphs.

Q11. What happens in a disconnected graph?

    A traversal from one source cannot reach every component.
    We run traversal from every unvisited vertex.

Q12. What is the difference between resize() and reserve()?

    resize() creates or removes actual elements.
    reserve() changes capacity without changing size.

Q13. What is the difference between directed and undirected
     graph insertion?

    Undirected:
        adj[u].push_back(v);
        adj[v].push_back(u);

    Directed:
        adj[u].push_back(v);

Q14. Can we use vector<vector<int>> instead of
     vector<list<int>>?

    Yes. Both are valid adjacency list implementations.

Q15. Why does BFS use q.front() followed by q.pop()?

    front() retrieves the element.
    pop() removes it.
    pop() itself does not return the element.


===============================================================================
                    END OF GRAPH BFS AND DFS NOTES
===============================================================================
*/
