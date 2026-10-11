#include<iostream>
using namespace std;

class stack{

    int arr[100];
    int cap;
    int top;

    public:
        
        stack(int cap){
            this->cap = cap;
            top = -1;
            
        }

        void push(int val){

            if(top == cap - 1){
                cout << "StackOverFlow" << endl;
                return;
            }

            top++;
            arr[top] = val;
        }

        void pop(){

            if(top == -1){
                cout << "The Stack is Empty" << endl;
                return;
            }
            top--;
        }

        void peek(){
            
            if(top == -1){
                cout << "The Stack is empty" << endl;
                return;
            }
            
                cout << arr[top] << endl;
            
        }

        void empty(){

            if(top == -1){
                cout << "The Stack is Empty" << endl;
                return;
            }

            cout << "The Stack is Not Empty" << endl;
        }

    void Display(){

        if(top == -1){
            return;
        }

        for (int i = top; i >= 0; i--){
            cout << arr[i] << " ";
        }

        cout << endl;
    }

    void size(){
        cout << "Size of stack: " << top + 1 << endl;
    }
};

int main(){

    stack s(20);

    s.empty();
    s.push(10);

    for (int i = 2; i < 11; i++){
        s.push(i * 10);
    }

    s.empty();

    s.peek();
    s.Display();
    s.pop();
    s.Display();
    s.size();

    return 0;
}