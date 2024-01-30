// https://codeforces.com/contest/1651/submission/244058058
// BFS multisource

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
	int row[4]{-1,0,1,0};
	int col[4]{0,1,0,-1};
	set<pair<int,int>> Set;
	map<pair<int,int>,int> Index;
	for(int i=0;i<n;i++){
		int x,y;
		cin >> x >> y;
		Set.insert({x,y});
		Index[{x,y}] = i;
	}
	queue<pair<int,int>> Q;
	map<pair<int,int>,int> dist;
	map<pair<int,int>,pair<int,int>> parent;
	for(auto &pi:Set){
		for(int r=0;r<4;r++){
			int I = pi.first + row[r];
			int J = pi.second + col[r];
			if(Set.find({I,J}) == Set.end()){
				if(dist.count({I,J}) == 0){
					dist[{I,J}] = 0;
					parent[{I,J}] = {I,J};
					Q.push({I,J});
				}
			}
		}
	}
	while(Q.size()){
		auto &pu = Q.front();
		Q.pop();
		for(int r=0;r<4;r++){
			int I = pu.first + row[r];
			int J = pu.second + col[r];
			if(Set.find({I,J}) != Set.end() && dist.count({I,J}) == 0){
				dist[{I,J}] = dist[{pu.first,pu.second}] + 1;
				parent[{I,J}] = parent[{pu.first,pu.second}];
				Q.push({I,J});
			}
		}
	}
	vector<pair<int,int>> ans(n,{0,0});
	for(auto &pi: Set){
		ans[Index[{pi.first,pi.second}]] = parent[{pi.first,pi.second}];
	}
	for(auto &a: ans){
		cout << a.first << " " << a.second << "\n";
	}

}
