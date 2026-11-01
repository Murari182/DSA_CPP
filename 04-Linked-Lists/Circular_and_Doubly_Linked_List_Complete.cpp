#include <iostream>
using namespace std;

// ============================================================
// PART 1: COMPLETE DOUBLY LINKED LIST
// ============================================================

class DNode
{
    int data;
    DNode *next;
    DNode *prev;

public:
    DNode(int data)
    {
        this->data = data;
        next = NULL;
        prev = NULL;
    }

    friend class DoublyList;
};

class DoublyList
{
    DNode *head;
    DNode *tail;

public:
    DoublyList()
    {
        head = NULL;
        tail = NULL;
    }

    void push_front(int val)
    {
        DNode *n1 = new DNode(val);

        if (head == NULL)
        {
            head = n1;
            tail = n1;
        }
        else
        {
            n1->next = head;
            head->prev = n1;
            head = n1;
        }
    }

    void push_back(int val)
    {
        DNode *n1 = new DNode(val);

        if (head == NULL)
        {
            head = n1;
            tail = n1;
        }
        else
        {
            tail->next = n1;
            n1->prev = tail;
            tail = n1;
        }
    }

    void insert(int val, int pos)
    {
        if (pos == 0)
        {
            push_front(val);
            return;
        }

        DNode *temp = head;
        for (int i = 0; i < pos - 1 && temp != NULL; i++)
        {
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Invalid position" << endl;
            return;
        }

        if (temp->next == NULL)
        {
            push_back(val);
            return;
        }

        DNode *n1 = new DNode(val);
        n1->next = temp->next;
        n1->prev = temp;
        temp->next->prev = n1;
        temp->next = n1;
    }

    void pop_front()
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }

        DNode *temp = head;

        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            head = head->next;
            head->prev = NULL;
        }

        delete temp;
    }

    void pop_back()
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }

        DNode *temp = tail;

        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            tail = tail->prev;
            tail->next = NULL;
        }

        delete temp;
    }

    void print()
    {
        DNode *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

// ============================================================
// PART 2: COMPLETE CIRCULAR LINKED LIST
// ============================================================

class CNode
{
    int data;
    CNode *next;

public:
    CNode(int data)
    {
        this->data = data;
        next = NULL;
    }

    friend class CircularList;
};

class CircularList
{
    CNode *head;
    CNode *tail;

public:
    CircularList()
    {
        head = NULL;
        tail = NULL;
    }

    void push_front(int val)
    {
        CNode *n1 = new CNode(val);

        if (head == NULL)
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

    void push_back(int val)
    {
        CNode *n1 = new CNode(val);

        if (head == NULL)
        {
            head = n1;
            tail = n1;
            tail->next = head;
        }
        else
        {
            tail->next = n1;
            tail = n1;
            tail->next = head;
        }
    }

    void pop_front()
    {
        if (head == NULL)
        {
            cout << "Circular List is empty" << endl;
            return;
        }

        if (head == tail)
        {
            delete head;
            head = NULL;
            tail = NULL;
            return;
        }

        CNode *temp = head;
        head = head->next;
        tail->next = head;
        delete temp;
    }

    void print()
    {
        if (head == NULL)
        {
            cout << "Circular List is empty" << endl;
            return;
        }

        CNode *temp = head;
        do
        {
            cout << temp->data << " --> ";
            temp = temp->next;
        } while (temp != head);

        cout << "(back to head: " << head->data << ")" << endl;
    }
};

int main()
{
    DoublyList dl;
    dl.push_back(10);
    dl.push_back(20);
    dl.push_back(40);
    dl.insert(30, 2);
    cout << "Doubly Linked List: ";
    dl.print();

    dl.pop_front();
    dl.pop_back();
    cout << "After pop_front and pop_back: ";
    dl.print();

    CircularList cl;
    cl.push_back(100);
    cl.push_back(200);
    cl.push_back(300);
    cl.push_front(50);
    cout << "Circular Linked List: ";
    cl.print();

    cl.pop_front();
    cout << "After pop_front: ";
    cl.print();

    return 0;
}
