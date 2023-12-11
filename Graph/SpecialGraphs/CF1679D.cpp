//dp dag + binary search

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<vector<int>> adj;
vector<int> visited;
vector<int> dp;
vector<int> vertex_w;



bool find_cycle(int u,int max_value){
	visited[u] = 1; // explored
	bool found = false;
	for(auto &v: adj[u]){
		if(visited[v] == 0 && vertex_w[v]<=max_value){
			found = found || find_cycle(v,max_value);
		}else if(visited[v] == 1){
			found = true;
		}
	}
	visited[u] = 2; // visited
	return found;
}

bool find_cycle(int max_value){
	visited.assign(adj.size(),0); // unvisited
	for(int i=0;i<adj.size();i++){
		if(vertex_w[i] <= max_value && visited[i] == 0){
			bool cycle = find_cycle(i,max_value);
			if(cycle)
				return true;
		}
	}
	return false;
}

int f(int u,int max_value){
	if(dp[u] != -1)
		return dp[u];
	int ans = 1;
	for(auto &v: adj[u]){
		if(vertex_w[v] <= max_value){
			ans = max(ans,1 + f(v,max_value));
		}
	}
	return dp[u] = ans;
}

int longest_vertex_path(int max_value){
	dp.assign(adj.size(),-1);
	int ans = 0;
	for(int i=0;i<adj.size();i++){
		if(vertex_w[i] <= max_value){
			ans = max(ans,f(i,max_value));
		}
	}
	return ans;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	lli n,m,k;
	cin >> n >> m >> k;
	adj.assign(n,vector<int>());
	vertex_w.assign(n,0);
	vector<int> vertexw_sorted(n);
	for(int i=0;i<n;i++){
		cin >> vertex_w[i];
		vertexw_sorted[i] = vertex_w[i];
	}
	for(int i=0;i<m;i++){
		int u,v;
		cin >> u >> v;
		adj[u-1].push_back(v-1);
	}
	sort(vertexw_sorted.begin(),vertexw_sorted.end());
	int low = 0,high = n-1,ans = -1;
	while(low<=high){
		int mid = (low + high) >> 1;
		int mid_value = vertexw_sorted[mid];
		if(find_cycle(mid_value)){
			ans = mid_value;
			high = mid - 1;
		}else{
			int ki = longest_vertex_path(mid_value);
			if(ki >= k){
				ans = mid_value;
				high = mid - 1;
			}else{
				low = mid + 1;
			}
		}
	}
	cout << ans << "\n";
}
