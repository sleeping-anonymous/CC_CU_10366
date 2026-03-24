#include <bits/stdc++.h>
using namespace std;

vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
{

    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto &p : prerequisites)
    {
        int course = p[0];
        int prereq = p[1];

        adj[prereq].push_back(course);
        indegree[course]++;
    }

    queue<int> q;

    for (int i = 0; i < numCourses; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    vector<int> topo;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        topo.push_back(node);

        for (auto neigh : adj[node])
        {
            indegree[neigh]--;

            if (indegree[neigh] == 0)
                q.push(neigh);
        }
    }

    if (topo.size() != numCourses)
        return {};

    return topo;
}

int main()
{
    int n = 4;

    vector<vector<int>> prereq = {{1, 2}, {2, 0}, {3, 1}, {3, 2}};

    vector<int> order = findOrder(n, prereq);

    for (auto &val : order)
        cout << val << " ";

    return 0;
}
