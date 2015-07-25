#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	unsigned long long n;
	cin >> n;
	vector<unsigned long long> a(n);
	vector<unsigned long long> left(n);
	for (unsigned long long i = 0; i < n; i++) {
		cin >> a[i];
		for (unsigned long long j = i - 1; j >= 0; j--) {
			if (a[j] > a[i]) {
				left[i] = j + 1;
				break;
			}
		}
	}
	unsigned long long max = 0;
	vector<unsigned long long> right(n);
	for (unsigned long long i = 0; i < n; i++) {
		for (unsigned long long j = i + 1; j < n; j++) {
			if (a[j] > a[i]) {
				right[i] = j + 1;
				if (left[i] * right[i] > max) {
					max = left[i] * right[i];
				}
				break;
			}
		}
	}
	cout << max << '\n';
	return 0;
}