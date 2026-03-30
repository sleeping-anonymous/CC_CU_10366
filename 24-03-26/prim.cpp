#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<vector<int>> mat = {
        {5, 4, 9}, {5, 1, 4}, {1, 2, 2}, {1, 4, 1}, {4, 2, 3}, {4, 3, 5}, {2, 6, 7}, {2, 3, 3}, {3, 6, 8}};  // u,v,wt

    int n = 6;

    vector<vector<pair<int, int>>> adj(n + 1);

    // build graph
    for (auto &m : mat)
    {
        int u = m[0];
        int v = m[1];
        int w = m[2];

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 1});

    vector<int> visited(n + 1, 0);
    int ans = 0;

    while (!pq.empty())
    {
        int wt = pq.top().first;
        int node = pq.top().second;

        pq.pop();

        if (visited[node])
            continue;

        visited[node] = 1;
        ans += wt;

        for (auto nei : adj[node])
        {
            if (!visited[nei.first])
            {
                pq.push({nei.second, nei.first});
            }
        }
    }

    cout << ans << " ";

    return 0;
}