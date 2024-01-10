//https://codeforces.com/problemset/problem/1765/D
// Two Pointers + greedy
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	lli n,m;
	cin >> n >> m; 
	deque<lli> DQ;
	lli sum = 1;
	for(int i=0;i<n;i++){
		lli aux;
		cin >> aux;
		sum += aux;
		DQ.push_back(aux);
	}
	sort(DQ.begin(),DQ.end());
	lli curr = DQ.back();
	int next = 0;
	DQ.pop_back();
	for(int i=1;i<n;i++){
		if(next){
			lli next_value = DQ.back();
			if(next_value + curr <= m){
				curr = next_value;
				DQ.pop_back();
				next = 0;
			}else{
				curr = next_value;
				DQ.pop_back();
				next = 0;
				sum++;
			}
		}else{
			lli next_value = DQ.front();
			if(next_value + curr <= m){
				DQ.pop_front();
				curr = next_value;
				next = 1;
			}else{
				next_value = DQ.back();
				DQ.pop_back();
				curr = next_value;
				next = 0;
				sum++;
			}
		}
	}
	cout << sum << "\n";
}
