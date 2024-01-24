//https://codeforces.com/contest/873/problem/E
// ST + greedy

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

int n;
vector<pair<lli,lli>> v;
vector<lli> st;
void construct_st(int l=0,int r=n-1,int i=0){
	if(l == r){
		if(!l){
			st[i] = v[l].first;
		}else{
			st[i] = v[l].first - v[l-1].first;
		}
		return;
	}
	int mid = (l + r) >> 1;
	construct_st(l,mid,i*2+1);
	construct_st(mid+1,r,i*2+2);
	st[i] = max(st[i*2+1],st[i*2+2]);
}

lli rMq(int s,int e,int l=0,int r=n-1,int i=0){
	if(s > r || e < l)
		return -1;
	if(s<=l && r<=e)
		return st[i];
	int mid = (l + r) >> 1;
	lli L = rMq(s,e,l,mid,i*2+1);
	lli R = rMq(s,e,mid+1,r,i*2+2);
	return max(L,R);
}

struct solution{
	lli d1,c1,d2,c2,d3,c3,third_condition;
	int i,j;
	bool operator<(const solution &other) const{
		lli first_condition = d1 - c2;
		lli first_condition_other = other.d1 - other.c2;
		if(first_condition != first_condition_other)
			return first_condition > first_condition_other;
		
		lli second_condition = d2 - c3;
		lli second_condition_other = other.d2 - other.c3;
		if(second_condition != second_condition_other)
			return second_condition > second_condition_other;
			
		if(third_condition != other.third_condition)
			return third_condition > other.third_condition;
		if(i != other.i)return i < other.i;
		return j < other.j;
	}
};


int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	v.assign(n,{0,0});
	for(int i=0;i<n;i++){
		cin >> v[i].first;
		v[i].second = i;
	}
	sort(v.begin(),v.end());
	st.assign(4*n,0);
	construct_st();
	set<solution> Set;
	for(int i=1;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			int z_len = n - j;
			int y_len = j - i;
			int x_len = i;
			if(z_len*2 < y_len || y_len*2 < z_len){
				continue;
			}
			int maxi = (max(y_len,z_len) +1)/2;
			if(x_len < maxi){
				continue;
			}
			int start_point = max(0,i-2*min(y_len,z_len));
			int end_point = i - maxi;
			int query = rMq(start_point,end_point);
			solution temp;
			temp.c1 = v[n-1].first;
			temp.d1 = v[j].first;
			temp.c2 = v[j-1].first;
			temp.d2 = v[i].first;
			temp.c3 = v[i-1].first;
			temp.third_condition = query;
			temp.i = i;
			temp.j = j;
			Set.insert(temp);
			if(Set.size() > 1){
				auto second_one = Set.end();
				second_one--;
				Set.erase(second_one);
			}
		}
	}
	auto temp = *Set.begin();
	int z_len = n - temp.j;
	int y_len = temp.j - temp.i;
	int x_len = temp.i;
	int maxi = (max(y_len,z_len) +1)/2;
	int start_point = max(0,temp.i-2*min(y_len,z_len));
	int end_point = temp.i - maxi;
	vector<int> ans(n,-1);
	for(int i=temp.i -1;i>end_point;i--){
		ans[v[i].second] = 3; 
	}
	for(int i=end_point;i>=start_point;i--){
		ans[v[i].second] = 3;
		if(rMq(i,i) == temp.third_condition){
			break;
		}
	}
	for(int i = temp.i;i<temp.j;i++){
		ans[v[i].second] = 2;
	}
	for(int i=temp.j;i<n;i++){
		ans[v[i].second] = 1;
	}
	vector<int> ans_sorted(n,-1);
	for(int i=0;i<n;i++){
		cout << ans[i] << " ";
	}
	cout << "\n";

}





