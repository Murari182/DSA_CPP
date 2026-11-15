
#include <iostream>
using namespace std;

/*
    ==========================================
        SEPARATE CHAINING USING LINKED LIST
    ==========================================

    THEORY:

    A Hash Table is a data structure used to store
    and retrieve elements efficiently.

    A Hash Function converts a given key into an
    index of an array.

    Example:

        key = 12
        index = key % 10
        index = 12 % 10 = 2

    So, key 12 will be stored at arr[2].

    PROBLEM: COLLISION

    A collision occurs when two or more keys produce
    the same hash index.

    Example:

        12 % 10 = 2
        22 % 10 = 2
        32 % 10 = 2
        42 % 10 = 2

    All four keys map to index 2.

    We cannot simply overwrite the previous value.

    SOLUTION: SEPARATE CHAINING

    In Separate Chaining, every array index acts
    as the HEAD of a linked list.

    Instead of storing only one element at an index,
    we store the address of the first node.

    If multiple keys produce the same index,
    we connect them using linked-list pointers.

    Example:

        arr[2] -> 42 -> 32 -> 22 -> 12 -> NULL

    IMPORTANT:

    arr[2] does not store the actual data 42.

    arr[2] stores the ADDRESS of the first node.

    That first node is called the HEAD of the chain.

    The head is not a separate node.
    It is simply a pointer that points to the first node.
*/


// NODE CLASS

class Node
{
private:

    int data;

    // Stores the address of the next node.
    // If there is no next node, it contains NULL.

    Node* next;

    /*
        FRIEND CLASS:

        The members data and next are private.

        Normally, another class cannot directly
        access private members.

        By declaring hashtable as a friend class,
        we allow hashtable to access data and next.

        This is required because our hash table
        needs to traverse and connect linked-list nodes.
    */

    friend class hashtable;

public:

    // CONSTRUCTOR

    Node(int data)
    {
        this->data = data;

        /*
            Initially, a newly created node does not
            point to any other node.

            Therefore, next is initialized to NULL.

            Later, we connect this node to another node
            during insertion.
        */

        next = NULL;
    }
};


// HASH TABLE CLASS

class hashtable
{
private:

    /*
        ARRAY OF NODE POINTERS

        arr[100] creates an array containing 100 pointers.

        Each array element can store the address of
        the first node of a linked list.

        Example:

            arr[0] -> HEAD of chain 0
            arr[1] -> HEAD of chain 1
            arr[2] -> HEAD of chain 2
            ...
            arr[99] -> HEAD of chain 99

        Initially, all pointers are NULL because
        no linked-list nodes have been inserted.

        IMPORTANT:

        arr[index] is itself the HEAD POINTER.

        We do not need another separate head variable
        for every linked list.
    */

    Node* arr[100];


public:

    // CONSTRUCTOR

    hashtable()
    {
        /*
            Initially, every bucket is empty.

            Setting every pointer to NULL means
            that no linked list exists at that index.

            If arr[2] == NULL:

                There is no node at bucket 2.
        */

        for (int i = 0; i < 100; i++)
        {
            arr[i] = NULL;
        }
    }


    // INSERTION OPERATION

    void Insert_key(int key)
    {
        /*
            STEP 1: HASH FUNCTION

            The hash function calculates the bucket index.

            We are using:

                index = key % 10

            Keys having the same remainder
            will belong to the same bucket.

            Example:

                12 % 10 = 2
                22 % 10 = 2
                32 % 10 = 2
        */

        int index = key % 10;


        /*
            STEP 2: CREATE A NEW NODE

            'new' dynamically allocates memory
            for a Node in the heap.

            n1 stores the address of that newly
            created node.

            Example:

                Node* n1 = new Node(12);

            Memory representation:

                n1
                |
                v
              +------+------+
              |  12  | NULL |
              +------+------+

            At this stage, the node is not yet
            connected to the hash table.
        */

        Node* n1 = new Node(key);


        /*
            STEP 3: CONNECT NEW NODE TO OLD HEAD

            This is the most important operation.

                n1->next = arr[index];

            arr[index] contains the address of
            the current first node.

            We assign that address to n1->next.

            WHY?

            Because we want the new node to point
            to the existing linked list.

            Suppose initially:

                arr[2] -> 12 -> NULL

            Now we insert 22.

            Before connection:

                arr[2] -> 12 -> NULL

                n1 -> 22 -> NULL

            After:

                n1->next = arr[2];

                n1 -> 22 -> 12 -> NULL

            Notice that the old head is not lost.

            We first connect the new node to the
            existing chain.
        */

        n1->next = arr[index];


        /*
            STEP 4: UPDATE THE HEAD POINTER

                arr[index] = n1;

            Now the array bucket points to the
            newly inserted node.

            WHY?

            Because n1 is now the first node
            of the linked list.

            The new node becomes the HEAD.

            Before:

                arr[2] -> 12 -> NULL

            After inserting 22:

                arr[2] -> 22 -> 12 -> NULL

            IMPORTANT:

            We update arr[index] only AFTER
            connecting n1 to the old head.

            If we update the head first, we may
            lose the address of the existing chain.

            This is called INSERTION AT HEAD.

            Time Complexity: O(1)
        */

        arr[index] = n1;
    }


