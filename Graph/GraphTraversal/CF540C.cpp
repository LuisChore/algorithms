// https://codeforces.com/problemset/problem/540/C
// floodfill

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

int n,m;
int row[4]{-1,0,1,0};
int col[4]{0,1,0,-1};


vector<string> grid;
vector<vector<bool>> vis;
void dfs(int i,int j,int x = n,int y = m){
	vis[i][j] = true;
	for(int r = 0; r < 4;r++){
		int I = i + row[r];
		int J = j + col[r];
		if(I>=0 && I < n && J >=0 && J <m && grid[I][J] != 'X' && vis[I][J] == false){
			if(I != x || J != y){
				dfs(I,J,x,y);
			}
		}
	}
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	grid.assign(n,"");
	for(int i=0;i<n;i++){
		cin >> grid[i];
	}
	int x,y,u,v;
	cin >> x >> y;
	cin >> u >> v;
	x--;
	y--;
	u--;
	v--;
	if(x == u && y == v){
		bool ok = false;
		for(int r = 0; r < 4; r ++){
			int I = x + row[r];
			int J = y + col[r];
			if(I>=0 && I<n && J>=0 && J<m && grid[I][J] == '.'){
				ok = true;
			}
		}
		cout << (ok ? "YES\n" : "NO\n");
	}else if(grid[u][v] == 'X'){
		grid[u][v] = '.';
		vis.assign(n,vector<bool>(m,false));
		dfs(x,y);
		cout << (vis[u][v] ? "YES\n" : "NO\n");
	}else{
		bool ok = false;
		for(int r=0;r<4;r++){
			int I = u + row[r];
			int J = v + col[r];
			if(I>=0 && I<n && J>=0 && J<m && grid[I][J] == '.'){
				vis.assign(n,vector<bool>(m,false));
				dfs(x,y,I,J);
				if(vis[u][v]){
					ok = true;
					break;
				}
			}
		}
		cout << (ok ? "YES\n" : "NO\n");
	}
	
	
}


