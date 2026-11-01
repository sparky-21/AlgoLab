
#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>>graph;
vector<bool>inMST;
vector<int>parent,key;


int prim(int src, int node)
{

    vector<bool>curMST(node,false);

    key[src] = 0;

    set<pair<int,int>>mst;
    mst.insert({key[src],src});

    while(!mst.empty())
    {

        int u = mst.begin()->second;

        mst.erase(mst.begin());

        if(inMST[u])continue;
        inMST[u] = true;
        curMST[u] = true;


        for(auto &[v,w]:graph[u])
        {

            if(!inMST[v] && key[v]>w)
            {

                mst.erase({key[v],v});

                parent[v] = u;
                key[v] = w;

                mst.insert({key[v],v});

            }
        }


    }

    int w=0, vertex;
    for(int v = 0; v < node; v++)
    {
        if(curMST[v] && parent[v]!=-1)
        {
            cout << parent[v] << " " << v << " : " << key[v] << endl;
            w+=key[v];
        }
        else if(curMST[v] && parent[v]==-1) vertex = v;
    }

    if(w==0) cout<<vertex<<endl;
    cout<<"Current MST weight: "<<w<<endl;
    return w;

}

int main()
{

    int node,edge;
    cin>>node>>edge;

    graph.resize(node);
    inMST.assign(node,false);
    parent.assign(node,-1);
    key.assign(node,INT_MAX);

    for(int i=0; i<edge; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;

        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }

    int cnt =1, w=0;
    for(int i=0; i<node; i++)
    {
        if(!inMST[i])
        {
            cout<<"\nTree "<<cnt<<":\n";
            key.assign(node,INT_MAX);
            parent.assign(node,-1);
            w+= prim(i,node);
            cnt++;
        }
    }

    cout<<"\nTotal Forest Weight: "<<w<<endl;

}
