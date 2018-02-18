// 938C
#include <cmath>
#include <iostream>
#include <map>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef long long ll;
typedef pair<int, int> ii;

ll orig_sol(int n, int m) {
  return (ll) n * n - (ll) (n / m) * (n / m);
}

int main() {
  int t;
  cin >> t;

  map<int, ii> ans;
  forf3(n_i, 1000) {
    forf3(m_i, n_i) {
      ans[orig_sol(n_i, m_i)] = mp(n_i, m_i);
    }
  }

  forf(i, t) {
    int x;
    cin >> x;
    if (x == 0) {
      cout << "1 1\n";
      continue;
    }

    if (ans.count(x)) {
      cout << ans[x].first << ' ' << ans[x].second << '\n';
      continue;
    }

    int sqrt_x = (int) sqrt(x);
    bool ans_found = false;
    forf3(m_i, sqrt_x) {
      if (m_i == 1) continue;
      for (int n_i = sqrt_x; ; n_i++) {
        ll temp = orig_sol(n_i, m_i);
        //cout << m_i << ' ' << n_i << ' ' << temp << ' ' << x << '\n';
        if (temp == (ll) x) {
          cout << n_i << ' ' << m_i << '\n';
          ans_found = true;
        }
        if (temp >= (ll) x) {
          break;
        }
      }
      if (ans_found) {
        break;
      }
    }
    if (!ans_found) cout << "-1\n";
  }
}
