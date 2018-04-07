// 960D
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb2(i, n) for (int i = n; i >= 0; i--)
typedef long long ll;
typedef vector<ll> vll;

int get_level(ll x) {
  int ret = 0;
  for (int i = 0; x && i < 64; i++) {
    if (x & 1) {
      ret = i;
    }
    x >>= 1LL;
  }
  return ret;
}

int main() {
  int q;
  scanf("%d", &q);
  vll val_shift(63), node_shift(63);
  forf(i, q) {
    int t;
    ll x;
    scanf("%d%llu", &t, &x);
    if (t == 1) {
      ll k;
      scanf("%llu", &k);
      int level = get_level(x);
      ll level_size = 1LL << level;
      k %= level_size;
      val_shift[level] = (val_shift[level] - k + level_size) % level_size;
    } else if (t == 2) {
      ll k;
      scanf("%llu", &k);
      int level = get_level(x);
      ll level_size = 1LL << level;
      k %= level_size;
      node_shift[level] = (node_shift[level] - k + level_size) % level_size;
    } else {
      ll cur = x;
      int start_level = get_level(x);
      ll level_size = 1LL << start_level;
      forb2(level, start_level) {
        printf("%llu ", cur);
        if (level == 0) {
          break;
        }
        cur -= val_shift[level];
        if (cur < level_size) {
          cur += level_size;
        }
        cur -= node_shift[level];
        if (cur < level_size) {
          cur += level_size;
        }

        cur >>= 1LL;
        int next_level = level - 1;
        ll next_level_size = level_size >> 1LL;
        cur += val_shift[next_level];
        if (cur >= level_size) {
          cur -= next_level_size;
        }

        level_size = next_level_size;
      }
      printf("\n");
    }
  }
}
