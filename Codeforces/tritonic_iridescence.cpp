// 957A
#include <iostream>
#include <set>
using namespace std;
#define ins insert

bool valid(int n, string& s) {
  for (int i = 1; i < n; i++) {
    if (s[i] != '?' && s[i] == s[i - 1]) {
      return false;
    }
  }
  for (int i = 0; i < n; i++) {
    if (s[i] == '?') {
      set<char> has_on_one_side;
      if (i > 0 && s[i - 1] != '?') {
        has_on_one_side.ins(s[i - 1]);
      }
      if (i < n - 1 && s[i + 1] != '?') {
        has_on_one_side.ins(s[i + 1]);
      }
      if (has_on_one_side.size() < 2) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  int n; cin >> n;
  string s; cin >> s;
  cout << (valid(n, s) ? "Yes" : "No") << '\n';
}
