#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

class SoManyRectangles {
 public:
  int maxOverlap(vi x1, vi y1, vi x2, vi y2) {
    int n = x1.size();
    set<int> xs, ys;
    forf(i, n) {
      xs.insert(x1[i]);
      xs.insert(x2[i]);
      ys.insert(y1[i]);
      ys.insert(y2[i]);
    }
    int max_overlap = 0;
    for (int x : xs) {
      for (int y : ys) {
        int overlap = 0;
        forf(i, n) {
          if (x1[i] <= x && y1[i] <= y && x2[i] > x && y2[i] > y) {
            overlap++;
          }
        }
        max_overlap = max(max_overlap, overlap);
      }
    }
    return max_overlap;
  }
};
