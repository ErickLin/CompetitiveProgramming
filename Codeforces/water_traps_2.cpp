// 954E
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef long long ll;
typedef vector<int> vi;

int main() {
  int n, T; cin >> n >> T;
  vi a(n), t(n);
  forf(i, n) {
    cin >> a[i];
  }
  forf(i, n) {
    cin >> t[i];
  }
  map<int, ll> unique_taps;
  forf(i, n) {
    unique_taps[t[i]] += a[i];
  }
  vector<pair<int, ll>> taps;
  for (const auto& kv : unique_taps) {
    taps.push_back({kv.first, kv.second});
  }
  n = taps.size();

  double amt = 0;

  int lo = 0, hi = n - 1, hi_idx = n + 1, lo_idx = -2;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (taps[mid].first == T) {
      amt += taps[mid].second;
      hi_idx = mid + 1;
      lo_idx = mid - 1;
      break;
    } else if (taps[mid].first > T) {
      hi_idx = min(hi_idx, mid);
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  if (lo_idx == -2 && hi_idx != n + 1) {
    lo_idx = hi_idx - 1;
  }

  ll hi_left_over = 0;
  ll lo_left_over = 0;
  while (lo_idx >= 0 && hi_idx < n) {
    if (!hi_left_over) {
      hi_left_over = (ll) (taps[hi_idx].first - T) * taps[hi_idx].second;
    }
    if (!lo_left_over) {
      lo_left_over = (ll) (T - taps[lo_idx].first) * taps[lo_idx].second;
    }
    ll taken_from_each = min(hi_left_over, lo_left_over);
    hi_left_over -= taken_from_each;
    lo_left_over -= taken_from_each;
    if (!hi_left_over) {
      amt += taps[hi_idx].second;
      hi_idx++;
      if (hi_idx == n && lo_left_over) {
        amt += taps[lo_idx].second - (double) lo_left_over / (T - taps[lo_idx].first);
      }
    }
    if (!lo_left_over) {
      amt += taps[lo_idx].second;
      lo_idx--;
      if (lo_idx == -1 && hi_left_over) {
        amt += taps[hi_idx].second - (double) hi_left_over / (taps[hi_idx].first - T);
      }
    }
  }

  printf("%.10f\n", amt);
}
