#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
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

    // Deleting a Node
    Delete_Node(root, 50);
    Print_Binaray_Tree(root);

    return 0;
}