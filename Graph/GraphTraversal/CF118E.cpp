//https://codeforces.com/contest/118/problem/E
// bridges + scc
// from CC -> SCC
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<vector<int>> adj,adj_scc;
vector<int> parent,dfs_num,dfs_low;
int counter_dfs{0};

void dfs(int u){
	dfs_num[u] = counter_dfs++;
	dfs_low[u] = dfs_num[u];
	for(auto &v:adj[u]){
		if(dfs_num[v] == -1){
			parent[v] = u;
			adj_scc[u].push_back(v);
			dfs(v);
			dfs_low[u] = min(dfs_low[u],dfs_low[v]);
		}else if(parent[u] != v){
			dfs_low[u] = min(dfs_num[v],dfs_low[u]);
			if(dfs_num[u] > dfs_num[v])
				adj_scc[u].push_back(v);
		}
	}
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin >> n >> m;
	adj.assign(n,vector<int>());
	parent.assign(n,-1);
	dfs_num.assign(n,-1);
	dfs_low.assign(n,-1);
	adj_scc.assign(n,vector<int>());
	while(m--){
		int u,v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(0);
	bool ok = true;
	for(int i=1;i<n;i++){
		if(dfs_num[i] == dfs_low[i]){
			ok = false;
		}
	}
	if(!ok){
		cout << "0\n";
		return 0;
	}
	for(int i=0;i<n;i++){
		for(auto &v:adj_scc[i]){
			cout << (i+1) << " " << (v+1) << "\n";
		}
		
	}
	
}
