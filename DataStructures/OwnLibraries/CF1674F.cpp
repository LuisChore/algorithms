//https://codeforces.com/problemset/problem/1674/F
// RMQ 
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<string> grid;
vector<int> st;
int n,m;
void construct_st(int l=0,int r=n*m-1,int i=0){
	if(l == r){
		int row = l%n;
		int col = l/n;
		st[i] = grid[row][col] == '*' ? 1 : 0;
		return;
	}
	int mid = (l + r) >> 1;
	construct_st(l,mid,i*2+1);
	construct_st(mid+1,r,i*2+2);
	st[i] = st[i*2+1] + st[i*2+2];
	
}

void update(int pos,int val,int l=0,int r=n*m-1,int i=0){
	if(pos < l || pos > r)
		return;
	if(l == r){
		st[i] = val;
		return;
	}
	int mid = (l + r) >> 1;
	update(pos,val,l,mid,i*2+1),
	update(pos,val,mid+1,r,i*2+2),
	st[i] = st[i*2+1] + st[i*2+2];
}


int query(int s,int e,int l=0,int r=n*m-1,int i=0){
	if(e < l || s > r)
		return 0;
	if(s<=l && r<=e){
		return st[i];
	}
	int mid = (l + r) >> 1;
	int L = query(s,e,l,mid,i*2+1);
	int R = query(s,e,mid+1,r,i*2+2);
	return L + R;
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int q,num_icons = 0;
	cin >> n >> m >> q;
	grid.assign(n,"");
	for(int i=0;i<n;i++){
		cin >> grid[i];
		for(int j=0;j<m;j++){
			if(grid[i][j] == '*')
				num_icons++;
		}
	}
	st.assign(4*n*m,0);
	construct_st();
	while(q--){
		int row,col,val = 0;
		cin >> row >> col;
		row--;col--;
		
		if(grid[row][col] == '*'){
			grid[row][col] = '.';
			val = 0;
			num_icons--;
		}else{
			grid[row][col] = '*';
			val = 1;
			num_icons++;
		}
		update(col*n + row,val);
		cout << num_icons - query(0,num_icons-1) << "\n";
	}
}
