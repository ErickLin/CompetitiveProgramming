#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

long long gcd(long long n1, long long n2) {
	if (max(n1, n2) % min(n1, n2) == 0) {
		return min(n1, n2);
	} else {
		return gcd(min(n1, n2), max(n1, n2) % min(n1, n2));
	}
}

struct Fraction {
	long long num;
	long long denom;
	bool operator<(Fraction other) const {
		return (num * other.denom) < (other.num * denom);
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		long n, k;
		cin >> n >> k;
		vector<pair<long long, long long> > procs(n);
		long long minC = 1000000000;
		for (int j = 0; j < n; j++) {
			long long c, l;
			cin >> c >> l;
			if (c < minC) {
				procs[j] = make_pair(c, l);
			} else {
				n--;
				j--;
			}
		}
		sort(procs.begin(), procs.end());
		for (int j = 0; j < k; j++) {
			long long m;
			cin >> m;
			Fraction earliest;
			earliest.num = 1000000000000000000;
			earliest.denom = 1;
			for (int p = 0; p < n; p++) {
				long long num = procs[p].second * procs[p].first + m;
				long long denom = procs[p].first;
				long long div = gcd(num, denom);
				num /= div;
				denom /= div;
				Fraction t;
				t.num = num;
				t.denom = denom;
				if (t < earliest) {
					earliest = t;
				}
			}
			cout << earliest.num << '/' << earliest.denom << '\n';
		}
	}
	return 0;
}