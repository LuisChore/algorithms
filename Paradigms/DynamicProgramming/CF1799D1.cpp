//https://codeforces.com/problemset/problem/1799/D1
// dp easy
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<lli> cold,hot;
vector<vector<lli>> dp;
vector<int> v;

lli f(int last_a,int last_b){
	int next_one = max(last_a,last_b) + 1;
	if(next_one == v.size())
		return 0;
	if(dp[last_a][last_b] != -1)
		return dp[last_a][last_b];
	lli c_a = (v[next_one] == v[last_a]) ? hot[v[next_one]] : cold[v[next_one]];
	lli c_b = (v[next_one] == v[last_b]) ? hot[v[next_one]] : cold[v[next_one]];
	lli opt_a = f(next_one,last_b) + c_a;
	lli opt_b = f(last_a,next_one) + c_b;
	return dp[last_a][last_b] = min(opt_a,opt_b);
	
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		lli n,k;
		cin >> n >> k;
		dp.assign(n+1,vector<lli>(n+1,-1));
		v.assign(n+1,0);
		cold.assign(k+1,0);
		hot.assign(k+1,0);
		for(int i=1;i<=n;i++)
			cin >> v[i];
		for(int i=1;i<=k;i++)
			cin >> cold[i];
		for(int i=1;i<=k;i++)
			cin >> hot[i];
		lli ans = f(1,0) + cold[v[1]];
		cout << ans << "\n";
	}
}
