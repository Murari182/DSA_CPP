#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Binary_Heap{
public:
    int arr[100];
    int size;

    Binary_Heap(){
        size = 0;
    }

    void heapify_down(int index)
    {
        while(true){

            int largest = index;
            int parent = largest/ 2 - 1;
            int left = 2 * largest + 1;
            int right = 2 * largest + 2;

            if(left < size && arr[left]>arr[largest] ){
                largest = left;
            }

            if(right<size && arr[right]>arr[largest]){
                largest = right;
            }

            if(largest == index){
                break;
            }

            swap(arr[largest], arr[index]);
            index = largest;
        }
    }
 void Insert_Binary_heapfyUP(int value){
    if(size == 100){
        cout << "Tree is Full" << endl;
        return;
    }

    arr[size] = value;
    int i = size;
    size++;

    while(i>0){

        int parent = (i - 1) / 2;
        if(arr[parent]<arr[i]){
            swap(arr[parent], arr[i]);
            i = parent;
        }

        else{
            break;
        }
    }
}

void print_BH(){
    if(size == 0){
        cout << "Trees is empty" << endl;
        return;
    }

    for (int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }

    cout << endl;
}

void delete_node(int index){
    if(size == 0){
        cout << "tree is empty" << endl;
        return;
    }

    if(index<0||index>=size){
        cout << "Invalid Index" << endl;
        return;
    }
    if(index == size-1){
        return;
    }

    swap(arr[index], arr[size - 1]);
    size--;

    while(true){
        int largest = index;
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;


        if(left_child<size && arr[left_child]>arr[largest]){
            largest = left_child;
                }
        if(right_child<size && arr[right_child]>arr[largest]){
            largest = right_child;
        }

        if(largest == index){
            break;
        }

        swap(arr[largest], arr[index]);
        index = largest;
    }
}

void heap_sort(){

    int originalSize = size;

    while (size > 1) {
        swap(arr[0], arr[size - 1]);
        size--;
        heapify_down(0);
    }

    size = originalSize;
}
    
 
};

int main() {

    Binary_Heap b1;
    vector<int> arr{100, 50, 70, 20, 40, 60};
    for (int i = 0; i < arr.size();i++){
        b1.Insert_Binary_heapfyUP(arr[i]);
    }

    cout << "unsorted array: " ;
    b1.print_BH();

    cout << "sorted array: ";
    b1.heap_sort();
    b1.print_BH();

   

    return 0;
}