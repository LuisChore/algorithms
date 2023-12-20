// https://codeforces.com/problemset/problem/1747/D
// XOR acum
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	lli n,q;
	cin >> n >> q;
	vector<lli> v(n);
	vector<lli> acum_xor(n,0),acum_sum(n,0);
	map<lli,int> Map;
	vector<vector<int>> Odds,Evens;

	int count = 0;
	for(int i=0;i<n;i++){
		cin >> v[i];
		acum_xor[i] = v[i];
		acum_sum[i] = v[i];
		if(i){
			acum_xor[i] ^= acum_xor[i-1];
			acum_sum[i] += acum_sum[i-1];
		}
		lli value = acum_xor[i];
		int index = -1;
		if(Map.count(value)){
			index = Map[value];				
		}else{
			Odds.push_back(vector<int>());
			Evens.push_back(vector<int>());
			index = count;
			Map[value] = count++;
		}
		if(i&1){
			Odds[index].push_back(i);
		}else{
			Evens[index].push_back(i);
		}
	}
	while(q--){
		lli l,r;
		cin >> l >> r;
		l--;
		r--;
		lli xor_value = acum_xor[r];
		if(l) xor_value ^= acum_xor[l-1];
		
		lli sum_value = acum_sum[r];
		if(l) sum_value -= acum_sum[l-1];
		
		if(!xor_value && !sum_value){
			cout << "0\n";
			continue;
		}
		if(xor_value){
			cout << "-1\n";
			continue;
		}
		if((r-l + 1)&1){
			cout << "1\n";
			continue;
		}
		//special case
		if(!v[l] || !v[r]){
			cout << "1\n";
			continue;
		}
		lli xor_c = (l ? acum_xor[l-1] : 0);
		int index = Map[xor_c];
		if(l&1){
			//find if in Odds[index] there is value between [l,r];
			int low = lower_bound(Odds[index].begin(),Odds[index].end(),l) - Odds[index].begin();
			if(low < Odds[index].size() && Odds[index][low] <= r){
				cout << "2\n";
			}else{
				cout << "-1\n";
			}
		}else{
		
			//find if in Evens[index] there is value between [l,r];
			int low = lower_bound(Evens[index].begin(),Evens[index].end(),l) - Evens[index].begin();
			if(low < Evens[index].size() && Evens[index][low] <= r){
				cout << "2\n";
			}else{
				cout << "-1\n";
			}
		}
		
	}	
}



