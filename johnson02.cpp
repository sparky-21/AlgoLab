#include<bits/stdc++.h>
using namespace std;

int main()
{
    int V, E;
    cin >> V >> E;
    vector<tuple<int,int,int>>g;
    for(int i=0 ; i<E; i++)
    {
        int u, v,w;
        cin >> u>>v>>w;
        g.push_back({u,v,w});
        g.push_back({v,u,w});
    }

    //bellmanford
    vector<tuple<int,int,int>>bfedg=g;
    vector<int>h(V+1,INT_MAX);
    int s=V;
    h[s]=0;
    for(int i=0 ; i<V; i++)
    {
        bfedg.push_back({s,i,0});
    }
    for(int i=0; i<V; i++)
    {
        for(auto[u,v,w] : bfedg)
        {
            if(h[u] != INT_MAX && h[v]>h[u]+w)
            {
                h[v]=h[u]+w;
            }
        }
    }
    for(auto[u,v,w] : bfedg)
    {
        if(h[u] != INT_MAX && h[v]>h[u]+w)
        {
            cout<<"NEG CYCLE ";
            return 0;
        }
    }
    // reweighting
    vector<vector<pair<int,int>>>adj(V);

    for(auto[u,v,w] : g)
    {
        int nw = w+h[u]-h[v];
        adj[u].push_back({v,nw});

    }
    //dijkstra
    for(int src=0; src<V; src++)
    {
        vector<int>dist(V,INT_MAX);
        dist[src]=0;
        priority_queue<
        pair<long long, int>,
             vector<pair<long long, int>>,
             greater<pair<long long, int>>
             > pq;
        pq.push({0,src});
        while(!pq.empty())
        {
            int d = pq.top().first;
            int u = pq.top().second;

            pq.pop();

            if (d > dist[u])
                continue;

            for (int i = 0; i < adj[u].size(); i++)
            {
                int v = adj[u][i].first;
                int w = adj[u][i].second;

                if (dist[v] > d + w)
                {
                    dist[v] = d + w;

                    pq.push({dist[v], v});
                }
            }
        }

        for(int j=0; j<V; j++)
        {
            if(dist[j]!=INT_MAX)
            {
                int orgdist= dist[j]-h[src]+h[j];

                cout<< src << " "<<j <<" "<<orgdist<<" "<<endl;
            }


        }
        cout<<endl;

    }
}
