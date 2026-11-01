/*Max Flow + Min Cut
Generate a directed capacitated graph.

Apply Ford-Fulkerson / Edmonds-Karp.

Find:

1.  Maximum flow
2.  Minimum cut
3.  Edges belonging to the minimum cut

Maximum Flow = 42

Minimum Cut:

S-side:
0 1 2 4

T-side:
3 5 6 7

Cut Edges:
0 -> 3 : 10
2 -> 5 : 15
4 -> 6 : 17

Cut Capacity = 42
Max Flow == Min Cut Capacity
YES*/


#include <bits/stdc++.h>
using namespace std;

bool dfs(vector<vector<int>>& rg, int s, int t, vector<int>& parent)
{
    int n = rg.size();

    vector<bool> vis(n, false);
    stack<int> st;

    st.push(s);
    vis[s] = true;
    parent[s] = -1;

    while(!st.empty())
    {
        int u = st.top();
        st.pop();

        for(int v = 0; v < n; v++)
        {
            if(!vis[v] && rg[u][v] > 0)
            {
                vis[v] = true;
                parent[v] = u;

                if(v == t)
                    return true;

                st.push(v);
            }
        }
    }

    return false;
}

void findMaxFlowMinCut(int V, vector<vector<int>>& edg)
{
    // -----------------------------
    // 1. Capacity graph
    // -----------------------------
    vector<vector<int>> g(V, vector<int>(V, 0));

    for(auto edge : edg)
    {
        int u = edge[0];
        int v = edge[1];
        int cap = edge[2];

        g[u][v] += cap;
    }

    // -----------------------------
    // 2. Residual graph
    // -----------------------------
    vector<vector<int>> rg = g;

    int s = 0;
    int t = V - 1;

    vector<int> parent(V);
    int maxFlow = 0;

    // -----------------------------
    // 3. Ford-Fulkerson
    // -----------------------------
    while(dfs(rg, s, t, parent))
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

    // -----------------------------
    // 4. Find S-side
    // -----------------------------
    vector<bool> vis(V, false);
    stack<int> st;

    st.push(s);
    vis[s] = true;

    while(!st.empty())
    {
        int u = st.top();
        st.pop();

        for(int v = 0; v < V; v++)
        {
            if(!vis[v] && rg[u][v] > 0)
            {
                vis[v] = true;
                st.push(v);
            }
        }
    }

    // -----------------------------
    // 5. Print Maximum Flow
    // -----------------------------
    cout << "Maximum Flow = " << maxFlow << endl;

    // -----------------------------
    // 6. Print Minimum Cut
    // -----------------------------
    cout << "\nMinimum Cut:\n\n";

    cout << "S-side:\n";
    for(int i = 0; i < V; i++)
    {
        if(vis[i])
            cout << i << " ";
    }
    cout << "\n";

    cout << "\nT-side:\n";
    for(int i = 0; i < V; i++)
    {
        if(!vis[i])
            cout << i << " ";
    }
    cout << "\n";

    // -----------------------------
    // 7. Find Cut Edges
    // -----------------------------
    int cutCapacity = 0;

    cout << "\nCut Edges:\n";

    for(auto edge : edg)
    {
        int u = edge[0];
        int v = edge[1];
        int cap = edge[2];

        // u belongs to S
        // v belongs to T
        if(vis[u] && !vis[v])
        {
            cout << u << " -> " << v << " : " << cap << endl;

            cutCapacity += cap;
        }
    }

    // -----------------------------
    // 8. Cut Capacity
    // -----------------------------
    cout << "\nCut Capacity = " << cutCapacity << endl;

    // -----------------------------
    // 9. Max-flow Min-cut theorem
    // -----------------------------
    cout << "Max Flow == Min Cut Capacity\n";

    if(maxFlow == cutCapacity)
        cout << "YES\n";
    else
        cout << "NO\n";
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

    findMaxFlowMinCut(V, edg);

    return 0;
}
