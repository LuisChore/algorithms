//https://codeforces.com/problemset/problem/1508/A
// two pointers
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


char max_char(string &s){
	int ones = 0,zeros = 0;
	for(int i=0;i<s.size();i++){
		if(s[i] == '0')
			zeros++;
		else
			ones++;
	}
	return (ones > zeros) ?'1':'0';
}

string process(string &s,string &t,char value){
	string ans = "";
	int j = 0;
	for(int i=0;i<s.size();i++){
		if(s[i] == value){
			while(j<t.size() && t[j] != value){
				ans += t[j];
				j++;
			}
			ans += s[i];
			j++;
		}else{
			ans += s[i];
		}
	}
	
	while(j<t.size())
		ans += t[j++];
	return ans;
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		int n;
		cin >> n;
		string s1,s2,s3;
		cin >> s1 >> s2 >> s3;
		char val1 = max_char(s1);
		char val2 = max_char(s2);
		char val3 = max_char(s3);
		string ans = "";
		if(val1 == val2){
			ans = process(s1,s2,val1);
		}else if(val1 == val3){
			ans = process(s1,s3,val1);
		}else{
			ans = process(s2,s3,val2);
		}
		
		cout << ans << "\n";
	}
}
