#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;


int less_than(int val,vector<int> &v){
	int low = 0,high = v.size()-1,ans = -1;
	while(low<=high){
		int mid = (low + high) >> 1;
		if(v[mid] >= val){
			high = mid - 1;
		}else{
			ans = mid;
			low = mid + 1;
		}
	}
	return ans + 1;
}
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int cases;
	cin >> cases;
	while(cases--){
		lli n,m,k;
		cin >> n >> m >> k;
		map<int,int> MapX,MapY;
		for(int i=0;i<n;i++){
			int xi;
			cin >> xi;
			MapX[xi] = i;
		}
		for(int i=0;i<m;i++){
			int yi;
			cin >> yi;
			MapY[yi] = i;
		}
		lli ans = 0;
		vector<int> vx,vy;
		vector<vector<int>> vvx(n,vector<int>());
		vector<vector<int>> vvy(m,vector<int>());
		while(k--){
			int xi,yi;
			cin >>xi >> yi;
			if(MapX.count(xi)!=0 && MapY.count(yi) != 0)
				continue;
			if(MapX.count(xi)){
				vvx[MapX[xi]].push_back(yi);
				vx.push_back(yi);
			}else{
				vvy[MapY[yi]].push_back(xi);
				vy.push_back(xi);
			}
		}
		sort(vx.begin(),vx.end());
		sort(vy.begin(),vy.end());
		for(int i=0;i<n;i++){
			sort(vvx[i].begin(),vvx[i].end());
			for(int yi: vvx[i]){
				auto it = MapY.upper_bound(yi);
				int yr = it->first;
				it--;
				int yl = it->first;
				
				int total = less_than(yr,vx) - less_than(yl,vx);
				total -= less_than(yr,vvx[i]) - less_than(yl,vvx[i]);
				ans += total; 
			}
		}
		
		for(int i=0;i<m;i++){
			sort(vvy[i].begin(),vvy[i].end());
			for(int xi: vvy[i]){
				auto it = MapX.upper_bound(xi);
				int xr = it->first;
				it--;
				int xl = it->first;
				int total = less_than(xr,vy) - less_than(xl,vy);
				total -= less_than(xr,vvy[i]) - less_than(xl,vvy[i]);
				ans += total; 
			}
		}
		cout << ans/2 << "\n";
	}
}
