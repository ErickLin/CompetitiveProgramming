#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		int ind, d = (m - 1) / n;
		if (n % 2 == 0) {
			if (m % 2 == 1) {
				ind = ((m % n) >> 1) + 1;
			} else {
				if (m % n == 0) {
					ind = (n >> 1) + 1;
				} else {
					ind = n - ((m % n) >> 1) + 1;
				}
			}
		} else {
			if (m % 2 == 1) {
				if (m % (n << 1) <= n) {
					ind = ((m % (n << 1)) >> 1) + 1;
				} else {
					ind = ((m % n) >> 1);
				}
			} else {
				if (m % (n << 1) == 0) {
					ind = (n >> 1) + 1;
				} else {
					if (m % (n << 1) <= n) {
						ind = n - ((m % (n << 1)) >> 1) + 1;
					} else {
						ind = n - ((m % n) >> 1);
					}
				}
			}
		}
		cout << ind << ' ' << d << '\n';
	}
	return 0;
}