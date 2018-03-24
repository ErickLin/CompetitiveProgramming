// 955C
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define ins insert
#define pb push_back
typedef long long ll;

int main() {
  vector<ll> pows_cache_dup;
  pows_cache_dup.pb(1);
  for (ll a = 2; a <= 1e6; a++) {
    for (ll ap = a * a; ; ap *= a) {
      ll root = sqrtl(ap);
      if (ap <= 1e12 || root * root != ap) {
        pows_cache_dup.pb(ap);
      }
      if (ap > 1e18 / a) {
        break;
      }
    }
  }
  sort(pows_cache_dup.begin(), pows_cache_dup.end());
  vector<ll> pows_cache;
  forf(i, pows_cache_dup.size()) {
    if (!i || pows_cache_dup[i] != pows_cache_dup[i - 1]) {
      pows_cache.pb(pows_cache_dup[i]);
    }
  }
  /*
  for (ll num : pows_cache) {
    cout << num << ' ';
  }
  cout << '\n';
  cout << pows_cache.size() << '\n';
  */

  int q; cin >> q;
  forf(i, q) {
    ll l, r; cin >> l >> r;
    ll ans = 0;
    {
      auto it = upper_bound(pows_cache.begin(), pows_cache.end(), r);
      ans += it - pows_cache.begin();
    }
    {
      auto it = lower_bound(pows_cache.begin(), pows_cache.end(), l);
      ans -= it - pows_cache.begin();
    }
    if (l > 1e12) {
      ll root = sqrtl(l);
      ans -= root - 1e6;
      if (root * root == l) {
        ans++;
      }
    }
    if (r > 1e12) {
      ll root = sqrtl(r);
      ans += root - 1e6;
    }
    cout << ans << '\n';
  }
}
