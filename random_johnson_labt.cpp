#include <bits/stdc++.h>
using namespace std;

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

        // No self-loop
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
        e++;
    }

    // -----------------------------------------
    // Add new vertex for Bellman-Ford
    // -----------------------------------------

    int s = V;

    vector<tuple<int, int, int>> bfedg = edg;

    // Connect new vertex to every vertex with weight 0
    for (int i = 0; i < V; i++)
    {
        bfedg.push_back({s, i, 0});
    }

    // -----------------------------------------
    // Bellman-Ford
    // -----------------------------------------

    vector<long long> h(V + 1, LLONG_MAX);

    h[s] = 0;

    // Relax V times
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
    // Check for negative weight cycle
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
    // Reweight all edges
    // -----------------------------------------

    vector<vector<pair<int, long long>>> adj(V);

    for (auto [u, v, w] : edg)
    {
        long long newWeight = w + h[u] - h[v];

        // Undirected graph
        adj[u].push_back({v, newWeight});
        adj[v].push_back({u, newWeight});
    }

    // -----------------------------------------
    // Dijkstra from every vertex
    // -----------------------------------------

    vector<vector<long long>> dist(
        V,
        vector<long long>(V, LLONG_MAX)
    );

    for (int src = 0; src < V; src++)
    {
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > pq;

        dist[src][src] = 0;

        pq.push({0, src});

        while (!pq.empty())
        {
            long long d = pq.top().first;
            int u = pq.top().second;

            pq.pop();

            // Ignore outdated entry
            if (d > dist[src][u])
                continue;

            for (int i = 0; i < adj[u].size(); i++)
            {
                int v = adj[u][i].first;
                long long w = adj[u][i].second;

                if (dist[src][v] > d + w)
                {
                    dist[src][v] = d + w;

                    pq.push({
                        dist[src][v],
                        v
                    });
                }
            }
        }

        // -----------------------------------------
        // Convert reweighted distance back
        // to original distance
        // -----------------------------------------

        for (int j = 0; j < V; j++)
        {
            if (dist[src][j] != LLONG_MAX)
            {
                dist[src][j] =
                    dist[src][j] - h[src] + h[j];
            }
        }
    }

    // -----------------------------------------
    // Save all distances to output.txt
    // -----------------------------------------

    ofstream fout("output.txt");

    if (!fout)
    {
        cout << "Error opening output.txt\n";
        return 0;
    }

    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
        {
            if (dist[u][v] != LLONG_MAX)
            {
                fout << u << " "
                     << v << " "
                     << dist[u][v] << "\n";
            }
        }
    }

    fout.close();

    cout << "Graph generated successfully.\n";
    cout << "All-pairs shortest distances saved in output.txt\n";

    return 0;
}
