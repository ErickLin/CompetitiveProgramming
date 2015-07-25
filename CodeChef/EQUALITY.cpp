#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
typedef unsigned long long u64;

int main() {
	ios_base::sync_with_stdio(false);
	u64 t;
	cin >> t;
	for (u64 i = 0; i < t; i++) {
		u64 n;
		cin >> n;
		vector<u64> a(n);
		u64 sum = 0;
		for (u64 j = 0; j < n; j++) {
			cin >> a[j];
			sum += a[j];
		}
		sum /= (n - 1);
		cout << (sum - a[0]);
		for (u64 j = 1; j < n; j++) {
			cout << ' ' << (sum - a[j]);
		}
		cout << '\n';
	}
	return 0;
}