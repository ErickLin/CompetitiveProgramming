// 948C
#include <iostream>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
#define ins insert
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

  multiset<ll> s;
  ll melt_accum = 0;
  forf(i, n) {
    ll ans = 0;
    s.ins(V[i] + melt_accum);
    while (s.size() > 0 && *s.begin() <= T[i] + melt_accum) {
      ans += *s.begin() - melt_accum;
      s.erase(s.begin());
    }
    ans += (ll) s.size() * T[i];
    melt_accum += T[i];
    cout << ans << ' ';
  }
  cout << '\n';
}
