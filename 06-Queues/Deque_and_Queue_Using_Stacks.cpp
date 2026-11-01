#include <iostream>
#include <stack>
using namespace std;

// Circular Array Deque (Double-Ended Queue)
class Deque
{
    int arr[100];
    int cap;
    int front;
    int rear;
    int size;

public:
    Deque(int cap)
    {
        this->cap = cap;
        front = 0;
        rear = -1;
        size = 0;
    }

    void push_front(int val)
    {
        if (size == cap)
        {
            cout << "Deque is Full" << endl;
            return;
        }

        front = (front - 1 + cap) % cap;
        arr[front] = val;
        if (size == 0)
        {
            rear = front;
        }
        size++;
    }

    void push_back(int val)
    {
        if (size == cap)
        {
            cout << "Deque is Full" << endl;
            return;
        }

        rear = (rear + 1) % cap;
        arr[rear] = val;
        if (size == 0)
        {
            front = rear;
        }
        size++;
    }

    void pop_front()
    {
        if (size == 0)
        {
            cout << "Deque Underflow" << endl;
            return;
        }

        front = (front + 1) % cap;
        size--;
    }

    void pop_back()
    {
        if (size == 0)
        {
            cout << "Deque Underflow" << endl;
            return;
        }

        rear = (rear - 1 + cap) % cap;
        size--;
    }

    int get_front()
    {
        if (size == 0)
        {
            return -1;
        }
        return arr[front];
    }

    int get_rear()
    {
        if (size == 0)
        {
            return -1;
        }
        return arr[rear];
    }
};

// Queue Implemented Using Two Stacks (Amortized O(1))
class QueueUsingStacks
{
    stack<int> s_in;
    stack<int> s_out;

    void transfer_if_needed()
    {
        if (s_out.empty())
        {
            while (!s_in.empty())
            {
                s_out.push(s_in.top());
                s_in.pop();
            }
        }
    }

public:
    void enqueue(int val)
    {
        s_in.push(val);
    }

    void dequeue()
    {
        transfer_if_needed();
        if (s_out.empty())
        {
            cout << "Queue is Empty" << endl;
            return;
        }
        s_out.pop();
    }

    int peek()
    {
        transfer_if_needed();
        if (s_out.empty())
        {
            cout << "Queue is Empty" << endl;
            return -1;
        }
        return s_out.top();
    }
};

int main()
{
    Deque dq(10);
    dq.push_back(10);
    dq.push_back(20);
    dq.push_front(5);

    cout << "Deque Front: " << dq.get_front() << ", Rear: " << dq.get_rear() << endl;
    dq.pop_front();
    cout << "Deque Front after pop_front: " << dq.get_front() << endl;

    QueueUsingStacks qs;
    qs.enqueue(100);
    qs.enqueue(200);
    qs.enqueue(300);
    cout << "QueueUsingStacks Peek: " << qs.peek() << endl;
    qs.dequeue();
    cout << "QueueUsingStacks Peek after dequeue: " << qs.peek() << endl;

    return 0;
}
