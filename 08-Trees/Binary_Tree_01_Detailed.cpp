#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

// ============================================================
// NODE CLASS
// ============================================================

// THEORY:
// Every binary tree node contains:
// 1. data  -> stores the node's value.
// 2. left  -> pointer to the left child.
// 3. right -> pointer to the right child.
//
// NULL means that the child does not exist.

class Node {
public:
    Node* left;
    Node* right;
    int data;

    Node(int data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};


// Global index used to read the preorder array.
static int idx = -1;


// ============================================================
// 1. BUILD BINARY TREE
// ============================================================

// THEORY:
// The input array represents a tree in preorder format:
//
// Root -> Left subtree -> Right subtree
//
// -1 represents a missing node.
//
// Example:
// {50, 30, -1, -1, 70, ...}
//
// 50 becomes the root.
// 30 becomes the left child of 50.
// The two -1 values mean 30 has no children.
//
// TIME COMPLEXITY: O(n)
// Each array element is processed once.

Node* build_tree(vector<int>& Nodes) {

    // Move to the next array element.
    idx++;

    // -1 represents an empty subtree.
    if (Nodes[idx] == -1) {
        return NULL;
    }

    // Create a node using the current value.
    Node* n1 = new Node(Nodes[idx]);

    // Recursively construct the left subtree.
    n1->left = build_tree(Nodes);

    // Recursively construct the right subtree.
    n1->right = build_tree(Nodes);

    // Return the root of the constructed subtree.
    return n1;
}


// ============================================================
// 2. INORDER TRAVERSAL
// ============================================================

// THEORY:
// Inorder = Left -> Root -> Right
//
// First visit the left subtree,
// then print the current node,
// then visit the right subtree.
//
// Inorder traversal of a BST produces sorted values.
// For a general binary tree, it does not necessarily produce
// sorted values.
//
// TIME COMPLEXITY: O(n)

void Inorder(Node* root) {

    // Base case: empty subtree.
    if (root == NULL) {
        return;
    }

    // Step 1: Visit left subtree.
    Inorder(root->left);

    // Step 2: Visit current node.
    cout << root->data << " ";

    // Step 3: Visit right subtree.
    Inorder(root->right);
}


// ============================================================
// 3. PREORDER TRAVERSAL
// ============================================================

// THEORY:
// Preorder = Root -> Left -> Right
//
// Print the current node first,
// then visit its left subtree,
// then visit its right subtree.
//
// Preorder is useful for serializing or reconstructing
// a binary tree when null-child markers are included.
//
// TIME COMPLEXITY: O(n)

void Preorder(Node* root) {

    if (root == NULL) {
        return;
    }

    // Step 1: Visit current node.
    cout << root->data << " ";

    // Step 2: Visit left subtree.
    Preorder(root->left);

    // Step 3: Visit right subtree.
    Preorder(root->right);
}


// ============================================================
// 4. POSTORDER TRAVERSAL
// ============================================================

// THEORY:
// Postorder = Left -> Right -> Root
//
// Visit both children before processing the current node.
//
// Postorder is useful when deleting or freeing a tree,
// because children can be processed before their parent.
//
// TIME COMPLEXITY: O(n)

void Postorder(Node* root) {

    if (root == NULL) {
        return;
    }

    // Step 1: Visit left subtree.
    Postorder(root->left);

    // Step 2: Visit right subtree.
    Postorder(root->right);

    // Step 3: Visit current node.
    cout << root->data << " ";
}


// ============================================================
// 5. LEVEL ORDER TRAVERSAL
// ============================================================

// THEORY:
// Level order visits nodes level by level.
//
// It uses BFS (Breadth-First Search) and a queue.
//
// Queue follows FIFO:
// First In, First Out.
//
// Algorithm:
// 1. Insert root into the queue.
// 2. Remove the front node and print it.
// 3. Insert its left child, if present.
// 4. Insert its right child, if present.
// 5. Repeat until the queue is empty.
//
// TIME COMPLEXITY: O(n)
// AUXILIARY SPACE: O(w), where w is maximum tree width.

void Level_Order(Node* root) {

    if (root == NULL) {
        return;
    }

    queue<Node*> q;

    // Begin with the root.
    q.push(root);

    while (!q.empty()) {

        // Take the front node.
        Node* curr = q.front();

        // Remove it from the queue.
        q.pop();

        // Visit the current node.
        cout << curr->data << " ";

        // Add the left child to the queue.
        if (curr->left != NULL) {
            q.push(curr->left);
        }

        // Add the right child to the queue.
        if (curr->right != NULL) {
            q.push(curr->right);
        }
    }
}


// ============================================================
// 6. LEVEL-WISE TRAVERSAL
// ============================================================

// THEORY:
// This is also BFS, but it prints each level on a separate line.
//
// A NULL marker is used to identify the end of a level.
//
// Algorithm:
// 1. Push root.
// 2. Push NULL to mark the end of the current level.
// 3. Process nodes until NULL is reached.
// 4. Print a newline and add another NULL marker if needed.
//
// TIME COMPLEXITY: O(n)

void level_Wise_Traversal(Node* root) {

    if (root == NULL) {
        return;
    }

    queue<Node*> q;

    q.push(root);

    // Marks the end of the first level.
    q.push(NULL);

    while (!q.empty()) {

        Node* curr = q.front();
        q.pop();

        // End of the current level.
        if (curr == NULL) {

            cout << endl;

            // No nodes remain for another level.
            if (q.empty()) {
                break;
            }

            // Mark the end of the next level.
            q.push(NULL);

            continue;
        }

        // Print current node.
        cout << curr->data << " ";

        // Add left child.
        if (curr->left != NULL) {
            q.push(curr->left);
        }

        // Add right child.
        if (curr->right != NULL) {
            q.push(curr->right);
        }
    }
}


// ============================================================
// 7. HEIGHT OF THE TREE
// ============================================================

// THEORY:
// Height here means the number of nodes on the longest
// root-to-leaf path.
//
// Base case:
// Empty tree has height 0.
//
// Recursive formula:
// Height = 1 + max(left height, right height)
//
// The +1 counts the current node.
//
// For our tree:
// Root 50 -> 70 -> 60 is a longest path of 3 nodes.
//
// TIME COMPLEXITY: O(n)

int Height_Node(Node* root) {

    if (root == NULL) {
        return 0;
    }

    int left_subtree_height = Height_Node(root->left);
    int right_subtree_height = Height_Node(root->right);

    return 1 + max(left_subtree_height,
                   right_subtree_height);
}


// ============================================================
// 8. COUNT TOTAL NODES
// ============================================================

// THEORY:
// Count the current node and all nodes in both subtrees.
//
// Recursive formula:
// Total = 1 + left count + right count
//
// The 1 represents the current node.
//
// TIME COMPLEXITY: O(n)

int Node_count(Node* root) {

    // An empty subtree contains zero nodes.
    if (root == NULL) {
        return 0;
    }

    int left_Node_count = Node_count(root->left);
    int right_Node_count = Node_count(root->right);

    return 1 + left_Node_count + right_Node_count;
}


// ============================================================
// 9. SUM OF ALL NODE VALUES
// ============================================================

// THEORY:
// Add the current node's value to the sums of both subtrees.
//
// Recursive formula:
// Sum = root->data + left sum + right sum
//
// An empty subtree contributes zero.
//
// TIME COMPLEXITY: O(n)

int sum_Nodes(Node* root) {

    if (root == NULL) {
        return 0;
    }

    int left_sum = sum_Nodes(root->left);
    int right_sum = sum_Nodes(root->right);

    int sum = root->data + left_sum + right_sum;

    return sum;
}


// ============================================================
// 10. SEARCH IN A BST
// ============================================================

// THEORY:
// This function assumes that the tree follows the BST property.
//
// If target == root->data, the value is found.
//
// If target < root->data, search only the left subtree.
//
// If target > root->data, search only the right subtree.
//
// We can eliminate one subtree at every step.
//
// TIME COMPLEXITY:
// Average: O(log n) for a balanced BST.
// Worst: O(n) for a skewed BST.

bool search_BST(Node* root, int target) {

    if (root == NULL) {
        return false;
    }

    // The current node contains the target.
    if (target == root->data) {
        return true;
    }

    // Smaller target: search left.
    if (target < root->data) {
        return search_BST(root->left, target);
    }

    // Larger target: search right.
    else {
        return search_BST(root->right, target);
    }
}


// ============================================================
// 11. SEARCH IN A GENERAL BINARY TREE
// ============================================================

// THEORY:
// A general binary tree does not have to follow BST ordering.
//
// Therefore, we cannot decide which subtree contains the
// target just by comparing values.
//
// We may need to search both subtrees.
//
// Algorithm:
// 1. Check the current node.
// 2. Search the left subtree.
// 3. If found on the left, return true.
// 4. Otherwise search the right subtree.
//
// TIME COMPLEXITY: O(n) in the worst case.

bool search(Node* root, int target) {

    if (root == NULL) {
        return false;
    }

    // Check the current node.
    if (root->data == target) {
        return true;
    }

    // Search the left subtree.
    bool left_tree = search(root->left, target);

    if (left_tree) {
        return true;
    }

    // Search the right subtree.
    bool right_tree = search(root->right, target);

    if (right_tree) {
        return true;
    }

    // Target was not found in either subtree.
    return false;
}


// ============================================================
// 12. CHECK WHETHER THE TREE IS A BST
// ============================================================

// THEORY:
// Checking only the immediate children is NOT sufficient.
//
// For every node, all values in its left subtree must be
// smaller than it, and all values in its right subtree
// must be greater than it.
//
// We maintain a valid range (minVal, maxVal) for every node.
//
// Initially, the root can have any int value.
// After visiting a node:
// - Its left subtree must be less than the node's value.
// - Its right subtree must be greater than the node's value.
//
// This version checks a STRICT BST with unique keys.
// An empty tree is considered a BST.
//
// TIME COMPLEXITY: O(n)

bool check_BST(Node* root,
               long long minVal = LLONG_MIN,
               long long maxVal = LLONG_MAX) {

    // An empty subtree satisfies the BST property.
    if (root == NULL) {
        return true;
    }

    // Current value must be strictly inside its valid range.
    if (root->data <= minVal || root->data >= maxVal) {
        return false;
    }

    // Every value in the left subtree must be smaller.
    bool left_valid = check_BST(
        root->left, minVal, root->data
    );

    // Stop if the left subtree is invalid.
    if (!left_valid) {
        return false;
    }

    // Every value in the right subtree must be greater.
    bool right_valid = check_BST(
        root->right, root->data, maxVal
    );

    return right_valid;
}


// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {

