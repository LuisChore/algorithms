//https://codeforces.com/problemset/problem/999/F
// dp + greedy
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

int n,k;
vector<int> cards;
vector<int> favs;
vector<int> H;
vector<vector<int>> dp;
int f(int ni,int ci){
	if(ni == 0 || ci == 0)
		return 0;
	if(dp[ni][ci] != -1)
		return dp[ni][ci];
	if(cards[ci-1] > favs[ni-1])
		return dp[ni][ci] = f(ni,ci-1);
	if(favs[ni-1] > cards[ci-1])
		return dp[ni][ci] = f(ni-1,ci);
	
	int ans = f(ni-1,ci);
	for(int i=0;i<k;i++){
		if(cards[ci-1-i] == favs[ni-1]){
			int opt = f(ni-1,ci-i-1) + H[i];
			ans = max(ans,opt);
		}
	}
	return dp[ni][ci] = ans;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	favs.assign(n,0);
	cards.assign(n*k,0);
	H.assign(k,0);
	dp.assign(n+5,vector<int>(n*k+5,-1));
	for(int i=0;i<n*k;i++){
		cin >> cards[i];
	}
	sort(cards.begin(),cards.end());
	for(int i=0;i<n;i++){
		cin >> favs[i];
	}
	sort(favs.begin(),favs.end());
	for(int i=0;i<k;i++){
		cin >>H[i];
	}
	cout << f(n,n*k) << "\n";
	
}
