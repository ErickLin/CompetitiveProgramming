// 948C
#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
#define forf(i, n) for (int i = 0; i < n; i++)

int main() {
  int n; cin >> n;
  vi V(n), T(n);
  forf(i, n) {
    cin >> V[i];
  }
  forf(i, n) {
    cin >> T[i];
  }

  map<ll, int> s;
  ll num_piles = 0;
  ll melt_accum = 0;
  forf(i, n) {
    ll ans = 0;
    if (V[i] > 0) {
      s[V[i] + melt_accum]++;
      num_piles++;
    }
    if (T[i] > 0) {
      while (s.size() > 0 && s.begin()->first <= T[i] + melt_accum) {
        ans += (s.begin()->first - melt_accum) * s.begin()->second;
        num_piles -= s.begin()->second;
        s.erase(s.begin());
      }
      ans += num_piles * T[i];
      melt_accum += T[i];
    }
    cout << ans << ' ';
  }
  cout << '\n';
}
