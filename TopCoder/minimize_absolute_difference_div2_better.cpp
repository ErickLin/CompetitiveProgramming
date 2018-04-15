#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
#define all(c) (c).begin(), (c).end()
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

class MinimizeAbsoluteDifferenceDiv2 {
 public:
  vi findTriple(int x0, int x1, int x2) {
    vi inp({x0, x1, x2});
    double smallest = 10000;
    vi ans;
    vi abc = {0, 1, 2};
    do {
      double val = abs((double)inp[abc[0]] / inp[abc[1]] - inp[abc[2]]);
      if (val < smallest) {
        smallest = val;
        ans = {abc[0], abc[1], abc[2]};
      }
    } while (next_permutation(all(abc)));
    return ans;
  }
};
