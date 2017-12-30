// 908D
#include <iostream>
#include <vector>
using namespace std;
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
#define forb2(i, n) for (int i = n; i >= 0; i--)
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

int MOD = 1e9 + 7;
int exp(int num, ll power) {
  if (power == 0) {
    return 1;
  } else if (power == 1) {
    return num;
  }
  return (ll) exp(num, power % 2) * exp((ll) num * num % MOD, power / 2) % MOD;
}

int inv(int num) {
  return exp(num, MOD - 2);
}

int sum(int a, int b) {
  return ((ll) a + b) % MOD;
}

int diff(int a, int b) {
  return ((ll) a - b + MOD) % MOD;
}

int prod(int a, int b) {
  return (ll) a * b % MOD;
}

int quot(int a, int b) {
  return (ll) a * inv(b) % MOD;
}

int main() {
  int k, pa, pb;
  cin >> k >> pa >> pb;
  int prob_a = quot(pa, pa + pb), prob_b = quot(pb, pa + pb);
  // expected final number of ab subsequences given the present number of a and
  // ab subsequences
  vvll dp(k + 1, vll(k + 1));
  forb2(a, k) {
    dp[a][k] = k;
    //cout << "dp[" << a << "][" << k << "] = " << dp[a][k] << '\n';
    for (int ab = k - a; ab < k; ab++) {
      // if a + ab >= k, then the next b completes the sequence
      // expected value is ab + a * (1 + (prob_a + 2prob_a^2 + ...)) * prob_b =
      //                   ab + a/(1 - prob_a) * (1 + prob_a^2/(1 - prob_a)) * prob_b
      dp[a][ab] = sum(ab, prod(prob_b, quot(a - 1 + quot(1, 1 - prob_a), 1 - prob_a)));
      //cout << "dp[" << a << "][" << ab << "] = " << dp[a][ab] << '\n';
    }
  }
  forb(a, k) {
    forb(ab, k - a) {
      dp[a][ab] = sum(prod(prob_a, dp[a + 1][ab]), prod(prob_b, dp[a][ab + a]));
      //cout << "dp[" << a << "][" << ab << "] = " << dp[a][ab] << '\n';
    }
  }
  cout << dp[1][0] << '\n';
}
