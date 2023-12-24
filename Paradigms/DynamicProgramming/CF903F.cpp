//https://codeforces.com/contest/903/problem/F
// dp
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

int n;
vector<int> a(4);
vector<int> v;
vector<vector<vector<vector<vector<int>>>>> dp;
int f(int index,int level,int x,int y,int z){
	if(index == n)
		return 0;
	if(dp[index][level][x][y][z] != -1)
		return dp[index][level][x][y][z];
	vector<int> opt(4,inf_int);
	int value = x | v[index];
	if(level == 0){
		int c = ((value & 1) == 0) ? a[0] : 0;
		int next_x = value | 1;
		int next_y = y;
		int next_z = z;
		opt[0] = f(index,level+1,next_x,next_y,next_z) + c;
		
		if(index + 1 < n){
			c = a[1];
			next_x = value | 3;
			next_y = y | 3;
			next_z = z;
			opt[1] = f(index,level +1,next_x,next_y,next_z) + c;
		}
		
		if(index + 2 < n){
			c = a[2];
			next_x = value | 7;
			next_y = y | 7;
			next_z = z | 7;
			opt[2] = f(index,level+1,next_x,next_y,next_z) + c;
		}
		
		if(index + 3 < n){
			c = a[3];
			next_x = 15;
			next_y = 15;
			next_z = 15;
			opt[3] = f(index+1,0,next_x,next_y,next_z) + c;
		}
	}
	
	
	if(level == 1){
		int c = ((value & 2) == 0) ? a[0] : 0;
		int next_x = value | 2;
		int next_y = y;
		int next_z = z;
		opt[0] = f(index,level+1,next_x,next_y,next_z) + c;
		
		if(index + 1 < n){
			c = a[1];
			next_x = value | 6;
			next_y = y | 6;
			next_z = z;
			opt[1] = f(index,level +1,next_x,next_y,next_z) + c;
		}
		
		if(index + 2 < n){
			c = a[2];
			next_x = y | 14;
			next_y = z | 14;
			next_z = 0;
			opt[2] = f(index+1,0,next_x,next_y,next_z) + c;
		}
		
	}
	
	if(level == 2){
		int c = ((value & 4) == 0) ? a[0] : 0;
		int next_x = value | 4;
		int next_y = y;
		int next_z = z;
		opt[0] = f(index,level+1,next_x,next_y,next_z) + c;
		
		if(index + 1 < n){
			c = a[1];
			next_x = y | 12;
			next_y = z;
			next_z = 0;
			opt[1] = f(index+1,0,next_x,next_y,next_z) + c;
		}
		
	}
	
	if(level == 3){
		int c = ((value & 8) == 0) ? a[0] : 0;
		int next_x = y;
		int next_y = z;
		int next_z = 0;
		opt[0] = f(index+1,0,next_x,next_y,next_z) + c;
		
	}
	
	sort(opt.begin(),opt.end());
	return dp[index][level][x][y][z] = opt[0];

}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for(int i=0;i<4;i++)
		cin >> a[i];
	v.assign(n,0);
	dp.assign(n,vector<vector<vector<vector<int>>>>
			  (4,vector<vector<vector<int>>>
			  (16,vector<vector<int>>
			  (16,vector<int>
			  (16,-1)))));
	for(int j=0;j<4;j++){
		string s;
		cin >> s;
		for(int i=0;i<n;i++){
			if(s[i] == '.')
				v[i] |= (1<<j);
		}
	}
	
	int ans = f(0,0,0,0,0);
	cout << ans << "\n";
	
}
