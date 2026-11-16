#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node {
    Node* left;
    Node* right;
    int height;
    int data;

public:
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
        height = 1;  // A leaf node has height 1.
    }

    friend class AVL_TREE;
};

class AVL_TREE {
public:

    // Return the height already stored in a node.
    // A NULL subtree has height 0.
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    // Recalculate a node's height from its two children.
    void update_height(Node* node) {
        if (node == nullptr) {
            return;
        }

        node->height = 1 + max(height(node->left),
                               height(node->right));
    }

    // Balance factor = height(left subtree) - height(right subtree).
    int get_balance(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        return height(node->left) - height(node->right);
    }

    // Right rotation: the left child moves up; the old root moves down right.
    Node* right_rotation(Node* node) {
        Node* y = node;
        Node* x = y->left;
        Node* t2 = x->right;

        // Rewire links. T2 is transferred to y's left to preserve BST order.
        x->right = y;
        y->left = t2;

        // Update the node moved down first, then the new subtree root.
        update_height(y);
        update_height(x);

        return x;
    }

    // Left rotation: the right child moves up; the old root moves down left.
    Node* left_rotation(Node* node) {
        Node* y = node;
        Node* x = y->right;
        Node* t2 = x->left;

        // Rewire links. T2 is transferred to y's right to preserve BST order.
        x->left = y;
        y->right = t2;

        update_height(y);
        update_height(x);

        return x;
    }

    // Left-Right rotation = left rotation on the left child, then right rotation.
    Node* left_right_rotation(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        node->left = left_rotation(node->left);
        return right_rotation(node);
    }

    // Right-Left rotation = right rotation on the right child, then left rotation.
    Node* right_left_rotation(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        node->right = right_rotation(node->right);
        return left_rotation(node);
    }

    // Insert using normal BST rules, then restore AVL balance while returning.
    Node* insert_node(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key > node->data) {
            node->right = insert_node(node->right, key);
        }
        else if (key < node->data) {
            node->left = insert_node(node->left, key);
        }
        else {
            return node;  // Ignore duplicate keys.
        }

        update_height(node);
        int bf = get_balance(node);

        // LL: inserted key lies in the left subtree of the left child.
        if (bf > 1 && key < node->left->data) {
            return right_rotation(node);
        }

        // LR: inserted key lies in the right subtree of the left child.
        if (bf > 1 && key > node->left->data) {
            return left_right_rotation(node);
        }

        // RR: inserted key lies in the right subtree of the right child.
        if (bf < -1 && key > node->right->data) {
            return left_rotation(node);
        }

        // RL: inserted key lies in the left subtree of the right child.
        if (bf < -1 && key < node->right->data) {
            return right_left_rotation(node);
        }

        return node;
    }

    // Return the leftmost node of a subtree: the inorder successor candidate.
    Node* Inorder_Successor(Node* root) {
        while (root != nullptr && root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

    // Delete using BST rules, then update heights and rebalance on the way up.
    Node* delete_node(Node* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }

        if (key < root->data) {
            root->left = delete_node(root->left, key);
        }
        else if (key > root->data) {
            root->right = delete_node(root->right, key);
        }
        else {
            // Case 1: no child (leaf).
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            // Case 2a: only right child.
            else if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            // Case 2b: only left child.
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Case 3: two children. Copy successor value, then remove its old node.
            Node* temp = Inorder_Successor(root->right);
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data);
        }

        // The subtree may have become shorter after deletion.
        update_height(root);
        int bf = get_balance(root);

        // LL: left-heavy node; left child is balanced or left-heavy.
        if (bf > 1 && get_balance(root->left) >= 0) {
            return right_rotation(root);
        }

        // LR: left-heavy node; left child is right-heavy.
        if (bf > 1 && get_balance(root->left) < 0) {
            return left_right_rotation(root);
        }

        // RR: right-heavy node; right child is balanced or right-heavy.
        if (bf < -1 && get_balance(root->right) <= 0) {
            return left_rotation(root);
        }

        // RL: right-heavy node; right child is left-heavy.
        if (bf < -1 && get_balance(root->right) > 0) {
            return right_left_rotation(root);
        }

        return root;
    }

    void preorder(Node* node) {
        if (node == nullptr) {
            return;
        }

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void display_details(Node* node) {
        if (node == nullptr) {
            return;
        }

        display_details(node->left);

        cout << "Node: " << node->data
             << " | Height: " << node->height
             << " | BF: " << get_balance(node)
             << '\n';

        display_details(node->right);
    }

    // Release every allocated node. Call once when finished with the tree.
    void destroy_tree(Node* node) {
        if (node == nullptr) {
            return;
        }

        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }
};

int main() {
    AVL_TREE tree;
    vector<int> values = {50, 30, 70, 20, 40, 10, 25, 35, 45};

    Node* root = nullptr;

    for (int val : values) {
        root = tree.insert_node(root, val);
    }

    cout << "Before deletion\n";
    cout << "Preorder: ";
    tree.preorder(root);
    cout << "\nInorder: ";
    tree.inorder(root);
    cout << "\nNode details (inorder):\n";
    tree.display_details(root);

    int key;
    cout << "\nEnter a value to delete: ";
    if (cin >> key) {
        root = tree.delete_node(root, key);

        cout << "\nAfter deleting " << key << '\n';
        cout << "Preorder: ";
        tree.preorder(root);
        cout << "\nInorder: ";
        tree.inorder(root);
        cout << "\nNode details (inorder):\n";
        tree.display_details(root);
    }

    tree.destroy_tree(root);
    root = nullptr;

    return 0;
}
