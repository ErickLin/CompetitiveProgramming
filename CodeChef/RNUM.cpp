#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main(int argc, char** argv) {
	u32 T;
	cin >> T;
	for (u32 t = 0; t < T; t++) {
		u32 n;
		cin >> n;
		vector<u32> a(n);
		for (u32 i = 0; i < n; i++) {
			cin >> a[i];
		}
		sort(a.begin(), a.end());
		u32 min = 0, max = 0;
		u32 streak = 1;
		for (u32 i = 0; i < n; i++) {
			if (i == n - 1 || a[i + 1] > a[i] + 1) {
				min += (int) ceil(((double) streak) / 3);
				max += (int) ceil(((double) streak) / 2);
				streak = 1;
			} else {
				streak++;
			}
		}
		cout << min << ' ' << max << '\n';
	}
	return 0;
}