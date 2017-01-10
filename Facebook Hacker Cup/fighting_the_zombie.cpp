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
typedef vector<vd> vvd;
typedef vector<vvd> vvvd;
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

double probSumAtLeast(int val, int rolls, int faces, vvvd &dp) {
    //cout << val << ' ' << rolls << ' ' << faces << '\n';
    if (dp[val][rolls][faces] >= 0) {
        return dp[val][rolls][faces];
    }
    double ret = 0;
    if (val == 0) {
        ret = 1;
    } else if (rolls == 1) {
        ret = max((double) (faces - val + 1) / faces, 0.0);
    } else {
        if (val <= rolls * faces) {
            for (int face = 1; face <= faces; face++) {
                ret += probSumAtLeast(max(val - face, 0), rolls - 1, faces, dp) / faces;
            }
        }
    }
    dp[val][rolls][faces] = ret;
    return ret;
}

int main() {
    int T;
    cin >> T;
    forf(t, T) {
        cout << "Case #" << t + 1 << ": ";
        int h, s;
        cin >> h >> s;
        double maxProb = 0;
        forf(i, s) {
            string shorthand;
            cin >> shorthand;
            int rolls = 0, faces = 0, offset = 0;
            size_t pos1 = shorthand.find("d");
            size_t pos2 = shorthand.find("+");
            if (pos2 == string::npos) {
                pos2 = shorthand.find("-");
            }
            rolls = stoi(shorthand.substr(0, pos1));
            if (pos2 == string::npos) {
                //cout << shorthand.substr(0, pos1) << ' ' << shorthand.substr(pos1 + 1) << '\n';
                faces = stoi(shorthand.substr(pos1 + 1));
            } else {
                //cout << shorthand.substr(0, pos1) << ' ' << shorthand.substr(pos1 + 1, pos2 - pos1 - 1) << ' ' << shorthand.substr(pos2) << '\n';
                faces = stoi(shorthand.substr(pos1 + 1, pos2 - pos1 - 1));
                offset = stoi(shorthand.substr(pos2));
            }
            //cout << rolls << ' ' << faces << ' ' << offset << '\n';
            vvvd dp(max(h - offset, 0) + 1, vvd(rolls + 1, vd(faces + 1)));
            forf(k, max(h - offset, 0) + 1) {
                forf(i, rolls + 1) {
                    forf(j, faces + 1) {
                        dp[k][i][j] = -1;
                    }
                }
            }
            //cout << probSumAtLeast(h - offset, rolls, faces, dp) << '\n';
            maxProb = max(maxProb, probSumAtLeast(max(h - offset, 0), rolls, faces, dp));
        }
        printf("%.6f\n", maxProb);
    }
    return 0;
}
