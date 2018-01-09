// 913D
#include <iostream>
#include <vector>
using namespace std;
#define mp make_pair
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

typedef pair<int, pair<int, int>> problem;
int main() {
  int n, T; cin >> n >> T;
  vector<problem> p(n);
  forf(i, n) {
    int a, t; cin >> a >> t;
    p[i] = mp(t, mp(a, i));
  }
  sort(p.begin(), p.end());

  int lo = 0, hi = n, max_s = 0;
  vi best_sol_idxes;
  while (lo <= hi) {
    int s = lo + (hi - lo) / 2;
    int cumul_t = 0;
    vi sol_idxes;
    forf(i, n) {
      if (sol_idxes.size() == s) {
        break;
      }
      if (cumul_t + p[i].first > T) {
        break;
      }
      if (p[i].second.first >= s) {
        cumul_t += p[i].first;
        sol_idxes.pb(i);
        if (sol_idxes.size() == s) {
          break;
        }
      }
    }
    if (sol_idxes.size() == s) {
      if (s > max_s) {
        max_s = s;
        best_sol_idxes = sol_idxes;
      }
      lo = s + 1;
    } else {
      hi = s - 1;
    }
  }
  cout << max_s << '\n' << max_s << '\n';
  for (int idx : best_sol_idxes) {
    cout << p[idx].second.second + 1 << ' ';
  }
  cout << '\n';
}
