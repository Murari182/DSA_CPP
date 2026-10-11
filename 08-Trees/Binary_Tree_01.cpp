#include <iostream>
#include <vector>
#include<algorithm>
#include <queue>

using namespace std;

// Node class
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

// Global index
static int idx = -1;

// ===============================
// BUILD BINARY TREE
// ===============================
Node *build_tree(vector<int> &Nodes)
{
    idx++;

    // -1 means no node
    if (Nodes[idx] == -1)
    {
        return NULL;
    }

    // Create new node
    Node *n1 = new Node(Nodes[idx]);

    // Build left subtree
    n1->left = build_tree(Nodes);

    // Build right subtree
    n1->right = build_tree(Nodes);

    return n1;
}

// ===============================
// INORDER
// Left → Root → Right
// ===============================
void Inorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    Inorder(root->left);

    cout << root->data << " ";

    Inorder(root->right);
}

// ===============================
// PREORDER
// Root → Left → Right
// ===============================
void Preorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    cout << root->data << " ";

    Preorder(root->left);

    Preorder(root->right);
}

// ===============================
// POSTORDER
// Left → Right → Root
// ===============================
void Postorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    Postorder(root->left);

    Postorder(root->right);

    cout << root->data << " ";
}

// ===============================
// LEVEL ORDER
// BFS using Queue
// ===============================
void Level_Order(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    queue<Node *> q;

    q.push(root);

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();

        cout << curr->data << " ";

        // Push current node's left child
        if (curr->left != NULL)
        {
            q.push(curr->left);
        }

        // Push current node's right child
        if (curr->right != NULL)
        {
            q.push(curr->right);
        }
    }
}

// ===============================
// LEVEL-WISE TRAVERSAL
// ===============================
void level_Wise_Traversal(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    queue<Node *> q;

    q.push(root);
    q.push(NULL);

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();

        // End of one level
        if (curr == NULL)
        {
            cout << endl;

            // If no more nodes
            if (q.empty())
            {
                break;
            }

            // Mark end of next level
            q.push(NULL);

            continue;
        }

        cout << curr->data << " ";

        // Add left child
        if (curr->left != NULL)
        {
            q.push(curr->left);
        }

        // Add right child
        if (curr->right != NULL)
        {
            q.push(curr->right);
        }
    }

   
}

int Height_Node(Node* root){
        
    if(root == NULL){
        return 0;
    }

    int left_subtree_height = Height_Node(root->left);
    int Right_subtree_height = Height_Node(root->right);

    return 1 + max(left_subtree_height, Right_subtree_height);
}

int Node_count(Node* root){

    if(root == NULL){
        return 0;
    }

  int  left_Node_count = Node_count(root->left);
  int right_Node_count = Node_count(root->right);

  return 1 + left_Node_count + right_Node_count;
}

int sum_Nodes(Node* root){

    if(root == NULL){
        return 0;
    }

    int left_sum = sum_Nodes(root->left);
    int right_sum = sum_Nodes(root->right);

  int   sum = root->data + left_sum + right_sum;
    return sum;
}

bool search_BST(Node* root,int target){

    if(root == NULL){
        return 0;
    }

    if(target==root->data){
        
        return 1;
    }

    if(target<root->data){
       
       return search_BST(root->left, target);
        
    }
    else {
       
       return  search_BST(root->right, target);
    }

   
   
}

bool search(Node*root,int target){

    if (root == NULL){
        return 0;
    }

    if(root->data == target){
        return true;
   }

   bool left_tree = search(root->left, target);
   if(left_tree){
       return true;
   }

   bool right_tree = search(root->right, target);
   if(right_tree){
       return true;
   }

   return false;
}

bool check_BST(Node* root){

    if(root == NULL){
        return false;
    }

}

// ===============================
// MAIN
// ===============================
int main()
{
    vector<int> arr = {50, 30, -1, -1, 70, 60, -1, -1, 80, -1, -1};

    // Build tree
    Node *root = build_tree(arr);

    // Display tree root
    cout << "Root Value: " << root->data << endl;

    // Inorder
    cout << "Inorder Traversal: ";
    Inorder(root);
    cout << endl;

    // Preorder
    cout << "Preorder Traversal: ";
    Preorder(root);
    cout << endl;

    // Postorder
    cout << "Postorder Traversal: ";
    Postorder(root);
    cout << endl;

    // Level Order
    cout << "Level Order Traversal: ";
    Level_Order(root);
    cout << endl;

    // Level Wise
    cout << "Level Wise Traversal:" << endl;
    level_Wise_Traversal(root);
    
    // Height_Node
    int height = Height_Node(root);
    cout << "Height of the tree is: " << height << endl;
    


    // No of Nodes
    int No_Nodes = Node_count(root);
    cout << "Number of Nodes in the Tree is: " << No_Nodes << endl;

    // Sum of Nodes
    int SumNodes = sum_Nodes(root);
    cout << "Sum of Nodes in the Tree is : " << SumNodes << endl;

    // Searching in BST
   cout << search_BST(root, 30) << endl;

    // searching in BT
   cout << search(root, 70) << endl;

   // Checking BST
   cout << check_BST(root) << endl;

   return 0;

}