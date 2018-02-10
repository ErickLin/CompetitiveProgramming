#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<bool> vb;

class RareItems {
 public:
  void recurse(double& prob, double prior, int num_calced, int num_picked, vb& picked, int last_picked, vd& p) {
    int n = p.size();
    if (num_calced == num_picked) {
      double rem = 0.0;
      forf(i, n) {
        if (!picked[i]) {
          rem += p[i];
        }
        cout << picked[i] << ' ';
      }
      cout << prior << ' ' << rem << ' ' << prior * rem << '\n';
      prob += prior * rem;
    } else {
      for (int i = last_picked + 1; i < n; i++) {
        if (!picked[i]) {
          picked[i] = true;
          recurse(prob, prior * p[i], num_calced + 1, num_picked, picked, i, p);
          picked[i] = false;
        }
      }
    }
  }

  double expectedPurchases(vi frequency) {
    int n = frequency.size();
    int sum_frequencies = 0;
    forf(i, n) {
      sum_frequencies += frequency[i];
    }
    vd p(n);
    forf(i, n) {
      p[i] = frequency[i] * 1.0 / sum_frequencies;
    }
    double ET = 1.0;
    for (int num_picked = 1; num_picked < n; num_picked++) {
      double prob = 0.0;
      vb picked(n);
      recurse(prob, 1.0, 0, num_picked, picked, -1, p);
      ET += 1.0 / prob;
      cout << prob << ' ' << 1.0 / prob << '\n';
    }
    return ET;
  }
};

int main() {
  RareItems a;
  //cout << a.expectedPurchases({1}) << '\n';
  //cout << a.expectedPurchases({2, 2}) << '\n';
  cout << a.expectedPurchases({1, 1, 100}) << '\n';
  cout << a.expectedPurchases({1, 1, 1, 1}) << '\n';
}
