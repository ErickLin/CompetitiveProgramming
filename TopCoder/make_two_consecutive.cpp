#include <iostream>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)

class MakeTwoConsecutive {
 public:
  string solve(string s) {
    if (s.size() == 1) {
      return "Impossible";
    }
    forf(i, s.size()) {
      string t = s;
      t.erase(i, 1);
      forf(j, t.size() - 1) {
        if (t[j] == t[j + 1]) {
          return "Possible";
        }
      }
    }
    return "Impossible";
  }
};
