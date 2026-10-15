// Array-Based Binary Tree in C++

#include <iostream>   // For input and output: cout, endl
#include <vector>     // For using vector<int>
#include <algorithm>  // For general-purpose algorithms
#include <string>     // For string data type

using namespace std;

// ==========================================================
// CLASS: tree
// CONCEPT: Classes and Objects in Object-Oriented Programming
//
// A Binary Tree is a hierarchical data structure in which
// each node can have at most two children:
// 1. Left child
// 2. Right child
//
// Here, we represent the tree using an array instead of
// dynamically allocated nodes.
//
// IMPORTANT:
// This array representation is most suitable for complete
// binary trees or binary heaps. A general binary tree with
// missing internal children needs a way to represent gaps.
// ==========================================================

class tree {

public:
    // ------------------------------------------------------
    // DATA MEMBERS
    // CONCEPT: Encapsulation and Array Representation
    // ------------------------------------------------------

    int arr[100];  // Stores tree nodes in an array.
                   // Maximum capacity = 100 integers.

    int size;      // Tracks the CURRENT number of nodes.
                   // size is NOT the capacity of the array.

    // ------------------------------------------------------
    // CONSTRUCTOR
    // CONCEPT: Constructor
    //
    // A constructor is automatically called when an object
    // is created. Here, it initializes the tree as empty.
    // ------------------------------------------------------

    tree() {
        size = 0;
    }

    // ------------------------------------------------------
    // FUNCTION: Build_BT
    // PURPOSE: Insert the elements of a vector into the tree.
    //
    // CONCEPTS:
    // 1. Pass by reference using vector<int>&
    // 2. Array indexing
    // 3. Capacity checking
    // 4. Iteration using a while loop
    // ------------------------------------------------------

    void Build_BT(const vector<int>& arr) {

        // Check whether the tree is already full.
        if (size == 100) {
            cout << "Tree is Full" << endl;
            return;
        }

        // vector.size() returns the number of input elements.
        int n = arr.size();

        // Copy elements while:
        // 1. There are input elements left.
        // 2. The tree has not reached its capacity.
        //
        // Using size as the insertion index means that
        // existing nodes are preserved when adding more data.
        while (size < n && size < 100) {

            // this->arr refers to the array belonging
            // to the current tree object.
            //
            // arr[size] on the right-hand side refers to
            // the input vector passed to this function.
            this->arr[size] = arr[size];

            // Increase the number of stored nodes.
            size++;
        }
    }

    // ------------------------------------------------------
    // FUNCTION: Print_tree
    // PURPOSE: Display all elements stored in the tree.
    //
    // CONCEPT: Traversing an array using a for loop.
    //
    // NOTE:
    // This prints the array representation in level order,
    // not an inorder, preorder, or postorder traversal.
    // ------------------------------------------------------

    void Print_tree() {

        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }

        cout << endl;
    }

    // ------------------------------------------------------
    // FUNCTION: child
    // PURPOSE: Display a node and its left and right children.
    //
    // CONCEPT: Index-based navigation in a binary tree.
    //
    // For a ZERO-INDEXED array:
    //
    // Parent of i = (i - 1) / 2, for i > 0
    // Left child  = 2*i + 1
    // Right child = 2*i + 2
    //
    // These formulas assume the standard compact array
    // representation of a complete binary tree.
    // ------------------------------------------------------

    void child(int index) {

        // A valid node index must satisfy:
        // 0 <= index < size
        //
        // index == size is INVALID because indexing starts
        // from 0 and the last valid index is size - 1.
        if (index < 0 || index >= size) {
            cout << "Invalid Index" << endl;
            return;
        }

        // Calculate the indices of the two children.
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;

        // Display the current node.
        cout << "Node is: " << arr[index] << endl;

        // Check whether the left child exists.
        if (left_child < size) {
            cout << "Left child is: "
                 << arr[left_child] << endl;
        }
        else {
            cout << "No Left Child" << endl;
        }

        // Check whether the right child exists.
        if (right_child < size) {
            cout << "Right child is: "
                 << arr[right_child] << endl;
        }
        else {
            cout << "No Right Child" << endl;
        }
    }
};

// ==========================================================
// MAIN FUNCTION
// CONCEPT: Program Execution and Object Creation
// ==========================================================

int main() {

    // Input data stored in a vector.
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70};

    // Create an object of class tree.
    // The constructor initializes size = 0.
    tree t1;

    // Copy the vector elements into the tree's internal array.
    t1.Build_BT(arr);

    // Display the number of stored nodes.
    cout << "Number of Nodes in Tree: "
         << t1.size << endl;

    // Print the array representation of the tree.
    t1.Print_tree();

    // Display the node at index 0 and its children.
    t1.child(0);

    return 0;
}

