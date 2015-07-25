#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int MOD = 1000000007;

/*
long long gen(long long num, int x, int y, int z) {
	long long ans = num;
	if (x > 0) {
		ans = (ans + gen((num * 10 + 4) % MOD, x - 1, y, z)) % MOD;
	}
	if (y > 0) {
		ans = (ans + gen((num * 10 + 5) % MOD, x, y - 1, z)) % MOD;
	}
	if (z > 0) {
		ans = (ans + gen((num * 10 + 6) % MOD, x, y, z - 1)) % MOD;
	}
	return ans;
}
*/

long long modInverse(long long n, long long m) {
	n = (n + m) % m;
	return n == 0 ? 0 : ((1 - modInverse(m % n, n) * m) / n + m) % m;
}

/*
long long comb(int n, int k, int m) {
	if (k > n / 2) {
		k = n - k;
	}
	long long ret = 1;
	for (int i = 0; i < k; i++) {
		ret = (ret * (n - i)) % m;
		ret = (ret * modInverse(i + 1, m)) % m;
	}
	return ret;
}
*/

int main() {
	vector<vector<long long> > prefix(301, vector<long long>(101));
	for (int n = 0; n <= 300; n++) {
		prefix[n][0] = 1;
        long long prev = 1;
		for (int k = 1; k <= min(n, 100); k++) {
            prev = prev * (n - k + 1) % MOD * modInverse(k, MOD) % MOD;
			prefix[n][k] = (prefix[n][k - 1] + prev) % MOD;
            //cout << n << ' ' << k << ' ' << prefix[n][k] << '\n';
		}
	}
	int x, y, z;
	cin >> x >> y >> z;
	long long ans = 0;
	for (int len = 1; len <= x + y + z; len++) {
        for (int numX = 1; numX <= min(len, x); numX++) {
            long long contrib = 1;
            for (int i = 1; i < len; i++) {
                contrib = contrib * 10 % MOD;
                contrib++;
            }
            long long add = prefix[len - 1][numX - 1];
            if (numX - 2 >= 0)
                add = (add - prefix[len - 1][numX - 2] + MOD) % MOD;
            contrib = contrib * add % MOD;
            long long perms = 0;
            if (len - numX - max(y, z) <= min(y, z)) {
                perms = prefix[len - numX][min(len - numX, min(y, z))] % MOD;
                if (len - numX - 1 - max(y, z) >= 0) {
                    perms = (perms - prefix[len - numX][min(len - numX, len - numX - 1 - max(y, z))] + MOD) % MOD;
                }
            }
            ans = (ans + 4 * perms % MOD * contrib) % MOD;
        }

        for (int numY = 1; numY <= min(len, y); numY++) {
            long long contrib = 1;
            for (int i = 1; i < len; i++) {
                contrib = contrib * 10 % MOD;
                contrib++;
            }
            long long add = prefix[len - 1][numY - 1];
            if (numY - 2 >= 0)
                add = (add - prefix[len - 1][numY - 2] + MOD) % MOD;
            contrib = contrib * add % MOD;
            long long perms = 0;
            if (len - numY - 1 - max(x, z) <= min(x, z)) {
                perms = prefix[len - numY][min(len - numY, min(x, z))] % MOD;
                if (len - numY - 1 - max(x, z) >= 0)
                    perms = (perms - prefix[len - numY][min(len - numY, len - numY - 1 - max(x, z))] + MOD) % MOD;
            }
            ans = (ans + 5 * perms % MOD * contrib) % MOD;
        }
        
        for (int numZ = 1; numZ <= min(len, z); numZ++) {
            long long contrib = 1;
            for (int i = 1; i < len; i++) {
                contrib = contrib * 10 % MOD;
                contrib++;
            }
            long long add = prefix[len - 1][numZ - 1];
            if (numZ - 2 >= 0)
                add = (add - prefix[len - 1][numZ - 2] + MOD) % MOD;
            contrib = contrib * add % MOD;
            long long perms = 0;
            if (len - numZ - 1 - max(x, y) <= min(x, y)) {
                perms = prefix[len - numZ][min(len - numZ, min(x, y))] % MOD;
                if (len - numZ - 1 - max(x, y) >= 0)
                    perms = (perms - prefix[len - numZ][min(len - numZ, len - numZ - 1 - max(x, y))] + MOD) % MOD;
            }
            ans = (ans + 6 * perms % MOD * contrib) % MOD;
        }
	}
	cout << ans << '\n';
	return 0;
}