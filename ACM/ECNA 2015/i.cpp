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
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
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

vvb rotate(vvb &grille) {
    int n = grille.size();
    vvb ret(n, vb(n));
    forf(i, n) {
        forf(j, n) {
            if (grille[i][j]) {
                ret[j][n - i - 1] = true;
            }
        }
    }
    return ret;
}

int main() {
    int n;
    cin >> n;
    vvb grille(n, vb(n));
    forf(i, n) {
        forf(j, n) {
            char c;
            cin >> c;
            if (c == '.') {
                grille[i][j] = true;
            }
        }
    }
    string s;
    cin >> s;
    vvc msg(n, vc(n));
    forf(i, n) {
        forf(j, n) {
            msg[i][j] = '0';
        }
    }
    int pos = 0;
    bool valid = true;
    forf(t, 4) {
        forf(i, n) {
            forf(j, n) {
                if (grille[i][j]) {
                    if (pos >= s.size()) {
                        valid = false;
                        break;
                    }
                    msg[i][j] = s[pos++];
                }
            }
            if (!valid) {
                break;
            }
        }
        if (!valid) {
            break;
        }
        grille = rotate(grille);
    }
    forf(i, n) {
        forf(j, n) {
            if (msg[i][j] == '0') {
                valid = false;
                break;
            }
        }
        if (!valid) {
            break;
        }
    }
    if (valid) {
        forf(i, n) {
            forf(j, n) {
                cout << msg[i][j];
            }
        }
    } else {
        cout << "invalid grille";
    }
    cout << '\n';
    return 0;
}
