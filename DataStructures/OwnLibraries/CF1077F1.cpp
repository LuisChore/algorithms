//https://codeforces.com/contest/1077/problem/F1
// DP using 2 ST for previous states

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<lli> st[2];
vector<lli> v;
int n,k,x;

inline void update(vector<lli> &tree,int pos,lli val,int l=0,int r=n,int i=0){
	if(pos < l || pos > r)
		return;
	if(l == r){
		tree[i] = val;
		return;
	}
	int mid = (l + r) >> 1;
	if(pos<=mid)
		update(tree,pos,val,l,mid,i*2+1);
	else
		update(tree,pos,val,mid+1,r,i*2+2);
	tree[i] = max(tree[i*2+1],tree[i*2+2]);
}

inline lli query(vector<lli> &tree,int s,int e,int l=0,int r=n,int i=0){
	if(s > r || e < l)
		return -inf;
	if(s<=l && r<=e)
		return tree[i];
	int mid = (l + r) >> 1;
	lli L = query(tree,s,e,l,mid,i*2+1);
	lli R = query(tree,s,e,mid+1,r,i*2+2);
	return max(L,R);
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >>n >> k >> x;
	v.assign(n+1,0);
	for(int i=1;i<=n;i++){
		cin >> v[i];
	}
	st[0].assign(4*(n+1),0);
	st[1].assign(4*(n+1),0);
	for(int i=1;i<=n;i++){
		if(i<=k){
			update(st[1],i,v[i]);
		}else{
			update(st[1],i,-inf);
		}
	}

	for(int xi=2;xi<=x;xi++){
		for(int i=1;i<=n;i++){
			if(xi > i){
				update(st[xi&1],i,-inf);
				continue;
			}
			int l = (i-k<1) ? 1:i-k;		
			lli q = query(st[(xi-1)&1],l,i-1);
			lli value = q + v[i];
			update(st[xi&1],i,value);
		}
	}
	lli ans = query(st[x&1],n-k+1,n);
	if(ans < 0) ans = -1;
	cout << ans << "\n";
}
