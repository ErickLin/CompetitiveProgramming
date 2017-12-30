// 908E
#include <iostream>
#include <vector>
using namespace std;
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<string> vs;

vvll comb(int n, int mod = 1e9 + 7) {
  vvll comb(n + 1, vll(n + 1));
  comb[0][0] = 1;
  for (int i = 0; i <= n; i++) {
    comb[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
    }
  }
  return comb;
}

vll bell(int n, vvll comb, int mod = 1e9 + 7) {
  vll B(n + 1);
  B[0] = 1;
  for (int i = 1; i <= n; i++) {
    forf(k, i) {
      B[i] = (B[i] + B[k] * comb[i - 1][k] % mod) % mod;
    }
  }
  return B;
}

int main() {
  int m, n; cin >> m >> n;
  vs T(n);
  forf(i, n) {
    cin >> T[i];
  }
  vll masks(m);
  forf(j, m) {
    forf(i, n) {
      if (T[i][j] == '1') {
        masks[j] |= 1LL << i;
      }
    }
  }

  // The sizes of the sets in the partition P for which any
  // partition corresponding to a good set must be a refinement.
  // Any partition that is not a refinement of P necessarily corresponds to a
  // set that does not include T.
  vi split_sizes;
  // Whether each bit has already been added to a partition.
  vb included(m);
  forf(bit, m) {
    if (included[bit]) {
      continue;
    }
    included[bit] = true;
    int cur_size = 1;
    for (int j = bit + 1; j < m; j++) {
      if (masks[bit] == masks[j]) {
        included[j] = true;
        cur_size++;
      }
    }
    split_sizes.pb(cur_size);
  }
  if (split_sizes.empty()) {
    split_sizes.pb(m);
  }

  int ans = 1;
  vll B = bell(m, comb(m));
  for (int cur_size : split_sizes) {
    ans = ans * B[cur_size] % (ll) (1e9 + 7);
  }
  cout << ans << '\n';
}
