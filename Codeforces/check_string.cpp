// 960A
#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)

int main() {
  string s;
  cin >> s;
  map<char, int> count;
  forf(i, s.size()) {
    char c = s[i];
    count[c]++;
    if (i > 0 && s[i] < s[i - 1]) {
      cout << "NO\n";
      return 0;
    }
  }
  if (count['a'] > 0 && count['b'] > 0 && (count['a'] == count['c'] || count['b'] == count['c'])) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
}
