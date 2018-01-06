// 912E
#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef long long ll;
typedef vector<int> vi;

void gen(ll cur, set<ll>& cands, vi& p) {
  for (int prime : p) {
    // detect overflow
    if (cur * prime > max(0ll, cur) && !cands.count(cur * prime)) {
      cands.insert(cur * prime);
      gen(cur * prime, cands, p);
    }
  }
}

int main() {
  int n;
  cin >> n;
  vi p(n);
  forf(i, n) {
    cin >> p[i];
  }
  int k;
  cin >> k;

  set<ll> cands;
  cands.insert(1);
  gen(1, cands, p);

  set<ll>::iterator it = cands.begin();
  for (int i = 1; it != cands.end() && i < k; it++, i++);
  cout << *it << '\n';
}
