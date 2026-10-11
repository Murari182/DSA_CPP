#include <iostream>
using namespace std;

class Node
{

    int data;
    Node *next;

public:
    Node(int data)
    {
        this->data = data;
        next = nullptr;
    }
    friend class list;
};

class list
{

    Node *head;
    Node *tail;

public:
    list()
    {

        head = nullptr;
        tail = nullptr;
    }

    void push_front(int val)
    {
        Node *n1 = new Node(val);

        if (head == nullptr)
        {
            head = n1;
            tail = n1;
            tail->next = head;
        }

        else
        {

            n1->next = head;
            head = n1;
            tail->next = head;
        }
    }

    void print()
    {
        Node *temp = head;

        // cout << temp->data << " --> ";

        do
        {
            cout << temp->data << " --> ";
            temp = temp->next;
        } while (temp != head);
        cout << temp->next << " --> " << temp->data
             << endl;
    }
};

int main()
{

    list cll;
    // cll.push_front(10);
    for (int i = 1; i < 11; i++)
    {
        cll.push_front(i * 10);
    }
    cll.print();

    return 0;
}
