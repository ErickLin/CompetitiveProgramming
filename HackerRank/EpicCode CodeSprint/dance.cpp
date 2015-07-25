#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> b(n), g(n);
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> g[i];
	}
	sort(b.begin(), b.end());
	sort(g.begin(), g.end());
	int c = 0, d = 0, count = 0;
	while (c < n && d < n) {
		if (abs(b[c] - g[d]) <= k) {
			count++;
			c++;
			d++;
		} else if (b[c] < g[d]) {
			c++;
		} else {
			d++;
		}
	}
	cout << count << '\n';
	return 0;
}