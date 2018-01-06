// 912E
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

bool prod_overflow(ll a, ll b) {
  return a && a * b / a != b;
}

void gen(ll cur, vll& cands, vi& p, int cur_idx) {
  for (int idx = cur_idx; idx < p.size(); idx++) {
    if (!prod_overflow(cur, p[idx])) {
      cands.pb(cur * p[idx]);
      gen(cur * p[idx], cands, p, idx);
    }
  }
}

int main() {
  int n; cin >> n;
  vi p(n), p_e, p_o;
  forf(i, n) {
    cin >> p[i];
    if (i % 2 == 0) {
      p_e.pb(p[i]);
    } else {
      p_o.pb(p[i]);
    }
  }
  int k; cin >> k;

  vll cands_e, cands_o;
  cands_e.pb(1);
  cands_o.pb(1);
  gen(1, cands_e, p_e, 0);
  gen(1, cands_o, p_o, 0);
  sort(cands_e.begin(), cands_e.end());
  sort(cands_o.begin(), cands_o.end());

  ll lo = 1, hi = 1e18;
  ll ans = hi;
  while (lo <= hi) {
    ll mid = lo + (hi - lo) / 2;
    ll num_at_most = 0;
    int o_idx = cands_o.size() - 1;
    for (int e_idx = 0; e_idx < cands_e.size() && cands_e[e_idx] <= mid; e_idx++) {
      while (o_idx >= 0 && (prod_overflow(cands_e[e_idx], cands_o[o_idx]) ||
                            cands_e[e_idx] * cands_o[o_idx] > mid)) {
        o_idx--;
      }
      num_at_most += o_idx + 1;
    }
    if (num_at_most == k) {
      ans = min(ans, mid);
      hi = mid - 1;
    } else if (num_at_most < k) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  cout << ans << '\n';
}
