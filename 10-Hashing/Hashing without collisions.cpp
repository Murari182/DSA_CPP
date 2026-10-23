#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class hash_table{
    int arr[10];
    public:

        void hash_function(int value){
            int h;

            h = value % 10;
            arr[h] = value;
        }

        void search(int key){

            int h = key % 10;

            if(key == arr[h]){
                cout << h << endl;
                return;
            }

            else{
                cout << "Invalid key" << endl;
                return;
            }
            
        }
        
};

int main() {

    hash_table h1;
    h1.hash_function(20);
    h1.hash_function(23);
    h1.search(20);

    return 0;
}