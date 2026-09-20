#include<bits/stdc++.c>
using namespace std;
int main()
{
    int V=33,E=333;
    srand(time(0));
    vector<tuple<int,int,int>>g;
    for(int i=0 ; i<E; i++)
    {
        int u=rand()%V;
        int v=rand()%V;
        int w=1+rand()%100;
        if(u==v) continue;
        bool ex=false;
        for(auto[x,y,z]:g)
        {
            if((x==u && y==v) ||(x==v && y==u))
            {
                ex=true;
                break;
            }

        }
        if(ex) continue;
        g.push_back({u,v,w});
        g.push_back({v,u,w});

    }
    vector<int>h(V+1,INT_MAX);
    vector<tuple<int,int,int>>bfedg=g;
    int s=V;
    h[s]=0;
    for(int i=0;i<V;i++)
    {
        bfedg.push_back({s,i,0});
    }
    for(int i=0; i<V; i++)
    {
        for(auto[u,v,w]:bfedg)
        {
            if(h[u]!=INT_MAX && h[v]>h[u]+w) h[v]=h[u]+w;
        }
    }
    for(auto[u,v,w]:bfedg)
    {
        if(h[u]!=INT_MAX && h[v]>h[u]+w)
        {
            cout<<"NEG CYCLE";
            return 0;
        }
    }
    vector<vector<pair<int,int>>>adj(V);
    for(auto[u,v,w]:g)
    {
        int nw= w+h[u]-h[v];
        adj[u].push_back({v,nw});
    }
    for(int src=0; src<V; src++)
    {
        vector<int>dist(V,INT_MAX);
        dist[src]=0;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        pq.push({0,src});
        while(!pq.empty())
        {
            int u= pq.top().second;
            int d= pq.top().first;

            pq.pop();
            if(d> dist[u])continue;

            for(int i=0; i<adj[u].size(); i++)
            {
                int v= adj[u][i].first;
                int w=adj[u][i].second;
                if(dist[v]>dist[u]+w)
                {
                    dist[v]=dist[u]+w ;
                    pq.push({dist[v],v});

                }
            }

            for(int v=0; v<V; v++)
            {
                if(dist[v]!=INT_MAX)
                {
                    int orgdist= dist[v]-h[src]+h[v];
                    cout << src <<" "<<v<<" "<<orgdist;
                }
            }
            cout<<endl;
        }
    }

}
