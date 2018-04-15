#include <cmath>
#include <iostream>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)

bool is_prime(int p) {
  if (p <= 1) {
    return false;
  }
  for (int i = 2; i <= sqrt(p); i++) {
    if (p % i == 0) {
      return false;
    }
  }
  return true;
}

class RingLex {
 public:
  string getmin(string s) {
    int n = s.size();
    string ret;
    forf(i, n) {
      ret += 'z';
    }
    forf(x, 50) {
      forf(p, n) {
        if (is_prime(p)) {
          string new_str;
          forf(i, n) {
            new_str += s[(x + i * p) % n];
          }
          ret = min(ret, new_str);
        }
      }
    }
    return ret;
  }
};
