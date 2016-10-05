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

int main() {
    int nr, nc, n, m;
    cin >> nr >> nc >> n >> m;
    vector<pii> remv(n), keep(m);
    set<int> rs, cs;
    forf(i, n) {
        int r, c;
        cin >> r >> c;
        remv[i] = mp(r, c);
        if (r + 8 >= 0 && r + 8 < nr) {
            rs.insert(r);
        }
        if (c + 5 >= 0 && c + 5 < nc) {
            cs.insert(c);
        }
    }
    forf(i, m) {
        int r, c;
        cin >> r >> c;
        keep[i] = mp(r, c);
        if (r + 8 >= 0 && r + 8 < nr) {
            rs.insert(r);
        }
        if (c + 5 >= 0 && c + 5 < nc) {
            cs.insert(c);
        }
    }
    vi rsv(rs.begin(), rs.end());
    vi csv(cs.begin(), cs.end());
    vvi dpremv(rsv.size(), vi(csv.size()));
    vvi dpkeep(rsv.size(), vi(csv.size()));
    forf(i, rsv.size()) {
        forf(j, csv.size()) {
            int r = rsv[i];
            int c = csv[j];
            forf(k, n) {
                if (remv[k].first <= r && remv[k].second <= c) {
                    dpremv[i][j]++;
                }
            }
            forf(k, m) {
                if (keep[k].first <= r && keep[k].second <= c) {
                    dpkeep[i][j]++;
                }
            }
        }
    }
    int mintomove = n == 0 ? 0 : n + m;
    forf(i, rsv.size()) {
        forf(j, csv.size()) {
            for (int k = i; k < rsv.size(); k++) {
                for (int l = j; l < csv.size(); l++) {
                    int remvtomove = n - dpremv[k][l];
                    if (i >= 1) {
                        remvtomove += dpremv[i - 1][l];
                    }
                    if (j >= 1) {
                        remvtomove += dpremv[k][j - 1];
                    }
                    if (i >= 1 && j >= 1) {
                        remvtomove -= dpremv[i - 1][j - 1];
                    }
                    int keeptomove = dpkeep[k][l];
                    if (i >= 1) {
                        keeptomove -= dpkeep[i - 1][l];
                    }
                    if (j >= 1) {
                        keeptomove -= dpkeep[k][j - 1];
                    }
                    if (i >= 1 && j >= 1) {
                        keeptomove += dpkeep[i - 1][j - 1];
                    }
                    mintomove = min(mintomove, remvtomove + keeptomove);
                }
            }
        }
    }
    cout << mintomove << '\n';
    return 0;
}
