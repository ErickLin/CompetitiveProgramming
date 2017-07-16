#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;

void propagate(int level, int row, int col, vvvll& pyramid, vvvll& dp,
               vvvb& taken) {
    int n = pyramid.size();

    if (!taken[level][row][col]) {
        ll score = pyramid[level][row][col];
        if (level > 0) {
            if (row > 0 && !taken[level - 1][row - 1][col]) {
                score += dp[level - 1][row - 1][col];
            }
            if (col > 0 && !taken[level - 1][row][col - 1]) {
                score += dp[level - 1][row][col - 1];
            }
            if (!taken[level - 1][row][col]) {
                score += dp[level - 1][row][col];
            }
        }
        if (score >= 0) {
            taken[level][row][col] = true;
        } else {
            dp[level][row][col] = score;
        }
    }

    if (taken[level][row][col]) {
        if (level > 0) {
            if (row > 0 && !taken[level - 1][row - 1][col]) {
                taken[level - 1][row - 1][col] = true;
                propagate(level - 1, row - 1, col, pyramid, dp, taken);
            }
            if (col > 0 && !taken[level - 1][row][col - 1]) {
                taken[level - 1][row][col - 1] = true;
                propagate(level - 1, row, col - 1, pyramid, dp, taken);
            }
            if (!taken[level - 1][row][col]) {
                taken[level - 1][row][col] = true;
                propagate(level - 1, row, col, pyramid, dp, taken);
            }
        }

        if (row > 0 && !taken[level][row - 1][col]) {
            propagate(level, row - 1, col, pyramid, dp, taken);
        }
        if (row > 0 && col < n - 1 && !taken[level][row - 1][col + 1]) {
            propagate(level, row - 1, col + 1, pyramid, dp, taken);
        }
        if (col > 0 && !taken[level][row][col - 1]) {
            propagate(level, row, col - 1, pyramid, dp, taken);
        }
        if (col < n - 1 && !taken[level][row][col + 1]) {
            propagate(level, row, col + 1, pyramid, dp, taken);
        }
        if (row < n - 1 && col > 0 && !taken[level][row + 1][col - 1]) {
            propagate(level, row + 1, col - 1, pyramid, dp, taken);
        }
        if (row < n - 1 && !taken[level][row + 1][col]) {
            propagate(level, row + 1, col, pyramid, dp, taken);
        }
    }
}

int main() {
    int n;
    cin >> n;
    vvvll pyramid(n, vvll(n, vll(n)));
    for (int level = 0; level < n; level++) {
        for (int row = 0; row <= level; row++) {
            for (int col = 0; col <= level - row; col++) {
                cin >> pyramid[level][row][col];
            }
        }
    }

    vvvll dp(n, vvll(n, vll(n)));
    vvvb taken(n, vvb(n, vb(n)));
    for (int level = 0; level < n; level++) {
        for (int row = 0; row <= level; row++) {
            for (int col = 0; col <= level - row; col++) {
                if (!taken[level][row][col]) {
                    propagate(level, row, col, pyramid, dp, taken);
                }
            }
        }
    }

    ll max_score = 0;
    for (int level = 0; level < n; level++) {
        for (int row = 0; row <= level; row++) {
            for (int col = 0; col <= level - row; col++) {
                if (taken[level][row][col]) {
                    max_score += pyramid[level][row][col];
                }
            }
        }
    }
    cout << max_score << '\n';
}
