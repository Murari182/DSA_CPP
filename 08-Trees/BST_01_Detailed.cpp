#include <iostream>
#include <vector>
using namespace std;

// ============================================================
// NODE CLASS
// ============================================================

// THEORY:
// Each node of a Binary Search Tree (BST) contains:
// 1. data  -> the value stored in the node.
// 2. left  -> pointer to the left child.
// 3. right -> pointer to the right child.
//
// BST PROPERTY:
// - Values in the left subtree are smaller than the node's value.
// - Values in the right subtree are greater than or equal to
//   the node's value in this implementation.

class Node {
public:
    Node* left;
    Node* right;
    int data;

    // Constructor: initializes a new node.
    Node(int data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};


// ============================================================
// FUNCTION 1: BUILD BST (INSERT A NODE)
// ============================================================

// THEORY:
// Insert a value at the correct position in the BST.
//
// BASE CASE:
// If root == NULL, we have found an empty position.
// Create a new node and return its address.
//
// RECURSIVE CASE:
// If data < root->data, insert into the left subtree.
// Otherwise, insert into the right subtree.
//
// WHY ASSIGN THE RETURN VALUE?
// root->left = Build_BST(root->left, data);
//
// The recursive function returns the root pointer of the
// updated subtree. We reconnect that subtree to its parent.
//
// TIME COMPLEXITY:
// Average: O(log n) for a reasonably balanced BST.
// Worst:   O(n) for a completely skewed BST.

Node* Build_BST(Node* root, int data) {

    // Base case: found an empty position.
    if (root == NULL) {
        return new Node(data);
    }

    // Smaller values go into the left subtree.
    if (data < root->data) {
        root->left = Build_BST(root->left, data);
    }

    // Greater or equal values go into the right subtree.
    else {
        root->right = Build_BST(root->right, data);
    }

    // Return the root of the current subtree.
    return root;
}


// ============================================================
// FUNCTION 2: PRINT BST USING INORDER TRAVERSAL
// ============================================================

// THEORY:
// Inorder traversal follows this order:
//
// 1. Traverse the left subtree.
// 2. Visit the current node.
// 3. Traverse the right subtree.
//
// IMPORTANT:
// Inorder traversal of a BST prints values in sorted order.
//
// BASE CASE:
// If root == NULL, there is no node to visit.
//
// TIME COMPLEXITY: O(n)
// Every node is visited exactly once.

void Print_Binaray_Tree(Node* root) {

    // Stop when an empty subtree is reached.
    if (root == NULL) {
        return;
    }

    // Step 1: Visit the left subtree.
    Print_Binaray_Tree(root->left);

    // Step 2: Print the current node.
    cout << root->data << " ";

    // Step 3: Visit the right subtree.
    Print_Binaray_Tree(root->right);
}


// ============================================================
// FUNCTION 3: SEARCH FOR A VALUE IN BST
// ============================================================

// THEORY:
// Search uses the BST property to avoid checking every node.
//
// CASE 1: root == NULL
// The value does not exist in this subtree. Return false.
//
// CASE 2: root->data == key
// The value is found. Return true.
//
// CASE 3: root->data < key
// The key must be in the right subtree.
//
// CASE 4: root->data > key
// The key must be in the left subtree.
//
// TIME COMPLEXITY:
// Average: O(log n) for a reasonably balanced BST.
// Worst:   O(n) for a completely skewed BST.

bool search(Node* root, int key) {

    // Base case: reached an empty subtree.
    if (root == NULL) {
        return false;
    }

    // The current node contains the key.
    if (root->data == key) {
        return true;
    }

    // The key is greater, so search the right subtree.
    if (root->data < key) {
        return search(root->right, key);
    }

    // The key is smaller, so search the left subtree.
    else {
        return search(root->left, key);
    }
}


// ============================================================
// FUNCTION 4: FIND INORDER SUCCESSOR
// ============================================================

// THEORY:
// When deleting a node with TWO children, we need a replacement.
//
// The inorder successor is the next node in inorder traversal.
// For a node with a right subtree, its inorder successor is the
// SMALLEST node in that right subtree.
//
// How do we find the smallest node?
// Keep moving to the left child until no left child exists.
//
// Example:
//       70
//      /  
//     60   80
//
// The minimum node is 60.
//
// TIME COMPLEXITY: O(h)
// h is the height of the subtree.

Node* Inorder_Sucessor(Node* root) {

    // Keep moving left while a left child exists.
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }

