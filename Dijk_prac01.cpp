#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;
    cin >> n>>m;

    vector<vector<pair<int,int>>>adj(n);
    // graph input
    for(int i=0; i<m; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }
    //graph output
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<adj[i].size(); j++)
        {
            cout << i <<" "<<adj[i][j].first<<" "<<adj[i][j].second<<endl;
        }
        cout<<endl;
    }
    // dijkstra
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    vector<int>dist(n,INT_MAX);
    vector<int>parent(n,-1);
    dist[0]=0;
    pq.push({0,0});
    while(!pq.empty())
    {
        int u= pq.top().second;
        int d= pq.top().first;
        pq.pop();
         if(d != dist[u]) continue;
        for(int i=0; i<adj[u].size(); i++)
        {
            int v= adj[u][i].first;
            int w= adj[u][i].second;
            if(dist[v]>dist[u]+w)
            {
                parent[v]=u;
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
    for(int i=0; i<n; i++)
    {
        if(dist[i]==INT_MAX) cout<<"INF"<<" ";
        else cout<<dist[i]<<" ";
    }
    cout <<endl;
    //path printing
    vector<int>path;
    for(int cur=n-1 ; cur!=-1; cur=parent[cur])
    {
        path.push_back(cur);
    }
    reverse(path.begin(),path.end());
    for(int i=0; i<path.size(); i++)
    {
        cout<< path[i]<<" ";
    }
}
