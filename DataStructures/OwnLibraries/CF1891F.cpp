//https://codeforces.com/problemset/problem/1891/F
// ST+Lazy on Trees (update subtree) 
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<vector<int>> adj;
vector<int> subtree_size,appears,v;

void dfs(int u){
	subtree_size[u] = 1;
	appears[u] = v.size();
	v.push_back(u);
	for(auto &v:adj[u]){
		dfs(v);
		subtree_size[u] += subtree_size[v];
	}
}

vector<lli> st,lazy;
int n;

void update(int s,int e,lli val,int l=0,int r=n-1,int i=0){
	if(lazy[i] != 0){
		st[i] += (r-l+1) * lazy[i];
		if(l != r){
			lazy[i*2+1] += lazy[i];
			lazy[i*2+2] += lazy[i];
		}
		lazy[i] = 0;
	}
	if(s > r || e < l){
		return;
	}
	if(s<=l && r<=e){
		st[i] += (r-l+1) * val;
		if(l != r){
			lazy[i*2+1] += val;
			lazy[i*2+2] += val;
		}
		return;
	}
	int mid = (l + r) >> 1;
	update(s,e,val,l,mid,i*2+1);
	update(s,e,val,mid+1,r,i*2+2);
	st[i] = st[i*2+1] + st[i*2+2];
}

lli rsq(int s,int e,int l=0,int r=n-1,int i=0){
	if(lazy[i] != 0){
		st[i] += (r-l+1) * lazy[i];
		if(l != r){
			lazy[i*2+1] += lazy[i];
			lazy[i*2+2] += lazy[i];
		}
		lazy[i] = 0;
	}
	if(s > r || e < l){
		return 0;
	}
	if(s<=l && r<=e){
		return st[i];
	}
	int mid = (l + r) >> 1;
	lli L = rsq(s,e,l,mid,i*2+1);
	lli R = rsq(s,e,mid+1,r,i*2+2);
	return L + R;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		vector<pair<int,int>> ops;
		int q,curr = 1;
		cin >> q,
		adj.clear(),
		adj.push_back(vector<int>());
		while(q--){
			int type;
			cin >> type;
			if(type == 2){
				int node,val;
				cin >> node >> val;
				node--;
				ops.push_back({node,val});
			}else{
				ops.push_back({-1,-1});
				int parent;
				cin >> parent;
				parent--;
				adj[parent].push_back(curr++);
				adj.push_back(vector<int>());
			}
		}
		subtree_size.assign(curr,0);
		appears.assign(curr,-1);
		v.clear();
		dfs(0);
		n = v.size();
		st.assign(4*n,0);
		lazy.assign(4*n,0);
		reverse(ops.begin(),ops.end());
		vector<lli> ans(n,0);
		int m = n-1;
		for(auto &qi: ops){
			int u = qi.first;
			lli val = qi.second;
			if(u == -1){
				ans[m] = rsq(appears[m],appears[m]);
				m--;
			}else{
				int l= appears[u];
				int r = l + subtree_size[u] - 1;
				update(l,r,val);
			}
		}
		ans[0] = rsq(0,0);
		for(auto &ai: ans){
			cout << ai << " ";
		}
		cout << "\n";
	}
}
