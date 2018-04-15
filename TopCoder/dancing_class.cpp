#include <string>
#include <vector>
using namespace std;
typedef vector<double> vd;
typedef vector<vd> vvd;

class DancingClass {
  double exp(double num, int power) {
    if (power == 0) {
      return 1;
    } else if (power == 1) {
      return num;
    }
    return exp(num, power % 2) * exp(num * num, power / 2);
  }

  vvd get_comb(int n) {
   vvd comb(n + 1, vd(n + 1));
   comb[0][0] = 1;
   for (int i = 0; i <= n; i++) {
     comb[i][0] = 1;
     for (int j = 1; j <= i; j++) {
       comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
     }
   }
   return comb;
  }

 public:
  string checkOdds(int n, int k) {
    vvd comb = get_comb(n);
    double prob = 0;
    for (int boys = 1; boys < n; boys++) {
      if (boys * (n - boys) >= k) {
        prob += comb[n][boys];
      }
    }
    prob /= exp(2, n);
    if (prob == 0.5) {
      return "Equal";
    } else if (prob > 0.5) {
      return "High";
    } else {
      return "Low";
    }
  }
};
