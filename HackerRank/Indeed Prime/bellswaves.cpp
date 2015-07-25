#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main() {
	u32 n;
	cin >> n;
	vector<double> pts(n);
	for (u32 i = 0; i < n; i++) {
		double x, y;
		cin >> x >> pts[i];
	}
	if (pts[0] != pts[1] && pts[1] != pts[2]) {
		cout << "sine-wave\n";
		u32 f = 0;
		for (u32 i = 2; i < n; i++) {
			if ((pts[i - 1] >= pts[i - 2] && pts[i] < pts[i - 1])
					|| (pts[i - 1] > pts[i - 2] && pts[i] <= pts[i - 1])) {
				f++;
				i++;
			}
		}
		f = (u32) round(((double) f) * 500 / (n - 1));
		if (f % 5 != 0) {
			if (f % 5 <= 2) {
				f -= (f % 5);
			} else {
				f += 5 - (f % 5);
			}
		}
		if (f < 5) {
			f = 5;
		}
		if (f > 50) {
			f = 50;
		}
		cout << f << '\n';
	} else {
		cout << "square-wave\n";
		u32 f = 0;
		for (u32 i = 1; i < n; i++) {
			if (pts[i] < pts[i - 1]) {
				f++;
			}
		}
		f = (u32) round(((double) f) * 500 / (n - 1));
		if (f % 5 != 0) {
			if (f % 5 <= 2) {
				f -= (f % 5);
			} else {
				f += 5 - (f % 5);
			}
		}
		if (f < 5) {
			f = 5;
		}
		if (f > 50) {
			f = 50;
		}
		cout << f << '\n';
	}
	return 0;
}