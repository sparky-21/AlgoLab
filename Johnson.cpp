#include <bits/stdc++.h>
using namespace std;

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<tuple<int, int, int>> edges;

    cout << "Enter edges (u v weight):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        // Assuming vertices are numbered 0 to V-1
        edges.push_back({u, v, w});
    }

    // --------------------------------------------------
    // STEP 1: Add a new vertex S
    // --------------------------------------------------

    int S = V;

    vector<tuple<int, int, int>> bfEdges = edges;

    // Connect S to every vertex with weight 0
    for (int i = 0; i < V; i++)
    {
        bfEdges.push_back({S, i, 0});
    }

    // --------------------------------------------------
    // STEP 2: Bellman-Ford from S
    // --------------------------------------------------

    vector<long long> h(V + 1, LLONG_MAX);
    h[S] = 0;

    for (int i = 0; i < V; i++)
    {
        bool changed = false;

        for (auto [u, v, w] : bfEdges)
        {
            if (h[u] != LLONG_MAX &&
                h[v] > h[u] + w)
            {
                h[v] = h[u] + w;
                changed = true;
            }
        }

        if (!changed)
            break;
    }

    // Check for negative cycle
    for (auto [u, v, w] : bfEdges)
    {
        if (h[u] != LLONG_MAX &&
            h[v] > h[u] + w)
        {
            cout << "Negative weight cycle exists.\n";
            return 0;
        }
    }

    // --------------------------------------------------
    // STEP 3: Reweight all edges
    // w'(u,v) = w(u,v) + h[u] - h[v]
    // --------------------------------------------------

    vector<vector<pair<int, long long>>> adj(V);

    for (auto [u, v, w] : edges)
    {
        long long newWeight = w + h[u] - h[v];

        adj[u].push_back({v, newWeight});
    }

    // --------------------------------------------------
    // STEP 4: Run Dijkstra from every vertex
    // --------------------------------------------------

    const long long INF = LLONG_MAX / 4;

    vector<vector<long long>> dist(V,
                                   vector<long long>(V, INF));

    for (int source = 0; source < V; source++)
    {
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > pq;

        dist[source][source] = 0;

        pq.push({0, source});

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[source][u])
                continue;

            for (auto [v, w] : adj[u])
            {
                if (dist[source][v] > d + w)
                {
                    dist[source][v] = d + w;
                    pq.push({dist[source][v], v});
                }
            }
        }

        // --------------------------------------------------
        // STEP 5: Convert distances back to original weights
        // d(u,v) = d'(u,v) - h[u] + h[v]
        // --------------------------------------------------

        for (int v = 0; v < V; v++)
        {
            if (dist[source][v] != INF)
            {
                dist[source][v] =
                    dist[source][v] - h[source] + h[v];
            }
        }
    }

    // --------------------------------------------------
    // STEP 6: Print APSP distance matrix
    // --------------------------------------------------

    cout << "\nAll-Pairs Shortest Path Matrix:\n\n";

    cout << "     ";
    for (int i = 0; i < V; i++)
        cout << setw(6) << i;

    cout << "\n";

    for (int i = 0; i < V; i++)
    {
        cout << setw(4) << i << " ";

        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                cout << setw(6) << "INF";
            else
                cout << setw(6) << dist[i][j];
        }

        cout << "\n";
    }

    return 0;
}
