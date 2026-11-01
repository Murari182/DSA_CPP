#include <iostream>
#include <string>
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

    void push(char val)
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
        return top == -1;
    }

    char pop()
    {
        if (isempty())
        {
            return '\0';
        }
        char val = arr[top];
        top--;
        return val;
    }

    char peek()
    {
        if (isempty())
        {
            return '\0';
        }
        return arr[top];
    }

    bool is_operand(char ch)
    {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
        {
            return true;
        }
        return false;
    }

    int prece(char op)
    {
        if (op == '+' || op == '-')
        {
            return 1;
        }
        if (op == '*' || op == '/' || op == '%')
        {
            return 2;
        }
        if (op == '^')
        {
            return 3;
        }
        return 0;
    }

    // Complete Infix to Postfix Conversion (Shunting-Yard Algorithm)
    string infix_to_postfix(string infix)
    {
        string postfix = "";

        for (char ch : infix)
        {
            if (is_operand(ch))
            {
                postfix = postfix + ch;
            }
            else if (ch == '(')
            {
                push(ch);
            }
            else if (ch == ')')
            {
                while (!isempty() && peek() != '(')
                {
                    postfix = postfix + pop();
                }
                if (!isempty())
                {
                    pop(); // Remove '('
                }
            }
            else
            {
                // Operator encountered
                while (!isempty() && peek() != '(' &&
                       (prece(peek()) > prece(ch) || (prece(peek()) == prece(ch) && ch != '^')))
                {
                    postfix = postfix + pop();
                }
                push(ch);
            }
        }

        while (!isempty())
        {
            postfix = postfix + pop();
        }

        return postfix;
    }
};

// Check Balanced Parentheses
bool is_balanced(string expr)
{
    stack s(100);

    for (char ch : expr)
    {
        if (ch == '(' || ch == '{' || ch == '[')
        {
            s.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (s.isempty())
            {
                return false;
            }
            char top_ch = s.pop();
            if ((ch == ')' && top_ch != '(') ||
                (ch == '}' && top_ch != '{') ||
                (ch == ']' && top_ch != '['))
            {
                return false;
            }
        }
    }

    return s.isempty();
}

// Evaluate single-digit Postfix Expression
int evaluate_postfix(string postfix)
{
    int num_stack[100];
    int top = -1;

    for (char ch : postfix)
    {
        if (ch >= '0' && ch <= '9')
        {
            top++;
            num_stack[top] = ch - '0';
        }
        else
        {
            int right = num_stack[top--];
            int left = num_stack[top--];
            int res = 0;

            if (ch == '+')
                res = left + right;
            else if (ch == '-')
                res = left - right;
            else if (ch == '*')
                res = left * right;
            else if (ch == '/')
                res = left / right;

            top++;
            num_stack[top] = res;
        }
    }

    return num_stack[top];
}

int main()
{
    stack st(100);
    string expr = "a+b*(c^d-e)";
    string postfix = st.infix_to_postfix(expr);

    cout << "Infix: " << expr << endl;
    cout << "Postfix: " << postfix << endl;

    string num_postfix = "231*+9-";
    cout << "Evaluate Postfix (231*+9-): " << evaluate_postfix(num_postfix) << endl;

    cout << "Balanced {[()]}: " << is_balanced("{[()]}") << endl;
    cout << "Balanced {[(])}: " << is_balanced("{[(])}") << endl;

    return 0;
}
