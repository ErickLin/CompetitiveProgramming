#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef int u32;
typedef long long u64;

int main() {
	u32 n;
	cin >> n;
	vector<u32> a(n);
	for (u32 i = 0; i < n; i++) {
		cin >> a[i];
	}
	u64 max = 0;
	for (u32 xLast = 0; xLast < n - 1; xLast++) {
		u32 yFirst = xLast + 1;
		u64 sum = 0;
		for (u32 i = 0; xLast - i >= 0 && yFirst + i < n; i++) {
			sum += ((long) a[xLast - i]) * a[yFirst + i];
			if (sum > 0) {
				max = max > sum ? max : sum;
			}
			if (sum < 0) {
				sum = 0;
			}
		}
		if (xLast < n - 2) {
			yFirst = xLast + 2;
			sum = 0;
			for (u32 i = 0; xLast - i >= 0 && yFirst + i < n; i++) {
				sum += ((long) a[xLast - i]) * a[yFirst + i];
				if (sum > 0) {
					max = max > sum ? max : sum;
				}
				if (sum < 0) {
					sum = 0;
				}
			}
		}
	}
	cout << max << '\n';
	return 0;
}