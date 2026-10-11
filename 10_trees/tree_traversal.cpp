/*
Topic: Trees
Concept: Inorder traversal of a binary tree.
Time Complexity: O(n)
Space Complexity: O(h) recursion stack
Example Input:
(uses fixed demo tree)
Example Output:
4 2 5 1 3
Practice Problems:
1) Preorder traversal
2) Postorder traversal
3) Level order traversal
*/

#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int value) : val(value), left(nullptr), right(nullptr) {}
};

void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->val << ' ';
    inorder(root->right);
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    inorder(root);
    cout << "\n";

    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;
    return 0;
}
