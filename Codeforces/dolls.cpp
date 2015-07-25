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
	int n, k;
	cin >> n >> k;
	int moves = k - 1;
	int beginChainLen = 0;
	for (int i = 0; i < k; i++) {
		int m;
		cin >> m;
		moves += ((m - 1) << 1);
		vector<int> a(m);
		for (int j = 0; j < m; j++) {
			cin >> a[j];
			if (a[j] == j + 1) {
				beginChainLen = max(beginChainLen, j + 1);
			}
		}
	}
	moves -= ((beginChainLen - 1) << 1);
	cout << moves << '\n';
	return 0;
}