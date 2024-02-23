//https://codeforces.com/problemset/problem/1850/H
// DFS graph traversal

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<vector<pair<int,int>>> adj;
vector<bool> vis;
vector<lli> dist;
bool ok = true;
void dfs(int u){
	vis[u] = true;
	for(auto &[v,w]:adj[u]){
		if(!vis[v]){
			dist[v] = dist[u] + w;
			dfs(v); 
		}else{
			if(dist[v] != dist[u] + w){
				ok = false;
			}
		}
	}
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		ok = true;
		int n,m;
		cin >> n >> m;
		vector<int> indegree(n,0);
		adj.assign(n,vector<pair<int,int>>());
		while(m--){
			int u,v,w;
			cin >> u >> v >> w;
			u--;
			v--;
			if(w > 0){
				adj[u].push_back({v,w});
				adj[v].push_back({u,-w});
			}else{
				adj[v].push_back({u,-w});
				adj[u].push_back({v,w});
			}
		}
		vis.assign(n,false);
		dist.assign(n,0);
		for(int i=0;i<n;i++){
			if(!vis[i]){
				dfs(i);
			}
		}
		cout << (ok ? "YES\n" : "NO\n");
	}
}
