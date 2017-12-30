// 908C
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef vector<double> vd;

int main() {
  int n, r;
  cin >> n >> r;
  vi x(n);
  forf(i, n) {
    cin >> x[i];
  }
  vd y(n);
  fill(y.begin(), y.end(), r);
  printf("%.10f", y[0]);
  for (int i = 1; i < n; i++) {
    forf(j, i) {
      if (abs(x[i] - x[j]) <= 2 * r) {
        double dy = sqrt(4 * r * r - (x[i] - x[j]) * (x[i] - x[j]));
        y[i] = max(y[i], y[j] + dy);
      }
    }
    printf(" %.10f", y[i]);
  }
  printf("\n");
}
