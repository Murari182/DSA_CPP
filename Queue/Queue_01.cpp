#include<iostream>
using namespace std;

class Node{
    int data;
    Node *next;

    public:

        Node(int data){
        this->data = data;
        next = NULL;
 }

 friend class que;
};

class que{

    Node *front;
    Node *rear;
    public:

    que(){

        front = NULL;
        rear = NULL;
    }

    void enque(int val){

        Node *n1 = new Node(val);
        if(rear == NULL){
            front = n1;
            rear = n1;
            return;
        }
        rear->next = n1;
        rear = n1;
    }

    void peek(){
        if(front == NULL){
            cout << "The que is Empty" << endl;
            return;
        }
        cout << front->data << endl;
    }

    void dequeue(){

        if(front->next == NULL){
            delete front;
            front = NULL;
            rear = NULL;
            return;
        }

        Node *temp = front;
        front = front->next;
        delete temp;
    }
};

int main(){
    que q1;
    q1.enque(10);
    q1.dequeue();
    q1.peek();
    // q1.enque(20);
    // q1.enque(30);
    // q1.enque(40);
    // q1.enque(50);
    // q1.enque(60);
    // q1.peek();
    // q1.dequeue();
    // cout << "After Deletion" << endl;
    // q1.peek();

    return 0;
}