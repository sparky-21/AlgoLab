#include <bits/stdc++.h>
using namespace std;
// using 1D distance vector
int main()
{
    int V = 33;
    int E = 333;

    vector<tuple<int, int, int>> edg;

    srand(time(0));

    // -----------------------------------------
    // Generate random undirected graph
    // -----------------------------------------

    int e = 0;

    while (e < E)
    {
        int u = rand() % V;
        int v = rand() % V;
        int w = 1 + rand() % 100;

        if (u == v)
            continue;

        bool ex = false;

        // Check duplicate edge
        for (auto [x, y, z] : edg)
        {
            if ((x == u && y == v) ||
                (x == v && y == u))
            {
                ex = true;
                break;
            }
        }

        if (ex)
            continue;

        edg.push_back({u, v, w});
        edg.push_back({v,u, w});
        e++;
    }

    // -----------------------------------------
    // Add new vertex for Bellman-Ford
    // -----------------------------------------

    int s = V;

    vector<tuple<int, int, int>> bfedg = edg;

    for (int i = 0; i < V; i++)
    {
        bfedg.push_back({s, i, 0});
    }

    // -----------------------------------------
    // Bellman-Ford
    // -----------------------------------------

    vector<long long> h(V + 1, LLONG_MAX);

    h[s] = 0;

    for (int i = 0; i < V; i++)
    {
        for (auto [u, v, w] : bfedg)
        {
            if (h[u] != LLONG_MAX &&
                h[v] > h[u] + w)
            {
                h[v] = h[u] + w;
            }
        }
    }

    // -----------------------------------------
    // Check negative cycle
    // -----------------------------------------

    for (auto [u, v, w] : bfedg)
    {
        if (h[u] != LLONG_MAX &&
            h[v] > h[u] + w)
        {
            cout << "Negative weight cycle exists.\n";
            return 0;
        }
    }

    // -----------------------------------------
    // Reweight edges
    // -----------------------------------------

    vector<vector<pair<int, long long>>> adj(V);

    for (auto [u, v, w] : edg)
    {
        long long newWeight = w + h[u] - h[v];

        adj[u].push_back({v, newWeight});
        //adj[v].push_back({u, newWeight});
    }

    // -----------------------------------------
    // Open output file
    // -----------------------------------------

    ofstream fout("output2.txt");

    if (!fout)
    {
        cout << "Error opening output.txt\n";
        return 0;
    }

    // -----------------------------------------
    // Dijkstra from every vertex
    // -----------------------------------------

    for (int src = 0; src < V; src++)
    {
        // 1D distance vector
        vector<long long> dist(V, LLONG_MAX);

        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > pq;

        dist[src] = 0;

        pq.push({0, src});

        while (!pq.empty())
        {
            long long d = pq.top().first;
            int u = pq.top().second;

            pq.pop();

            if (d > dist[u])
                continue;

            for (int i = 0; i < adj[u].size(); i++)
            {
                int v = adj[u][i].first;
                long long w = adj[u][i].second;

                if (dist[v] > d + w)
                {
                    dist[v] = d + w;

                    pq.push({dist[v], v});
                }
            }
        }

        // -----------------------------------------
        // Convert back to original distances
        // and directly write to file
        // -----------------------------------------

        for (int v = 0; v < V; v++)
        {
            if (dist[v] != LLONG_MAX)
            {
                long long originalDist =
                    dist[v] - h[src] + h[v];

                fout << src << " "
                     << v << " "
                     << originalDist << "\n";
            }
        }
    }

    fout.close();

    cout << "All-pairs shortest distances saved in output2.txt\n";

    return 0;
}
