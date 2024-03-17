// https://codeforces.com/problemset/problem/1691/D
// ST + STACK (greater than)

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

int n;
vector<lli> acum_lr,acum_rl;
vector<lli> ST_lr,ST_rl;

void construct_st(vector<lli> &st,vector<lli> &acum,bool flag,int l=0,int r=n-1,int i=0){
	if(l == r){
		st[i] = l;
		return;
	}	
	int mid = (l + r) >> 1;
	construct_st(st,acum,flag,l,mid,i*2+1);
	construct_st(st,acum,flag,mid+1,r,i*2+2);
	if(flag){
		if(acum[st[i*2+1]]>=acum[st[i*2+2]]) st[i] = st[i*2+1];
		else st[i] = st[i*2+2];
	}else{
		if(acum[st[i*2+2]]>=acum[st[i*2+1]]) st[i] = st[i*2+2];
		else st[i] = st[i*2+1];
	}
}

int query(vector<lli> &st,vector<lli> &acum,bool flag,int s,int e,int l=0,int r=n-1,int i=0){
	if(s>r || e<l)
		return -1;
	if(s<=l && r<=e)
		return st[i];
	int mid = (l + r) >> 1;
	int L = query(st,acum,flag,s,e,l,mid,i*2+1);
	int R = query(st,acum,flag,s,e,mid+1,r,i*2+2);
	if(L == -1 || R == -1)
		return max(L,R);
	
	if(flag){
		if(acum[L] >= acum[R])return L;
		return R;
	}else{
		if(acum[R] >= acum[L]) return R;
		return L; 
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		cin >> n;
		vector<lli> v(n,0);
		vector<int> GTL(n,-1),GTR(n,n);
		for(int i=0;i<n;i++){
			cin >> v[i];
		}
		
		stack<int> Stack;
		for(int i=0;i<n;i++){
			if(Stack.size() == 0){
				Stack.push(i);
				continue;
			}
			while(Stack.size() && v[Stack.top()] < v[i]){
				GTR[Stack.top()] = i;
				Stack.pop();
			}
			Stack.push(i);
		}
		while(Stack.size())Stack.pop();
		
		
		for(int i=n-1;i>=0;i--){
			if(Stack.size() == 0){
				Stack.push(i);
				continue;
			}
			while(Stack.size() && v[Stack.top()] < v[i]){
				GTL[Stack.top()] = i;
				Stack.pop();
			}
			Stack.push(i);
		}
	
		acum_lr.assign(n,0);
		ST_lr.assign(4*n,0);		
		for(int i=0;i<n;i++){
			acum_lr[i] = v[i];
			if(i) acum_lr[i] += acum_lr[i-1];
		}
		construct_st(ST_lr,acum_lr,false);
		
		acum_rl.assign(n,0);
		ST_rl.assign(4*n,0);
		for(int i=n-1;i>=0;i--){
			acum_rl[i] = v[i];
			if(i < n-1)acum_rl[i] += acum_rl[i+1];
		}
		construct_st(ST_rl,acum_rl,true);
		
		bool ok = true;
		for(int i=0;i<n;i++){
			int l_index =  query(ST_rl,acum_rl,true,GTL[i] + 1,i);
			int r_index = query(ST_lr,acum_lr,false,i,GTR[i] - 1);
			lli sum = acum_lr[r_index];
			if(l_index) sum -= acum_lr[l_index - 1];
			if(v[i] < sum){
				ok = false;
				break;
			}
		}
		if(ok) cout << "YES\n";
		else cout << "NO\n";
	}
}
