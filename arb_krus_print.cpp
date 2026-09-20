#include <bits/stdc++.h>
using namespace std;

int parent[100];

int find(int x)
{
    if(parent[x] == x)
        return x;

    return parent[x] = find(parent[x]);
}

void unite(int x, int y)
{
    int a = find(x);
    int b = find(y);

    if(a != b)
        parent[b] = a;
}


bool generate(vector<tuple<int,int,int>>& g,
              int pos, int cnt, int V, int E,
              int total, int target,
              vector<tuple<int,int,int>>& selected)
{
    // Required number of edges selected
    if(cnt == V - 1)
    {
        if(total == target)
        {
            cout << "Spanning Tree Found:\n";

            for(auto [w,u,v] : selected)
            {
                cout << u << " " << v
                     << " " << w << endl;
            }

            cout << "Total Weight = " << total << endl;

            return true;
        }

        return false;
    }

    for(int i = pos; i < E; i++)
    {
        auto [w,u,v] = g[i];

        // Cycle check
        if(find(u) == find(v))
            continue;

        // Save DSU
        vector<int> temp(V);

        for(int j = 0; j < V; j++)
            temp[j] = parent[j];

        // Select edge
        unite(u,v);
        selected.push_back({w,u,v});

        // Explore this branch
        bool found = generate(g, i + 1, cnt + 1,
                              V, E, total + w,
                              target, selected);

        // Backtrack
        selected.pop_back();

        for(int j = 0; j < V; j++)
            parent[j] = temp[j];

        // If tree already found, stop searching
        if(found)
            return true;
    }

    return false;
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<tuple<int,int,int>> g;

    for(int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        g.push_back({w,u,v});
    }

    int target;
    cin >> target;

    for(int i = 0; i < V; i++)
        parent[i] = i;

    vector<tuple<int,int,int>> selected;

    bool found = generate(g, 0, 0, V, E,
                          0, target, selected);

    if(!found)
        cout << "Tree not found\n";
}
