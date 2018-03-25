// 957D
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef vector<int> vi;

int main() {
  int n; cin >> n;
  vi m(n), step_monotonic_seq(n);
  int max_seen = 0;
  forf(i, n) {
    cin >> m[i];
    max_seen = max(max_seen, m[i]);
    step_monotonic_seq[i] = max_seen;
  }
  forb(i, n) {
    if (i < n - 1) {
      step_monotonic_seq[i] = max(step_monotonic_seq[i], step_monotonic_seq[i + 1] - 1);
    }
  }
  ll min_sum_below = 0;
  forf(i, n) {
    min_sum_below += step_monotonic_seq[i] - m[i];
  }
  cout << min_sum_below << '\n';
}
