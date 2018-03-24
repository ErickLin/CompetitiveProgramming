// 955A
#include <iostream>
#include <cmath>
using namespace std;
typedef pair<int, int> ii;

int time_until(ii t1, ii t2) {
  if (t2.first == t1.first) {
    return max(t2.second - t1.second, 0);
  } else if (t2.first < t1.first) {
    return 0;
  } else {
    return (t2.first - t1.first) * 60 + t2.second - t1.second;
  }
}

int main() {
  int hh, mm; cin >> hh >> mm;
  int h, d, c, n; cin >> h >> d >> c >> n;
  double ans = min(ceil((double) h / n) * c, ceil((double) (h + time_until({hh, mm}, {20, 0}) * d) / n) * c * 0.8);
  printf("%.10f\n", ans);
}
