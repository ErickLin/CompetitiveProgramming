// 954B
#include <iostream>
using namespace std;

int main() {
  int n; cin >> n;
  string s; cin >> s;
  int num_typed = 1, moves = 1;
  while (num_typed < n) {
    if (num_typed + num_typed <= n && s.substr(0, num_typed) == s.substr(num_typed, num_typed)) {
      num_typed += num_typed;
    } else {
      num_typed++;
    }
    moves++;
  }
  cout << moves << '\n';
}
