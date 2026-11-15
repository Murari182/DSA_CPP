
#include <iostream>
using namespace std;

class Node
{
private:
    int data;
    Node* next;

    friend class hashtable;

public:
    Node(int data)
    {
        this->data = data;
        next = NULL;
    }
};

class hashtable
{
private:
    Node* arr[100];

public:
    hashtable()
    {
        for (int i = 0; i < 100; i++)
        {
            arr[i] = NULL;
        }
    }

    void Insert_key(int key)
    {
        int index = key % 10;

        Node* n1 = new Node(key);

        n1->next = arr[index];
        arr[index] = n1;
    }

    bool search(int key)
    {
        int index = key % 10;

        Node* temp = arr[index];

        while (temp != NULL)
        {
            if (temp->data == key)
            {
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

    void print_hash(int index){

        if(index<0 || index>100){
            cout<<"Invaild Index"<<endl;
            return;
        }
        
        Node* temp = arr[index];
        if(temp == NULL){
            cout<<"hash_function is empty"<<endl;
            return;
        }
        while(temp != NULL){
            cout<<temp->data<<" ";
            temp = temp->next;
        }

        cout<<endl;
    }
};

int main()
{
    hashtable h1;

    h1.Insert_key(12);
    h1.Insert_key(22);
    h1.Insert_key(32);
    h1.Insert_key(42);

    cout << h1.search(32) << endl;
    cout << h1.search(55) << endl;

   


    return 0;
}
