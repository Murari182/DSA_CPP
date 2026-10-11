#include <iostream>
using namespace std;

class queue
{
    int arr[100];
    int cap;
    int front;
    int rare;
    int size;

public:
    queue(int cap)
    {
        this->cap = cap;
        front = 0;
        rare = -1;
        size = 0;
    }

    void enqueue(int val)
    {

        if (size == cap)
        {
            cout << "Queue is Full" << endl;
            return;
        }

        rare = (rare + 1) % cap;
        arr[rare] = val;
        size++;
    }

    void peek()
    {

        if (size == 0)
        {
            cout << " Queue is empty" << endl;
            return;
        }

        cout << arr[front] << endl;
    }

    void pop()
    {
        if (size == 0)
        {
            cout << "Queue Underflow" << endl;
            return;
        }

        front = (front + 1) % cap;
        size--;
    }
};

int main()
{

    queue q(5);

    for (int i = 0; i < 5; i++)
    {
        q.enqueue(i * 10);
    }
    q.peek();
    q.pop();
    q.enqueue(60);
    q.peek();

    return 0;
}