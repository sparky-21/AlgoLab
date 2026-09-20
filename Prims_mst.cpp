#include<bits/stdc++.h>
using namespace std;

int main()
{
    int V,E; cin >> V>> E;
    vector<vector<pair<int,int>>>g(V);
    for(int i=0 ;i<E ;i++)
    {
        int u,v,w; cin >> u>> v>>w;

        g[u].push_back({v,w});
        g[v].push_back({u,w});

    }

    vector<bool>visit(V,false);
    vector<int>parent(V,-1);
    vector<int>key(V,INT_MAX);
    key[0]=0;
    int tc=0;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({0,0});
   while(!pq.empty())
    {
        int u= pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if(visit[u]) continue;

        visit[u]= true;
        tc+=d;

        for(int i=0;i<g[u].size();i++)
        {
            int v= g[u][i].first;
            int w= g[u][i].second;

            if(!visit[v]&& w<key[v])
            {
                key[v]=w;
                parent[v]=u;
                pq.push({w,v});
            }
        }
    }
    cout <<endl;

    for(int i=0 ; i<V;i++)
    {
        cout<< parent[i]<<" "<<i<<" "<<key[i]<<endl;
    }

    cout<<" TOTAL COST " <<tc<<endl;
}
