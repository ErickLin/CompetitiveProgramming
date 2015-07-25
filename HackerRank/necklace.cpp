#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;
int MOD = 1000000007;

long long modInverse(long long n, long long m) {
	n = (n + m) % m;
	return n == 0 ? 0 : ((1 - modInverse(m % n, n) * m) / n + m) % m;
}

int main() {
	int n, k;
	cin >> n >> k;

	vector<bool> isPrime(n + 1);
	vector<long long> phi(n + 1);

	for (int i = 2; i <= n; i++) {
		isPrime[i] = true;
	}
	for (int i = 2; i < sqrt(n) + 1; i++) {
		for (int j = i * i; j <= n; j += i) {
			isPrime[j] = false;
		}
	}

	for (int i = 1; i <= n; i++) {
		phi[i] = i;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i + i; j <= n; j += i) {
			phi[j] -= phi[i];
		}
	}

	long long ans = 0;
	for (int d = 1; d <= n; d++) {
		if (n % d == 0) {
			long long add = phi[d];
			for (int i = 0; i < n / d; i++) {
				add = (add * k) % MOD;
			}
			ans = (ans + add) % MOD;
		}
	}
    if (n > 1) {
	    ans = (ans * modInverse(n, MOD)) % MOD;
    }
    cout << ans << '\n';
	return 0;
}