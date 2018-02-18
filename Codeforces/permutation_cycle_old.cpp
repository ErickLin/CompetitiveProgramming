// 932C
#include <iostream>
#include <vector>
using namespace std;
typedef vector<bool> vb;

bool is_lin_comb_of_a_and_b(int x, int a, int b, vb& cache, int& k, int& l) {
  if (cache[x]) {
  } else if (x % a == 0 || x % b == 0) {
    cache[x] = true;
  } else {
    if (x > a) {
      k++;
      cache[x] = is_lin_comb_of_a_and_b(x - a, a, b, cache, k, l);
      k--;
    }
    if (x > b) {
      l++;
      cache[x] = is_lin_comb_of_a_and_b(x - b, a, b, cache, k, l);
      l--;
    }
  }
  return cache[x];
}

int main() {
  int n, a, b;
  cin >> n >> a >> b;
  vb cache(1000001);
  int k = 0, l = 0;
  if (!is_lin_comb_of_a_and_b(n, a, b, cache, k, l)) {
    cout << "-1\n";
    return 0;
  }
  cout << k << ' ' << l << '\n';
}
