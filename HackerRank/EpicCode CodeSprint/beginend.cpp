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
	u64 n;
	cin >> n;
	string s;
	cin >> s;
	map<char, u64> occs;
	for (u64 i = 0; i < n; i++) {
		occs[s.at(i)]++;
	}
	u64 sum = 0;
	for (map<char, u64>::iterator it = occs.begin(); it != occs.end(); it++) {
		u64 k = it->second;
		sum += ((k * (k + 1)) >> 1);
	}
	cout << sum << '\n';
}