//https://codeforces.com/problemset/problem/1012/C
// dp
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	int m = (n+1)/2;
	vector<lli> h(n+5,0);
	for(int i=1;i<=n;i++){
		cin >> h[i];
	}		
	vector<vector<vector<lli>>> dp(3,vector<vector<lli>>(m+5,vector<lli>(2,0)));
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int k=0;k<=1;k++){
				if(i==0 || j == 0){
					dp[i%3][j][k] = (j) ? inf_int:0;
					continue;
				}
				//yes
				lli diff = 0;
				if(h[i-1] >= h[i]){
					diff = h[i-1] - (h[i] - 1);
				}
				lli updated_hr = h[i+1];
				if(k){
					updated_hr = min(updated_hr,h[i+2]-1);
				}
				
				if(updated_hr >= h[i]){
					diff += updated_hr - (h[i] -1);
				}
				int index = max(0,i-2);
				lli opt1 = dp[index%3][j-1][1];
				opt1 += diff;
				//no
				
				lli opt2 = dp[(i-1)%3][j][0];
				dp[i%3][j][k] = min(opt1,opt2);
			}
		}
	}
	for(int i=1;i<=m;i++){
		cout << dp[n%3][i][0] << " ";
	}
	cout << "\n";

}
