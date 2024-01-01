//https://codeforces.com/problemset/problem/1902/D
/*
SEGMENT TREE (queries: find an element withint a range)
Coud be solved using offline approach
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


int n;
vector<pair<int,int>> acum,acumR;
vector<set<pair<int,int>> > st;

void construct_st(int l=0,int r=n-1,int i=0){
	if(l == r){
		st[i].insert({acumR[l].first,acumR[l].second});
		return;
	}
	for(int j=l;j<=r;j++){
		st[i].insert({acumR[j].first,acumR[j].second});
	}
	int mid = (l + r) >> 1;
	construct_st(l,mid,i*2+1);
	construct_st(mid+1,r,i*2+2);
}
 
int get_query(int x,int y,int s,int e,int l=0,int r=n-1,int i=0){
	if(e<l || s > r)
		return 0;
	if(s<=l && r<=e){
		int value = (st[i].find({x,y}) != st[i].end());
		return value;
	}
	if(st[i].find({x,y}) == st[i].end())
		return 0;
	int mid = (l + r) >> 1;
	int L{0},R{0};
	L = get_query(x,y,s,e,l,mid,i*2+1);
	R = get_query(x,y,s,e,mid+1,r,i*2+2);
	return L+R;
}

struct query{
	int ind;
	int x,y;
	int l,r;
	query(){}
	query(int _ind,int _x,int _y,int _l,int _r):
		ind(_ind),x(_x),y(_y),l(_l),r(_r){}	
};

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int q;
	string s;
	cin >> n >> q;
	cin >> s;
	acum.assign(n+2,{0,0});
	acumR.assign(n+2,{0,0});

	for(int i=0;i<s.size();i++){
		int l = 0,r = 0;
		if(s[i] == 'U')r++;
		if(s[i] == 'D')r--;
		if(s[i] == 'L')l--;
		if(s[i] == 'R')l++;
		
		acum[i+1] = {l,r};
		acum[i+1].first += acum[i].first;
		acum[i+1].second += acum[i].second;
	}
	
	for(int i=s.size()-1;i>=0;i--){
		int l = 0,r = 0;
		if(s[i] == 'U')r++;
		if(s[i] == 'D')r--;
		if(s[i] == 'L')l--;
		if(s[i] == 'R')l++;
		
		acumR[i+1] = {l,r};
		acumR[i+1].first += acumR[i+2].first;
		acumR[i+1].second += acumR[i+2].second;
	}
	
	
	vector<query> queries(q);
	for(int i=0;i<q;i++){
		int x,y,l,r;
		cin >> x >> y >> l >> r;
		query temp(i,x,y,l,r);
		queries[i] = temp;
	}
	
	sort(queries.begin(),queries.end(),[](query a,query b){
		if(a.l != b.l)
			return a.l < b.l;
		return a.ind < b.ind;
	});
	vector<bool> ans(q,0);
	n += 2;
	set<pair<int,int>> Set;
	int index_q = 0;
	for(int i=0;i<=n;i++){
		while(index_q < q && queries[index_q].l == i){
			if(Set.find({queries[index_q].x,queries[index_q].y}) != Set.end()){
				ans[queries[index_q].ind] = true;
			}
			index_q++;
		} 
		Set.insert(acum[i]);
	}
	
	
	sort(queries.begin(),queries.end(),[](query a,query b){
		if(a.r != b.r)
			return a.r > b.r;
		return a.ind < b.ind;
	});
	
	Set.clear();
	index_q = 0;
	for(int i=n;i>=1;i--){
		while(index_q < q && queries[index_q].r == i){
			if(Set.find({queries[index_q].x,queries[index_q].y}) != Set.end()){
				ans[queries[index_q].ind] = true;
			}
			index_q++;
		} 
		Set.insert(acum[i]);
	}
	
	Set.clear();
	
	sort(queries.begin(),queries.end(),[](query a,query b){
		return a.ind < b.ind;
	});
	
	
	
	st.assign(4*n,set<pair<int,int>>());
	construct_st();
	
	for(int i=0;i<q;i++){
		int x = queries[i].x;
		int y = queries[i].y;
		int l = queries[i].l;
		int r = queries[i].r;
		
		auto before = acum[l-1];
		auto before_rev = acumR[r+1];
		int diffx = x - before.first;
		int diffy = y - before.second;
		
		int neededx = before_rev.first + diffx;
		int neededy = before_rev.second + diffy;
				int query = get_query(neededx,neededy,l,r);
		if(query || ans[i]){
			cout << "YES\n";	
		}else{
			cout << "NO\n";
		}

	}
	
	
}

