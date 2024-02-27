//https://codeforces.com/problemset/problem/1005/F
// BFS finding paths
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<vector<int>> adj;
map<pair<int,int>,int> Index;
vector<lli> dist,nodes;
vector<string> answers;
int paths = 0;

bool f(int i,int j){
	return dist[i] > dist[j];
}

void solve(int index,string &ans){
	if(paths == 0)
		return;
	if(nodes[index] == 0){
		answers.push_back(ans);
		paths--;
		return;
	}
	int u= nodes[index];
	for(auto &v:adj[u]){
		int m = min(u,v);
		int M = max(u,v);
		int e = Index[{m,M}];
		if(dist[v] < dist[u]){
			ans[e] = '1';
			solve(index + 1,ans);
			ans[e] = '0';
		}
	}
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n,m,k;
	cin >> n >> m >> k;
	adj.assign(n,vector<int>());
	for(int i=0;i<m;i++){
		int u,v;
		cin >> u >> v;
		u--;
		v--;
		int m = min(u,v);
		int M = max(u,v);
		Index[{m,M}] = i;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dist.assign(n,inf_int);
	queue<int> Q;
	Q.push(0);
	dist[0] = 0;
	while(Q.size()){
		int u = Q.front();
		Q.pop();
		for(auto &v:adj[u]){
			if(dist[v] ==  inf_int){
				dist[v] = dist[u] + 1;
				Q.push(v);
			}
		}
	}
	nodes.assign(n,0);
	iota(nodes.begin(),nodes.end(),0);
	sort(nodes.begin(),nodes.end(),f);
	string ans = "";
	for(int i=0;i<m;i++)
		ans += "0";
		
	paths = k;
	solve(0,ans);
	cout << answers.size() << "\n";
	for(auto &ai: answers){
		cout << ai << "\n";
	}
	
	
}
