#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<int> a,ans;
vector<vector<int>> adj;
bool is_odd(int val){
	return (val&1);
}

bool is_even(int val){
	return (val%2 == 0);
}
void bfs(function<bool(int)> func){
	int n = a.size();
	vector<int> dist(n,inf_int);
	queue<int> Q;
	for(int i=0;i<n;i++){
		if(func(a[i])){
			Q.push(i);
			dist[i] = 0;
		}
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
	for(int i=0;i<n;i++){
		if(func(a[i]) == false && dist[i] != inf_int){
			ans[i] = dist[i];
		}
	}
}
void create_graph(){
	int n = a.size();
	for(int i=0;i<n;i++){
		int l = i - a[i],r = i + a[i];
		if(l>=0){
			adj[l].push_back(i);
		}
		if(r<a.size()){
			adj[r].push_back(i);
		}
	}
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	a.assign(n,0);
	ans.assign(n,-1);
	adj.assign(n,vector<int>());
	for(int i=0;i<n;i++){
		cin >> a[i];
	}
	create_graph();
	bfs(is_even);
	bfs(is_odd);
	for(auto &ai:ans){
		cout << ai << " ";
		
	}
	cout << "\n";
	
	return 0;
}


