#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class PaintTheRoom {
  public:
    string canPaintEvenly(int R, int C, int K) {
      return (K == 1 || R % 2 == 0 || C % 2 == 0) ? "Paint" : "Cannot paint";
    }
};

int main() {
  PaintTheRoom a;
  cout << a.canPaintEvenly(1, 1, 1) << '\n';
  cout << a.canPaintEvenly(1, 1, 2) << '\n';
  cout << a.canPaintEvenly(1, 2, 2) << '\n';
  cout << a.canPaintEvenly(2, 2, 3) << '\n';
}
