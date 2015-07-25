#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<bool> sieve(int n) {
	vector<bool> isPrime(n + 1);
	fill(isPrime.begin() + 2, isPrime.end(), true);
	for (int i = 2; i <= (int) ceil(sqrt(n)); i++) {
		if (isPrime[i]) {
			for (int j = i * i; j <= n; j += i) {
				isPrime[j] = false;
			}
		}
	}
	return isPrime;
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	vector<bool> isPrime = sieve(n);
	vector<int> primes;
	for (int i = 2; i <= n; i++) {
		if (isPrime[i]) {
			primes.push_back(i);
		}
	}
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int l, r;
		cin >> l >> r;

	}
	return 0;
}