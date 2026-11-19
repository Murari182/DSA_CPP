#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <queue>
using namespace std;

class graph
{
    int V;
    vector<list<int>> arr;

public:
    graph(int v)
    {
        V = v;
        arr.resize(V);
    }

    void adj_list(int u, int v)
    {

        arr[u].push_back(v);
        arr[v].push_back(u);
    }

    void display_adj_list()
    {

        cout << "Adjacency List: "<<endl;
        for (int i = 0; i < V; i++)
        {

            cout << i << " --> ";
            for (int nigh : arr[i])
            {
                cout << nigh << " ";
            }

            cout << endl;
        }
    }

    void BFS()
    {

        vector<bool> vis(V, 0);
        queue<int> q;

        q.push(0);
        vis[0] = true;

        cout<<"BFS Traversal: ";
        while (q.size())
        {
            int u = q.front();
            q.pop();
            cout << u << " ";
            for (int v : arr[u])
            {

                if (!vis[v])
                {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }

        cout<<endl;
    }

    void DFS_helper(int u, vector<bool> &vis){

        cout<<u<<" ";
        vis[u] = true;

        for(int v : arr[u]){
            if(!vis[v]){
                DFS_helper(v,vis);

            }
        }
        
    }

    void DFS(){

        cout<<"DFS Traversal: ";
    int src = 0;
    vector<bool> status(V,false);
    DFS_helper(src, status);

    cout<<endl;
}

    
};



int main()
{
    graph g(5);

    g.adj_list(0, 1);
    g.adj_list(1, 2);
    g.adj_list(2, 4);
    g.adj_list(1, 3);
    
    g.display_adj_list();

    g.BFS();
  
    g.DFS();
  

    return 0;
}