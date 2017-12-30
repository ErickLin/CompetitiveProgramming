// 911A
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

int main() {
  int n;
  cin >> n;
  vi a(n);
  int min_val = INT_MAX;
  forf(i, n) {
    cin >> a[i];
    min_val = min(min_val, a[i]);
  }
  int last_min_idx = -1, min_dist = INT_MAX;
  for (int i = 0; i < n; i++) {
    if (a[i] == min_val) {
      if (last_min_idx != -1) {
        min_dist = min(min_dist, i - last_min_idx);
      }
      last_min_idx = i;
    }
  }
  cout << min_dist << '\n';
}
