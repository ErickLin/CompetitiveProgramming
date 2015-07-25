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
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	bool done = false;
	for (int t = 0; t < n && !done; t++) {
		done = true;
		for (int i = 0; i < n && done; i++) {
			if (a[i] != i) {
				done = false;
			}
		}
		for (int i = 0; i < n; i++) {
			if ((i & 1) == 0) {
				a[i] = (a[i] + 1) % n;
			} else {
				a[i] = a[i] - 1;
				if (a[i] < 0) {
					a[i] += n;
				}
			}
		}
	}
	if (done) {
		cout << "Yes\n";
	} else {
		cout << "No\n";
	}
	return 0;
}