// https://codeforces.com/problemset/problem/1731/D
// Binary Search on Grid


#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


void get_aux(vector<vector<int>> &original, vector<vector<int>> &aux,int mid){
	int n = original.size();
	int m = original.back().size();
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			aux[i][j] = (original[i][j] >= mid) ? 1 : 0;
			if(i) aux[i][j] += aux[i-1][j];
			if(j) aux[i][j] += aux[i][j-1];
			if(i && j) aux[i][j] -= aux[i-1][j-1];
		}
	}
}

bool can(vector<vector<int>> &aux,int mid){
	int n= aux.size();
	int m = aux.back().size();
	bool ok = false;
	for(int i=0;i<n && ok == false;i++){
		for(int j=0;j<m;j++){
			int I = i + mid - 1;
			int J = j + mid - 1;
			if(I>=n || J>=m)
				break;
			
			lli sum = aux[I][J];
			if(i) sum -= aux[i-1][J];
			if(j) sum -= aux[I][j-1];
			if(i && j) sum += aux[i-1][j-1];
			if(sum == mid*mid){
				ok = true;
				break;
			}
		}
	}
	return ok;
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		int n,m;
		cin >> n >> m;
		vector<vector<int>> original(n,vector<int>(m,0));
		vector<vector<int>> aux(n,vector<int>(m,0));
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cin >> original[i][j];
			}
		}
		int low = 1,high = min(n,m),ans = low;
		while(low<=high){
			int mid = (low + high) >> 1;
			get_aux(original,aux,mid);
			bool ok = can(aux,mid);
			if(ok){
				ans = mid;
				low = mid + 1;
			}else{
				high = mid - 1;
			}
		}
		cout << ans << "\n";
	}
}
