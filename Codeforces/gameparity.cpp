#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <cmath>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main() {
	//first index is number of odd cities remaining, second index " " even " "
	//vector<vector<bool> > strategy(200001, 200001);
	//strategy[0][0] = false;
	u32 n, k, odd = 0, even = 0;
	cin >> n >> k;
	for (u32 i = 0; i < n; i++) {
		u32 a;
		cin >> a;
		if ((a & (1 << 0)) == 0) {
			even++;
		} else {
			odd++;
		}
	}
	u32 t = n - k;
	if (even > t && odd > t) {
		if ((t & (1 << 0) == 0) {
			cout << "Daenerys\n";
		} else {
			cout << "Stannis\n";
		}
	}
	
	return 0;
}