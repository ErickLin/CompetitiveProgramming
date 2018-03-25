#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;

int gcd(int a, int b) {
  if (max(a, b) % min(a, b) == 0) {
    return min(a, b);
  }
  return gcd(min(a, b), max(a, b) % min(a, b));
}

struct fraction {
  int num, denom;
  fraction(int num, int denom) {
    int gcd_res = gcd(abs(num), abs(denom));
    this->num = num / gcd_res;
    this->denom = denom / gcd_res;
    if (this->denom < 0) {
      this->num *= -1;
      this->denom *= -1;
    }
  }
  fraction() : fraction(1, 1) {}
  bool operator<(const fraction& other) const {
    return (ll)num * other.denom < (ll)other.num * denom;
  }
  bool operator==(const fraction& other) const {
    return (ll)num * other.denom == (ll)other.num * denom;
  }
  bool operator<=(const fraction& other) const {
    return *this < other || *this == other;
  }
  bool operator>(const fraction& other) const { return !(*this <= other); }
  bool operator!=(const fraction& other) const { return !(*this == other); }
  bool operator>=(const fraction& other) const { return !(*this < other); }
};
std::ostream& operator<<(std::ostream& Str, fraction const& f) {
  Str << f.num << '/' << f.denom;
  return Str;
}
