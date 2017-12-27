// 909A
#include <iostream>
using namespace std;

int main() {
  string first, last;
  cin >> first >> last;
  string res;
  res += first[0];
  for (int i = 1; i < first.size(); i++) {
    if (first[i] >= last[0]) {
      break;
    }
    res += first[i];
  }
  res += last[0];
  cout << res << '\n';
}
