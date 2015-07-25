#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	long t;
	cin >> t;
	for (long i = 0; i < t; i++) {
		long n;
		cin >> n;
		vector<bool> isPrime(n + 1);
		fill(isPrime.begin(), isPrime.end(), true);
		isPrime[0] = false;
		isPrime[1] = false;
		for (long j = 2; j <= ceil(sqrt(n)); j++) {
			if (isPrime[j]) {
				for (long k = j * j; k <= n; k += j) {
					isPrime[k] = false;
				}
			}
		}
		vector<long> primes(n);
		long p = 0;
		for (long i = 2; i <= n; i++) {
			if (isPrime[i]) {
				primes[p++] = i;
			}
		}
		vector<bool> isProd(n + 1);
		long count = 0;
		for (long i = 0; i < p; i++) {
			for (long j = i; j < p && primes[i] * primes[j] <= n; j++) {
				if (!isProd[primes[i] * primes[j]]) {
					isProd[primes[i] * primes[j]] = true;
					count++;
				}
			}
		}
		cout << count << '\n';
	}
	return 0;
}