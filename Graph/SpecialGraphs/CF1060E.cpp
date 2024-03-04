// https://codeforces.com/contest/1060/problem/E
// dp on trees

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<vector<int>> adj;
vector<lli> vis,subtree_size,sol,childrenSum,parent;
void dfs(int u){
	vis[u] = true;
	subtree_size[u] = 1;
	int counter_children = 0;
	sol[u] = 0;
	childrenSum[u] = 0;
	for(auto &v:adj[u]){
		if(!vis[v]){
			parent[v] = u;
			dfs(v);
			counter_children++;
			sol[u] += childrenSum[v];
			childrenSum[u] += sol[v] + subtree_size[v];
			subtree_size[u] += subtree_size[v];
		}	
	}
	sol[u] += counter_children;
}

lli global_ans = 0;
void dfs2(int u,int n){
	vis[u] = true;
	
	if(parent[u] != -1){
		global_ans += childrenSum[parent[u]] - subtree_size[u] + 1;
		sol[u] = childrenSum[parent[u]] - subtree_size[u] + 1;
		lli temp_solp = sol[parent[u]] - childrenSum[u] - 1;
		lli temp_sizep = n - subtree_size[u];
		childrenSum[u] += temp_solp + temp_sizep;
	}
	for(auto &v:adj[u]){
		if(!vis[v]){
			dfs2(v,n);
		}
	}
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	adj.assign(n,vector<int>());
	vis.assign(n,false);
	subtree_size.assign(n,0);
	childrenSum.assign(n,0);
	parent.assign(n,-1);
	sol.assign(n,0);
	
	for(int i=0;i<n-1;i++){
		int u,v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(0);
	global_ans = sol[0];
	vis.assign(n,0);
	dfs2(0,n);
	cout << global_ans/2 << "\n";
}
