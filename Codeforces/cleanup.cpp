#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

int main() {
	u32 n;
	cin >> n;
	u32 max = 0;
	map<string, u32> occs;
	for (u32 i = 0; i < n; i++) {
		string s;
		cin >> s;
		occs[s]++;
		if (occs[s] > max) {
			max = occs[s];
		}
	}
	cout << max << '\n';
	return 0;
}