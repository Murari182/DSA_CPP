#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Binaray_Heap{
public:
    int arr[1000];
    int size;
    Binaray_Heap(){
        size = 0;
    }

    void heapify_down(int index){

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

    void Build_Binary_heap(vector<int> heap){
        if(size == 1000){
            cout << "Tree is Full" << endl;
            return;
        }
        while(size < heap.size()){
        this->arr[size] = heap[size];
        size++;
        }
    }

    void Insert_BH(int value){

        if(size == 1000){
            cout << "Tree is Full" << endl;
            return;
        }

        arr[size] = value;
        int i = size;
        size++;
        while(i>0){
            int parent = (i - 1) / 2;

            if(arr[parent] < arr[i]){
                swap(arr[parent], arr[i]);
                i = parent;
            }

            else{
                break;
            }
        }
    }

    void print(){

        for (int i = 0; i < size; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }

   void delete_node(int index){
    if(size == 0){
        cout << "Tree is Empty" << endl;
        return;
    }

    if(index>=size || index<0){
        cout << "Invalid Index" << endl;
    }

    swap(arr[index], arr[size - 1]);
    size--;

    
   }

  void heap_sort(){
    while(size > 0){
        swap(arr[0], arr[size - 1]);
        size--;
        heapify_down(0);
    }
      
  }
};

int main() {

    vector<int> heap = {100, 50, 70, 20, 40, 60};
    Binaray_Heap t1;

    for (int i = 0; i < heap.size();i++){
        t1.Insert_BH(heap[i]);
    }

    cout << "unsorted array: " ;
    t1.print();

    cout << "sorted array: ";
    t1.heap_sort();
    t1.print();

    return 0;

   
}