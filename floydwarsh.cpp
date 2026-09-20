#include<bits/stdc++.h>
using namespace std;

int main()
{
    int V,E;
    cin >> V>>E;

    vector<vector<int>>dist(V,vector<int>(V,INT_MAX));
    for(int i=0 ; i<V; i++)
    {
        dist[i][i]=0;
    }
    for(int i=0; i<E; i++)
    {
        int u, v,w;
        cin >>u>>v>>w;
        dist[u][v]=w;
    }
    for(int k=0; k<V; k++)
    {
        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                if(dist[i][k]!= INT_MAX &&dist[k][j]!= INT_MAX)
                {
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }
    }

    for(int i=0; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            if(dist[i][j]==INT_MAX) cout<<"INF "<<" ";
            else cout <<dist[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
