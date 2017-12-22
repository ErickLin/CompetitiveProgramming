#include <algorithm>
using namespace std;
typedef long long ll;

int exp(int num, ll power, int mod) {
  if (power == 0) {
    return 1;
  } else if (power == 1) {
    return num;
  }
  return (ll) exp(num, power % 2, mod) * exp((ll) num * num % mod, power / 2, mod) % mod;
}
