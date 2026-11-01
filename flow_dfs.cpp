#include <bits/stdc++.h>
using namespace std;
bool dfs(vector<vector<int>>&rg, int s, int t, vector<int>&parent)
{
    int n= rg.size();
    vector<bool>vis(n,false);
    stack<int>q;
    vis[s]=true;
    parent[s]=-1;

    q.push(s);

    while(!q.empty())
    {
        int u= q.top();
        q.pop();
        for(int v=1; v<n; v++)
        {
            if(!vis[v] && rg[u][v]>0)
            {
                vis[v]=true;
                parent[v]=u;
                if(v==t) return true; // if(v==t)return true;

                q.push(v);
            }
        }
    }

    return false;

}
void findMaxFlow(int V,vector<vector<int>>&edg)
{
    //capacity graph

    vector<vector<int>>g(V+1, vector<int>(V+1));

    for(auto edgs : edg)
    {
        int u=edgs[0];
        int v=edgs[1];
        int cap=edgs[2];

        g[u][v]=cap;
    }

    // residual graph;
    vector<vector<int>>rg=g;
    int s=1;
    int t=V;
    vector<int>parent(V+1);
    int maxflow=0;
    while(dfs(rg, s,t,parent))
    {
        int pathflow=INT_MAX;

        for(int v= t; v!=s ; v= parent[v])
        {
            int u= parent[v];
            pathflow= min(rg[u][v],pathflow);
        }

        for(int v= t; v!=s ; v= parent[v])
        {
            int u= parent[v];
            rg[u][v] -= pathflow;
            rg[v][u] += pathflow;
        }

        maxflow+=pathflow;
    }

    cout<<maxflow<<endl;
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

