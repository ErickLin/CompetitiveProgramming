#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int MOD = 1000000007; 
vector<long long> fac(200001);
vector<long long> facInv(200001);

long long modInverse(long long a, long long m) {
    a %= m;
    return a == 0 ? 0 : ((1 - modInverse(m % a, a) * m) / a + m) % m;
}

int compare(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) {
        return a.second < b.second;
    } else {
        return a.first < b.first;
    }
}

long long comb(long long n, long long k) {
    return (long long) fac[n] * facInv[k] % MOD * facInv[n - k] % MOD;
}

int main() {
    /*
    vector<vector<int> > comb(200001, vector<int>(200001));
    for (int i = 0; i <= 200000; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
        }
    }
    */
    fac[0] = 1;
    for (int i = 1; i <= 200000; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    for (int i = 0; i <= 200000; i++) {
        facInv[i] = modInverse(fac[i], MOD);
    }

    int h, w, n;
    cin >> h >> w >> n;
    vector<pair<int, int> > cells(n + 1);
    for (int i = 0; i < n; i++) {
        int r, c;
        cin >> r >> c;
        cells[i] = make_pair(r - 1, c - 1);
    }
    cells[n++] = make_pair(h - 1, w - 1);
    sort(cells.begin(), cells.end(), compare);

    vector<long long> numPaths(n);
    for (int i = 0; i < n; i++) {
        numPaths[i] = comb(cells[i].first + cells[i].second, cells[i].first);
        for (int j = 0; j < n; j++) {
            if (cells[j].first <= cells[i].first && cells[j].second <= cells[i].second
                    && j != i) {
                long long overcount = numPaths[j] * comb(cells[i].first
                        + cells[i].second - cells[j].first - cells[j].second,
                        cells[i].first - cells[j].first) % MOD;
                numPaths[i] = (numPaths[i] - overcount + MOD) % MOD;
            } 
        }
    }
    cout << numPaths[n - 1] << '\n';
}
