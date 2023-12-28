//https://codeforces.com/contest/1801/problem/C
// dp + greedy

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<int> endpoints;
vector<vector<int>> vi;
vector<vector<int>> adj;
map<int,vector<int>> indexes;
vector<int> dp;
int get_next(int val){
	int low = 0,high = endpoints.size()-1,ans = high;
	while(low<=high){
		int mid = (low + high) >> 1;
		if(endpoints[mid] < val){
			ans = mid;
			low = mid + 1;
		}else{
			high = mid - 1;
		}
	}
	return ans;
}

int f(int ind){
	if(ind == 0)
		return 0;
	if(dp[ind] !=-1)
		return dp[ind];
	int val = endpoints[ind];
	int ans = 0;
	for(auto &i:indexes[val]){
		int sz = vi[i].size();
		for(int j=0;j<sz;j++){
			int valj = vi[i][j];
			int next_one = get_next(valj);
			int opt = (sz - j) + f(next_one);
			ans = max(ans,opt);
		}
	}
	return dp[ind] = ans;
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		int n;
		cin >> n;
		indexes.clear();
		vi.assign(n,vector<int>());
		endpoints.assign(n,0);
		for(int i=0;i<n;i++){
			int ki;
			cin >> ki;
			int curr = 0;
			for(int j=0;j<ki;j++){
				int val;
				cin >> val;
				if(val > curr){
					vi[i].push_back(val);
					curr = val;
				}
			}
			endpoints[i] = vi[i].back();
			if(indexes.count(endpoints[i]) == 0){
				indexes[endpoints[i]] = vector<int>();
			}
			indexes[endpoints[i]].push_back(i);
		}
		endpoints.push_back(0);
		sort(endpoints.begin(),endpoints.end());
		dp.assign(endpoints.size()+1,-1);
		cout << f(endpoints.size()-1) << "\n";
	}
}
