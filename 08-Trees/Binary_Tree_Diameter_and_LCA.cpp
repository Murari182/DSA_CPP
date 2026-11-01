#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

class Node
{
public:
    Node *left;
    Node *right;
    int data;

    Node(int data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

Node *Build_BST(Node *root, int data)
{
    if (root == NULL)
    {
        return new Node(data);
    }

    if (data < root->data)
    {
        root->left = Build_BST(root->left, data);
    }
    else
    {
        root->right = Build_BST(root->right, data);
    }

    return root;
}

// 1. Diameter of Binary Tree in O(n) Time (single bottom-up pass)
int height_for_diameter(Node *root, int &max_diameter)
{
    if (root == NULL)
    {
        return 0;
    }

    int left_h = height_for_diameter(root->left, max_diameter);
    int right_h = height_for_diameter(root->right, max_diameter);

    // Diameter passing through current root (in edges)
    max_diameter = max(max_diameter, left_h + right_h);

    return 1 + max(left_h, right_h);
}

int Diameter_BT(Node *root)
{
    int max_diameter = 0;
    height_for_diameter(root, max_diameter);
    return max_diameter;
}

// 2. Check if Binary Tree is Height-Balanced in O(n) Time
int check_height_balanced(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int left_h = check_height_balanced(root->left);
    if (left_h == -1)
    {
        return -1;
    }

    int right_h = check_height_balanced(root->right);
    if (right_h == -1)
    {
        return -1;
    }

    if (abs(left_h - right_h) > 1)
    {
        return -1;
    }

    return 1 + max(left_h, right_h);
}

bool is_Balanced_BT(Node *root)
{
    return check_height_balanced(root) != -1;
}

// 3. Lowest Common Ancestor (LCA) in a BST: O(h) Time
Node *LCA_BST(Node *root, int n1, int n2)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->data > n1 && root->data > n2)
    {
        return LCA_BST(root->left, n1, n2);
    }

    if (root->data < n1 && root->data < n2)
    {
        return LCA_BST(root->right, n1, n2);
    }

    return root;
}

// 4. Complete Strict BST Check (Full Binary Tree + Valid BST): O(n) Time
bool is_strict_bst_helper(Node *root, long long minVal, long long maxVal)
{
    if (root == NULL)
    {
        return true;
    }

    if (root->data <= minVal || root->data >= maxVal)
    {
        return false;
    }

    // Leaf node (0 children)
    if (root->left == NULL && root->right == NULL)
    {
        return true;
    }

    // Internal node with 2 children
    if (root->left != NULL && root->right != NULL)
    {
        return is_strict_bst_helper(root->left, minVal, root->data) &&
               is_strict_bst_helper(root->right, root->data, maxVal);
    }

    // Node with only 1 child violates strict binary tree property
    return false;
}

bool IS_STRICT_BST(Node *root)
{
    if (root == NULL)
    {
        return false;
    }
    return is_strict_bst_helper(root, LLONG_MIN, LLONG_MAX);
}

int main()
{
    Node *root = NULL;
    vector<int> values = {50, 30, 70, 20, 40, 60, 80};

    for (int val : values)
    {
        root = Build_BST(root, val);
    }

    cout << "Diameter of Tree (in edges): " << Diameter_BT(root) << endl;
    cout << "Is Height-Balanced: " << is_Balanced_BT(root) << endl;

    Node *lca = LCA_BST(root, 20, 40);
    if (lca != NULL)
    {
        cout << "LCA of 20 and 40: " << lca->data << endl;
    }

    cout << "Is Strict BST: " << IS_STRICT_BST(root) << endl;

    return 0;
}
