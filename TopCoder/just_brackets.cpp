#include <string>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define pb push_back

class JustBrackets {
  string recurse(string s) {
    vector<string> best_inside;
    int imbalance = 0, prev_balanced = -1;
    forf(i, s.size()) {
      if (s[i] == '(') {
        imbalance++;
      } else {
        imbalance--;
      }
      if (imbalance == 0) {
        string append = recurse(s.substr(prev_balanced + 2, i - prev_balanced - 2));
        while (!best_inside.empty() && best_inside.back() > append) {
          best_inside.pop_back();
        }
        best_inside.pb(append);
        prev_balanced = i;
      }
    }
    string ret = "(";
    for (string s : best_inside) {
      ret += s;
    }
    return ret + ")";
  }

 public:
  string getSmallest(string s) {
    string ret = s;
    // answer is same as that for lexicographically smallest balanced substring
    int imbalance = 0, prev_balanced = -1;
    forf(i, s.size()) {
      if (s[i] == '(') {
        imbalance++;
      } else {
        imbalance--;
      }
      if (imbalance == 0) {
        ret = min(ret, recurse(s.substr(prev_balanced + 2, i - prev_balanced - 2)));
        prev_balanced = i;
      }
    }
    return ret;
  }
};
