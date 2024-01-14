// https://codeforces.com/contest/863/problem/E
// greedy sorting segments

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
	vector<pair<pair<lli,lli>,int>> v(n);
	for(int i=0;i<n;i++){
		cin >> v[i].first.first;
		cin >> v[i].first.second;
		v[i].first.second *= -1;
		v[i].second = i + 1;
	}
	sort(v.begin(),v.end());
	
	int index = 0;
	int ans = -1;
	while(index < n){
		auto curr = v[index]; curr.first.second*=-1;
		int index_next = index + 1;
		if(index_next == n)
			break;
		auto next = v[index_next]; next.first.second *=-1;
		if(next.first.first > curr.first.second){
			index++;
			continue;
		}
		if(next.first.second <= curr.first.second){
			ans = next.second;
			break;
		}
		
		if(index_next == n -1){
			break;
		}	
		int index_next_next = index_next + 1;
		auto next_next = v[index_next_next]; next_next.first.second *= -1;
		if(next_next.first.first > curr.first.second + 1 && next_next.first.second > next.first.second){
			index = index_next_next;
			continue;
		}
		
		if(next.first.first <= next_next.first.first && next_next.first.second<=next.first.second){
				ans = next_next.second;
		}else{
				ans = next.second;
		}
		break;
	}
	cout << ans << "\n";
	
}
