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

  double hi_left_over = 0;
  double lo_left_over = 0;
  while (lo_idx >= 0 && hi_idx < n) {
    if (abs(hi_left_over) < 1e-10) {
      hi_left_over = (double) (taps[hi_idx].first - T) * taps[hi_idx].second;
    }
    if (abs(lo_left_over) < 1e-10) {
      lo_left_over = (double) (T - taps[lo_idx].first) * taps[lo_idx].second;
    }
    double taken_from_each = min(hi_left_over, lo_left_over);
    amt += taken_from_each / (taps[hi_idx].first - T) + taken_from_each / (T - taps[lo_idx].first);
    hi_left_over -= taken_from_each;
    lo_left_over -= taken_from_each;
    if (abs(hi_left_over) < 1e-10) {
      hi_idx++;
    }
    if (abs(lo_left_over) < 1e-10) {
      lo_idx--;
    }
  }

  printf("%.10f\n", amt);
}
