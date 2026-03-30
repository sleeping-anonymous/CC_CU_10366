#include<bits/stdc++.h>
using namespace std;

const int N = 100;
int capacity[N][N];   // residual capacity
vector<int> adj[N];

int n; // number of nodes

// DFS to find augmenting path
int dfs(int u, int t, vector<int>& visited, int flow) {
    if (u == t) return flow;

    visited[u] = 1;

    for (int v : adj[u]) {
        if (!visited[v] && capacity[u][v] > 0) {
            int new_flow = min(flow, capacity[u][v]);
            int pushed = dfs(v, t, visited, new_flow);

            if (pushed > 0) {
                capacity[u][v] -= pushed;
                capacity[v][u] += pushed; // reverse edge
                return pushed;
            }
        }
    }
    return 0;
}

// Ford-Fulkerson
int maxFlow(int s, int t) {
    int flow = 0;

    while (true) {
        vector<int> visited(n + 1, 0);
        int pushed = dfs(s, t, visited, INT_MAX);

        if (pushed == 0) break; // no augmenting path
        flow += pushed;
    }
    return flow;
}

int main() {
    n = 6;

    // edges: u, v, capacity
    vector<vector<int>> edges = {
        {1,2,16}, {1,3,13}, {2,3,10}, {3,2,4},
        {2,4,12}, {3,5,14}, {4,3,9},
        {4,6,20}, {5,4,7}, {5,6,4}
    };

    // build graph
    for (auto &e : edges) {
        int u = e[0], v = e[1], cap = e[2];
        adj[u].push_back(v);
        adj[v].push_back(u); // reverse edge
        capacity[u][v] = cap;
    }

    int source = 1, sink = 6;

    cout << "Max Flow = " << maxFlow(source, sink) << endl;

    return 0;
}