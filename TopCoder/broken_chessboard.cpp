#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<string> vs;

class BrokenChessboard {
  public:
    int minimumFixes(vs board) {
      int n = board.size();
      int m = board[0].size();
      int min_swaps = n * m;
      forf(k, 2) {
        int num_swaps = 0;
        forf(i, n) {
          forf(j, m) {
            if (board[i][j] == (((i + j + k) % 2) ? 'B' : 'W')) {
              num_swaps++;
            }
          }
        }
        min_swaps = min(min_swaps, num_swaps);
      }
      return min_swaps;
    }
};
