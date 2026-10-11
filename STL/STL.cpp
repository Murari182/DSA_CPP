#include<iostream>
#include<list>
#include<iterator>
#include<algorithm>
using namespace std;

int main(){

    list<int> l;
    l.push_front(10);
    for (int i = 2; i < 11;i++){
        l.push_back(i * 10);
    }

    for(int x : l){
        cout << x << " ";
    }
    cout << endl;

    auto it = l.begin();

 auto key =  find(l.begin(), l.end(), 300);


 return 0;
}