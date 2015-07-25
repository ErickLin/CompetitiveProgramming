#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		long long n, k, c;
		cin >> n >> k >> c;
		vector<long long> df(n - 1);
		vector<long long> dists(n);
		vector<long long> p(n - 1);
		long long sum = 0;
		dists[0] = 0;
		for (long long i = 0; i < n - 1; i++) {
			cin >> df[i] >> p[i];
			sum += df[i];
			dists[i + 1] = sum;
		}
		stack<long long> s;
		vector<long long> nextCheaper(n - 1);
		for (long long i = n - 2; i >= 0; i--) {
			while (!s.empty()) {
				if (p[s.top()] < p[i]) {
					nextCheaper[i] = s.top();
					break;
				} else {
					s.pop();
				}
			}
			s.push(i);
		}
		for (long long q = 0; q < k; q++) {
			long long a, b;
			cin >> a >> b;
			a--;
			b--;
			long long currentFuel = 0;
			long long totalCost = 0;
			for (long long i = a; i < b; i++) {
				if (i > a) {
					currentFuel -= df[i - 1];
				}
				long long fuelToAdd = 0;
				if (nextCheaper[i] == 0) {
					fuelToAdd = c - currentFuel;
				} else {
					fuelToAdd = min(c - currentFuel, max((long long) 0,
							dists[nextCheaper[i]] - dists[i] - currentFuel));
				}
				fuelToAdd = min(fuelToAdd, max((long long) 0,
						dists[b] - dists[i] - currentFuel));
				totalCost += p[i] * fuelToAdd;
				currentFuel += fuelToAdd;
			}
			cout << totalCost << '\n';
		}
	}
	return 0;
}