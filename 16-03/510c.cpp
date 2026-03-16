#include <bits/stdc++.h>
using namespace std;

vector<int> adj[26];
int vis[26];
vector<int> order;
bool cycle = false;

void dfs(int u)
{
    vis[u] = 1;

    for (int v : adj[u])
    {
        if (vis[v] == 0)
        {
            dfs(v);
        }
        else if (vis[v] == 1)
        {
            cycle = true;
        }
    }

    vis[u] = 2;
    order.push_back(u);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<string> names(n);

    for (int i = 0; i < n; i++)
        cin >> names[i];

    for (int i = 0; i < n - 1; i++)
    {

        string a = names[i];
        string b = names[i + 1];

        int len = min(a.size(), b.size());
        bool found = false;

        for (int j = 0; j < len; j++)
        {

            if (a[j] != b[j])
            {
                adj[a[j] - 'a'].push_back(b[j] - 'a');
                found = true;
                break;
            }
        }

        if (!found && a.size() > b.size())
        {
            cout << "Impossible";
            return 0;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (!vis[i])
            dfs(i);
    }

    if (cycle)
    {
        cout << "Impossible";
        return 0;
    }

    reverse(order.begin(), order.end());

    for (int x : order)
        cout << char(x + 'a');

    return 0;
}