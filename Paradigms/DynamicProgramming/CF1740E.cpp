// https://codeforces.com/problemset/problem/1740/E
// dp on tree

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<vector<int>> adj;
vector<int> dp,largest;

void dfs(int u){
	largest[u] = 1;
	for(auto &v:adj[u]){
		dfs(v);
		largest[u] = max(largest[u],1 + largest[v]);
	}
}

void dfs2(int u){
	dp[u] = largest[u];
	int sum = 0;
	for(auto &v:adj[u]){
		dfs2(v);
		sum += dp[v];
	}
	dp[u] = max(dp[u],sum);
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	adj.assign(n,vector<int>());
	dp.assign(n,0);
	largest.assign(n,0);
	for(int i=1;i<n;i++){
		int v;
		cin >> v;
		v--;
		adj[v].push_back(i);
	}
	dfs(0);
	dfs2(0);
	cout << dp[0] << "\n";
}
