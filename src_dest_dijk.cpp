#include<bits/stdc++.h>
using namespace std;
// user input source destination
int main()
{
    int n, m;
    cin >> n>>m;
    vector<vector<pair<int,int>>>adj(n+1);
    int a,b,c;
    for(int i=0; i<m; i++)
    {
        cin>>a >>b>>c;
        adj[a].push_back({b,c});
    }
    vector<int>dist(n+1,INT_MAX);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    int src, dest;
    cin>>src>>dest;
    dist[src]=0;
    pq.push({0,src});
    while(!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;

        pq.pop();
        if(d> dist[u]) continue;
        for(int i=0; i<adj[u].size(); i++)
        {
            int v= adj[u][i].first;
            int w= adj[u][i].second;
            if(dist[v]>dist[u]+w)
            {
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
    if(dist[dest]==INT_MAX) cout<<"-1";
   else cout<<dist[dest];
    cout<<endl;
}


