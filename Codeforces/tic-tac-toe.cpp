#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<double> vd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;

int main() {
    vvc board(4, vc(4));
    forf(i, 4) {
        forf(j, 4) {
            cin >> board[i][j];
        }
    }
    bool yes = false;
    forf(i, 4) {
        forf(j, 4) {
            if (board[i][j] == '.') {
                board[i][j] = 'x';
                forf(a, 4) {
                    forf(b, 4) {
                        if (board[a][b] == 'x') {
                            if (a > 0 && a < 3) {
                                if (board[a - 1][b] == 'x' && board[a + 1][b] == 'x') {
                                    yes = true;
                                }
                            }
                            if (b > 0 && b < 3) {
                                if (board[a][b - 1] == 'x' && board[a][b + 1] == 'x') {
                                    yes = true;
                                }
                            }
                            if (a > 0 && a < 3 && b > 0 && b < 3) {
                                if (board[a - 1][b - 1] == 'x' && board[a + 1][b + 1] == 'x') {
                                    yes = true;
                                }
                                if (board[a - 1][b + 1] == 'x' && board[a + 1][b - 1] == 'x') {
                                    yes = true;
                                }
                            }
                        }
                    }
                }
                board[i][j] = '.';
            }
        }
    }
    if (yes) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
