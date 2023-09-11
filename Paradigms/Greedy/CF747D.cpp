#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1e18;
const int inf_int = 1e9;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n,k,neg = 0;
	cin >> n >> k;
	vector<int> a(n);
	int index = -1;
	for(int i=0;i<n;i++){
		cin >> a[i];
		if(a[i] < 0 && index == -1){
			index = i;
		}
		if(a[i] < 0){
			neg++;
		}
	}
	if(index == -1){
		cout << "0\n";
		return 0;
	}
	if(neg > k){
		cout << "-1\n";
		return 0;
	}
	int x = n - index;
	if(x <= k){
		cout << 1 << "\n";
		return 0;
	}
	vector<int> two;
	int one = -1;
	int sum = 0;
	for(int i=index;i<n;i++){
		if(a[i] < 0){
			if(sum > 0){
				two.push_back(sum);
				sum = 0;
			}
		}
		if(a[i] >= 0){
			sum++;
		}
	}
	if(sum > 0){
		one = sum;
	}
	//all 2's
	sort(two.begin(),two.end());
	reverse(two.begin(),two.end());
	int ans1 = 1;
	int temp_x = x;
	for(int i=0;i<two.size();i++){
		ans1+=2;
		temp_x-=two[i];
		if(temp_x <= k)
			break;
	}
	if(temp_x >k){
		ans1++;
	}
	
	//one first
	int ans2 = (one != -1) ? 2 : inf_int;
	temp_x = x - one;
	for(int i=0;i<two.size();i++){
		if(temp_x <= k)
			break;
		ans2+=2;
		temp_x-=two[i];
	}
	cout << min(ans1,ans2) << "\n";
	return 0;
}




























