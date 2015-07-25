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
int blkSize = 100000;

int main() {
	int t;
	cin >> t;
    long long power = 1;
    for (int j = 0; j < blkSize; j++) {
        power = (power << 1) % MOD;
    }
	vector<long long> pows(blkSize + 1);
	pows[0] = 1;
	for (int i = 1; i <= blkSize; i++) {
        pows[i] = (pows[i - 1] * power) % MOD;
	}
	while (t--) {
		int n;
		cin >> n;
        long long ans = pows[(n - 1) / blkSize];
        for (int i = ((n - 1) / blkSize) * blkSize + 1; i < n; i++) {
            ans = (ans << 1) % MOD;
        }
		cout << ans << '\n';
	}
	return 0;
}