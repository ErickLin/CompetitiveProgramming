#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		unsigned int n;
		cin >> n;
		unsigned int alloc = 0;
		unsigned long long total = 0;
		for (unsigned int i = 0; i < n; i++) {
			unsigned int m;
			cin >> m;
			if (m > alloc) {
				total += m - alloc;
			}
			alloc = m;
		}
		cout << total << '\n';
	}
	return 0;
}