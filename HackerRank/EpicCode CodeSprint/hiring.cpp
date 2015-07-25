#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

int main() {
	u64 n, p, x;
	cin >> n >> p >> x;
	vector<u32> a(n);
	u64 max = 0;
	u32 maxInd = 0;
	for (u32 i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] * p > max) {
			max = a[i] * p;
			maxInd = i;
		}
		p -= x;
	}
	cout << (maxInd + 1) << '\n';
}