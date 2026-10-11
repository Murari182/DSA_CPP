#include<iostream>
using namespace std;

int print(int n){

    cout << n << endl;
    if(n==1){
        return 1;
    }

    return print(n - 1);
}

int main(){

    print(1000);

    return 0;
}