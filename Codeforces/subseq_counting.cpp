// 960C
#include <iostream>
#include <vector>
using namespace std;
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
typedef long long ll;
typedef vector<ll> vll;

int num_subseq(int sz) {
  return (1 << sz) - 1;
}

int main() {
  int x, d; cin >> x >> d;
  int sz = 1;
  while (num_subseq(sz + 1) <= x) {
    sz++;
  }

  vll ans;
  ll elem = 1;
  while (x) {
    forf(i, sz) {
      ans.pb(elem);
    }
    elem += d;

    x -= num_subseq(sz);
    //cout << sz << '\n';
    while (num_subseq(sz) > x) {
      sz--;
    }
  }

  if (ans.size() > 1e4) {
    cout << "-1\n";
    return 0;
  }
  cout << ans.size() << '\n';
  for (ll i : ans) {
    cout << i << ' ';
  }
  cout << '\n';
}
