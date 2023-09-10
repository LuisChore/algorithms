#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

lli n,k;
vector<vector<int>> next_index;
vector<vector<lli>> dp;
lli f(int index,int _size){
	if(_size == 0)
		return 1;
	if(index > n)
		return 0;
	if(dp[index][_size] != -1)
		return dp[index][_size];
	lli ans = 0;
	for(int c=0;c<26;c++){
		int res = (next_index[index][c] != n+1) ? 1:0;
		ans += f(next_index[index][c],_size-res);
	}
	return dp[index][_size] = ans;
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	string s;
	cin >> n >> k;
	cin >> s;
	s = "0" + s;
	next_index.assign(n+1,vector<int>(26,n+1));
	vector<int> last_seen(26,n+1);
	dp.assign(n+1,vector<lli>(n+1,-1));
	for(int i=n;i>=0;i--){
		for(int j=0;j<26;j++){
			next_index[i][j] = last_seen[j];
		}
		if(i)
			last_seen[s[i]-'a'] = i;
	}
	if(k == 1){
		cout << 0 << "\n";
		return 0;
	}
	k--;
	lli ans = 0;
	lli curr_size = n - 1;
	while(k && curr_size){
		lli aux = f(0,curr_size);
		lli m = min(aux,k);
		ans += (n-curr_size) * m;
		curr_size--;
		k-=m;
	}
	if(k>1){
		cout << "-1\n";
	}else if(k == 1){
		cout << ans + n << "\n";
	}else{
		cout << ans << "\n";
	}
	return 0;
}



