#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include<climits>
using namespace std;

class Node{
    public:
    Node *left;
    Node *right;
    int data;

        Node(int data){
            this->data = data;
            left = NULL;
            right = NULL;
        }
};

Node* Build_BST(Node* root,int data){
    if(root==NULL){

        return new Node(data);
    }

    if(data < root->data){
        root->left = Build_BST(root->left, data);
    }

    else{
        root->right = Build_BST(root->right, data);
    }

    return root;
}

void Print_Binaray_Tree(Node* root){

    if(root == NULL){
        return;
    }

    Print_Binaray_Tree(root->left);
    cout << root->data << " ";
    Print_Binaray_Tree(root->right);
}

bool search(Node*root,int key){

    if(root == NULL){
        return false;
    }

    if(root->data == key){
        return true;
    }

    if(root->data < key){
      return  search(root->right, key);
        
    }

    else{

        return search(root->left, key);
    }


    
}

Node* Inorder_Sucessor(Node* root){

   
   while (root != NULL && root->left != NULL){
       root = root->left;
    }

    return root;
}

Node* Delete_Node(Node* root,int node){

    if(root == NULL){
        return NULL;
    }

    if(root->data<node){
        root->right = Delete_Node(root->right, node);
    }

   else if(root->data>node){
        root->left = Delete_Node(root->left, node);
    }

    else{

        if(root->left == NULL){

            Node *temp = root->right;
            delete root;
            return temp;
        }

        else if(root->right == NULL){
            Node *temp = root->left;
            delete root;
            return temp;
        }

        Node *temp = Inorder_Sucessor(root->right);

        root->data = temp->data;
        root->right = Delete_Node(root->right, temp->data);
    }

    return root;
}

static int count = 0;
void Count_leaf_Nodes_01(Node* root){

    if(root == NULL){
        cout << "BST is Empty" << endl;
        return;
    }

    if (root->left == NULL && root->right == NULL){
        ::count++;
        return;
    }
    Count_leaf_Nodes_01(root->left);
    Count_leaf_Nodes_01(root->right);

    
}

int Count_leaf_Nodes_02(Node* root){
    if(root == NULL){
        return 0;
    }

    if(root->left == NULL && root->right == NULL){
        return 1;
    }
    int left_subtree = Count_leaf_Nodes_02(root->left);
    int right_subtree = Count_leaf_Nodes_02(root->right);

    return  left_subtree + right_subtree;
}

int count_Nodes(Node * root){

    if(root == NULL){
        return 0;
    }

    int left_subtree = count_Nodes(root->left);
    int right_subtree = count_Nodes(root->right);

    return  1 + left_subtree + right_subtree;

}

int count_internal_Nodes(Node* root){

    if(root == NULL){
        return 0;
    }

    if(root->left == NULL && root->right == NULL){
        return 0;
    }

   

    int left_subtree = count_internal_Nodes(root->left);
    int right_subtree = count_internal_Nodes(root->right);

    return 1 + left_subtree + right_subtree;
}

int count_internal_Nodes_02(Node* root) {

    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 0;
    }

    int count = 0;

    
    if (root->left != NULL && root->right != NULL) {
        count = 1;
    }


    else if (root->left != NULL || root->right != NULL) {
        count = 1;
    }

    int left_subtree = count_internal_Nodes_02(root->left);
    int right_subtree = count_internal_Nodes_02(root->right);

    return count + left_subtree + right_subtree;
}

int Height_BST(Node* root){
    if(root == NULL){
        return 0;
    }

    int left_subtree = Height_BST(root->left);
    int right_subtree = Height_BST(root->right);

    return 1 + max(left_subtree,right_subtree);
}
// Strict Binary Tree Not BST
bool is_Strict_BT(Node* root){
    // zero Nodes
    if(root == NULL){
        cout << "No TREE" << endl;
        return false;
    }

    // No leaf Nodes
    if(root->left == NULL && root->right == NULL){
        return true;
    }

    // having 2 childs
    else if(root->left != NULL && root->right != NULL){
        return is_Strict_BT(root->left) && is_Strict_BT(root->right);
    }

    return false;
}

// STRICT BST
bool IS_STRICT_BST(Node* root){
    if(root == NULL){
        return false;
    }


}

int main() {

    Node *root = NULL;
    vector<int> values = {50, 30, 70, 20, 40, 60, 80};

    // Building BST
    for (int i = 0; i < values.size(); i++){
     
       root =  Build_BST(root,values[i]);
    }

    // Printing BST
    Print_Binaray_Tree(root);
    cout << endl;

    // search in a BST
    cout << search(root, 0) << endl;

    // No of Leaf Nodes
    Count_leaf_Nodes_01(root);
    cout << "No of Leaf Nodes Method_01:" << ::count << endl;

    // No of leafs 2nd method
    cout << "No of Leaf Nodes Method_02:" <<  Count_leaf_Nodes_02(root) << endl;

    // No of Nodes in BST
    cout << "No of Nodes Method:" << count_Nodes(root) << endl;

    // No of Internal Nodes in BST

    cout << "Total Number of Internal Nodes Method_01: " << count_internal_Nodes(root)
    << endl;

    // No of Internal Nodes in BST

    cout << "Total Number of Internal Nodes Method_02: " << count_internal_Nodes_02(root)
    << endl;

    // Deleting a Node
   root =  Delete_Node(root, 50);
    Print_Binaray_Tree(root);

    // Height of BST
    cout << "Height of BST: " << Height_BST(root) << endl;

    // Strict BT
    cout << is_Strict_BT(root) << endl;

    return 0;
}