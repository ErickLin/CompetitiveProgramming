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

class MinMaxMax {
    public:
        ll findMin(vi a, vi b, vi w, vi v) {
            int m = w.size();
            int n = v.size();
            vvi adj(n, vi(n));
            forf(i, m) {
                adj[a[i]][b[i]] = w[i];
                adj[b[i]][a[i]] = w[i];
            }

            vvi dn(n, vi(n));
            vvi de(n, vi(n));
            vvll d(n, vll(n));
            forf(i, n) {
                fill(dn[i].begin(), dn[i].end(), 0);
                fill(de[i].begin(), de[i].end(), 0);
                fill(d[i].begin(), d[i].end(), LLONG_MAX);
            }
            forf(i, n) {
                dn[i][i] = v[i];
                de[i][i] = 0;
                queue<ll> q;
                q.push(i);
                vb vis(n);
                vis[i] = true;
                while (!q.empty()) {
                    int cur = q.front();
                    q.pop();
                    for (int next = 0; next < n; next++) {
                        if (adj[cur][next] != 0 && !vis[next]) {
                            dn[i][next] = max(dn[i][cur], v[next]);
                            de[i][next] = max(de[i][cur], adj[cur][next]);
                            dn[next][i] = dn[i][next];
                            de[next][i] = de[i][next];
                            q.push(next);
                            vis[next] = true;
                        }
                    }
                }
            }
            ll ret = 0;
            forf(i, n) {
                for (int j = i + 1; j < n; j++) {
                    if (adj[i][j] != 0) {
                        ret += ((ll) dn[i][j]) * de[i][j];
                    }
                }
            }
            return ret;
        }
};

int main() {
    MinMaxMax a;
    vi a0({0}), b0({1}), w0({5}), v0({3, 6});
    cout << a.findMin(a0, b0, w0, v0) << '\n';
    vi a5({4,16,0,10,11,21,11,21,20,6,13,10,10,3,20,15,16,9,6,14,13,8, 17,9,2,21,3,4,10,13,5,7,13,1,12,1,3,13,5,21,12,0,19,15,6,0, 5,13,1,8});
    vi b5({17,1,8,2,1,7,6,12,18,21,7,20,18,7,6,7,17,20,15,10,14,16,2,6, 19,3,19,3,6,18,10,11,10,4,17,13,15,9,15,17,11,16,13,1,19,17, 19,17,10,2});
    vi w5({327583,4194,990205,481090,868602,722789,547481,738569,188373, 973550,462208,74066,639614,693164,86808,442101,811939,995334, 551737,335601,147231,93330,799032,130164,839277,757103,234057, 909252,415269,945015,715797,549525,581349,130104,493780,553519, 755216,626951,743631,231151,205857,917585,553454,352015,873807, 573520,569698,317228,754891,875856});
    vi v5({220468,844712,599675,53333,825995,711279,289092,415428,805292, 985205,197039,193974,95433,244829,558762,555423,725065,498922, 519543,4803,305565,61949});
    cout << a.findMin(a5, b5, w5, v5) << '\n';
}
