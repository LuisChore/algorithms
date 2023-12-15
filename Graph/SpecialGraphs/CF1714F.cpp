//https://codeforces.com/problemset/problem/1714/F
// tree + implementation
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
		int n, x,y,z;
		cin >> n >> x >> z >> y;
		int index = -1;
		int lengthY = -1;
		bool ok = false;
		for(int i=0;i<=x;i++){
			int length_y = y - i;
			int length_x = x - i;
			if(length_y < 0){
				break;
			}
			if(length_x + length_y == z){
				lengthY = length_y;
				index = i;
				ok = true;
				break;
				
			}
		}
		if(!ok){
			cout << "NO\n";
			continue;
		}
		int m = x + lengthY + 1;
		if(m > n){
			cout << "NO\n";
			continue;
		}
		cout << "YES\n";
		int prev = 1,curr = 4;
		bool y_ok = false;
		int value_y = -1;
		for(int i=1;i<x;i++){
			if(i == index && lengthY == 0){
				cout << prev << " 3\n";
				y_ok = true;
				prev = 3;
				continue;
			}
			if(i == index){
				value_y = curr;
			}
			cout << prev << " " << curr << "\n";
			prev = curr;
			curr++;
		}
		cout << prev << " 2\n";
		if(y_ok){
			for(int i=curr;i<=n;i++){
				cout << 1 << " " << i << "\n";
			}
			continue;
		}
		
		if(index == 0){
			value_y = 1;
		}else if(index == x){
			value_y = 2;
		}
		prev = value_y;
		for(int i=1;i<lengthY;i++){
			cout << prev << " " << curr << "\n";
			prev = curr;
			curr++;
		}
		cout << prev << " 3\n";
		for(int i=curr;i<=n;i++){
			cout << 1 << " " << i << "\n";
		}
	}
}



