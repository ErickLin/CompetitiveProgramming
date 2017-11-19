// 553A
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int MOD = 1000000007;
    vector<vector<long long> > comb(1001, vector<long long>(1001));
    comb[0][0] = 1;
    for (int i = 0; i <= 1000; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
        }
    }

    int n;
    cin >> n;
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    long long ans = 1;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += c[i];
        ans = ans * comb[sum - 1][c[i] - 1] % MOD;
    }
    cout << ans << '\n';
    return 0;
}
