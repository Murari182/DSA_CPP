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

        friend class stack;
};

class stack{

    Node *top;

    public:
        stack(){
            top = NULL;
        }

    void push(int val){
        Node *n1 = new Node(val);

        if(top == NULL){
            top = n1;
            return;
        }

        n1->next = top;
        top = n1;
    }

    void peek(){
        if(top == NULL){
            cout << "The Stack is Empty" << endl;
            return;
        }

        cout << top->data << endl;
    }

    void pop(){
        if(top == NULL){
            cout << "The Stack is Empty" << endl;
            return;
        }

        Node *temp = top;
        top = top->next;
        delete temp;
    }
};

int main(){

    stack s1;
    s1.push(10);
    s1.peek();
    s1.push(20);
    s1.push(30);
    s1.peek();
    s1.push(40);
    s1.push(50);
    s1.push(60);
    s1.push(70);
    s1.push(80);
    s1.peek();

    cout << "Lets check pop" << endl;
    s1.pop();
    cout << "Lets check result" << endl;
    s1.peek();

    return 0;
}