// https://codeforces.com/problemset/problem/1198/D
// DP Reference
/*
 Min cost dp in a grid
 Just split by rectangles
*/


#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


vector<vector<vector<vector<int>>>> dp;
vector<vector<int>> grid;

int get_sum(int i1,int j1,int i2,int j2){
	int total = grid[i2][j2];
	if(i1) total -= grid[i1-1][j2];
	if(j1) total -= grid[i2][j1-1];
	if(i1 && j1) total += grid[i1-1][j1-1];
	return total;
}

int f(int i1,int j1,int i2,int j2){
	if(i1 == i2 && j1 == j2){
		return get_sum(i1,j1,i2,j2);
	}
	if(dp[i1][j1][i2][j2] != -1)
		return dp[i1][j1][i2][j2];
	int ans = max(i2-i1+1,j2-j1+1);
	for(int i=i1;i<=i2;i++){
		int sumi = get_sum(i,j1,i,j2);
		if(sumi == 0){
			int up = (i>i1) ? f(i1,j1,i-1,j2) : 0;
			int down = (i<i2) ? f(i+1,j1,i2,j2) : 0;
			ans = min(ans,up + down);
		}
	}
	
	for(int j=j1;j<=j2;j++){
		int sumj = get_sum(i1,j,i2,j);
		if(sumj==0){
			int left = (j > j1) ?f(i1,j1,i2,j-1) : 0;
			int rigth = (j < j2) ?f(i1,j+1,i2,j2) : 0;
			ans = min(ans,left + rigth);
		}
	}
	return dp[i1][j1][i2][j2] = ans;
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	string s;
	
	grid.assign(n,vector<int>(n,0));
	for(int i=0;i<n;i++){
		cin >> s;
		for(int j=0;j<s.size();j++){
			grid[i][j] = (s[j] == '#') ? 1: 0;
			if(j)grid[i][j] += grid[i][j-1];
			if(i)grid[i][j] += grid[i-1][j];
			if(i && j) grid[i][j] -= grid[i-1][j-1];
		}
	}
	dp.assign(n,vector<vector<vector<int>>>
			 (n,vector<vector<int>>
			 (n,vector<int>
			 (n,-1))));
			 
	 int ans = f(0,0,n-1,n-1);
	 cout << ans << "\n";
}






















