//#include <iostream>
#include <map>
#include <string>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)

class JustBrackets {
  map<string, string> dp;

  string recurse(string s) {
    if (dp.count(s)) {
      return dp[s];
    }

    if (s.size() <= 2) {
      dp[s] = s;
      return s;
    }

    string ret = s;
    forf(i, s.size() - 1) {
      if (s[i] == '(' && s[i + 1] == ')') {
        ret = min(ret, recurse(s.substr(0, i) + s.substr(i + 2)));
      }
    }
    dp[s] = ret;
    return ret;
  }

 public:
  string getSmallest(string s) {
    return recurse(s);
  }
};

/*
int main() {
  JustBrackets a;
  cout << a.getSmallest("()()") << '\n';
}
*/
