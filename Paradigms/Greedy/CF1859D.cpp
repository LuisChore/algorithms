#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		int seg;
		cin >> seg;
		vector<pair<int,int>> segs;
		while(seg--){
			int l,r,ai,bi;
			cin >> l >> r >> ai >> bi;
			segs.push_back({-bi,l});
		}
		sort(segs.begin(),segs.end());
		auto [curr_r,curr_l] = segs[0];
		curr_r = - curr_r;
		vector<pair<int,int>> final_segs;
		for(int i=1;i<segs.size();i++){
			auto [r,l] = segs[i];
			r = - r;
			if(r >= curr_l){
				curr_l = min(curr_l,l);
			}else{
				final_segs.push_back({curr_l,curr_r});
				curr_l = l;
				curr_r = r;
			}
		}
		final_segs.push_back({curr_l,curr_r});
		reverse(final_segs.begin(),final_segs.end());
		int q;
		cin >> q;
		while(q--){
			int qi;
			cin >> qi;
			int low = 0,high = final_segs.size()-1,s_ans = 0;
			while(low<=high){
				int mid = (low + high) >> 1;
				if(final_segs[mid].first <= qi && qi <= final_segs[mid].second){
					s_ans = mid;
					break;
				}else if(qi < final_segs[mid].first){
					high = mid - 1;
				}else{
					low = mid + 1;

				}
			}
			if(final_segs[s_ans].first <= qi && qi <= final_segs[s_ans].second){
				cout << final_segs[s_ans].second << " ";
			}else{
				cout << qi << " ";
			}
			
		}
		cout << "\n";
	}
}
