//https://codeforces.com/problemset/problem/1433/F
// dp classic
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n,m,mod;
	cin >> n >> m >> mod;
	vector<vector<int>> grid(n,vector<int>(m,0));
	vector<vector<vector<lli>>> dp(2,vector<vector<lli>>(mod+1,vector<lli>(m,-1)));
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin >> grid[i][j];
		}
	}
	for(int i=0;i<=n*m;i++){
		for(int j=0;j<mod;j++){
			for(int k=0;k<=m/2;k++){
				if(i==0){
					dp[i&1][j][k] = (j == 0) ? 0 : -inf;
					continue;
				}
				int val= i - 1;
				int r = val/m;
				int c = val%m;
				int next_k = (c > 0) ? k : m/2;
				lli opt1 = dp[(i-1)&1][j][next_k];
				lli opt2 = -inf;
				if(k){
					next_k = (c > 0) ? (k - 1) : m/2;
					int next_j = (j + grid[r][c]) % mod;
					opt2 = dp[(i-1)&1][next_j][next_k] + grid[r][c];
				}
				dp[i&1][j][k] = max(opt1,opt2);
			}
		}
	}
	cout << dp[(n*m)&1][0][m/2] << "\n";
}
