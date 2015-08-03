#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int MOD = 1000000007;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<long long> count(1 << 20);
    for (int i = 0; i < n; i++) {
        for (int j = m - 1; j >= 0; j--) {
            char p;
            cin >> p;
            a[i] += ((p - '0') << j);
        }
        count[a[i]]++;
    }
    int b = 0;
    for (int j = m - 1; j >= 0; j--) {
        char p;
        cin >> p;
        b += ((p - '0') << j);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < (1 << 20); j++) {
            if (j & (1 << i)) {
                count[j] += count[j ^ (1 << i)];
            }
        }
    }
    vector<long long> pows(1 << 20);
    pows[0] = 1;
    for (int i = 1; i < (1 << 20); i++) {
        pows[i] = (pows[i - 1] << 1) % MOD;
    }
    for (int i = 0; i < (1 << 20); i++) {
        pows[i] = (pows[i] - 1 + MOD) % MOD;
    }
    long long ans = 0;
    for (int i = 0; i < (1 << 20); i++) {
        if ((i | b) == b) {
            if (__builtin_popcount(i ^ b) % 2) {
                ans = (ans - pows[count[i]] + MOD) % MOD;
            } else {
                ans = (ans + pows[count[i]]) % MOD;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}