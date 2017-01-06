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
    int n, v;
    ll hash;
    cin >> n;
    vi c(n);
    forf(i, n) {
        hash <<= 7;
        cin >> c[i];
        if (i == 0) {
            hash = c[i];
        }
    }
    cin >> v;
    bool found = false;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, greater<pair<ll, ll> > > pq;
    pq.push(mp(0, hash));
    set<int> visited;
    vi amts(n);
    while (!pq.empty() && !found) {
        ll cur = pq.top().second;
        ll amt = pq.top().first;
        //cout << amt << '\n';
        pq.pop();
        if (visited.find(cur) == visited.end()) {
            visited.insert(cur);
            ll temp = cur;
            forb(i, n) {
                amts[i] = temp % 128;
                temp /= 128;
            }
            if (amts[0] == v) {
                cout << amt << '\n';
                found = true;
            }
            forf(i, n) {
                forf(j, n) {
                    if (i != j && amts[i] > 0 && amts[j] < c[j]) {
                        int d = min(amts[i], c[j] - amts[j]);
                        amts[i] -= d;
                        amts[j] += d;
                        temp = 0;
                        forf(k, n) {
                            if (k != 0) {
                                temp <<= 7;
                            }
                            temp += amts[k];
                            //cout << amts[k] << ' ';
                        }
                        //cout << '\n';
                        pq.push(mp(amt + (ll) d, temp));
                        amts[i] += d;
                        amts[j] -= d;
                    }
                }
            }
        }
    }
    if (!found) {
        cout << "impossible\n";
    }
    return 0;
}
