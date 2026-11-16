
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Node {
    Node* left;
    Node* right;
    int height;
    int data;

public:
    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
        height = 1;  // Leaf node height = 1
    }

    friend class AVL_TREE;
};

class AVL_TREE {
public:

    // Get stored height
    int height(Node* node) {
        if (node == NULL) {
            return 0;
        }

        return node->height;
    }

    // Update height
    void update_height(Node* node) {
        if (node == NULL) {
            return;
        }

        node->height = 1 + max(height(node->left),
                               height(node->right));
    }

    // Calculate balance factor
    int get_balance(Node* node) {
        if (node == NULL) {
            return 0;
        }

        return height(node->left) - height(node->right);
    }

    // Right Rotation
    Node* right_rotation(Node* node) {

        Node* y = node;
        Node* x = y->left;
        Node* t2 = x->right;

        // Rotation
        x->right = y;
        y->left = t2;

        // Update heights
        update_height(y);
        update_height(x);

        return x;
    }

    // Left Rotation
    Node* left_rotation(Node* node) {

        Node* y = node;
        Node* x = y->right;
        Node* t2 = x->left;

        // Rotation
        x->left = y;
        y->right = t2;

        // Update heights
        update_height(y);
        update_height(x);

        return x;
    }

    // Left-Right Rotation
    Node* left_right_rotation(Node* node) {

        if (node == NULL) {
            return NULL;
        }

        node->left = left_rotation(node->left);

        return right_rotation(node);
    }

    // Right-Left Rotation
    Node* right_left_rotation(Node* node) {

        if (node == NULL) {
            return NULL;
        }

        node->right = right_rotation(node->right);

        return left_rotation(node);
    }

    // Insertion
    Node* insert_node(Node* node, int key) {
        if (node == NULL) {
            return new Node(key);
        }

        if (key > node->data) {
            node->right = insert_node(node->right, key);
        }

        else if (key < node->data) {
            node->left = insert_node(node->left, key);
        }

        else {
            return node;
        }

        update_height(node);

        int bf = get_balance(node);

        // LL case
        if (bf > 1 && key < node->left->data) {
            return right_rotation(node);
        }

        // LR case
        if (bf > 1 && key > node->left->data) {
            return left_right_rotation(node);
        }

        // RR case
        if (bf < -1 && key > node->right->data) {
            return left_rotation(node);
        }

        // RL case
        if (bf < -1 && key < node->right->data) {
            return right_left_rotation(node);
        }

        return node;
    }

    void preorder(Node* node) {
        if (node == NULL)
            return;

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void display_details(Node* node) {
        if (node == NULL) {
            return;
        }

        display_details(node->left);

        cout << "Node: " << node->data
             << " | Height: " << node->height
             << " | BF: " << get_balance(node)
             << endl;

        display_details(node->right);
    }

    Node* Inorder_Successor(Node* root) {

        while (root != NULL && root->left != NULL) {
            root = root->left;
        }

        return root;
    }

    Node* delete_node(Node* root, int key) {

        if (root == NULL) {
            return NULL;
        }

        if (key < root->data) {
            root->left = delete_node(root->left, key);
        }
        else if (key > root->data) {
            root->right = delete_node(root->right, key);
        }
        else {

            if (root->left == NULL &&
                root->right == NULL) {

                delete root;
                return NULL;
            }

            else if (root->left == NULL) {

                Node* temp = root->right;
                delete root;
                return temp;
            }

            else if (root->right == NULL) {

                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = Inorder_Successor(root->right);

            root->data = temp->data;

            root->right = delete_node(root->right, temp->data);
        }

        update_height(root);

        int bf = get_balance(root);

        // LL case
        if (bf > 1 && get_balance(root->left) >= 0) {
            return right_rotation(root);
        }

        // LR case
        if (bf > 1 && get_balance(root->left) < 0) {
            return left_right_rotation(root);
        }

        // RR case
        if (bf < -1 && get_balance(root->right) <= 0) {
            return left_rotation(root);
        }

        // RL case
        if (bf < -1 && get_balance(root->right) > 0) {
            return right_left_rotation(root);
        }

        return root;
    }
};

int main() {

    AVL_TREE tree;

    vector<int> values = {50, 30, 70, 20, 40, 10, 25, 35, 45};

    Node* root = NULL;

    for (int val : values) {
        root = tree.insert_node(root, val);
    }

    cout << "Preorder: ";
    tree.preorder(root);
    cout << endl;

    tree.display_details(root);

    int key;
    cout << "\nEnter node to delete: ";
    cin >> key;

    root = tree.delete_node(root, key);

    cout << "\nPreorder after deletion: ";
    tree.preorder(root);
    cout << endl;

    tree.display_details(root);

    cout << "\n";

    return 0;
}
