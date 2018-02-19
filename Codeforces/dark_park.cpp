// 526B
#include <cmath>
#include <iostream>
#include <map>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef pair<int, int> ii;
typedef map<int, int> mii;

ii num_lights_add_and_max(int cur, int n, mii& a) {
  if (cur >= (1 << n)) {
    return {0, 0};
  }
  ii left = num_lights_add_and_max(cur << 1, n, a);
  ii right = num_lights_add_and_max((cur << 1) + 1, n, a);
  return {left.first + right.first + abs(a[cur << 1] + left.second - (a[(cur << 1) + 1] + right.second)), max(a[cur << 1] + left.second, a[(cur << 1) + 1] + right.second)};
}

int main() {
  int n;
  cin >> n;
  mii a;
  for (int i = 2; i <= (1 << (n + 1)) - 1; i++) {
    int val;
    cin >> val;
    a[i] = val;
  }
  cout << num_lights_add_and_max(1, n, a).first << '\n';
}
