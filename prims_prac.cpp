#include <bits/stdc++.h>
using namespace std;

int main()
{
    int V;
    cin >> V;

    vector<vector<pair<int,int>>>g(V);

    for(int i=0; i<V; i++)
    {
        for(int j=i+1; j<V; j++)
        {
            int w= rand()%100 +1;

            g[i].push_back({j,w});
            g[j].push_back({i,w});
        }
    }

    vector<bool>vis(V,false);

    vector<int>parent(V,-1);

    vector<int>key(V,INT_MAX);

    key[0]=0;

    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   greater<pair<int,int>>>pq;

    pq.push({0,0});

    while(!pq.empty())
    {
        int u= pq.top().second;
        int d= pq.top().first;

        pq.pop();

        if(vis[u])
            continue;

        vis[u]=true;

        for(int i=0; i<g[u].size(); i++)
        {
            int v= g[u][i].first;
            int w= g[u][i].second;

            if(!vis[v] && w < key[v])
            {
                parent[v]=u;
                key[v]=w;

                pq.push({w,v});
            }
        }
    }

    cout << "MST:\n";

    for(int i=1; i<V; i++)
    {
        cout << parent[i] << " " << i << " " << key[i] << endl;
    }

    return 0;
}
