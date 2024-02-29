//https://codeforces.com/contest/1702/problem/G2
// LCA 

#include <bits/stdc++.h>

#define lowBit(S) (S & (-S))
#define isPowerOfTwo(S) (!(S & (S-1)))

using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<int> parent;
vector<vector<int>> adj;
vector<int> dist;
vector<int> vis;

void dfs(int u,int d = 0){
	vis[u] = true;
	dist[u] = d;
	for(auto &v:adj[u])	{
		if(!vis[v]){
			parent[v] = u;
			dfs(v,dist[u] + 1);
		}
	}
}

auto process_kth(vector<int> &parent){
	int n = parent.size();
	int h = 18;
	vector<vector<int>> kth(n,vector<int>(h+1,-1));
	for(int k=0;k<=h;k++){
		for(int i=0;i<n;i++){
			if(k == 0){
				kth[i][k] = parent[i];
			}else{
				kth[i][k] = (kth[i][k-1] != -1)?kth[kth[i][k-1]][k-1] : -1;
			}
		}
	}
	return kth;
}

int get_kth(int u,int k,vector<vector<int>> &kth){
	int n = parent.size();
	int h = 18;
	for(int i=0;i<=h;i++){
		if(k& (1<<i))
			u = kth[u][i];
		if(u == -1)
			break;
	}
	return u;
}

int lca(int u,int v,vector<vector<int>> &kth){
	if(dist[u] > dist[v])
		swap(u,v);
	int diff =  dist[v] - dist[u];
	v = get_kth(v,diff,kth);
	
	if(u == v)
		return u;
	int n = kth.size();
	int low = 0,high = n,ans = -1;
	while(low<=high){
		int mid = (low + high) >> 1;
		int ku = get_kth(u,mid,kth);
		int kv = get_kth(v,mid,kth);
		if(ku == kv){
			ans = ku;
			high = mid - 1;
		}else{
			low = mid + 1;
		}
	}
	return ans;
}


int solve_with_root(int root,int index,vector<int> &path,int u,int v,vector<vector<int>> &kth){
	if(lca(u,v,kth) != root)
		return -1;
	int ok = 1;
	for(int i=index;i<path.size();i++){
		int diff_u = dist[path[i]] - dist[u];
		int diff_v = dist[path[i]] - dist[v];
		if(get_kth(path[i],diff_u,kth) == u){
			u = path[i];
		}else if(get_kth(path[i],diff_v,kth) == v){
			v = path[i];
		}else{
			ok = -2;
			break;
		}
	}
	return ok;	
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	adj.assign(n,vector<int>());
	for(int i=0;i<n-1;i++){
		int u,v;
		cin >> u >> v;
		adj[u-1].push_back(v-1);
		adj[v-1].push_back(u-1);
	}
	vis.assign(n,0);
	parent.assign(n,-1);
	dist.assign(n,-1);
	dfs(0);
	auto kth = process_kth(parent);
	int q;
	cin >> q;
	while(q--){
		int k;
		cin >> k;
		vector<int> path(k);
		for(int i=0;i<k;i++){
			cin >> path[i];
			path[i]--;
		}
    	sort(path.begin(), path.end(), [](int i, int j) { return dist[i] < dist[j]; });
    	
    	int ok = 1;
    	int u = path[0];
    	for(int i=1;i<path.size();i++){
    		int diff_u = dist[path[i]] - dist[u];
    		if(get_kth(path[i],diff_u,kth) == u){
    			u = path[i];
    		}else{
    			ok = solve_with_root(lca(path[i],path[0],kth),i+1,path,u,path[i],kth);
    			break;
    		}
    	}
    	if(ok == 1)cout << "YES\n";
    	else if(ok == -1) cout << "NO\n";
    	else cout << "No\n";
  
	}
	
}