    // SEARCH OPERATION

    bool search(int key)
    {
        /*
            STEP 1: CALCULATE THE BUCKET INDEX

            We use the same hash function that
            was used during insertion.

            Otherwise, we would search in the
            wrong linked list.
        */

        int index = key % 10;


        /*
            STEP 2: START FROM THE HEAD

            arr[index] contains the address of
            the first node.

            temp is a temporary pointer.

            We use temp because we do not want
            to modify the actual head pointer.

            If we directly move arr[index],
            we would lose the starting address
            of our linked list.
        */

        Node* temp = arr[index];


        /*
            STEP 3: TRAVERSE THE LINKED LIST

            Continue until temp becomes NULL.

            NULL means that we have reached
            the end of the linked list.

            At every node, compare its data
            with the key we are searching for.
        */

        while (temp != NULL)
        {
            /*
                If the current node contains
                the required key, return true.
            */

            if (temp->data == key)
            {
                return true;
            }


            /*
                MOVE TO THE NEXT NODE

                temp = temp->next;

                This changes temp to store the
                address of the next node.

                We continue checking every node
                in the chain.
            */

            temp = temp->next;
        }


        /*
            If the loop finishes, the key was
            not present in the linked list.

            Therefore, return false.
        */

        return false;
    }


    // PRINT A PARTICULAR HASH BUCKET

    void print_hash(int index)
    {
        /*
            VALID INDEX RANGE:

            Our array has 100 elements.

            Valid indices:

                0 to 99

            Index 100 is invalid because array
            indexing starts from 0.
        */

        if (index < 0 || index >= 100)
        {
            cout << "Invalid Index" << endl;
            return;
        }


        /*
            START FROM THE HEAD OF THE BUCKET.

            temp gets the address stored in arr[index].

            We use a temporary pointer so that
            the actual head remains unchanged.
        */

        Node* temp = arr[index];


        /*
            CHECK WHETHER THE BUCKET IS EMPTY.

            If temp is NULL, there are no nodes
            in this linked list.
        */

        if (temp == NULL)
        {
            cout << "hash_function is empty" << endl;
            return;
        }


        /*
            TRAVERSE AND PRINT ALL NODES.

            Print the current node's data.

            Then move temp to the next node.

            Stop when temp becomes NULL.
        */

        while (temp != NULL)
        {
            cout << temp->data << " ";

            temp = temp->next;
        }

        cout << endl;
    }
};


int main()
{
    hashtable h1;


    /*
        INSERTING KEYS

        All these keys produce index 2.

            12 % 10 = 2
            22 % 10 = 2
            32 % 10 = 2
            42 % 10 = 2

        Since we insert at HEAD, the final chain is:

            arr[2] -> 42 -> 32 -> 22 -> 12 -> NULL
    */

    h1.Insert_key(12);
    h1.Insert_key(22);
    h1.Insert_key(32);
    h1.Insert_key(42);


    // SEARCH TESTING

    cout << h1.search(32) << endl;  // 1 (Found)

    cout << h1.search(55) << endl;  // 0 (Not Found)


    // PRINT THE LINKED LIST AT BUCKET 2

    h1.print_hash(2);

    return 0;
}
