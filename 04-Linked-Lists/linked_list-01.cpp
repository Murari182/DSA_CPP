#include <iostream>
using namespace std;

class Node
{
    int data;
    Node* next;

public:
    Node(int data)
    {
        this->data = data;
        next = NULL;
    }

    friend class list;
};

class list
{
    Node* head;
    Node* tail;

public:

    // Constructor
    list()
    {
        head = NULL;
        tail = NULL;
    }

    // Insert at beginning
    void push_front(int val)
    {
        Node* n1 = new Node(val);

        if(head == NULL)
        {
            head = n1;
            tail = n1;
        }
        else
        {
            n1->next = head;
            head = n1;
        }
    }

    // Insert at end
    void pushb_back(int val)
    {
        Node* n1 = new Node(val);

        if(head == NULL)
        {
            head = n1;
            tail = n1;
        }
        else
        {
            tail->next = n1;
            tail = n1;
        }
    }

    // Print normal linked list
    void print()
    {
        Node* temp = head;

        while(temp != NULL)
        {
            cout << temp->data << "-->";
            temp = temp->next;
        }

        cout << "NULL" << endl;
    }

    // Insert at a given position
    void insert(int val, int pos)
    {
        if(pos == 0)
        {
            push_front(val);
            return;
        }

        Node* n1 = new Node(val);
        Node* temp = head;

        for(int i = 0; i < pos - 1 && temp != NULL; i++)
        {
            temp = temp->next;
        }

        if(temp == NULL)
        {
            cout << "Invalid position" << endl;
            delete n1;
            return;
        }

        n1->next = temp->next;
        temp->next = n1;

        if(n1->next == NULL)
        {
            tail = n1;
        }
    }

    // Delete all nodes
    void delete_all()
    {
        Node* temp = head;

        while(head != NULL)
        {
            head = head->next;
            delete temp;
            temp = head;
        }

        tail = NULL;
    }

    // Delete node from position from the end
    void del_last(int pos)
    {
        if(head == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }

        // Count number of nodes
        int count = 0;
        Node* temp = head;

        while(temp != NULL)
        {
            count++;
            temp = temp->next;
        }

        // Check position
        if(pos < 0 || pos >= count)
        {
            cout << "Invalid position" << endl;
            return;
        }

        // If deleting head
        if(pos == count - 1)
        {
            Node* temp = head;
            head = head->next;
            delete temp;

            if(head == NULL)
                tail = NULL;

            return;
        }

        // Find node before the node to delete
        Node* prev = head;

        for(int i = 0; i < count - pos - 2; i++)
        {
            prev = prev->next;
        }

        Node* curr = prev->next;

        prev->next = curr->next;

        if(curr == tail)
        {
            tail = prev;
        }

        delete curr;
    }

    // Floyd's Cycle Detection Algorithm
    bool Dect_cycle()
    {
        Node* slow = head;
        Node* fast = head;

        while(fast != NULL && fast->next != NULL)
        {
            // Slow moves one step
            slow = slow->next;

            // Fast moves two steps
            fast = fast->next->next;

            // If they meet, cycle exists
            if(slow == fast)
            {
                cout << slow->data << " = " << fast->data << endl;
                return true;
            }
        }

        // Fast reached NULL
        return false;
    }

    // Create a cycle
    void make_cycle()
    {
        if(head == NULL)
        {
            return;
        }

        Node* temp = head;

        // Move to last node
        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        // Last node points back to head
        temp->next = head;
    }

    void cos_cycle(int val){
        Node *temp = head;
        Node *req = head;

        while(temp->next != NULL){
            
            temp = temp->next;
        }

        while(req != NULL){

            if(req->data == val){
                temp->next = req;
                return;
            }
            req = req->next;
            
        }

        cout << "The Value Does Not Contain in Linked List" << endl;
    }

    void reverse(){

        Node *curr = head;
        Node *next;
        Node *prev = NULL;

        while(curr != NULL){

            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head = prev;
    }
};

int main()
{
    list lq;

    // Create linked list
    lq.push_front(10);

    for(int i = 2; i < 11; i++)
    {
        lq.pushb_back(i * 10);
    }

    lq.print();
    lq.reverse();
    lq.print();

    // Normal linked list
    // cout << "Original Linked List:" << endl;
    // lq.print();

    // Create cycle
   // lq.make_cycle();

   // cout << "\nCycle created." << endl;

    // Detect cycle using Floyd's Algorithm
    // cout << "Cycle detected: ";

    // if(lq.Dect_cycle())
    // {
    //     cout << "YES" << endl;
    // }
    // else
    // {
    //     cout << "NO" << endl;
    // }
   // lq.cos_cycle(50);

   // Detect cycle using Floyd's Algorithm
    // cout << "Cycle detected: ";

    // if(lq.Dect_cycle())
    // {
    //     cout << "YES" << endl;
    // }
    // else
    // {
    //     cout << "NO" << endl;
    // }

    return 0;
}