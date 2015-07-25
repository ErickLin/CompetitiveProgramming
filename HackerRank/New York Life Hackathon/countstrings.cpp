int MOD = 10000007;

long long modInverse(long long n, long long m) {
	n = (n + m) % m;
	return n == 0 ? 0 : ((1 - modInverse(m % n, n) * m) / n + m) % m;
}

int countStrings(int l, int v) {
    vector<map<vector<int>, int> > dp(v + 1);
    vector<int> temp2(27);
    dp[0][temp2] = 0;
    for (int a = 1; a <= 26; a++) {
        for (int sum = v - a * a; sum >= 0; sum--) {
            for (map<vector<int>, int>::iterator i = dp[sum].begin(); i != dp[sum].end(); i++) {
                for (int n = 1; i->second + n <= l && sum + n * a * a <= v; n++) {
                    vector<int> temp = i->first;
                    temp[a] += n;
                    dp[sum + n * a * a][temp] = i->second + n;
                }
            }
        }
    }
    long long ans = 0;
    for (map<vector<int>, int>::iterator i = dp[v].begin(); i != dp[v].end(); i++) {
        if (i->second == l) {
            long long d = 1;
            for (int j = 2; j <= l; j++) {
                d = d * j % MOD;
            }
            for (int j = 0; j < i->first.size(); j++) {
                for (int k = 2; k <= i->first[j]; k++) {
                    d = d * modInverse(k, MOD) % MOD;
                }
            }
            ans = (ans + d) % MOD;
        }
    }
    return ans;
}