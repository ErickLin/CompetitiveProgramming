// 957E
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
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

template<typename T>
ll count_inversions(vector<T> &arr) {
  if (arr.size() >= 2) {
    vector<T> left(arr.size() >> 1);
    for (int i = 0; i < (arr.size() >> 1); i++) {
      left[i] = arr[i];
    }
    vector<T> right(arr.size() - (arr.size() >> 1));
    for (int i = (arr.size() >> 1); i < arr.size(); i++) {
      right[i - (arr.size() >> 1)] = arr[i];
    }
    ll inversions = count_inversions(left) + count_inversions(right);
    int i = 0;
    int j = 0;
    while (i + j < arr.size()) {
      if (j == right.size() || (i < left.size() && left[i] <= right[j])) {
        arr[i + j] = left[i++];
      } else {
        arr[i + j] = right[j++];
        inversions += left.size() - i;
      }
    }
    return inversions;
  }
  return 0;
}

int sign(int x) {
  return (x > 0) - (x < 0);
}

int w;
struct plane {
  int x, v;
  plane(int x, int v) {
    this->x = x;
    this->v = v;
  }
  plane() : plane(0, 0) {}
  bool tiebreaker(const plane& other) const {
    if (sign(x) == sign(other.x)) {
      return v > other.v;
    } else {
      return v < other.v;
    }
  }
  // natural ordering is the time to origin given wind velocity of -w
  bool operator<(const plane& other) const {
    fraction t1 = fraction(-x, v - w), t2 = fraction(-other.x, other.v - w);
    if (t1 == t2) {
      return tiebreaker(other);
    }
    return t1 < t2;
  }
  bool operator==(const plane& other) const {
    return x == other.x && v == other.v;
  }
  bool operator<=(const plane& other) const {
    return *this < other || *this == other;
  }
};

int main() {
  int n;
  cin >> n >> w;
  vector<plane> planes(n);
  forf(i, n) {
    int x, v;
    cin >> x >> v;
    planes[i] = plane(x, v);
  }
  sort(planes.begin(), planes.end(), [](plane p1, plane p2) {
    // sort by time to origin given wind velocity of w
    fraction t1 = fraction(-p1.x, p1.v + w), t2 = fraction(-p2.x, p2.v + w);
    if (t1 == t2) {
      return !p1.tiebreaker(p2);
    }
    return t1 < t2;
  });
  cout << count_inversions(planes) << '\n';
}