    // Preorder representation of the binary tree.
    // -1 represents a missing child.
    vector<int> arr = {
        50, 30, -1, -1, 70, 60, -1, -1, 80, -1, -1
    };

    // Reset the global index before building the tree.
    idx = -1;

    Node* root = build_tree(arr);

    // Display root value.
    cout << "Root Value: " << root->data << endl;

    // Inorder traversal.
    cout << "Inorder Traversal: ";
    Inorder(root);
    cout << endl;

    // Preorder traversal.
    cout << "Preorder Traversal: ";
    Preorder(root);
    cout << endl;

    // Postorder traversal.
    cout << "Postorder Traversal: ";
    Postorder(root);
    cout << endl;

    // Level order traversal.
    cout << "Level Order Traversal: ";
    Level_Order(root);
    cout << endl;

    // Print each level on a separate line.
    cout << "Level Wise Traversal:" << endl;
    level_Wise_Traversal(root);

    // Height.
    int height = Height_Node(root);
    cout << "Height of the tree is: " << height << endl;

    // Total number of nodes.
    int No_Nodes = Node_count(root);
    cout << "Number of Nodes in the Tree is: "
         << No_Nodes << endl;

    // Sum of node values.
    int SumNodes = sum_Nodes(root);
    cout << "Sum of Nodes in the Tree is: "
         << SumNodes << endl;

    // Search using BST property.
    cout << "Search 30 in BST: "
         << search_BST(root, 30) << endl;

    // Search in a general binary tree.
    cout << "Search 70 in BT: "
         << search(root, 70) << endl;

    // Check whether the entire tree is a BST.
    cout << "Is this a BST? "
         << check_BST(root) << endl;

    return 0;
}