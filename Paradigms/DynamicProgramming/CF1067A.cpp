//https://codeforces.com/contest/1067/submission/250259520

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

const lli mod = 998244353;
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i=0;i<n;i++){
		cin >> a[i];
	}
	vector<vector<vector<int>>> dp(5,vector<vector<int>>(210,vector<int>(5,0)));
	int offset = 1;
	for(int i=0;i<n-1;i++){
		for(int k=-1;k<=1;k++){
			int ini = (k <= 0) ? 1 : 200;
			int end = (k<=0) ? 201 : 0;
			int diff = (k <= 0) ? 1: -1;
			for(int j=ini;j!=end;j+=diff){
				dp[i&1][j][k + offset] = 0;
				if(i == 0){
					if(a[i] != -1){
						if(k == 0){
							dp[i&1][j][k + offset] = (j == a[i]);
							
						}else if (k < 0){
							dp[i&1][j][k + offset] = (j >= a[i]);
							
						}
					}else{
						if(k == 0){
							dp[i&1][j][k + offset] = 1;
						}else if(k<0){
							dp[i&1][j][k + offset] = j;
						}
					}
					continue;
				}
	
				if(a[i] != -1){
					if(k == 0){
						if(j == a[i]){
							lli aux1 = dp[(i-1)&1][j][0 + offset];
							lli aux2 = (j < 200) ? dp[(i-1)&1][j+1][1 + offset] : 0;
							lli aux3 = (j > 1) ? dp[(i-1)&1][j-1][-1 + offset]: 0;
							lli ans = (aux1 + aux2 + aux3) % mod;
							dp[i&1][j][k + offset] = ans;
						}
					}else if(k == 1){
						if(j<=a[i]){
							lli aux1 = dp[(i-1)&1][a[i]][0 + offset];
							lli aux2 = (a[i] < 200) ? dp[(i-1)&1][a[i] + 1][1 + offset] : 0;
							lli ans = (aux1 + aux2) %mod;
							dp[i&1][j][k + offset] = ans;
						}
					}else if(k == -1){
						if(j >= a[i]){
							lli aux1 = dp[(i-1)&1][a[i]][0 + offset];
							lli aux2 = (a[i] < 200) ? dp[(i-1)&1][a[i] + 1][1 + offset] : 0;
							lli aux3 = (a[i] > 1) ? dp[(i-1)&1][a[i] - 1][-1 + offset] : 0;
							lli ans = (aux1 + aux2 + aux3) %mod;
							dp[i&1][j][k + offset] = ans;
						}
					}
					continue;
				}
				
				if(k == 0){
					lli aux1 = dp[(i-1)&1][j][0 + offset];
					lli aux2 = (j < 200) ? dp[(i-1)&1][j+1][1 + offset] : 0;
					lli aux3 = (j > 1) ? dp[(i-1)&1][j-1][-1 + offset]: 0;
					lli ans = (aux1 + aux2 + aux3) % mod;
					dp[i&1][j][k + offset] = ans;
				}else if(k == 1){
					lli aux1 = dp[(i-1)&1][j][0 + offset];
					lli aux2 = (j < 200) ? dp[(i-1)&1][j + 1][1 + offset] : 0;
					lli aux3 = (j < 200) ? dp[i&1][j + 1][1 + offset]: 0;
					lli ans = (aux1 + aux2 + aux3 ) % mod;
					dp[i&1][j][k + offset] = ans;
				}else if(k == -1){
					lli aux1 = dp[(i-1)&1][j][0 + offset];
					lli aux2 = (j < 200) ? dp[(i-1)&1][j + 1][1 + offset] : 0;
					lli aux3 = (j > 1) ? dp[(i-1)&1][j - 1][-1 + offset] : 0;
					lli aux4 = (j > 1) ? dp[i&1][j-1][-1 + offset] : 0;
					lli ans = (aux1 + aux2 + aux3) %mod;
					ans = (ans + aux4) %mod;
					dp[i&1][j][k + offset] = ans;		
				}
			}
		}
	}
	lli ans = 0;
	for(int i=1;i<=200;i++){
		if(a[n-1] == -1){
			lli aux1 = dp[(n-2)&1][i][0 + offset];
			lli aux2 = (i<200) ? dp[(n-2)&1][i+1][1 + offset]:0;
			lli ans_temp = (aux1 + aux2) %mod;
			ans = (ans + ans_temp) %mod;
		}else if(i == a[n-1]){
			lli aux1 = dp[(n-2)&1][i][0 + offset];
			lli aux2 = (i<200) ? dp[(n-2)&1][i+1][1 + offset]:0;
			lli ans_temp = (aux1 + aux2)%mod;
			ans = (ans_temp + ans) %mod;
		}
	}
	cout << ans << "\n";
}
