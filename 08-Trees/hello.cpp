#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Node{
    Node * left;
    Node*right;
    int height;
    int data;
    public:
    Node(int val)
    {
        data=val;
        left=NULL;
        right=NULL;
        height=0;
    }

    friend class AVL_TREE;
};

class AVL_TREE{
    public:

    int height(Node* node){
        if(node == NULL){
            return;
        }
        node->height =  1 + max(height(node->left),height(node->right));
        return node->height;
    }

    int get_balance(Node * node){
        if(node == NULL){
            return 0;
        }

        return height(node->left) - height(node->right);
    }

    void right_rotation(Node* node){

        if(node==NULL){
            return;
        }
        Node* x;
        Node* y;
        Node* t2;

        // nmaking notations to rotate
        y = node;
        x = y->left;
        t2 = x->right;

        // right rotation
        x->right = y;
        y->left = t2;


    }

    void left_rotation(Node* node){

        if(node==NULL){
            return;
        }
        Node* x;
        Node* y;
        Node* t2;

        // notation
        x = y->left;
        t2 = x->left;

        // rotation
        x->left = y;
        y->right = t2;
        
    
    }

    void right_left_rotation(Node* node){

        if(node==NULL){
            return;
        }
        Node* x;
        Node* y;
        Node* t2;

        

    }
};

int main()
{
    
    return 0;
}