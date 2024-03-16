//https://codeforces.com/problemset/problem/1884/C
// ST RMQ + lazy

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<pair<lli,lli>> segments;
map<lli,int> Index;
int n;
vector<lli> lazy,st;

void construct_st(int l=0,int r= n-1,int i=0){
	if(l == r){
		lazy[i] = 0;
		st[i] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	construct_st(l,mid,i*2+1);
	construct_st(mid+1,r,i*2+2);
	st[i] = lazy[i] = 0;
}

void update(int s,int e,lli val,int l=0,int r=n-1,int i=0){
	if(lazy[i] != 0){
		st[i] += lazy[i];
		if(l != r){
			lazy[i*2+1] += lazy[i];
			lazy[i*2+2] += lazy[i];
		}
		lazy[i] = 0;
	}
	if(s > r || e < l ){
		return;
	}
	if(s<=l && r<=e){
		st[i] += val;
		if(l != r){
			lazy[i*2+1] += val;
			lazy[i*2+2] += val;
		}
		return;
	}
	int mid = (l + r) >> 1;
	update(s,e,val,l,mid,i*2+1);
	update(s,e,val,mid+1,r,i*2+2);
	st[i] = max(st[i*2+1],st[i*2+2]);
}


lli query(int s,int e,int l=0,int r=n-1,int i=0){
	if(lazy[i] != 0){
		st[i] += lazy[i];
		if(l != r){
			lazy[i*2+1] += lazy[i];
			lazy[i*2+2] += lazy[i];
		}
		lazy[i] = 0;
	}
	if(s > r || e < l ){
		return 0;
	}
	if(s<=l && r<=e){
		return st[i];
	}
	int mid = (l + r) >> 1;
	lli L = query(s,e,l,mid,i*2+1);
	lli R = query(s,e,mid+1,r,i*2+2);
	return max(L,R);
}

bool f(pair<lli,lli> &a,pair<lli,lli> &b){
	if(a.second != b.second){
		return a.second < b.second;
	}
	return a.first < b.first;
}


bool g(pair<lli,lli> &a,pair<lli,lli> &b){
	if(a.first != b.first){
		return a.first > b.first;
	}
	return a.second > b.second;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		lli _n,_m;
		cin >> _n >> _m;
		segments.assign(_n,{0,0});
		Index.clear();
		set<lli> temp;
		temp.insert(1);
		temp.insert(_m); 
		for(int i=0;i<_n;i++){
			lli l,r;
			cin >> l >> r;
			segments[i] = {l,r};
			temp.insert(l);
			temp.insert(r);
		}
		int count = 0;
		for(auto &ti: temp){
			Index[ti] = count++;
		}
		n = count; 
		st.assign(4*n,0);
		lazy.assign(4*n,0);
		lli ans = 0;
		sort(segments.begin(),segments.end(),f);
		int index = 0;
		for(int i=1;i<n;i++){
			while(index < _n && Index[segments[index].second] <i){
				int li = Index[segments[index].first];
				int ri = Index[segments[index].second];
				update(li,ri,1);
				index++;
			}
			lli maxi = query(0,i-1);
			ans = max(ans,maxi);
		}
		
		
		sort(segments.begin(),segments.end(),g);
		construct_st();
		index = 0;
		for(int i=n-2;i>=0;i--){
			while(index < _n && Index[segments[index].first] > i){
				int li = Index[segments[index].first];
				int ri = Index[segments[index].second];
				update(li,ri,1);
				index++;
			}
			lli maxi = query(i+1,n-1);
			ans = max(ans,maxi);
		}
		cout << ans << "\n";
		
	}
}
