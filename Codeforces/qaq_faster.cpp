// 894A
#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)

int main() {
  string s;
  cin >> s;
  int ans = 0;
  forf(i, s.size()) {
    for (int j = i + 1; j < s.size(); j++) {
      for (int k = j + 1; k < s.size(); k++) {
        if (s[i] == 'Q' && s[j] == 'A' && s[k] == 'Q') {
          ans++;
        }
      }
    }
  }
  cout << ans << '\n';
}
