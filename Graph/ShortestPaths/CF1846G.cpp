
//https://codeforces.com/problemset/problem/1846/G
// dijkstra
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


int main(){
	int cases;
	cin >> cases;
	while(cases--){
		int n,m;
		cin >> n >> m;
		vector<lli> weight(m),med(m),syn(m);
		string s;
		cin >> s;
		int value = 0;
		for(int i=0;i<s.size();i++){
			if(s[i] == '1')
				value += (1<<i); 
		}
		
		int source  = value;
		
		for(int i=0;i<m;i++){
			cin >> weight[i];
			cin >> s;
			value = 0;
			for(int j=0;j<s.size();j++){
				if(s[j] == '1')
					value += (1<<j);
			}
			med[i] = value;
			
			cin >> s;
			value = 0;
			for(int j=0;j<s.size();j++){
				if(s[j] == '1')
					value += (1<<j);
			}
			syn[i] = value;
		}
		
		vector<lli> dist((1<<n),inf);
		dist[source] = 0;
		set<pair<lli,lli>> pq;
		for(int i=0;i<(1<<n);i++){
			pq.emplace(dist[i],i);
		}
		while(!pq.empty()){
		
			auto [d,u] = *pq.begin();
			pq.erase(pq.begin());
			for(int mi=0;mi<m;mi++){
				int v = 0;
				for(int i=0;i<n;i++){
					if(med[mi] & (1<<i)){
						//
					}else if(syn[mi] & (1<<i)){
						v += (1<<i);
					}else if(u & (1<<i)){
						v += (1<<i);
					}
				}
				if(dist[u] + weight[mi] >= dist[v])continue;
				pq.erase(pq.find({dist[v],v}));
				dist[v] = dist[u] + weight[mi];
				pq.emplace(dist[v],v);
			}
		}
		cout << (dist[0] != inf ? dist[0] : -1) << "\n";
		
	}
}
