#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
long long MOD = 1000000007;

int main() {
	ios_base::sync_with_stdio(false);
	int m, r, s, aSum, bSum;
	cin >> m >> r >> s;
	if ((r + s) % 2 != 0) {
		cout << "0\n";
		return 0;
	}
	aSum = (r + s) / 2;
	bSum = (r - s) / 2;
	vector<int> x(m);
	//index 1 = sum of elements, index 2 = cardinality of subsequence
	//value = number of subsequences that sum to key
	vector<vector<unsigned long long> > dp(2001, vector<unsigned long long>(101));
	dp[0][0] = 1;
	for (int i = 0; i < m; i++) {
		cin >> x[i];
		for (int sum = 2000; sum >= 0; sum--) {
			for (int card = 100; card >= 0; card--) {
				if (sum + x[i] <= 2000 && dp[sum][card] > 0) {
					dp[sum + x[i]][card + 1] = (dp[sum + x[i]][card + 1] + dp[sum][card]) % MOD;
				}
			}
		}
	}
	unsigned long long count = 0;
	for (int card = 0; card <= 100; card++) {
		if (bSum == 0) {
			count = (count + dp[aSum][card]) % MOD;
		} else {
			count = (count + ((dp[aSum][card] * dp[bSum][card]) % MOD)) % MOD;
		}
	}
	cout << count << '\n';
	/*
	//key = sum of elements, value = number of subsequences that sum to key
	map<unsigned long long, unsigned long long> dp;
	dp[0] = 1;
	for (int i = 0; i < m; i++) {
		cin >> x[i];
		map<unsigned long long, unsigned long long>::reverse_iterator rit;
		for (rit = dp.rbegin(); rit != dp.rend(); rit++) {
			if (dp.find(rit->first + x[i]) == dp.end()) {
				dp[rit->first + x[i]] = dp[rit->first];
			} else {
				dp[rit->first + x[i]] = (dp[rit->first + x[i]] + dp[rit->first]) % MOD;
			}
		}
	}
	cout << (dp[aSum] * dp[bSum]) % MOD;
	*/
	return 0;
}