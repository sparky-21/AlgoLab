#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n+1);

    // graph input
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(pair<int,int>(v,w));
        adj[v].push_back(pair<int,int>(u,w));
    }

    // graph output
    for(int u = 1; u <= n; u++) {
        for(int j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j].first;
            int w = adj[u][j].second;
            cout << "(" << v << "," << w << ") ";
        }
        cout << "\n";
    }
    cout << "\n";

    // Dijkstra
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> dist(n+1, INT_MAX);
    vector<int> parent(n+1, -1);

    dist[1] = 0;
    pq.push(pair<int,int>(0, 1));

    while(!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(d > dist[u]) continue;

        for(int j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j].first;
            int w = adj[u][j].second;

            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(pair<int,int>(dist[v], v));
            }
        }
    }

    // Print distances
    cout << "Shortest distances from node 1:\n";
    for(int i = 1; i <= n; i++) {
        if(dist[i] == INT_MAX) cout << i << ": -1\n";
        else cout << i << ": " << dist[i] << "\n";
    }
    cout << "\n";

    // Print paths
    cout << "Shortest paths from node 1:\n";
    for(int i = 1; i <= n; i++) {
        if(dist[i] == INT_MAX) {
            cout << "No path to " << i << "\n";
        } else {
            vector<int> path;
            for(int cur = i; cur != -1; cur = parent[cur]) {
                path.push_back(cur);
            }
            reverse(path.begin(), path.end());

            cout << "Path to " << i << ": ";
            for(int k = 0; k < path.size(); k++) {
                cout << path[k] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}

/*// Priority queue input output
    priority_queue<
        pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        int prio, val;
        cin >> prio >> val;

        pq.push({prio, val});
    }

    while(!pq.empty()) {

        pair<int,int> p = pq.top();

        cout << p.first << " " << p.second << endl;

        pq.pop();
    }*/

