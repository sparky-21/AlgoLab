#include <bits/stdc++.h>
using namespace std;

bool bfs(vector<vector<int>>& rg, int s, int t, vector<int>& parent)
{
    int n = rg.size();

    vector<bool> vis(n, false);
    queue<int> q;

    q.push(s);
    vis[s] = true;
    parent[s] = -1;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(int v = 1; v < n; v++)
        {
            if(!vis[v] && rg[u][v] > 0)
            {
                vis[v] = true;
                parent[v] = u;

                if(v == t)
                    return true;

                q.push(v);
            }
        }
    }

    return false;
}

void findMaxFlow(int n, vector<vector<int>>& edg)
{
    vector<vector<int>> g(n + 1, vector<int>(n + 1, 0));

    // Capacity graph
    for(auto edge : edg)
    {
        int u = edge[0];
        int v = edge[1];
        int cap = edge[2];

        g[u][v] = cap;
    }

    // Residual graph
    vector<vector<int>> rg = g;

    int s = 1;
    int t = n;

    vector<int> parent(n + 1);
    int maxFlow = 0;

    // Keep finding augmenting paths
    while(bfs(rg, s, t, parent))
    {
        int pathFlow = INT_MAX;

        // Find bottleneck
        for(int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            pathFlow = min(pathFlow, rg[u][v]);
        }

        // Update residual graph
        for(int v = t; v != s; v = parent[v])
        {
            int u = parent[v];

            rg[u][v] -= pathFlow;
            rg[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    cout << maxFlow << endl;
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<int>> edg;

    for(int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        edg.push_back({u, v, w});
    }

    findMaxFlow(V, edg);

    return 0;
}
