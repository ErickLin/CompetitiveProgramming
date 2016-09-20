#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

vector<vector<long long> > comb(31, vector<long long>(31));

long long calcComps(int cur, vi &numEach, int sum, int n, int m, int k) {
    long long ret = 0;
    if (sum == n) {
        bool miss = true;
        for (int i = m; i <= n; i += k) {
            if (numEach[i] > 0) {
                miss = false;
            }
        }
        if (miss) {
            //cout << sum << ' ' << n << ' ';
            int numParts = 0;
            for (int i = 1; i <= 30; i++) {
                //if (numEach[i] > 0) {
                    //cout << i << ':' << numEach[i] << ' ';
                //}
                numParts += numEach[i];
            }
            //cout << '\n';
            ret = 1;
            for (int i = 1; i <= 30; i++) {
                ret *= comb[numParts][numEach[i]];
                numParts -= numEach[i];
            }
        }
    } else if (cur > n - sum) {
        ret = 0;
    } else for (int i = 0; sum + i * cur <= n; i++) {
        numEach[cur] = i;
        ret += calcComps(cur + 1, numEach, sum + i * cur, n, m, k);
        numEach[cur] = 0;
    }
    return ret;
}

int main() {
    comb[0][0] = 1;
    for (int i = 0; i <= 30; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]);
        }
    }
    int p;
    cin >> p;
    while (p--) {
        int K, n, m, k;
        cin >> K >> n >> m >> k;
        vi numEach(31);
        long long comps = calcComps(1, numEach, 0, n, m, k);
        cout << K << ' ' << comps << '\n';
    }
    return 0;
}
