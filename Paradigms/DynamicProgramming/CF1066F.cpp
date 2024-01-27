//https://codeforces.com/problemset/problem/1066/F
// dp on 2D grid
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<vector<pair<lli,lli>>> points_by_level;
vector<vector<lli>> dp;
lli f(int level,int flag){
	if(level == 0){
		return 0;
	}
	if(dp[level][flag] != -1)
		return dp[level][flag];
	
	lli xi = points_by_level[level][0].first;
	lli yi = - points_by_level[level][0].second;
	
	lli xn = points_by_level[level].back().first;
	lli yn = - points_by_level[level].back().second;
	lli dist = abs(xn-xi) + abs(yn-yi);
	
	lli xi_prev = points_by_level[level-1][0].first;
	lli yi_prev = - points_by_level[level-1][0].second;
	
	lli xn_prev = points_by_level[level-1].back().first;
	lli yn_prev = - points_by_level[level-1].back().second;
	
	lli opt1 = inf,opt2= inf,ans;
	if(!flag){
		opt1 = dist + abs(xn-xn_prev) + abs(yn-yn_prev) + f(level-1,1);
		opt2 = dist + abs(xn-xi_prev) + abs(yn-yi_prev) + f(level-1,0);
		ans = min(opt1,opt2);
	}else{
		opt1 = dist + abs(xi-xn_prev) + abs(yi-yn_prev) + f(level-1,1);
		opt2 = dist + abs(xi-xi_prev) + abs(yi-yi_prev) + f(level-1,0);
		ans = min(opt1,opt2);
	}
	return dp[level][flag] = ans;
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	map<int,int> LevelToIndex;
	vector<pair<lli,lli>> points;
	vector<lli> levels;
	for(int i=0;i<n;i++){
		lli xi,yi;
		cin >> xi >> yi;
		points.push_back({xi,yi});
		levels.push_back(max(xi,yi));
	}
	sort(levels.begin(),levels.end());
	int n_level = 1;
	for(auto &li: levels){
		if(LevelToIndex.count(li) == 0){
			LevelToIndex[li] = n_level++;
		}
	}
	points_by_level.assign(n_level,vector<pair<lli,lli>>());
	points_by_level[0].push_back({0,0});
	for(auto &pi:points){
		int index = LevelToIndex[max(pi.first,pi.second)];
		points_by_level[index].push_back({pi.first,-pi.second});
	}
	for(auto &v:points_by_level){
		sort(v.begin(),v.end());
	}
	
	dp.assign(n_level,vector<lli>(2,-1));
	lli ans = min(f(n_level-1,0),f(n_level-1,1));
	cout << ans << "\n";
	
	
	
	
}
