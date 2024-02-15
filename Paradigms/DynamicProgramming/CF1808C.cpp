//https://codeforces.com/problemset/problem/1808/C
// DP, solution reconstruction
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


int dp[20][10][10][2][2];
string L,R;

string get_string(lli n){
	string s = "";
	while(n){
		int digit = n%10;
		s += (digit + '0');
		n/=10;
	}
	reverse(s.begin(),s.end());
	return s;
}

int f(int index,int mini,int maxi,int flag1,int flag2){
	if(index == L.size()){
		return maxi - mini;
	}
	if(dp[index][mini][maxi][flag1][flag2] != -1)
		return dp[index][mini][maxi][flag1][flag2];
	
	int ini = (flag1) ? 0 : (L[index] - '0');
	int end = (flag2) ? 9 : (R[index] - '0');
	int ans = inf_int;
	for(int i=ini;i<=end;i++){
		bool next_flag1 = (flag1 || i > (L[index] - '0')) ? true : false;
		bool next_flag2 = (flag2 || i < (R[index] - '0')) ? true : false;
		int opt =  f(index + 1,min(mini,i),max(maxi,i),next_flag1,next_flag2);
		ans = min(ans,opt);
	}
	return dp[index][mini][maxi][flag1][flag2] = ans;
}

void rec(int index,int mini,int maxi,int flag1,int flag2){
	if(index == L.size()){
		cout << "\n";
		return;
	}
	int ini = (flag1) ? 0 : (L[index] - '0');
	int end = (flag2) ? 9 : (R[index] - '0');
	for(int i=ini;i<=end;i++){
		bool next_flag1 = (flag1 || i > (L[index] - '0')) ? true : false;
		bool next_flag2 = (flag2 || i < (R[index] - '0')) ? true : false;
		int opt =  f(index + 1,min(mini,i),max(maxi,i),next_flag1,next_flag2);
		if(dp[index][mini][maxi][flag1][flag2] == opt){
			cout <<i;
			rec(index + 1,min(mini,i),max(maxi,i),next_flag1,next_flag2);
			break;
		}
	}
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin  >> cases;
	while(cases--){
		lli l,r;
		cin >> l >> r;
		int lenl = log10(l) + 1;
		int lenr = log10(r) + 1;
		if(lenl < lenr){
			while(lenl--){
				cout << "9";
			}
			cout << "\n";	
		}else{
			L = get_string(l);
			R = get_string(r);
			memset(dp,-1,sizeof(dp));
			f(0,9,0,0,0);
			rec(0,9,0,0,0);
		}
	}
}