    // Return the minimum node's address.
    return root;
}


// ============================================================
// FUNCTION 5: DELETE A NODE FROM BST
// ============================================================

// THEORY:
// First, search for the node to delete.
// Once found, there are THREE possible cases.
//
// CASE 1: LEAF NODE
// Both children are NULL.
// Delete the node and return NULL.
//
// CASE 2: NODE WITH ONE CHILD
// Save the existing child's pointer.
// Delete the current node.
// Return the child pointer so the parent reconnects to it.
//
// CASE 3: NODE WITH TWO CHILDREN
// 1. Find the inorder successor in the right subtree.
// 2. Copy the successor's data into the current node.
// 3. Delete the successor's original node recursively.
//
// WHY RETURN root?
// Returning the updated subtree root lets the parent reconnect
// its left or right pointer correctly.
//
// TIME COMPLEXITY:
// Average: O(log n) for a reasonably balanced BST.
// Worst:   O(n) for a completely skewed BST.

Node* Delete_Node(Node* root, int node) {

    // Base case: the value was not found.
    if (root == NULL) {
        return NULL;
    }

    // The target is greater than the current value.
    // Search and reconnect the right subtree.
    if (root->data < node) {
        root->right = Delete_Node(root->right, node);
    }

    // The target is smaller than the current value.
    // Search and reconnect the left subtree.
    else if (root->data > node) {
        root->left = Delete_Node(root->left, node);
    }

    // The target value has been found.
    else {

        // ----------------------------------------------------
        // CASE 1 AND CASE 2:
        // No left child: the right child replaces this node.
        // ----------------------------------------------------
        if (root->left == NULL) {

            Node* temp = root->right;

            // Free the memory occupied by the current node.
            delete root;

            // Return the replacement pointer.
            // It is NULL for a leaf node.
            return temp;
        }

        // ----------------------------------------------------
        // CASE 2:
        // No right child: the left child replaces this node.
        // ----------------------------------------------------
        else if (root->right == NULL) {

            Node* temp = root->left;

            delete root;

            return temp;
        }

        // ----------------------------------------------------
        // CASE 3:
        // The node has both left and right children.
        // ----------------------------------------------------

        // Find the smallest node in the right subtree.
        Node* temp = Inorder_Sucessor(root->right);

        // Copy its value into the current node.
        root->data = temp->data;

        // Delete the successor's original node.
        // Reconnect the updated right subtree.
        root->right = Delete_Node(root->right, temp->data);
    }

    // Return the root of the updated subtree.
    return root;
}


// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {

    // Initially, the BST is empty.
    Node* root = NULL;

    // Values to insert into the BST.
    vector<int> values = {50, 30, 70, 20, 40, 60, 80};

    // Build the BST by inserting each value.
    for (int i = 0; i < values.size(); i++) {
        root = Build_BST(root, values[i]);
    }

    // Print the BST using inorder traversal.
    cout << "BST (Inorder): ";
    Print_Binaray_Tree(root);
    cout << endl;

    // Search for a value.
    cout << "Search 0: " << search(root, 0) << endl;

    // Delete node 50.
    // Always assign the returned pointer to root.
    root = Delete_Node(root, 50);

    // Print the BST after deletion.
    cout << "After deleting 50: ";
    Print_Binaray_Tree(root);
    cout << endl;

    return 0;
}