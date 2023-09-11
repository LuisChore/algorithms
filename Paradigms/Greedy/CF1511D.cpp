#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

string get_string(int k){
	string ans = "";
	ans += (char)('a' + k - 1);
	for(int i=0;i<k;i++){
		ans += (char)('a' + i);
		for(int j=i+1;j<k;j++){
			ans += (char)('a' + i);
			ans += (char)('a' + j);
		}
	}
	return ans;
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n,k;
	cin >> n >> k;
	if(k == 1){
		while(n--)
			cout << 'a';
		cout << "\n";
		return 0;
	}
	string aux = get_string(k);
	cout << aux[0];
	int index = 1;
	for(int i=1;i<n;i++){
		cout << aux[index];
		index++;
		if(index == aux.size())
			index = 1;
	}
	cout << "\n";
	return 0;
}
