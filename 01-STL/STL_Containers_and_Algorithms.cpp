#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
    // 1. std::vector (Dynamic Array)
    vector<int> v = {40, 10, 50, 20, 30};
    v.push_back(60);

    sort(v.begin(), v.end());

    cout << "Sorted vector: ";
    for (int x : v)
    {
        cout << x << " ";
    }
    cout << endl;

    // 2. std::list and std::find with iterator verification
    list<int> l;
    l.push_front(10);
    for (int i = 2; i < 6; i++)
    {
        l.push_back(i * 10);
    }

    auto key_found = find(l.begin(), l.end(), 30);
    if (key_found != l.end())
    {
        cout << "Found in list: " << *key_found << endl;
    }

    auto key_missing = find(l.begin(), l.end(), 300);
    if (key_missing == l.end())
    {
        cout << "300 not found in list" << endl;
    }

    // 3. std::stack (LIFO)
    stack<int> st;
    st.push(10);
    st.push(20);
    st.push(30);
    cout << "Stack top: " << st.top() << endl;
    st.pop();
    cout << "Stack top after pop: " << st.top() << endl;

    // 4. std::queue (FIFO)
    queue<int> q;
    q.push(100);
    q.push(200);
    q.push(300);
    cout << "Queue front: " << q.front() << endl;
    q.pop();
    cout << "Queue front after pop: " << q.front() << endl;

    return 0;
}
