// 574C
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

long long gcd(long long a, long long b) {
	if (max(a, b) % (min(a, b)) == 0) {
		return min(a, b);
	} else {
		return gcd(min(a, b), max(a, b) % min(a, b));
	}
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int gcdTot = gcd(a[0], a[1]);
	for (int i = 2; i < n; i++) {
		gcdTot = gcd(gcdTot, a[i]);
	}
	bool possible = true;
	for (int i = 0; i < n && possible; i++) {
		a[i] /= gcdTot;
		int temp = a[i];
		while (temp % 2 == 0 || temp % 3 == 0) {
			if (temp % 2 == 0) {
				temp /= 2;
			} else {
				temp /= 3;
			}
		}
		if (temp != 1) {
			possible = false;
		}
	}
	if (possible) {
		cout << "Yes\n";
	} else {
		cout << "No\n";
	}
    return 0;
}
