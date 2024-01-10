//https://codeforces.com/problemset/problem/1580/A
// acummulative sum in a grid

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
		int n,m;
		cin >> n >> m;
		vector<string> grid(n);
		for(int i=0;i<n;i++)
			cin >> grid[i];
		vector<vector<int>> columns_sum(m,vector<int>(n,0));
		for(int j=0;j<m;j++){
			for(int i=0;i<n;i++){
				columns_sum[j][i] = (grid[i][j] == '1' ? 1 : 0);
				if(i)
					columns_sum[j][i] += columns_sum[j][i-1];
			}
		}
		int ans = inf_int;
		for(int i1=0;i1<=n-5;i1++){
			for(int i2 = i1 + 4;i2<n;i2++){
				vector<int> sum_parallel(m,0);
				vector<int> sum_rectangle(m,0);
				vector<int> min_acum(m,0);
				for(int j=m-1;j>=0;j--){
					//sum parallel
					int inside_portal_cost = columns_sum[j][i2-1] - columns_sum[j][i1];
					int outside_portal_cost = (grid[i1][j] == '0') + (grid[i2][j] == '0');
					sum_parallel[j] = inside_portal_cost + outside_portal_cost;
					if(j < m - 1) sum_parallel[j] += sum_parallel[j+1];
					
					//sum rectangle
					int border_cost = (i2-i1-1) - inside_portal_cost;
					sum_rectangle[j] = border_cost;
					if(j < m - 1)sum_rectangle[j] += sum_parallel[j+1];
				}
				for(int j=0;j<m;j++){
					min_acum[j] = sum_rectangle[j];
					if(j) min_acum[j] = min(min_acum[j],min_acum[j-1]);
				}
				int best_here = inf_int;
				for(int j=m-1;j>=3;j--){
					int inside_portal_cost = columns_sum[j][i2-1] - columns_sum[j][i1];
					int border_cost = (i2 - i1 - 1) - inside_portal_cost;
					int opt = min_acum[j-3] - sum_parallel[j] + border_cost;
					best_here = min(best_here,opt);
				}
				ans = min(ans,best_here);
			}
		}	
		cout << ans << "\n";
	}
}
