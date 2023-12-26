//https://codeforces.com/problemset/problem/682/D
// dp + strings

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


string s,t;
vector<vector<vector<vector<int>>>> dp;

int f(int i,int j,int k,int flag){
	if(!i || !j || !k){
		if(k)return -inf_int;
		return 0;
	}
	if(dp[i][j][k][flag] != -1)
		return dp[i][j][k][flag];
	if(flag){
		int opt1,opt2;
		opt1 = opt2 = -inf_int;
		if(s[i] == t[j]){
			opt1 = f(i-1,j-1,k,true) + 1;
			opt2 = f(i-1,j-1,k-1,false) + 1;
		}
		return dp[i][j][k][flag] = max(opt1,opt2);
	}
	int opt1 = f(i-1,j,k,false);
	int opt2 = f(i,j-1,k,false);
	int ans = max(opt1,opt2);
	if(s[i] == t[j]){
		int opt = f(i,j,k,true);
		ans = max(ans,opt);
	}
	return dp[i][j][k][flag] = ans;
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n,m,o;
	cin >> n >> m >> o;
	dp.assign(2,vector<vector<vector<int>>>
			 (m+2,vector<vector<int>>
			 (o+1,vector<int>
			 (2,-1))));
	 cin >> s >> t;
	 s = "x" + s;
	 t = "x" + t;
	 for(int i=0;i<=n;i++){
	 	for(int j=0;j<=m;j++){
	 		for(int k=0;k<=o;k++){
	 			for(int l=1;l>=0;l--){
	 				if(!i || !j || !k){
	 					dp[i&1][j][k][l] = k!=0 ? -inf_int : 0;
	 					continue;
	 				}
	 				if(l){
						int opt1,opt2;
						opt1 = opt2 = -inf_int;
						if(s[i] == t[j]){
							opt1 = dp[(i-1)&1][j-1][k][1] + 1;
							opt2 = dp[(i-1)&1][j-1][k-1][0] + 1;
						}
						dp[i&1][j][k][l] = max(opt1,opt2);
						continue;
					}
					int opt1 = dp[(i-1)&1][j][k][0];
					int opt2 = dp[i&1][j-1][k][0];
					int ans = max(opt1,opt2);
					if(s[i] == t[j]){
						int opt = dp[i&1][j][k][1];
						ans = max(ans,opt);
					}
					dp[i&1][j][k][l] = ans;
	 			}
	 		}
	 	}
	 }
	 cout << dp[n&1][m][o][0] << "\n";
	 return 0;
}
