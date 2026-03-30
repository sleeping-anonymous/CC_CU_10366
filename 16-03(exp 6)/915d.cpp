#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

int n, m;
vector<pair<int,int>> edges;
vector<int> adj[MAXN];

int vis[MAXN];
int parent[MAXN];
int parentEdge[MAXN];

vector<int> cycleEdges;

bool dfs(int u){
    vis[u] = 1;

    for(int id : adj[u]){
        int v = edges[id].second;

        if(vis[v] == 0){
            parent[v] = u;
            parentEdge[v] = id;

            if(dfs(v)) return true;
        }
        else if(vis[v] == 1){
            int cur = u;
            cycleEdges.push_back(id);

            while(cur != v){
                cycleEdges.push_back(parentEdge[cur]);
                cur = parent[cur];
            }

            return true;
        }
    }

    vis[u] = 2;
    return false;
}

bool checkWithout(int banned){

    vector<int> indeg(n+1,0);
    vector<vector<int>> g(n+1);

    for(int i=0;i<m;i++){
        if(i==banned) continue;

        int u = edges[i].first;
        int v = edges[i].second;

        g[u].push_back(v);
        indeg[v]++;
    }

    queue<int> q;

    for(int i=1;i<=n;i++)
        if(indeg[i]==0)
            q.push(i);

    int cnt=0;

    while(!q.empty()){
        int u=q.front(); q.pop();
        cnt++;

        for(int v:g[u]){
            if(--indeg[v]==0)
                q.push(v);
        }
    }

    return cnt==n;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>m;

    edges.resize(m);

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;

        edges[i]={u,v};
        adj[u].push_back(i);
    }

    for(int i=1;i<=n;i++){
        if(!vis[i] && dfs(i))
            break;
    }

    if(cycleEdges.empty()){
        cout<<"YES";
        return 0;
    }

    for(int id:cycleEdges){
        if(checkWithout(id)){
            cout<<"YES";
            return 0;
        }
    }

    cout<<"NO";
}