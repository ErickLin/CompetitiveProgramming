// 526A
#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef map<int, int> mii;

int get_max_lights(int cur, int n, mii& a) {
  if (cur >= (1 << n)) {
    return 0;
  }
  return max(a[cur << 1] + get_max_lights(cur << 1, n, a),
             a[(cur << 1) + 1] + get_max_lights((cur << 1) + 1, n, a));
}

int num_lights_add(int cur, int cur_lights, int max_lights, int n, mii& a) {
  if (cur >= (1 << n)) {
    return max_lights - cur_lights;
  }
  return num_lights_add(cur << 1, cur_lights + a[cur << 1], max_lights, n, a) + num_lights_add((cur << 1) + 1, cur_lights + a[(cur << 1) + 1], max_lights, n, a);
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
  cout << num_lights_add(1, 0, get_max_lights(1, n, a), n, a) << '\n';
}
