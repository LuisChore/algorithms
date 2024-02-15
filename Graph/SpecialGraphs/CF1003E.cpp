// https://codeforces.com/problemset/problem/1003/E
// tree construction with constraints

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

lli n,d,k,curr_nodes = 0;
vector<pair<int,int>> edges;
vector<vector<int>> adj;
vector<lli> degrees;
vector<lli> level;

void dfs(int u,int missing){
	int rest = k - degrees[u];
	for(int i=0;i<rest && curr_nodes<n;i++){
		int v = curr_nodes;
		adj[u].push_back(v);
		edges.push_back({u+1,v+1});
		degrees[u]++;
		degrees[v]++;
		curr_nodes++;
		if(curr_nodes == n)
			break;
		if(missing -1 > 0 && k > degrees[v]){
			dfs(v,missing-1);
		}	
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> d >> k;
	degrees.assign(n,0);
	level.assign(n,0);
	adj.assign(n,vector<int>());
	if(n <= d){
		cout << "NO\n";
		return 0;
	}
	
	level[0] = 0;
	for(int i=1;i<=d;i++){
		adj[i-1].push_back(i);
		degrees[i-1]++;
		degrees[i]++;
		level[i] = i;
		edges.push_back({i,i+1});
	}
	curr_nodes = d+1;	
	for(int i=1;i<d && curr_nodes < n;i++){
		int length = max(level[i],d-level[i]);
		if(degrees[i] < k){
			dfs(i,d-length);
		}
	}
	auto val = *max_element(degrees.begin(),degrees.end());
	if(curr_nodes != n || val > k){
		cout << "NO\n";
	}else{
		cout << "YES\n";
		for(auto &e:edges){
			cout << e.first << " " << e.second << "\n";
		}
	}
	
}
