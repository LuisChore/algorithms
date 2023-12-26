//https://codeforces.com/problemset/problem/1027/D
// SCC TO DAG

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


vector<vector<int>> adj;
vector<int> cost;
vector<int> min_cost;
vector<int> out_degree; // problem
//SCC
vector<int> visited,dfs_num,dfs_low;
stack<int> Stack;
int SCC{0},dfs_count{0};
vector<int> belongs_to;
void find_scc(int u){
	dfs_num[u] = dfs_count++;
	dfs_low[u] = dfs_num[u];
	visited[u] = true;
	Stack.push(u);
	for(auto &v:adj[u]){
		if(dfs_num[v] == -1){
			find_scc(v);
		}
		if(visited[v]){
			dfs_low[u] = min(dfs_low[u],dfs_low[v]);
		}
	}
	if(dfs_num[u] == dfs_low[u]){
		int min_cost_value = inf_int; // problem
		while(1){
			int v = Stack.top();
			Stack.pop();
			belongs_to[v] = SCC;
			visited[v] = false;
			min_cost_value = min(min_cost_value,cost[v]);// problem
			if(u == v)
				break;
		}
		min_cost.push_back(min_cost_value); // problem
		SCC++;
	}
}


// SCC TO DAG
vector<vector<int>> dag;
set<pair<int,int>> edges;
void scc_to_dag(int u){
	visited[u] = 1;
	int U = belongs_to[u];
	for(auto &v:adj[u]){
		int V = belongs_to[v];
		if(visited[v] == -1){
			if(U != V && edges.find({U,V})==edges.end() ){
				dag[U].push_back(V);
				out_degree[U]++;
				edges.insert({U,V});
			}
			scc_to_dag(v);
		}else if(visited[v] == 2){
			if(U != V && edges.find({U,V})==edges.end() ){
				dag[U].push_back(V);
				out_degree[U]++;
				edges.insert({U,V});
			}
		}
	}
	visited[u] = 2;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	cost.assign(n,0);
	visited.assign(n,0);
	belongs_to.assign(n,0);
	adj.assign(n,vector<int>());
	dfs_num.assign(n,-1);
	dfs_low.assign(n,-1);
	for(int i=0;i<n;i++){
		cin >> cost[i];
	}
	for(int i=0;i<n;i++){
		int u = i,v;
		cin >> v;
		v--;
		if(u != v)
			adj[u].push_back(v);
	}
	for(int i=0;i<n;i++){
		if(dfs_num[i] == -1)
			find_scc(i);
	}
	
	dag.assign(SCC,vector<int>());
	visited.assign(n,-1);
	out_degree.assign(SCC,0);
	for(int i=0;i<n;i++){
		if(visited[i] == -1)
			scc_to_dag(i);
	}
	lli ans = 0;
	for(int i=0;i<SCC;i++){
		if(out_degree[i] == 0){
			ans+= min_cost[i];
		}
	}
	cout << ans << "\n";
	
}
