//Order Statistics Tree 
//https://codeforces.com/problemset/problem/1579/E2
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

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		int n;
		lli ans = 0;
		cin >> n;
		ordered_set<pair<int,int>> Set;
		for(int i=0;i<n;i++){
			int aux;
			cin >> aux;
			int str_smaller = Set.order_of_key({aux,0});
			int str_greater = Set.size() - Set.order_of_key({aux,i});
			ans += min(str_smaller,str_greater);
			Set.insert({aux,i});
		}
		cout << ans << "\n";
	}
}
