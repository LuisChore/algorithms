//https://codeforces.com/contest/61/problem/E
// ST RSQ
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds;
using namespace std;

typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

vector<lli> st;
int n;
lli rsq(int s,int e,int l=0,int r=n-1,int i=0){
	if(e <l || s > r){
		return 0;
	}
	if(s<=l && r <= e){
		return st[i];
	}
	
	int mid = (l + r) >> 1;
	lli L = rsq(s,e,l,mid,i*2+1);
	lli R = rsq(s,e,mid+1,r,i*2+2);
	return L + R;
	
}

void update(int pos,lli val,int l=0,int r=n-1,int i=0){
	if(pos < l || pos > r)
		return;
	if(l == r){
		st[i] = val;
		return;
	}
	int mid = (l + r) >> 1;
	update(pos,val,l,mid,i*2+1);
	update(pos,val,mid+1,r,i*2+2);
	st[i] = st[i*2+1] + st[i*2+2];
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	vector<int> a(n),sorta(n);
	map<int,int> index;
	for(int i=0;i<n;i++){
		cin >> a[i];
		sorta[i] = a[i];
	}
	sort(sorta.begin(),sorta.end());
	for(int i=0;i<n;i++){
		 index[sorta[i]] = i;
	}
	ordered_set<int> Set;
	st.assign(4*n,0);
	for(int i=n-1;i>=0;i--){
		int value = Set.order_of_key(a[i]);
		int index_i = index[a[i]];
		update(index_i,value);
		Set.insert(a[i]);
	}
	lli ans = 0;
	for(int i=0;i<n;i++){
		int index_i = index[a[i]];
		if(index_i)
			ans += rsq(0,index_i-1);
		update(index_i,0);
	}
	cout << ans << "\n";
}


