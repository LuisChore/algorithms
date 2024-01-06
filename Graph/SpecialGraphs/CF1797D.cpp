// https://codeforces.com/problemset/problem/1797/D
// Tree rotate operations
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;



vector<lli> a,patent,subtree_importance,subtree_size,parent;
vector<vector<int>> adj;
vector<set<pair<lli,int>>> children;

void dfs(int u){
	subtree_importance[u] = a[u];
	subtree_size[u] = 1;
	for(auto &v:adj[u]){
		if(parent[u] != v){
			parent[v] = u;
			dfs(v);
			subtree_size[u] += subtree_size[v];
			subtree_importance[u] += subtree_importance[v];
		}
	}
	for(auto &v: adj[u]){
		if(parent[u] != v){
			children[u].insert({-subtree_size[v],v});
		}
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n,q;
	cin >> n >> q;
	a.assign(n,0);
	parent.assign(n,-1);
	subtree_importance.assign(n,0);
	subtree_size.assign(n,0);
	adj.assign(n,vector<int>());
	children.assign(n,set<pair<lli,int>>());
	for(int i=0;i<n;i++){
		cin >> a[i];
	}
	for(int i=0;i<n-1;i++){
		int u,v;
		cin >> u >> v;
		adj[u-1].push_back(v-1);
		adj[v-1].push_back(u-1);
	}
	dfs(0);
	while(q--){
		int type,x;
		cin >> type >> x;
		x--;
		if(type == 1){
			cout << subtree_importance[x] << "\n";
			continue;
		}
		if(children[x].size() == 0){
			continue;
		}
		lli x_importance = subtree_importance[x];
		int x_size = subtree_size[x];
		children[parent[x]].erase({-x_size,x});
		
		auto sonx = *children[x].begin();
		children[x].erase(sonx);
		subtree_size[x] -= subtree_size[sonx.second];
		subtree_importance[x] -= subtree_importance[sonx.second];
		
		children[sonx.second].insert({-subtree_size[x],x});
		subtree_size[sonx.second] += subtree_size[x];
		subtree_importance[sonx.second] += subtree_importance[x];
		parent[sonx.second] = parent[x];
		
		children[parent[x]].insert({-subtree_size[sonx.second],sonx.second});
		parent[x] = sonx.second;
		
	}
}



