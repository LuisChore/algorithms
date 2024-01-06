// https://codeforces.com/problemset/problem/1611/E2
// BFS multisource

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		int n,k;
		cin >> n >> k;
		vector<int> dist(n,inf_int);
		vector<vector<int>> adj(n,vector<int>());
		queue<int> Q;
		for(int i=0;i<k;i++){
			int u;
			cin >> u;
			Q.push(u-1);
			dist[u-1] = 0;
		}
		
		for(int i=0;i<n-1;i++){
			int u,v;
			cin >> u >> v;
			adj[u-1].push_back(v-1);
			adj[v-1].push_back(u-1);
		}
		
		while(Q.size()){
			int u = Q.front();
			Q.pop();
			for(auto &v:adj[u]){
				if(dist[v] > dist[u] + 1){
					dist[v] = dist[u] + 1;
					Q.push(v);
				}
			}
		}
		
		vector<int> dist_1(n,inf_int);
		Q.push(0);
		dist_1[0] = 0;
		int ans = 0;
		while(Q.size() && ans >= 0){
			int u = Q.front();
			Q.pop();
			for(auto &v:adj[u]){
				if(dist_1[v] > dist_1[u] + 1){
					dist_1[v] = dist_1[u] + 1;
					//check
					if(dist[v] <= dist_1[v]){
						ans++;
					}else if(adj[v].size() == 1){
						ans = -1;
						break;
					}else{
						Q.push(v);
					}
				}
			}		
		}
		cout << ans << "\n";
	}
}
