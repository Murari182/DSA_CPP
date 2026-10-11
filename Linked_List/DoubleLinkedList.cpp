#include <iostream>
using namespace std;

class Node
{
    int data;
    Node *next;
    Node *prev;

public:
    Node(int data)
    {
        this->data = data;
        next = NULL;
        prev = NULL;
    }
    friend class D_List;
};

class D_List
{

    Node *head;
    Node *tail;

public:
    D_List()
    {
        head = NULL;
        tail = NULL;
    }

    void push_front(int val)
    {

        Node *n1 = new Node(val);

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

    void print()
    {

        Node *temp = head;

        while (temp != NULL)
        {

            cout << temp->data << " <-> ";
            temp = temp->next;
        }

        cout << "NULL" << endl;
    }

    void push_back(int val)
    {
        Node *n1 = new Node(val);

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

        Node *n1 = new Node(val);
        Node *temp = head;

        if (pos == 0)
        {
            push_front(val);
            return;
        }

        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
        }

        n1->next = temp->next;
        n1->prev = temp;
        // temp = temp->next;
        // temp->prev = n1;
        (temp->next)->prev = n1;
        temp->next = n1;
    }

    void delete_last(int n){
        Node *prev;
        Node *curr;
    }

    void del_last(int pos){
        Node *prev = head;
        Node *curr = head;
        Node *temp = head;
        int count = 0;

        while(temp != NULL){
            
            count++;
            temp = temp->next;
        }
        cout << count << endl;

        int front = count - pos - 1;
        for (int i = 0; i < count - (pos + 1) - 1; i++){

            prev = prev->next;

        }
        prev->next = prev->next->next;

        for (int i = 0; i < count - pos - 1; i++){

            curr = curr->next;
        }
        curr->next = NULL;
        delete curr;
    }
};

int main()
{

    D_List dl;

    

    return 0;
}
