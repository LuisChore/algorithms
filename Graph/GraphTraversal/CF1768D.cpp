// https://codeforces.com/problemset/problem/1768/D
// array inversions dsu check

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<int> vis,val;

int dfs(int u,int color){
	if(vis[u] != -1)
		return 0;
	vis[u] = color;
	if(val[u] == u)
		return 1;
	return 1 + dfs(val[u],color);
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		int n;
		cin >> n;
		val.assign(n+1,0);
		vis.assign(n+1,-1);
		for(int i=1;i<=n;i++){
			cin >> val[i];
		}
		int cc = 1;
		lli ans = 0;
		for(int i=1;i<=n;i++){
			if(vis[i] == -1){
				ans += (dfs(i,cc)-1);
				cc++;
			}
		}
		bool found = false;
		for(int i=1;i<=n-1;i++){
			if(vis[i] == vis[i+1])
				found = true;
		}
		if(found)
			ans--;
		else
			ans++;
		cout << ans << "\n";
		
	}
}
