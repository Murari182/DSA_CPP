/*
Topic: Linked Lists
Concept: Build and print singly linked list.
Time Complexity: O(n)
Space Complexity: O(n)
Example Input:
4
10 20 30 40
Example Output:
10 20 30 40
Practice Problems:
1) Insert at head/tail
2) Delete by value
3) Reverse linked list
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

int main() {
    int n;
    cin >> n;

    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        Node* node = new Node(x);
        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        cout << cur->data << (cur->next ? ' ' : '\n');
    }

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
