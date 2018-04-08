#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<bool> vb;
typedef vector<vb> vvb;

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int a; cin >> a;
    vvb filled(1001, vb(1001));
    cout << "2 2\n";
    int min_i, min_j, max_i, max_j;
    cin >> min_i >> min_j;
    filled[min_i][min_j] = true;
    max_i = min_i;
    max_j = min_j;
    bool done = false, error = false;
    while ((max_i - min_i + 1) * (max_j - min_j + 1) < a) {
      cout << max_i + 1 << ' ' << max_j + 1 << '\n';
      int i, j; cin >> i >> j;
      if (i == 0 && j == 0) {
        done = true;
        break;
      }
      if (i == -1 && j == -1) {
        error = true;
        return 0;
      }
      filled[i][j] = true;
      max_i = max(max_i, i);
      max_j = max(max_j, j);
    }
    //cout << min_i << ' ' << min_j << ' ' << max_i << ' ' << max_j << '\n';
    if (done) continue;
    for (int i_c = min_i; i_c <= max_i; i_c++) {
      for (int j_c = min_j; j_c <= max_j; j_c++) {
        while (!filled[i_c][j_c]) {
          cout << min(i_c + 1, max_i - 1) << ' ' << min(j_c + 1, max_j - 1) << '\n';
          int i, j; cin >> i >> j;
          if (i == 0 && j == 0) {
            done = true;
            break;
          }
          if (i == -1 && j == -1) {
            error = true;
            return 0;
          }
          filled[i][j] = true;
          max_i = max(max_i, i);
          max_j = max(max_j, j);
        }
        if (done) break;
      }
      if (done) break;
    }
    if (done) continue;
  }
}
