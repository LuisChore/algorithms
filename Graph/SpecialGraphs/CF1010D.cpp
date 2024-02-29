//https://codeforces.com/problemset/problem/1010/D
// Tree

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<vector<int>> tree;
vector<string>operation;
vector<int> output,ans;

void compute_output(int u){
	int ch = operation[u][0];
	if(ch == 'I'){
		return;
	}
	if(ch == 'A'){
		compute_output(tree[u][0]);
		compute_output(tree[u][1]);
		output[u] = output[tree[u][0]] & output[tree[u][1]]; 
	}
	
	if(ch == 'O'){
		compute_output(tree[u][0]);
		compute_output(tree[u][1]);
		output[u] = output[tree[u][0]] | output[tree[u][1]]; 
	}
	
	
	if(ch == 'X'){
		compute_output(tree[u][0]);
		compute_output(tree[u][1]);
		output[u] = output[tree[u][0]] ^ output[tree[u][1]]; 
	}
	
	if(ch == 'N'){
		compute_output(tree[u][0]);
		output[u] = 1 - output[tree[u][0]];
	}
	
	
}

void solve(int u){
	int ch = operation[u][0];
	if(ch == 'I'){
		ans[u] = 1 - output[0];
		return;
	}
	if(ch == 'A'){
		int a = output[tree[u][0]];
		int b = output[tree[u][1]];
		if(!a && !b){
			return;
		}
		if(a && b){
			solve(tree[u][0]);
			solve(tree[u][1]);
			return;
		}
		if(a && !b){
			solve(tree[u][1]);
		}
		if(!a && b){
			solve(tree[u][0]);
		}
	}
	
	
	if(ch == 'O'){
		int a = output[tree[u][0]];
		int b = output[tree[u][1]];
		if(!a && !b){
			solve(tree[u][0]);
			solve(tree[u][1]);
		}
		if(a && b){
			return;
		}
		if(a && !b){
			solve(tree[u][0]);
		}
		if(!a && b){
			solve(tree[u][1]);
		}
	}
	
	if(ch == 'X'){
		solve(tree[u][0]);
		solve(tree[u][1]);
	}
	
	
	if(ch == 'N'){
		solve(tree[u][0]);
	}
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	tree.assign(n,vector<int>());
	operation.assign(n,"");
	output.assign(n,0);
	
	for(int i=0;i<n;i++){
		cin >>operation[i];
		if(operation[i][0] == 'I'){
			cin >>output[i];
		}else if(operation[i][0] == 'A' || operation[i][0] == 'X' || operation[i][0] == 'O'){
			int v1,v2;
			cin >> v1 >> v2;
			v1--;
			v2--;
			tree[i].push_back(v1);
			tree[i].push_back(v2);
		}else{
			int v;
			cin >> v;
			v--;
			tree[i].push_back(v);
		}
	}
	
	compute_output(0);
	ans.assign(n,output[0]);
	solve(0);
	for(int i=0;i<n;i++){
		if(operation[i][0] == 'I'){
			cout << ans[i];
		}
	}
	cout << "\n";
}
