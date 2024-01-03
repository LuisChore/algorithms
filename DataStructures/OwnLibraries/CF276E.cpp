// https://codeforces.com/contest/276/problem/E
// Multiple ST + Lazy in a Tree

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


// set of ST
vector<vector<lli>> st;
vector<vector<lli>> lazy;
vector<int> st_size;
int numST{0};
vector<int> Map; // st index


// distance ST
vector<lli> dist_st;
vector<lli> dist_lazy;
int dist_st_size{0};


vector<vector<int>> adj;
vector<int> dist;


void update(vector<lli> &ST,vector<lli> &Lazy,int s,int e,lli val,int l,int r,int i=0){
	if(Lazy[i] != 0){
		ST[i] += Lazy[i] * (r-l+1);
		if(l != r){
			Lazy[i*2+1] += Lazy[i];
			Lazy[i*2+2] += Lazy[i];
		} 
		Lazy[i] = 0;
	}
	if(e < l || s > r)
		return;
	if(s<=l && r<=e){
		ST[i] += val * (r-l+1);
		if(l != r){
			Lazy[i*2+1] += val;
			Lazy[i*2+2] += val;
		}
		return;
	}
	int mid = (l + r) >> 1;
	update(ST,Lazy,s,e,val,l,mid,i*2+1);
	update(ST,Lazy,s,e,val,mid+1,r,i*2+2);
	ST[i] = ST[i*2+1] + ST[i*2+2];
}

lli rsq(vector<lli> &ST,vector<lli> &Lazy,int s,int e,int l,int r,int i=0){
  if(Lazy[i] != 0){
	  ST[i] += Lazy[i] * (r-l+1);
		if(l != r){
			Lazy[i*2+1] += Lazy[i];
			Lazy[i*2+2] += Lazy[i];
		} 
		Lazy[i] = 0;
	}
	if(e < l || s > r)
		return 0;
	if(s<=l && r<=e){
		return ST[i];
	}
	int mid = (l + r) >> 1;
	lli L = rsq(ST,Lazy,s,e,l,mid,i*2+1);
	lli R = rsq(ST,Lazy,s,e,mid+1,r,i*2+2);
	return L + R;
}


void process(int u,int d = 0,int st_index = 0){
	dist[u] = d;
	if(dist[u] == 1){
		Map[u] = numST++;
		st.push_back(vector<lli>());
		lazy.push_back(vector<lli>());
		st_size.push_back(0);
	}else{
		Map[u] = st_index;
	}
	for(auto &v: adj[u]){
	  if(dist[v] == -1)
	  	process(v,d+1,Map[u]);
	}
	
	if(adj[u].size() == 1 && u != 0){
		dist_st_size = max(dist_st_size,dist[u]+1);
		st_size[Map[u]] = dist[u];
		st[Map[u]].assign(4*dist[u],0);
		lazy[Map[u]].assign(4*dist[u],0);
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	int n,q;
	cin >> n >> q;
	Map.assign(n,0);
	adj.assign(n,vector<int>());
	dist.assign(n,-1);
	for(int i=0;i<n-1;i++){
		int u,v;
		cin >> u >> v;
		adj[u-1].push_back(v-1);
		adj[v-1].push_back(u-1);
	}
	process(0);
	dist_st.assign(4*dist_st_size,0);
	dist_lazy.assign(4*dist_st_size,0);
	
	while(q--){
		int type;
		cin >> type;
		if(type == 0){
			int v,x,d;
			cin >> v >> x >> d;
			v--;
			if(v == 0){
				int start_query = 0;
				int end_query = min(d,dist_st_size-1);
				update(dist_st,dist_lazy,start_query,end_query,x,0,dist_st_size-1);
			}else if(d >= dist[v]){
				int diff = d - dist[v];
				int start_query = 0;
				int end_query = min(diff,dist_st_size-1);
				update(dist_st,dist_lazy,start_query,end_query,x,0,dist_st_size-1);
				
				start_query = diff;
				end_query = min(dist[v] - 1 + d,st_size[Map[v]]-1);
				if(start_query<=end_query){
					update(st[Map[v]],lazy[Map[v]],start_query,end_query,x,0,st_size[Map[v]]-1);
				}
				
			}else{
				int start_query = dist[v]-1 -d;
				int end_query = min(dist[v]-1 + d,st_size[Map[v]]-1);
				update(st[Map[v]],lazy[Map[v]],start_query,end_query,x,0,st_size[Map[v]]-1);
			}
		}else{
			int v;
			cin >> v;
			v--;
			lli value = (v ? rsq(st[Map[v]],lazy[Map[v]],dist[v]-1,dist[v]-1,0,st_size[Map[v]]-1) : 0);
			lli plus = rsq(dist_st,dist_lazy,dist[v],dist[v],0,dist_st_size-1);
			cout << value + plus << "\n";
		}
	}
}
