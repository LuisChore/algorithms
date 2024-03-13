//https://codeforces.com/contest/1619/problem/D
// Binary Search on Answer

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		int m,n;
		cin >> m >> n;
		vector<vector<lli>> friends(n,vector<lli>());
		vector<vector<lli>> stores(m,vector<lli>(n,0));
		set<pair<lli,int>> bests;
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				cin >> stores[i][j];
				friends[j].push_back(stores[i][j]);
			}
		}
		for(int j=0;j<n;j++){
			sort(friends[j].begin(),friends[j].end());
			bests.insert({friends[j].back(),j});
		}
		for(int i=0;i<m;i++){
			sort(stores[i].begin(),stores[i].end());
		}
		
		if(m < n){
			cout << (bests.begin()->first) << "\n";
			continue;
		}
		
		
		lli low = 0,high = (bests.begin()->first),ans = 0;
		while(low<=high){
			lli mid = (low + high) >> 1;
			bool ok = false;
			for(int i=0;i<m;i++){
				if(stores[i][n-2] >= mid){
					ok = true;
					break;
				}
			}
			if(ok){
				ans = mid;
				low = mid + 1;
			}else{
				high = mid - 1;
			}
		}
		cout << ans << "\n";
	}
}
