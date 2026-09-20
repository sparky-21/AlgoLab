#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;
    cin >> n >> m;

    vector<tuple<int,int,int>> adj;

    // graph input
    for(int i=0; i<m; i++)
    {
        int u,v,w;
        cin >> u >> v >> w;

        adj.push_back({u,v,w});
    }

    // graph output
    for(auto [x,y,z] : adj)
    {
        cout << x << " " << y << " " << z << endl;
    }

    // Bellman-Ford
    vector<int> dist(n,INT_MAX);
    vector<int> parent(n,-1);

    dist[0] = 0;

    for(int i=0; i<n-1; i++)
    {
        for(auto [u,v,w] : adj)
        {
            if(dist[u] != INT_MAX && dist[v] > dist[u] + w)
            {
                parent[v] = u;
                dist[v] = dist[u] + w;
            }
        }
    }

    // Negative cycle detection
    bool negcy = false;

    for(auto [u,v,w] : adj)
    {
        if(dist[u] != INT_MAX && dist[v] > dist[u] + w)
        {
            negcy = true;
            break;
        }
    }

    if(negcy)
    {
        cout << "NEG CYCLE DETECTED" << endl;
    }
    else
    {
        for(int i=0; i<n; i++)
        {
            if(dist[i] == INT_MAX)
                cout << "INF ";
            else
                cout << dist[i] << " ";
        }

        cout << endl;

        // Path from 0 to n-1
        vector<int> path;

        for(int cur=n-1; cur!=-1; cur=parent[cur])
        {
            path.push_back(cur);
        }

        reverse(path.begin(),path.end());

        for(int i=0; i<path.size(); i++)
        {
            cout << path[i] << " ";
        }
    }
}
