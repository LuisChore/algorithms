// https://codeforces.com/problemset/problem/1902/E
// trie (reimplement)
#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


vector<map<int,int>> trie;
vector<int> counter;

void add_word(string &s){
	int curr_node = 0;
	for(int i=0;i<s.size();i++){
		int val = s[i]-'a';
		int next_node = -1;
		if(trie[curr_node].count(val)){
			next_node = trie[curr_node][val];
		}else{
			next_node = trie.size();
			trie[curr_node][val] = next_node;
			counter.push_back(0);
			trie.push_back(map<int,int>());
		}
		counter[next_node]++;
		curr_node = next_node;
	}
}

lli solve(string &s){
	int curr_node = 0;
	lli ans = 0;
	for(int i=0;i<s.size();i++){
		int val = s[i] -'a';
		int next_node = -1;
		if(trie[curr_node].count(val)){
			next_node = trie[curr_node][val];
			ans += counter[next_node];
		}else{
			break;
		}
		curr_node = next_node;
	}
	return ans;
}


int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	lli n,all_size = 0;
	cin >> n;
	trie.push_back(map<int,int>()); // root;
	counter.push_back(0);
	vector<string> S;
	while(n--){
		string s;
		cin >> s;
		reverse(s.begin(),s.end());
		add_word(s);
		reverse(s.begin(),s.end());
		S.push_back(s);
		all_size += s.size();
	}
	lli ans = 0;
	for(auto &si: S){
		ans += solve(si);
	}
	ans = 2LL*S.size()*all_size - ans*2LL;
	cout << ans << "\n";
	
}
