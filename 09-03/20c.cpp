#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<long long> dist(n, 1e18);

    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>>
        pq;
    vector<int> parent(n);

    for (int i = 0; i < n; i++)
        parent[i] = i;

    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty())
    {
        auto [distance, node] = pq.top();
        pq.pop();
        if (distance > dist[node])
            continue;
        for (auto &it : adj[node])
        {
            long long adjNode = it.first;
            long long wt = it.second;

            if (distance + wt < dist[adjNode])
            {
                dist[adjNode] = distance + wt;
                parent[adjNode] = node;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }

    if (dist[n - 1] == 1e18)
    {
        cout << -1;
        return 0;
    }

    vector<int> path;
    int node = n - 1;

    while (parent[node] != node)
    {
        path.push_back(node + 1);
        node = parent[node];
    }

    path.push_back(1);
    reverse(path.begin(), path.end());

    for (int x : path)
        cout << x << " ";
}