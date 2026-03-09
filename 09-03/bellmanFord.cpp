#include <bits/stdc++.h>
using namespace std;

vector<int> bellmanFord(int V, vector<vector<int>> &edges, int src)
{

    vector<int> dist(V, 1e8);
    dist[src] = 0;

    for (int i = 0; i < V; i++)
    {

        for (vector<int> edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            if (dist[u] != 1e8 && dist[u] + wt < dist[v])
            {

                // If this is the Vth relaxation, then there is
                // a negative cycle
                if (i == V - 1)
                    return {-1};

                dist[v] = dist[u] + wt;
            }
        }
    }

    return dist;
}

int main()
{

    int V, E;
    cin >> V >> E;

    vector<vector<int>> edges;

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    int src;
    cin >> src;

    vector<int> ans = bellmanFord(V, edges, src);

    for (int d : ans)
        cout << d << " ";
}