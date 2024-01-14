//https://codeforces.com/problemset/problem/1847/D
// ST + greedy

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

vector<int> v,index_map;
int n;
vector<int> st;
string s;
void construct_st(vector<int> &st,int l=0,int r=n-1,int i=0){
	if(l == r){
		st[i] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	construct_st(st,l,mid,i*2+1);
	construct_st(st,mid+1,r,i*2+2);
	st[i] = st[i*2+1] + st[i*2+2];
}

void construct_st2(vector<int> &st,int l=0,int r=n-1,int i=0){
	if(l == r){
		st[i] = (s[v[l]] == '1') ? 1 : 0;
		return;
	}
	int mid = (l + r) >> 1;
	construct_st2(st,l,mid,i*2+1);
	construct_st2(st,mid+1,r,i*2+2);
	st[i] = st[i*2+1] + st[i*2+2];
}

int rsq(vector<int> &st,int s,int e,int l=0,int r=n-1,int i=0){
	if(s > r || e < l){
		return 0 ;
	}
	if(s<=l && r<=e){
		return st[i];
	}
	int mid = (l + r) >> 1;
	int L = rsq(st,s,e,l,mid,i*2+1);
	int R = rsq(st,s,e,mid+1,r,i*2+2);
	return L + R;
}

void update(vector<int> &st,int pos,int val,int l=0,int r=n-1,int i=0){
	if(pos < l || pos > r){
		return;
	}
	if(l == r){
		st[i] = val;
		return;
	}
	int mid = (l+r) >> 1;
	update(st,pos,val,l,mid,i*2+1);
	update(st,pos,val,mid+1,r,i*2+2);
	st[i] = st[i*2+1] + st[i*2+2];
}

int next_one(int l,int r){
	int low = l,high = r,ans = -1;
	while(low<=high){
		int mid = (low + high) >> 1;
		int sum = rsq(st,l,mid);
		if(sum){
			ans = mid;
			high = mid - 1;
		}else{
			low = mid + 1;
		}
	}
	return ans;
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int m,q;
	cin >> n >> m >> q;
	cin >> s;
	st.assign(4*n,0);
	index_map.assign(n,-1);
	construct_st(st);
	while(m--){
		int l,r;
		cin >> l >> r;
		l--;
		r--;
		int next_ind = next_one(l,r);
		while(next_ind != -1){
			update(st,next_ind,0);
			index_map[next_ind] = v.size();
			v.push_back(next_ind);
			next_ind = next_one(next_ind,r);
		}
	}
	int t_size = v.size();
	for(int i=0;i<n;i++){
		if(index_map[i] == -1){
			index_map[i] = v.size();
			v.push_back(i);
		}
	}
	st.assign(4*n,0);
	construct_st2(st);
	while(q--){
		int pos;
		cin >> pos;
		pos--;
		s[pos] = (s[pos] == '1') ? '0': '1';
		int val = s[pos] - '0';
		update(st,index_map[pos],val);
		int number_of_ones = rsq(st,0,n-1);
	//	cout << number_of_ones << "<-\n";
		if(number_of_ones >= t_size){
			int ans = t_size - rsq(st,0,t_size-1);
			cout << ans << "\n";
		}else{
			int ans = rsq(st,number_of_ones,n-1);
			cout << ans << "\n";
		}
	}
	
}
