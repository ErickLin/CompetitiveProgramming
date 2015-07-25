#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
	int n, q;
	cin >> n >> q;
	vector<bool> even(n);
	int a;
	cin >> a;
	even[0] = abs(a) % 2 == 0;
	for (int i = 1; i < n; i++) {
		cin >> a;
		even[i] = even[i - 1] == (abs(a) % 2 == 0);
	}
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		if (l == 0) {
			cout << (even[r] ? "Even" : "Odd") << '\n';
		} else {
			cout << (even[l - 1] == even[r] ? "Even" : "Odd") << '\n';
		}
	}
	return 0;
}