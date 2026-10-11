/*
Topic: Binary Search Trees
Concept: Insert and search in BST.
Time Complexity: O(h)
Space Complexity: O(h)
Example Input:
5
8 3 10 1 6
6
Example Output:
Found
Practice Problems:
1) Delete node in BST
2) Validate BST
3) Find inorder successor
*/

#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int value) : val(value), left(nullptr), right(nullptr) {}
};

Node* insertNode(Node* root, int value) {
    if (root == nullptr) return new Node(value);
    if (value < root->val) root->left = insertNode(root->left, value);
    else if (value > root->val) root->right = insertNode(root->right, value);
    return root;
}

bool searchNode(Node* root, int target) {
    if (root == nullptr) return false;
    if (root->val == target) return true;
    if (target < root->val) return searchNode(root->left, target);
    return searchNode(root->right, target);
}

void freeTree(Node* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    int n;
    cin >> n;
    Node* root = nullptr;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        root = insertNode(root, x);
    }

    int target;
    cin >> target;
    cout << (searchNode(root, target) ? "Found\n" : "Not Found\n");

    freeTree(root);
    return 0;
}
