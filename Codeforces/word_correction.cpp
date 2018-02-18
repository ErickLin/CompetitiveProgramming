// 938A
#include <iostream>
using namespace std;

bool is_vowel(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int main() {
  int n;
  string s;
  cin >> n >> s;
  for (int i = 1; i < s.size();) {
    if (is_vowel(s[i]) && is_vowel(s[i - 1])) {
      s.erase(i, 1);
    } else {
      i++;
    }
  }
  cout << s << '\n';
}
