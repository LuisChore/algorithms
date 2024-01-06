// https://codeforces.com/problemset/problem/1575/D
// complete search (recursive)
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

string s;
lli f(int index,int res,int x = -1){
	if(index == s.size())
		return (res ? 0: 1);
	
	if(s[index] != 'X' && s[index] != '_'){
		int value = s[index] -'0';
		res = (res*10 + value)%25;
		if(res < 0)res += 25;
		return f(index + 1,res,x);
	}
	
	bool mark_x = false;
	if(s[index] == 'X'){
		if(x == -1){
			mark_x = true;
		}else{
			res = (res*10 + x)%25;
			if(res <0) res += 25;
			return f(index+1,res,x);
		}
	}
	int ini = (index || s.size() == 1) ? 0: 1;
	lli ans = 0;
	
	for(int i=ini;i<10;i++){
		x = mark_x ? i : x;
		int temp_res = (res*10 + i) % 25;
		if(temp_res < 0) temp_res += 25;
		ans += f(index+1,temp_res,x);
	}
	return ans;
} 
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> s;
	if(s[0] == '0' && s.size() > 1)
		cout << "0\n";
	else
		cout << f(0,0) << "\n";
}
