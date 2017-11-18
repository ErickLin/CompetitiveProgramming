#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vb> vvb;

class WalkingToSchool {
  public:
    int gcd(int a, int b) {
      if (min(a, b) == 0) {
        return max(a, b);
      }
      return gcd(min(a, b), max(a, b) % min(a, b));
    }

    bool infWalkExists(int s, int t, int n, vi& from, vi& to) {
      const int m = from.size(), max_loop_len = 2 * n;

      // compute both whether a k-walk exists from s to each vertex for all k
      // and whether a path exists from s to t
      bool walk_exists = false;
      vvb k_walk_exists(n, vb(max_loop_len + 1));
      k_walk_exists[s][0] = true;
      for (int loop_len = 0; loop_len < max_loop_len; loop_len++) {
        for (int i = 0; i < m; i++) {
          if (k_walk_exists[from[i]][loop_len]) {
            k_walk_exists[to[i]][loop_len + 1] = true;

            if (to[i] == t) {
              walk_exists = true;
            }
          }
        }
      }
      if (!walk_exists) {
        return false;
      }

      for (int loop1_len = 2; loop1_len <= max_loop_len; loop1_len++) {
        if (!k_walk_exists[s][loop1_len]) {
          continue;
        }
        for (int loop2_len = 2; loop2_len < loop1_len; loop2_len++) {
          if (k_walk_exists[s][loop2_len] && gcd(loop1_len, loop2_len) == 1) {
            return true;
          }
        }
      }
      return false;
    }

    string canWalkExactly(int n, vi from, vi to) {
      return infWalkExists(0, 1, n, from, to) && infWalkExists(1, 0, n, from, to)
          ? "Freedom" : "Chores";
    }
};

int main() {
  WalkingToSchool a;
  cout << a.canWalkExactly(2, {0, 1}, {1, 0}) << '\n';
  cout << a.canWalkExactly(3, {0, 1, 1, 2}, {1, 0, 2, 0}) << '\n';
  cout << a.canWalkExactly(4, {0, 2, 2, 3, 0}, {2, 0, 3, 0, 1}) << '\n';
  cout << a.canWalkExactly(10, {0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 5, 5, 5, 6, 6, 6, 7, 8, 9, 9, 9, 9}, {4, 5, 6, 7, 9, 4, 6, 0, 1, 3, 8, 4, 6, 1, 4, 8, 1, 7, 8, 1, 4, 2, 5, 6, 8}) << '\n';
  cout << a.canWalkExactly(8, {0, 1, 4, 6, 7, 5, 2, 3, 0}, {1, 4, 6, 7, 5, 2, 3, 0, 7}) << '\n';
  cout << a.canWalkExactly(2000, {}, {}) << '\n';
}
