
#include <iostream>
#include <vector>
using namespace std;

class hashtable
{
private:
    vector<int> arr;
    vector<int> status; // 0 = EMPTY, 1 = OCCUPIED, 2 = DELETED

    int cap;
    int size;

public:
    // Constructor
    hashtable(int cap)
    {
        this->cap = cap;
        size = 0;
        arr.resize(cap);
        status.resize(cap, 0);
    }

    // Hash function
    int hashFunction(int key)
    {
        int index = key % cap;
        return index;
    }

    // Insert element using Linear Probing
    void insert(int key)
    {
        int oindex = hashFunction(key);

        for (int i = 0; i < cap; i++)
        {
            int index = (oindex + i) % cap;
            if (status[index] == 0)
            {
                arr[index] = key;
                status[index] = 1;
                size++;
                cout << "element inserted" << endl;

                return;
            }

            else if (status[index] == 1 && arr[index] == key)
            {
                cout << "duplicate key" << endl;
                return;
            }
        }

        cout << "hash table is full" << endl;
    }

    // Search an element
    int search(int key)
    {
        int oindex = hashFunction(key);

        for (int i = 0; i < cap; i++)
        {
            int index = (oindex + i) % cap;

            if (arr[index] == key && status[index] == 1)
            {
                return index;
            }
        }

        return -1;
    }

    // Delete an element
    void remove(int key){

        int oindex = hashFunction(key);
        for(int i=0; i<cap; i++){
            int index = (oindex + i)%cap;

            if(status[index] == 0){
                cout<<"Key does not exist"<<endl;
                return;
            }
            if(arr[index] == key && status[index] == 1){
                arr[index] = 0;
                status[index] = 2;
                size--;
                return;
            }

        }
    }

   
};

int main()
{
    hashtable h(7);
    h.insert(10);
    h.insert(17);
    h.insert(24);

    cout << h.search(10) << endl; // 3
    cout << h.search(17) << endl; // 4
    cout << h.search(24) << endl; // 5
   // cout << h.search(50) << endl; // -1

    h.remove(17);
    cout<<h.search(17)<<endl;

    return 0;
}
