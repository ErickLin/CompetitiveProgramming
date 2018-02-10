#include <iostream>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf2(i, n) for (int i = 0; i <= n; i++)

class ManageSubsequences {
 public:
  bool can_add(int num_to_add, string& s, string& a, string& b) {
    int a_pos = 0, b_pos = 0;

    if (a.size() - a_pos == num_to_add) {
      for (; a_pos < a.size(); a_pos++) {
        if (b[b_pos] == a[a_pos]) {
          b_pos++;
          if (b_pos == b.size()) {
            return false;
          }
        }
      }
    }

    forf(s_pos, s.size()) {
      if (s[s_pos] == b[b_pos]) {
        b_pos++;
        if (b_pos == b.size()) {
          return false;
        }
      }
      if (a_pos < a.size() && s[s_pos] == a[a_pos]) {
        a_pos++;
        if (a.size() - a_pos == num_to_add) {
          for (; a_pos < a.size(); a_pos++) {
            if (b[b_pos] == a[a_pos]) {
              b_pos++;
              if (b_pos == b.size()) {
                return false;
              }
            }
          }
        }
      }
    }

    if (a_pos == a.size()) {
      return true;
    }
    return false;
  }

  int minAdded(string s, string a, string b) {
    forf2(num_to_add, a.size()) {
      if (can_add(num_to_add, s, a, b)) {
        return num_to_add;
      }
    }
    return -1;
  }
};
