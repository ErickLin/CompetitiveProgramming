#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
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
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<double> vd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef set<int> si;
typedef vector<si> vsi;

struct elem {
    int count = 0, imbalance = 0, imbalance2 = 0, len = 0;
    bool operator<(const elem& other) const {
        if (imbalance >= 0) {
            return imbalance > other.imbalance;
        } else {
            if (other.imbalance >= 0) {
                return false;
            } else {
                if (count >= 0) {
                    if (other.count >= 0) {
                        return imbalance > other.imbalance;
                    } else {
                        return true;
                    }
                } else {
                    if (other.count >= 0) {
                        return false;
                    } else {
                        struct elem a, b;
                        a.imbalance = imbalance2;
                        a.count = -count;
                        b.imbalance = other.imbalance2;
                        b.count = -other.count;
                        return b < a;
                    }
                }
            }
            /*
            bool a = imbalance < 0 && count < 0;
            bool b = other.imbalance < 0 && other.count < 0;
            if (a && !b) {
                return 0;
            } else if (!a && b) {
                return 1;
            } else {
                return imbalance > other.imbalance;
            }
            */
        }
    }
};

int main() {
    int n;
    cin >> n;
    vs s(n);
    vector<struct elem> elems(n);
    forf(i, n) {
        cin >> s[i];
        int count = 0, count2 = 0, imbalance = 0, imbalance2 = 0;
        forf(j, s[i].size()) {
            if (s[i][j] == '(') {
                count++;
            } else {
                count--;
            }
            imbalance = min(imbalance, count);
        }
        forb(j, s[i].size()) {
            if (s[i][j] == ')') {
                count2++;
            } else {
                count2--;
            }
            imbalance2 = min(imbalance2, count2);
        }
        struct elem a;
        a.count = count;
        a.imbalance = imbalance;
        a.imbalance2 = imbalance2;
        a.len = s[i].size();
        elems[i] = a;
        //cout << count << ' ' << imbalance << '\n';
    }
    sort(elems.begin(), elems.end());
    vi dp(300*300 + 1);
    fill(dp.begin(), dp.end(), -1);
    dp[0] = 0;
    forf(i, n) {
        int count = elems[i].count;
        int imbalance = elems[i].imbalance;
        int imbalance2 = elems[i].imbalance2;
        int len = elems[i].len;
        //cout << count << ' ' << imbalance << ' ' << imbalance2 << ' ' << '\n';
        if (count >= 0) {
            for (int val = 300*300; val >= -imbalance; val--) {
                if (dp[val] != -1 && val + count < dp.size()) {
                    if (dp[val + count] < dp[val] + len) {
                        dp[val + count] = dp[val] + len;
                    }
                    /*
                    if (dp[val + count] == dp[val] + len) {
                        imbalance_at[val + count] = imbalance_at[val] + imbalance + count;
                    }
                    */
                }
            }
        } else if (count < 0) {
            for (int val = -imbalance; val <= 300*300; val++) {
                if (dp[val] != -1 && val + count < dp.size()) {
                    if (dp[val + count] < dp[val] + len) {
                        dp[val + count] = dp[val] + len;
                    }
                }
            }
        }
    }
    cout << dp[0] << '\n';
    return 0;
}
