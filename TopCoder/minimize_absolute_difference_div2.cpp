#include <cmath>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

class MinimizeAbsoluteDifferenceDiv2 {
 public:
  vi findTriple(int x0, int x1, int x2) {
    double smallest = abs((double)x0 / x1 - x2);
    vi ans = {0, 1, 2};
    vi inp({x0, x1, x2});
    forf(i, 3) {
      forf(j, 3) {
        forf(k, 3) {
          if (i == j || i == k || j == k) {
            continue;
          }
          double val = abs((double)inp[i] / inp[j] - inp[k]);
          //cout << i << ' ' << j << ' ' << k << ' ' << val << '\n';
          if (val < smallest) {
            smallest = val;
            ans = {i, j, k};
          }
        }
      }
    }
    return ans;
  }
};
