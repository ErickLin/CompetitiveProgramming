#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
int MOD = 1000000007;

long long comb(int n, int k) {
	if (k > n / 2) {
		return comb(n, n - k);
	}
	long long ret = 1;
	for (int i = 1; i <= k; i++) {
		ret *= (n - i + 1);
		ret /= i;
		ret %= MOD;
	}
	return ret;
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n, p;
		cin >> n >> p;
		/*
		long long combs = 1;
		for (int i = 1; i < p; i++) {
			combs = (combs + comb(n, i)) % MOD;
		}
		cout << combs << '\n';
		*/
		vector<long long> dp(n + 1);
		if (p == 1) {
			cout << 1 << '\n';
		} else {
			for (int i = 1; i <= p; i++) {
				dp[i] = 1 << (i - 1);
			}
			dp[p + 1] = 2 * dp[p];
			for (int i = p + 2; i <= n; i++) {
				for (int numX = 0; numX < p && i - numX - 1 >= 1; numX++) {
					dp[i] = (dp[i] + dp[i - numX - 1]) % MOD;
				}
			}
			cout << dp[n] << '\n';
		}
	}
}