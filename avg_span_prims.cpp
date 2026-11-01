#include <bits/stdc++.h>
using namespace std;

int mincost= INT_MAX;
int maxcost = INT_MIN;

set<int>arb;
vector<tuple<int,int,int>>bestTree;

bool hascycle(vector<tuple<int,int,int>>&selected, int u, int v, int V)
{
    vector<vector<int>>g(V);
    for(int i = 0; i < selected.size(); i++)
    {
        int w, a, b;
        tie(w, a, b) = selected[i];

        g[a].push_back(b);
        g[b].push_back(a);
    }

    queue<int>q;
    vector<bool>vis(V,false);

    q.push(u);
    vis[u]=true;

    while(!q.empty())
    {
        int x = q.front();
        q.pop();

        for(int i = 0; i < g[x].size(); i++)
        {
            int y = g[x][i];

            if(!vis[y])
            {
                vis[y] = true;
                q.push(y);
            }
        }
    }

    return vis[v];


}

void findAll(vector<tuple<int,int,int>>& g,
             int pos,
             int cnt,
             int V,
             int E,
             int total,
             vector<tuple<int,int,int>>& selected)
{
    if(cnt ==V-1)
    {
        arb.insert(total);
        mincost=min(mincost,total);
        maxcost = max(maxcost, total);
        return;
    }

    for(int i= pos ; i<E ; i++)
    {
        int w, u, v;
        tie(w, u, v) = g[i];

        if(hascycle(selected, u, v, V))
            continue;

        selected.push_back({w, u, v});

        findAll(g, i + 1, cnt + 1,
                V, E, total + w, selected);

        selected.pop_back();
    }


}

void findAvg(vector<tuple<int,int,int>>& g,
        int pos,
        int cnt,
        int V,
        int E,
        int total,
        double target,
        vector<tuple<int,int,int>>& selected,
        double& bestDiff)
{
    if(cnt ==V-1)
    {
        double diff = abs(total - target);

        if(diff<bestDiff)
        {
            bestDiff=diff;
            bestTree=selected;
        }
        return;
    }
    for(int i = pos; i < E; i++)
    {
        int w, u, v;
        tie(w, u, v) = g[i];

        if(hascycle(selected, u, v, V))
            continue;

        selected.push_back({w, u, v});

        findAvg(g, i + 1, cnt + 1,
                        V, E, total + w,
                        target, selected, bestDiff);

        selected.pop_back();
    }
}
int main()
{
    int V,E;
    cin >>V>>E;

    vector<tuple<int,int,int>>g;
    for(int i=0; i<E; i++)
    {
        int u,v,w;
        cin >> u>>v>>w;

        g.push_back({w,u,v});
    }

    sort(g.begin(),g.end());
    vector<tuple<int,int,int>>selected;
    int pos =0, cnt=0, tt=0;
    findAll(g,pos,cnt,V,E,tt,selected);
    double avg = (mincost+ maxcost)/2.0;
    cout<<" all possible cost "<<endl;

    for(int num : arb)
    {
        cout<<num<<" ";
    }
    cout<<endl;
    cout << "Minimum Spanning Tree Cost = "
         << mincost << endl;

    cout << "Maximum Spanning Tree Cost = "
         << maxcost << endl;

    cout << "Average = " << avg << endl;

    double bestDiff =DBL_MAX;
    findAvg(g,pos,cnt, V,E,tt,avg,selected, bestDiff);

    cout << "\nAverage Spanning Tree:" << endl;

    int total = 0;

    for(int i = 0; i < bestTree.size(); i++)
    {
        int w, u, v;

        tie(w, u, v) = bestTree[i];

        cout << u << " " << v << " " << w << endl;

        total += w;
    }

    cout << "Tree Cost = " << total << endl;


    return 0;
}
