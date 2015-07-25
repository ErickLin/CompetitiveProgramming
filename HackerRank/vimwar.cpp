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
    vector<long long> count(1 << m);
    vector<long long> count2(1 << m);
    for (int i = 0; i < n; i++) {
        for (int j = m - 1; j >= 0; j--) {
            char p;
            cin >> p;
            a[i] += ((p -= '0') << j);
        }
    }
    int b = 0;
    for (int j = m - 1; j >= 0; j--) {
        char p;
        cin >> p;
        b += ((p -= '0') << j);
    }
    int startIndex = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((a[i] & (1 << j)) == 1 && (b & (1 << j)) == 0) {
                a[i] = -1;
                startIndex++;
                break;
            }
        }
    }
    sort(a.begin(), a.end());
    for (int i = startIndex; i < n; i++) {
        count[a[i]]++;
    }
    for (int i = startIndex; i < n; i++) {
        for (int j = (1 << m) - 1; j >= 0; j--) {
            count2[a[i] | j] = (count2[a[i] | j] + count2[j]) % MOD;
        }
        count2[a[i]]++;
    }
    cout << count2[b] << '\n';
    return 0;
}