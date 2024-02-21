//https://codeforces.com/contest/1000/problem/E
// Bridges, graph to tree
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<vector<int>> adj;
vector<int> dfs_num,dfs_low,dfs_parent;
int dfs_counter{};
set<pair<int,int>> bridges;
void dfs1(int u){
	dfs_num[u] = dfs_counter++;
	dfs_low[u] = dfs_num[u];
	for(auto &v:adj[u]){
		if(dfs_num[v] == -1){
			dfs_parent[v] = u;
			dfs1(v);
			if(dfs_low[v] > dfs_low[u]){
				int _u = min(u,v);
				int _v = max(u,v);
				bridges.insert({_u,_v});
			}
			dfs_low[u] = min(dfs_low[u],dfs_low[v]);
		}else if(dfs_parent[u] != v){
			dfs_low[u] = min(dfs_low[u],dfs_num[v]);
		}
	}
}


void dfs3(int u,int cc){
	dfs_low[u] = cc;
	for(auto &v: adj[u]){
		int _u = min(u,v);
		int _v = max(u,v);
		if(bridges.find({_u,_v}) != bridges.end())
			continue;
		if(dfs_low[v] == -1){
			dfs3(v,cc);
		} 
	}
}

int nodes_tree{};

vector<vector<int>> tree;
void dfs2(int u){
	dfs_num[u] = 1;
	for(auto &v:adj[u]){
		if(dfs_num[v] == -1){
			if(dfs_low[u] != dfs_low[v]){
				tree[dfs_low[u]].push_back(dfs_low[v]);
				tree[dfs_low[v]].push_back(dfs_low[u]);
			}
			dfs2(v);
		}
	}
}

pair<int,int> bfs(int source){
	dfs_num.assign(nodes_tree,-1);
	queue<int> Q;
	Q.push(source);
	dfs_num[source] = 0;
	pair<int,int> ans{0,source};
	while(Q.size()){
		int u = Q.front();
		Q.pop();
		for(auto &v:tree[u]){
			if(dfs_num[v] == -1){
				dfs_num[v] = dfs_num[u] + 1;
				if(dfs_num[v] > ans.first){
					ans = {dfs_num[v],v};
				}
				Q.push(v);
			}
		}
	}
	return ans;
}
int main(){
	cin.sync_with_stdio(0);cin.tie(0);
	int n,m;
	cin >> n >> m;
	adj.assign(n,vector<int>());
	dfs_num.assign(n,-1);
	dfs_low.assign(n,-1);
	dfs_parent.assign(n,-1);
	while(m--){
		int u,v;
		cin >> u >> v;
		adj[u-1].push_back(v-1);
		adj[v-1].push_back(u-1);
	}
	dfs1(0);
	dfs_low.assign(n,-1);
	for(int i=0;i<n;i++){
		if(dfs_low[i] == -1){
			dfs3(i,nodes_tree);
			nodes_tree++;
		}
	}
	dfs_num.assign(n,-1);
	tree.assign(nodes_tree,vector<int>());
	dfs2(0);
	
	auto aux = bfs(0);
	aux = bfs(aux.second);
	cout << aux.first << "\n";
	
}
