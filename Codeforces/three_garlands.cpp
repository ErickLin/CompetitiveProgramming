// 911C
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;

bool always_lit(vi& k) {
  return k[0] == 1 || k[1] == 2 || (k[0] == 3 && k[2] == 3) ||
         (k[0] == 2 && k[1] == 4 && k[2] == 4);
}

int main() {
  vi k(3);
  cin >> k[0] >> k[1] >> k[2];
  sort(k.begin(), k.end());
  cout << (always_lit(k) ? "YES" : "NO") << '\n';
}
