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
set<int>arb;
vector<tuple<int,int,int>> bestTree;

int minCost = INT_MAX;
int maxCost = INT_MIN;

void findAll(vector<tuple<int,int,int>>& g,
             int pos, int cnt, int V, int E,
             int total)
{
    if(cnt == V - 1)
    {
        arb.insert(total);
        minCost = min(minCost, total);
        maxCost = max(maxCost, total);

        return;
    }

    for(int i = pos; i < E; i++)
    {
        int w, u, v;
        tie(w, u, v) = g[i];

        if(find(u) == find(v))
            continue;

        vector<int> temp(V);

        for(int j = 0; j < V; j++)
            temp[j] = parent[j];

        unite(u, v);
        findAll(g, i + 1, cnt + 1,
                V, E, total + w);

        for(int j = 0; j < V; j++)
            parent[j] = temp[j];
    }
}


void findAverageTree(vector<tuple<int,int,int>>& g,
                     int pos, int cnt, int V, int E,
                     int total,
                     double target,
                     vector<tuple<int,int,int>>& selected,
                     double& bestDiff)
{
    if(cnt == V - 1)
    {
        double diff = abs(total - target);

        if(diff < bestDiff)
        {
            bestDiff = diff;
            bestTree = selected;
        }

        return;
    }

    for(int i = pos; i < E; i++)
    {
        int w, u, v;
        tie(w, u, v) = g[i];

        if(find(u) == find(v))
            continue;

        vector<int> temp(V);

        for(int j = 0; j < V; j++)
            temp[j] = parent[j];

        unite(u, v);
        selected.push_back({w, u, v});

        findAverageTree(g, i + 1, cnt + 1,
                        V, E, total + w,
                        target, selected, bestDiff);

        selected.pop_back();

        for(int j = 0; j < V; j++)
            parent[j] = temp[j];
    }
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

        g.push_back({w, u, v});
    }

    // Find all spanning tree costs
    for(int i = 0; i < V; i++)
        parent[i] = i;

    findAll(g, 0, 0, V, E, 0);

    // Average of minimum and maximum spanning tree cost
    double avg = (minCost + maxCost) / 2.0;
    cout<<"all possible cost "<<endl;
    for(int num : arb)
    {
        cout<<num<<" ";
    }
    cout<<endl;

    cout << "Minimum Spanning Tree Cost = "
         << minCost << endl;

    cout << "Maximum Spanning Tree Cost = "
         << maxCost << endl;

    cout << "Average = " << avg << endl;

    // Find closest spanning tree
    for(int i = 0; i < V; i++)
        parent[i] = i;

    vector<tuple<int,int,int>> selected;


    double bestDiff = DBL_MAX;

    findAverageTree(g, 0, 0, V, E, 0,
                    avg, selected, bestDiff);

    cout << "\nAverage Spanning Tree:\n";

    int total = 0;

    for(int i = 0; i < bestTree.size(); i++)
    {
        int w, u, v;
        tie(w, u, v) = bestTree[i];

        cout << u << " " << v << " " << w << endl;

        total += w;
    }

    cout << "Tree Cost = " << total << endl;

    return 0;
}
