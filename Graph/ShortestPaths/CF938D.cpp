// https://codeforces.com/problemset/problem/938/D
// DIJKSTRA
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<vector<pair<lli,lli>>> adj;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin >> n >> m;
	adj.assign(n,vector<pair<lli,lli>>());
	vector<lli> dist(n,0);
	while(m--){
		lli u,v,w;
		cin >> u >> v >> w;
		u--;
		v--;
		adj[u].push_back({v,w});
		adj[v].push_back({u,w});
	}
	for(int i=0;i<n;i++){
		cin >> dist[i];
	}
	set<pair<lli,int>> pq;
	for(int i=0;i<n;i++){
		pq.emplace(dist[i],i);
	}
	
	while(!pq.empty()){
		auto [d,u] = *pq.begin();
		pq.erase(pq.begin());
		for(auto &[v,w]: adj[u]){
			if(dist[u] + 2*w >= dist[v])
				continue;
			pq.erase(pq.find({dist[v],v}));
			dist[v] = dist[u] + 2*w;
			pq.emplace(dist[v],v);
		}
	}
	for(int i=0;i<n;i++){
		cout << dist[i] << " ";
	}
	cout << "\n";
	
}
