#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class stack
{

    char arr[100];
    int cap;
    int top;

public:
    stack(int cap)
    {
        this->cap = cap;
        top = -1;
    }

    void push(int val)
    {
        if (top == cap - 1)
        {
            cout << "Stack is Full" << endl;
            return;
        }

        top++;
        arr[top] = val;
    }

    bool isempty()
    {

        if (top == -1)
        {
            return true;
        }

        return false;
    }

    char pop()
    {

        if (isempty())
        {
            cout << "Stack UnderFlow" << endl;
            return '\0';
        }

        char val = arr[top];
        top--;
        return val;
    }

    char peek()
    {

        if (top == -1)
        {
            cout << "Stack is Empty" << endl;
            return '\0';
        }

        char val = arr[top];
        return val;
    }

    bool isoperator(char ch)
    {

        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'b') || (ch >= '0' && ch <= '9'))
        {
            return true;
        }

        return false;
    }

    int prece(char op){

        if(op =='+'||op=='-'){
            return 1;
        }

        if(op =='*'||op=='/'||op=='%'){
            return 2;
        }

        if(op =='^'){
            return 3;
        }

        return 0;
    }

    string infix_postfix(string infinix){

        string postfix = "";

        for (char ch : infinix){

            if(isoperator(ch)){
                postfix = postfix + ch;
            }

           else if(ch == '('){
               push(ch);
            }

            else if(ch == ')'){
                while(!isempty()&& peek() != '('){
                postfix = postfix + pop();
                }
                if(!isempty()){
                    pop();
                }
            }
        }

        }
    
};