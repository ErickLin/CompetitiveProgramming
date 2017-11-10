#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
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
typedef vector<vd> vvd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
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

int main() {
  int n = 10;
  vll usage(n), recovery(n);
  forf(i, n) {
    cin >> usage[i] >> recovery[i];
  }
  vll u(n), r(n), start(n);
  forf(i, n) {
    cin >> u[i] >> r[i] >> start[i];
  }
  ll t = 0;
  forf(rep, 3) {
    forf(i, n) {
      // Wait for other person
      if (t >= start[i]) {
        ll phase_t = (t - start[i]) % (u[i] + r[i]);
        if (phase_t < u[i]) {
          t += u[i] - phase_t;
        }
      }
      // If the other person waited longer than recovery time
      if (t + usage[i] >= start[i]) {
        if (t < start[i]) {
          start[i] = t + usage[i];
        } else {
          ll phase_t = (t - start[i]) % (u[i] + r[i]);
          ll phase_new_t = (t + usage[i] - start[i]) % (u[i] + r[i]);
          if (usage[i] > r[i] || (phase_t >= u[i] && phase_new_t < u[i])) {
            start[i] = t + usage[i];
          }
        }
      }
      t += usage[i] + recovery[i];
    }
  }
  t -= recovery[n - 1];
  cout << t << '\n';
}
