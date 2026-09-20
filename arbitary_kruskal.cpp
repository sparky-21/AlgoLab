#include<bits/stdc++.h>
using namespace std;

int parent[100];
set<int> arb;

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
    {
        parent[b] = a;
    }
}

void generate(vector<tuple<int,int,int>>& g, int pos,
              int cnt, int V, int E, int total)
{
    // V-1 edges selected
    if(cnt == V-1)
    {
        arb.insert(total);
        return;
    }

    // Not enough edges remaining
    if(E - pos < V - 1 - cnt)
        return;

    for(int i = pos; i < E; i++)
    {
        auto [w,u,v] = g[i];

        int a = find(u);
        int b = find(v);

        // If adding this edge creates a cycle, skip it
        if(a == b)
            continue;

        // Save current DSU state
        vector<int> temp(V);

        for(int j = 0; j < V; j++)
            temp[j] = parent[j];

        unite(u,v);

        generate(g, i + 1, cnt + 1, V, E, total + w);

        // Restore DSU state
        for(int j = 0; j < V; j++)
            parent[j] = temp[j];
    }
}

int main()
{
    int V,E;
    cin >> V >> E;

    vector<tuple<int,int,int>> g;

    for(int i=0; i<E; i++)
    {
        int u,v,w;
        cin >> u >> v >> w;

        g.push_back({w,u,v});
    }

    // Initially every vertex is its own parent
    for(int i=0; i<V; i++)
    {
        parent[i] = i;
    }

    generate(g, 0, 0, V, E, 0);

    for(int wei : arb)
    {
        cout << wei << " ";
    }

    cout << endl;
}
/*4 5
0 1 2
1 3 4
0 3 6
0 2 5
2 3 1*/

