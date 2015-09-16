#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class PaintTheRoom {
    public:
        string canPaintEvenly(int R, int C, int K) {
            bool canPaint = false;
            if (K == 1 || R % 2 == 0 || C % 2 == 0) {
                canPaint = true;
            } else {
                canPaint = false;
            }
            if (canPaint) {
                return "Paint";
            } else {
                return "Cannot paint";
            }
        }
};

int main() {
    PaintTheRoom a;
    cout << a.canPaintEvenly(1, 1, 1) << '\n';
    cout << a.canPaintEvenly(1, 1, 2) << '\n';
    cout << a.canPaintEvenly(1, 2, 2) << '\n';
    cout << a.canPaintEvenly(2, 2, 3) << '\n';
    for (int r = 1; r <= 50; r++) {
        for (int c = 1; c <= 50; c++) {
        }
    }
}
