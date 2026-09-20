#include<bits/stdc++.h>
using namespace std;
int parent[100];
int find(int x)
{
    if(parent[x]==x) return x;

    return parent[x]=find(parent[x]);
}
void unite(int x,int y)
{
    int a= find(x);
    int b= find(y);

    if(a!=b)
    {
        parent[b]=a;
    }
}
int main()
{
    int V,E;
    cin>>V>>E;

    set<tuple<int,int,int>>g;

    for(int i=0;i<E;i++)
    {
        int u,v,w; cin>>u>>v>>w;
        g.insert({w,u,v});
    }

    for(int i=0;i<V;i++)
    {
       parent[i]=i;
    }

    int tc=0;int edcnt=0;

    for(auto[w,u,v]:g)
    {
        if(find(u)!=find(v))
        {
            unite(u,v);
            cout<<u<<" "<<v<<" "<<w<<endl;
            tc+=w;
            edcnt++;
        }

        if(edcnt == V-1) break;
    }

    cout<<" Total cost "<<tc<<endl;
}
