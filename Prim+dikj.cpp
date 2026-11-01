/*Input: V

        Random Connected Weighted Graph
                    │
          ┌─────────┴─────────┐
          ↓                   ↓
      Dijkstra              Prim
          ↓                   ↓
 Main Graph-এর           MST Graph
 Shortest Path               │
          │                  ↓
          │               Dijkstra
          │                  ↓
          │             MST-এর Shortest Path
          │                  │
          └────────┬─────────┘
                   ↓
              COMPARISON
*/

#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> generateGraph(int V)
{
    vector<vector<pair<int,int>>> g(V);

    set<pair<int,int>> edges;

    // First create a random spanning tree
    // This guarantees that the graph is connected
    for(int i=1; i<V; i++)
    {
        int u = i;
        int v = rand()%i;
        int w = rand()%100 + 1;

        g[u].push_back({v,w});
        g[v].push_back({u,w});

        if(u>v)
            swap(u,v);

        edges.insert({u,v});
    }

    // Random number of extra edges
    int maxEdges = V*(V-1)/2;
    int E = V-1;

    if(maxEdges > V-1)
        E += rand()%(maxEdges-(V-1)+1);

    // Add random extra edges
    while(edges.size() < E)
    {
        int u = rand()%V;
        int v = rand()%V;

        if(u==v)
            continue;

        int a=u,b=v;

        if(a>b)
            swap(a,b);

        if(edges.count({a,b}))
            continue;

        int w = rand()%100 + 1;

        g[u].push_back({v,w});
        g[v].push_back({u,w});

        edges.insert({a,b});
    }

    return g;
}


void dijkstra(vector<vector<pair<int,int>>> &g,
              int src,
              vector<int> &dist,
              vector<int> &parent)
{
    int V = g.size();

    dist.assign(V,INT_MAX);
    parent.assign(V,-1);

    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   greater<pair<int,int>>> pq;

    dist[src]=0;
    pq.push({0,src});

    while(!pq.empty())
    {
        int d=pq.top().first;
        int u=pq.top().second;

        pq.pop();

        if(d>dist[u])
            continue;

        for(int i=0;i<g[u].size();i++)
        {
            int v=g[u][i].first;
            int w=g[u][i].second;

            if(dist[u]+w<dist[v])
            {
                dist[v]=dist[u]+w;
                parent[v]=u;

                pq.push({dist[v],v});
            }
        }
    }
}


vector<vector<pair<int,int>>> prim(vector<vector<pair<int,int>>> &g)
{
    int V=g.size();

    vector<bool>vis(V,false);
    vector<int>parent(V,-1);
    vector<int>key(V,INT_MAX);

    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   greater<pair<int,int>>> pq;

    key[0]=0;
    pq.push({0,0});

    while(!pq.empty())
    {
        int u=pq.top().second;

        pq.pop();

        if(vis[u])
            continue;

        vis[u]=true;

        for(int i=0;i<g[u].size();i++)
        {
            int v=g[u][i].first;
            int w=g[u][i].second;

            if(!vis[v] && w<key[v])
            {
                key[v]=w;
                parent[v]=u;

                pq.push({key[v],v});
            }
        }
    }

    vector<vector<pair<int,int>>> mst(V);

    for(int i=1;i<V;i++)
    {
        int u=parent[i];
        int v=i;
        int w=key[i];

        mst[u].push_back({v,w});
        mst[v].push_back({u,w});
    }

    return mst;
}


vector<int> getPath(int src,int dest,vector<int> &parent)
{
    vector<int> path;

    int cur=dest;

    while(cur!=-1)
    {
        path.push_back(cur);
        cur=parent[cur];
    }

    reverse(path.begin(),path.end());

    if(path[0]!=src)
        return {};

    return path;
}


bool edgeExists(vector<vector<pair<int,int>>> &g,int u,int v)
{
    for(int i=0;i<g[u].size();i++)
    {
        if(g[u][i].first==v)
            return true;
    }

    return false;
}


void printPath(vector<int> &path)
{
    for(int i=0;i<path.size();i++)
    {
        cout<<path[i];

        if(i!=path.size()-1)
            cout<<" -> ";
    }
}


int main()
{
    srand(time(0));

    int V;
    cin>>V;

    int src=0;
    int dest=V-1;

    // Generate random connected weighted graph
    vector<vector<pair<int,int>>> g=generateGraph(V);

    cout<<"Original Graph:\n";

    for(int i=0;i<V;i++)
    {
        for(int j=0;j<g[i].size();j++)
        {
            int v=g[i][j].first;
            int w=g[i][j].second;

            if(i<v)
                cout<<i<<" - "<<v<<" : "<<w<<endl;
        }
    }


    // Dijkstra on original graph
    vector<int>originalDist;
    vector<int>originalParent;

    dijkstra(g,src,originalDist,originalParent);

    vector<int>originalPath=
        getPath(src,dest,originalParent);


    cout<<"\n================================\n";
    cout<<"MAIN GRAPH DIJKSTRA\n";
    cout<<"================================\n";

    cout<<"Source = "<<src<<endl;
    cout<<"Destination = "<<dest<<endl;

    cout<<"Shortest Distance = "
        <<originalDist[dest]<<endl;

    cout<<"Shortest Path = ";

    printPath(originalPath);

    cout<<endl;


    // Prim
    vector<vector<pair<int,int>>> mst=prim(g);

    cout<<"\n================================\n";
    cout<<"MST\n";
    cout<<"================================\n";

    for(int i=0;i<V;i++)
    {
        for(int j=0;j<mst[i].size();j++)
        {
            int v=mst[i][j].first;
            int w=mst[i][j].second;

            if(i<v)
                cout<<i<<" - "<<v<<" : "<<w<<endl;
        }
    }


    // Dijkstra on MST
    vector<int>mstDist;
    vector<int>mstParent;

    dijkstra(mst,src,mstDist,mstParent);

    vector<int>mstPath=
        getPath(src,dest,mstParent);


    cout<<"\n================================\n";
    cout<<"MST DIJKSTRA\n";
    cout<<"================================\n";

    cout<<"Source = "<<src<<endl;
    cout<<"Destination = "<<dest<<endl;

    cout<<"Shortest Distance = "
        <<mstDist[dest]<<endl;

    cout<<"Shortest Path = ";

    printPath(mstPath);

    cout<<endl;


    // Compare shortest paths
    cout<<"\n================================\n";
    cout<<"COMPARISON\n";
    cout<<"================================\n";

    cout<<"Main Graph Path : ";
    printPath(originalPath);
    cout<<endl;

    cout<<"MST Path        : ";
    printPath(mstPath);
    cout<<endl;


    if(originalPath==mstPath)
        cout<<"\nPath: SAME"<<endl;
    else
        cout<<"\nPath: DIFFERENT"<<endl;


    if(originalDist[dest]==mstDist[dest])
        cout<<"Distance: SAME"<<endl;
    else
        cout<<"Distance: DIFFERENT"<<endl;


    // Check which edges of original shortest path
    // are present in MST
    cout<<"\n================================\n";
    cout<<"ORIGINAL SHORTEST PATH EDGES IN MST\n";
    cout<<"================================\n";

    for(int i=0;i<originalPath.size()-1;i++)
    {
        int u=originalPath[i];
        int v=originalPath[i+1];

        cout<<u<<" - "<<v<<" : ";

        if(edgeExists(mst,u,v))
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }

    return 0;
}
