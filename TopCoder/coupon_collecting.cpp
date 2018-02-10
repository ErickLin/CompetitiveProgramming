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
  void recurse(double& ET, int num_calced, int num_picked, int last_picked, double running_sum, vd& p) {
    if (num_calced == num_picked) {
      ET += ((num_picked % 2 == 1) ? 1.0 : -1.0) / running_sum;
    } else {
      int n = p.size();
      for (int i = last_picked + 1; i < n; i++) {
        recurse(ET, num_calced + 1, num_picked, i, running_sum + p[i], p);
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
    // E[T] = \sum_i 1/p_i - \sum_{i < j} 1/(p_i + p_j) + \sum{i < j < k} 1/(p_i + p_j + p_k) - ... + (-1)^{n+1} 1/(p_1 + ... + p_n)
    // (http://mat.uab.cat/matmat/PDFv2014/v2014n02.pdf)
    double ET = 0.0;
    for (int i = 1; i <= n; i++) {
      recurse(ET, 0, i, -1, 0.0, p);
    }
    return ET;
  }
};
