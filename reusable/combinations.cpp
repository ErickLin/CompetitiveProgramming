#include <vector>
using namespace std;

vector<vector<long long> > comb(int n, int MOD) {
	vector<vector<long long> > comb(n + 1, vector<long long>(n + 1));
    comb[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
        }
    }
    return comb;
}