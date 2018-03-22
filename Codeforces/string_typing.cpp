// 954B
#include <iostream>
using namespace std;

int main() {
  int n; cin >> n;
  string s; cin >> s;
  int pos_to_copy = 0;
  for (int len = 1; len <= s.size() / 2; len++) {
    if (s.substr(0, len) == s.substr(len, len)) {
      pos_to_copy = len;
    }
  }
  cout << s.size() - pos_to_copy + (pos_to_copy > 0) << '\n';
}
