//https://codeforces.com/problemset/problem/1092/F
// dp + tree

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<vector<int>> adj,tree;
vector<lli> cost,sol;
vector<int> vis;
vector<lli> dist_subtree;
vector<lli> sum_subtree;
vector<int> parent;
void dfs(int u){
	vis[u] = true;
	sum_subtree[u] = cost[u];
	dist_subtree[u] = 0;
	for(auto &v:adj[u]){
		if(!vis[v]){
			parent[v] = u;
			tree[u].push_back(v);
			dfs(v);
			sum_subtree[u] += sum_subtree[v];
			dist_subtree[u] += dist_subtree[v] + sum_subtree[v];
		}
	}
}

void solve(int u,lli &ans){
	if(parent[u] == -1){
		sol[u] = dist_subtree[u];
		ans = max(ans,dist_subtree[u]);
	}else{
		sol[u] = sol[parent[u]] + sum_subtree[0] - 2LL*sum_subtree[u];
		ans = max(ans,sol[u]);
	}
	for(auto &v: tree[u]){
		solve(v,ans);
	}
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	cost.assign(n,0);
	sol.assign(n,-1);
	parent.assign(n,-1);
	adj.assign(n,vector<int>());
	tree.assign(n,vector<int>());
	vis.assign(n,0);
	sum_subtree.assign(n,0);
	dist_subtree.assign(n,0);
	for(int i=0;i<n;i++){
		cin >> cost[i];
	}
	for(int i=0;i<n-1;i++){
		int u,v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(0);
	lli ans = -inf;
	solve(0,ans);
	cout << ans << "\n";
}








